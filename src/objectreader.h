#ifndef OBJECTREADER_H
#define OBJECTREADER_H

#include "object.h"
#define GLEW_STATIC
#include <GL/glew.h>

struct object* read_object(char* path);

#endif
