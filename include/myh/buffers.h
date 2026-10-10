#ifndef BUFFERS
#define BUFFERS

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<stdlib.h>

#include<shapes.h>

typedef struct{
    GLuint VAO,VBO,EBO;
    int mesh_index_count;
}buffer;


typedef struct stack_buf{
    buffer bf;
    struct stack_buf*next;
}stack_buf;

void push(stack_buf**head,buffer val);
void pop(stack_buf**head);
void delete_by_index(stack_buf**head,int index);
int stack_size(stack_buf*head);
void clear_stack(stack_buf*head);
void draw_stack(stack_buf*head,void(*draw_function)(const buffer*));


void init_buffer(buffer*bf,const Mesh*m);
void draw_shape(const buffer*bf);

#endif