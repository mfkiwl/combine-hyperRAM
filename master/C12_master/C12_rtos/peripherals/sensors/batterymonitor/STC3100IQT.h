/* File: STC3100IQT.h
 * Author: Matthew Fonken
 * Source: https://www.mouser.com/datasheet/2/389/STC3100-974293.pdf
 * Description:
    The STC3100 monitors the critical parameters of a single-cell Li-Ion battery (voltage, temperature and current) and includes hardware functions to implement a gas gauge for battery charge monitoring, based on a programmable 12- to 14-bit A/D converter. With a typical 30 milliOhms external sense resistor, the battery current can be up to 2.5 A and the accumulator system provides a capacity up to +/-7000 mAh with a resolution of 0.2 mAh. The device is programmable through the I2C interface.
 */

#ifndef STC3100IQT_h
#define STC3100IQT_h

#include "i2c_template.h"
#include <stdlib.h>

#define STC_ADDR                0x70  // STC I2C address
#define STC_ID                  0x10  // STC type ID
#define STC_CRC_LENGTH_BIT      8     // Byte length of CRC
#define STC_TIMEBASE            32768 // Hz
#define STC_MV_RANGE            80    // +/-mV

#define STC_REG_LEN             1   // Byte length of register
#define STC_WORD_LEN            2   // Byte length of word

/* Control registers 0 to 23 */
#define STC_REG_MODE            0   // R/W Mode register
#define STC_REG_CTRL            1   // R/W Control and status register
#define STC_REG_CHARGE_LOW      2   // R Gas gauge charge data, bits 0-7
#define STC_REG_CHARGE_HIGH     3   // R Gas gauge charge data, bits 8-15
#define STC_REG_COUNTER_LOW     4   // R Number of conversions, bits 0-7
#define STC_REG_COUNTER_HIGH    5   // R Number of conversions, bits 8-15
#define STC_REG_CURRENT_LOW     6   // R Battery current value, bits 0-7
#define STC_REG_CURRENT_HIGH    7   // R Battery current value, bits 8-15
#define STC_REG_VOLTAGE_LOW     8   // R Battery voltage value, bits 0-7
#define STC_REG_VOLTAGE_HIGH    9   // R Battery voltage value, bits 8-15
#define STC_REG_TEMPERATURE_LOW 10  // R Temperature value, bits 0-7
#define STC_REG_TEMPERATURE_HIGH 11 // R Temperature value, bits 8-15

/* Device ID registers 24 to 31 */
#define STC_REG_ID_LEN          8   // ID length in bytes
#define STC_REG_ID0             24  // R Part type ID = 10h
#define STC_REG_ID1             25  // R Unique part ID, bits 0-7
#define STC_REG_ID2             26  // R Unique part ID, bits 8-15
#define STC_REG_ID3             27  // R Unique part ID, bits 16-23
#define STC_REG_ID4             28  // R Unique part ID, bits 24-31
#define STC_REG_ID5             29  // R Unique part ID, bits 32-39
#define STC_REG_ID6             30  // R Unique part ID, bits 40-47
#define STC_REG_ID7             31  // R Device ID CRC

typedef long STC_id_t;

/* RAM Register 32 - 63 */
#define STC_REG_RAM_LEN         32  // RAM number of registers
#define STC_REG_RAM_START       32  // R/W General-purpose RAM registers 0-31

/* REG MODE - Regoister 0 */
typedef struct
{
uint8_t
    SEL_EXT_CLK:1,  // 0    R/W 0   32,768 Hz clock source: 0: auto-detect, 1: external clock
    GG_RES:2,       // 1-2  R/W 00  Gas gauge ADC resolution: 00:14 bits, 01:13 bits, 10:12 bits
    GG_CAL:1,       // 3    R/W 0   0: no effect 1: used to calibrate the AD converters
    GG_RUN:1,       // 4    R/W 0   0: standby mode. Accumulator and counter registers are frozen, gas gauge and battery monitor functions are in standby. 1: operating mode.
    RESERVED:3;     // 5-7  Unused
} stc_reg_mode_t;

/* REG CTRL - Register 1 */
typedef struct
{
uint8_t
    IO0DATA:1,      // 0    R   X   Port IO0 data status: 0 = IO0 input is low, 1 = IO0 input is high
                    //      W   1   Port IO0 data output drive: 0 = IO0 output is driven low,1 = IO0 output is open
    GG_RST:1,       // 1    W   0   0: no effect 1: resets the charge accumulator and conversion counter. GG_RST is a self-clearing bit.
    GG_EOC:1,       // 2    R   1   Set at the end of a battery current conversion cycle. Clears upon reading.
    VTM_EOC:1,      // 3    R   1   Set at the end of a battery voltage or temperature conversion cycle. Clears upon reading.
    PORDET:1,       // 4    R   1   Power on reset (POR) detection bit: 0 = no POR event occurred, 1 = POR event occurred
                    //      W   0   Soft reset: 0 = release the soft-reset and clear the POR detection bit, 1 = assert the soft-reset and set the POR detection bit.
    RESERVED:3;     // 5-7  Unused
} stc_reg_ctrl_t;

/* STC basic structure */
typedef struct
{
    stc_reg_mode_t mode;
    stc_reg_ctrl_t ctrl;
} stc_t;

