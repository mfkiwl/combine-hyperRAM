//
//  rho_utility.c
//  Created by Matthew Fonken on 2/7/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#include "rho_utility.h"

void CumulateMomentsRhoUtility( floating_t v, floating_t i, floating_t *m0, floating_t *m1, floating_t *n )
{
    floating_t n_=1/((floating_t)(++(*n)));
    *m0+=((v-*m0)*n_);
    *m1+=(((v*i)-*m1)*n_);
}

void CalculateBlobScoreRhoUtility( blob_t *b, density_t total_density, byte_t peak )
{
    floating_t
    delta_d = ( (floating_t)b->den / (floating_t)total_density) - 0.5,
    delta_p = (floating_t)peak / (floating_t)b->max;
    b->scr = BLOB_SCORE_FACTOR*( ( delta_d * delta_d ) + ( delta_p * delta_p ) );
}

#ifdef USE_INTERRUPT_MODEL
/* Universal Port for interrupt model */
pixel_base_t test_port = 0;
#endif

/* Quadrant density redistribution lookup table */
const density_redistribution_lookup_t rlookup =
{
    {
        { // Case #1
            { { 0, 1, 3, 4 }, { 2, 5 }, { 6, 7 }, { 8 } },
            { { 0 }, { 1, 2 }, { 3, 6 }, { 4, 5, 7, 8 } },
            { { 0, 1, 2, 3 }, { 1, 3 }, { 2, 3 }, { 3 } },
            { 4, 2, 2, 1 }
        },
        { // Case #2
            { { 0, 3 }, { 1, 2, 4, 5 }, { 6 }, { 7, 8 } },
            { { 0, 1 }, { 2 }, { 3, 4, 6, 7 }, { 5, 8 } },
            { { 0, 2 }, { 0, 1, 2, 3 }, { 2 }, { 2, 3 } },
            { 2, 4, 1, 2 }
        },
        { // Case #3
            { { 0, 1 }, { 2 }, { 3, 4, 6, 7 }, { 5, 8 } },
            { { 0, 3 }, { 1, 2, 4, 5 }, { 6 }, { 7, 8 } },
            { { 0, 1 }, { 1 }, { 0, 1, 2, 3 }, { 1, 3 } },
            { 2, 1, 4, 2 }
        },
        { // Case #4
            { { 0 }, { 1, 2 }, { 3, 6 }, { 4, 5, 7, 8 } },
            { { 0, 1, 3, 4 }, { 2, 5 }, { 6, 7 }, { 8 } },
            { { 0 }, { 0, 1 }, { 0, 2 }, { 0, 1, 2, 3 } },
            { 1, 2, 2, 4 }
        }
    }
};

/* Generic centroid and mass calculator */
floating_t CalculateCentroidRhoUtility( density_t * map, index_t l, index_t * C, /*register*/ density_t thresh )
{
    floating_t avg = 0, mavg = 0, cnt = 0, tot = 0;
    for( index_t i = 0; i < l; i++ )
    {
        density_t c = map[i];
        if( c > thresh )
        {
            RhoUtility.CumulateMoments((floating_t)c, (floating_t)i, &avg, &mavg, &cnt);
            tot += c;
        }
    }
    *C = (index_t)(mavg/avg);
    return tot;
}

void PrintPacketRhoUtility( packet_t * p, index_t l )
{
#ifdef PACKET_DEBUG
    LOG_PACKET(DEBUG_0,"Packet Size - %lubytes\n", sizeof(packet_t));
    for(int i = 0; i < sizeof(packet_t); )
    {
        LOG_PACKET(DEBUG_0,"(%02d)", i);
        for( int j = 0; j < l && i < sizeof(packet_t); j++, i++ )
            LOG_PACKET(DEBUG_0," 0x%02x", *(byte_t*)(&((byte_t*)&p->header)[i]));
        LOG_PACKET(DEBUG_0,"\n");
    }
    uint32_t px = *(uint32_t*)p->data;
    floating_t pxf = *(floating_t*)p->data;
    uint8_t * ptr = (uint8_t*)&px;
    
    uint8_t pxr[4] = {ptr[3],ptr[2],ptr[1],ptr[0]};
    floating_t pxfr = *(floating_t*)&pxr;
    LOG_PACKET(DEBUG_0,"{%02x}{%02x}{%02x}{%02x} %f:%f\n",ptr[0],ptr[1],ptr[2],ptr[3],pxf,pxfr);
#endif
}

