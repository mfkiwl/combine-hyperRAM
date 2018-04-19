//
//  tau_test.cpp
//  tau+
//
//  Created by Matthew Fonken on 8/27/17.
//  Copyright © 2017 Marbl. All rights reserved.
//

#include "tau_test.hpp"
#include <string.h>

using namespace cv;
using namespace std;

Vec3b pos_color = { 255,   0, 255};
Vec3b vel_color = { 255, 255,   0};
Vec3b acc_color = {   0, 255,   0};
Vec3b jrk_color = {   0, 255, 255};
Vec3b jnc_color = {   0,   0, 255};

Vec3b ap        = { 150, 255, 150};
Vec3b bp        = { 150, 150, 255};
Vec3b white     = { 255, 255, 255};
Vec3b red       = {   0,   0, 255};
Vec3b blue      = { 255,   0,   0};

void drawTau(Mat M, density_map_pair_t * m, peak_list_pair_t * p, probability_list_pair_t * r, prediction_pair_t * e)
{
    int h       = m->x.length;
    int w       = m->y.length;
    int width   = M.rows;
    int height  = M.cols;
    
    if( h > width )  h = width;
    if( w > height ) w = height;
    
    FLOAT x_scale = 1;
    FLOAT y_scale = 1;
    
    uint16_t pos = 0, vel = 0, acc = 0, jrk = 0, jnc = 0;
    
    int xp = e->x.primary;
    int xs = e->x.secondary;
    int yp = e->y.primary;
    int ys = e->y.secondary;
    
    for(int x=0; x<h; x++)
    {
        pos = m->x.map[x] * x_scale * 2;
        vel = m->x.vel[x] * x_scale * MAP_SCALE + MAP_INSET;
        acc = m->x.acc[x] * x_scale * MAP_SCALE*2 + MAP_INSET;
        jrk = m->x.jrk[x] * x_scale * MAP_SCALE*4 + MAP_INSET;
        jnc = m->x.jnc[x] * x_scale * MAP_SCALE*8 + MAP_INSET;
        if(pos >= height) pos = height-1;
        if(vel >= height) vel = height-1;
        if(acc >= height) acc = height-1;
        if(jrk >= height) jrk = height-1;
        if(jnc >= height) jnc = height-1;
//        for(int q=(MAP_INSET-10);q<=(MAP_INSET+10);q+=5) M.at<Vec3b>(x,q) = white;
        M.at<Vec3b>(x,pos) = pos_color;
//        M.at<Vec3b>(x,vel) = vel_color;
        M.at<Vec3b>(x,acc) = acc_color;
        
        M.at<Vec3b>(x,jnc) = jnc_color;
        
        if( fabs(m->x.jrk[x]) >= 0.10 ) M.at<Vec3b>(x,jrk) = white;
        else M.at<Vec3b>(x,jrk) = jrk_color;
        
        if( fabs(m->x.vel[x]) >= 2 ) M.at<Vec3b>(x,vel) = white;
        else M.at<Vec3b>(x,vel) = vel_color;
        
    }
    for(int i=0; i<p->x.length; i++)
    {
        int l = p->x.map[i];
        for(int k = 0; k < p->x.den[i]; k++)
        {
            int dir = p->x.dir[i];
            if( dir == 1) M.at<Vec3b>(l,k) = red;
            else if( dir == 2 ) M.at<Vec3b>(l,k) = blue;
            else M.at<Vec3b>(l,k) = white;
        }
    }
    
//    int x = 0.1*MAP_SCALE*4 + MAP_INSET;
//    for(int y=0;y<h;y++) M.at<Vec3b>(y,x) = white;
    
    for(int i=0; i<p->x.length; i++)
    {
        int l = p->x.map[i];
        FLOAT v = r->x.primary[i];
        v -= 0.6;
        v *= 3;
        if(v > 1 || v < 0) break;
        Vec3b rp;
        rp[0] = 0;
        rp[1] = 255*(1-v);
        rp[2] = 255*v;
        for(int z = 0; z < height*v*x_scale; z++)
            M.at<Vec3b>(l,z) = rp;
    }
    
    for(int j=0; j<height; j++)
    {
        M.at<Vec3b>(xp,j) = ap;
        M.at<Vec3b>(xs,j) = bp;
    }
    
    for(int y=0; y<w; y++)
    {
        pos = m->y.map[y] * y_scale * 2;
        vel = m->y.vel[y] * y_scale * MAP_SCALE + MAP_INSET;
        acc = m->y.acc[y] * y_scale * MAP_SCALE*4 + MAP_INSET;
        jrk = m->y.jrk[y] * y_scale * MAP_SCALE*8 + MAP_INSET;
        jnc = m->y.jnc[y] * y_scale * MAP_SCALE*16 + MAP_INSET;
        if(pos >= height) pos = width-1;
        if(vel >= height) vel = width-1;
        if(acc >= height) acc = width-1;
        if(jrk >= height) jrk = width-1;
        if(jnc >= height) jnc = width-1;
        M.at<Vec3b>(pos,y) = pos_color;
        M.at<Vec3b>(vel,y) = vel_color;
        M.at<Vec3b>(acc,y) = acc_color;
        M.at<Vec3b>(jrk,y) = jrk_color;
        M.at<Vec3b>(jnc,y) = jnc_color;
    }
    
    for(int i=0; i<p->y.length; i++)
    {
        int l = p->y.map[i];
        for(int k = 0; k < p->y.den[i]; k++)
        {
            int dir = p->y.dir[i];
            if( dir == 1) M.at<Vec3b>(k,l) = red;
            else if( dir == 2 ) M.at<Vec3b>(k,l) = blue;
            else M.at<Vec3b>(k,l) = white;
        }
    }
    
    for(int i=0; i<p->y.length; i++)
    {
        int l = p->y.map[i];
        FLOAT v = r->y.primary[i];
        v -= 0.6;
        v *= 3;
        if(v > 1 || v < 0) break;
        Vec3b rp;
        rp[0] = 0;
        rp[1] = 255*(1-v);
        rp[2] = 255*v;
        for(int z = 0; z < width*v*y_scale; z++)
            M.at<Vec3b>(z, l) = rp;
    }
    
    for(int j = 0; j < width; j++)
    {
        M.at<Vec3b>(j,yp) = ap;
        M.at<Vec3b>(j,ys) = bp;
    }
    
    Mat overlay;
    float alpha = 0.3;
    M.copyTo(overlay);
    rectangle(overlay,Point(yp,xp), Point(ys,xs), Scalar(0,255,255), -1);
    addWeighted(overlay, alpha, M, 1 - alpha, 0, M);
    
    imshow("...", M);
}

