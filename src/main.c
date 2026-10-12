#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include<stdlib.h>

#include<mat/matall.h>
#include<glhelper.h>
#include<shapes.h>
#include<buffers.h>
#include<camera.h>
#include<overlay.h>

static float cube_vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    // Back face
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
};

static float cube2_vertices[] = {
    // Front face
    -0.5f, -0.5f,  6.5f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  6.5f,  1.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  6.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  6.5f,  1.0f, 1.0f, 1.0f,
    // Back face
    -0.5f, -0.5f,  5.5f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  5.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  5.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  5.5f,  1.0f, 0.0f, 1.0f,
};

static unsigned int cube_indices[] = {
    0, 1, 2,  2, 3, 0,   // front
    4, 5, 6,  6, 7, 4,   // back
    3, 2, 6,  6, 7, 3,   // top
    0, 1, 5,  5, 4, 0,   // bottom
    0, 3, 7,  7, 4, 0,   // left
    1, 2, 6,  6, 5, 1,   // right
};

int main(void){
    GLFWwindow*window;
    if(init_gl_stuff(&window)){
        return -1;
    }
    overlay_init(window);
    // glfwSwapInterval(1);   // enable vsync, cap at monitor refresh rate
    glfwSwapInterval(2);   // enable vsync, cap at half monitor refresh rate
    glEnable(GL_DEPTH_TEST);

    GLuint program;
    if(create_program("shaders/vertex.glsl","shaders/fragment.glsl",&program)){
        return -1;
    }

    Mesh cube_mesh;
    init_mesh(&cube_mesh,
        cube_vertices,sizeof(cube_vertices)/sizeof(cube_vertices[0]),
        cube_indices,sizeof(cube_indices)/sizeof(cube_indices[0])
    );

    buffer b;
    init_buffer(&b,&cube_mesh);

    Mesh cube2_mesh;
    init_mesh(&cube2_mesh,
        cube2_vertices,sizeof(cube2_vertices)/sizeof(cube2_vertices[0]),
        cube_indices,sizeof(cube_indices)/sizeof(cube_indices[0])
    );

    buffer b2;
    init_buffer(&b2,&cube2_mesh);

    Mesh pyramid_mesh=make_pyramid(1.f,1.f,-1.5f,0.f,0.f);
    buffer bp;
    init_buffer(&bp,&pyramid_mesh);
    free_mesh(&pyramid_mesh);

    Mesh cone_mesh=make_cone(32,.5f,1.f,1.5f,0.f,0.f);
    buffer bc;
    init_buffer(&bc,&cone_mesh);
    free_mesh(&cone_mesh);

    stack_buf*draw_stack_var=NULL;
    push(&draw_stack_var,b);
    push(&draw_stack_var,bp);
    push(&draw_stack_var,bc);
    push(&draw_stack_var,b2);
    // printf("%d",stack_size(draw_stack_var));
    
    Camera cam;
    camera_init(&cam,.0f,.0f,3.f,   // position
        .0f,.0f);
        
    GLint mvpLoc=glGetUniformLocation(program,"uMVP");
    
    bool b2_deleted=false;
    bool g_prev=false;
    while(!glfwWindowShouldClose(window)){
        // frame setup
        glClearColor(.1f,.1f,.15f,1.f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        // resize window viewpoint
        int w,h;
        glfwGetFramebufferSize(window,&w,&h);
        glViewport(0,0,w,h);
        
        float t=(float)glfwGetTime();
        bool spin=false;
        
        // BUILD THE MVP MATRIX
        Mat4 proj=mat4_perspective(1.f,(float)w/(float)h,.1f,100.f);
        Mat4 view=camera_view(&cam);
        Mat4 model=spin?mat4_mul(mat4_rotate_y(t),mat4_rotate_x(t*.5f)):mat4_identity();
        Mat4 mvp=mat4_mul(proj,mat4_mul(view,model));
        
        // UPLOAD TO GPU
        glUseProgram(program);
        glUniformMatrix4fv(mvpLoc,1,GL_FALSE,mvp.m);
        
        
        // DRAW
        bool g_pressed=glfwGetKey(window,GLFW_KEY_G)==GLFW_PRESS;
        if(g_pressed&&!g_prev){
            if(b2_deleted){
                push(&draw_stack_var,b2);
                b2_deleted=false;
            }else{
                delete_by_index(&draw_stack_var,0);
                b2_deleted=true;
            }
        }
        g_prev=g_pressed;
        draw_stack(draw_stack_var,draw_shape);

        overlay_draw(window,&cam);
        // {
        //     int w, h;
        //     glfwGetFramebufferSize(window, &w, &h);
        //     const char* msg   = "Hello World";
        //     const float scale = 2.0f;
        //     const float pad   = 12.0f;
        //     float x = (float)w - text_width(msg, scale) - pad;
        //     float y = pad;
        //     draw_text(window, msg, x, y, 1.0f, 0.5f, 0.2f, 1.0f, scale); // orange
        // }
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera_keyboard_input(window,&cam);
        
        // camera_move(&cam,.01,.0f);
        // camera_rotate(&cam,.01f,.0f);
    }
    clear_stack(draw_stack_var);
    glfwTerminate();
    return 0;
}