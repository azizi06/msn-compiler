#include "analyseur_syntaxique.h"
#include <string.h>
#include <stdio.h>

int analyser_bloc_instructions(UL **current) {
    while (*current != NULL && strcmp((*current)->Lexeme, "}") != 0) {
        if (strcmp((*current)->Lexeme, "printf") == 0) {
            int ligne = (*current)->Ligne;
            *current = (*current)->Suivant;
            if (*current == NULL || strcmp((*current)->Lexeme, "(") != 0) {
                printf("Erreur syntaxique (ligne %d) : '(' attendu apres 'printf'.\n", ligne);
                return 0;
            }
            *current = (*current)->Suivant;
            while (*current != NULL && strcmp((*current)->Lexeme, ")") != 0) {
                *current = (*current)->Suivant;
            }
            if (*current == NULL || strcmp((*current)->Lexeme, ")") != 0) {
                printf("Erreur syntaxique (ligne %d) : ')' attendu apres 'printf'.\n", ligne);
                return 0;
            }
            *current = (*current)->Suivant;
            if (*current == NULL || strcmp((*current)->Lexeme, ";") != 0) {
                printf("Erreur syntaxique (ligne %d) : ';' attendu apres 'printf'.\n", ligne);
                return 0;
            }
            *current = (*current)->Suivant;
        } else if ((*current)->Code == 102) {
            int ligne = (*current)->Ligne;
            *current = (*current)->Suivant;
            if (*current != NULL && strcmp((*current)->Lexeme, "++") == 0) {
                *current = (*current)->Suivant;
                if (*current == NULL || strcmp((*current)->Lexeme, ";") != 0) {
                    printf("Erreur syntaxique (ligne %d) : ';' attendu apres '++'.\n", ligne);
                    return 0;
                }
                *current = (*current)->Suivant;
            } else {
                printf("Erreur syntaxique (ligne %d) : '++' attendu apres identifiant.\n", ligne);
                return 0;
            }
        } else {
            printf("Erreur syntaxique (ligne %d) : instruction invalide dans le bloc 'do'.\n", (*current)->Ligne);
            return 0;
        }
    }

    if (*current == NULL || strcmp((*current)->Lexeme, "}") != 0) {
        printf("Erreur syntaxique : '}' manquant à la fin du bloc 'do'.\n");
        return 0;
    }

    return 1;
}

int analyser_do_while(UL *root) {
    UL *current = root;
    int etat = 0;

    while (current != NULL) {
        switch (etat) {
            case 0:
                if (strcmp(current->Lexeme, "do") == 0) {
                    etat = 1;
                    current = current->Suivant;
                } else {
                    printf("Erreur (ligne %d) : 'do' attendu.\n", current ? current->Ligne : -1);
                    return 0;
                }
                break;

            case 1:
                if (strcmp(current->Lexeme, "{") == 0) {
                    etat = 2;
                    current = current->Suivant;
                } else {
                    printf("Erreur (ligne %d) : '{' attendu apres 'do'.\n", current ? current->Ligne : -1);
                    return 0;
                }
                break;

            case 2:
                if (!analyser_bloc_instructions(&current)) {
                    return 0;
                }
                if (current == NULL || strcmp(current->Lexeme, "}") != 0) {
                    printf("Erreur (ligne %d) : '}' attendu à la fin du bloc.\n", current ? current->Ligne : -1);
                    return 0;
                }
                etat = 3;
                current = current->Suivant;
                break;

            case 3:
                if (strcmp(current->Lexeme, "while") == 0) {
                    etat = 4;
                    current = current->Suivant;
                } else {
                    printf("Erreur (ligne %d) : 'while' attendu apres le bloc 'do'.\n", current ? current->Ligne : -1);
                    return 0;
                }
                break;

            case 4:
                if (strcmp(current->Lexeme, "(") == 0) {
                    etat = 5;
                    current = current->Suivant;
                } else {
                    printf("Erreur (ligne %d) : '(' attendu apres 'while'.\n", current ? current->Ligne : -1);
                    return 0;
                }
                break;

            case 5:
                if (current->Code == 102) {
                    current = current->Suivant;
                    if (current == NULL || strcmp(current->Lexeme, "<") != 0) {
                        printf("Erreur (ligne %d) : '<' attendu apres identifiant.\n", current ? current->Ligne : -1);
                        return 0;
                    }
                    current = current->Suivant;
                    if (current == NULL || current->Code != 103) {
                        printf("Erreur (ligne %d) : constante entiere attendue apres '<'.\n", current ? current->Ligne : -1);
                        return 0;
                    }
                    etat = 6;
                    current = current->Suivant;
                } else {
                    printf("Erreur (ligne %d) : identifiant attendu dans la condition.\n", current ? current->Ligne : -1);
                    return 0;
                }
                break;

            case 6:
                if (strcmp(current->Lexeme, ")") == 0) {
                    etat = 7;
                    current = current->Suivant;
                } else {
                    printf("Erreur (ligne %d) : ')' attendu apres condition.\n", current ? current->Ligne : -1);
                    return 0;
                }
                break;

            case 7:
                if (strcmp(current->Lexeme, ";") == 0) {
                    printf("Syntaxe correcte : boucle 'do-while' reconnue.\n");
                    return 1;
                } else {
                    printf("Erreur (ligne %d) : ';' attendu apres 'while(...)'.\n", current ? current->Ligne : -1);
                    return 0;
                }

            default:
                printf("Erreur : etat inconnu.\n");
                return 0;
        }
    }

    printf("Erreur : fin de fichier inattendue.\n");
    return 0;
}

void analyseur_syntaxique(UL *root) {
    if (!analyser_do_while(root)) {
        printf("Le programme ne respecte pas la syntaxe attendue pour 'do-while'.\n");
    } else {
        printf("La structure do-while est syntaxiquement correcte.\n");
    }
}
