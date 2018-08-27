//
//  C11_profile.h
//  C11_rtos
//
//  Created by Matthew Fonken on 8/9/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#ifndef C11_profile_h
#define C11_profile_h

#include "systemtypes.h"

/* Port spoof */
#define PORT0 0
#define PORTA 0
#define PORTB 0
#define PORTC 0
#define PORTD 0
#define PORTF 0

/* BNO080 - Primary Motion Sensor */
#define BNO080_ID           SYSTEM_COMPONENT_MOTION_PRIMARY
#define BNO080_FAMILY       SYSTEM_FAMILY_B
#define BNO080_COMM         COMM_SPI
#define BNO080_CHANN        COMM_CHANNEL_PRIMARY
#define BNO080_ADDR         COMM_ADDR_NONE
#define BNO080_PORT         PORTC
#define BNO080_PIN          9
#define BNO080_STATE        COMPONENT_STATE_OFF
#define BNO080_COMPONENT  { BNO080_ID, BNO080_FAMILY, BNO080_COMM, BNO080_CHANN, BNO080_ADDR, BNO080_PORT, BNO080_PIN, BNO080_STATE }

/* Camera Module - Primary Rho Sensor */
#define RHOMOD_ID           SYSTEM_COMPONENT_RHO_MODULE_PRIMARY
#define RHOMOD_FAMILY       SYSTEM_FAMILY_A
#define RHOMOD_COMM         COMM_UART
#define RHOMOD_CHANN        COMM_CHANNEL_PRIMARY
#define RHOMOD_ADDR         COMM_ADDR_NONE
#define RHOMOD_PORT         PORTA
#define RHOMOD_PIN          2
#define RHOMOD_STATE        COMPONENT_STATE_OFF
#define RHOMOD_COMPONENT  { RHOMOD_ID, RHOMOD_FAMILY, RHOMOD_COMM, RHOMOD_CHANN, RHOMOD_ADDR, RHOMOD_PORT, RHOMOD_PIN, RHOMOD_STATE }

/* CPT112S - Primary Touch Sensor */
#define CPT112_ID           SYSTEM_COMPONENT_TOUCH_PRIMARY
#define CPT112_FAMILY       SYSTEM_FAMILY_0
#define CPT112_COMM         COMM_I2C
#define CPT112_CHANN        COMM_CHANNEL_PRIMARY
#define CPT112_ADDR         0xee
#define CPT112_PORT         PORTA
#define CPT112_PIN          2
#define CPT112_STATE        COMPONENT_STATE_INTERRUPT
#define CPT112_COMPONENT  { CPT112_ID, CPT112_FAMILY, CPT112_COMM, CPT112_CHANN, CPT112_ADDR, CPT112_PORT, CPT112_PIN, CPT112_STATE }

/* STC310 - Primary Touch Sensor */
#define STC310_ID           SYSTEM_COMPONENT_BATTERY_MONITOR_PRIMARY
#define STC310_FAMILY       SYSTEM_FAMILY_0
#define STC310_COMM         COMM_I2C
#define STC310_CHANN        COMM_CHANNEL_PRIMARY
#define STC310_ADDR         0x00
#define STC310_PORT         PORTA
#define STC310_PIN          2
#define STC310_STATE        COMPONENT_STATE_INTERRUPT
#define STC310_COMPONENT  { STC310_ID, STC310_FAMILY, STC310_COMM, STC310_CHANN, STC310_ADDR, STC310_PORT, STC310_PIN, STC310_STATE }

/* Tip Module - Primary Tip Sensor */
#define TIPMOD_ID           SYSTEM_COMPONENT_TIP_PRIMARY
#define TIPMOD_FAMILY       SYSTEM_FAMILY_C
#define TIPMOD_COMM         COMM_I2C
#define TIPMOD_CHANN        COMM_CHANNEL_PRIMARY
#define TIPMOD_ADDR         0x00
#define TIPMOD_PORT         PORT0
#define TIPMOD_PIN          0
#define TIPMOD_STATE        COMPONENT_STATE_INTERRUPT
#define TIPMOD_COMPONENT  { TIPMOD_ID, TIPMOD_FAMILY, TIPMOD_COMM, TIPMOD_CHANN, TIPMOD_ADDR, TIPMOD_PORT, TIPMOD_PIN, TIPMOD_STATE }

/* DRV2605L - Primary Haptic Motor Driver */
#define DRV260_ID           SYSTEM_COMPONENT_HAPTIC_PRIMARY
#define DRV260_FAMILY       SYSTEM_FAMILY_B
#define DRV260_COMM         COMM_I2C
#define DRV260_CHANN        COMM_CHANNEL_PRIMARY
#define DRV260_ADDR         0x00
#define DRV260_PORT         PORTF
#define DRV260_PIN          0
#define DRV260_STATE        COMPONENT_STATE_OFF
#define DRV260_COMPONENT  { DRV260_ID, DRV260_FAMILY, DRV260_COMM, DRV260_CHANN, DRV260_ADDR, DRV260_PORT, DRV260_PIN, DRV260_STATE }

