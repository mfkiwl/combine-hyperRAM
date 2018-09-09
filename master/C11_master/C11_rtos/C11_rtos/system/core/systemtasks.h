//
//  systemtasks.h
//  C11_rtos
//
//  Created by Matthew Fonken on 9/1/18.
//  Copyright © 2018 Marbl. All rights reserved.
//
#include "systemtypes.h"

#ifndef systemtasks_h
#define systemtasks_h

#define DEFAULT_TASK_STACK_LIMIT_FACTOR 10u

typedef enum
{
    TASK_PRIORITY_CLASS_EXECUTIVE = 2,
    TASK_PRIORITY_CLASS_HIGH,
    TASK_PRIORITY_CLASS_MEDIUM,
    TASK_PRIORITY_CLASS_LOW,
    TASK_PRIORITY_CLASS_PASSIVE
} TASK_PRIORITY_CLASS;

typedef unsigned int CPU_STK;

#define OS_TCB void *
#define DEFAULT_TASK_OS_OPTIONS             0 //OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR

#define COMBINE_API_STACK_SIZE    (100 / sizeof(CPU_STK))
static  OS_TCB                    CombineAPITaskTCB;
static  CPU_STK                   CombineAPITaskStack[COMBINE_API_STACK_SIZE];
#define COMBINE_API_ID            SYSTEM_SCHEDULER_ID_TIP_POLL
#define COMBINE_API_TCB           CombineAPITaskTCB
#define COMBINE_API_NAME          task_id_strings[SYSTEM_INTERRUPTER_ID_SUB_RADIO_PACKET_TRANSMIT]
#define COMBINE_API_TASK_PTR(X)   X
#define COMBINE_API_ARGS          0 //&System.buffers.
#define COMBINE_API_PRIORITY      TASK_PRIORITY_CLASS_HIGH
#define COMBINE_API_STACK         CombineAPITaskStack
#define COMBINE_API_STACK_LIMIT   COMBINE_API_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
//#define COMBINE_API_STACK_SIZE    COMBINE_API_STACK_SIZE
#define COMBINE_API_Q_SIZE        0u
#define COMBINE_API_OS_TICK       0u
#define COMBINE_API_OS_OPTIONS    DEFAULT_TASK_OS_OPTIONS
#define COMBINE_API_ERROR         0 //&System.errors.comm
#define COMBINE_API_OS_TASK(X) { \
    COMBINE_API_ID, \
    COMBINE_API_NAME, \
    COMBINE_API_TASK_PTR(X), \
    COMBINE_API_ARGS, \
    COMBINE_API_PRIORITY, \
    COMBINE_API_STACK, \
    COMBINE_API_STACK_LIMIT, \
    COMBINE_API_STACK_SIZE, \
    COMBINE_API_Q_SIZE, \
    COMBINE_API_OS_TICK, \
    COMBINE_API_OS_OPTIONS, \
    COMBINE_API_ERROR }


#define TAU_PERFORM_STACK_SIZE              (1500 / sizeof(CPU_STK))
static  OS_TCB                              TauPerformTaskTCB;
static  CPU_STK                             TauPerformTaskStack[TAU_PERFORM_STACK_SIZE];
#define SCHEDULER_TAU_PERFORM_ID            SYSTEM_SCHEDULER_ID_TAU_PERFORM
#define SCHEDULER_TAU_PERFORM_TCB           TauPerformTaskTCB
#define SCHEDULER_TAU_PERFORM_NAME          task_id_strings[SYSTEM_SCHEDULER_ID_TAU_PERFORM]
#define SCHEDULER_TAU_PERFORM_TASK_PTR(X)   X
#define SCHEDULER_TAU_PERFORM_ARGS          0u
#define SCHEDULER_TAU_PERFORM_PRIORITY      TASK_PRIORITY_CLASS_HIGH
#define SCHEDULER_TAU_PERFORM_STACK         TauPerformTaskStack
#define SCHEDULER_TAU_PERFORM_STACK_LIMIT   TAU_PERFORM_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define SCHEDULER_TAU_PERFORM_STACK_SIZE    TAU_PERFORM_STACK_SIZE
#define SCHEDULER_TAU_PERFORM_Q_SIZE        0u
#define SCHEDULER_TAU_PERFORM_OS_TICK       0u
#define SCHEDULER_TAU_PERFORM_OS_OPTIONS    DEFAULT_TASK_OS_OPTIONS
#define SCHEDULER_TAU_PERFORM_ERROR         0 //&System.errors.tau
#define SCHEDULER_TAU_PERFORM_OS_TASK(X) { \
    SCHEDULER_TAU_PERFORM_ID, \
    SCHEDULER_TAU_PERFORM_NAME, \
    SCHEDULER_TAU_PERFORM_TASK_PTR(X), \
    SCHEDULER_TAU_PERFORM_ARGS, \
    SCHEDULER_TAU_PERFORM_PRIORITY, \
    SCHEDULER_TAU_PERFORM_STACK, \
    SCHEDULER_TAU_PERFORM_STACK_LIMIT, \
    SCHEDULER_TAU_PERFORM_STACK_SIZE, \
    SCHEDULER_TAU_PERFORM_Q_SIZE, \
    SCHEDULER_TAU_PERFORM_OS_TICK, \
    SCHEDULER_TAU_PERFORM_OS_OPTIONS, \
    SCHEDULER_TAU_PERFORM_ERROR }


