#ifndef SHAPES_H
#define SHAPES_H

#include<stddef.h>

typedef struct{
    float*vertices;
    size_t vertex_count;
    unsigned int*indices;
    size_t index_count;
}Mesh;

static inline Mesh*init_mesh(Mesh*m,float*verts,size_t vert_count,unsigned int*inds,size_t ind_count){
    m->vertices=verts;
    m->vertex_count=vert_count;
    m->indices=inds;
    m->index_count=ind_count;
    return m;
}

Mesh make_pyramid(float base,float height,float ox,float oy,float oz);
Mesh make_cone(int segments,float radius,float height,float ox,float oy,float oz);
void free_mesh(Mesh*m);

#endif