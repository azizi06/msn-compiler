#include "analyseur_lexical.h"
#include "analyseur_syntaxique.h"
#include "lexime.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Erreur : veuillez fournir le fichier du code source.\n");
        return 1;
    }

    // Lecture du fichier source
    char *data = read_file(argv[1]);
    if (!data) {
        return 1;
    }

    // === Analyseur lexical ===
    SU *err_list = NULL;
    UL *root = NULL;

    root = analyseur_lexical(data, root, &err_list);

    printf("\n=== Analyseur Lexical ===\n");
    aff_lexims(root);
    aff_su(err_list);

    // === Vérification des erreurs lexicales ===
    if (err_list != NULL) {
        printf("\nErreur(s) lexicale(s) detectee(s). Compilation stoppee.\n");
        free(data);
        return 1;
    }
    printf("\n=== Analyseur Syntaxique ===\n");

    // === Analyseur syntaxique ===
    ULPile* pile = (ULPile*) malloc(sizeof(ULPile));
    UL* nlexime = malloc(sizeof(UL));
    if (!nlexime) {
        printf("Erreur d'allocation memoire\n");
        return -1;
    }
    nlexime->Code = FIN_SUITE_UL;
    strncpy(nlexime->Lexeme, "#", strlen("#"));
    nlexime->Ligne = -2;
    nlexime->Suivant = NULL;
    pile->sommet = nlexime;
    pile ->size = 0;
    push_ul(pile,"",NT_DO_WHILE,-1);

    aff_ulPile(pile);
    analyseur_syntaxique(root,pile);

    free(data);
    return 0;
}
