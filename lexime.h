#ifndef LEXIME_H
#define LEXIME_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LEXEME_SIZE  50
#define BUFFER_SIZE  256

<<<<<<< Updated upstream
// === CODES LEXICAUX POUR CHAQUE TYPE DE LEXÈME (uniformisés)

// Mots-clés
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

#define PLUS 21       // Code pour '+'
#define PLUSPLUS 5    // Code pour '++'
#define EGAL 19       // Code pour '=='
#define AFF 11        // Code pour '='


#define FIN_SUITE_UL   999
#define ERREUR         -1

// === DÉFINITIONS DES MOTS-CLÉS ET OPÉRATEURS (pour comparaison)
#define DO_KEYWORD       "do"
#define WHILE_KEYWORD    "while"
#define IF_KEYWORD       "if"
#define FOR_KEYWORD      "for"
#define RETURN_KEYWORD   "return"
#define INT_KEYWORD      "int"

#define AND_OPERATOR     "&&"
#define OR_OPERATOR      "||"
#define INC_OPERATOR     "++"
#define DEC_OPERATOR     "--"
#define EQ_OPERATOR      "=="
#define NEQ_OPERATOR     "!="

// === Structure d'une unité lexicale
typedef struct Unite_Lexicale {
    char Lexeme[LEXEME_SIZE];   // Le texte du lexème (ex: "do", "++", "var1", "5")
    int Code;                   // Le code lexical défini ci-dessus
    int Ligne;                  // Numéro de ligne dans le fichier source
=======
typedef struct Unite_Lexicale { 
    char   Lexeme[LEXEME_SIZE]; 
    int    Code; 
    int    Ligne; 
>>>>>>> Stashed changes
    struct Unite_Lexicale* Suivant; 
} UL;

// === Liste chaînée des unités lexicales
UL* inserer_debut(UL* root, char* lexeme, int code, int ligne);
UL* inserer_fin(UL* root, char* lexeme, int code, int ligne);
void aff_lexims(UL *root);

// === PILE POUR L’ANALYSE SYNTAXIQUE (optionnel)
typedef struct ULPile {
    int size;
    UL* sommet;
} ULPile;

ULPile* push_ul(ULPile *root, char* lexeme, int code, int ligne);  // empiler
ULPile* pop_ul(ULPile *root);                                      // dépiler
void aff_ulPile(ULPile *root);
void free_ulPile(ULPile *root);
// ---------------------------------

#endif
