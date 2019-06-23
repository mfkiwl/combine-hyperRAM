//
//  rho_client.c
//  rho_client
//
//  Created by Matthew Fonken on 9/19/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#include "rho_client.h"

//#define __ASSEMBLY_RHO__
// #define __CHECK_FRAME_FLAG__

__attribute__((naked)) inline void PixelThreshLoop(
                            register byte_t * capture_address,   // capture buffer index
                            register index_t * thresh_address,    // address of thresh buffer
                            const register byte_t thresh_value,
                            const register byte_t sub_sample,
                            const register index_t width,
                            const register address_t capture_buffer,
                            const register address_t flag_address )
{
    register uint32_t working_register;
    // = *capture_address;
    //  register address_t capture_base = (address_t)RhoSystem.Variables.Buffers.Capture;
    //  register register_t capture_offset = 0;
#ifndef __ASSEMBLY_RHO__
    while( 1 )
    {
#ifdef __CHECK_FRAME_FLAG__
        working_register = *flag_address;
        if( working_register ) return;
#endif
        capture_address += sub_sample;
        if(capture_address >= width) return;

        working_register = *(capture_address);
        if(working_register >= thresh )
        {
            working_register = capture_address - capture_buffer;
            *(thresh_address++) = working_register;
        }
    }
#else
    __asm volatile
    (
    ".capture:\n\t"
#ifdef __CHECK_FRAME_FLAG__
        "ldrb    %0, [%7]    ; Load flag byte\n\t"
        "cmp     %0, #1      ; Check if set\n\t"
        "bge     .end        ; End if set\n\t"
#endif
        "add     %2, %2, %1  ; Increment capture index by sub_sample\n\t"
        "cmp     %2, %3      ; Check if capture index has reach buffer Width\n\t"
        "bge     .end        ; If so end\n\t"

        "ldrb    %0, [%2]    ; Load byte at capture index into RO\n\t"
        "cmp     %0, %4      ; Compare with threshold value\n\t"
        "blt     .capture    ; If less than, continue to next capture\n\t"

        "sub     %0, %2, %5  ; Subtract capture buffer start from index\n\t"
        "strw    %0, [%6]    ; Store offset word at thresh index\n\t"
        "add     %6, %6, #2  ; Increment thresh index by word\n\t"
        "b       .capture    ; Branch back to next capture\n"
    ".end\n"
        ::
        "r"(working_register),  // %0
        "r"(sub_sample),        // %1
        "r"(capture_address),   // %2
        "r"(width),             // %3
        "r"(thresh_value),      // %4
        "r"(capture_buffer),    // %5
        "r"(thresh_address),    // %6
        "r"(flag_address)       // %7
    );
#endif
}

inline index_t CaptureFrame()
{
    while(RhoSystem.Variables.Flags.Row);
    address_t
    capture_buffer = RhoSystem.Variables.Buffers.Capture;
    row_flag = RhoSystem.Variables.Flags.Row;
    index_t
    y_counter = (index_t)RhoSystem.Variables.Utility.Height,
    t_counter = 0,
    t_max = (index_t)((uint32_t)RhoSystem.Variables.Addresses.ThreshMax - (uint32_t)RhoSystem.Variables.Buffers.Thresh);
    width = RhoSystem.Variables.Utility.Width;
    byte_t
    thresh_value = (byte_t)RhoSystem.Variables.Utility.Thresh,
    *capture_address = RhoSystem.Variables.Buffers.Capture,
    sub_sample = (byte_t)RhoSystem.Variables.Utility.Subsample;
    index_t
    *thresh_address = RhoSystem.Variables.Buffers.Thresh;
    while( ( --y_counter > 0 ) && ( t_counter < t_max ) )
    {
        RhoSystem.Variables.Buffers.Thresh[t_counter++] = Y_DEL;
        while(RhoSystem.Variables.Flags.Row);
        PixelThreshLoop(
            capture_address,
            thresh_address,
            thresh_value,
            sub_sample,
            width,
            capture_buffer,
            row_flag );
        while(!RhoSystem.Variables.Flags.Row);
    }
    return t_counter;
}