/* XC9265 - 1.5v Voltage Regulator */
#define XC9265_ID           SYSTEM_COMPONENT_REGULATOR_1V5
#define XC9265_FAMILY       SYSTEM_FAMILY_A
#define XC9265_COMM         COMM_NONE
#define XC9265_CHANN        COMM_CHANNEL_NONE
#define XC9265_ADDR         0x00
#define XC9265_PORT         PORTF
#define XC9265_PIN          0
#define XC9265_STATE        COMPONENT_STATE_OFF
#define XC9265_COMPONENT  { XC9265_ID, XC9265_FAMILY, XC9265_COMM, XC9265_CHANN, XC9265_ADDR, XC9265_PORT, XC9265_PIN, XC9265_STATE }

#define SYSTEM_NO_TASK { \
.ID.interrupter = SYSTEM_SCHEDULER_ID_NONE, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_NONE, SYSTEM_PROFILE_ENTRY_DIRECTION_NONE, SYSTEM_PROFILE_ENTRY_TYPE_NONE }, \
.data.info = { 0 }, \
.component = SYSTEM_COMPONENT_NONE, \
.handler_id = SYSTEM_SUBACTIVITY_NONE }

#define SYSTEM_SENSOR_MOTION_PRIMARY_INTERRUPT_ENTRY { \
.ID.interrupter = SYSTEM_SCHEDULER_ID_MOTION_INTERRUPT, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_INPUT, SYSTEM_PROFILE_ENTRY_TYPE_INTERRUPT }, \
.data.info = { 0 }, \
.component = SYSTEM_SENSOR_MOTION_PRIMARY, \
.handler_id = SYSTEM_SUBACTIVITY_HANDLE_MOTION_EVENT }

#define SYSTEM_SENSOR_TOUCH_PRIMARY_INTERRUPT_ENTRY { \
.ID.interrupter = SYSTEM_SCHEDULER_ID_TOUCH_INTERRUPT, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_INPUT, SYSTEM_PROFILE_ENTRY_TYPE_INTERRUPT }, \
.data.info = { 0 }, \
.component = SYSTEM_SENSOR_TOUCH_PRIMARY, \
.handler_id = SYSTEM_SUBACTIVITY_HANDLE_TOUCH_EVENT }

#define SYSTEM_SENSOR_TIP_SCHEDULED_PROBE_ENTRY { \
.ID.scheduler = SYSTEM_SCHEDULER_ID_TIP_POLL, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_OUTPUT, SYSTEM_PROFILE_ENTRY_TYPE_SCHEDULED }, \
.data.schedule = 0, \
.component = SYSTEM_SENSOR_TIP_PRIMARY, \
.handler_id = SYSTEM_SUBACTIVITY_POLL_TIP }

#define SYSTEM_SENSOR_BATTERY_MONITOR_SCHEDULED_PROBE_ENTRY { \
.ID.scheduler = SYSTEM_SCHEDULER_ID_BATTERY_MONITOR_POLL, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_OUTPUT, SYSTEM_PROFILE_ENTRY_TYPE_SCHEDULED }, \
.data.schedule = 0, \
.component = SYSTEM_SENSOR_BATTERY_MONITOR_PRIMARY, \
.handler_id = SYSTEM_SUBACTIVITY_POLL_BATTERY_MONITOR }

#define SYSTEM_SENSOR_RHO_RECEIVE_INTERRUPT_ENTRY { \
.ID.interrupter = SYSTEM_SCHEDULER_ID_RHO_INTERRUPT, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_INPUT, SYSTEM_PROFILE_ENTRY_TYPE_INTERRUPT }, \
.data.info = { 0 }, \
.component = SYSTEM_SENSOR_RHO_MODULE_PRIMARY, \
.handler_id = SYSTEM_SUBACTIVITY_HANDLE_RHO_EVENT }

#define SYSTEM_DRIVER_HAPTIC_PRIMARY_TRIGGER_ENTRY { \
.ID.interrupter = SYSTEM_INTERRUPTER_ID_HAPTIC_TRIGGER, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_OUTPUT, SYSTEM_PROFILE_ENTRY_TYPE_INTERRUPT }, \
.data.info = { 0 }, \
.component = SYSTEM_DRIVER_HAPTIC_PRIMARY, \
.handler_id = SYSTEM_SUBACTIVITY_TRIGGER_HAPTIC }

