#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC

#include <GL/glew.h>
#include "util.h"

struct shader {
  GLuint id;
  int success;
};

struct shader create_shader_program(const char* vertex_shader_source, const char* fragment_shader_source);
void activate(struct shader* s);
void delete(struct shader* s);

#endif
