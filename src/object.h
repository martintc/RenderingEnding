#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "face.h"

struct object {
  int v_num;
  int f_num;
  struct vector3float *vertices;
  struct face *faces;
  /* vector3float *texture_coordinates; */
  /* vector3float *vertex_normals; */
  /* vector3float *faces; // indicies */
  /* vector3float *group; */
};

void object_free(struct object *obj);

#endif
