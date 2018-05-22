#include "master.h"
#include <string.h>

//#define ACTIVE_CAMERA

uint8_t startingString[] = "******************\r\nStarting.\r\n",
				readyString[] = "Ready\r\n",
				testStartString[] = "Starting Test\r\n",
				alertString[] = "Alert!\r\n",
				interruptString[] = "Interrupt #";

uint16_t BUFFER_TX_DEL = (0xabcd);

uint16_t thresh_buffer_size = THRESH_BUFFER_SIZE;

extern void rho_init(void);
extern void frame_start(void);
extern void frame_end(void);
extern void row_int(void);
extern inline void pixel_proc(void);
extern void rho_proc( uint32_t t );

extern void asm_test(void);

rho_utility Rho;
typedef volatile uint8_t flag_t;
/***************************** Memory *****************************/
flag_t
	frame_flag,
	active_flag,
	process_flag,
	row_flag,
	row_parity,
	uart_dma_busy;
capture_t
    CAPTURE_BUFFER[CAPTURE_BUFFER_SIZE];    /* Raw capture buffer for DMA */
index_t
    THRESH_BUFFER[THRESH_BUFFER_SIZE],        /* Threshold processing buffer */
    CENTROID_X,
    CENTROID_Y;
density_t
    DENSITY_Y[CAPTURE_WIDTH],                                        /* Processed density X array */
    DENSITY_X[CAPTURE_HEIGHT],                                        /* Processed density Y array */
    QUADRANT_BUFFER[4],                                                                    /* Quadrant density array */
    QUADRANT_TOTAL,                                                            /* Total density */
    QUADRANT_PREVIOUS,                                                                /* Previous row density */
    DENSITY_X_MAX;
address_t
    CAPTURE_BUFFER_END,
    CAPTURE_BUFFER_MAX,
    THRESH_BUFFER_END,                                        /* Max threshold buffering size */
    THRESH_BUFFER_MAX,
    THRESH_VALUE,                                                    /* Shared threshold value */
    RHO_MEM_END;
/******************************************************************/

uint32_t CAMERA_PORT, UART_TX_ADDRESS, WR, RB;
uint8_t proc_flag = 0;
volatile uint16_t vcounter = 0, hcounter = 0, fcounter = 0, tcounter = 0, pcounter = 0;
#define HEX_LEN 20
uint8_t hex[HEX_LEN];
uint16_t x, y;

uint8_t irq = 0;

#define UART_TIMEOUT	100
UART_HandleTypeDef * this_uart;
TIM_HandleTypeDef * this_timer;

//static double now( void ) { return (double)HAL_GetTick()/1000; }
static void tog( void ) { HAL_GPIO_TogglePin( CAM__CS_GPIO_Port, CAM__CS_Pin ); }
static void set( GPIO_PinState s ) { HAL_GPIO_WritePin( CAM__CS_GPIO_Port, CAM__CS_Pin, s ); }
inline void irqEnable( void ) { irq = 1; }
inline void irqDisable( void ) { irq = 0; }

#define tg  r8  // Green toggle
#define rb  r9  // Write index of capture buffer
#define wr  r10 // Read index of threshold buffer
#define th	r11	// Threshold register
#define tp	r0

uint32_t rb, th, wr, tp;

void spoofFrameProcessor( void )
{
	while(uart_dma_busy);
	zero_memory();
	spoofPixels();
	frame_start();
	
	uint16_t x = 0, y = 0, p = 0, t = 0;
	for( ; y < CAPTURE_HEIGHT; y++ )
	{
		THRESH_BUFFER[t++] = 0xaaaa;
		for( x = 0; x < CAPTURE_WIDTH; x++, p++ )
		{
			if( CAPTURE_BUFFER[p] > THRESH_VALUE )
				THRESH_BUFFER[t++] = x;
		}
	}
	thresh_buffer_size = t - CAPTURE_HEIGHT + 1;
	rho_proc( thresh_buffer_size << 1 );
	
	Rho.density_map_pair.x.max = DENSITY_X_MAX;
	RhoFunctions.Filter_and_Select_Pairs( &Rho );
	RhoFunctions.Update_Prediction( &Rho );
}

