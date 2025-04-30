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
SU *SU_inserer_debut(SU *root, char *phrase);
void aff_su(SU *root);
// -------------

// la fontion principale de la'analyseur lexical
UL *analyseur_lexical(char *phrase, UL *root, SU **err_list);

// les états de l automates :
#define Q0 0
#define Q1 1
#define Q2 2

// codes des leximes
#define FIN_SUITE_UL 999 
#define ERREUR -1 
#endif
