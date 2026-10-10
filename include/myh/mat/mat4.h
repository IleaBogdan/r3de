#ifndef MAT4
#define MAT4

#include<math.h>

typedef struct{float m[16];}Mat4;
Mat4 mat4_identity(void);
Mat4 mat4_mul(Mat4 a,Mat4 b);
Mat4 mat4_perspective(float fov,float aspect,float near,float far);
Mat4 mat4_translate(float x,float y,float z);
Mat4 mat4_rotate_y(float angle);
Mat4 mat4_rotate_x(float angle);

Mat4 mat4_look_at(float eyeX,float eyeY,float eyeZ,float targetX,float targetY,float targetZ,float upX,float upY,float upZ);

#endif