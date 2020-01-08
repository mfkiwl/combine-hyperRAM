/***********************************************************************************************//**
* \file   matrix.c
* \brief  Matrix Math
***************************************************************************************************
*      Author: Matthew Fonken
**************************************************************************************************/

/* Own header */
#include "vector.h"

floating_t len2( vec3_t * v )
{
    floating_t i_2 = v->i * v->i;
    floating_t j_2 = v->j * v->j;
    return sqrt( i_2 + j_2 );
}

floating_t len3( vec3_t * v )
{
    floating_t i_2 = v->i * v->i;
    floating_t j_2 = v->j * v->j;
    floating_t k_2 = v->k * v->k;
    return sqrt( i_2 + j_2 + k_2 );
}

void nrm3( vec3_t * v )
{
    floating_t length = len3( v );
    if(!length) return;
    v->i /= length;
    v->j /= length;
    v->k /= length;
}

void sub3( vec3_t * x, vec3_t * y, vec3_t * z )
{
    z->i = x->i - y->i;
    z->j = x->j - y->j;
    z->k = x->k - y->k;
}

/* Dot product of two vectors */
floating_t dot3( vec3_t * u, vec3_t * v )
{
    return u->i*v->i + u->j*v->j + u->k*v->k;
}

/* Angle between two vectors */
floating_t ang2( vec3_t * u, vec3_t * v)
{
    floating_t uk = u->k, vk = v->k;
    u->k = 0; v->k = 0;
    floating_t lu, lv;
    lu = len3(u);
    floating_t ret = M_PI_2;
    if( lu )
    {
        lv = len3(v);
        if( lv )
        {
            ret =  acos( dot3( u, v ) / ( lu * lv ) );
        }
    }
    u->k = uk; v->k = vk;
    return ret;
}

floating_t ang3( vec3_t * u, vec3_t * v)
{
    floating_t lu, lv;
    lu = len3(u);
    if( lu )
    {
        lv = len3(v);
        if( lv )
        {
            return acos( dot3( u, v ) / ( lu * lv ) );
        }
    }
    return M_PI_2;
}

/* Multiply a vector by a scalar */
void mul3( floating_t m, vec3_t * v, vec3_t * r )
{
    r->i = m * v->i;
    r->j = m * v->j;
    r->k = m * v->k;
}

/* Cross product of two vectors */
void cross3( vec3_t * u, vec3_t * v, vec3_t * r )
{
    r->i = u->j*v->k - u->k*v->j;
    r->j = u->k*v->i - u->i*v->k;
    r->k = u->i*v->j - u->j*v->i;
}

/* Add two vectors */
void add3( vec3_t * u, vec3_t * v, vec3_t * w )
{
    w->i = u->i + v->i;
    w->j = u->j + v->j;
    w->k = u->k + v->k;
}

/* Add three vectors */
void add33( vec3_t * u, vec3_t * v, vec3_t * w, vec3_t * r)
{
    r->i = u->i + v->i + w->i;
    r->j = u->j + v->j + w->j;
    r->k = u->k + v->k + w->k;
}

/* Rotate vector by angle */
void rot2(vec3_t* a, floating_t theta)
{
    double i = a->i, j = a->j;
    double cos_theta = cos(theta), sin_theta = sin(theta);
    a->i = i * cos_theta - j * sin_theta;
    a->j = i * sin_theta + j * cos_theta;
}

const struct kvector Vector =
{
    .sub3 = sub3,
    .len2 = len2,
    .len3 = len3,
    .nrm3 = nrm3,
    .ang2 = ang2,
    .ang3 = ang3,
    .dot3 = dot3,
    .mul3 = mul3,
    .add3 = add3,
    .add33 = add33,
    .cross3 = cross3,
    .rot2 = rot2
};
