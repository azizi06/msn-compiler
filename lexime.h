#ifndef LEXIME_H
#define LEXIME_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LEXEME_SIZE  50
#define BUFFER_SIZE  256

// === Structure d'une unité lexicale
typedef struct Unite_Lexicale {
    char Lexeme[LEXEME_SIZE];   // Le texte du lexème (ex: "do", "++", "var1", "5")
    int Code;                   // Le code lexical défini ci-dessus
    int Ligne;       // Numéro de ligne dans le fichier source
    struct Unite_Lexicale* Suivant;            
}UL;


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
