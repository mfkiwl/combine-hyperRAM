//
//  rho_global.h
//  rho_client
//
//  Created by Matthew Fonken on 10/22/18.
//  Copyright © 2018 Marbl. All rights reserved.
//

#ifndef rho_global_h
#define rho_global_h

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef double          floating_t;
typedef uint8_t         byte_t;
typedef uint16_t        index_t;
typedef uint16_t        density_t;
typedef int16_t         sdensity_t;
typedef int16_t         variance_t;
typedef uint32_t        density_2d_t;
//typedef uint32_t        register_t;
typedef register_t *    address_t;
typedef floating_t      timestamp_t;
typedef uint8_t         capture_t;
typedef volatile bool   flag_t;

#define byte_t_max          ( (sizeof(byte_t)       << 3 ) - 1 )
#define index_t_max         ( (sizeof(index_t)      << 3 ) - 1 )
#define density_t_max       ( (sizeof(density_t)    << 3 ) - 1 )
#define density_2d_t_max    ( (sizeof(density_2d_t) << 3 ) - 1 )

#define USE_INTERRUPT_MODEL

//#define ALLOW_NEGATIVE_REDISTRIBUTION

//#define RHO_DEBUG
//#define KALMAN_DEBUG
//#define PACKET_DEBUG

#define PSM_DEBUG
#define HMM_DEBUG
//#define GMM_DEBUG
//#define FSM_DEBUG

#ifndef LOG_LEVEL
#define LOG_LEVEL
enum LogLevel
{
    TEST = 0,
    DEBUG_0,
    DEBUG_1,
    DEBUG_2,
    ALWAYS
};
#endif

#define TEST_LOG_LEVEL DEBUG_1

#ifndef LOG
#define LOG(L,...) if(L >= TEST_LOG_LEVEL) \
{  for(uint8_t i=L;i<ALWAYS;i++) printf("\t"); printf(__VA_ARGS__); }
#endif

#ifdef RHO_DEBUG
#define LOG_RHO(L,...) LOG(L,"<Rho> " __VA_ARGS__)
#else
#define LOG_RHO(...)
#endif

#ifdef KALMAN_DEBUG
#define LOG_KALMAN(L,...) LOG(L,"<Kalman> " __VA_ARGS__)
#else
#define LOG_KALMAN(...)
#endif

#ifdef PACKET_DEBUG
#define LOG_PACKET(L,...) LOG(L,"<Packet> " __VA_ARGS__)
#else
#define LOG_PACKET(...)
#endif

#ifdef PSM_DEBUG
#define LOG_PSM(L,...) LOG(L,"<PSM> " __VA_ARGS__)
#else
#define LOG_PSM(...)
#endif

#ifdef HMM_DEBUG
#define LOG_HMM(L,...) LOG(L,"<HMM> " __VA_ARGS__)
#define LOG_HMM_BARE(L,...) LOG(L,"" __VA_ARGS__)
#else
#define LOG_HMM(...)
#define LOG_HMM_BARE(...)
#endif

#ifdef GMM_DEBUG
#define LOG_GMM(L,...) LOG(L,"<GMM> " __VA_ARGS__)
#else
#define LOG_GMM(...)
#endif

#ifdef FSM_DEBUG
#define LOG_FSM(L,...) LOG(L,"<FSM> " __VA_ARGS__)
#else
#define LOG_FSM(...)
#endif


#ifndef MAX
#define MAX(A,B)        ((A>B)?A:B)
#endif

#define SWAP(A,B)      ({typeof(A) temp = A; A = B; B = temp;})

#define BOUNDU(X,MAX)    ((X>MAX)?(MAX):X)         // Bound in upper range
#define BOUND(X,MIN,MAX) ((X<MIN)?MIN:BOUNDU(X,MAX)) // Bound in upper and lower range

#define FBOUND(X,MIN,MAX) ((X<MIN)?MIN:((X>MAX)?MAX:X))

#define SQUARE(X)                       ( X * X )
#define DISTANCE_SQ(X,Y)                ( SQUARE(X) + SQUARE(Y) )
#define INRANGE(X,Y,T)                  ( abs( X - Y ) < T )

#define ZDIV_LNUM 1 << 10
#define ZDIV(X,Y) ((Y==0)?(X==0?0:ZDIV_LNUM):X/Y)

#endif /* rho_global_h */