inline section_process_t ProcessFrameSection( register index_t t_counter, register index_t t_len, register index_t y_counter, register index_t y_len )
{
    register index_t t_value = 0;
    register density_2d_t Q_left = 0, Q_right = 0, Q_total = 0, Q_prev = 0;
    while( t_counter < t_len )
    {
        t_value = RhoSystem.Variables.Buffers.Thresh[t_counter++];
        if(t_value == Y_DEL)
        {
            Q_total = Q_left + Q_right;
            RhoSystem.Variables.Utility.DensityMapPair.x.map[y_counter] = Q_total - Q_prev;
            Q_prev = Q_total;
            if( ++y_counter > y_len ) break;
        }
        else if( t_value < RhoSystem.Variables.Utility.Cx )
        {
            Q_left++;
            RhoSystem.Variables.Utility.DensityMapPair.y.map[t_value]++;
        }
        else
        {
            Q_right++;
            RhoSystem.Variables.Utility.DensityMapPair.y.map[t_value]++;
        }
    }
    return (section_process_t){ t_counter, y_counter, Q_left, Q_right };
}

inline void ActivateBackgrounding( void )
{
    RhoSystem.Variables.Flags.Backgrounding = true;
    RhoSystem.Variables.Buffers.DensityX = RhoSystem.Variables.Utility.DensityMapPair.x.background;
    RhoSystem.Variables.Buffers.DensityY = RhoSystem.Variables.Utility.DensityMapPair.y.background;
    RhoSystem.Variables.Buffers.Quadrant = RhoSystem.Variables.Utility.Qb;
}

inline void DeactivateBackgrounding( void )
{
    RhoSystem.Variables.Flags.Backgrounding = false;
    RhoSystem.Variables.Buffers.DensityX = RhoSystem.Variables.Utility.DensityMapPair.x.map;
    RhoSystem.Variables.Buffers.DensityY = RhoSystem.Variables.Utility.DensityMapPair.y.map;
    RhoSystem.Variables.Buffers.Quadrant = RhoSystem.Variables.Utility.Q;
}

inline void FilterPixelCount( index_t * PixelCount, index_t NewCount )
{
    *PixelCount = (index_t)( ( (floating_t)(*PixelCount) * ( 1. - PIXEL_COUNT_TRUST_FACTOR ) ) + ( (floating_t)NewCount * PIXEL_COUNT_TRUST_FACTOR ) );
}

inline bool HasPixelCountDrop( index_t * PixelCount, index_t NewCount )
{
    index_t OldCount = *PixelCount;
    FilterPixelCount( PixelCount, NewCount );
    return ( *PixelCount < ( (floating_t)OldCount * PIXEL_COUNT_DROP_FACTOR ) );
}

inline void ProcessFrame( index_t t_len )
{
    if( HasPixelCountDrop( (index_t *)RhoSystem.Variables.Addresses.PixelCount, t_len ) )
        ActivateBackgrounding();
    else DeactivateBackgrounding();

    uint8_t start = 0, end = 0;
    section_process_t ProcessedTopSectionData    = ProcessFrameSection( start, t_len, end, RhoSystem.Variables.Utility.Cy );
    start   = ProcessedTopSectionData.pixels;
    end     = ProcessedTopSectionData.rows;
    section_process_t ProcessedBottomSectionData = ProcessFrameSection( start, t_len, end, RhoSystem.Variables.Utility.Height );

    RhoSystem.Variables.Buffers.Quadrant[0] = ProcessedTopSectionData.left;
    RhoSystem.Variables.Buffers.Quadrant[1] = ProcessedTopSectionData.right;
    RhoSystem.Variables.Buffers.Quadrant[2] = ProcessedBottomSectionData.left;
    RhoSystem.Variables.Buffers.Quadrant[3] = ProcessedBottomSectionData.right;

    //    RhoSystem.Variables.Buffers.DensityX[CAPTURE_BUFFER_HEIGHT-1] = FRAME_ROW_END;ı
}

void ProcessRhoSystemFrameCapture( void )
{
    RhoSystem.Functions.Memory.Zero();
    while(!RhoSystem.Variables.Flags.Frame);

    ProcessFrame( CaptureFrame() );
}

