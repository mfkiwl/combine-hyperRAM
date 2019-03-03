//
//  hmm.h
//  hmmtest
//
//  Created by Matthew Fonken on 2/10/19.
//  Copyright © 2019 Matthew Fonken. All rights reserved.
//

#ifndef hmm_h
#define hmm_h

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "fsm.h"

void   InitializeHMM(                hidden_markov_model_t * );
double ForwardRecursionHMM(          hidden_markov_model_t *, uint8_t, uint8_t );
double ForwardSolveHMM(              hidden_markov_model_t *, uint8_t );
double BackwardRecursionHMM(         hidden_markov_model_t *, uint8_t, uint8_t );
double BackwardSolveHMM(             hidden_markov_model_t *, uint8_t );
void   UpdateObservationMatrixHMM(   hidden_markov_model_t *, uint8_t );
void   BaumWelchObservationSolveHMM( hidden_markov_model_t *, uint8_t );
void   BaumWelchTransitionSolveHMM( hidden_markov_model_t *, uint8_t );
void   BaumWelchSolveHMM( hidden_markov_model_t *, uint8_t );

typedef struct
{
    void   (*Initialize)(                hidden_markov_model_t * );
    double (*ForwardRecursion)(          hidden_markov_model_t *, uint8_t, uint8_t );
    double (*ForwardSolve)(              hidden_markov_model_t *, uint8_t );
    double (*BackwardRecursion)(         hidden_markov_model_t *, uint8_t, uint8_t );
    double (*BackwardSolve)(             hidden_markov_model_t *, uint8_t );
    void   (*UpdateObservationMatrix)(   hidden_markov_model_t *, uint8_t );
    void   (*BaumWelchObservationSolve)( hidden_markov_model_t *, uint8_t );
    void   (*BaumWelchTransitionSolve)( hidden_markov_model_t *, uint8_t );
    void   (*BaumWelchSolve)( hidden_markov_model_t *, uint8_t );
} hidden_markov_model_function_t;

static const hidden_markov_model_function_t HMMFunctions =
{
    .Initialize = InitializeHMM,
    .ForwardRecursion = ForwardRecursionHMM,
    .ForwardSolve = ForwardSolveHMM,
    .BackwardRecursion = BackwardRecursionHMM,
    .BackwardSolve = BackwardSolveHMM,
    .UpdateObservationMatrix = UpdateObservationMatrixHMM,
    .BaumWelchObservationSolve = BaumWelchObservationSolveHMM,
    .BaumWelchTransitionSolve = BaumWelchTransitionSolveHMM,
    .BaumWelchSolve = BaumWelchSolveHMM
};
    
#ifdef __cplusplus
}
#endif

#endif /* hmm_h */
