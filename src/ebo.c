#include "ebo.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct ebo* create_ebo(GLuint* indices, long int size) {
  struct ebo* e = malloc(sizeof(struct ebo));
  GLuint buffer;
  glGenBuffers(1, &buffer);
  e->id = buffer;
  e->size = size * 3;
  e->indices = malloc(sizeof(GLuint) * e->size);
  for (unsigned int i = 0; i < e->size; i++) {
    e->indices[i] = indices[i];
  }
  return e;
}

void bind_ebo(struct ebo* e) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->id);
}

void buffer_ebo_data(struct ebo* e) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, e->size * sizeof(GLuint), e->indices, GL_STATIC_DRAW);
}

void unbind_ebo() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void delete_ebo(struct ebo*  e) {
  glDeleteBuffers(1, &e->id);
  free(e->indices);
  free(e);
}
