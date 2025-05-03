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

    // === Analyseur syntaxique ===
    printf("\n=== Analyseur Syntaxique ===\n");

    if (analyser_do_while(root)) {
        printf("La structure do-while est syntaxiquement correcte.\n");
    } else {
        printf("Erreur syntaxique dans la structure do-while.\n");
    }

    free(data);
    return 0;
}
