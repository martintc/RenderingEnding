#ifndef VAO_H
#define VAO_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "vbo.h"

struct vao {
  GLuint id;
};

struct vao* create_vao();
void bind_vao(struct vao* v);
void link_vao_vbo(struct vbo *vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset);
void enable_vao();
void unbind_vao();
void delete_vao(struct vao * v);

#endif
