// ********************** DO NOT EDIT - AUTO-GENERATED ********************** //
// C12_profile.h

// Created by Combine Profile Generator v0.1 on 9/8/2020
// Copyright © Marbl. All rights reserved.

#ifndef C12_profile_h
#define C12_profile_h

#define NONE 0

typedef enum
{
	COMPONENT_ID_NONE = 0,
	COMPONENT_ID_COMPONENT_A_GPIO,
	COMPONENT_ID_COMPONENT_B_I2C,
	NUM_COMPONENT_ID
} COMPONENT_ID, APPLICATION_COMPONENT_ID, application_component_id_t;
#define NUM_APPLICATION_COMPONENT_ID NUM_COMPONENT_ID

typedef enum
{
	COMPONENT_FAMILY_NONE = 0,
	COMPONENT_FAMILY_0,
	COMPONENT_FAMILY_A,
	COMPONENT_FAMILY_B,
	NUM_COMPONENT_FAMILY
} COMPONENT_FAMILY, APPLICATION_COMPONENT_FAMILY, application_component_family_t;
#define NUM_APPLICATION_COMPONENT_FAMILY NUM_COMPONENT_FAMILY

typedef enum
{
	COMPONENT_PROTOCOL_NONE = 0,
	COMPONENT_PROTOCOL_I2C,
	COMPONENT_PROTOCOL_GPIO,
	NUM_COMPONENT_PROTOCOL
} COMPONENT_PROTOCOL, APPLICATION_COMM_PROTOCOL, application_comm_protocol_t;
#define NUM_APPLICATION_COMM_PROTOCOL NUM_COMPONENT_PROTOCOL

typedef enum
{
	COMPONENT_ADDR_NONE = 0,
	NUM_COMPONENT_ADDR
} COMPONENT_ADDR;

typedef enum
{
	COMPONENT_PORT_0 = 0,
	COMPONENT_PORT_A,
	COMPONENT_PORT_B,
	COMPONENT_PORT_C,
	COMPONENT_PORT_D,
	COMPONENT_PORT_F,
	COMPONENT_PORT_NONE,
	NUM_COMPONENT_PORT
} COMPONENT_PORT, APPLICATION_PORT, application_port_t;
#define NUM_APPLICATION_PORT NUM_COMPONENT_PORT

typedef enum
{
	COMPONENT_PIN_INTERNAL = 0,
	NUM_COMPONENT_PIN
} COMPONENT_PIN;

typedef enum
{
	COMPONENT_STATE_OFF = 0,
	COMPONENT_STATE_ON,
	COMPONENT_STATE_INTERRUPT,
	COMPONENT_STATE_ENABLING,
	COMPONENT_STATE_DISABLING,
	NUM_COMPONENT_STATE
} COMPONENT_STATE, APPLICATION_COMPONENT_STATE, application_component_state_t;
#define NUM_APPLICATION_COMPONENT_STATE NUM_COMPONENT_STATE

#ifdef DEBUG
static const char * COMPONENT_ID_STRINGS[] =
{
	"COMPONENT_ID_NONE",
	"COMPONENT_ID_COMPONENT_A_GPIO",
	"COMPONENT_ID_COMPONENT_B_I2C"
};
#define APPLICATION_COMPONENT_ID_STRINGS COMPONENT_ID_STRINGS
#endif

#ifdef DEBUG
static const char * COMPONENT_FAMILY_STRINGS[] =
{
	"COMPONENT_FAMILY_NONE",
	"COMPONENT_FAMILY_0",
	"COMPONENT_FAMILY_A",
	"COMPONENT_FAMILY_B"
};
#define APPLICATION_COMPONENT_FAMILY_STRINGS COMPONENT_FAMILY_STRINGS
#endif

#ifdef DEBUG
static const char * COMPONENT_PROTOCOL_STRINGS[] =
{
	"COMPONENT_PROTOCOL_NONE",
	"COMPONENT_PROTOCOL_I2C",
	"COMPONENT_PROTOCOL_GPIO"
};
#define APPLICATION_COMM_PROTOCOL_STRINGS COMPONENT_PROTOCOL_STRINGS
#endif

#ifdef DEBUG
static const char * COMPONENT_ADDR_STRINGS[] =
{
	"COMPONENT_ADDR_NONE"
};
#endif

#ifdef DEBUG
static const char * COMPONENT_PORT_STRINGS[] =
{
	"COMPONENT_PORT_0",
	"COMPONENT_PORT_A",
	"COMPONENT_PORT_B",
	"COMPONENT_PORT_C",
	"COMPONENT_PORT_D",
	"COMPONENT_PORT_F",
	"COMPONENT_PORT_NONE"
};
#define APPLICATION_PORT_STRINGS COMPONENT_PORT_STRINGS
#endif

