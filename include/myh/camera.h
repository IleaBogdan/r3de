#ifndef CAMERA_H
#define CAMERA_H

#include<mat/mat4.h>
#include<math.h>

typedef struct{
    float pos[3];     // camera position
    float yaw;        // rotation around Y (left/right), in radians
    float pitch;      // rotation around X (up/down), in radians
    float up[3];      // usually (0,1,0)
}Camera;

static inline void camera_init(Camera*c,float px,float py,float pz,float yaw,float pitch){
    c->pos[0]=px; 
    c->pos[1]=py; 
    c->pos[2]=pz;
    c->yaw=yaw;
    c->pitch=pitch;
    c->up[0]=0.f; 
    c->up[1]=1.f; 
    c->up[2]=0.f;
}

// Rotate camera by deltas (typically from mouse movement)
static inline void camera_rotate(Camera*c,float dYaw,float dPitch){
    c->yaw+=dYaw;
    c->pitch+=dPitch;

    // Clamp pitch so we never flip upside-down
    const float limit=1.55334f; // ~89 degrees in radians
    if(c->pitch>limit)c->pitch=limit;
    if(c->pitch<-limit)c->pitch=-limit;
}

// Move the camera along its own forward/right axes
static inline void camera_move(Camera*c,float forward,float right){
    float cy=cosf(c->yaw),sy=sinf(c->yaw);
    float cp=cosf(c->pitch),sp=sinf(c->pitch);

    // Forward direction (where camera looks)
    float fx=sy*cp;
    float fy=-sp;
    float fz=-cy*cp;

    // Right direction = normalize(cross(forward, up)) with up=(0,1,0)
    float rx=cy;
    float rz=sy;

    c->pos[0]+=fx*forward+rx*right;
    c->pos[1]+=fy*forward;
    c->pos[2]+=fz*forward+rz*right;
}

// Build the view matrix
static inline Mat4 camera_view(const Camera*c) {
    float cp=cosf(c->pitch),sp=sinf(c->pitch);
    float cy=cosf(c->yaw),sy=sinf(c->yaw);

    // Target = pos + forward
    float tx=c->pos[0]+sy*cp;
    float ty=c->pos[1]-sp;
    float tz=c->pos[2]-cy*cp;

    return mat4_look_at(
        c->pos[0],c->pos[1],c->pos[2],
        tx,ty,tz,
        c->up[0],c->up[1],c->up[2]
    );
}

static inline void camera_keyboard_input(GLFWwindow*window,Camera*cam){
    float rotSpeed=.02f;
    if(glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS)camera_rotate(cam,-rotSpeed,0.f);
    if(glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS)camera_rotate(cam,rotSpeed,0.f);
    if(glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS)camera_rotate(cam,0.f,-rotSpeed);
    if(glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS)camera_rotate(cam,0.f,rotSpeed);
    float moveSpeed=.02f;
    if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)camera_move(cam,-moveSpeed,0.f);
    if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)camera_move(cam,moveSpeed,0.f);
    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)camera_move(cam,0.f,-moveSpeed);
    if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)camera_move(cam,0.f,moveSpeed);
}

#endif