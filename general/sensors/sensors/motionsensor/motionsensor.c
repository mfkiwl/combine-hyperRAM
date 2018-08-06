//
//  motionsensor.c
//  sensors
//
//  Created by Matthew Fonken on 7/28/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#include <stdio.h>
#include "motionsensor.h"

bool Init_IMU( imu_t * imu, uint8_t ID, system_comm_channel channel, imu_chip_t chip )
{
    imu->client.ID = ID;
    imu->client.comm_channel = channel;
    imu->chip = chip;
    imu->sensor_specific_metadata = 0;
    return true;
}