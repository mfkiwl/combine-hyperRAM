//
//  C11_component_list.h
//  C11_rtos
//
//  Created by Matthew Fonken on 8/6/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#ifndef C11_component_list_h
#define C11_component_list_h

#include "system_types.h"

/* Port spoof */
#define PORT0 0
#define PORTA 0
#define PORTB 0
#define PORTC 0
#define PORTD 0
#define PORTF 0

/* BNO080 - Primary Motion Sensor */
#define BNO080_ID         { SYSTEM_SENSOR, SYSTEM_SENSOR_MOTION_PRIMARY }
#define BNO080_FAMILY       SYSTEM_FAMILY_B
#define BNO080_COMM         SYSTME_COMM_SPI
#define BNO080_CHANN        SYSTEM_COMM_CHANNEL_PRIMARY
#define BNO080_ADDR         SYSTEM_COMM_ADDR_NONE
#define BNO080_PORT         PORTC
#define BNO080_PIN          9
#define BNO080_STATE        COMPONENT_STATE_OFF
#define BNO080_COMPONENT  { BNO080_ID, BNO080_FAMILY, BNO080_COMM, BNO080_CHANN, BNO080_ADDR, BNO080_PORT, BNO080_PIN, BNO080_STATE }

/* Camera Module - Primary Rho Sensor */
#define RHOMOD_ID         { SYSTEM_SENSOR, SYSTEM_SENSOR_RHO_MODULE_PRIMARY }
#define RHOMOD_FAMILY       SYSTEM_FAMILY_A
#define RHOMOD_COMM         SYSTME_COMM_UART
#define RHOMOD_CHANN        SYSTEM_COMM_CHANNEL_PRIMARY
#define RHOMOD_ADDR         SYSTEM_COMM_ADDR_NONE
#define RHOMOD_PORT         PORTA
#define RHOMOD_PIN          2
#define RHOMOD_STATE        COMPONENT_STATE_OFF
#define RHOMOD_COMPONENT  { RHOMOD_ID, RHOMOD_FAMILY, RHOMOD_COMM, RHOMOD_CHANN, RHOMOD_ADDR, RHOMOD_PORT, RHOMOD_PIN, RHOMOD_STATE }

/* CPT112S - Primary Touch Sensor */
#define CPT112_ID         { SYSTEM_SENSOR, SYSTEM_SENSOR_TOUCH_PRIMARY }
#define CPT112_FAMILY       SYSTEM_FAMILY_0
#define CPT112_COMM         SYSTEM_COMM_I2C
#define CPT112_CHANN        SYSTME_COMM_CHANNEL_PRIMARY
#define CPT112_ADDR         0xee
#define CPT112_PORT         PORTA
#define CPT112_PIN          2
#define CPT112_STATE        COMPONENT_STATE_INTERRUPT

#define CPT112_COMPONENT  { CPT112_ID, CPT112_FAMILY, CPT112_COMM, CPT112_CHANN, CPT112_ADDR, CPT112_PORT, CPT112_PIN, CPT112_STATE }

/* STC310 - Primary Touch Sensor */
#define STC310_ID         { SYSTEM_SENSOR, SYSTEM_SENSOR_BATTERY_MONITOR_PRIMARY }
#define STC310_FAMILY       SYSTEM_FAMILY_0
#define STC310_COMM         SYSTEM_COMM_I2C
#define STC310_CHANN        SYSTEM_COMM_CHANNEL_PRIMARY
#define STC310_ADDR         0x00
#define STC310_PORT         PORTA
#define STC310_PIN          2
#define STC310_STATE        COMPONENT_STATE_INTERRUPT
#define STC310_COMPONENT  { STC310_ID, STC310_FAMILY, STC310_COMM, STC310_CHANN, STC310_ADDR, STC310_PORT, STC310_PIN, STC310_STATE }

/* Tip Module - Primary Tip Sensor */
#define TIPMOD_ID         { SYSTEM_SENSOR, SYSTEM_SENSOR_BATTERY_MONITOR_PRIMARY }
#define TIPMOD_FAMILY       SYSTEM_FAMILY_C
#define TIPMOD_COMM         SYSTEM_COMM_I2C
#define TIPMOD_CHANN        SYSTEM_COMM_CHANNEL_PRIMARY
#define TIPMOD_ADDR         0x00
#define TIPMOD_PORT         PORT0
#define TIPMOD_PIN          0
#define TIPMOD_STATE        COMPONENT_STATE_INTERRUPT
#define TIPMOD_COMPONENT  { TIPMOD_ID, TIPMOD_FAMILY, TIPMOD_COMM, TIPMOD_CHANN, TIPMOD_ADDR, TIPMOD_PORT, TIPMOD_PIN, TIPMOD_STATE }

/* DRV2605L - Primary Haptic Motor Driver */
#define TIPMOD_ID         { SYSTEM_DRIVER, SYSTEM_DRIVER_HAPTIC_PRIMARY }
#define TIPMOD_FAMILY       SYSTEM_FAMILY_B
#define TIPMOD_COMM         SYSTEM_COMM_I2C
#define TIPMOD_CHANN        SYSTEM_COMM_CHANNEL_PRIMARY
#define TIPMOD_ADDR         0x00
#define TIPMOD_PORT         PORTF
#define TIPMOD_PIN          0
#define TIPMOD_STATE        COMPONENT_STATE_OFF
#define TIPMOD_COMPONENT  { TIPMOD_ID, TIPMOD_FAMILY, TIPMOD_COMM, TIPMOD_CHANN, TIPMOD_ADDR, TIPMOD_PORT, TIPMOD_PIN, TIPMOD_STATE }

/* XC9265 - 1.5v Voltage Regulator */
#define XC9265_ID         { SYSTEM_DRIVER, SYSTEM_DRIVER_REGULATOR_1V5 }
#define XC9265_FAMILY       SYSTEM_FAMILY_B
#define XC9265_COMM         SYSTEM_COMM_I2C
#define XC9265_CHANN        SYSTEM_COMM_CHANNEL_PRIMARY
#define XC9265_ADDR         0x00
#define XC9265_PORT         PORTF
#define XC9265_PIN          0
#define XC9265_STATE        COMPONENT_STATE_OFF
#define XC9265_COMPONENT  { XC9265_ID, XC9265_FAMILY, XC9265_COMM, XC9265_CHANN, XC9265_ADDR, XC9265_PORT, XC9265_PIN, XC9265_STATE }

static sys_component_t C11_V1_ComponentList[] =
{
    BNO080_COMPONENT,
    RHOMOD_COMPONENT,
    CPT112_COMPONENT,
    STC310_COMPONENT,
    TIPMOD_COMPONENT,
    XC9265_COMPONENT
};

#endif /* C11_component_list_h */
