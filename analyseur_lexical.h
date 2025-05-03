#ifndef ANALYSEUR_LEXICAL_H
#define ANALYSEUR_LEXICAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexime.h"

// === Constantes de taille
#define BUFFER_SIZE 256

// === Structure pour stocker les erreurs lexicales (SU = String Unit)
typedef struct SU {
    char data[BUFFER_SIZE];  // Message d'erreur
    struct SU *suivant;
} SU;

// === Fonctions utilitaires
int isIn(char c, const char str[]);
char *read_file(const char *filename);

// === Fonctions pour la gestion des erreurs
SU *SU_inserer_debut(SU *root, char *phrase);
void aff_su(SU *root);

// === Fonction principale de l'analyseur lexical
UL *analyseur_lexical(char *phrase, UL *root, SU **err_list);
void ajouter_token(UL **root, const char *lexeme, int code, int ligne);

// === États de l'automate (optionnel, non utilisé dans version actuelle)
#define Q0  0
#define Q1  1
#define Q2  2
#define Q3  3
#define Q4  4

// === Codes symboliques pour les lexèmes
// Codes pour chaque type de lexème
#define CODE_DO        100
#define CODE_WHILE     101
#define CODE_IDF       102
#define CODE_INT_CONST 103
#define CODE_PV        104
#define CODE_INCR      105
#define CODE_INF       106
#define CODE_STRING    107
#define CODE_EQ        108
#define CODE_NEQ       109
#define CODE_AND       110
#define CODE_OR        111
#define CODE_FOR       112
#define CODE_IF        113
#define CODE_RETURN    114
#define CODE_INT       115
#define CODE_PLUS      116
#define CODE_DELIM     117
#define CODE_PAR       118

#define PLUSPLUS    5  // ++
#define EGAL        19 // ==
#define AFF         11 // =
#define PLUS 21  // Code pour l'opérateur '+'

#define CODE_AFFECT 120  // =

#define MINUSMINUS 6
#define MINUS 7
#define SUP 8


// Définir les codes pour les symboles
#define CODE_MODULO 130  // Code pour le symbole '%'
#define CODE_VIRGULE 131  // Code pour la virgule
// Définir le code pour le caractère '.'
#define CODE_POINT 132  // Code pour le symbole '.'







#define FIN_SUITE_UL           999
#define ERREUR                 -1


// === Liste des mots-clés à reconnaître
#define DO_KEYWORD     "do"
#define WHILE_KEYWORD  "while"
#define IF_KEYWORD     "if"
#define FOR_KEYWORD    "for"
#define RETURN_KEYWORD "return"
#define INT_KEYWORD    "int"

// === Liste des opérateurs
#define AND_OPERATOR  "&&"
#define OR_OPERATOR   "||"
#define INC_OPERATOR  "++"
#define DEC_OPERATOR  "--"
#define EQ_OPERATOR   "=="
#define NEQ_OPERATOR  "!="


#endif // ANALYSEUR_LEXICAL_H
