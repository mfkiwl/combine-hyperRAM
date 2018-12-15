#include "rho_kalman.h"

/** SOURCE: http://preview.tinyurl.com/9djhrem */

void InitRhoKalman( rho_kalman_t * k, kfl_t v, kfl_t ls, kfl_t vu, kfl_t bu, kfl_t su )
{
    k->K[0]        = 0;
    k->K[1]        = 0;
    k->P[0][0]     = 0;
    k->P[0][1]     = 0;
    k->P[1][0]     = 0;
    k->P[1][1]     = 0;
    k->rate        = 0;
    k->bias        = 0;
    k->value       = v;
    k->prev        = 0;
    k->velocity    = 0;
    k->variance    = 0;
    
    k->lifespan    = ls;
    k->uncertainty.value   = vu;
    k->uncertainty.bias    = bu;
    k->uncertainty.sensor  = su;
}

void PredictRhoKalman( rho_kalman_t * k, kfl_t rate_new )
{
    kfl_t delta_time = timestamp() - k->timestamp;
    
    /* Quick expiration check */
    if(delta_time > k->lifespan)
    {
        k->timestamp = timestamp();
        return;
    }
    k->velocity   = k->value - k->prev;
    k->prev       = k->value;
    k->rate       = rate_new - k->bias;
    k->value     += delta_time * k->rate;
    
    kfl_t dt_P_1_1 = delta_time * k->P[1][1];
    k->P[0][0]   += delta_time * ( dt_P_1_1 -
                                  k->P[0][1] -
                                  k->P[1][0] +
                                  k->uncertainty.value );
    k->P[0][1]   -= dt_P_1_1;
    k->P[1][0]   -= dt_P_1_1;
    k->P[1][1]   += k->uncertainty.bias * delta_time;
}

void UpdateRhoKalman( rho_kalman_t * k, kfl_t value_new )
{
    kfl_t S_      = 1 / ( k->P[0][0] + k->uncertainty.sensor );
    k->K[0]       = k->P[0][0] * S_;
    k->K[1]       = k->P[1][0] * S_;
    kfl_t delta_value = value_new - k->value;
    k->value     += k->K[0] * delta_value;
    k->bias      += k->K[1] * delta_value;
    
    k->P[0][0]   -= k->K[0] * k->P[0][0];
    k->P[0][1]   -= k->K[0] * k->P[0][1];
    k->P[1][0]   -= k->K[1] * k->P[0][0];
    k->P[1][1]   -= k->K[1] * k->P[0][1];
    
    k->timestamp  = timestamp();
};

void StepRhoKalman( rho_kalman_t * k, kfl_t value_new, kfl_t rate_new )
{
    PredictRhoKalman(k, rate_new);
    UpdateRhoKalman(k, value_new);
}

bool IsRhoKalmanExpired( rho_kalman_t * k )
{
    return ((timestamp() - k->timestamp) > k->lifespan);
}

inline kfl_t ScoreRhoKalman( rho_kalman_t * k )
{
    return k->K[0];
}

void PunishRhoKalman( rho_kalman_t * k )
{
    k->K[0] *= KALMAN_PUNISH_FACTOR;
}