void InitializeDataRhoUtility( rho_core_t * core, index_t width, index_t height )
{
    /* Reset entire structure */
    memset(core, 0, sizeof(rho_core_t));
    
    /* Core frame */
    core->Width = width;
    core->Height = height;
    
    /* Centroid */
    core->Cx   = width/2;
    core->Cy   = height/2;
    core->Px   = width/2;
    core->Py   = height/2;
    core->Sx   = width/2;
    core->Sy   = height/2;
    
    core->TargetCoverageFactor = FILTERED_COVERAGE_TARGET;
    
    /* Packet */
    core->Packet.header.ID       = PACKET_HEADER_ID;
    core->Packet.header.includes = PACKET_INCLUDES;
    memset(core->Packet.data, 0, sizeof(packet_offset_lookup_t));
    
    /* Background */
    core->BackgroundCounter = 0;
    core->BackgroundPeriod = BACKGROUNDING_PERIOD;
    
    core->Thresh = (double)(MAX_THRESH - MIN_THRESH) / 2.;
    core->ThreshByte = (byte_t)core->Thresh;
}

void InitializeFiltersRhoUtility( rho_core_t * core )
{
    /* Threshold Filter */
    RhoPID.Initialize(&core->ThreshFilter, DEFAULT_PID_GAIN );
    
    /* Coverage Filter */
    core->TargetCoverageFactor  = (floating_t)FILTERED_COVERAGE_TARGET;
    RhoKalman.Initialize(&core->TargetFilter, core->TargetCoverageFactor, RHO_TARGET_LS, 0, 1, DEFAULT_TARGET_UNCERTAINTY );
}

void InitializePredictionRhoUtility( prediction_t * r, index_t l )
{
    /* Prediction probabilities */
    memset(&r->Probabilities, 0, sizeof(floating_t)*4);
    for(uint8_t i = 0; i < MAX_TRACKING_FILTERS; i++)
    {
        RhoKalman.Initialize( &r->TrackingFilters[i], 0., RHO_PREDICTION_LS, 0, l, DEFAULT_PREDICTION_UNCERTAINTY );
        r->TrackingFiltersOrder[i] = i;
    }
    /* Blobs */
    for(uint8_t i = 0; i < MAX_BLOBS; i++)
    {
        memset(&r->Blobs[i], 0, sizeof(blob_t));
        r->BlobsOrder[i] = i;
    }
}

void InitializeDensityMapRhoUtility( density_map_t * dmap, index_t len, index_t centroid )
{
    size_t size = sizeof(density_t)*len;
    dmap->map = (density_t*)malloc(size);
    dmap->background = (density_t*)malloc(size);
    dmap->filtered = (density_t*)malloc(size);
    memset(dmap->map, 0, size);
    memset(dmap->background, 0, size);
    memset(dmap->filtered, 0, size);
    dmap->length = len;
    dmap->max[0] = 0;
    dmap->max[1] = 0;
    dmap->centroid = centroid;
    RhoKalman.Initialize( &dmap->kalmans[0], 0, RHO_DEFAULT_LS, 0, len, DEFAULT_KALMAN_UNCERTAINTY );
    RhoKalman.Initialize( &dmap->kalmans[1], 0, RHO_DEFAULT_LS, 0, len, DEFAULT_KALMAN_UNCERTAINTY );
}

void ResetForDetectRhoUtility( rho_detection_variables *_, density_map_t * d, prediction_t * r )
{
    memset(_, 0, sizeof(rho_detection_variables));
    
    _->len = d->length;
    _->range[0] = d->length;
    _->range[1] = d->centroid;
    _->range[2] = 0;
    
    memset( &r->Probabilities, 0, sizeof(floating_t)*NUM_STATES );
    memset( &r->Probabilities, 0, sizeof(floating_t)*NUM_STATES );

    r->NuBlobs = 0;
    r->TotalDensity = 0;
    r->NumBlobs = 0;
    
    index_t i;
    for( i = 0; i < MAX_BLOBS; i++ )
    {
        memset(&r->Blobs[i], 0, sizeof(blob_t));
        r->BlobsOrder[i] = i;
    }
    for( i = 0; i < MAX_TRACKING_FILTERS; i++ )
    {
        r->TrackingFiltersOrder[i] = i;
    }
}

