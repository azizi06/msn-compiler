#include "lexime.h"

UL* inserer_fin(UL* root,  char* lexime, int code, int ligne) {
    UL* nlexime = malloc(sizeof(UL));
    if (!nlexime) {
        printf("Erreur d'allocation mémoire\n");
        return root;
    }
    nlexime->Code = code;
    strncpy(nlexime->Lexeme,lexime,sizeof(nlexime->Lexeme));
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
  
  UL* inserer_debut(UL* root, char* lexime, int code, int ligne) {
    UL* nlexime = malloc(sizeof(UL));
    if (nlexime == NULL) {
        printf("Erreur d'allocation memoire\n");
        return root;
    }
    nlexime->Code = code;
    strncpy(nlexime->Lexeme,lexime,sizeof(nlexime->Lexeme));
    nlexime->Ligne = ligne;
    nlexime->Suivant = root;
    return nlexime;
  }
  
  void aff_lexims(UL *root) {
    UL* current = root;
    while (current != NULL) {
        printf("\nLexime: [%s]     Code:[%d]    Ligne[%d] ", current->Lexeme, current->Code, current->Ligne);
        current = current->Suivant;
    }
  }
  