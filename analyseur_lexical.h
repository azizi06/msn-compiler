#ifndef ANALYSEUR_LEXICAL_H
#define ANALYSEUR_LEXICAL_H
#include "lexime.h"


int isIn(char c, const char str[]);
char *read_file(const char *filename);

// une structure de donne pour stokes les msg SU : string unit
typedef struct SU{
    char data[BUFFER_SIZE];
    struct SU *suivant;
  } SU;
#endif
