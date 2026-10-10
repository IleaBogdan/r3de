#include"mat/mat4.h"

// returns the I4 matrix
Mat4 mat4_identity(void){
    Mat4 r={{
        1,0,0,0, 
        0,1,0,0, 
        0,0,1,0, 
        0,0,0,1
    }};
    return r;
}

Mat4 mat4_mul(Mat4 a,Mat4 b){
    Mat4 r;
    for(int c=0;c<4;++c){
        for(int row=0;row<4;++row) {
            r.m[c*4+row]=0;
            for (int k=0;k<4;++k){
                r.m[c*4+row]+=a.m[k*4+row]*b.m[c*4+k];
            }
        }
    }
    return r;
}

Mat4 mat4_perspective(float fov,float aspect,float near,float far){
    Mat4 r={{0}};
    float f=1.f/(float)tan(fov/2.f);
    r.m[0]=f/aspect;
    r.m[5]=f;
    r.m[10]=(far+near)/(near-far);
    r.m[11]=-1.f;
    r.m[14]=(2.f*far*near)/(near-far);
    return r;
}

Mat4 mat4_translate(float x,float y,float z){
    Mat4 r=mat4_identity();
    r.m[12]=x; 
    r.m[13]=y; 
    r.m[14]=z;
    return r;
}

Mat4 mat4_rotate_y(float angle){
    Mat4 r=mat4_identity();
    float c=(float)cos(angle),s=(float)sin(angle);
    r.m[0]=c;  
    r.m[2]=-s;
    r.m[8]=s;  
    r.m[10]=c;
    return r;
}

Mat4 mat4_rotate_x(float angle){
    Mat4 r=mat4_identity();
    float c=(float)cos(angle),s=(float)sin(angle);
    r.m[5]=c;  
    r.m[6]=s;
    r.m[9]=-s; 
    r.m[10]=c;
    return r;
}

Mat4 mat4_look_at(float eyeX,float eyeY,float eyeZ,float targetX,float targetY,float targetZ,float upX,float upY,float upZ){
    // Forward = normalize(target - eye)
    float fx=targetX-eyeX;
    float fy=targetY-eyeY;
    float fz=targetZ-eyeZ;
    float flen=sqrtf(fx*fx+fy*fy+fz*fz);
    fx/=flen; 
    fy/=flen; 
    fz/=flen;

    // Right = normalize(cross(forward, up))
    float sx=fy*upZ-fz*upY;
    float sy=fz*upX-fx*upZ;
    float sz=fx*upY-fy*upX;
    float slen=sqrtf(sx*sx+sy*sy+sz*sz);
    sx/=slen; 
    sy/=slen; 
    sz/=slen;

    // Up' = cross(right, forward)
    float ux=sy*fz-sz*fy;
    float uy=sz*fx-sx*fz;
    float uz=sx*fy-sy*fx;

    Mat4 r;
    // Column-major
    r.m[0]=sx;  
    r.m[1]=ux;  
    r.m[2]=-fx;  
    r.m[3]=.0f;
    r.m[4]=sy;  
    r.m[5]=uy;  
    r.m[6]=-fy;  
    r.m[7]=.0f;
    r.m[8]=sz;  
    r.m[9]=uz;  
    r.m[10]=-fz; 
    r.m[11]=.0f;

    r.m[12]=-(sx*eyeX+sy*eyeY+sz*eyeZ);
    r.m[13]=-(ux*eyeX+uy*eyeY+uz*eyeZ);
    r.m[14]=(fx*eyeX+fy*eyeY+fz*eyeZ);
    r.m[15]=1.f;
    return r;
}