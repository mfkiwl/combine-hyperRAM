//
//  motionsensor.h
//  sensors
//
//  Created by Matthew Fonken on 7/28/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#ifndef motionsensor_h
#define motionsensor_h

#include "quaternion.h"
#include "BNO080.h"

#define IMU_DEFAULT_COMPONENT_PROTOCOL SYSTEM_COMPONENT_PROTOCOLSPI

typedef enum
{
    IMU_CHIP_BNO080 = 1
} IMU_CHIP;

typedef IMU_CHIP imu_chip_t;
typedef uint8_t imu_feature_t;

typedef struct
{
    shtp_client_t client;
    component_id_t ID;
    imu_chip_t chip;
    rotation_vector_t rotation;
    uint32_t sensor_specific_metadata;
    uint32_t interval;
} imu_t;

bool Init_IMU( imu_t *, component_id_t, uint8_t, comm_protocol, imu_chip_t );
bool Resume_IMU_RotVec( imu_t * );
bool Pause_IMU_RotVec( imu_t * );

static void RotVecToQuaternion( rotation_vector_t * r, quaternion_t * q )
{
    q->w = r->real;
    q->x = r->i;
    q->y = r->j;
    q->z = r->k;
}

typedef struct
{
    bool (*Init)( imu_t *, component_id_t, uint8_t, comm_protocol, imu_chip_t );
    bool (*Start)( shtp_client_t *, imu_feature_t, uint32_t, uint32_t );
    bool (*Stop)( shtp_client_t *, imu_feature_t );
    bool (*Read)( shtp_client_t * );
    bool (*Refresh)( shtp_client_t * );
    bool (*ResumeRotVec)( imu_t * );
    bool (*PauseRotVec)( imu_t * );
    void (*GenerateClient)( shtp_client_t *, uint8_t, void * );
} imu_functions;

static const imu_functions IMUFunctions =
{
    .Init = Init_IMU,
    .Start = BNO080EnableFeature,
    .Stop = BNO080DisableFeature,
    .Read = BNO080Read,
    .Refresh = BNO080Refresh,
    .ResumeRotVec = Resume_IMU_RotVec,
    .PauseRotVec = Pause_IMU_RotVec,
    .GenerateClient = BNO080GenerateSH2Client
};

#endif /* motionsensor_h */