#define TAU_PACKET_QUEUE_STACK_SIZE             (100 / sizeof(CPU_STK))
static  OS_TCB                                  TauPacketQueueTaskTCB;
static  CPU_STK                                 TauPacketQueueTaskStack[TAU_PACKET_QUEUE_STACK_SIZE];
#define SCHEDULER_TAU_PACKET_QUEUE_ID           SYSTEM_SCHEDULER_ID_TAU_PACKET_QUEUE
#define SCHEDULER_TAU_PACKET_QUEUE_TCB          TauPacketQueueTaskTCB
#define SCHEDULER_TAU_PACKET_QUEUE_NAME         task_id_strings[SYSTEM_SCHEDULER_ID_TAU_PACKET_QUEUE]
#define SCHEDULER_TAU_PACKET_QUEUE_TASK_PTR(X)  X
#define SCHEDULER_TAU_PACKET_QUEUE_ARGS         0 //&System.buffers.packet_out
#define SCHEDULER_TAU_PACKET_QUEUE_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define SCHEDULER_TAU_PACKET_QUEUE_STACK        TauPacketQueueTaskStack
#define SCHEDULER_TAU_PACKET_QUEUE_STACK_LIMIT  TAU_PACKET_QUEUE_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define SCHEDULER_TAU_PACKET_QUEUE_STACK_SIZE   TAU_PACKET_QUEUE_STACK_SIZE
#define SCHEDULER_TAU_PACKET_QUEUE_Q_SIZE       0u
#define SCHEDULER_TAU_PACKET_QUEUE_OS_TICK      0u
#define SCHEDULER_TAU_PACKET_QUEUE_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define SCHEDULER_TAU_PACKET_QUEUE_ERROR        0 //&System.errors.comm
#define SCHEDULER_TAU_PACKET_QUEUE_OS_TASK(X) { \
    SCHEDULER_TAU_PACKET_QUEUE_ID, \
    SCHEDULER_TAU_PACKET_QUEUE_NAME, \
    SCHEDULER_TAU_PACKET_QUEUE_TASK_PTR(X), \
    SCHEDULER_TAU_PACKET_QUEUE_ARGS, \
    SCHEDULER_TAU_PACKET_QUEUE_PRIORITY, \
    SCHEDULER_TAU_PACKET_QUEUE_STACK, \
    SCHEDULER_TAU_PACKET_QUEUE_STACK_LIMIT, \
    SCHEDULER_TAU_PACKET_QUEUE_STACK_SIZE, \
    SCHEDULER_TAU_PACKET_QUEUE_Q_SIZE, \
    SCHEDULER_TAU_PACKET_QUEUE_OS_TICK, \
    SCHEDULER_TAU_PACKET_QUEUE_OS_OPTIONS, \
    SCHEDULER_TAU_PACKET_QUEUE_ERROR }


