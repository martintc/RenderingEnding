#include "vbo.h"

#include <stdio.h>
#include <stdlib.h>

struct vbo* create_vbo(GLfloat* vertices, long int size) {
  fprintf(stderr, "%ld\n", size);
  struct vbo* v = malloc(sizeof(struct vbo*));
  GLuint buffer;
  glGenBuffers(1, &buffer);
  /* glGenBuffers(1, &v->id); */
  v->id = buffer;
  v->size = size;
  v->vertices = malloc(sizeof(GLfloat) * size);
  for (int i = 0; i < (int)size; i++) {
    v->vertices[i] = vertices[i];
  }
  return v;
}

void bind_vbo(struct vbo* v) {
  glBindBuffer(GL_ARRAY_BUFFER, v->id);
}

void buffer_vbo_data(struct vbo* v) {
  glBufferData(GL_ARRAY_BUFFER, v->size * sizeof(GLfloat), v->vertices, GL_STATIC_DRAW);
}

void unbind_vbo() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void delete_vbo(struct vbo* v) {
  glDeleteBuffers(1, &v->id);
  free(v->vertices);
  free(v);
}
