#ifndef GLHELPER
#define GLHELPER
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include<stdlib.h>

GLuint compile_shader_from_file(GLenum type,const char*path);
GLuint compile_shader(GLenum type,const char*src);
char*read_file(const char*path,size_t*out_size);
int init_gl_stuff(GLFWwindow**window);
int create_program(const char*vpath,const char*fpath,GLuint*program);

#endif