#define BATTERY_MONITOR_POLL_STACK_SIZE             (100 / sizeof(CPU_STK))
static  OS_TCB                                      BatteryMonitorPollTaskTCB;
static  CPU_STK                                     BatteryMonitorTaskStack[BATTERY_MONITOR_POLL_STACK_SIZE];
#define SCHEDULER_BATTERY_MONITOR_POLL_ID           SYSTEM_SCHEDULER_ID_BATTERY_MONITOR_POLL
#define SCHEDULER_BATTERY_MONITOR_POLL_TCB          BatteryMonitorPollTaskTCB
#define SCHEDULER_BATTERY_MONITOR_POLL_NAME         task_id_strings[SYSTEM_SCHEDULER_ID_BATTERY_MONITOR_POLL]
#define SCHEDULER_BATTERY_MONITOR_POLL_TASK_PTR(X)  X
#define SCHEDULER_BATTERY_MONITOR_POLL_ARGS         0 //&System.buffers.
#define SCHEDULER_BATTERY_MONITOR_POLL_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define SCHEDULER_BATTERY_MONITOR_POLL_STACK        BatteryMonitorTaskStack
#define SCHEDULER_BATTERY_MONITOR_POLL_STACK_LIMIT  BATTERY_MONITOR_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define SCHEDULER_BATTERY_MONITOR_POLL_STACK_SIZE   BATTERY_MONITOR_POLL_STACK_SIZE
#define SCHEDULER_BATTERY_MONITOR_POLL_Q_SIZE       0u
#define SCHEDULER_BATTERY_MONITOR_POLL_OS_TICK      0u
#define SCHEDULER_BATTERY_MONITOR_POLL_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define SCHEDULER_BATTERY_MONITOR_POLL_ERROR        0 //&System.errors.comm
#define SCHEDULER_BATTERY_MONITOR_POLL_OS_TASK(X) { \
    SCHEDULER_BATTERY_MONITOR_POLL_ID, \
    SCHEDULER_BATTERY_MONITOR_POLL_NAME, \
    SCHEDULER_BATTERY_MONITOR_POLL_TASK_PTR(X), \
    SCHEDULER_BATTERY_MONITOR_POLL_ARGS, \
    SCHEDULER_BATTERY_MONITOR_POLL_PRIORITY, \
    SCHEDULER_BATTERY_MONITOR_POLL_STACK, \
    SCHEDULER_BATTERY_MONITOR_POLL_STACK_LIMIT, \
    SCHEDULER_BATTERY_MONITOR_POLL_STACK_SIZE, \
    SCHEDULER_BATTERY_MONITOR_POLL_Q_SIZE, \
    SCHEDULER_BATTERY_MONITOR_POLL_OS_TICK, \
    SCHEDULER_BATTERY_MONITOR_POLL_OS_OPTIONS, \
    SCHEDULER_BATTERY_MONITOR_POLL_ERROR }


#define TIP_POLL_STACK_SIZE             (100 / sizeof(CPU_STK))
static  OS_TCB                          TipPollTaskTCB;
static  CPU_STK                         TipPollTaskStack[TIP_POLL_STACK_SIZE];
#define SCHEDULER_TIP_POLL_ID           SYSTEM_SCHEDULER_ID_TIP_POLL
#define SCHEDULER_TIP_POLL_TCB          TipPollTaskTCB
#define SCHEDULER_TIP_POLL_NAME         task_id_strings[SYSTEM_SCHEDULER_ID_TIP_POLL]
#define SCHEDULER_TIP_POLL_TASK_PTR(X)  X
#define SCHEDULER_TIP_POLL_ARGS         0 //&System.buffers.
#define SCHEDULER_TIP_POLL_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define SCHEDULER_TIP_POLL_STACK        TipPollTaskStack
#define SCHEDULER_TIP_POLL_STACK_LIMIT  TIP_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define SCHEDULER_TIP_POLL_STACK_SIZE   TIP_POLL_STACK_SIZE
#define SCHEDULER_TIP_POLL_Q_SIZE       0u
#define SCHEDULER_TIP_POLL_OS_TICK      0u
#define SCHEDULER_TIP_POLL_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define SCHEDULER_TIP_POLL_ERROR        0 //&System.errors.comm
#define SCHEDULER_TIP_POLL_OS_TASK(X) { \
    SCHEDULER_TIP_POLL_ID, \
    SCHEDULER_TIP_POLL_NAME, \
    SCHEDULER_TIP_POLL_TASK_PTR(X), \
    SCHEDULER_TIP_POLL_ARGS, \
    SCHEDULER_TIP_POLL_PRIORITY, \
    SCHEDULER_TIP_POLL_STACK, \
    SCHEDULER_TIP_POLL_STACK_LIMIT, \
    SCHEDULER_TIP_POLL_STACK_SIZE, \
    SCHEDULER_TIP_POLL_Q_SIZE, \
    SCHEDULER_TIP_POLL_OS_TICK, \
    SCHEDULER_TIP_POLL_OS_OPTIONS, \
    SCHEDULER_TIP_POLL_ERROR }


