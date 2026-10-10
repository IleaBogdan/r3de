#include"glhelper.h"

GLuint compile_shader(GLenum type,const char*src){
    GLuint s=glCreateShader(type);
    glShaderSource(s,1,&src,NULL);
    glCompileShader(s);
    int ok;
    glGetShaderiv(s,GL_COMPILE_STATUS,&ok);
    if(!ok){
        char log[512];
        glGetShaderInfoLog(s,512,NULL,log);
        fprintf(stderr,"Shader error: %s\n",log);
    }
    return s;
}

GLuint compile_shader_from_file(GLenum type,const char*path){
    size_t len;
    char*src=read_file(path,&len);
    if(!src){
        fprintf(stderr,"Failed to read shader file: %s\n",path);
        return 0;
    }
    GLuint s=compile_shader(type,src);
    free(src);
    return s;
}

char*read_file(const char*path,size_t*out_size){
    if(!path)return NULL;
    FILE*f=fopen(path,"rb");
    if(!f)return NULL;
    if(fseek(f,0,SEEK_END)!=0){fclose(f);return NULL;}
    long size=ftell(f);
    if(size<0){fclose(f);return NULL;}
    rewind(f);
    char*buf=malloc((size_t)size+1);
    if(!buf){fclose(f);return NULL;}
    size_t n=fread(buf,1,(size_t)size,f);
    if(n!=(size_t)size){
        free(buf);
        fclose(f);
        return NULL;
    }
    buf[n]='\0';
    fclose(f);
    if(out_size)*out_size=n;
    return buf;
}

int init_gl_stuff(GLFWwindow**window){
    if(!glfwInit())return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    *window=glfwCreateWindow(800,600,"r3de",NULL,NULL);
    if(!*window){glfwTerminate();return -1;}
    glfwMakeContextCurrent(*window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        fprintf(stderr,"Failed to init GLAD\n");
        return -1;
    }
    return 0;
}

int create_program(const char*vpath,const char*fpath,GLuint*program){
    GLuint vs=compile_shader_from_file(GL_VERTEX_SHADER,vpath);
    GLuint fs=compile_shader_from_file(GL_FRAGMENT_SHADER,fpath);
    if(!vs||!fs){glfwTerminate();return -1;}

    *program=glCreateProgram();
    glAttachShader(*program,vs);
    glAttachShader(*program,fs);
    glLinkProgram(*program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return 0;
}