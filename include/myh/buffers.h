#ifndef BUFFERS
#define BUFFERS

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<shapes.h>

typedef struct{
    GLuint VAO,VBO,EBO;
    int mesh_index_count;
}buffer;

void init_buffer(buffer*bf,const Mesh*m);
void draw_shape(const buffer*bf);

#endif