#define TAU_PACKET_TRANSMIT_STACK_SIZE             (100 / sizeof(CPU_STK))
static  OS_TCB                                      TauPackTransmitTaskTCB;
static  CPU_STK                                     TauPackTransmitTaskStack[TAU_PACKET_TRANSMIT_STACK_SIZE];
#define INTERRUPTER_TAU_PACKET_TRANSMIT_ID           SYSTEM_INTERRUPTER_ID_TAU_PACKET_TRANSMIT
#define INTERRUPTER_TAU_PACKET_TRANSMIT_TCB          TauPackTransmitTaskTCB
#define INTERRUPTER_TAU_PACKET_TRANSMIT_NAME         task_id_strings[SYSTEM_INTERRUPTER_ID_TAU_PACKET_TRANSMIT]
#define INTERRUPTER_TAU_PACKET_TRANSMIT_TASK_PTR(X)  X
#define INTERRUPTER_TAU_PACKET_TRANSMIT_ARGS         0 //&System.buffers.
#define INTERRUPTER_TAU_PACKET_TRANSMIT_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define INTERRUPTER_TAU_PACKET_TRANSMIT_STACK        TauPackTransmitTaskStack
#define INTERRUPTER_TAU_PACKET_TRANSMIT_STACK_LIMIT  TIP_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define INTERRUPTER_TAU_PACKET_TRANSMIT_STACK_SIZE   TIP_POLL_STACK_SIZE
#define INTERRUPTER_TAU_PACKET_TRANSMIT_Q_SIZE       0u
#define INTERRUPTER_TAU_PACKET_TRANSMIT_OS_TICK      0u
#define INTERRUPTER_TAU_PACKET_TRANSMIT_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define INTERRUPTER_TAU_PACKET_TRANSMIT_ERROR        0 //&System.errors.comm
#define INTERRUPTER_TAU_PACKET_TRANSMIT_OS_TASK(X) { \
    INTERRUPTER_TAU_PACKET_TRANSMIT_ID, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_NAME, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_TASK_PTR(X), \
    INTERRUPTER_TAU_PACKET_TRANSMIT_ARGS, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_PRIORITY, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_STACK, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_STACK_LIMIT, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_STACK_SIZE, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_Q_SIZE, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_OS_TICK, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_OS_OPTIONS, \
    INTERRUPTER_TAU_PACKET_TRANSMIT_ERROR }


#define TAU_PACKET_RECEIVE_STACK_SIZE               (100 / sizeof(CPU_STK))
static  OS_TCB                                      TauPackReceiveTaskTCB;
static  CPU_STK                                     TauPackReceiveTaskStack[TAU_PACKET_RECEIVE_STACK_SIZE];
#define INTERRUPTER_TAU_PACKET_RECEIVE_ID           SYSTEM_INTERRUPTER_ID_TAU_PACKET_RECEIVE
#define INTERRUPTER_TAU_PACKET_RECEIVE_TCB          TauPackReceiveTaskTCB
#define INTERRUPTER_TAU_PACKET_RECEIVE_NAME         task_id_strings[SYSTEM_INTERRUPTER_ID_TAU_PACKET_RECEIVE]
#define INTERRUPTER_TAU_PACKET_RECEIVE_TASK_PTR(X)  X
#define INTERRUPTER_TAU_PACKET_RECEIVE_ARGS         0 //&System.buffers.
#define INTERRUPTER_TAU_PACKET_RECEIVE_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define INTERRUPTER_TAU_PACKET_RECEIVE_STACK        TauPackReceiveTaskStack
#define INTERRUPTER_TAU_PACKET_RECEIVE_STACK_LIMIT  TIP_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define INTERRUPTER_TAU_PACKET_RECEIVE_STACK_SIZE   TIP_POLL_STACK_SIZE
#define INTERRUPTER_TAU_PACKET_RECEIVE_Q_SIZE       0u
#define INTERRUPTER_TAU_PACKET_RECEIVE_OS_TICK      0u
#define INTERRUPTER_TAU_PACKET_RECEIVE_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define INTERRUPTER_TAU_PACKET_RECEIVE_ERROR        0 //&System.errors.comm
#define INTERRUPTER_TAU_PACKET_RECEIVE_OS_TASK(X) { \
    INTERRUPTER_TAU_PACKET_RECEIVE_ID, \
    INTERRUPTER_TAU_PACKET_RECEIVE_NAME, \
    INTERRUPTER_TAU_PACKET_RECEIVE_TASK_PTR(X), \
    INTERRUPTER_TAU_PACKET_RECEIVE_ARGS, \
    INTERRUPTER_TAU_PACKET_RECEIVE_PRIORITY, \
    INTERRUPTER_TAU_PACKET_RECEIVE_STACK, \
    INTERRUPTER_TAU_PACKET_RECEIVE_STACK_LIMIT, \
    INTERRUPTER_TAU_PACKET_RECEIVE_STACK_SIZE, \
    INTERRUPTER_TAU_PACKET_RECEIVE_Q_SIZE, \
    INTERRUPTER_TAU_PACKET_RECEIVE_OS_TICK, \
    INTERRUPTER_TAU_PACKET_RECEIVE_OS_OPTIONS, \
    INTERRUPTER_TAU_PACKET_RECEIVE_ERROR }

