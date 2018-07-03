//
//  state_machine_utility.cpp
//  tau+
//
//  Created by Matthew Fonken on 2/8/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#include "state_machine_utility.h"

typedef define_loop_variable_template_struct(state_dimension_t, state_global_t)
state_global_t _;

/* Temporary macros */
#define numberOfSelectedPeaks 1

inline void reset_loop_variables( state_global_t * _, state_dimension_t l )
{ _.l = l; _.i = 0; _.j = 0; _.u = 0, _.v = 0.}

static FLOAT doubt( state_dimension_t i, state_t cs )
{
  FLOAT ret = ((FLOAT)( ( i << 1 ) + 1 )) / NUM_STATES;
  if( isStable(cs) && ( i < stateNumber(cs) ) )
    ret *= DOUBT_STABILITY;
  return ret;
}

static void initMap( bayesian_map_t * bm )
{
  printf("Initializing State Machine.\n");
  reset_loop_variables( &_, NUM_STATES );
  bm->length = NUM_STATES;
  for( ; _.i < _.l; _.i++ )
  {
    for( _.j = 0; _.j < _.l; _.j++ )
    {
      bm->map[_.i][_.j] = 0.0;
    }
    bm->map[_.i][_.i] = 1.0;
  }
}

static void normalizeMap( bayesian_map_t * bm )
{
  reset_loop_variables( &_, bm->length );
  for(  _.i = 0; _.i < _.l; _.i++ ) BayesianFunctions.map.normalizeState( bm, _.i );
}

static void normalizeState( bayesian_map_t * bm, state_dimension_t i )
{
  reset_loop_variables( &_, bm->length );
  FLOAT * total = &_.v;
  for( _.j = 0; _.j < _.l; _.j++ ) *total += bm->map[_.j][_.i];
  if(*total)
  {
    _.v = 1/(*total);
    for( _.j = 0; _.j < _.l; _.j++ ) bm->map[_.j][_.i] *= _.v;
  }
  else bm->map[_.i][_.i] = 1.0;
}

static void resetState( bayesian_map_t * bm, state_dimension_t i )
{
  reset_loop_variables( &_, bm->length );
  for( _.j = 0; _.j < _.l; _.j++ ) bm->map[_.j][_.i] = 0.0;
  bm->map[_.i][_.i] = 1.0;
  BayesianFunctions.map.normalizeState( bm, _.i );
}

static void print( bayesian_map_t * bm, state_t s )
{
  reset_loop_variables( &_, bm->length );
  for( _.i = 0; _.i < _.l; _.i++ ) printf("\t\t %s-[%d]", stateString(_.i), _.i);
  for( _.i = 0; _.i < _.l; _.i++ )
  {
    printf("\n%s-[%d]", stateString(i), i);
    for( _.j = 0; _.j < _.l; _.j++ )
    {
      char c = ' ';
      if(j == (state_dimension_t)s) c = '|';
      printf("\t%c[%.2f]%c",c, bm->map[_.i][_.j],c);
    }
  }
  printf("\n");
}

static void init( bayesian_system_t * sys )
{
  sys->state                = STABLE_NONE;
  sys->prev                 = UNKNOWN_STATE;
  sys->next                 = UNKNOWN_STATE;
  sys->selection_index      = 0;
  sys->stability.primary    = 0.0;
  sys->stability.secondary  = 0.0;
  sys->stability.alternate  = 0.0;
  sys->stability.overall    = 0.0;

  BayesianFunctions.map.initMap( &sys->probabilities );
}