#define COMMUNICATION_HOST_SCHEDULED_TRANSMIT_PACKET_ENTRY { \
.ID.scheduler = SYSTEM_INTERRUPTER_ID_TAU_PACKET_TRANSMIT, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_OUTPUT, SYSTEM_PROFILE_ENTRY_TYPE_SCHEDULED }, \
.data.schedule = 0, \
.component = SYSTEM_DRIVER_BLE_RADIO, \
.handler_id = SYSTEM_SUBACTIVITY_TRANSMIT_HOST_PACKET }

#define COMMUNICATION_HOST_RECEIVE_PACKET_INTERRUPT_ENTRY { \
.ID.interrupter = SYSTEM_INTERRUPTER_ID_TAU_PACKET_RECEIVE, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_INPUT, SYSTEM_PROFILE_ENTRY_TYPE_SCHEDULED }, \
.data.schedule = 0, \
.component = SYSTEM_DRIVER_BLE_RADIO, \
.handler_id = SYSTEM_SUBACTIVITY_RECEIVE_HOST_PACKET }

#define COMMUNICATION_SUB_TRANSMIT_PACKET_INTERRUPT_ENTRY { \
.ID.interrupter = SYSTEM_INTERRUPTER_ID_SUB_RADIO_PACKET_TRANSMIT, \
.header = { SYSTEM_PROFILE_ENTRY_STATE_ENABLED, SYSTEM_PROFILE_ENTRY_DIRECTION_OUTPUT, SYSTEM_PROFILE_ENTRY_TYPE_INTERRUPT }, \
.data.info = { 0 }, \
.component = SYSTEM_DRIVER_SUB_RADIO, \
.handler_id = SYSTEM_SUBACTIVITY_TRANSMIT_SUB_RADIO_PACKET }

#define SYSTEM_TASK_SHELF_ENTRY_NULL { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS, \
.num_interrupts = 0, \
.interrupts = { SYSTEM_NO_TASK }, \
.num_scheduled = 0, \
.scheduled = { SYSTEM_NO_TASK } }

#define SYSTEM_TASK_SHELF_ENTRY_SENSOR_MOTION_TASKS { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_SENSOR_MOTION_TASKS, \
.num_interrupts = 1, \
.interrupts = { SYSTEM_SENSOR_MOTION_PRIMARY_INTERRUPT_ENTRY }, \
.num_scheduled = 0, \
.scheduled = { SYSTEM_NO_TASK } }

#define SYSTEM_TASK_SHELF_ENTRY_SENSOR_TOUCH_TASKS { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_SENSOR_TOUCH_TASKS, \
.num_interrupts = 1, \
.interrupts = { SYSTEM_SENSOR_TOUCH_PRIMARY_INTERRUPT_ENTRY }, \
.num_scheduled = 0, \
.scheduled = { SYSTEM_NO_TASK } }

#define SYSTEM_TASK_SHELF_ENTRY_SENSOR_TIP_TASKS { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_SENSOR_TIP_TASKS, \
.num_interrupts = 0, \
.interrupts = { SYSTEM_NO_TASK }, \
.num_scheduled = 1, \
.scheduled = { SYSTEM_SENSOR_TIP_SCHEDULED_PROBE_ENTRY } }

#define SYSTEM_TASK_SHELF_ENTRY_SENSOR_BATTERY_MONITOR_TASKS { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_SENSOR_BATTERY_MONITOR_TASKS, \
.num_interrupts = 0, \
.interrupts = { SYSTEM_NO_TASK }, \
.num_scheduled = 1, \
.scheduled = { SYSTEM_SENSOR_BATTERY_MONITOR_SCHEDULED_PROBE_ENTRY } }

#define SYSTEM_TASK_SHELF_ENTRY_SENSOR_RHO_TASKS { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_SENSOR_RHO_TASKS, \
.num_interrupts = 0, \
.interrupts = { SYSTEM_NO_TASK }, \
.num_scheduled = 1, \
.scheduled = { SYSTEM_SENSOR_RHO_RECEIVE_INTERRUPT_ENTRY } }

#define SYSTEM_TASK_SHELF_ENTRY_DRIVER_HAPTIC_PRIMARY_TASKS { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_DRIVER_HAPTIC_PRIMARY_TASKS, \
.num_interrupts = 1, \
.interrupts = { SYSTEM_DRIVER_HAPTIC_PRIMARY_TRIGGER_ENTRY }, \
.num_scheduled = 0, \
.scheduled = { SYSTEM_NO_TASK } }

#define SYSTEM_TASK_SHELF_ENTRY_COMMUNICATION_HOST_RADIO_TASKS { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_COMMUNICATION_HOST_RADIO_TASKS, \
.num_interrupts = 1, \
.interrupts = { COMMUNICATION_HOST_RECEIVE_PACKET_INTERRUPT_ENTRY }, \
.num_scheduled = 1, \
.scheduled = { COMMUNICATION_HOST_SCHEDULED_TRANSMIT_PACKET_ENTRY } }

