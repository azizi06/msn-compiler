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

// === Symbolic Codes for Lexemes (Terminals) ===

// --- Keywords ---
#define CODE_DO                  100  // "do"
#define CODE_WHILE               101  // "while"

// --- Identifiers & Constants ---
#define CODE_ID                  102  // identifier
#define CODE_INT                 103  // "int"
#define CODE_CHAR                104  // "char"

// --- Delimiters ---
#define CODE_PV                  105  // ;
#define CODE_ACCOLADE_OUVRANTE   106  // {
#define CODE_ACCOLADE_FERMANTE   107  // }
#define CODE_PARENTHESE_OUVRANTE 108  // (
#define CODE_PARENTHESE_FERMANTE 109  // )
#define CODE_AFFECTATION         110  // =

// --- Arithmetic Operators ---
#define CODE_PLUS                111  // +
#define CODE_MINUS               112  // -
#define CODE_MULTIPLY            113  // *
#define CODE_DIVIDE              114  // /
#define CODE_PLUSPLUS            115  // ++
#define CODE_MINUSMINUS          116  // --

// --- Relational Operators ---
#define CODE_EQ                  117  // ==
#define CODE_NEQ                 118  // !=
#define CODE_INF                 119  // <
#define CODE_SUP                 120  // >
#define CODE_LEQ                 121  // <=
#define CODE_GEQ                 122  // >=

// --- Logical Operators ---
#define CODE_AND                 123  // &&
#define CODE_OR                  124  // ||

// --- Constants ---
#define CODE_INT_CONST           125  // integer constant
#define CODE_STRING              126  // string literal

// --- Other Symbols (Optional) ---
#define CODE_VIRGULE             127  // ,
#define CODE_POINT               128  // .

// --- Control / Special ---
#define CODE_EPSILON             129  // ε (internal use)
#define FIN_SUITE_UL             999  // #
#define ERREUR                  -1

// --- Special Control Codes ---
#define FIN_SUITE_UL             999  // #
#define ERREUR                   -1  // Error code

// --- Keyword Strings for Lexer (if needed) ---
#define DO_KEYWORD               "do"
#define WHILE_KEYWORD            "while"
#define CHAR_KEYWORD             "char"
#define INT_KEYWORD              "int"
#define RETURN_KEYWORD           "return"

// --- Operator Strings for Lexer (if needed) ---
#define AND_OPERATOR             "&&"
#define OR_OPERATOR              "||"
#define INC_OPERATOR             "++"
#define DEC_OPERATOR             "--"
#define EQ_OPERATOR              "=="
#define NEQ_OPERATOR             "!="

#define   NUMBER_OF_TERMINALS          34


#endif // ANALYSEUR_LEXICAL_H