#define SUB_RADIO_PACKET_TRANSMIT_STACK_SIZE               (100 / sizeof(CPU_STK))
static  OS_TCB                                          SubRadioPacketTransmitTaskTCB;
static  CPU_STK                                         SubRadioPacketTransmitTaskStack[SUB_RADIO_PACKET_TRANSMIT_STACK_SIZE];
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_ID           SYSTEM_INTERRUPTER_ID_SUB_RADIO_PACKET_TRANSMIT
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_TCB          SubRadioPacketTransmitTaskTCB
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_NAME         task_id_strings[SYSTEM_INTERRUPTER_ID_SUB_RADIO_PACKET_TRANSMIT]
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_TASK_PTR(X)  X
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_ARGS         0 //&System.buffers.
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_STACK        SubRadioPacketTransmitTaskStack
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_STACK_LIMIT  TIP_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_STACK_SIZE   TIP_POLL_STACK_SIZE
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_Q_SIZE       0u
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_OS_TICK      0u
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_ERROR        0 //&System.errors.comm
#define INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_OS_TASK(X) { \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_ID, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_NAME, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_TASK_PTR(X), \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_ARGS, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_PRIORITY, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_STACK, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_STACK_LIMIT, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_STACK_SIZE, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_Q_SIZE, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_OS_TICK, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_OS_OPTIONS, \
    INTERRUPTER_SUB_RADIO_PACKET_TRANSMIT_ERROR }


#define HAPTIC_TRIGGER_STACK_SIZE               (100 / sizeof(CPU_STK))
static  OS_TCB                                  HapticTriggerTaskTCB;
static  CPU_STK                                 HapticTriggerTaskStack[HAPTIC_TRIGGER_STACK_SIZE];
#define INTERRUPTER_HAPTIC_TRIGGER_ID           SYSTEM_INTERRUPTER_ID_HAPTIC_TRIGGER
#define INTERRUPTER_HAPTIC_TRIGGER_TCB          HapticTriggerTaskTCB
#define INTERRUPTER_HAPTIC_TRIGGER_NAME         task_id_strings[SYSTEM_INTERRUPTER_ID_HAPTIC_TRIGGER]
#define INTERRUPTER_HAPTIC_TRIGGER_TASK_PTR(X)  X
#define INTERRUPTER_HAPTIC_TRIGGER_ARGS         0 //&System.buffers.
#define INTERRUPTER_HAPTIC_TRIGGER_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define INTERRUPTER_HAPTIC_TRIGGER_STACK        HapticTriggerTaskStack
#define INTERRUPTER_HAPTIC_TRIGGER_STACK_LIMIT  TIP_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define INTERRUPTER_HAPTIC_TRIGGER_STACK_SIZE   TIP_POLL_STACK_SIZE
#define INTERRUPTER_HAPTIC_TRIGGER_Q_SIZE       0u
#define INTERRUPTER_HAPTIC_TRIGGER_OS_TICK      0u
#define INTERRUPTER_HAPTIC_TRIGGER_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define INTERRUPTER_HAPTIC_TRIGGER_ERROR        0 //&System.errors.comm
#define INTERRUPTER_HAPTIC_TRIGGER_OS_TASK(X) { \
    INTERRUPTER_HAPTIC_TRIGGER_ID, \
    INTERRUPTER_HAPTIC_TRIGGER_NAME, \
    INTERRUPTER_HAPTIC_TRIGGER_TASK_PTR(X), \
    INTERRUPTER_HAPTIC_TRIGGER_ARGS, \
    INTERRUPTER_HAPTIC_TRIGGER_PRIORITY, \
    INTERRUPTER_HAPTIC_TRIGGER_STACK, \
    INTERRUPTER_HAPTIC_TRIGGER_STACK_LIMIT, \
    INTERRUPTER_HAPTIC_TRIGGER_STACK_SIZE, \
    INTERRUPTER_HAPTIC_TRIGGER_Q_SIZE, \
    INTERRUPTER_HAPTIC_TRIGGER_OS_TICK, \
    INTERRUPTER_HAPTIC_TRIGGER_OS_OPTIONS, \
    INTERRUPTER_HAPTIC_TRIGGER_ERROR }