void frameProcessor( void )
{
	while(uart_dma_busy);
	while(!frame_flag);
	tog();
	zero_memory();
	/* * * * * Register Protection Start * * * * */
	frame_start();
	while(frame_flag)
	{
		while(!row_flag);
		row_int();
		pcounter = 0;
		hcounter = 0;
		row_flag = 0;
		while( hcounter++ < CAPTURE_WIDTH && !row_flag )
		{
			pixel_proc();
		}
		vcounter++;
		tog();
	}
	rho_proc(0);
	/* * * * *  Register Protection End  * * * * */

	
	Rho.density_map_pair.x.max = DENSITY_X_MAX;
	RhoFunctions.Filter_and_Select_Pairs( &Rho );
	RhoFunctions.Update_Prediction( &Rho );
}



/***************************************************************************************/
/*                                      Core                                           */
/***************************************************************************************/
void master_init( I2C_HandleTypeDef * i2c, TIM_HandleTypeDef * timer, UART_HandleTypeDef * uart )
{
	this_uart = uart;
	this_timer = timer;
	//HAL_Delay(50);
	irqDisable();
    /* Debug delay */
	UART_Clear();

	print( startingString );

	init_memory();
	printAddresses();
	
	RhoFunctions.Init( &Rho, uart, CAPTURE_WIDTH, CAPTURE_HEIGHT );
	/*
	master_test();
	while(1);
	*/
	//master_test();
	
#ifdef ACTIVE_CAMERA
	initTimerDMA( timer );
	Camera.init(i2c);
	irqEnable();
#endif
	fcounter = 0;
	while( fcounter < 100 )
	{
		vcounter = 0;
		tcounter = 0;
		fcounter++;
		
#ifdef ACTIVE_CAMERA
		frameProcessor();
#else
		spoofFrameProcessor();
		HAL_Delay(100);
#endif
		
		//sprintf( (char *)hex, "\tF: %d | V: %d | R: %d\r\n", fcounter, vcounter, hcounter );
		//print( hex );
		//printBuffers( CAPTURE_BUFFER_WIDTH );
		//dprintBuffers();
		printPredictionPair( &Rho.prediction_pair );
	}
#ifdef ACTIVE_CAMERA
	irqDisable();
	Camera.disable();
	pauseDMA(timer);
#endif

	//printAddresses();

	//master_test();
  while(1);
}

void master_test( void )
{
	HAL_Delay(10);
	//print( testStartString );

	spoofDensityMaps();

	dprintBuffers();
	
	for( volatile int i = 0; i < 100; i++)
	{
		//HAL_Delay(10);
		//Rho.density_map_pair.x.max = DENSITY_X_MAX;
		RhoFunctions.Filter_and_Select_Pairs( &Rho );
		RhoFunctions.Update_Prediction( &Rho );
	}
	int xp = (int)Rho.prediction_pair.x.primary.value;
	int yp = (int)Rho.prediction_pair.y.primary.value;
	int xs = (int)Rho.prediction_pair.x.secondary.value;
	int ys = (int)Rho.prediction_pair.y.secondary.value;
	print("Printing predictions ");
	sprintf((char *)hex, "\tP(%d, %d) | S(%d, %d)\r\n", xp, yp, xs, ys);
	print( hex );
	return;
	while(1);
}

