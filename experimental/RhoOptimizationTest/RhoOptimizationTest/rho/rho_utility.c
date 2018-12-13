//
//  rho_utility.c
//  tau+
//
//  Created by Matthew Fonken on 2/7/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#include "rho_utility.h"
#include "rho_master.h"

#define MAX(A,B)        ((A>B)?A:B)
#define XRNGU(A,MAX)    (A>MAX?1:0) //Check if exceeds range
#define XRNG(A,MIN,MAX) (A<MIN?-1:(A>MAX?1:0)) //Check if exceeds range
#define XTOLU(A,TOL)    (A>TOL?1:0) //Check if exceeds range
#define XTOL(A,TOL)     (A<-TOL?-1:(A>TOL?1:0)) //Check if exceeds range

//#define ALLOW_NEGATIVE_REDISTRIBUTION

#define BOUNDU(X,MAX)    ((X>MAX)?(MAX-1):X)         // Bound in upper range
#define BOUND(X,MIN,MAX) ((X<MIN)?MIN:BOUNDU(X,MAX)) // Bound in upper and lower range

static packet_offset_lookup_t packet_offset_lookup = PACKET_OFFSETS;
static floating_t timestamp(void){struct timeval stamp; gettimeofday(&stamp, NULL); return stamp.tv_sec + stamp.tv_usec/1000000.0;}

static void cma_M0_M1( floating_t v, floating_t i, floating_t *m0, floating_t *m1, floating_t *n )
{
    floating_t n_=1/((floating_t)(++(*n)));
    *m0+=((v-*m0)*n_);
    *m1+=(((v*i)-*m1)*n_);
}
static void iswap( index_t *a, index_t *b ) { index_t t=(*a);*a=*b;*b=t; }

static void printPacket( packet_t * p, int l )
{
    printf("Packet Size - %lubytes\n", sizeof(packet_t));
    for(int i = 0; i < sizeof(packet_t); )
    {
        printf("(%02d)", i);
        for( int j = 0; j < l && i < sizeof(packet_t); j++, i++ )
            printf(" 0x%02x", *(byte_t*)(&((byte_t*)&p->header)[i]));
        printf("\n");
    }
    uint32_t px = *(uint32_t*)p->data;
    floating_t pxf = *(floating_t*)p->data;
    uint8_t * ptr = (uint8_t*)&px;
    
    uint8_t pxr[4] = {ptr[3],ptr[2],ptr[1],ptr[0]};
    floating_t pxfr = *(floating_t*)&pxr;
    printf("{%02x}{%02x}{%02x}{%02x} %f:%f\n",ptr[0],ptr[1],ptr[2],ptr[3],pxf,pxfr);
}

#ifdef USE_INTERRUPT_MODEL
/* Universal Port for interrupt model */
pixel_base_t test_port = 0;
#endif

/* Quadrant density redistribution lookup table */
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

/* Generic centroid and mass calculator */
static floating_t CalculateCentroid( density_t * map, index_t l, index_t * C, register density_t thresh )
{
    floating_t avg = 0, mavg = 0, cnt = 0, tot = 0;
    for( index_t i = 0; i < l; i++ )
    {
        density_t c = map[i];
        if( c > thresh )
        {
            cma_M0_M1((floating_t)c, (floating_t)i, &avg, &mavg, &cnt);
            tot += c;
        }
    }
    *C = (index_t)(mavg/avg);
    return tot;
}


