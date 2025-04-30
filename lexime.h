#ifndef LEIXIME_H
#define LEIXIME_H

#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define LEXEME_SIZE 20
#define BUFFER_SIZE 100

typedef struct Unite_Lexicale { 
    char   Lexeme[20]; 
    int    Code; 
    int    Ligne; 
    struct Unite_Lexicale* Suivant; 
} UL; 

// la liste chainée
UL* inserer_debut(UL* root,char* lexime,int code,int ligne);
UL* inserer_fin(UL* root,char* lexime,int code,int ligne);
void aff_lexims(UL *root);

// la pile
typedef struct ULPile{
    int size ;
    UL* sommet;
  
}ULPile;
ULPile* push_ul(ULPile *root,char* lexime,int code,int ligne);// ajouter debute
ULPile* pop_ul(ULPile *root); //suprimier premire
void aff_ulPile(ULPile *root);
void free_ulPile(ULPile *root);

#endif