#include "vao.h"

#include <stdlib.h>

struct vao* create_vao() {
  struct vao* v = malloc(sizeof(struct vao));
  glGenVertexArrays(1, &v->id);
  return v;
}

void bind_vao(struct vao* v) {
  glBindVertexArray(v->id); 
}

void link_vao_vbo(struct vbo *vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset) {
  bind_vbo(vbo);
  glVertexAttribPointer(layout, num_components, GL_FLOAT, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  unbind_vbo();
}

void enable_vao() {
  glEnableVertexAttribArray(0);
}

void unbind_vao() {
  glBindVertexArray(0);
}

void delete_vao(struct vao * v) {
  glDeleteBuffers(1, &v->id);
  free(v);
}