void Init( rho_utility * utility )
{
    /* Utility frame */
    index_t w = utility->Width;
    index_t h = utility->Height;
    
    /* Threshold Filter */
    RhoKalman.init(&utility->ThreshFilter, 0, RHO_THRESH_LS, RHO_THRESH_VU, RHO_THRESH_BU, RHO_THRESH_SU );
    
    /* Coverage Filter */
    utility->TargetCoverageFactor  = (floating_t)FILTERED_COVERAGE_TARGET;
    RhoKalman.init(&utility->TargetFilter, utility->TargetCoverageFactor, RHO_TARGET_LS, RHO_TARGET_VU, RHO_TARGET_BU, RHO_TARGET_SU );
    
    /* Density Filters */
    utility->DensityMapPair.x.map = (density_t*)malloc(sizeof(density_t)*h);
    utility->DensityMapPair.x.length = h;
    utility->DensityMapPair.x.max[0] = 0;
    utility->DensityMapPair.x.max[1] = 0;
    RhoKalman.init(&utility->DensityMapPair.x.kalmans[0], 0, RHO_DEFAULT_LS, RHO_DEFAULT_VU, RHO_DEFAULT_BU, RHO_DEFAULT_SU);
    RhoKalman.init(&utility->DensityMapPair.x.kalmans[1], 0, RHO_DEFAULT_LS, RHO_DEFAULT_VU, RHO_DEFAULT_BU, RHO_DEFAULT_SU);
    
    utility->DensityMapPair.y.map = (density_t*)malloc(sizeof(density_t)*w);
    utility->DensityMapPair.y.length = w;
    utility->DensityMapPair.y.max[0] = 0;
    utility->DensityMapPair.y.max[1] = 0;
    RhoKalman.init(&utility->DensityMapPair.y.kalmans[0], 0, RHO_DEFAULT_LS, RHO_DEFAULT_VU, RHO_DEFAULT_BU, RHO_DEFAULT_SU);
    RhoKalman.init(&utility->DensityMapPair.y.kalmans[1], 0, RHO_DEFAULT_LS, RHO_DEFAULT_VU, RHO_DEFAULT_BU, RHO_DEFAULT_SU);
    
    utility->DensityMapPair.x.background = (density_t*)malloc(sizeof(density_t)*h);
    utility->DensityMapPair.y.background = (density_t*)malloc(sizeof(density_t)*w);
    utility->DensityMapPair.x.filtered   = (density_t*)malloc(sizeof(density_t)*h);
    utility->DensityMapPair.y.filtered   = (density_t*)malloc(sizeof(density_t)*w);
    
    /* Prediction Filters */
    RhoKalman.init(&utility->PredictionPair.x.primary,   0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    RhoKalman.init(&utility->PredictionPair.x.secondary, 0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    RhoKalman.init(&utility->PredictionPair.y.primary,   0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    RhoKalman.init(&utility->PredictionPair.y.secondary, 0., RHO_PREDICTION_LS, RHO_PREDICTION_VU, RHO_PREDICTION_BU, RHO_PREDICTION_SU);
    utility->PredictionPair.x.primary_new   = w/2;
    utility->PredictionPair.x.secondary_new = w/2;
    utility->PredictionPair.y.primary_new   = h/2;
    utility->PredictionPair.y.secondary_new = h/2;
    
    /* Prediction probabilities */
    memset(&utility->PredictionPair.x.probabilities, 0, sizeof(floating_t)*4);
    memset(&utility->PredictionPair.y.probabilities, 0, sizeof(floating_t)*4);
    
    utility->Packet.header.ID       = PACKET_HEADER_ID;
    utility->Packet.header.includes = PACKET_INCLUDES;
    memset(utility->Packet.data, 0, sizeof(packet_offset_lookup_t));
    
    utility->BackgroundCounter = 0;
    utility->BackgroundPeriod = BACKGROUND_PERIOD;
}

void Perform( rho_utility * utility, bool background_event )
{
    if(background_event)
        RhoFunctions.Generate_Background( utility );
    else
    {
        //        printf("Rho: Redistributing densities.\n");
        RhoFunctions.Redistribute_Densities( utility );
        //        printf("Rho: Filtering and selecting pairs.\n");
        RhoFunctions.Filter_and_Select_Pairs( utility );
        //        printf("Rho: Updating predictions.\n");
        RhoFunctions.Update_Prediction( utility );
        //        printf("Rho: Updating threshold.\n");
        RhoFunctions.Update_Threshold( utility );
        //        printf("Rho: Generating packets.\n");
        RhoFunctions.Generate_Packet( utility );
    }
}

/* Calculate and process data in variance band from density filter to generate predictions */
void Filter_and_Select( rho_utility * utility, density_map_t * d, prediction_t * r )
{
    index_t
    len = 0,
    cloc = 0,
    gapc = 0;
    density_t
    fpeak = 0,
    fbandl = 0,
    c1 = 0,
    c2 = 0,
    b = 0,
    p = 0;
    variance_t
    fvar = 0;
    density_2d_t
    cmax = 0,
    amax = 0,
    cden = 0,
    tden = 0,
    fden = 0;
    bool
    has = 0,
    sel = 0;
    floating_t
    avgc = 0,
    fcov = 0,   /* Filtered coverage ratio */
    cavg = 0,   /* cumulative average */
    mavg = 0,   /* moment average */
    afac = 0,   /* alternate factor */
    bfac = 0,   /* absence factor */
    pfac = 0,   /* primary factor */
    sfac = 0,   /* secondary factor */
    cfac = 0,   /* coverage factor */
    vfac = 0,   /* variance factor */
    fdn_ = 0,   /* filtered density (float) */
    tdnf = 0,   /* target density (float) */
    fvf_ = 0;   /* filtered variance inverse (float) */
    blob_t
    blobs[2] = {0};
    
    memset(&r->probabilities, 0, sizeof(floating_t)*4);
    memset(&r->probabilities, 0, sizeof(floating_t)*4);
    
    rho_selection_variables _ = {d->length, 0};
    
    utility->FilteredCoverage = 0;
    utility->TotalCoverage = 0;
    
    /* Find max and update kalman */
    byte_t cyc, cyc_;
    index_t x1 = len,
    x2 = len,
    range[3] = { len, d->centroid, 0 };
    //    LOG_RHO("Range is <%d | %d | %d>\n", range[2], range[1], range[0]);
    
    for( cyc = 1, cyc_ = 2; cyc_ > 0; cyc--, cyc_-- )
    {
        cmax = 0;
        if( d->has_background )
        {
            for( x1 = range[cyc]; x1 > range[cyc_]; --x1, c1 = d->map[x1], b = d->background[x1] )
            {
                c1 = abs( (int)c1 - (int)b );
                if( c1 < (d->length>>2) )
                {
                    tden += c1;
                    if( c1 > cmax ) cmax = c1;
                    d->filtered[x1] = c1;
                }
                else
                    d->filtered[x1] = 0;
            }
        }
        else
        {
            for( x1 = range[cyc]; x1 > range[cyc_]; --x1, c1 = d->map[x1] )
            {
                if( c1 < (d->length>>2) )
                {
                    tden += c1;
                    if( c1 > cmax ) cmax = c1;
                    d->map[x1] = c1;
                }
                else
                    d->map[x1] = 0;
            }
        }
        
        RhoKalman.update(&d->kalmans[cyc], cmax, 0. );
        d->max[cyc] = cmax;
        fpeak = d->kalmans[cyc].value;
        fvar = RHO_VARIANCE( d->kalmans[cyc].K[0] );
        d->kalmans[cyc].variance = fvar;
        
        LOG_RHO("Map(%d): max>%d\n", cyc, cmax);
        
        if( fvar > 0 && fpeak > fvar )
        {
            fbandl = fpeak - fvar;
            LOG_RHO("Peak>%d | var>%d | bandl>%d\n", fpeak, fvar, fbandl);
            /* Find blob centroids and sort out the top 2 */
            for( x2 = range[cyc]; x2 > range[cyc_]; --x2, c1 = d->map[x2] )
            {
                /* Punish values above the filter peak */
                if( c1 > fpeak )
                {
                    p = RHO_PUNISH_FACTOR*(c1 - fpeak);
                    if( fpeak > p ) c1 = fpeak - p;
                    else c1 = 0;
                }
                
                /* Check if CMA value is in band */
                if( c1 > fbandl )
                {
                    /* De-offset valid values */
                    c2 = c1 - fbandl;
                    
                    /* Process new values into blob */
                    cma_M0_M1((floating_t)c2, (floating_t)x2, &cavg, &mavg, &avgc);
                    if(c2 > cmax) cmax = c2;
                    has = 1; gapc = 0;
                }
                
                /* Process completed blobs */
                else if( has && gapc > RHO_GAP_MAX )
                {
                    cden = (density_2d_t)cavg;
                    if( cden > blobs[!sel].den )
                    {
                        if( ( cden > blobs[sel].den ) || ( !blobs[!sel].den ) )
                        {
                            sel = !sel;
                            amax = blobs[sel].max;
                        }
                        blobs[sel] = (blob_t){ cmax, cden, (index_t)ZDIV(mavg,cavg) };
                    }
                    fden += cden;
                    mavg = 0.; cavg = 0.; avgc = 0.;
                    has = 0; gapc = 0;
                }
                
                /* Count gaps for all invalid values */
                else if( has )
                    gapc++;
            }
        }
    }
    
    //    if( !blobs[0].loc || !blobs[1].loc ) return;
    
    /* Update prediction with best peaks */
    r->primary_new   = blobs[ sel].loc;
    r->secondary_new = blobs[!sel].loc;
    
    /* Generate prediction probabilities */
    fdn_ = ZDIV(     1, fden);              // filtered density inverse
    
    pfac = blobs[ sel].den * fdn_;
    sfac = blobs[!sel].den * fdn_;
    
    floating_t n =  pfac + sfac;
    afac = pow( 1 - n, 1);
    n += afac;
    bfac = pow( 1 - n, 1);
    n += bfac;
    n = ZDIV( 1., n );
    
    fcov = BOUND(ZDIV(fden, tden), 0, 2); // filtered coverage
    cfac = 1. - BOUND(ZDIV( fcov, utility->TargetCoverageFactor ), 0, 2); // coverage factor
    vfac = ZDIV(fvar, fpeak); // variance factor
    
    r->probabilities.primary        = pfac * n;
    r->probabilities.secondary      = sfac * n;
    r->probabilities.alternate      = afac * n;
    r->probabilities.absence        = bfac * n;
    
    utility->FilteredCoverage      = fden;
    utility->TotalCoverage         = tden;
    utility->FilteredPercentage    = fcov;
    utility->CoverageFactor        = cfac;
    utility->VarianceFactor        = vfac;
    
    LOG_RHO("%.3f[cf] %.3f[vf] %.3f%%[fc] %.3f%%[tc] | %.3f[tf]\n", cfac, vfac, fcov*100, utility->target_coverage_factor*100, fdn_*tdnf );
    LOG_RHO("Rho: pri-%.3f sec-%.3f alt-%.3f abs-%.3f\n", r->probabilities.primary, r->probabilities.secondary, r->probabilities.alternate, r->probabilities.absence);
    LOG_RHO("* %.3f%% ( %d / %d )\n", fcov*100, fden, tden);
    LOG_RHO("Blobs: [0](%d,%d,%d) | [1](%d,%d,%d)\n", blobs[0].loc, blobs[0].den, blobs[0].max, blobs[1].loc, blobs[1].den, blobs[1].max);
    LOG_RHO("Normalized total probability: %.3f\n", r->probabilities.primary + r->probabilities.secondary + r->probabilities.alternate + r->probabilities.absence );
}

void Generate_Background( rho_utility * utility )
{
    floating_t xt = CalculateCentroid( utility->DensityMapPair.x.background, utility->DensityMapPair.x.length, &utility->Bx, BACKGROUND_CENTROID_CALC_THRESH );
    floating_t yt = CalculateCentroid( utility->DensityMapPair.y.background, utility->DensityMapPair.y.length, &utility->By, BACKGROUND_CENTROID_CALC_THRESH );
    LOG_RHO("^^^Total X density is %.2f & Total Y density is %.2f^^^\n", xt, yt);
    utility->QbT = MAX(xt, yt);
}

static void Redistribute_Densities( rho_utility * utility )
{
    redistribution_variables _ =
    {
        { utility->Bx, abs(utility->Cx-utility->Bx), utility->Width - utility->Cx  },
        { utility->By, abs(utility->Cy-utility->By), utility->Height - utility->Cy },
        { 0 }, 0
    };
    if( utility->Cx < utility->Bx )
    {
        _.xl[0] = utility->Cx;
        _.xl[2] = utility->Width - utility->Bx;
        _.c |= 0x01;
    }
    if( utility->Cy < utility->By )
    {
        _.yl[0] = utility->Cy;
        _.yl[2] = utility->Width - utility->By;
        _.c |= 0x02;
    }
    while( _.y < 3 )
        for( _.x = 0; _.x < 3; )
            _.area[_.p++] = _.xl[_.x++]* _.yl[_.y++];
    for( ; _.q < 4; _.q++ )
    {
        _.l  = rlookup.config[_.c].length[    _.q];
        _.l_ = rlookup.config[_.c].length[3 - _.q];
        for( _.x = 0, _.b = 0; _.x < _.l; _.x++ )
        {
            _.a = _.area[rlookup.config[_.c].current[_.q][_.x]];
            for( _.y = 0; _.y < _.l_; _.y++ )
                _.b += _.area[rlookup.config[_.c].background[rlookup.config[_.c].factor[_.q][_.x]][_.y]];
            _.d += ZDIV( _.a, _.b ) * utility->Qb[_.q];
        }
#ifndef ALLOW_NEGATIVE_REDISTRIBUTION
        if( _.d > utility->Q[_.q] ) utility->Qf[_.q] = 0;
        else
#endif
            utility->Qf[_.q] = utility->Q[_.q] - _.d;
    }
}

void Filter_and_Select_Pairs( rho_utility * utility )
{
    LOG_RHO("X Map:\n");
    Filter_and_Select( utility, &utility->DensityMapPair.x, &utility->PredictionPair.x );
    LOG_RHO("Y Map:\n");
    Filter_and_Select( utility, &utility->DensityMapPair.y, &utility->PredictionPair.y );
}

/* Correct and factor predictions from variance band filtering into global model */
void Update_Prediction( rho_utility * utility )
{
    prediction_update_variables _ =
    {
        utility->PredictionPair.y.primary_new,
        utility->PredictionPair.x.primary_new,
        utility->PredictionPair.y.secondary_new,
        utility->PredictionPair.x.secondary_new,
        utility->Cx,
        utility->Cy,
        0
    };
    if(_.Ax > _.Bx) iswap(&_.Ax, &_.Bx);
    if(_.Ay > _.By) iswap(&_.Ay, &_.By);
    
    if( ( _.Ax < _.Cx ) ^ ( _.Bx > _.Cx ) ) /* X ambiguous */
    {
        _.x1 = utility->PredictionPair.x.primary.value + utility->PredictionPair.x.primary.velocity;
        if( fabs( _.x1 - _.Ax ) > fabs( _.x1 - _.Bx ) ) iswap( &_.Ax, &_.Bx );
        _.non_diag = true;
        LOG_RHO("X Ambiguous (%d < %d > %d)\n", _.Ax, _.Cx, _.Bx);
    }
    if( ( _.Ay < _.Cy ) ^ ( _.By > _.Cy ) ) /* Y ambiguous */
    {
        _.y1 = utility->PredictionPair.y.primary.value + utility->PredictionPair.y.primary.velocity;
        if( fabs( _.y1 - _.Ay ) > fabs( _.y1 -_. By ) ) iswap( &_.Ay, &_.By );
        _.non_diag = true;
        LOG_RHO("Y Ambiguous (%d < %d > %d)\n", _.Ay, _.Cy, _.By);
    }
    if ( !_.non_diag )
    {
        _.qcheck = ( utility->Qf[0] > utility->Qf[1] ) + ( utility->Qf[2] < utility->Qf[3] ) - 1;
        if( ( _.Ax > _.Bx ) ^ ( ( _.qcheck > 0 ) ^ ( _.Ay < _.By ) ) ) iswap(&_.Ax, &_.Bx);
        LOG_RHO("Quadrant Check %d\n", _.qcheck);
    }
    
    if( _.Ax ) RhoKalman.update( &utility->PredictionPair.x.primary,   _.Ax, 0 );
    if( _.Bx ) RhoKalman.update( &utility->PredictionPair.x.secondary, _.Bx, 0 );
    if( _.Ay ) RhoKalman.update( &utility->PredictionPair.y.primary,   _.Ay, 0 );
    if( _.By ) RhoKalman.update( &utility->PredictionPair.y.secondary, _.By, 0 );
    
    _.Cx = (index_t)((utility->PredictionPair.x.primary.value + utility->PredictionPair.x.secondary.value)) >> 1;
    _.Cy = (index_t)((utility->PredictionPair.y.primary.value + utility->PredictionPair.y.secondary.value)) >> 1;
    
    _.Cx = BOUNDU(_.Cx, utility->Width );
    _.Cy = BOUNDU(_.Cy, utility->Height);
    
    utility->Cx = _.Cx;
    utility->Cy = _.Cy;
    LOG_RHO("Cx>%d | Cy>%d\n", _.Cx, _.Cy);
    utility->DensityMapPair.x.centroid = _.Cy;
    utility->DensityMapPair.y.centroid = _.Cx;
    
    utility->PredictionPair.probabilities.primary   = sqrt( utility->PredictionPair.x.probabilities.primary   * utility->PredictionPair.y.probabilities.primary   );
    utility->PredictionPair.probabilities.secondary = sqrt( utility->PredictionPair.x.probabilities.secondary * utility->PredictionPair.y.probabilities.secondary );
    utility->PredictionPair.probabilities.alternate = sqrt( utility->PredictionPair.x.probabilities.alternate * utility->PredictionPair.y.probabilities.alternate );
    
    BayesianFunctions.sys.update( &utility->BayeSys, &utility->PredictionPair );
}

/* Use background and state information to update image threshold */
void Update_Threshold( rho_utility * utility )
{
    /* Hard-Tune on significant background */
    floating_t  hard_tune_factor = 0.;
    if( utility->QbT > BACKGROUND_COVERAGE_MIN )
    {
        floating_t background_coverage_factor = 1 - ZDIV( BACKGROUND_COVERAGE_MIN, utility->QbT );
        hard_tune_factor = THRESH_STEP_MAX*pow( BOUND(background_coverage_factor, -1, 1), 3);
        hard_tune_factor *= HARD_TUNING_PRESIDENCE*utility->CoverageFactor;
    }

    /* Soft-Tune on State */
    floating_t soft_tune_factor = SOFT_TUNING_PRESIDENCE*THRESH_STEP_BASE;
    switch(utility->BayeSys.state)
    {
        case UNSTABLE_NONE:
            soft_tune_factor *= 2;
        case UNSTABLE_SINGLE:
            soft_tune_factor *= utility->VarianceFactor;
            break;
        case STABLE_NONE:
            soft_tune_factor *= 2;
         case STABLE_SINGLE:
            soft_tune_factor *= utility->CoverageFactor;
            break;
        case STABLE_DOUBLE:
            RhoKalman.update( &utility->TargetFilter, utility->FilteredPercentage, 0. );
            utility->TargetCoverageFactor = utility->TargetFilter.value;
            LOG_RHO("*** COVERAGE TARGET IS %.3f ***\n", utility->target_coverage_factor);
            soft_tune_factor = 0.;
            break;
        case UNSTABLE_MANY:
            soft_tune_factor *= -utility->VarianceFactor;
            break;
        case STABLE_MANY:
            soft_tune_factor *= -utility->CoverageFactor;
            break;
        default:
            break;
    }
    
    utility->TargetCoverageFactor -= 0.01*(utility->TargetCoverageFactor - (floating_t)FILTERED_COVERAGE_TARGET);
    floating_t proposed_thresh = *utility->Thresh + hard_tune_factor + soft_tune_factor;
    RhoKalman.update( &utility->ThreshFilter, proposed_thresh, 0);
    *utility->Thresh = BOUND(utility->ThreshFilter.value, THRESH_MIN, THRESH_MAX);
    
    LOG_RHO("*** THRESH IS %d ***\n", utility->thresh);
    LOG_RHO("Hard factor is %.3f & soft factor is %.3f [c%.3f|v%.3f]\n", hard_tune_factor, soft_tune_factor, utility->coverage_factor, utility->variance_factor);
    LOG_RHO("Background coverage compare: Actual>%dpx vs. Target>%d±%dpx\n", utility->QbT, BACKGROUND_COVERAGE_MIN, BACKGROUND_COVERAGE_TOL_PX);
}

void Generate_Packet( rho_utility * utility )
{
    packet_value_lookup_t  packet_value_lookup  = PACKET_ADDRESS_INITIALIZER(utility->PredictionPair);
    packet_generation_variables _ =
    {
        &utility->Packet,
        (address_t)&utility->Packet.data,
        (address_t)&packet_offset_lookup,
        (address_t*)&packet_value_lookup,
        0
    };
    _.packet->header.timestamp = timestamp();
    while( _.i++ < NUM_PACKET_ELEMENTS )
    {
        if( _.packet->header.includes & 0x01 )
        {
            if(!_.t) _.l = (*(packing_template_t*)_.llPtr).a;
            else          _.l = (*(packing_template_t*)_.llPtr).b;
            for( _.j = 0; _.j < _.l; _.j++)
                ((byte_t*)_.pdPtr)[_.j] = *(((byte_t*)*_.alPtr)+_.j);
            _.pdPtr += _.l;
        }
        _.alPtr++;
        _.includes >>= 1;
        if((_.t=!_.t )) _.llPtr++;
    }
    printPacket( &utility->Packet, 3    );
}

/* Rho global functions */
const struct rho_functions RhoFunctions =
{
    .Init = Init,
    .Perform = Perform,
    .Generate_Background = Generate_Background,
    .Redistribute_Densities = Redistribute_Densities,
    .Filter_and_Select_Pairs = Filter_and_Select_Pairs,
    .Filter_and_Select = Filter_and_Select,
    .Update_Prediction = Update_Prediction,
    .Update_Threshold = Update_Threshold,
    .Generate_Packet = Generate_Packet
};
