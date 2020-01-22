//
//  application_debug.h
//  C12_rtos
//
//  Created by Matthew Fonken on 8/28/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#ifndef application_debug_h
#define application_debug_h

#define _DEBUG_

#ifdef _DEBUG_
#define printd printf
#else
#define printd void
#endif

static const char * state_strings[] =
{
    "STATE_STARTUP",
    "STATE_IDLE",
    "STATE_WAITING",
    "STATE_ACTIVE",
    "STATE_ASLEEP",
    "STATE_ERROR",
    "STATE_RECOVERY",
    "STATE_UNKNOWN"
};
static const char * activity_strings[] =
{
    "ACTIVITY_NONE",
    "ACTIVITY_STARTUP",
    "ACTIVITY_TAU_STANDARD_START",
    
    "ACTIVITY_IDLE",
    "ACTIVITY_SLEEP"
};
static const char * subactivity_strings[] =
{
    /* General */
    "SUBACTIVITY_NONE",
    "SUBACTIVITY_SELF_CHECK",
    "SUBACTIVITY_WAIT_FOR_WAKE",

    /* Initialization */
    "SUBACTIVITY_INIT_COMMUNICATION",
    "SUBACTIVITY_INIT_COMPONENTS",
    "SUBACTIVITY_INIT_TAU_CLIENT",
    "SUBACTIVITY_INIT_RHO_CLIENT",
    "SUBACTIVITY_INIT_CONFIRM",
    "SUBACTIVITY_BATTERY_MONITOR_ACTIVE",

    /* Profile */
    //    "SUBACTIVITY_PROFILE_FETCH",
    //    "SUBACTIVITY_PROFILE_PERFORM",
    //    "SUBACTIVITY_PROFILE_UPDATE",
    //    "SUBACTIVITY_PROFILE_STORE",

    /* Probes */
    "SUBACTIVITY_SEND_HOST_PROBE",
    "SUBACTIVITY_RECEIVE_HOST_PROBE",

    /* Handles */
    "SUBACTIVITY_HANDLE_MOTION_EVENT",
    "SUBACTIVITY_HANDLE_RHO_EVENT",
    "SUBACTIVITY_HANDLE_TOUCH_EVENT",

    "SUBACTIVITY_POLL_BATTERY_MONITOR",
    "SUBACTIVITY_POLL_TIP",

    "SUBACTIVITY_TRIGGER_HAPTIC",

    "SUBACTIVITY_TRANSMIT_HOST_PACKET",
    "SUBACTIVITY_RECEIVE_HOST_PACKET",
    "SUBACTIVITY_TRANSMIT_SUB_RADIO_PACKET",
    "SUBACTIVITY_RECEIVE_SUB_RADIO_PACKET",

    /* Tau */
    "SUBACTIVITY_TAU_STANDARD_RHO_START",
    "SUBACTIVITY_TAU_STANDARD_MOTION_START",
    "SUBACTIVITY_TAU_STANDARD_START",

    /* Sleep/Idle */
    "SUBACTIVITY_TAU_STANDARD_RHO_STOP",
    "SUBACTIVITY_TAU_STANDARD_MOTION_STOP",
    "SUBACTIVITY_TAU_STOP",
    "SUBACTIVITY_BATTERY_MONITOR_SLEEP",
};
static const char * error_strings[] =
{
    "ERROR_NONE",
    "ERROR_STARTUP",
    "ERROR_HARDWARE_NOT_FOUND",
    "ERROR_HOST_NOT_FOUND"
};
static const char * consumption_strings[] =
{
    "CONSUMPTION_NONE",
    "CONSUMPTION_MICRO",
    "CONSUMPTION_LOW",
    "CONSUMPTION_NORMAL",
    "CONSUMPTION_HIGH",
    "CONSUMPTION_SURGE"
};
static const char * family_strings[] =
{
    "FAMILY_NONE",
    "FAMILY_0",
    "FAMILY_A",
    "FAMILY_B",
    "FAMILY_C",
    "FAMILY_D"
};
static const char * sensors_strings[] =
{
    "SENSOR_MOTION_PRIMARY",
    "SENSOR_MOTION_SECONDARY",
    "SENSOR_RHO_MODULE_PRIMARY",
    "SENSOR_RHO_MODULE_SECONDARY",
    "SENSOR_TOUCH_PRIMARY",
    "SENSOR_TOUCH_SECONDARY",
    "SENSOR_TIP_PRIMARY",
    "SENSOR_TIP_SECONDARY",
    "SENSOR_TIP_ALTERNATE",
    "SENSOR_BATTERY_MONITOR_PRIMARY"
};
static const char * drivers_strings[] =
{
    "DRIVER_BLE_RADIO",
    "DRIVER_SUB_RADIO",
    "DRIVER_HAPTIC_PRIMARY",
    "DRIVER_HAPTIC_SECONDARY",
    "DRIVER_REGULATOR_1V5"
};
static const char * component_type_strings[] =
{
    "COMPONENT_TYPE_NONE",
    "COMPONENT_TYPE_SENSOR",
    "COMPONENT_TYPE_DRIVER"
};
static const char * component_strings[] =
{
    "COMPONENT_NONE",
    "COMPONENT_MOTION_PRIMARY",
    "COMPONENT_MOTION_SECONDARY",
    "COMPONENT_RHO_MODULE_PRIMARY",
    "COMPONENT_RHO_MODULE_SECONDARY",
    "COMPONENT_TOUCH_PRIMARY",
    "COMPONENT_TOUCH_SECONDARY",
    "COMPONENT_TIP_PRIMARY",
    "COMPONENT_TIP_SECONDARY",
    "COMPONENT_TIP_ALTERNATE",
    "COMPONENT_BATTERY_MONITOR_PRIMARY",

    "COMPONENT_BLE_RADIO",
    "COMPONENT_SUB_RADIO",
    "COMPONENT_HAPTIC_PRIMARY",
    "COMPONENT_HAPTIC_SECONDARY",
    "COMPONENT_REGULATOR_1V5"
};