void PerformDetectRhoUtility( rho_detection_variables *_, density_map_t * d, prediction_t * r )
{
    DUAL_FILTER_CYCLE(_->cyc)
    {
        _->cmax = 0;
        _->start = _->range[_->cyc];
        _->end = _->range[_->cyc_];
        
        RhoUtility.Predict.PeakFilter( _, d, r );
        if( RhoUtility.Detect.LowerBound( _ ) )
        {
            do
            {
                RhoUtility.Detect.Blobs( _, d, r );
                RhoUtility.Detect.CalculateChaos( _, r );
                RhoUtility.Detect.ScoreBlobs( _, d, r );
            } while( _->rcal && ++_->rcal_c < MAX_RHO_RECALCULATION_LEVEL );
            
            RhoUtility.Detect.SortBlobs( _, r );
        }
        
        r->PreviousPeak[_->cyc] = BOUND(_->cmax, 0, _->len);
        r->PreviousDensity[_->cyc] = _->fden;
        d->max[_->cyc] = _->cmax;
    }
}

void PredictPeakFilterRhoUtility( rho_detection_variables *_, density_map_t * d, prediction_t * r )
{
    _->fpeak = (index_t)RhoKalman.Step(&d->kalmans[_->cyc], r->PreviousPeak[_->cyc], d->kalmans[_->cyc].velocity );
    _->fpeak_2 = _->fpeak << 1;
    _->fvar = BOUND((index_t)RHO_VARIANCE( d->kalmans[_->cyc].K[0] ), MIN_VARIANCE, MAX_VARIANCE);
    d->kalmans[_->cyc].variance = _->fvar;
}

inline bool CalculateBandLowerBoundRhoUtility( rho_detection_variables *_ )
{
    if( _->fvar > 0 )// && (_->fpeak == 0 || _->fpeak > _->fvar ))
    {
        if(_->fpeak > _->fvar)
            _->fbandl = _->fpeak - _->fvar;
        else
            _->fbandl = 0;
        return true;
    }
    return false;
}

inline void DetectBlobsRhoUtility( rho_detection_variables *_, density_map_t * d, prediction_t * r )
{ /* Detect blobs - START */
    _->tden = 0;
    _->fden = 0;
    BOUNDED_CYCLE_DUAL(_->x, _->start, _->end, _->c1, d->map, _->b, d->background)
    {
        RhoUtility.Detect.SubtractBackground( _, d );
        RhoUtility.Detect.Blob( _, d, r );
    }
} /* Detect blobs - END */

inline void SubtractBackgroundForDetectionRhoUtility( rho_detection_variables *_, density_map_t * d )
{
    if( _->c1 > _->b )
    {
        _->tden += _->c1;
        
        // Subtract background
        _->c1 -= _->b;
        
        if( _->c1 > _->cmax )
            _->cmax = _->c1;
        
        /* Punish values above the filter peak */
        if( ( _->c1 > _->fpeak )
           && ( _->fpeak_2 > _->c1 ) )
            _->c1 = _->fpeak_2 - _->c1;
    }
    else
        _->c1 = 0;
}

inline void DetectBlobRhoUtility( rho_detection_variables *_, density_map_t * d, prediction_t * r )
{
    /* Check if CMA value is in band */
    if( _->c1 > _->fbandl )
    {
        /* De-offset valid values */
        _->c2 = _->c1 - _->fbandl;
        
        /* Process new values into blob */
        RhoUtility.CumulateMoments((floating_t)_->c2, (floating_t)_->x, &_->cavg, &_->mavg, &_->avgc);
        
        /* Update max */
        if(_->c2 > _->cmax) _->cmax = _->c2;
        
        /* Increment width */
        _->width++;
        
        /* Reset flag and counter */
        _->has = 1; _->gapc = 0;
    }
    
    /* Process completed blobs and increment count */
    else if( ++_->gapc > RHO_GAP_MAX && _->has )
    {
        /* Get latest blob centroid */
        _->cden = (density_2d_t)_->cavg;
        _->fden += _->cden;
        
        /* Check if new blob is dense enough to be saved */
        if( _->cden > MIN_BLOB_DENSITY)
        {
            /* Create new blob at secondary */
            index_t loc = (index_t)ZDIV(_->mavg,_->cavg);
            r->Blobs[_->blbf] = (blob_t){ d->map[loc], _->cden, loc, _->width };
            r->BlobsOrder[_->blbf] = _->blbf;
            _->blbf++;
        }
        
        /* Reset variables */
        _->mavg = 0.; _->cavg = 0.; _->avgc = 0.;
        _->has = 0; _->gapc = 0;
    }
    
    else if (!_->has)
    {
        /* Reset width */
        _->width = 0;
    }
}

