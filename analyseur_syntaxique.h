#ifndef ANALYSEUR_SYNTAXIQUE_H
#define ANALYSEUR_SYNTAXIQUE_H

#include "analyseur_lexical.h"
#include "lexime.h"

// === les non terminaux : 
#define NT_DO_WHILE         200
#define NT_STATEMENTS       201
#define NT_STATEMENT        202
#define NT_DECLARE_STMT     203
#define NT_TYPE             204
#define NT_EXPRESSION       205
#define NT_OPERAND          206
#define NT_OPERATION        207
#define NT_INCREMENT_STMT   208
#define NT_DECREMENT_STMT   209
#define NT_CONDITION        210
#define NT_REL_OP           211
#define NT_BOOL_OP          212


#define NUMBER_OF_NON_TERMINALS  13

// Prototypes des fonctions de l'analyseur syntaxique
int est_mot_cle(const char *mot);                      // Vérifie si un lexème est un mot clé comme 'do' ou 'while'
int est_identificateur(const char *mot);               // Vérifie si un lexème est un identificateur valide
int est_operateur(const char *mot);                    // Vérifie si un lexème est un opérateur logique/comparatif
int est_constante(const char *mot);                    // Vérifie si un lexème est une constante entière

// Fonction principale pour analyser la structure do-while
                   // Analyse la syntaxe d'une boucle do-while
int analyseur_syntaxique(UL *root,ULPile * pile);
#endif // ANALYSEUR_SYNTAXIQUE_H