#ifdef DEBUG
static const char * COMPONENT_PIN_STRINGS[] =
{
	"COMPONENT_PIN_INTERNAL"
};
#endif

#ifdef DEBUG
static const char * COMPONENT_STATE_STRINGS[] =
{
	"COMPONENT_STATE_OFF",
	"COMPONENT_STATE_ON",
	"COMPONENT_STATE_INTERRUPT",
	"COMPONENT_STATE_ENABLING",
	"COMPONENT_STATE_DISABLING"
};
#define APPLICATION_COMPONENT_STATE_STRINGS COMPONENT_STATE_STRINGS
#endif

typedef enum
{
	SUBACTIVITIY_ID_NONE = 0,
	SUBACTIVITIY_ID_INIT,
	SUBACTIVITIY_ID_SET_GPIO_COMPONENT_A,
	SUBACTIVITIY_ID_CLEAR_GPIO_COMPONENT_A,
	SUBACTIVITIY_ID_POLL_COMPONENT_A_GPIO,
	NUM_SUBACTIVITIY_ID
} SUBACTIVITIY_ID, APPLICATION_SUBACTIVITY_ID, application_subactivity_id_t;
#define NUM_APPLICATION_SUBACTIVITY_ID NUM_SUBACTIVITIY_ID

#ifdef DEBUG
static const char * SUBACTIVITIY_ID_STRINGS[] =
{
	"SUBACTIVITIY_ID_NONE",
	"SUBACTIVITIY_ID_INIT",
	"SUBACTIVITIY_ID_SET_GPIO_COMPONENT_A",
	"SUBACTIVITIY_ID_CLEAR_GPIO_COMPONENT_A",
	"SUBACTIVITIY_ID_POLL_COMPONENT_A_GPIO"
};
#define APPLICATION_SUBACTIVITY_ID_STRINGS SUBACTIVITIY_ID_STRINGS
#endif

typedef enum
{
	QUEUE_ID_HW_INTERRUPTS = 0,
	QUEUE_ID_COMM_MESSAGES,
	QUEUE_ID_RUNTIME_MESSAGES,
	QUEUE_ID_APPLICATION_MESSAGES,
	NUM_QUEUE_ID
} QUEUE_ID, APPLICATION_QUEUE_ID, application_queue_id_t;
#define NUM_APPLICATION_QUEUE_ID NUM_QUEUE_ID

#ifdef DEBUG
static const char * QUEUE_ID_STRINGS[] =
{
	"QUEUE_ID_HW_INTERRUPTS",
	"QUEUE_ID_COMM_MESSAGES",
	"QUEUE_ID_RUNTIME_MESSAGES",
	"QUEUE_ID_APPLICATION_MESSAGES"
};
#define APPLICATION_QUEUE_ID_STRINGS QUEUE_ID_STRINGS
#endif

typedef enum
{
	TASK_ID_NONE = 0,
	TASK_ID_BLINK_GPIO_COMPONENT_A,
	TASK_ID_POLL_COMPONENT_A_GPIO,
	NUM_TASK_ID
} TASK_ID, APPLICATION_TASK_ID, application_task_id_t;
#define NUM_APPLICATION_TASK_ID NUM_TASK_ID

typedef enum
{
	TASK_ACTION_NONE = 0,
	TASK_ACTION_INTERRUPT,
	TASK_ACTION_SCHEDULE,
	TASK_ACTION_QUEUE,
	NUM_TASK_ACTION
} TASK_ACTION, APPLICATION_TASK_ACTION, application_task_action_t;
#define NUM_APPLICATION_TASK_ACTION NUM_TASK_ACTION

typedef enum
{
	TASK_PRIORITY_EXECUTIVE = 0,
	TASK_PRIORITY_HIGH,
	TASK_PRIORITY_MEDIUM,
	TASK_PRIORITY_LOW,
	TASK_PRIORITY_PASSIVE,
	TASK_PRIORITY_QUARANTINE,
	NUM_TASK_PRIORITY
} TASK_PRIORITY, APPLICATION_TASK_PRIORITY, application_task_priority_t;
#define NUM_APPLICATION_TASK_PRIORITY NUM_TASK_PRIORITY

#ifdef DEBUG
static const char * TASK_ID_STRINGS[] =
{
	"TASK_ID_NONE",
	"TASK_ID_BLINK_GPIO_COMPONENT_A",
	"TASK_ID_POLL_COMPONENT_A_GPIO"
};
#define APPLICATION_TASK_ID_STRINGS TASK_ID_STRINGS
#endif

#ifdef DEBUG
static const char * TASK_ACTION_STRINGS[] =
{
	"TASK_ACTION_NONE",
	"TASK_ACTION_INTERRUPT",
	"TASK_ACTION_SCHEDULE",
	"TASK_ACTION_QUEUE"
};
#define APPLICATION_TASK_ACTION_STRINGS TASK_ACTION_STRINGS
#endif