void CalculateDetectionChaosRhoUtility( rho_detection_variables *_, prediction_t * r )
{
    _->chaos = (floating_t)r->PreviousDensity[_->cyc] / (floating_t)_->fden;
    /* Assume no recalculations are needed */
    _->rcal = false;
}

void ScoreBlobsRhoUtility( rho_detection_variables *_, density_map_t * d, prediction_t * r )
{
    /* Return on empty frames */
    if(_->fden > 0 )
    {
        /* Cycle blobs */
        for(uint8_t i = 0; i < _->blbf; i++)
        {
            /* Get blob at index from order array and check validity */
            uint8_t j = r->BlobsOrder[i];
            if(j >= MAX_BLOBS) continue;
            blob_t * curr = &r->Blobs[j];
            
            /* Score current blob */
            RhoUtility.CalculateBlobScore(curr, _->fden, _->cmax);
            
            /* Recalculate blobs with chaos */
            if(curr->scr > _->chaos)
            {
                /* Recalculate around chaotic blob */
                _->rcal = true;
                
                /* Remove this index */
                r->BlobsOrder[i] = MAX_BLOBS;
                
                /* Get centroid peak and update filter double peak */
                sdensity_t cpeak = (sdensity_t)d->map[curr->loc];
                _->fpeak_2 = cpeak << 1;
                
                /* Raise lower band half of blob centroid to band center when below */
                if( cpeak < _->fpeak)
                    _->fbandl += abs( (sdensity_t)_->fpeak - cpeak) >> 1;
                
                /* Otherwise raise to centroid peak */
                else _->fbandl = cpeak;
                
                /* Recalculate _->cycle width */
                index_t w_2 = curr->wth >> 1;
                if(curr->loc - w_2 > _->range[_->cyc_])
                    _->end = curr->loc - w_2;
                else _->end = _->range[_->cyc_];
                if(curr->loc + w_2 < _->range[_->cyc])
                    _->start = curr->loc + w_2;
                else _->start = _->range[_->cyc];
                break;
            }
        }
    }
}

void SortBlobsRhoUtility( rho_detection_variables *_, prediction_t * r )
{
    /// NOTE: Smaller scores are better
    /* Assume all blobs are valid */
    index_t i, io, j, jo, best_index;
    floating_t best_score;
    blob_t *curr, *check;
    
    /* Cycle through found blobs */
    for( i = 0; i < _->blbf; i++)
    {
        io = r->BlobsOrder[i];
        curr = &r->Blobs[io];
        if( curr->srt ) continue;

        best_score = curr->scr;
        best_index = i;
        /* Cycle through other blobs */
        for( j = i+1; j < _->blbf; j++ )
        {
            jo = r->BlobsOrder[j];
            check = &r->Blobs[jo];
            
            /* If unscored and less than min, set as new min */
            if( check->scr < best_score )
            {
                best_score = curr->scr;
                best_index = j;
            }
        }

        {
            r->BlobsOrder[i] = best_index;
            r->BlobsOrder[best_index] = i;
        }
        
        r->Blobs[i].srt = true;
    }
    for(; i < MAX_BLOBS; i++ )
    {
        r->BlobsOrder[i] = i;
    }
}

void CalculatedFrameStatisticsRhoUtility( rho_detection_variables *_, prediction_t * r )
{
    /* Update frame statistics */
    _->assumed_blobs = (floating_t)_->blbf;
    if( _->assumed_blobs == 0 ) _->assumed_blobs = 1;
    
    r->NuBlobs = BOUNDU( ZDIV( (floating_t)_->tden * (floating_t)_->assumed_blobs, _->target_density ), MAX_NU_BLOBS );
    r->NumBlobs = _->blbf;
    r->TotalDensity = _->tden;
    
    /* Reset sort flags */
    for( uint8_t i = 0; i < MAX_BLOBS; i++ )
        r->Blobs[i].srt = false;
}

