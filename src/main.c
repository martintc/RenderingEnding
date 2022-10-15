#include <stdio.h>

#include<SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <cglm/cglm.h>

#include "ebo.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "object.h"
#include "objectreader.h"
#include "vector.h"
#include "face.h"

static const GLuint WIDTH = 512;
static const GLuint HEIGHT = 512;
/* static const GLchar* vertex_shader_source = */
/* "#version 330 core\n" */
/* "layout (location = 0) in vec3 aPos;\n" */
/* "void main()\n" */
/* "{\n" */
/* "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" */
/* "}\0"; */
/* static const GLchar* fragment_shader_source = */
/* "#version 330 core\n" */
/* "out vec4 FragColor;\n" */
/* "void main()\n" */
/* "{\n" */
/* "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n" */
/* "}\n\0"; */

GLfloat vertices[] = {
  // First three in the row are positions
  // Last three in the row are RGB values
  -0.25f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
  0.0f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
  0.25f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

GLuint indices[] = {
  0, 1, 2,
  2, 3, 4,
  4, 5, 0
};

/* GLfloat vertices[] = { */
/*   -0.5f, -0.5f, 0.0f, */
/*   0.5f, -0.5f, 0.0f, */
/*   0.5f, 0.5f, 0.0f, */
/*   -0.5f, 0.5f, 0.0f */
/* }; */

/* GLuint indices[] = { */
/*   0, 1, 2, */
/*   2, 3, 0 */
/* }; */

SDL_Window *window;
SDL_GLContext gl_context;
// ebo for index buffer
GLuint program, vbo, ebo, vao;
GLint attribute_coord2d;

void print_sdl_error() {
  fprintf(stderr, "An error occured: %s\n.", SDL_GetError());
}

void gl_error() {
  if (glGetError()  > 0) {
    fprintf(stderr, "Error in OpenGL: %d\n", glGetError());
  }
}

int initialize_sdl_opengl() {
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    print_sdl_error();
    return -1;
  }

  window = SDL_CreateWindow(
			    "My Window",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    WIDTH,
			    HEIGHT,
			    SDL_WINDOW_OPENGL
			    );
  if (window == NULL) {
    print_sdl_error();
    return -1;
  }

  gl_context = SDL_GL_CreateContext(window);

  if (gl_context == NULL) {
    print_sdl_error();
    return -1;
  }

  return 0;
}

void destroy() {
  glDeleteBuffers(1, &vao);
  glDeleteBuffers(1, &ebo);
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

GLuint common_get_shader_program(const char* vertex_shader_source, const char* fragment_shader_source) {
  GLchar *log = NULL;
  GLint log_length, success;
  GLuint fragment_shader, program, vertex_shader;

  /* vertex shader */
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
  log = malloc(log_length);
  if (log_length > 0) {
    glGetShaderInfoLog(vertex_shader, log_length, NULL, log);
    fprintf(stderr, "Vertex shader log: %s\n", log);
  }
  if(!success) {
    fprintf(stderr, "vertex shader compile error\n");
    exit(EXIT_FAILURE);
  }

  // fragment shader
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        log = realloc(log, log_length);
        glGetShaderInfoLog(fragment_shader, log_length, NULL, log);
        printf("fragment shader log:\n\n%s\n", log);
    }
    if (!success) {
        printf("fragment shader compile error\n");
        exit(EXIT_FAILURE);
    }
  
  // link shaders
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
  if (log_length > 0) {
      log = realloc(log, log_length);
      glGetProgramInfoLog(program, log_length, NULL, log);
      printf("shader link log:\n\n%s\n", log);
  }
  if (!success) {
      printf("shader link error");
      exit(EXIT_FAILURE);
  }

  free(log);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  return program;
}

void shader_setup() {
  /* program = common_get_shader_program(vertex_shader_source, fragment_shader_source); */
  attribute_coord2d = glGetAttribLocation(program, "coord2d");
}

/* int main(void) { */
/*   if(initialize_sdl_opengl() < 0) { */
/*     return 0; */
/*   } */

/*   // initialize glew */
/*   glewInit();  */

/*   glViewport(0, 0, 512, 512); */

/*   char* vertex_shader_source = "shaders/vertex.vert"; */
/*   char* fragment_shader_source = "shaders/fragment.frag"; */

/*   //shader_setup(); */
  
/*   struct shader s = create_shader_program(vertex_shader_source, fragment_shader_source); */

/*   // ordering matters for generating */
/*   /\* glGenVertexArrays(1, &vao); *\/ */
/*   struct vao* vao = create_vao(); */
/*   /\* glGenBuffers(1, &vbo); *\/ */
/*   struct vbo* v = create_vbo(vertices, sizeof(vertices)/sizeof(vertices[0])); */
/*   /\* glGenBuffers(1, &ebo); *\/ */
/*   struct ebo* e = create_ebo(indices, sizeof(indices)/sizeof(indices[0])); */
  
