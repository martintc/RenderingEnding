#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "face.h"
#define GLEW_STATIC
#include <GL/glew.h>

struct object {
  int v_num;
  int f_num;
  GLfloat *vertices;
  GLuint *faces;
  /* vector3float *texture_coordinates; */
  /* vector3float *vertex_normals; */
  /* vector3float *faces; // indicies */
  /* vector3float *group; */
};

void object_free(struct object *obj);

#endif
