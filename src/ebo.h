#ifndef EBO_H
#define EBO_H

#define GLEW_STATIC
#include <GL/glew.h>

struct ebo {
  GLuint id;
  unsigned int size;
  GLuint* indices;
};

struct ebo* create_ebo(GLuint* indices, long int size);
void bind_ebo(struct ebo* e);
void buffer_ebo_data(struct ebo* e);
void unbind_ebo();
void delete_ebo(struct ebo*  e);

#endif