void PredictTrackingFiltersRhoUtility( prediction_t * r )
{    
    index_t valid_tracks = RhoUtility.Predict.CalculateValidTracks( r );
    LOG_RHO( DEBUG_0, "Found %d valid/active tracking filter\n", valid_tracks);
    
    /* Declare essential variables */
    floating_t aa, bb, ab, ba, total_difference = 0., average_difference = 0.;
    
    /* Match blobs to Kalmans */
    index_t m = 0, n = 0, updated = 0;
    for( ; m < ( valid_tracks - 1 ); m ++ )
    {
        for( ; n < ( r->NumBlobs - 1 ); n++ )
        { /* Update tracking filters in pairs following determinant */
            
            /* Retreive current blob pair */
            blob_t
            *blobA = &r->Blobs[r->BlobsOrder[n]],
            *blobB = &r->Blobs[r->BlobsOrder[n+1]];
            
            /* Retreive tracking filters pair */
            byte_t
            fAi = r->TrackingFiltersOrder[m],
            fBi = r->TrackingFiltersOrder[m+1];
            
            rho_kalman_t
            *filterA = &r->TrackingFilters[fAi],
            *filterB = &r->TrackingFilters[fBi];
            
            bool swapped = false;
//            floating_t
//            blocA = blobA->loc,
//            blocB = blobB->loc;
            
            /* Calculate distances between filters and blobs */
            aa = fabs(filterA->value - blobA->loc);
            bb = fabs(filterB->value - blobB->loc);
            ab = fabs(filterA->value - blobB->loc);
            ba = fabs(filterB->value - blobA->loc);
            
            if( aa > MAX_TRACKING_MATCH_DIFFERNCE )
            {
                aa = MAX_TRACKING_MATCH_DIFFERNCE;
                RhoKalman.Punish(filterA);
            }
            if( ab > MAX_TRACKING_MATCH_DIFFERNCE )
            {
                ab = MAX_TRACKING_MATCH_DIFFERNCE;
                RhoKalman.Punish(filterA);
            }
            if( bb > MAX_TRACKING_MATCH_DIFFERNCE )
            {
                bb = MAX_TRACKING_MATCH_DIFFERNCE;
                RhoKalman.Punish(filterB);
            }
            if( ba > MAX_TRACKING_MATCH_DIFFERNCE )
            {
                ba = MAX_TRACKING_MATCH_DIFFERNCE;
                RhoKalman.Punish(filterB);
            }
            
            /* Swap on upward determinant */
            if( aa * bb > ab * ba )
            {
                swapped = true;
                total_difference += aa + bb;
            }
            else
                total_difference += ab + ba;
            updated += 2;

            /* Update filters */
            if(swapped)
            {
                RhoKalman.Update(filterA, blobB->loc);
                RhoKalman.Update(filterB, blobA->loc);
                blobB->tracking_id = fAi;
                blobA->tracking_id = fBi;
            }
            else
            {
                RhoKalman.Update(filterA, blobA->loc);
                RhoKalman.Update(filterB, blobB->loc);
                blobA->tracking_id = fAi;
                blobB->tracking_id = fBi;
            }
            
            m++; n++;
        }
        
        /* Account for odd number of and spare blobs */
        if( m < valid_tracks && n < r->NumBlobs )
        {
            rho_kalman_t
            *filter = &r->TrackingFilters[r->TrackingFiltersOrder[m]];
            floating_t
            bloc = (floating_t)r->Blobs[r->BlobsOrder[n]].loc;
            RhoKalman.Update(filter, bloc);
            
            aa = fabs(filter->value - bloc);
            total_difference += aa;
            updated++;
        }
    }
    
    /* Activate new filters */
    for( ; n < r->NumBlobs && n < MAX_BLOBS; n++ )
    {
        LOG_RHO( DEBUG_0, "Activating filter at index %d[%d]\n", r->TrackingFiltersOrder[n], n );
        RhoKalman.Step( &r->TrackingFilters[r->TrackingFiltersOrder[n]], r->Blobs[r->BlobsOrder[n]].loc, 0. );
    }
    
    /* Punish unused ones */
    for( ; m < MAX_TRACKING_FILTERS; m++ )
    {
        LOG_RHO( DEBUG_0, "Punishing filter at index %d[%d]\n", r->TrackingFiltersOrder[m], m );
        RhoKalman.Punish(&r->TrackingFilters[r->TrackingFiltersOrder[m]]);
    }
    
    /* Calculate confidence */
    if( updated )
    {
        average_difference = total_difference / (floating_t)updated;
        if( average_difference < MAX_TRACKING_MATCH_DIFFERNCE )
            r->Probabilities.confidence = TRACKING_MATCH_TRUST * ( 1 - ( average_difference / MAX_TRACKING_MATCH_DIFFERNCE ) );
        else
            r->Probabilities.confidence = 0.;
    }
    
    RhoUtility.Predict.SortFilters( r );
}