#define MOTION_INTERRUPT_STACK_SIZE             (100 / sizeof(CPU_STK))
static  OS_TCB                                  MotionTriggerTaskTCB;
static  CPU_STK                                 MotionTriggerTaskStack[MOTION_INTERRUPT_STACK_SIZE];
#define SCHEDULER_MOTION_INTERRUPT_ID           SYSTEM_SCHEDULER_ID_MOTION_INTERRUPT
#define SCHEDULER_MOTION_INTERRUPT_TCB          MotionTriggerTaskTCB
#define SCHEDULER_MOTION_INTERRUPT_NAME         task_id_strings[SYSTEM_SCHEDULER_ID_MOTION_INTERRUPT]
#define SCHEDULER_MOTION_INTERRUPT_TASK_PTR(X)  X
#define SCHEDULER_MOTION_INTERRUPT_ARGS         0 //&System.buffers.
#define SCHEDULER_MOTION_INTERRUPT_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define SCHEDULER_MOTION_INTERRUPT_STACK        MotionTriggerTaskStack
#define SCHEDULER_MOTION_INTERRUPT_STACK_LIMIT  TIP_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define SCHEDULER_MOTION_INTERRUPT_STACK_SIZE   TIP_POLL_STACK_SIZE
#define SCHEDULER_MOTION_INTERRUPT_Q_SIZE       0u
#define SCHEDULER_MOTION_INTERRUPT_OS_TICK      0u
#define SCHEDULER_MOTION_INTERRUPT_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define SCHEDULER_MOTION_INTERRUPT_ERROR        0 //&System.errors.comm
#define SCHEDULER_MOTION_INTERRUPT_OS_TASK(X) { \
    SCHEDULER_MOTION_INTERRUPT_ID, \
    SCHEDULER_MOTION_INTERRUPT_NAME, \
    SCHEDULER_MOTION_INTERRUPT_TASK_PTR(X), \
    SCHEDULER_MOTION_INTERRUPT_ARGS, \
    SCHEDULER_MOTION_INTERRUPT_PRIORITY, \
    SCHEDULER_MOTION_INTERRUPT_STACK, \
    SCHEDULER_MOTION_INTERRUPT_STACK_LIMIT, \
    SCHEDULER_MOTION_INTERRUPT_STACK_SIZE, \
    SCHEDULER_MOTION_INTERRUPT_Q_SIZE, \
    SCHEDULER_MOTION_INTERRUPT_OS_TICK, \
    SCHEDULER_MOTION_INTERRUPT_OS_OPTIONS, \
    SCHEDULER_MOTION_INTERRUPT_ERROR }


