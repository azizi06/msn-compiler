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
#define CODE_INT                 102  // "int"
#define CODE_CHAR                103  // "char"
#define CODE_RETURN              104  // "return"

// --- Identifiers & Constants ---
#define CODE_ID                  105  // identifier
#define CODE_INT_CONST           106  // integer constant
#define CODE_STRING              107  // string literal

// --- Delimiters ---
#define CODE_PV                  108  // ;
#define CODE_ACCOLADE_OUVRANTE   109  // {
#define CODE_ACCOLADE_FERMANTE   110  // }
#define CODE_PARENTHESE_OUVRANTE 111  // (
#define CODE_PARENTHESE_FERMANTE 112  // )
#define CODE_AFFECTATION         113  // =

// --- Arithmetic Operators ---
#define CODE_PLUS                114  // +
#define CODE_MINUS               115  // -
#define CODE_MULTIPLY            116  // *
#define CODE_DIVIDE              117  // /
#define CODE_PLUSPLUS            118  // ++
#define CODE_MINUSMINUS          119  // --

// --- Relational Operators ---
#define CODE_SUP                 120  // >
#define CODE_INF                 121  // <
#define CODE_EQ                  122  // ==
#define CODE_NEQ                 123  // !=
#define CODE_LEQ                 124  // <=
#define CODE_GEQ                 125  // >=

// --- Logical Operators ---
#define CODE_AND                 126  // &&
#define CODE_OR                  127  // ||

// --- Other Symbols (Optional) ---
#define CODE_MODULO              128  // %
#define CODE_VIRGULE             129  // ,
#define CODE_POINT               130  // .
#define CODE_EPSILON             131  // ε (internal use)

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
