#include "shader.h"
#include <string.h>

void print_error();

/**
 * Create a shader program
 * params:
 *   vertex_shader_source - vertex shader source code
 *   fragnment_shader_source - fragment shader source code
 * returns:
 *   A shader structure
 */
struct shader create_shader_program(const char* vertex_shader_source, const char* fragment_shader_source) {
  const char *vertex_source = read_file(vertex_shader_source);
  if (strcmp(vertex_source, "") == 0) {
        print_error("Error in reading in file: %s\n.", vertex_shader_source);
  }
  
  const char *fragment_source = read_file(fragment_shader_source);
  if (strcmp(fragment_source, "") == 0) {
    print_error("Error in reading in file: %s\n.", fragment_shader_source);
  }
  
  struct shader s;
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLchar *log = NULL;
  GLint log_length, success;
  
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_source, NULL);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
  log = malloc(log_length);
  if (log_length > 0) {
    glGetShaderInfoLog(vertex_shader, log_length, NULL, log);
    print_error(log);
  }
  if(!success) {
    print_error("Error in compiling Vertex shader.\n");
    s.success = -1;
  }
  
  // fragment shader
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_source, NULL);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
  if (log_length > 0) {
    log = realloc(log, log_length);
    glGetShaderInfoLog(fragment_shader, log_length, NULL, log);
    print_error(log);
  }
  if (!success) {
    print_error("Error in compiling Fragment shader.\n");
    s.success = -1;
  }

  s.id = glCreateProgram();
  glAttachShader(s.id, vertex_shader);
  glAttachShader(s.id, fragment_shader);
  glLinkProgram(s.id);
  glGetProgramiv(s.id, GL_LINK_STATUS, &success);
  glGetProgramiv(s.id, GL_INFO_LOG_LENGTH, &log_length);
  if (log_length > 0) {
    log = realloc(log, log_length);
    glGetProgramInfoLog(s.id, log_length, NULL, log);
    print_error(log);
  }
  if (!success) {
    print_error("Issue in linking shader program.\n");
    s.success = -1;
  }
  
  // free resources
  // TODO: revist this deallocation
  /* free(vertex_source); */
  /* free(fragment_source); */
  free(log);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  
  return s;
}

void activate(struct shader* s) {
  glUseProgram(s->id);
}

void delete(struct shader* s) {
  glDeleteProgram(s->id);
}

void print_error(char* log) {
  fprintf(stderr, "Vertex shader log: %s\n", log);
}