/***************************************************************************************/
/*                                    Callbacks                                        */
/***************************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(!irq) return;
	switch(GPIO_Pin)
	{
		case VSYNC_Pin:
			if(!(VSYNC_GPIO_Port->IDR & VSYNC_Pin))	
				frame_flag = 1;
			else 
				frame_flag = 0;
			return;
		case HREF_Pin:
			if(HREF_GPIO_Port->IDR & HREF_Pin) 
				row_flag = 1;
			return;
		default:
			return;
	}
}
/***************************************************************************************/
/*                              Spoof Generators                                       */
/***************************************************************************************/
void spoofPixels( void )
{
	/*
	bool t = 0;
	for(int y = 0; y < CAPTURE_BUFFER_HEIGHT; y++ )
	{
		for(int x = 0; x < CAPTURE_BUFFER_WIDTH; x+=2 )
		{
			int p = x + y * CAPTURE_BUFFER_WIDTH;
			CAPTURE_BUFFER[p+t] 	= 0xab;
			CAPTURE_BUFFER[p+1-t] = 0xcd;
		}
		t = !t;
	}
	*/
	
	capture_t c = THRESH_VALUE+1;
	int p, y, x;
	for( y = 20; y < 30; y++ )
	{
		for( x = 20; x < 30; x++ )
		{
			p = x + y * CAPTURE_BUFFER_WIDTH;
			CAPTURE_BUFFER[p] 	= c;
		}
		
		for( x = 100; x < 110; x++ )
		{
			p = x + y * CAPTURE_BUFFER_WIDTH;
			CAPTURE_BUFFER[p] 	= c;
		}
		
	}
	for( y = 80; y < 90; y++ )
	{
		for( x = 20; x < 30; x++ )
		{
			p = x + y * CAPTURE_BUFFER_WIDTH;
			CAPTURE_BUFFER[p] 	= c;
		}
		
		for( x = 100; x < 110; x++ )
		{
			p = x + y * CAPTURE_BUFFER_WIDTH;
			CAPTURE_BUFFER[p] 	= c;
		}
		
	}
	
}

void spoofDensityMaps( void )
{
	density_t S = 100, B = 10;
	int a,b;
	a = CAPTURE_WIDTH / 4; b = 3 * a;
	for(int x = 0; x < CAPTURE_WIDTH;  x++ )
		DENSITY_Y[x] = B;
	DENSITY_Y[a] 		= S;
	DENSITY_Y[a+1] 	= S;
	DENSITY_Y[b] 		= S;
	DENSITY_Y[b+1] 	= S;


	a = CAPTURE_HEIGHT / 4; b = 3 * a;
	for(int y = 0; y < CAPTURE_HEIGHT; y++ )
		DENSITY_X[y] = B;
	DENSITY_X[a] 		= S;
	DENSITY_X[a+1] 	= S;
	DENSITY_X[b] 		= S;
	DENSITY_X[b+1] 	= S;

	for( int i = 0; i < 4; i++ )
		QUADRANT_BUFFER[i] = S*2;
	QUADRANT_TOTAL = S*8;
}


/***************************************************************************************/
/*                                  Initializers                                       */
/***************************************************************************************/
void zero_memory( void )
{
	//memset(CAPTURE_BUFFER,	0, sizeof(capture_t)    * CAPTURE_BUFFER_SIZE );
	memset(THRESH_BUFFER,  	0, sizeof(index_t)      * THRESH_BUFFER_SIZE  );
	memset(DENSITY_X,       0, sizeof(density_t)  	* CAPTURE_HEIGHT      );
	memset(DENSITY_Y,       0, sizeof(density_t) 		* CAPTURE_WIDTH      	);
	memset(QUADRANT_BUFFER,	0, sizeof(density_t) 		* 4                   );
	QUADRANT_PREVIOUS = 0;
	
	uart_dma_busy = 0;
	/*
	frame_flag = 0;
	row_flag = 0;
	active_flag = 0;
	process_flag = 0;
	*/
}

