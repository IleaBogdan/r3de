#ifndef CAMERA_H
#define CAMERA_H

#include <mat4.h>

typedef struct{
    float pos[3];     // where the camera is
    float target[3];  // the point it looks at
    float up[3];      // usually (0,1,0)
}Camera;

static inline void camera_init(Camera*c,float px,float py,float pz,float tx,float ty,float tz){
    c->pos[0]=px; 
    c->pos[1]=py; 
    c->pos[2]=pz;
    c->target[0]=tx; 
    c->target[1]=ty; 
    c->target[2]=tz;
    c->up[0]=.0f; 
    c->up[1]=1.f; 
    c->up[2]=.0f;
}

// Move the camera (and its look-at point) freely in world space.
static inline void camera_move(Camera*c,float dx,float dy,float dz){
    c->pos[0]+=dx; 
    c->pos[1]+=dy; 
    c->pos[2]+=dz;
    c->target[0]+=dx; 
    c->target[1]+=dy; 
    c->target[2]+=dz;
}

// Just aim the camera at a new point.
static inline void camera_look_at(Camera*c,float tx,float ty,float tz){
    c->target[0]=tx; 
    c->target[1]=ty; 
    c->target[2]=tz;
}

// Build the view matrix from this camera.
static inline Mat4 camera_view(const Camera*c){
    return mat4_look_at(
        c->pos[0],c->pos[1],c->pos[2],
        c->target[0],c->target[1],c->target[2],
        c->up[0],c->up[1],c->up[2]
    );
}

#endif