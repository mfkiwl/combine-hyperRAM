#include "master.h"
#include <string.h>

uint8_t startingString[] = "******************\r\nStarting.\r\n",
				readyString[] = "Ready\r\n",
				testStartString[] = "Starting Test\r\n",
				alertString[] = "Alert!\r\n",
				interruptString[] = "Interrupt #";


extern void rho_init(void);
extern void frame_start(void);
extern void frame_end(void);
extern void row_int(void);
extern void pixel_proc(void);
extern void rho_proc(void);

extern void asm_test(void);

rho_utility Rho;

/***************************** Memory *****************************/
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

uint32_t CAMERA_PORT;
uint8_t proc_flag = 0;
volatile uint8_t flag = 0, frame_flag = 0, row_flag = 0;
volatile uint16_t vcounter = 0, hcounter = 0;
#define HEX_LEN 20
uint8_t hex[HEX_LEN];
uint16_t x, y;

#define UART_TIMEOUT	100
UART_HandleTypeDef * this_uart;
TIM_HandleTypeDef * this_timer;

static void UART_Clear( void )
{
	uint8_t ascii_clear = 0x0c;
	HAL_UART_Transmit( this_uart, &ascii_clear, 1, UART_TIMEOUT );
}

static void print(uint8_t* Buf)
{
	HAL_UART_Transmit( this_uart, Buf, strlen((const char *)Buf), UART_TIMEOUT );
}

/*
static void spoofPixels( void )
{
	bool t = 0;
	for(int y = 0; y < CAPTURE_BUFFER_HEIGHT; y++ )
	{
		for(int x = 0; x < CAPTURE_BUFFER_WIDTH; x+=2 )
		{
			int p = x + y * CAPTURE_BUFFER_WIDTH;
			CAPTURE_BUFFER[p+t] 	= 0xcd;
			CAPTURE_BUFFER[p+1-t] = 0xab;
		}
		t = !t;
	}
}
*/

static void spoofDensityMaps( void )
{
	for(int x = 0; x < CAPTURE_WIDTH;  x++ )
		DENSITY_Y[x] = 0x00;
	DENSITY_Y[3] = 0x3a;
	DENSITY_Y[4] = 0x30;
	DENSITY_Y[15] = 0x3a;
	DENSITY_Y[16] = 0x30;
	
	for(int y = 0; y < CAPTURE_HEIGHT; y++ )
		DENSITY_X[y] = 0x00;
	DENSITY_X[1] = 0x30;
	DENSITY_X[2] = 0x3a;
	DENSITY_X[3] = 0x30;
	DENSITY_X[10] = 0x33;
	DENSITY_X[11] = 0x3a;
	DENSITY_X[12] = 0x33;
}

//static double now( void ) { return (double)HAL_GetTick()/1000; }

