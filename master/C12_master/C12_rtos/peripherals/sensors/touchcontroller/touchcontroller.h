//
//  touch_controller.h
//  sensors
//
//  Created by Matthew Fonken on 7/27/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#ifndef touch_controller_h
#define touch_controller_h

#include "CPT112S.h"

#define TOUCH_SLIDER_NULL 0xff

typedef cpt_packet_t touch_packet_t;
typedef cpt_event_t touch_event_t;

static touch_packet_t ReadTouchController( comm_host_t * host )
{
    touch_packet_t packet;
    PerformI2CEvent(CPTFunctions.GetReadEvent( host, (cpt_packet_t*)&packet));
    return packet;
}

typedef struct
{
    touch_packet_t(*Read)( comm_host_t * );
} touch_controller_functions;

static touch_controller_functions TouchController =
{
    .Read = ReadTouchController
};

#endif /* touch_controller_h */
