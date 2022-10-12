#include "util.h"

char* read_file(const char* path) {
  long length;
  FILE* file = fopen(path, "r");

  // check for error
  if(file == NULL) {
    return "";
  }

  fseek(file, 0, SEEK_END);
  length = ftell(file);
  rewind(file);

  char *content = malloc(sizeof(char) * length);

  fread(content, 1, length, file);
  
  fclose(file);

  return content;
}

FILE* open_file(const char* path) {
  FILE* file = fopen(path, "r");
  if(file == NULL) {
    return NULL;
  }
  return file;
}