void drawKalmanData( prediction_kalman_pair_t * k )
{
    double a,b,c,d;
    string A("A:"),B("B:"),C("C:"),D("D:");
    /* GET VALUES */
    a = k->x.primary.value;
    b = k->x.secondary.value;
    c = k->y.primary.value;
    d = k->y.secondary.value;
    A.append(to_string(a));
    B.append(to_string(b));
    C.append(to_string(c));
    D.append(to_string(d));
    
    /* GET P VALUES */
    string E("xp-P00: "),F("xs-P00: "),G("yp-P00: "),H("ys-P00: ");
    a = k->x.primary.P_k[1][0];
    b = k->x.secondary.P_k[1][0];
    c = k->y.primary.P_k[1][0];
    d = k->y.secondary.P_k[1][0];
    E.append(to_string(a));
    F.append(to_string(b));
    G.append(to_string(c));
    H.append(to_string(d));
    
    int grid = 200, ox = 3, oy = 18;
    int thickness = 1;
    
    Mat O(2*grid, 2*grid, CV_8UC3, Scalar(245,245,245));
    line(O, Point(0,grid), Point(2*grid,grid), Scalar::all(0), thickness,8);
    line(O, Point(grid,0), Point(grid,2*grid), Scalar::all(0), thickness,8);
    
    Point AOrg(ox, oy);
    Point BOrg(ox + grid, oy);
    Point COrg(ox, oy + grid);
    Point DOrg(ox + grid, oy + grid);
    Point EOrg(ox, oy+oy);
    Point FOrg(ox + grid, oy+oy);
    Point GOrg(ox, oy+oy + grid);
    Point HOrg(ox + grid, oy+oy + grid);
    
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.5;
    
    putText(O, A, AOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
    putText(O, B, BOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
    putText(O, C, COrg, fontFace, fontScale, Scalar::all(0), thickness,8);
    putText(O, D, DOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
    
    putText(O, E, EOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
    putText(O, F, FOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
    putText(O, G, GOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
    putText(O, H, HOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
    
    imshow("Kalman Data", O);
}

