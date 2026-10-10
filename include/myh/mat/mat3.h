#ifndef MAT3
#define MAT3

#include<math.h>

typedef struct{float m[9];}Mat3;
Mat3 mat3_identity(void);
Mat3 mat3_mul(Mat3 a,Mat3 b);
Mat3 mat3_translate(float x,float y,float z);
Mat3 mat3_rotate_y(float angle);
Mat3 mat3_rotate_x(float angle);

#endif