#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL_events.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <cglm/cglm.h>

#include "shader.h"

struct camera {
  vec3 position;
  vec3 orientation;
  vec3 up;
  unsigned int width;
  unsigned int height;
  float speed;
  float sensitivity;
};

/**
 * Initialize camera
 * args:
 *  width
 *  height
 *  pos
 * return:
 *  a camera structure
 */
struct camera camera_initialize(unsigned int width, unsigned int height, vec3 pos);

/**
 * Function for rendering camera in render loop
 *
 * args:
 *  cam - camera structure
 *  fov - field of view, use degrees
 *  near - near plane on z axis
 *  far - far plane on z axis
 *  s - shader to be used
 *  uniform - name of the unform imported into shader
 */
void camera_matrix(struct camera *cam, float fov, float near, float far, struct shader *s, const char* uniform);

void camera_handle_event(struct camera *cam, SDL_Event *event);


#endif