static void update( bayesian_system_t * sys, prediction_pair_t * p )
{
  /** Assumptions
  *  - Column is current state
  *  - Row is next state
  */
  reset_loop_variables( &_, sys->probabilities.length );
  /* Update self-diagnostics based on state */
  FLOAT prob[4] =
    {
      DISTANCE_SQ(p->x.probabilities.absence,   p->y.probabilities.absence),
      DISTANCE_SQ(p->x.probabilities.primary,   p->y.probabilities.primary),
      DISTANCE_SQ(p->x.probabilities.secondary, p->y.probabilities.secondary),
      DISTANCE_SQ(p->x.probabilities.alternate, p->y.probabilities.alternate)
    },
    out[4] = { 0 },
        *f =  &_.u,
        *p =  &_.v,
    *max_v =  &_.u;
  state_t next = sys->current;
  bool ch[4] =
    { 0, //ABSENCE_FACTOR
      prob[1] > PROBABILITY_TUNING_THRESHOLD,
      prob[2] > PROBABILITY_TUNING_THRESHOLD,
      prob[3] > PROBABILITY_TUNING_THRESHOLD
    };

  /* Find most probable next state */

  for( ; _.i < _.l; _.i++ )
  {
    _.v = sys->probabilities.map[_.i][(state_dimension_t)sys->state;];
    if( _.v > *max_v )
    {
      *max_v = _.v;
      next = _.i;
    }
  }
  /* Only update sys->next state on change */
  if( next != sys_current ) sys->next = next;

#ifdef STATEM_DEBUG
printf("\n###### Current state is %s. ######\n\n", stateString((state_dimension_t)sys->state));
printf("Next state is %s(%.2f).\n", stateString((state_dimension_t)sys->next), max_v);
#endif

  _.l = ch[1] + ch[2] + ch[3];
  sys->selection_index = _.l;
  for( _.i = 0; _.i <= _.l; _.i++)
  {
    *p = prob[_.i] * PROBABILITY_TUNING_FACTOR;
    *f = (FLOAT)doubt(_.i, sys->state);
    out[_.i] = (*p) * (*f);
#ifdef STATEM_DEBUG
    printf("Punishing prob[%d]-%.3f by a factor of %.3f for a result of %.3f\n", _.i, *p, *f, out[_.i]);
#endif
  }

  /* Independent Alternate Check */
  if( prob[3] > PROBABILITY_ALTERNATE_THRESH )
    out[3] = prob[3] * PROBABILITY_TUNING_FACTOR_SQ;

  BayesianFunctions.sys.updateProbabilities( sys, out );
  BayesianFunctions.map.normalizeState( &sys->probabilities, sys->state );
  BayesianFunctions.sys.updateState( sys );
  #ifdef STATEM_DEBUG
  print( &sys->probabilities, sys->state );
  #endif
}

static void updateProbabilities( bayesian_system_t * sys, FLOAT p[4] )
{
  state_dimension_t
    c = (state_dimension_t)sys->state,
    x = stateNumber(c);
  int8_t k = -1;

#ifdef STATEM_DEBUG
  for( _.i = 0; _.i < 4; _.i++)
    if( p[_.i] > 10 )
      printf("!\n");
  printf("Probabilies are [0]%.2f [1]%.2f [2]%.2f [3]%.2f.\n", p[0], p[1], p[2], p[3]);
  printf("State %s is ", stateString(c));
  if(!isStable(c)) printf("not ");
  printf("stable.\n");
#endif
  for( _.i = 0; _.i < 4; _.i++ )
  {
    k = -1;
    _.j = x - _.i;
    if(!isStable(c))
    {
      if( x == _.i ) k = c - 1;
      else k = c - ( 2 * _.j );
    }
    else if( x == _.i ) k = c;
    else k = ( c + 1 ) - ( _.j << 1);

#ifdef STATEM_DEBUG
  printf("Updating %s by %.2f.\n", stateString(k), p[_.i]);
#endif
    sys->probabilities.map[k][c] += p[_.i];
  }
}

static void updateState( bayesian_system_t * sys )
{
  if(sys->next != UNKNOWN_STATE )
  {
#ifdef STATEM_DEBUG
  printf("Updating state from %s to %s\n", stateString((int)sys->state), stateString((int)sys->next));
  if(sys->next != sys->state) printf("~~~ State is %s ~~~\n", stateString(sys->next));
#endif
    sys->prev   = sys->state;
    sys->state  = sys->next;
    sys->next   = UNKNOWN_STATE;
    BayesianFunctions.map.resetState( &sys->probabilities, sys->prev );
  }
}

const struct bayesian_functions BayesianFunctions =
{
  { /* Map functions */
    .initMap = initMap,
    .normalizeMap = normalizeMap,
    .normalizeState = normalizeState,
    .resetState = resetState,
    .print = print
  },
  { /* System functions */
    .init = init,
    .update = update,
    .updateProbabilities = updateProbabilities,
    .updateState = updateState
  }
};