#ifdef DEBUG
static const char * TASK_PRIORITY_STRINGS[] =
{
	"TASK_PRIORITY_EXECUTIVE",
	"TASK_PRIORITY_HIGH",
	"TASK_PRIORITY_MEDIUM",
	"TASK_PRIORITY_LOW",
	"TASK_PRIORITY_PASSIVE",
	"TASK_PRIORITY_QUARANTINE"
};
#define APPLICATION_TASK_PRIORITY_STRINGS TASK_PRIORITY_STRINGS
#endif

typedef enum
{
	TASK_SHELF_ID_NONE = 0,
	TASK_SHELF_ID_GPIO_ONLY,
	TASK_SHELF_ID_ALL,
	NUM_TASK_SHELF_ID
} TASK_SHELF_ID, APPLICATION_TASK_SHELF_ENTRY_ID, application_task_shelf_entry_id_t;
#define NUM_APPLICATION_TASK_SHELF_ENTRY_ID NUM_TASK_SHELF_ID

#ifdef DEBUG
static const char * TASK_SHELF_ID_STRINGS[] =
{
	"TASK_SHELF_ID_NONE",
	"TASK_SHELF_ID_GPIO_ONLY",
	"TASK_SHELF_ID_ALL"
};
#define APPLICATION_TASK_SHELF_ENTRY_ID_STRINGS TASK_SHELF_ID_STRINGS
#endif

typedef enum
{
	STATE_NAME_STARTUP = 0,
	STATE_NAME_IDLE,
	STATE_NAME_ACTIVE,
	STATE_NAME_ASLEEP,
	STATE_NAME_ERROR,
	STATE_NAME_RECOVERY,
	STATE_NAME_UNKNOWN,
	NUM_STATE_NAME
} STATE_NAME, APPLICATION_STATE, application_state_t;
#define NUM_APPLICATION_STATE NUM_STATE_NAME

typedef enum
{
	STATE_ACTIVITY_NONE = 0,
	STATE_ACTIVITY_STARTUP,
	STATE_ACTIVITY_ACTIVATE,
	STATE_ACTIVITY_WAIT,
	STATE_ACTIVITY_SLEEP,
	NUM_STATE_ACTIVITY
} STATE_ACTIVITY, APPLICATION_ACTIVITY, application_activity_t;
#define NUM_APPLICATION_ACTIVITY NUM_STATE_ACTIVITY

#ifdef DEBUG
static const char * STATE_NAME_STRINGS[] =
{
	"STATE_NAME_STARTUP",
	"STATE_NAME_IDLE",
	"STATE_NAME_ACTIVE",
	"STATE_NAME_ASLEEP",
	"STATE_NAME_ERROR",
	"STATE_NAME_RECOVERY",
	"STATE_NAME_UNKNOWN"
};
#define APPLICATION_STATE_STRINGS STATE_NAME_STRINGS
#endif

#ifdef DEBUG
static const char * STATE_ACTIVITY_STRINGS[] =
{
	"STATE_ACTIVITY_NONE",
	"STATE_ACTIVITY_STARTUP",
	"STATE_ACTIVITY_ACTIVATE",
	"STATE_ACTIVITY_WAIT",
	"STATE_ACTIVITY_SLEEP"
};
#define APPLICATION_ACTIVITY_STRINGS STATE_ACTIVITY_STRINGS
#endif


/* Families */
#define FAMILY_IDLE { COMPONENT_FAMILY_NONE }
#define FAMILY_ALL { COMPONENT_FAMILY_A }
#define FAMILY_ERROR { COMPONENT_FAMILY_NONE }

/* Channels */
#define CHANNEL_I2C { I2C1, I2C2 }

/* Components */
#define A_NAME "A"
#define A_ID COMPONENT_ID_COMPONENT_A_GPIO
#define A_FAMILY COMPONENT_FAMILY_A
#define A_PROTOCOL COMPONENT_PROTOCOL_GPIO
#define A_ADDR NONE
#define A_PORT COMPONENT_PORT_D
#define A_PIN 13
#define A_STATE COMPONENT_STATE_OFF
#define A_COMPONENT { A_NAME, A_ID, A_FAMILY, A_PROTOCOL, A_ADDR, A_PORT, A_PIN, A_STATE }

/* Subactivities */
#define SUBACTIVITIY_SET_GPIO_COMPONENT_A { \
	.ID = SUBACTIVITIY_ID_SET_GPIO_COMPONENT_A, \
	.component_id = { COMPONENT_ID_COMPONENT_A_GPIO }, \
	.num_component_id = 1, \
	.function = PAPI.IO.Set, \
	.data = ACTIVE \
}

