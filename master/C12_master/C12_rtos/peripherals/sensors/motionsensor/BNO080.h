//
//  BNO080.h
//  sensors
//
//  Created by Matthew Fonken on 7/28/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#ifndef BNO080_h
#define BNO080_h

#include "shtp.h"
#include <string.h>

#define BNO080_DEFAULT_ADDRESS 0x4B
#define BNO080_DEFAULT_CHANNEL COMM_CHAN_I2C
#define BNO080_UART_RVC_HEADER 0xAAAA

#define BNO080_DEFAULT_GET_TIMEOUT 1

typedef enum
{
    BNO080_MOTION_OUTPUT_ACCELERATION,
    BNO080_MOTION_OUTPUT_ANGULAR_VELOCITY,
    BNO080_MOTION_OUTPUT_MAGNETOMETER,
} BNO080_MOTION_OUTPUT;
typedef enum
{
    BNO080_ORIENTATION_OUTPUT_GEOMAGNETIC_ROTATION_VECTOR = 0,
    BNO080_ORIENTATION_OUTPUT_GAME_ROTATION_VECTOR,
    BNO080_ORIENTATION_OUTPUT_AR_VR_STABILIZED_GAME_ROTATION_VECTOR,
    BNO080_ORIENTATION_OUTPUT_ROTATION_VECTOR,
    BNO080_ORIENTATION_OUTPUT_AR_VR_STABILIZED_ROTATION_VECTOR,
    BNO080_ORIENTATION_OUTPUT_GYRO_ROTATION_VECTOR,
    BNO080_ORIENTATION_OUTPUT_GYRO_ROTATION_VECTOR_PREDICTION,
} BNO080_ORIENTATION_OUTPUT;
typedef enum
{
    BNO080_ACCELEROMETER = SH2_SENSOR_REPORT_ACCELEROMETER,
    BNO080_RAW_ACCELEROMETER = SH2_SENSOR_REPORT_RAW_ACCELEROMETER,
    
    BNO080_GYROSCOPE_CALIBRATED = SH2_SENSOR_REPORT_GYROSCOPE_CALIBRATED,
    BNO080_GYROSCOPE_UNCALIBRATED = SH2_SENSOR_REPORT_GYROSCOPE_UNCALIBRATED,
    BNO080_RAW_GYROSCOPE = SH2_SENSOR_REPORT_RAW_GYROSCOPE,
    
    BNO080_MAGNETIC_FIELD_CALIBRATED = SH2_SENSOR_REPORT_MAGNETIC_FIELD_CALIBRATED,
    BNO080_MAGNETIC_FIELD_UNCALIBRATED = SH2_SENSOR_REPORT_MAGNETIC_FIELD_UNCALIBRATED,
    BNO080_RAW_MAGNETOMETER = SH2_SENSOR_REPORT_RAW_MAGNETOMTER,
    
    BNO080_LINEAR_ACCELERATION = SH2_SENSOR_REPORT_LINEAR_ACCELERATION,
    BNO080_SIGNIFICANT_MOTION = SH2_SENSOR_REPORT_SIGNIFICANT_MOTION,
} BNO080_MOTION;

typedef enum
{
    BNO080_ROTATION_VECTOR = SH2_SENSOR_REPORT_ROTATION_VECTOR,
    BNO080_GRAVITY = SH2_SENSOR_REPORT_GRAVITY,
    BNO080_GAME_ROTATION_VECTOR = SH2_SENSOR_REPORT_GAME_ROTATION_VECTOR,
    BNO080_GEOMAGNETIC_ROTATION_VECTOR = SH2_SENSOR_REPORT_GEOMAGNETIC_ROTATION_VECTOR,
    BNO080_STABILIZED_ROTATION_VECTOR = SH2_SENSOR_REPORT_STABILIZED_ROTATION_VECTOR,
    BNO080_STABILIZED_GAME_ROTATION_VECTOR = SH2_SENSOR_REPORT_STABILIZED_GAME_ROTATION_VECTOR,
    BNO080_GYRO_INTEGRATED_ROTATION_VECTOR = SH2_SENSOR_REPORT_GYRO_INTEGRATED_ROTATION_VECTOR,
} BNO080_ROTATION;
typedef enum
{
    BNO080_STABILITY_CLASSIFIER = SH2_SENSOR_REPORT_STABILITY_CLASSIFIER,
    BNO080_PERSONAL_ACTIVITY_CLASSIFIER = SH2_SENSOR_REPORT_PERSONAL_ACTIVITY_CLASSIFIER,
} BNO080_CLASSIFIER;
typedef enum
{
    BNO080_STEP_DETECTOR = SH2_SENSOR_REPORT_STEP_DETECTOR,
    BNO080_STEP_COUNTER = SH2_SENSOR_REPORT_STEP_COUNTER,
    BNO080_SHAKE_DETECTOR = SH2_SENSOR_REPORT_SHAKE_DETECTOR,
    BNO080_FLIP_DETECTOR = SH2_SENSOR_REPORT_FLIP_DETECTOR,
    BNO080_PICKUP_DETECTOR = SH2_SENSOR_REPORT_PICKUP_DETECTOR,
    BNO080_STABILITY_DETECTOR = SH2_SENSOR_REPORT_STABILITY_DETECTOR,
    BNO080_SLEEP_DETECTOR = SH2_SENSOR_REPORT_SLEEP_DETECTOR,
    BNO080_TILT_DETECTOR = SH2_SENSOR_REPORT_TILT_DETECTOR,
    BNO080_POCKET_DETECTOR = SH2_SENSOR_REPORT_POCKET_DETECTOR,
    BNO080_CIRCLE_DETECTOR = SH2_SENSOR_REPORT_CIRCLE_DETECTOR,
} BNO080_DETECTOR;

typedef BNO080_MOTION bno080_motion_t;
typedef BNO080_ROTATION bno080_rotation_t;
typedef BNO080_CLASSIFIER bno080_classifier_t;
typedef BNO080_DETECTOR bno080_detector_t;
typedef uint8_t bno080_feature_t;

static void BNO080GenerateSH2Client( shtp_client_t * client, uint8_t ID )
{
    shtp_client_header header = { BNO080_DEFAULT_ADDRESS, BNO080_DEFAULT_CHANNEL };
    shtp_client_buffer buffer = { 0 };
    shtp_client_product_id product = { 0 };
    shtp_client_output output = { 0 };
    SHTPFunctions.GenerateClient( client, ID, 0, &header, &buffer, &product, &output );
}

bool BNO080EnableFeature( shtp_client_t *, bno080_feature_t, uint32_t, uint32_t );
bool BNO080DisableFeature( shtp_client_t *, bno080_feature_t );
bool BNO080Refresh( shtp_client_t * );
bool BNO080Read( shtp_client_t * );
bool BNO080AttemptGet( uint32_t );

typedef struct
{
    bool (*EnableFeature)( shtp_client_t *, bno080_feature_t, uint32_t, uint32_t );
    bool (*Refresh)( shtp_client_t * );
    bool (*Read)( shtp_client_t * );
    bool (*AttemptGet)( uint32_t );
    void (*GenerateClient)( shtp_client_t *, uint8_t );
} bno080_functions;

static const bno080_functions BNO080Functions =
{
    .EnableFeature = BNO080EnableFeature,
    .Refresh = BNO080Refresh,
    .Read = BNO080Read,
    .AttemptGet = BNO080AttemptGet,
    .GenerateClient = BNO080GenerateSH2Client
};

#endif /* BNO080_h */