#define SYSTEM_TASK_SHELF_ENTRY_COMMUNICATION_SUB_RADIO_TASKS { \
.task_id = SYSTEM_TASK_SHELF_ENTRY_ID_COMMUNICATION_SUB_RADIO_TASKS, \
.num_interrupts = 1, \
.interrupts = { COMMUNICATION_SUB_TRANSMIT_PACKET_INTERRUPT_ENTRY }, \
.num_scheduled = 0, \
.scheduled = { SYSTEM_NO_TASK } }

static system_profile_t Profile =
{
    { /* Task Shelf */
        SYSTEM_TASK_SHELF_ENTRY_NULL,
        SYSTEM_TASK_SHELF_ENTRY_SENSOR_MOTION_TASKS,
        SYSTEM_TASK_SHELF_ENTRY_SENSOR_TOUCH_TASKS,
        SYSTEM_TASK_SHELF_ENTRY_SENSOR_TIP_TASKS,
        SYSTEM_TASK_SHELF_ENTRY_SENSOR_BATTERY_MONITOR_TASKS,
        SYSTEM_TASK_SHELF_ENTRY_SENSOR_RHO_TASKS,
        SYSTEM_TASK_SHELF_ENTRY_DRIVER_HAPTIC_PRIMARY_TASKS,
        SYSTEM_TASK_SHELF_ENTRY_COMMUNICATION_HOST_RADIO_TASKS,
        SYSTEM_TASK_SHELF_ENTRY_COMMUNICATION_SUB_RADIO_TASKS
    },
    
    { /* State Profiles */
        { /* SYSTEM_STATE_STARTUP */
            {
                SYSTEM_ACTIVITY_STARTUP,
                5, {
                    SYSTEM_SUBACTIVITY_SELF_CHECK,
                    SYSTEM_SUBACTIVITY_INIT_COMMUNICATION,
                    SYSTEM_SUBACTIVITY_INIT_COMPONENTS,
                    SYSTEM_SUBACTIVITY_INIT_TAU_CLIENT,
                    SYSTEM_SUBACTIVITY_INIT_CONFIRM
                },
                SYSTEM_STATE_ACTIVE
            },
            { SYSTEM_FAMILY_A }, /* Families */
            { /* Tasks */
                SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS,
            }
        },
        { /* SYSTEM_STATE_IDLE */
            {
                SYSTEM_ACTIVITY_NONE,
                0, {}, SYSTEM_STATE_IDLE
            },
            { SYSTEM_FAMILY_A }, /* Families */
            { /* Tasks */
                SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS
            }
        },
        { /* SYSTEM_STATE_WAITING */
            {
                SYSTEM_ACTIVITY_NONE,
                0, {}, SYSTEM_STATE_WAITING
            },
            { SYSTEM_FAMILY_A }, /* Families */
            { /* Tasks */
                SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS
            }
        },
        { /* SYSTEM_STATE_ACTIVE */
            {
                SYSTEM_ACTIVITY_NONE,
                0, {}, SYSTEM_STATE_ACTIVE
            },
            { SYSTEM_FAMILY_A }, /* Families */
            { /* Tasks */
                SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS
            }
        },
        { /* SYSTEM_STATE_ASLEEP */
            {
                SYSTEM_ACTIVITY_NONE,
                0, {}, SYSTEM_STATE_ASLEEP
            },
            { SYSTEM_FAMILY_A }, /* Families */
            { /* Tasks */
                SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS
            }
        },
        { /* SYSTEM_STATE_ERROR */
            {
                SYSTEM_ACTIVITY_NONE,
                0, {}, SYSTEM_STATE_ERROR
            },
            { SYSTEM_FAMILY_A }, /* Families */
            { /* Tasks */
                SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS
            }
        },
        { /* SYSTEM_STATE_RECOVERY */
            {
                SYSTEM_ACTIVITY_NONE,
                0, {}, SYSTEM_STATE_RECOVERY
            },
            { SYSTEM_FAMILY_A }, /* Families */
            { /* Tasks */
                SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS
            }
        },
        { /* SYSTEM_STATE_UNKNOWN */
            {
                SYSTEM_ACTIVITY_NONE,
                0, {}, SYSTEM_STATE_UNKNOWN
            },
            { SYSTEM_FAMILY_A }, /* Families */
            { /* Tasks */
                SYSTEM_TASK_SHELF_ENTRY_ID_NULL_TASKS
            }
        }
    },
    { /* Components */
        BNO080_COMPONENT,
        RHOMOD_COMPONENT,
        CPT112_COMPONENT,
        STC310_COMPONENT,
        TIPMOD_COMPONENT,
        XC9265_COMPONENT
    }
};

#endif /* C11_profile_h */