void SortTrackingFiltersRhoUtility( prediction_t * r )
{
    rho_kalman_t *curr, *check;
    floating_t best_score;
    index_t i, io, j, jo, best_index = 0;
    /* Score all filters */
    for( i = 0; i < MAX_TRACKING_FILTERS; i++ )
    {
        RhoKalman.Score( &r->TrackingFilters[i] );
    }
    
    /* Swap sort - Cycle through found blobs */
    for( i = 0; i < MAX_TRACKING_FILTERS; i++)
    {
        io = r->TrackingFiltersOrder[i];
        curr = &r->TrackingFilters[io];
        if( curr->sorted == true) continue;
        
        best_score = curr->score;
        best_index = i;
        /* Cycle through other blobs */
        for( j = i+1; j < MAX_TRACKING_FILTERS; j++ )
        {
            jo = r->TrackingFiltersOrder[j];
            check = &r->TrackingFilters[jo];
            
            /* If unscored and less than min, set as new min */
            if( check->score > best_score )
            {
                best_score = curr->score;
                best_index = j;
            }
        }
//        if( best_index != i )
        {
            r->TrackingFiltersOrder[i] = best_index;
            r->TrackingFiltersOrder[best_index] = i;
        }
        
        r->TrackingFilters[i].sorted = true;
    }
    
    for( i = 0; i < MAX_TRACKING_FILTERS; i++ )
    {
        r->TrackingFilters[i].sorted = false;
    }
}

index_t CalculateValidTracksRhoUtility( prediction_t * r )
{
    index_t valid_tracks = 0, i, io;
    for( i = 0; i < MAX_TRACKING_FILTERS; i++ )
    {
        io = r->TrackingFiltersOrder[i];
        rho_kalman_t *curr = &r->TrackingFilters[io];
        curr->valid = false;
        floating_t score = RhoKalman.Score( curr );
        if( RhoKalman.IsExpired(curr)
           || ( score < MIN_TRACKING_KALMAN_SCORE ) ) break;
        
        RhoKalman.Predict(curr, curr->velocity);
        curr->valid = true;
        valid_tracks++;
    }
    return valid_tracks;
}

void PredictTrackingProbabilitiesRhoUtility( prediction_t * r )
{
    floating_t a = r->NuBlobs+1, b = (floating_t)NUM_STATE_GROUPS+1, curr_CDF, prev_CDF = 0.,
    interval[4] = STATE_KUMARASWAMY_INTERVALS;
    for( uint8_t i = 0; i < NUM_STATE_GROUPS; i++ )
    {
        curr_CDF = KUMARASWAMY_CDF(interval[i],a,b);
        r->Probabilities.P[i] = curr_CDF - prev_CDF;
        prev_CDF = curr_CDF;
    }
}

void ResetForPredictionRhoUtility( prediction_predict_variables * _, prediction_pair_t * p, index_t Cx, index_t Cy )
{
    _->Ax = p->y.Primary;
    _->Ay = p->x.Primary;
    _->Bx = p->y.Secondary;
    _->By = p->x.Secondary;
    _->Cx = Cx;
    _->Cy = Cy;
}

void CorrectPredictionAmbiguityRhoUtility( prediction_predict_variables * _, rho_core_t * core )
{
    /* Check if X or Y are ambiguous */
    if(   !( ( _->Ax < _->Cx ) ^ ( _->Bx > _->Cx ) )
       || !( ( _->Ay < _->Cy ) ^ ( _->By > _->Cy ) ) )
    {
        RhoUtility.Predict.RedistributeDensities( core );
        _->qcheck = (  core->Qf[0] > core->Qf[1] ) + ( core->Qf[2] < core->Qf[3] ) - 1;
        if( ( _->Ax > _->Bx ) ^ ( ( _->qcheck > 0 ) ^ ( _->Ay < _->By ) ) ) SWAP(_->Ax, _->Bx);
    }
}

