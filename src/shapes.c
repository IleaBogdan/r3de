#include"shapes.h"
#include<stdlib.h>
#include<math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const float palette[][3]={
    {1.f,0.f,0.f},{0.f,1.f,0.f},{0.f,0.f,1.f},{1.f,1.f,0.f},
    {1.f,0.f,1.f},{0.f,1.f,1.f},{1.f,1.f,1.f},{0.5f,0.5f,0.5f},
};

static Mesh make_cone_mesh(int segments,float radius,float height,float phase,float ox,float oy,float oz){
    Mesh m;
    int nverts=segments+2;
    m.vertex_count=nverts*6;
    m.vertices=malloc(m.vertex_count*sizeof(float));
    if(!m.vertices){
        m.indices=NULL;
        m.index_count=0;
        return m;
    }

    m.index_count=segments*6;
    m.indices=malloc(m.index_count*sizeof(unsigned int));
    if(!m.indices){
        free(m.vertices);
        m.vertices=NULL;
        m.vertex_count=0;
        m.index_count=0;
        return m;
    }

    float half=height*.5f;
    float*v=m.vertices;

    // apex (index 0)
    v[0]=ox;v[1]=oy+half;v[2]=oz;v[3]=1.f;v[4]=1.f;v[5]=1.f;

    // base ring (indices 1..segments)
    for(int i=0;i<segments;i++){
        float a=phase+2.f*(float)M_PI*i/segments;
        float*p=v+(1+i)*6;
        p[0]=ox+radius*cosf(a);
        p[1]=oy-half;
        p[2]=oz+radius*sinf(a);
        const float*c=palette[i%8];
        p[3]=c[0];p[4]=c[1];p[5]=c[2];
    }

    // base center (index 1+segments)
    float*p=v+(1+segments)*6;
    p[0]=ox;p[1]=oy-half;p[2]=oz;p[3]=.3f;p[4]=.3f;p[5]=.3f;

    unsigned int*idx=m.indices;
    int apex=0;
    int center=1+segments;
    for(int i=0;i<segments;i++){
        int a=1+i;
        int b=1+(i+1)%segments;
        *idx++=apex;*idx++=a;*idx++=b;
        *idx++=center;*idx++=b;*idx++=a;
    }

    return m;
}

Mesh make_pyramid(float base,float height,float ox,float oy,float oz){
    return make_cone_mesh(4,base*.70710678f,height,(float)M_PI/4.f,ox,oy,oz);
}

Mesh make_cone(int segments,float radius,float height,float ox,float oy,float oz){
    if(segments<3)segments=3;
    return make_cone_mesh(segments,radius,height,0.f,ox,oy,oz);
}

void free_mesh(Mesh*m){
    free(m->vertices);
    free(m->indices);
    m->vertices=NULL;
    m->indices=NULL;
    m->vertex_count=0;
    m->index_count=0;
}