#define RHO_INTERRUPT_STACK_SIZE               (100 / sizeof(CPU_STK))
static  OS_TCB                                  RhoTriggerTaskTCB;
static  CPU_STK                                 RhoTriggerTaskStack[RHO_INTERRUPT_STACK_SIZE];
#define SCHEDULER_RHO_INTERRUPT_ID           SYSTEM_SCHEDULER_ID_RHO_INTERRUPT
#define SCHEDULER_RHO_INTERRUPT_TCB          RhoTriggerTaskTCB
#define SCHEDULER_RHO_INTERRUPT_NAME         task_id_strings[SYSTEM_SCHEDULER_ID_RHO_INTERRUPT]
#define SCHEDULER_RHO_INTERRUPT_TASK_PTR(X)  X
#define SCHEDULER_RHO_INTERRUPT_ARGS         0 //&System.buffers.
#define SCHEDULER_RHO_INTERRUPT_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define SCHEDULER_RHO_INTERRUPT_STACK        RhoTriggerTaskStack
#define SCHEDULER_RHO_INTERRUPT_STACK_LIMIT  TIP_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define SCHEDULER_RHO_INTERRUPT_STACK_SIZE   TIP_POLL_STACK_SIZE
#define SCHEDULER_RHO_INTERRUPT_Q_SIZE       0u
#define SCHEDULER_RHO_INTERRUPT_OS_TICK      0u
#define SCHEDULER_RHO_INTERRUPT_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define SCHEDULER_RHO_INTERRUPT_ERROR        0 //&System.errors.comm
#define SCHEDULER_RHO_INTERRUPT_OS_TASK(X) { \
    SCHEDULER_RHO_INTERRUPT_ID, \
    SCHEDULER_RHO_INTERRUPT_NAME, \
    SCHEDULER_RHO_INTERRUPT_TASK_PTR(X), \
    SCHEDULER_RHO_INTERRUPT_ARGS, \
    SCHEDULER_RHO_INTERRUPT_PRIORITY, \
    SCHEDULER_RHO_INTERRUPT_STACK, \
    SCHEDULER_RHO_INTERRUPT_STACK_LIMIT, \
    SCHEDULER_RHO_INTERRUPT_STACK_SIZE, \
    SCHEDULER_RHO_INTERRUPT_Q_SIZE, \
    SCHEDULER_RHO_INTERRUPT_OS_TICK, \
    SCHEDULER_RHO_INTERRUPT_OS_OPTIONS, \
    SCHEDULER_RHO_INTERRUPT_ERROR }


#define TOUCH_INTERRUPT_STACK_SIZE             (100 / sizeof(CPU_STK))
static  OS_TCB                                 TouchTriggerTaskTCB;
static  CPU_STK                                TouchTriggerTaskStack[TOUCH_INTERRUPT_STACK_SIZE];
#define SCHEDULER_TOUCH_INTERRUPT_ID           SYSTEM_SCHEDULER_ID_TOUCH_INTERRUPT
#define SCHEDULER_TOUCH_INTERRUPT_TCB          TouchTriggerTaskTCB
#define SCHEDULER_TOUCH_INTERRUPT_NAME         task_id_strings[SYSTEM_SCHEDULER_ID_TOUCH_INTERRUPT]
#define SCHEDULER_TOUCH_INTERRUPT_TASK_PTR(X)  X
#define SCHEDULER_TOUCH_INTERRUPT_ARGS         0 //&System.buffers.
#define SCHEDULER_TOUCH_INTERRUPT_PRIORITY     TASK_PRIORITY_CLASS_HIGH
#define SCHEDULER_TOUCH_INTERRUPT_STACK        TouchTriggerTaskStack
#define SCHEDULER_TOUCH_INTERRUPT_STACK_LIMIT  TIP_POLL_STACK_SIZE / DEFAULT_TASK_STACK_LIMIT_FACTOR
#define SCHEDULER_TOUCH_INTERRUPT_STACK_SIZE   TIP_POLL_STACK_SIZE
#define SCHEDULER_TOUCH_INTERRUPT_Q_SIZE       0u
#define SCHEDULER_TOUCH_INTERRUPT_OS_TICK      0u
#define SCHEDULER_TOUCH_INTERRUPT_OS_OPTIONS   DEFAULT_TASK_OS_OPTIONS
#define SCHEDULER_TOUCH_INTERRUPT_ERROR        0 //&System.errors.comm
#define SCHEDULER_TOUCH_INTERRUPT_OS_TASK(X) { \
    SCHEDULER_TOUCH_INTERRUPT_ID, \
    SCHEDULER_TOUCH_INTERRUPT_NAME, \
    SCHEDULER_TOUCH_INTERRUPT_TASK_PTR(X), \
    SCHEDULER_TOUCH_INTERRUPT_ARGS, \
    SCHEDULER_TOUCH_INTERRUPT_PRIORITY, \
    SCHEDULER_TOUCH_INTERRUPT_STACK, \
    SCHEDULER_TOUCH_INTERRUPT_STACK_LIMIT, \
    SCHEDULER_TOUCH_INTERRUPT_STACK_SIZE, \
    SCHEDULER_TOUCH_INTERRUPT_Q_SIZE, \
    SCHEDULER_TOUCH_INTERRUPT_OS_TICK, \
    SCHEDULER_TOUCH_INTERRUPT_OS_OPTIONS, \
    SCHEDULER_TOUCH_INTERRUPT_ERROR }

#endif /* systemtasks_h */
