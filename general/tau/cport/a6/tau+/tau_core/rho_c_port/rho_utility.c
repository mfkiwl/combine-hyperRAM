//
//  rho_utility.c
//  tau+
//
//  Created by Matthew Fonken on 2/7/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#include "rho_utility.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

//#define ALLOW_NEGATIVE_REDISTRIBUTION

#define FOR(L)       for( int i = L; i > 0; --i)
#define FORA(L,A)    for( int i = L; i > 0; --i, A[i] )
#define FORA2(L,A,B) for( int i = L; i > 0; --i, A[i], B[i] )
#define ZDIV(X,Y)    (!Y?2<<10:X/Y)

#define N -1

const density_redistribution_lookup_t rlookup =
{
    {
        {
            { { 0, 1, 3, 4 }, { 2, 5 }, { 6, 7 }, { 8 } },
            { { 0 }, { 1, 2 }, { 3, 6 }, { 4, 5, 7, 8 } },
            { { 0, 1, 2, 3 }, { 1, 3 }, { 2, 3 }, { 3 } },
            { 4, 2, 2, 1 }
        },
        {
            { { 0, 3 }, { 1, 2, 4, 5 }, { 6 }, { 7, 8 } },
            { { 0, 1 }, { 2 }, { 3, 4, 6, 7 }, { 5, 8 } },
            { { 0, 2 }, { 0, 1, 2, 3 }, { 2 }, { 2, 3 } },
            { 2, 4, 1, 2 }
        },
        {
            { { 0, 1 }, { 2 }, { 3, 4, 6, 7 }, { 5, 8 } },
            { { 0, 3 }, { 1, 2, 4, 5 }, { 6 }, { 7, 8 } },
            { { 0, 1 }, { 1 }, { 0, 1, 2, 3 }, { 1, 3 } },
            { 2, 1, 4, 2 }
        },
        {
            { { 0 }, { 1, 2 }, { 3, 6 }, { 4, 5, 7, 8 } },
            { { 0, 1, 3, 4 }, { 2, 5 }, { 6, 7 }, { 8 } },
            { { 0 }, { 0, 1 }, { 0, 2 }, { 0, 1, 2, 3 } },
            { 1, 2, 2, 4 }
        }
    }
};

static void Redistribute_Densities( rho_c_utility * utility, const density_redistribution_lookup_t * lookup )
{
    int Bx = utility->background_map_pair.x.centroid,
        By = utility->background_map_pair.y.centroid,
        Cx = utility->Cx,
        Cy = utility->Cy,
        x0 = Bx, x1 = Cx, y0 = By, y1 = Cy,
        area[9];
    if( Cx < Bx ){x0 = Cx; x1 = Bx;}
    if( Cy < By ){y0 = Cy; y1 = By;}
    
    int xl[3] = {x0, x1-x0, utility->width-x1},
        yl[3] = {y0, y1-y0, utility->height-y1};
    for( int y = 0, p = 0; y < 3; y++ )
        for( int x = 0; x < 3; x++ )
            area[p++] = xl[x]* yl[y];
    
    uint8_t c = ( (uint8_t)( utility->Cy < By ) << 1 ) + (uint8_t)( utility->Cx < Bx );
    for( int q = 0; q < 4; q++ )
    {
        int bd = 0, l = lookup->config[c].length[q], l_ = lookup->config[c].length[3-q];
        for( int i = 0; i < l; i++ )
        {
            int a = 0, b = 0;
            a = area[lookup->config[c].current[q][i]];
            for( int j = 0; j < l_; j++ )
                b += area[lookup->config[c].background[lookup->config[c].factor[q][i]][j]];
            bd += ZDIV( a, b ) * utility->Qb[q];
        }
#ifndef ALLOW_NEGATIVE_REDISTRIBUTION
        if( bd > utility->Q[q] ) utility->Q[q] = 0;
        else
#endif
            utility->Q[q] -= bd;
    }
}

