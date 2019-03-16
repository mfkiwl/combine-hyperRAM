//
//  detection_map.c
//  pcrxprm
//
//  Created by Matthew Fonken on 2/5/19.
//  Copyright © 2019 Matthew Fonken. All rights reserved.
//

#include "detection_map.h"

void InitializeDetectionMap( detection_map_t * map, uint16_t len )
{
    memset( map, 0, sizeof(detection_map_t) );
    map->length = len;
    
#ifdef WRITE_DETECTION_MAP_TO_FILE
    detection_map_file = fopen(WRITE_DETECTION_MAP_TO_FILE, "w+");
    fputs(DETECTION_MAP_DESCRIPTOR"\n", detection_map_file);
    fputs("Density,Threshold,Id\n", detection_map_file);
    fclose(detection_map_file);
#endif
}

uint8_t GetDetectionMapFirstIndex( detection_map_t * map )
{
    if( map->fill < ( map->length - 1 ) )
        return 0;
    else
        return ( map->index + 1 ) % ( map->length );
}

void IncrementDetectionMapIndex( detection_map_t * map )
{
    map->index++;
    map->index &= ( DETECTION_BUFFER_MASK );
    if( ++map->fill > DETECTION_BUFFER_SIZE )
        map->fill = DETECTION_BUFFER_MASK;
}

void AddBlobToPredictionMap( detection_map_t * map, uint8_t thresh, uint8_t density, uint8_t tracking_id )
{
    detection_element_t e = { thresh, density, tracking_id };
    map->buffer[map->index] = e;
    DetectionMapFunctions.Increment( map );
    
#ifdef WRITE_DETECTION_MAP_TO_FILE
    char msg[32] = { 0 };
    sprintf(msg, "%d,%d,%d\n", e.density, e.thresh, e.tracking_id);
    detection_map_file = fopen(WRITE_DETECTION_MAP_TO_FILE, "a");
    fputs(msg, detection_map_file);
    fclose(detection_map_file);
#endif
}

void AddBlobSetToPredictionMap( detection_map_t * map, prediction_pair_t * pp, uint8_t thresh )
{
    uint8_t p = 0, i, io;

    prediction_t * pair[2] = { &pp->x, &pp->y };
    for( ; p < 2; p++ )
    {
        for( i = 0; i < pair[p]->NumBlobs; i++ )
        {
            io = pair[p]->BlobsOrder[i];
            blob_t * b = &pair[p]->Blobs[io];
            double estimated_density = (double)b->den + (double)*pair[p]->PreviousPeak;
//            double A = (double)(b->den<<8), B = (double)MAX_DENSITY;
            uint8_t byteDensity = estimated_density;//(uint8_t)ZDIV( A, B );
            int ar = rand() % (2*SHAKE_INJECTION) - SHAKE_INJECTION, br = rand() % (2*SHAKE_INJECTION) - SHAKE_INJECTION;
            byteDensity = (uint8_t)BOUND((int)byteDensity+ar, 0, 256);
            thresh = (uint8_t)BOUND((int)thresh+br, 0, 256);
            DetectionMapFunctions.Add( map, thresh, byteDensity, b->tracking_id);
        }
    }
    map->first = DetectionMapFunctions.FirstIndex( map );
}