void CombineAxisProbabilitesRhoUtility( prediction_pair_t * p )
{
    /* Combine X & Y probabilities with confidence factor */
    for( uint8_t i = 0; i < NUM_STATE_GROUPS; i++ )
        p->Probabilities.P[i] = ( ( p->x.Probabilities.confidence * p->x.Probabilities.P[i] ) + ( p->y.Probabilities.confidence * p->y.Probabilities.P[i] ) ) / 2;
    p->Probabilities.confidence = ( p->x.Probabilities.confidence + p->y.Probabilities.confidence ) / 2;
}

void UpdateCorePredictionDataRhoUtility( prediction_predict_variables * _, rho_core_t * core )
{
    _->Cx = BOUNDU((index_t)(_->Ax + _->Bx) >> 1, core->Width );
    _->Cy = BOUNDU((index_t)(_->Ay + _->By) >> 1, core->Height);
    
    LOG_RHO(RHO_DEBUG, "Cx>%d | Cy>%d\n", _->Cx, _->Cy);
    
    core->Px = _->Ax;
    core->Py = _->Ay;
    core->Sx = _->Bx;
    core->Sy = _->By;
    core->Cx = _->Cx;
    core->Cy = _->Cy;
    
    /* NOTE: density maps invert axes */
    core->DensityMapPair.y.centroid = _->Cx;
    core->DensityMapPair.x.centroid = _->Cy;

    core->PredictionPair.y.PreviousCentroid = _->Cx;
    core->PredictionPair.x.PreviousCentroid = _->Cy;
}

void CalculateTuneRhoUtility( rho_core_t * core )
{
    /* Background-Tune on significant background */
    RhoUtility.Calculate.BackgroundTuneFactor( core );
    
    /* State-Tune by FSM state */
    RhoUtility.Calculate.StateTuneFactor( core );
    
    /* Filtered-Tune on target difference */
    RhoUtility.Calculate.TargetTuneFactor( core );
    
    core->Tune.proposed = BOUND( core->Tune.background + core->Tune.state + core->Tune.target, -THRESH_STEP_MAX, THRESH_STEP_MAX);
}

void CalculateBackgroundTuneFactorRhoUtility( rho_core_t * core )
{
    floating_t background_tune_factor = 0.;
    if( core->QbT > BACKGROUND_COVERAGE_MIN )
    {
        floating_t background_coverage_factor = 1 - ZDIV( BACKGROUND_COVERAGE_MIN, core->QbT );
        background_tune_factor = -pow( BOUND(background_coverage_factor, -2, 2), 3);
    }
    core->Tune.background = background_tune_factor;
}

void CalculateStateTuneFactorRhoUtility( rho_core_t * core )
{
    LOG_RHO(ALWAYS, "Current State: %s\n", stateString(core->PredictiveStateModel.current_state));
    double state_tune = 0;
    /* Core tune by state */
    switch(core->PredictiveStateModel.current_state)
    {
        case TARGET_POPULATED:
            RhoKalman.Step( &core->TargetFilter, core->FilteredPercentage, 0. );
            break;
        case CHAOTIC:
            RhoKalman.Reset( &core->DensityMapPair.x.kalmans[0], core->PredictionPair.x.PreviousPeak[0] );
            RhoKalman.Reset( &core->DensityMapPair.x.kalmans[1], core->PredictionPair.x.PreviousPeak[1] );
            RhoKalman.Reset( &core->DensityMapPair.y.kalmans[0], core->PredictionPair.y.PreviousPeak[0] );
            RhoKalman.Reset( &core->DensityMapPair.y.kalmans[1], core->PredictionPair.y.PreviousPeak[1] );
        case OVER_POPULATED:
            state_tune = STATE_TUNE_FACTOR;
            break;
        case UNDER_POPULATED:
            state_tune = -STATE_TUNE_FACTOR;
            break;
        default:
            break;
    }

    core->Tune.state = state_tune;
}

void CalculateTargetTuneFactor( rho_core_t * core )
{
    core->TargetCoverageFactor = core->TargetFilter.value;
    floating_t TotalPixels = (floating_t)core->Width * (floating_t)core->Height;
    if( core->PredictiveStateModel.best_confidence > MIN_STATE_CONFIDENCE )
        core->TargetCoverageFactor = ZDIV( core->PredictiveStateModel.proposed_nu * core->PredictiveStateModel.proposed_avg_den, TotalPixels );
    else
        core->TargetCoverageFactor = ZDIV( core->TotalCoverage, TotalPixels );
    LOG_RHO(ALWAYS, "TCF:%.4f\n", core->TargetCoverageFactor);
    RhoPID.Update( &core->ThreshFilter, core->TargetCoverageFactor, core->TargetFilter.value );
    
    core->Tune.target = TARGET_TUNE_FACTOR * core->ThreshFilter.Value;
}