/***************************************************************************************/
/*                                      Core                                           */
/***************************************************************************************/
void master_init( I2C_HandleTypeDef * i2c, TIM_HandleTypeDef * timer, DMA_HandleTypeDef * dma, UART_HandleTypeDef * uart )
{
	this_uart = uart;
	this_timer = timer;
	HAL_Delay(50);
	HAL_NVIC_DisableIRQ(VSYNC_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(HREF_EXTI_IRQn);
    /* Debug delay */
	UART_Clear();
	
	print( startingString );
	init_memory();
	
  
	//RhoFunctions.Init( &Rho, uart, CAPTURE_WIDTH, CAPTURE_HEIGHT );

	Camera.init(i2c);
	
	
	initTimerDMA( timer, dma );
	//HAL_Delay(20);
	//double before = now();
	//asm_test();
	while(  HAL_GPIO_ReadPin( VSYNC_GPIO_Port, VSYNC_Pin ));
	while( !HAL_GPIO_ReadPin( VSYNC_GPIO_Port, VSYNC_Pin ));
	HAL_NVIC_EnableIRQ(VSYNC_EXTI_IRQn);
  HAL_NVIC_EnableIRQ(HREF_EXTI_IRQn);
	while(!frame_flag);
	//while(!row_flag)
		//pixel_proc();
	HAL_Delay(20);
	//double after = now();
	pauseDMA(timer);
	//rho_proc();
	
	print( "DMA Paused\r\n" );
	sprintf( (char *)hex, "\tV: %d | H: %d\r\n", vcounter, hcounter );
	print( hex );
	//sprintf((char *)hex, "\tTime elapsed: %f\r\n", after-before);
	//print( hex );
	printAddresses();
  while(1);
}

void master_test( void )
{
	print( testStartString );
	
	spoofDensityMaps();
	
	print( "Printing Dx\r\n" );
	drawDensityMap(DENSITY_X, CAPTURE_HEIGHT);
	
	print( "Printing Dy\r\n" );
	drawDensityMap(DENSITY_Y, CAPTURE_WIDTH);
	
	for( volatile int i = 0; i < 100; i++)
	{		
		HAL_Delay(10);
		Rho.density_map_pair.x.max = DENSITY_X_MAX;
		RhoFunctions.Filter_and_Select_Pairs( &Rho );
		RhoFunctions.Update_Prediction( &Rho );
		int xp = (int)Rho.prediction_pair.x.primary.value;
		int yp = (int)Rho.prediction_pair.y.primary.value;
		int xs = (int)Rho.prediction_pair.x.secondary.value;
		int ys = (int)Rho.prediction_pair.y.secondary.value;
		print("Printing predictions ");
		sprintf((char *)hex, "\t\t\tP(%d, %d) | S(%d, %d)\r\n", xp, yp, xs, ys);
		print( hex );
	}
	while(1);
}

/***************************************************************************************/
/*                                    Callbacks                                        */
/***************************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case VSYNC_Pin:
			if( !HAL_GPIO_ReadPin( VSYNC_GPIO_Port, VSYNC_Pin ) )
			{
				if( !frame_flag )
				{
					frame_start();
					row_int();
					vcounter++;
				}
				frame_flag = !frame_flag;
			}
			else 
			{
				if( frame_flag )
				{
					Camera.disable();
				}
			}
			
			break;
		case HREF_Pin:
			if( frame_flag )
			{
				if( row_flag )
				{
					row_int();
				}
				else
				{
					
				}
					
				hcounter++;
				row_flag = !row_flag;
			}
		default:
			break;
	}
}


/***************************************************************************************/
/*                                  Initializers                                       */
/***************************************************************************************/
void zero_memory( void )
{
    memset(CAPTURE_BUFFER,	0, sizeof(capture_t)    * CAPTURE_BUFFER_SIZE );
    memset(THRESH_BUFFER,  	0, sizeof(index_t)      * THRESH_BUFFER_SIZE  );
    memset(DENSITY_X,       0, sizeof(density_t)  	* CAPTURE_WIDTH       );
    memset(DENSITY_Y,       0, sizeof(density_t) 		* CAPTURE_HEIGHT      );
    memset(QUADRANT_BUFFER,	0, sizeof(density_t) 		* 4                   );
    QUADRANT_PREVIOUS = 0;
}

void init_memory( void )
{
    zero_memory();
    CAMERA_PORT = (address_t)&(GPIOA->IDR);
#ifdef DYNAMIC_BUFFER
	CAPTURE_BUFFER_END = (address_t)CAPTURE_BUFFER+CAPTURE_WIDTH;
#else
	CAPTURE_BUFFER_END = (address_t)CAPTURE_BUFFER;
#endif
    CAPTURE_BUFFER_MAX = (address_t)CAPTURE_BUFFER + CAPTURE_BUFFER_SIZE;
    THRESH_BUFFER_MAX = (address_t)THRESH_BUFFER + sizeof(index_t)*THRESH_BUFFER_SIZE;
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
    Rho.density_map_pair.y.map = DENSITY_X;
}

//static void TransferComplete(DMA_HandleTypeDef *DmaHandle) { flag = 1; }

void initTimerDMA( TIM_HandleTypeDef * timer, DMA_HandleTypeDef * dma )
{
    print("Starting DMA from ");
    sprintf((char *)hex, "0x%8x > 0x%8x\r\n", (uint32_t)CAMERA_PORT, (uint32_t)CAPTURE_BUFFER);
    print( hex );
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
void printBuffers( uint32_t r, uint32_t s )
{
    print( "Printing Thresh Buffer\r\n" );
    printBuffer(THRESH_BUFFER, THRESH_BUFFER_SIZE);

    print( "Printing Dx\r\n" );
    drawDensityMap(DENSITY_X, s);

    print( "Printing Dy\r\n" );
    drawDensityMap(DENSITY_Y, s);
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
