#include"mat/mat3.h"

// returns the I3 matrix
Mat3 mat3_identity(void){
    Mat3 r={{ 
        1,0,0, 
        0,1,0, 
        0,0,1 
    }};
    return r;
}

Mat3 mat3_mul(Mat3 a,Mat3 b){
    Mat3 r;
    for(int c=0;c<3;++c){
        for(int row=0;row<3;++row){
            r.m[c*3+row]=0;
            for(int k=0;k<3;++k){
                r.m[c*3+row]+=a.m[k*3+row]*b.m[c*3+k];
            }
        }
    }
    return r;
}


Mat3 mat3_translate(float x,float y,float z){
    // 3x3 affine translation stored in the third column.
    Mat3 r=mat3_identity();
    r.m[6]=x;   // column 2, row 0
    r.m[7]=y;   // column 2, row 1
    r.m[8]=z;   // column 2, row 2
    return r;
}

Mat3 mat3_rotate_y(float angle){
    Mat3 r=mat3_identity();
    float c=(float)cos(angle),s=(float)sin(angle);
    r.m[0]=c;   // col0 row0
    r.m[2]=-s;  // col0 row2
    r.m[6]=s;   // col2 row0
    r.m[8]=c;   // col2 row2
    return r;
}

Mat3 mat3_rotate_x(float angle){
    Mat3 r=mat3_identity();
    float c=(float)cos(angle),s=(float)sin(angle);
    r.m[4]=c;   // col1 row1
    r.m[5]=s;   // col1 row2
    r.m[7]=-s;  // col2 row1
    r.m[8]=c;   // col2 row2
    return r;
}