/* Perform density redistribution from combining current frame and background */
void RedistributeDensitiesRhoUtility( rho_core_t * core )
{
    /* Quadrant density redistribution lookup table */
    static const density_redistribution_lookup_t rlookup =
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
    
    LOG_RHO(DEBUG_0, "Redistributing densities.\n");
    redistribution_variables _ =
    {
        { core->Bx, abs(core->Cx-core->Bx), core->Width - core->Cx  },
        { core->By, abs(core->Cy-core->By), core->Height - core->Cy },
        { 0 }, 0
    };
    if( core->Cx < core->Bx )
    {
        _.xl[0] = core->Cx;
        _.xl[2] = core->Width - core->Bx;
        _.c |= 0x01;
    }
    if( core->Cy < core->By )
    {
        _.yl[0] = core->Cy;
        _.yl[2] = core->Width - core->By;
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
            _.d += ZDIV( _.a, _.b ) * core->Qb[_.q];
        }
#ifndef ALLOW_NEGATIVE_REDISTRIBUTION
        if( _.d > core->Q[_.q] ) core->Qf[_.q] = 0;
        else
#endif
            core->Qf[_.q] = core->Q[_.q] - _.d;
    }
}

inline void GenerateBackgroundRhoUtility( rho_core_t * core )
{
    floating_t xt = RhoUtility.CalculateCentroid( core->DensityMapPair.x.background, core->DensityMapPair.x.length, &core->Bx, BACKGROUND_CENTROID_CALC_THRESH );
    floating_t yt = RhoUtility.CalculateCentroid( core->DensityMapPair.y.background, core->DensityMapPair.y.length, &core->By, BACKGROUND_CENTROID_CALC_THRESH );
    core->QbT = MAX(xt, yt);
}

void GeneratePacketRhoUtility( rho_core_t * core )
{
    packet_value_lookup_t  packet_value_lookup  = PACKET_ADDRESS_INITIALIZER(core->PredictionPair);
    packet_offset_lookup_t packet_offset_lookup = PACKET_OFFSETS;
    packet_generation_variables _ =
    {
        &core->Packet,
        (address_t)&core->Packet.data,
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
        if((_.t=!_.t )) ++_.llPtr;
    }
    
    RhoUtility.PrintPacket( &core->Packet, 3    );
}

void GenerateObservationListFromPredictionsRhoUtility( prediction_t * r, uint8_t thresh )
{
    index_t i = 0;
    for( ; i < r->NumBlobs && i < MAX_OBSERVATIONS; i++ )
    {
        index_t io = r->TrackingFiltersOrder[i];
        if( io >= MAX_TRACKING_FILTERS ) continue;
        floating_t x = r->TrackingFilters[io].value;
        io = r->BlobsOrder[i];
        blob_t * b = &r->Blobs[io];
        bool below_centroid = (density_t)x < r->PreviousCentroid;
        
        index_t density =  (index_t)b->den + (index_t)r->PreviousPeak[(uint8_t)below_centroid];
        density = BOUNDU(density,WIDTH);
        LOG_RHO_BARE(RHO_DEBUG_2, "\t\t(%d) <%d %d %d>\n", i, density, thresh, io);
        r->ObservationList.observations[i] = (observation_t){ density, thresh, io };
    }
    r->ObservationList.length = i;
}
void GenerateObservationListsFromPredictionsRhoUtility( rho_core_t * core )
{
    if(core->PredictionPair.x.NumBlobs > 0)
    {
        LOG_RHO(RHO_DEBUG_2, "Creating observation list for X:\n");
        RhoUtility.Predict.GenerateObservationList( &core->PredictionPair.x, core->ThreshByte );
    }
    if(core->PredictionPair.y.NumBlobs > 0)
    {
        LOG_RHO(RHO_DEBUG_2, "Creating observation list for Y:\n");
        RhoUtility.Predict.GenerateObservationList( &core->PredictionPair.y, core->ThreshByte );
    }
}