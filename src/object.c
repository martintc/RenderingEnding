#include <stdlib.h>
#include "object.h"

void object_free(struct object *obj) {
  free(obj->vertices);
  free(obj->faces);
  free(obj);
  obj = NULL;
}
