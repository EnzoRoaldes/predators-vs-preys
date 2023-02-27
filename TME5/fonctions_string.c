#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "devel.h"

void *dupliquer_str(const void *src) {
  return strdup((char *) src);
}

void copier_str(const void *src, void *dst) {
  strcpy((char *) dst, (char *) src);
}

void detruire_str(void *data) {
  free(data);
}

void afficher_str(const void *data) {
  printf("%s\n", (char *) data);
}

int comparer_str(const void *a, const void *b) {
  return strcmp((char *) a, (char *) b);
}

int ecrire_str(const void *data, FILE *f) {
  return fprintf(f, "%s", (char *) data);
}

void *lire_str(FILE *f) {
  char *res = malloc(sizeof(char)*100);
  fscanf(f, "%s", res);
  return (void *) res;
}
