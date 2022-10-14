#ifndef VBO_H
#define VBO_H

#define GLEW_STATIC
#include <GL/glew.h>

struct vbo {
  GLuint id;
  unsigned size;
  GLfloat* vertices;
};

struct vbo* create_vbo(GLfloat* vertices, long int size);
void bind_vbo(struct vbo* v);
void buffer_vbo_data(struct vbo* v);
void unbind_vbo();
void delete_vbo(struct vbo* v);

#endif
