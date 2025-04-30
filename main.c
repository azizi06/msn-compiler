#include "analyseur_lexical.h"
#include "analyseur_syntaxique.h"
#include "lexime.h"



int main(int argc, char *argv[]){
    if (argc < 2)
    {
      printf("Error : saisie le fichier du code source");
      return 1;
    }
    char* data = read_file(argv[1]); 
// === analyseure lexicale :
    SU *err_list = NULL;
    UL *root = NULL;
    root = analyseur_lexical(data, root, &err_list);
    printf("\n=== analyseure lexicale === : ");
    aff_lexims(root);
    aff_su(err_list);
// === analyseure syntaxique :
    ULPile* pile = (ULPile*) malloc(sizeof(ULPile));  
    if (pile == NULL) {
        printf("err allocation memoire : Upile\n");
        return 1; 
    }
    pile->sommet = NULL;  

    printf("\n=== analyseur syntaxique === : ");
    pile = push_ul(pile,"az",3,4);
    pile = push_ul(pile,"aze",3,4);
    pile = push_ul(pile,"mi",36,4);
    pile = push_ul(pile,"23",4,4);
    aff_ulPile(pile);

    

    return 0;
}