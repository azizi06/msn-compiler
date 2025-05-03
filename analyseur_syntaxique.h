#ifndef ANALYSEUR_SYNTAXIQUE_H
#define ANALYSEUR_SYNTAXIQUE_H

#include "analyseur_lexical.h"
#include "lexime.h"

// Prototypes des fonctions de l'analyseur syntaxique
int est_mot_cle(const char *mot);                      // Vérifie si un lexème est un mot clé comme 'do' ou 'while'
int est_identificateur(const char *mot);               // Vérifie si un lexème est un identificateur valide
int est_operateur(const char *mot);                    // Vérifie si un lexème est un opérateur logique/comparatif
int est_constante(const char *mot);                    // Vérifie si un lexème est une constante entière

// Fonction principale pour analyser la structure do-while
int analyser_do_while(UL *root);                       // Analyse la syntaxe d'une boucle do-while

#endif // ANALYSEUR_SYNTAXIQUE_H
