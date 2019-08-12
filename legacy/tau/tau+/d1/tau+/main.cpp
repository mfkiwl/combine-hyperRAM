//
//  main.cpp
//  tau+
//
//  Created by Matthew Fonken on 8/23/17.
//  Copyright © 2017 Marbl. All rights reserved.
//

#include <stdio.h>
#include <stdint.h>

#include "utility_master.h"
#include "environment_master.h"
#include "tau_master.h"
#include "combine.hpp"

using namespace cv;
using namespace std;

#define DRAW        0
#define FPS         10
#define KEY_DELAY   1000/FPS

#define PAUSE_ENVIRONMENT_KEY   ' '
#define PERFORMANCE_TEST_KEY    'p'
#define REQUEST_IMU_OFFSET_KEY  'c'

int main( int argc, const char * argv[] )
{
#ifdef HAS_CAMERA
    ImageUtility utility("ImageUtility");
#else
    ImageUtility utility("ImageUtility", "frames/noiseS5", 22, FNL_RESIZE_W, FNL_RESIZE_H);
#endif
    Tau tau("Tau", &utility, FNL_RESIZE_W, FNL_RESIZE_H);
    Combine combine("Combine", &tau, FNL_RESIZE_W, FNL_RESIZE_H);
    SerialWriter comm(SFILE, FILENAME);
    
    Environment env(&utility, 15);
    env.addTest(&tau, 60);
    env.addTest(&combine, &comm, 10);
    
    env.start();
    usleep(50000);
    combine.request();
    env.pause();
    
    pthread_mutex_lock(&utility.outframe_mutex);
    TauDraw drawer(&tau, utility.outframe);
    pthread_mutex_unlock(&utility.outframe_mutex);
    
    usleep(500000);
    env.resume();
    
    while(1)
    {
#ifdef DRAW
        pthread_mutex_lock(&utility.outframe_mutex);
        drawer.drawDensitiesOnFrame(utility.outframe);
        imshow("Outframe", utility.outframe);
#ifdef DRAW_RHO_MAPS
        imshow("Rho X Map", drawer.RMX);
        imshow("Rho Y Map", drawer.RMY);
#endif
        pthread_mutex_unlock(&utility.outframe_mutex);
#endif
    
        char c = waitKey(KEY_DELAY);
        switch(c)
        {
            case PAUSE_ENVIRONMENT_KEY:
                if(env.status != LIVE) env.resume();
                else env.pause();
                break;
            case PERFORMANCE_TEST_KEY:
                env.pause();
                usleep(10000);
                tau.avg = 0;
                tau.count = 0;
                env.start();
                usleep(10000000);
                env.pause();
                printf("Tau averaged %fms for %d iterations\n", tau.avg*1000, tau.count);
                break;
            case REQUEST_IMU_OFFSET_KEY:
                printf("Sending imu offset request\n");
                combine.request();
                break;
            default:
                if(utility.loop(c))
                {
                    utility.trigger();
                    tau.trigger();
                }
                break;
        }
    }
    return 0;
}