#include "camera.h"

#include <stdio.h>

/**
 * Initialize camera
 * args:
 *  width
 *  height
 *  pos
 * return:
 *  a camera structure
 */
struct camera camera_initialize(unsigned int width, unsigned int height, vec3 pos) {
  struct camera c;
  
  // set up camera
  c.width = width;
  c.height = height;
  
  c.position[0] = pos[0];
  c.position[1] = pos[1];
  c.position[2] = pos[2];
  
  c.orientation[0] = 0.0f;
  c.orientation[1] = 0.0f;
  c.orientation[2] = -1.0;
  
  c.up[0] = 0.0f;
  c.up[1] = 1.0f;
  c.up[2] = 0.0f;
  
  c.speed = 0.1f;
  c.sensitivity = 100.0f;

  return c;
}

void camera_matrix(struct camera *cam, float fov, float near, float far, struct shader *s, const char* uniform) {
  mat4 view = GLM_MAT4_IDENTITY_INIT;
  mat4 projection = GLM_MAT4_IDENTITY_INIT;
  vec3 pos_plus_orien;
  mat4 result_matrix;
  
  glm_vec3_add(cam->position, cam->orientation, pos_plus_orien);
  glm_lookat(cam->position, pos_plus_orien, cam->up, view);

  glm_perspective(glm_rad(fov), (float)(cam->width/cam->height), near, far, projection);

  glm_mat4_mul(projection, view, result_matrix);
  
  // export camera to Vertex Shader?
  glUniformMatrix4fv(glGetUniformLocation(s->id, uniform), 1, GL_FALSE, (float*)result_matrix);
}

void camera_handle_event(struct camera *cam, SDL_Event *event) {
  vec3 vector;
  switch (event->type) {
  case SDL_KEYDOWN:
    switch(event->key.keysym.sym) {
    case SDLK_w: // forward
      glm_vec3_scale(cam->orientation, cam->speed, vector);
      glm_vec3_add(cam->position, vector, cam->position);
      return;
    case SDLK_s: // back
      glm_vec3_scale(cam->orientation, -1.0f, vector);
      glm_vec3_scale(vector, cam->speed, vector);
      glm_vec3_add(cam->position, vector, cam->position);
      return;
    case SDLK_a: // left
      glm_vec3_crossn(cam->orientation, cam->up, vector);
      glm_vec3_scale(vector, cam->speed * -1, vector);
      glm_vec3_add(cam->position, vector, cam->position);
      return;
    case SDLK_d: // right
      glm_vec3_crossn(cam->orientation, cam->up, vector);
      glm_vec3_scale(vector, cam->speed, vector);
      glm_vec3_add(cam->position, vector, cam->position);
      return;
    }
  }
}