/* I2C Events */
static inline i2c_event_t STCSetModeEvent(void)        { return (i2c_event_t){ I2C_WRITE_REG_EVENT, STC_REG_MODE,             STC_REG_LEN,     STC_ADDR    }; }
static inline i2c_event_t STCGetModeEvent(void)        { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_MODE,             STC_REG_LEN,     STC_ADDR    }; }
static inline i2c_event_t STCSetControlEvent(void)     { return (i2c_event_t){ I2C_WRITE_REG_EVENT, STC_REG_CTRL,             STC_REG_LEN,     STC_ADDR    }; }
static inline i2c_event_t STCGetControlEvent(void)     { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_CTRL,             STC_REG_LEN,     STC_ADDR    }; }
static inline i2c_event_t STCGetIDEvent(void)          { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_ID0,              STC_REG_ID_LEN,  STC_ADDR    }; }
static inline i2c_event_t STCGetRAMEvent(void)         { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_RAM_START,        STC_REG_RAM_LEN, STC_ADDR    }; }
static inline i2c_event_t STCGetChargeEvent(void)      { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_CHARGE_LOW,       STC_WORD_LEN,    STC_ADDR    }; }
static inline i2c_event_t STCGetCounterEvent(void)     { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_COUNTER_LOW,      STC_WORD_LEN,    STC_ADDR    }; }
static inline i2c_event_t STCGetCurrentEvent(void)     { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_CURRENT_LOW,      STC_WORD_LEN,    STC_ADDR    }; }
static inline i2c_event_t STCGetVoltageEvent(void)     { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_VOLTAGE_LOW,      STC_WORD_LEN,    STC_ADDR    }; }
static inline i2c_event_t STCGetTemperatureEvent(void) { return (i2c_event_t){ I2C_READ_REG_EVENT,  STC_REG_TEMPERATURE_LOW,  STC_WORD_LEN,    STC_ADDR    }; }

static void STCSetMode( stc_reg_mode_t data )
{
    i2c_data[0] = *(uint8_t *)&data;
    performI2CEvent(STCSetModeEvent(), i2c_data);
}
static stc_reg_mode_t STCGetMode(void)
{
    performI2CEvent(STCGetModeEvent(), i2c_data);
    return *(stc_reg_mode_t *)&i2c_data[0];
}
static void STCSetControl( stc_reg_ctrl_t data )
{
    i2c_data[0] = *(uint8_t *)&data;
    performI2CEvent(STCSetControlEvent(), i2c_data);
}
static stc_reg_ctrl_t STCGetControl(void)
{
    performI2CEvent(STCGetControlEvent(), i2c_data);
    return *(stc_reg_ctrl_t *)&i2c_data;
}
static uint8_t STCGetIDE(void)
{
    performI2CEvent(STCGetIDEvent(), i2c_data);
    return (uint8_t)*i2c_data;
}
static uint8_t STCGetRAM(void)
{
    performI2CEvent(STCGetRAMEvent(), i2c_data);
    return (uint8_t)*i2c_data;
}
static uint8_t STCGetCharge(void)
{
    performI2CEvent(STCGetChargeEvent(), i2c_data);
    return (uint8_t)*i2c_data;
}
static uint8_t STCGetCounter(void)
{
    performI2CEvent(STCGetCounterEvent(), i2c_data);
    return (uint8_t)*i2c_data;
}
static uint8_t STCGetCurrent(void)
{
    performI2CEvent(STCGetCurrentEvent(), i2c_data);
    return (uint8_t)*i2c_data;
}
static uint8_t STCGetVoltage(void)
{
    performI2CEvent(STCGetVoltageEvent(), i2c_data);
    return (uint8_t)*i2c_data;
}
static uint8_t STCGetTemperature(void)
{
    performI2CEvent(STCGetTemperatureEvent(), i2c_data);
    return (uint8_t)*i2c_data;
}

typedef struct
{
i2c_event_t
    (*SetModeEvent)(void),
    (*GetModeEvent)(void),
    (*SetControlEvent)(void),
    (*GetControlEvent)(void),
    (*GetIDEvent)(void),
    (*GetRAMEvent)(void),
    (*GetChargeEvent)(void),
    (*GetCounterEvent)(void),
    (*GetCurrentEvent)(void),
    (*GetVoltageEvent)(void),
    (*GetTemperatureEvent)(void);
    void (*SetMode)( stc_reg_mode_t );
    stc_reg_mode_t (*GetMode)(void);
    void (*SetControl)( stc_reg_ctrl_t );
    stc_reg_ctrl_t (*GetControl)(void);
uint8_t
    (*GetIDE)(void),
    (*GetRAM)(void),
    (*GetCharge)(void),
    (*GetCounter)(void),
    (*GetCurrent)(void),
    (*GetVoltage)(void),
    (*GetTemperature)(void);
} stc_functions;

static stc_functions STCFunctions =
{
    .SetMode             = STCSetMode,
    .GetMode             = STCGetMode,
    .SetControl          = STCSetControl,
    .GetControl          = STCGetControl,
    .GetIDE              = STCGetIDE,
    .GetRAM              = STCGetRAM,
    .GetCharge           = STCGetCharge,
    .GetCounter          = STCGetCounter,
    .GetCurrent          = STCGetCurrent,
    .GetVoltage          = STCGetVoltage,
    .GetTemperature      = STCGetTemperature,
    .SetModeEvent        = STCSetModeEvent,
    .GetModeEvent        = STCGetModeEvent,
    .SetControlEvent     = STCSetControlEvent,
    .GetControlEvent     = STCGetControlEvent,
    .GetIDEvent          = STCGetIDEvent,
    .GetRAMEvent         = STCGetRAMEvent,
    .GetChargeEvent      = STCGetChargeEvent,
    .GetCounterEvent     = STCGetCounterEvent,
    .GetCurrentEvent     = STCGetCurrentEvent,
    .GetVoltageEvent     = STCGetVoltageEvent,
    .GetTemperatureEvent = STCGetTemperatureEvent
};


#endif /* STC3100IQT_h */