void Init(rho_c_utility * utility, int w, int h)
{
    utility->width  = w;
    utility->height = h;
    
    utility->density_map_pair.x.map = (int*)malloc(sizeof(int)*h);
    utility->density_map_pair.x.length = h;
    utility->density_map_pair.x.max[0] = 0;
    utility->density_map_pair.x.max[1] = 0;
    RhoKalman.init(&utility->density_map_pair.x.kalmans[0], 0, RHO_DEFAULT_LS, RHO_DEFAULT_VU, RHO_DEFAULT_BU, RHO_DEFAULT_SU);
    RhoKalman.init(&utility->density_map_pair.x.kalmans[1], 0, RHO_DEFAULT_LS, RHO_DEFAULT_VU, RHO_DEFAULT_BU, RHO_DEFAULT_SU);
    
    utility->density_map_pair.y.map = (int*)malloc(sizeof(int)*w);
    utility->density_map_pair.y.length = w;
    utility->density_map_pair.y.max[0] = 0;
    utility->density_map_pair.y.max[1] = 0;
    RhoKalman.init(&utility->density_map_pair.y.kalmans[0], 0, RHO_DEFAULT_LS, RHO_DEFAULT_VU, RHO_DEFAULT_BU, RHO_DEFAULT_SU);
    RhoKalman.init(&utility->density_map_pair.y.kalmans[1], 0, RHO_DEFAULT_LS, RHO_DEFAULT_VU, RHO_DEFAULT_BU, RHO_DEFAULT_SU);
    
    utility->background_map_pair.x.map = (int*)malloc(sizeof(int)*h);
    utility->background_map_pair.x.length = h;
    //memset( &utility->background_map_pair.x.map, 0, sizeof(int)*h );
    
    utility->background_map_pair.y.map = (int*)malloc(sizeof(int)*w);
    utility->background_map_pair.y.length = w;
    //memset( &utility->background_map_pair.y.map, 0, sizeof(int)*w );
    
    RhoKalman.init(&utility->prediction_pair.x.primary,   0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    RhoKalman.init(&utility->prediction_pair.x.secondary, 0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    RhoKalman.init(&utility->prediction_pair.y.primary,   0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    RhoKalman.init(&utility->prediction_pair.y.secondary, 0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    utility->prediction_pair.x.primary_new   = 0.;
    utility->prediction_pair.x.secondary_new = 0.;
    utility->prediction_pair.y.primary_new   = 0.;
    utility->prediction_pair.y.secondary_new = 0.;
    
    memset(&utility->prediction_pair.x.probabilities, 0, sizeof(double)*3);
    memset(&utility->prediction_pair.y.probabilities, 0, sizeof(double)*3);
    
    /* Connect to Interrupt Model variable structure */
    RhoVariables.ram.Dx      =  utility->density_map_pair.x.map;
    RhoVariables.ram.Dy      =  utility->density_map_pair.y.map;
    RhoVariables.ram.Q       =  utility->Q;
    RhoVariables.ram.CX_ADDR = &utility->Cx;
    RhoVariables.ram.CY_ADDR = &utility->Cy;
    RhoVariables.ram.C_FRAME =  utility->cframe;
    RhoVariables.ram.THRESH_ADDR = &utility->thresh;
    
    RhoVariables.global.C_FRAME_MAX = C_FRAME_SIZE;
    RhoVariables.global.y_delimiter = Y_DEL;
    RhoVariables.global.W    =  utility->width;
    RhoVariables.global.H    =  utility->height;
    
    RhoInterrupts.FRAME_INIT();
    pthread_mutex_init(&RhoVariables.global.rho_int_mutex, NULL);
    pthread_mutex_lock(&RhoVariables.global.rho_int_mutex);
}

/* Interrupt (Simulated Hardware-Driven) Density map generator */
void Generate_Density_Map_Using_Interrupt_Model( rho_c_utility * utility, cimage_t image, bool backgrounding )
{
    if( backgrounding )
    {
        RhoVariables.ram.Dx      =  utility->background_map_pair.x.map;
        RhoVariables.ram.Dy      =  utility->background_map_pair.y.map;
        RhoVariables.ram.Q       =  utility->Qb;
        utility->background_map_pair.x.centroid =  utility->Cx;
        utility->background_map_pair.y.centroid =  utility->Cy;
    }
    pixel_base_t test_port = 0;
    RhoVariables.ram.CAM_PORT = &test_port;
    RhoInterrupts.FRAME_START();
    pthread_create(&RhoVariables.global.loop_thread, NULL, (void *)RhoInterrupts.LOOP_THREAD, (void *)&RhoVariables.global.rho_int_mutex);
    int p = 0;
    for( int y = 0; y < image.height; y++ )
    {
        RhoInterrupts.ROW_INT();
        for( int x = 0; x < image.width; x++, p++ )
        {
            *(RhoVariables.ram.CAM_PORT) = image.pixels[p];
            RhoInterrupts.PCLK_INT();
        }
    }
    RhoInterrupts.FRAME_END();
    
    if( backgrounding )
    {
        RhoVariables.ram.Dx      =  utility->density_map_pair.x.map;
        RhoVariables.ram.Dy      =  utility->density_map_pair.y.map;
        RhoVariables.ram.Q       =  utility->Q;
    }
    else
    {
        Redistribute_Densities( utility, &rlookup );
    }
}

void Filter_and_Select( rho_c_utility * utility, DensityMapC * d, DensityMapC * b, PredictionC * r )
{
    int l = d->length,
    fpeak   = 0,
    fvar    = 0,
    fbandl  = 0,
    c       = 0,
    m[2]    = {0,0},
    c1      = 0,
    c2      = 0,
    b1      = 0,
    count   = 0,
    gapc    = 0,
    has     = 0,
    denc    = 0,
    maxc    = 0,
    den[]   = {0,0},
    loc[]   = {0,0},
    max[]   = {0,0,0};
    
    double
    cavg    = 0.,
    mavg    = 0.;
    
    utility->QF = 0;
    utility->QT = 0;
    /* Find max and update kalman */
    int range[3] = { l, d->centroid, 0 };
#ifdef RHO_DEBUG
    printf("Map centroid is %d\n", range[1]);
#endif
    int x1 = l, x2 = l;
    
    for( int i = 1, j = 2; i >= 0; i--, j-- )
    {
        for( x1 = range[i]; x1 > range[j]; --x1, c = d->map[x1], b1 = b->map[x1] )
        {
            if( c < d->length/8 )
            {
                utility->QT += c;
                if( c > m[i] ) m[i] = c;
            }
        }
        
        RhoKalman.update(&d->kalmans[i], m[i], 0.);
        d->max[i] = m[i];
        fpeak = d->kalmans[i].value;
        fvar = d->kalmans[i].variance;
        
        if( fvar < fpeak && fvar > 0)
        {
            fbandl = fpeak - fvar;
#ifdef RHO_DEBUG
            printf("Map(%d): max>%d | peak>%d | var>%d | bandl>%d\n", i, m[i], fpeak, fvar, fbandl);
#endif
            /* Find blob centroids and sort out the top 2 */
            for( x2 = range[i]; x2 > range[j]; --x2, c1 = d->map[x2] )
            {
                /* Punish values above the filter peak */
                if(c1 > fpeak) c1 = fpeak - RHO_PUNISH_FACTOR*(c1 - fpeak);
                
                /* CMA value in band */
                if(c1 > fbandl)
                {
                    /* De-offset valid values */
                    c2 = c1 - fbandl;
                    
                    cma_M0_M1((double)c2, x2, &cavg, &mavg, &count);
                    if(c2 > maxc) maxc = c2;
                    has = 1; gapc = 0;
                }
                
                /* Process completed blobs */
                else if(has && gapc > RHO_GAP_MAX)
                {
                    denc = (int)cavg;
                    if( denc > den[0] )
                    {
                        loc[1] = loc[0]; loc[0] = (int)(mavg/cavg);
                        den[1] = den[0]; den[0] = denc;
                        max[2] = max[1]; max[1] = max[0]; max[0] = maxc;
                    }
                    else if( denc > den[1] )
                    {
                        loc[1] = (int)(mavg/cavg);
                        den[1] = denc;
                        max[2] = max[1]; max[1] = maxc;
                    }
                    utility->QF += cavg;
                    mavg = 0; cavg = 0;
                    has = 0; count = 0; gapc = 0;
                }
                
                /* Count gaps for all invalid values */
                else gapc++;
            }
        }
        utility->FT = ((double)utility->QF)/((double)utility->QT);
#ifdef RHO_DEBUG
//        printf("* Filtered coverage is %.5f%%\n", utility->FT*100);
#endif
    }
#ifdef RHO_DEBUG
    printf("Blobs: [0](%d,%d,%d) | [1](%d,%d,%d)\n", loc[0], den[0], max[0], loc[1], den[1], max[1]);
#endif
        if( !loc[0] && !loc[1] ) return;
    
    /* Update prediction with best peaks */
    r->primary_new   = loc[0];
    r->secondary_new = loc[1];
    
    double comp = utility->FT/FILTERED_CONVERAGE_TARGET;
    if(comp > 1)
    {
        double v_ = ZDIV(1.0,fvar);
        r->probabilities.primary   = ((double)den[0]) * v_;
        r->probabilities.secondary = ((double)den[1]) * v_;
        r->probabilities.alternate = ((double)den[2]) * v_;
    }
    else
    {
        r->probabilities.primary   = comp;
        r->probabilities.secondary = comp;
        r->probabilities.alternate = 1 - comp;
    }
    
#ifdef RHO_DEBUG
//    printf("Alternate probability is %.3f\n", r->probabilities.alternate);
#endif
}

void Filter_and_Select_Pairs( rho_c_utility * utility )
{
    Filter_and_Select( utility, &utility->density_map_pair.x, &utility->background_map_pair.x, &utility->prediction_pair.x );
    Filter_and_Select( utility, &utility->density_map_pair.y, &utility->background_map_pair.y, &utility->prediction_pair.y );
}

void Update_Prediction( rho_c_utility * utility )
{
    int Ax = utility->prediction_pair.x.primary_new,
    Ay = utility->prediction_pair.y.primary_new,
    Bx = utility->prediction_pair.x.secondary_new,
    By = utility->prediction_pair.y.secondary_new;
    int Cx = utility->Cx, Cy = utility->Cy;
    
    bool nondiag = false;
    signed char qcheck = ( utility->Q[0] > utility->Q[1] ) + ( utility->Q[2] < utility->Q[3] ) - 1;
    if( ( Ax < Cx ) ^ ( Bx > Cx ) ) /* X ambiguous */
    {
        double x1 = utility->prediction_pair.x.primary.value + utility->prediction_pair.x.primary.velocity;
        double p1 = fabs(x1-Ax), p2 = fabs(x1-Bx);
        if( p1 > p2 ) iswap(&Ax, &Bx);
        nondiag = true;
#ifdef RHO_DEBUG
        printf("X Ambiguity (%d,%d,%d)\n", Ax, Bx, Cx);
#endif
    }
    if( ( Ay < Cy ) ^ ( By > Cy ) ) /* Y ambiguous */
    {
        double y1 = utility->prediction_pair.y.primary.value + utility->prediction_pair.y.primary.velocity;
        double p1 = fabs(y1-Ay), p2 = fabs(y1-By);
        if( p1 > p2 ) iswap(&Ay, &By);
        nondiag = true;
#ifdef RHO_DEBUG
        printf("Y Ambiguity (%d,%d,%d)\n", Ay, By, Cy);
#endif
    }
    
    if ( !nondiag )
    {
        if( Ax > Bx ) iswap(&Ax, &Bx);
        if ( ( qcheck > 0 ) ^ ( Ay < By ) ) iswap(&Ay, &By);
        
#ifdef RHO_DEBUG
        //        if( qcheck < 0 ) printf("Secondary diagonal\n");
        //        if( qcheck > 0 ) printf("Primary diagonal\n");
#endif
    }
    
    RhoKalman.update( &utility->prediction_pair.x.primary,   Ax, 0);
    RhoKalman.update( &utility->prediction_pair.x.secondary, Bx, 0);
    RhoKalman.update( &utility->prediction_pair.y.primary,   Ay, 0);
    RhoKalman.update( &utility->prediction_pair.y.secondary, By, 0);
    
    Cy = (int)((utility->prediction_pair.x.primary.value + utility->prediction_pair.x.secondary.value)) / 2;
    Cx = (int)((utility->prediction_pair.y.primary.value + utility->prediction_pair.y.secondary.value)) / 2;
    if( Cx < 0               ) Cx = 0;
    if( Cy < 0               ) Cy = 0;
    if( Cx > utility->width  ) Cx = utility->width;
    if( Cy > utility->height ) Cy = utility->height;
    utility->Cx = Cx;
    utility->Cy = Cy;
    utility->density_map_pair.x.centroid = Cx;
    utility->density_map_pair.y.centroid = Cy;
}

const struct rho_functions RhoFunctions =
{
    .Init = Init,
    .Generate_Density_Map_Using_Interrupt_Model = Generate_Density_Map_Using_Interrupt_Model,
    .Redistribute_Densities = Redistribute_Densities,
    .Filter_and_Select_Pairs = Filter_and_Select_Pairs,
    .Filter_and_Select = Filter_and_Select,
    .Update_Prediction = Update_Prediction
};

