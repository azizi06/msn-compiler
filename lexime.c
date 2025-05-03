#include "lexime.h"

// === Fonction pour insérer un lexème à la fin de la liste chaînée
UL* inserer_fin(UL* root, char* lexime, int code, int ligne) {
    UL* nlexime = malloc(sizeof(UL));
    if (!nlexime) {
        printf("Erreur d'allocation memoire\n");
        return root;
    }
    nlexime->Code = code;
    strncpy(nlexime->Lexeme, lexime, sizeof(nlexime->Lexeme));
    nlexime->Ligne = ligne;
    nlexime->Suivant = NULL;

    if (!root) {
        return nlexime;
    }

    UL* current = root;
    while (current->Suivant != NULL) {
        current = current->Suivant;
    }
    current->Suivant = nlexime;
    return root;
}

// === Fonction pour insérer un lexème au début de la liste chaînée
UL* inserer_debut(UL* root, char* lexime, int code, int ligne) {
    UL* nlexime = malloc(sizeof(UL));
    if (nlexime == NULL) {
        printf("Erreur d'allocation memoire\n");
        return root;
    }
    nlexime->Code = code;
    strncpy(nlexime->Lexeme, lexime, sizeof(nlexime->Lexeme));
    nlexime->Ligne = ligne;
    nlexime->Suivant = root;
    return nlexime;
}

// === Fonction pour afficher les lexèmes dans la liste chaînée
void aff_lexims(UL *root) {
    UL* current = root;
    while (current != NULL) {
        printf("\nLexeme: [%s]  Code: [%d]  Ligne: [%d]", current->Lexeme, current->Code, current->Ligne);
        current = current->Suivant;
    }
}

// === Fonction pour gérer la pile des lexèmes (pour l'analyse syntaxique, par exemple)
ULPile* push_ul(ULPile *root, char* lexime, int code, int ligne) {
    UL* nlexime = malloc(sizeof(UL));
    if (nlexime == NULL) {
        printf("Erreur d'allocation memoire pour le lexeme\n");
        return root;
    }
    nlexime->Code = code;
    strncpy(nlexime->Lexeme, lexime, sizeof(nlexime->Lexeme));
    nlexime->Ligne = ligne;
    nlexime->Suivant = root->sommet;
    
    root->sommet = nlexime;
    root->size++;
    return root;
}

// === Fonction pour supprimer le sommet de la pile
ULPile* pop_ul(ULPile *root) {
    if (root->size == 0) {
        printf("La pile est vide, impossible de depiler\n");
        return root;
    }

    UL* temp = root->sommet;
    root->sommet = root->sommet->Suivant;
    free(temp);
    root->size--;
    return root;
}

// === Fonction pour afficher les éléments de la pile
void aff_ulPile(ULPile *root) {
    UL* current = root->sommet;
    while (current != NULL) {
        printf("\nPile: Lexeme: [%s]  Code: [%d]  Ligne: [%d]", current->Lexeme, current->Code, current->Ligne);
        current = current->Suivant;
    }
}

// === Fonction pour libérer la pile
void free_ulPile(ULPile *root) {
    UL* current = root->sommet;
    UL* temp;
    while (current != NULL) {
        temp = current;
        current = current->Suivant;
        free(temp);
    }
    free(root);
}