static const char * component_state_strings[] =
{
    "COMPONENT_STATE_OFFx00",
    "COMPONENT_STATE_ONx01",
    "COMPONENT_STATE_Zx02",
    "COMPONENT_STATE_INTERRUPT"
};
static const char * profile_entry_state_strings[] =
{
    "PROFILE_ENTRY_STATE_NONE",
    "PROFILE_ENTRY_STATE_IDLE", // Uninitialized
    "PROFILE_ENTRY_STATE_DISABLED",
    "PROFILE_ENTRY_STATE_ENABLED",
    "PROFILE_ENTRY_STATE_ACTIVE"
};
static const char * profile_entry_direction_strings[] =
{
    "PROFILE_ENTRY_DIRECTION_NONE",
    "PROFILE_ENTRY_DIRECTION_INPUT",
    "PROFILE_ENTRY_DIRECTION_OUTPUT",
    "PROFILE_ENTRY_DIRECTION_INOUT"
};
static const char * profile_entry_type_strings[] =
{
    "PROFILE_ENTRY_TYPE_NONE",
    "PROFILE_ENTRY_TYPE_INTERRUPT",
    "PROFILE_ENTRY_TYPE_SCHEDULED"
};
static const char * task_shelf_entry_id_strings[] =
{
    "TASK_SHELF_ENTRY_ID_NULL_TASKS",
    "TASK_SHELF_ENTRY_ID_GLOBAL_TASKS",
    "TASK_SHELF_ENTRY_ID_SENSOR_MOTION_TASKS",
    "TASK_SHELF_ENTRY_ID_SENSOR_TOUCH_TASKS",
    "TASK_SHELF_ENTRY_ID_SENSOR_TIP_TASKS",
    "TASK_SHELF_ENTRY_ID_SENSOR_BATTERY_MONITOR_TASKS",
    "TASK_SHELF_ENTRY_ID_SENSOR_RHO_TASKS",
    "TASK_SHELF_ENTRY_ID_DRIVER_HAPTIC_PRIMARY_TASKS",
    "TASK_SHELF_ENTRY_ID_COMMUNICATION_HOST_RADIO_TASKS",
    "TASK_SHELF_ENTRY_ID_COMMUNICATION_SUB_RADIO_TASKS"
};
static const char * task_id_strings[] =
{
    "ACTION_ID_NONE",
    "COMBINE_GLOBAL",
    
    "PROBE_ID_HOST",
    "PROBE_ID_RHO",
    "PROBE_ID_TIP",
    "PROBE_ID_BATTERY_MONITOR",
    
    //    "INTERRUPTER_ID_NONE",
    "INTERRUPTER_ID_TAU_PACKET_TRANSMIT",
    "INTERRUPTER_ID_TAU_PACKET_RECEIVE",
    "INTERRUPTER_ID_SUB_RADIO_PACKET_TRANSMIT",
    "INTERRUPTER_ID_HAPTIC_TRIGGER",

//    "SCHEDULER_ID_NONE",
    "SCHEDULER_ID_TAU_PERFORM",
    "SCHEDULER_ID_TAU_PACKET_QUEUE",
    "SCHEDULER_ID_TIP_POLL",
    "SCHEDULER_ID_BATTERY_MONITOR_POLL",
    
    "SCHEDULER_ID_MOTION_INTERRUPT",
    "SCHEDULER_ID_RHO_INTERRUPT",
    "SCHEDULER_ID_TOUCH_INTERRUPT"
};

static const char * queue_id_strings[] =
{
    "SYSTEM_QUEUE_ID_HW_INTERRUPTS",
    "SYSTEM_QUEUE_ID_COMM_INTERRUPTS",
    "SYSTEM_QUEUE_ID_RUNTIME_MESSAGES",
    "SYSTEM_QUEUE_ID_APPLICATION_MESSAGES"
};

#define timer_id_strings task_id_strings

#endif /* application_debug_h */