void init_memory( void )
{
    zero_memory();

		RB = (address_t)CAPTURE_BUFFER;
		WR = (address_t)THRESH_BUFFER;

    CAMERA_PORT 		= (address_t)&(GPIOA->IDR);
		UART_TX_ADDRESS = (address_t)&(USART1->TDR);
#ifdef DYNAMIC_BUFFER
	CAPTURE_BUFFER_END = (address_t)CAPTURE_BUFFER+CAPTURE_WIDTH;
#else
	CAPTURE_BUFFER_END = (address_t)CAPTURE_BUFFER;
#endif
    CAPTURE_BUFFER_MAX = (address_t)CAPTURE_BUFFER + CAPTURE_BUFFER_SIZE;
    THRESH_BUFFER_MAX = (address_t)THRESH_BUFFER + sizeof(index_t)*(THRESH_BUFFER_SIZE-CAPTURE_HEIGHT);
		THRESH_BUFFER_END = (address_t)THRESH_BUFFER;
    CENTROID_X = 3;
    CENTROID_Y = 3;
    THRESH_VALUE = DEFAULT_THRESH;

    /* Initialize Rho Type */
    Rho.density_map_pair.x.length   = CAPTURE_HEIGHT;
    Rho.density_map_pair.y.length   = CAPTURE_WIDTH;
    Rho.density_map_pair.x.max      = 0;
    Rho.density_map_pair.y.max      = 0;
    Rho.density_map_pair.x.variance = 0.;
    Rho.density_map_pair.y.variance = 0.;

    rho_kalman_t * kpx = &Rho.density_map_pair.x.kalman,
                 * kpy = &Rho.density_map_pair.y.kalman;
    RhoKalman.init(kpx, 0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    RhoKalman.init(kpy, 0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);

    Rho.density_map_pair.x.map = DENSITY_X;
    Rho.density_map_pair.y.map = DENSITY_Y;
}

//static void TransferComplete(DMA_HandleTypeDef *DmaHandle) { tog(); }

void initTimerDMA( TIM_HandleTypeDef * timer )
{
    //print("Starting DMA from ");
    //sprintf((char *)hex, "0x%8x > 0x%8x\r\n", (uint32_t)CAMERA_PORT, (uint32_t)CAPTURE_BUFFER);
    //print( hex );
    //timer->hdma[TIM2_DMA_ID]->XferCpltCallback = TransferComplete;
    if(HAL_DMA_Start_IT(timer->hdma[TIM2_DMA_ID], CAMERA_PORT, (uint32_t)CAPTURE_BUFFER, CAPTURE_BUFFER_SIZE) != HAL_OK) Error_Handler();
    __HAL_TIM_ENABLE_DMA(timer, TIM2_DMA_CC);
    __HAL_TIM_ENABLE_IT(timer, TIM2_IT_CC);
    TIM_CCxChannelCmd(timer->Instance, TIM2_CHANNEL, TIM_CCx_ENABLE);
}
inline void pauseDMA( TIM_HandleTypeDef * timer )
{
    TIM_CCxChannelCmd(timer->Instance, TIM2_CHANNEL, TIM_CCx_DISABLE);
}

inline void resumeDMA( TIM_HandleTypeDef * timer )
{
    TIM_CCxChannelCmd(timer->Instance, TIM2_CHANNEL, TIM_CCx_ENABLE);
}



/***************************************************************************************/
/*                                    Printers                                         */
/***************************************************************************************/
void dprint( uint8_t * scrAddr, uint16_t len )
{
	while(uart_dma_busy);
	uart_dma_busy = 1;
	while(HAL_UART_Transmit_DMA( this_uart, scrAddr, len ) != HAL_OK);// Error_Handler();
}

void UART_Clear( void )
{
	uint8_t ascii_clear = 0x0c;
	HAL_UART_Transmit( this_uart, &ascii_clear, 1, UART_TIMEOUT );
}

void print( uint8_t * Buf )
{
	HAL_UART_Transmit( this_uart, Buf, strlen((const char *)Buf), UART_TIMEOUT );
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	uart_dma_busy = 0;
	uint8_t temp_buff[2] = { 0xef, 0x12 };
	HAL_UART_Transmit( this_uart, temp_buff, 2, UART_TIMEOUT );
}

void dprintBuffers( void )
{
	HAL_UART_Transmit( this_uart, (uint8_t *)&BUFFER_TX_DEL, 2, UART_TIMEOUT );
	dprint( (uint8_t *)DENSITY_Y, sizeof(density_t)*(CAPTURE_BUFFER_WIDTH + CAPTURE_BUFFER_HEIGHT ) );
}

void printBuffers( uint32_t s )
{
    print( "Printing Thresh Buffer\r\n" );
    printBuffer( THRESH_BUFFER, thresh_buffer_size );

    print( "Printing Dx\r\n" );
    drawDensityMap(DENSITY_X, CAPTURE_BUFFER_HEIGHT+1);

    print( "Printing Dy\r\n" );
    drawDensityMap(DENSITY_Y, CAPTURE_BUFFER_WIDTH);
}

void printAddress( const char * s, uint32_t addr )
{
    sprintf((char *)hex, "%s: %8x\r\n", s, addr);
    print( hex );
    HAL_Delay(100);
}

void printAddresses( void )
{
    printAddress("CamPt", (uint32_t)CAMERA_PORT);
    printAddress("C bfr", (uint32_t)CAPTURE_BUFFER);
    printAddress("C end", (uint32_t)CAPTURE_BUFFER_END);
    printAddress("C max", (uint32_t)CAPTURE_BUFFER_MAX);
    printAddress("T bfr", (uint32_t)THRESH_BUFFER);
    printAddress("T end", (uint32_t)THRESH_BUFFER_END);
    printAddress("T max", (uint32_t)THRESH_BUFFER_MAX);
    printAddress("   Dx", (uint32_t)DENSITY_X);
    printAddress("   Dy", (uint32_t)DENSITY_Y);
    printAddress("    Q", (uint32_t)QUADRANT_BUFFER);
    printAddress("Q tot", (uint32_t)&QUADRANT_TOTAL);
    printAddress("Q prv", (uint32_t)&QUADRANT_PREVIOUS);
    printAddress("   Cx", (uint32_t)&CENTROID_X);
    printAddress("   Cy", (uint32_t)&CENTROID_Y);
    printAddress("   Xm", (uint32_t)&DENSITY_X_MAX);
    printAddress("T val", (uint32_t)&THRESH_VALUE);
    printAddress("M end", (uint32_t)&RHO_MEM_END);
}

void printCapture( void )
{
	for(int y = 0; y < CAPTURE_BUFFER_HEIGHT; y++ )
	{
		for(int x = 0; x < CAPTURE_BUFFER_WIDTH; x++ )
		{
			uint32_t p = x + y * CAPTURE_BUFFER_WIDTH;
			sprintf((char *)hex, " 0x%2x", CAPTURE_BUFFER[p]);
			print( hex );
		}
		print( "\r\n" );
	}
}

void printBuffer( index_t * a, int l )
{
    for( int i = 0; i < l; i++ )
    {
        index_t curr = a[i];
        if( curr == 0xaaaa )
            sprintf((char *)hex, "\r\n(%d):", i);
        else
            sprintf((char *)hex, " 0x%x", curr);
        print( hex );
    }
    print("\r\n");
}

void drawDensityMap( density_t * a, int l )
{
    for( int i = 0; i < l; i++ )
    {
        density_t curr = a[i];
        sprintf((char *)hex, "%4d[%2d]", curr, i);
        print( hex );
        if( curr > 10 ) curr = 10;
        for( ; curr > 0; curr--) print( " " );
        print( "|\r\n" );
    }
}

void printPredictionPair( prediction_pair_t * pr )
{
	int xp = (int)pr->x.primary.value;
	int yp = (int)pr->y.primary.value;
	int xs = (int)pr->x.secondary.value;
	int ys = (int)pr->y.secondary.value;
	print("Printing predictions ");
	sprintf((char *)hex, "\t\t\tP(%d, %d) | S(%d, %d)\r\n", xp, yp, xs, ys);
	print( hex );
}