inline void PerformRhoSystemProcess( void )
{
    RhoSystem.Functions.Perform.FrameCapture();
    RhoSystem.Functions.Perform.CoreProcess();
    RhoSystem.Functions.Perform.TransmitPacket();
}

void ActivateRhoSystem( void  )
{
    RhoSystem.Variables.Flags.Active = true;
    RhoSystem.Functions.Perform.TransmitPacket();
}

void DeactivateRhoSystem( void )
{
    RhoSystem.Variables.Flags.Active = false;
    // TODO: zero period
    RhoSystem.Functions.Perform.TransmitPacket();
}

void TransmitRhoSystemPacket( void )
{
    RhoSystem.Functions.Platform.Host.Transmit( (byte_t *)&RhoSystem.Variables.Utility.Packet, sizeof(packet_t) );
}
/***************************************************************************************/
/*                                  Initializers                                       */
/***************************************************************************************/
void InitRhoSystem( address_t CameraPort, address_t HostTxPort )
{
    DeactivateBackgrounding();

    RhoSystem.Variables.Addresses.CameraPort  = CameraPort;
    RhoSystem.Variables.Addresses.HostTxPort  = HostTxPort;

#ifdef DYNAMIC_BUFFER
    RhoSystem.Variables.Addresses.CaptureEnd  = (address_t)RhoSystem.Variables.Buffers.Capture[CAPTURE_WIDTH];
#else
    RhoSystem.Variables.Addresses.CaptureEnd  = (address_t)RhoSystem.Variables.Buffers.Capture;
#endif
    RhoSystem.Variables.Addresses.CaptureMax  = (address_t)RhoSystem.Variables.Buffers.Capture[THRESH_BUFFER_SIZE];
    RhoSystem.Variables.Addresses.ThreshMax   = (address_t)RhoSystem.Variables.Buffers.Thresh[THRESH_BUFFER_MAX];
    RhoSystem.Variables.Addresses.ThreshEnd   = (address_t)RhoSystem.Variables.Buffers.Thresh;

    RhoSystem.Variables.Buffers.BeaconPacket  = malloc( sizeof( packet_t ) );
    RhoSystem.Variables.Buffers.BeaconPacket->header.ID = BEACON_PACKET_ID;
    RhoSystem.Variables.Buffers.BeaconPacket->header.includes = BEACON_DEFAULT_PERIOD;

    RhoSystem.Functions.Memory.Zero();
    RhoSystem.Functions.Perform.Init( (address_t)CAPTURE_WIDTH, (address_t)CAPTURE_HEIGHT );
}

void ConnectRhoSystemPlatformInterface( platform_interface_functions * platform_interface, camera_application_flags * flags )
{
  memcpy( (void *)&RhoSystem.Functions.Platform, platform_interface, sizeof(platform_interface_functions) );
  RhoSystem.Variables.Flags = flags;

//     RhoSystem.Functions.Platform.DMA.Init       = PlatformInterface->DMA.Init;
//     RhoSystem.Functions.Platform.DMA.Pause      = PlatformInterface->DMA.Pause;
//     RhoSystem.Functions.Platform.DMA.Resume     = PlatformInterface->DMA.Resume;
//     RhoSystem.Functions.Platform.DMA.Reset      = PlatformInterface->DMA.Reset;
//
//     RhoSystem.Functions.Platform.Host.Transmit = PlatformInterface->Host.Transmit;
//
// //    RhoSystem.Functions.Platform.Flags.Activate = PlatformInterface->Flags.Activate;
//
//     RhoSystem.Functions.Platform.Time.Now       = PlatformInterface->Time.Now;
}

void ConfigureRhoSystem( void )
{
  RhoSystem.Functions.Platform.DMA.Init( RhoSystem.Variables.Addresses.CameraPort, (address_t)RhoSystem.Variables.Buffers.Capture );
}

void ZeroRhoSystemMemory( void )
{
    memset( RhoSystem.Variables.Buffers.Thresh,   0, sizeof(index_t)   * THRESH_BUFFER_SIZE );
    memset( RhoSystem.Variables.Buffers.Quadrant, 0, sizeof(density_t) * 4                  );
}