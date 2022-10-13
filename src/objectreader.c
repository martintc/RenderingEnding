#include <stdio.h>
#include <string.h>
#include "objectreader.h"
#include "util.h"
#include "vector.h"
#include "face.h"

struct object* read_object(char* path) {
  char* contents = read_file(path);

  // find number of vertices and faces
  int v, f = 0;
  for(int i = 0; i < strlen(contents); i++) {
    if(contents[i] == 'v') {
      v++;
    }
    if(contents[i] == 'f') {
      f++;
    }
  }

  /* FILE* file = open_file(path); */
  /* if (file == NULL) { */
  /*   return NULL; */
  /* } */

  /* int v, f = 0; */
  /* unsigned char c; */
  /* while((c = fgetc(file)) != '\0'){ */
  /*   printf("%c\n", c); */
  /*   if(c == 'v') { */
  /*     v++; */
  /*   } */
  /*   if (c == 'f') { */
  /*     f++; */
  /*   } */
  /* } */
    
  printf("vertices: %d\n", v);
  printf("faces: %d\n", f);

  // initialzie object
  struct object *obj = malloc(sizeof(struct object));
  obj->v_num = v;
  obj->f_num = f;
  obj->vertices = malloc(sizeof(GLfloat) * 3 * v);
  obj->faces = malloc(sizeof(GLuint) * 3 * f);
  
  // fill in vertices
  float i, j, k = 0.0;
  char c;
  // index in allocated vertices array in object
  int v_i = 0;
  // index in allocated face array in object
  int f_i = 0;
  char* rest_string = contents;
  int pos = 0;
  while((sscanf(rest_string, "%c %f %f %f %n", &c, &i, &j, &k, &pos)) != EOF) {
    /* printf("Line recv: %c %f %f %f", c, i, j, k); */
    if (c == 'v') {
      /* obj->vertices[v_i].i = i; */
      /* obj->vertices[v_i].j = j; */
      /* obj->vertices[v_i].k = k; */
      /* v_i++; */
      obj->vertices[v_i] = (GLfloat)i;
      v_i++;
      obj->vertices[v_i] = (GLfloat)j;
      v_i++;
      obj->vertices[v_i] = (GLfloat)k;
      v_i++;
    }
    // if line starts with an f, it is a face
    // populate face line
    if (c == 'f') {
      /* obj->faces[f_i].i = (int)i; */
      /* obj->faces[f_i].j = (int)j; */
      /* obj->faces[f_i].k = (int)k; */
      obj->faces[f_i] = (GLuint)i;
      f_i++;
      obj->faces[f_i] = (GLuint)j;
      f_i++;
      obj->faces[f_i] = (GLuint)k;
      f_i++;
    }
    rest_string = &rest_string[pos];
  }
  
  return obj;
}
