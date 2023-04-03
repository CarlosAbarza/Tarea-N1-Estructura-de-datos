#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arraylist.h"

//normal array
typedef struct ArrayList {
    void **data;
    int capacity;
    int size;
} ArrayList;

ArrayList *createArray(void) {
  ArrayList *local = (ArrayList*) malloc(sizeof(ArrayList));
  if (local == NULL) return NULL;
  local->data = (void*) calloc(2, sizeof(void*));
  if (local->data == NULL) return NULL;
  local->capacity = 2;
  local->size = 0;
  return local;
}

void append(ArrayList * l, void * data){
  if (l->size == l->capacity) {
    l->data = (void*) realloc(l->data, l->capacity * 2 * sizeof(void*));
    if (l->data == NULL) {
      printf("Error al reservar memoria");
      return;
    }
    l->capacity *= 2;
  }
  l->data[l->size] = data;
  l->size++;
}

void push(ArrayList * l, void * data, int i){
  if (i > l->size) return;
  if (l->size == l->capacity) {
    l->data = (void*) realloc(l->data, l->capacity * 2 * sizeof(void*));
    if (l->data == NULL) {
      printf("Error al reservar memoria");
      return;
    }
    l->capacity *= 2;
  }
  for (int j = l->size; j > i; j--) {
    l->data[j] = l->data[j-1];
  }
  l->data[i] = data;
  l->size++;
}

void* pop(ArrayList * l, int i){
  if (l->size == 0 || i >= l->size) return NULL;
  void* aux = get(l, i);
  if (i < 0) {
    for (int j = l->size + i; j < l->size; j++) {
      l->data[j] = l->data[j+1];
    }
  }
  else {
    for (int j = i; j < l->size; j++) {
      l->data[j] = l->data[j+1];
    }
  }
  l->size--;
  return aux;
}

void* get(ArrayList * l, int i){
  if (i >= l->size) return NULL;
  if (i < 0) {
    return l->data[l->size + i];
  }
  return l->data[i];
}

int get_size(ArrayList * l){
    return l->size;
}

//remove elements
void clean(ArrayList * l){
  for (int i = 0; i < l->size; i++) {
    free(l->data[i]);
  }
  free(l);
  l = createArray();
}
