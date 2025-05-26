#include <obj.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void String_destroy(obj_t class);

// Define a class with a destructor
CLASSD(String, String_destroy) {
  char* data;
  int size;
  int cap;
};

void String_destroy(obj_t obj) {
  String* string = obj;
  free(string->data);
  printf("String destroyed\n");
}

String* String_create(char* data) {
  String* string = OBJ_CREATE(String);
  string->size = strlen(data);
  string->cap = string->size;
  string->data = malloc(string->size);
  memcpy(string->data, data, string->size);
  return string;
}

void String_add(String* self, char* data) {
  int size = strlen(data);
  if (self->size + size > self->cap) {
    while (self->cap < self->size + size) {
      self->cap *= 2;
    }
    self->data = realloc(self->data, self->cap);
  }

  memcpy(self->data + self->size, data, size);
  self->size += size;
}

#define STRING_FMT(string) string->size, string->data

int main(void) {
  String* string = String_create("Hello world");
  printf("%.*s\n", STRING_FMT(string));

  String_add(string, ", how are you today?");
  printf("%.*s\n", STRING_FMT(string));

  obj_release(string);
}