/*   /\* glBindVertexArray(vao); *\/ */
/*   bind_vao(vao); */
/*   /\* glBindBuffer(GL_ARRAY_BUFFER, vbo); *\/ */
/*   bind_vbo(v); */
/*   /\* glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); *\/ */
/*   buffer_vbo_data(v); */
  
/*   /\* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); *\/ */
/*   bind_ebo(e); */
/*   /\* glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); *\/ */
/*   buffer_ebo_data(e); */

/*   /\* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); *\/ */
/*   // only a single vertex array, so 0 */
/*   /\* glEnableVertexAttribArray(0); *\/ */
/*   /\* enable_vao(vao); *\/ */
/*   link_vao_vbo(v, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); */
/*   link_vao_vbo(v, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); */
  
/*   unbind_vbo(); */
/*   /\* glBindVertexArray(0); *\/ */
/*   unbind_vao(); */
/*   /\* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); *\/ */
/*   unbind_ebo(); */

/*   /\* glClearColor(0.0f, 0.0f, 0.0f, 1.0f); *\/ */
/*   /\* glClear(GL_COLOR_BUFFER_BIT); *\/ */

/*   /\* SDL_GL_SwapWindow(window); *\/ */
  
/*   SDL_Event event; */
  
/*   /\* main loop *\/ */
/*   while(1) { */

/*     glClearColor(0.0f, 0.0f, 0.0f, 1.0f); */
/*     glClear(GL_COLOR_BUFFER_BIT); */

/*     activate(&s); */
/*     /\* glBindVertexArray(vao); *\/ */
/*     bind_vao(vao); */
/*     /\* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); *\/ */
/*     bind_ebo(e); */
/*     /\* glDrawArrays(GL_TRIANGLES, 0, 3); *\/ */
/*     glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, (void*)0); */

/*     SDL_GL_SwapWindow(window); */
    
/*     if (SDL_PollEvent(&event) && event.type == SDL_QUIT) { */
/*       break; */
/*     } */
/*   } */

/*   delete(&s); */
/*   delete_vbo(v); */
/*   destroy(); */
  
/*   return 0; */
/* } */

// testing object reader

int main(void) {
  if(initialize_sdl_opengl() < 0) {
    return 0;
  }

  // initialize glew
  glewInit();

  glViewport(0, 0, 512, 512);

  char* vertex_shader_source = "shaders/vertex.vert";
  char* fragment_shader_source = "shaders/fragment.frag";
  
  //shader_setup();
  
  struct shader s = create_shader_program(vertex_shader_source, fragment_shader_source);
  
  char* pumpkin = "samples/pumpkin_tall_10k.obj";
  char* triforce = "samples/triforce.obj";
  char* triangle = "samples/triangle.obj";
  char* box = "samples/box.obj";
  
  struct object *obj = read_object(triangle);
  
  // ordering matters for generating
  /* glGenVertexArrays(1, &vao); */
  struct vao* vao = create_vao();
  /* glGenBuffers(1, &vbo); */
  struct vbo* v = create_vbo(obj->vertices, obj->v_num);

  /* glGenBuffers(1, &ebo); */
  struct ebo* e = create_ebo(obj->faces, obj->f_num);
  
  /* glBindVertexArray(vao); */
  bind_vao(vao);
  /* glBindBuffer(GL_ARRAY_BUFFER, vbo); */
  bind_vbo(v);
  /* glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); */
  buffer_vbo_data(v);
  
  /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); */
  bind_ebo(e);
  /* glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); */
  buffer_ebo_data(e);

  /* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); */
  // only a single vertex array, so 0
  /* glEnableVertexAttribArray(0); */
  /* enable_vao(vao); */
  // link_vao_vbo(v, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
  link_vao_vbo(v, 0, 3, GL_FLOAT, 0, (void*)0);
  /* link_vao_vbo(v, 1, 3, GL_FLOAT, 3 * sizeof(float), (void*)(3 * sizeof(float))); */
  
  unbind_vbo();
  /* glBindVertexArray(0); */
  unbind_vao();
  /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); */
  unbind_ebo();

  /* glClearColor(0.0f, 0.0f, 0.0f, 1.0f); */
  /* glClear(GL_COLOR_BUFFER_BIT); */

  /* SDL_GL_SwapWindow(window); */
  
  SDL_Event event;

  /* main loop */
  while(1) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    activate(&s);
    /* glBindVertexArray(vao); */
    bind_vao(vao);
    /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); */
    bind_ebo(e);
    /* glDrawArrays(GL_TRIANGLES, 0, 3); */
    glDrawElements(GL_TRIANGLES, obj->f_num * 3, GL_UNSIGNED_INT, (void*)0);

    SDL_GL_SwapWindow(window);
    
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
      break;
    }
  }
  
  delete(&s);
  delete_vbo(v);
  destroy();
  object_free(obj);
  
  return 0;
}