#define SUBACTIVITIY_CLEAR_GPIO_COMPONENT_A { \
	.ID = SUBACTIVITIY_ID_CLEAR_GPIO_COMPONENT_A, \
	.component_id = { COMPONENT_ID_COMPONENT_A_GPIO }, \
	.num_component_id = 1, \
	.function = PAPI.IO.Clear, \
	.data = INACTIVE \
}

#define SUBACTIVITIY_INIT { \
	.ID = SUBACTIVITIY_ID_INIT, \
	.component_id = { COMPONENT_ID_COMPONENT_A_GPIO }, \
	.num_component_id = 1, \
	.function = CommFunctions.Init, \
	.data = &App.buffers.config \
}

/* Queues */
#define QUEUE_APPLICATION_MESSAGES QUEUE( \
	QUEUE_ID_APPLICATION_MESSAGES, \
	DEFAULT_QUEUE_MAX_QTY, \
	DEFAULT_QUEUE_TIMEOUT_MS, \
	&System.error.system \
)

/* Tasks */
#define TASK_BLINK_GPIO_COMPONENT_A { \
	.ID = TASK_ID_BLINK_GPIO_COMPONENT_A, \
	.component_id = { COMPONENT_ID_COMPONENT_A_GPIO }, \
	.num_component_id = 1, \
	.data = NONE, \
	.ACTION = TASK_ACTION_SCHEDULE, \
	.function = AppFunctions.Tick, \
	.object = &App.buffers.config, \
	.PRIORITY = TASK_PRIORITY_HIGH, \
	.error = &System.error.runtime \
}

/* Task Shelf */
#define TASK_SHELF_GPIO_ONLY { \
	.ID = TASK_SHELF_ID_GPIO_ONLY, \
	.interrupts = { TASK_ID_NONE }, \
	.num_interrupts = 1, \
	.scheduled = { TASK_ID_BLINK_GPIO_COMPONENT_A }, \
	.num_scheduled = 1 \
}

/* States */
#define PROFILE_TEMPLATE \
{ \
	{ /* COMPONENT */ \
		1, \
		{ \
			A_COMPONENT \
		} \
	},  \
	{ /* SUBACTIVITIY */ \
		3, \
		{ \
			SUBACTIVITIY_SET_GPIO_COMPONENT_A, \
			SUBACTIVITIY_CLEAR_GPIO_COMPONENT_A, \
			SUBACTIVITIY_INIT \
		} \
	},  \
	{ /* QUEUE */ \
		1, \
		{ \
			QUEUE_APPLICATION_MESSAGES \
		} \
	},  \
	{ /* TASK */ \
		1, \
		{ \
			TASK_BLINK_GPIO_COMPONENT_A \
		} \
	},  \
	{ /* TASK_SHELF */ \
		1, \
		{ \
			TASK_SHELF_GPIO_ONLY \
		} \
	},  \
	{ /* STATE */ \
		{ \
			{ \
				STATE_ACTIVITY_STARTUP, /* STATE_ACTIVITY */ \
				{ /* SUBACTIVITIES */ \
					SUBACTIVITIY_ID_INIT \
				}, \
				1, /* num_SUBACTIVITIES */ \
				STATE_NAME_ACTIVE, /* EXIT_STATE */ \
			}, \
			STATE_NAME_STARTUP, /* STATE_NAME */ \
			{ /* TASK_SHELF */ \
				TASK_SHELF_ID_NONE \
			}, \
			1, /* num_TASK_SHELF */ \
		}, \
		{ \
			{ \
				STATE_ACTIVITY_ACTIVATE, /* STATE_ACTIVITY */ \
				{ /* SUBACTIVITIES */ \
					SUBACTIVITIY_ID_NONE \
				}, \
				1, /* num_SUBACTIVITIES */ \
				STATE_NAME_IDLE, /* EXIT_STATE */ \
			}, \
			STATE_NAME_ACTIVE, /* STATE_NAME */ \
			{ /* TASK_SHELF */ \
				TASK_SHELF_ID_GPIO_ONLY \
			}, \
			1, /* num_TASK_SHELF */ \
		}, \
		{ \
			{ \
				STATE_ACTIVITY_WAIT, /* STATE_ACTIVITY */ \
				{ /* SUBACTIVITIES */ \
					SUBACTIVITIY_ID_NONE \
				}, \
				1, /* num_SUBACTIVITIES */ \
				STATE_NAME_IDLE, /* EXIT_STATE */ \
			}, \
			STATE_NAME_IDLE, /* STATE_NAME */ \
			{ /* TASK_SHELF */ \
				TASK_SHELF_ID_NONE \
			}, \
			1, /* num_TASK_SHELF */ \
		} \
	} \
};

#endif /*C12_profile_h */
