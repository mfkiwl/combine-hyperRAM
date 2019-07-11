//
//  rho_wrapper.cpp
//  tau+
//
//  Created by Matthew Fonken on 3/26/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#include "rho_wrapper.hpp"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

//using namespace cv;

Rho::Rho( int width, int height ) : width(width), height(height)
{
    LOG_RHO(ALWAYS, "Initializing Rho Utility: %dx%d & [KTarg-%f, VarNorm-%.3f, VarSca-%.3f]\n", width, height, RHO_K_TARGET, RHO_VARIANCE_NORMAL, RHO_VARIANCE_SCALE);
    size_t
        aa = CAPTURE_WIDTH + CAPTURE_HEIGHT,
        a = sizeof(redistribution_variables),
        b = sizeof(rho_detection_variables),
        c = sizeof(prediction_predict_variables),
        d = sizeof(rho_core_t)-sizeof(core.cframe),
        e = a + b + c + d,
        f = sizeof(density_map_pair_t),
        g = sizeof(prediction_pair_t),
        h = sizeof(rho_pid_t),
        j = sizeof(rho_kalman_t)
#ifdef __PSM__
        ,k = sizeof(gaussian_mixture_model_t),
        l = sizeof(hidden_markov_model_t),
        m = sizeof(fsm_system_t),
        n = sizeof(psm_t);
        LOG_RHO(ALWAYS, "\tgmm-%luB\thmm: %luB\tfsm: %luB\tpsm: %luB\n",k,l,m,n);
#else
        ;
#endif
    LOG_RHO(ALWAYS, "\tSizes: Frame-%.3fkB RedVar-%luB SelVars-%luB PredVars-%luB Rho-%lukB > Tot-%.3fkB\n", ((double)aa)/1024, a, b, c, d>>10, ((double)e)/1024);
    LOG_RHO(ALWAYS, "\tdenmapp-%luB\tpredmap: %luB\tpid: %luB\trkal: %luB\n",f,g,h,j);
    pthread_mutex_init(&density_map_pair_mutex, NULL);
    pthread_mutex_init(&c_mutex, NULL);
    
    RhoCore.Initialize(&core, width, height);
#ifdef __PSM__
    PSMFunctions.Initialize( &core.PredictiveStateModel );
#endif
    backgrounding_event = false;
    
    RhoInterrupts.FRAME_INIT();
}

void Rho::Perform( cimage_t & img, GlobalPacket * p )
{
    pthread_mutex_lock(&c_mutex);
    pthread_mutex_lock(&density_map_pair_mutex);
    
    /* Core Rho Functions */
    Generate_Density_Map_Using_Interrupt_Model( img, backgrounding_event );
    RhoCore.Perform( &core, backgrounding_event );
    /* * * * * * * * * * */
    
    pthread_mutex_unlock(&density_map_pair_mutex);
    memcpy((byte_t *)p, (byte_t*)&core.Packet, sizeof(packet_t));
    backgrounding_event = false; // Generate background always and only once
    pthread_mutex_unlock(&c_mutex);
}

/* Interrupt (Simulated Hardware-Driven) Density map generator */
void Rho::Generate_Density_Map_Using_Interrupt_Model( const cimage_t image, bool backgrounding )
{
    if( backgrounding )
    {
        RhoVariables.ram.Dx      =  core.DensityMapPair.x.background;
        RhoVariables.ram.Dy      =  core.DensityMapPair.y.background;
        RhoVariables.ram.CX_ADDR = &core.By;
        RhoVariables.ram.CY_ADDR = &core.Bx;
        RhoVariables.ram.Q       =  core.Qb;
    }
    
    RhoInterrupts.RHO_FUNCTION( image );
    
    if( backgrounding )
    {
        RhoVariables.ram.Dx      =  core.DensityMapPair.x.map;
        RhoVariables.ram.Dy      =  core.DensityMapPair.y.map;
        RhoVariables.ram.CX_ADDR = &core.Cx;
        RhoVariables.ram.CY_ADDR = &core.Cy;
        RhoVariables.ram.Q       =  core.Q;
        core.DensityMapPair.x.has_background = true;
        core.DensityMapPair.y.has_background = true;
    }
}
