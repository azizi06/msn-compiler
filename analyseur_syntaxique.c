#include "analyseur_syntaxique.h"
#include <string.h>
#include <stdio.h>







static const int RPs[][10] = {
    /*  0 */ { CODE_DO, CODE_ACCOLADE_OUVRANTE, NT_STATEMENTS, CODE_ACCOLADE_FERMANTE, 
              CODE_WHILE, CODE_PARENTHESE_OUVRANTE, NT_CONDITION, CODE_PARENTHESE_FERMANTE, CODE_PV, -1 },
    /*  1 */ { NT_STATEMENT, NT_STATEMENTS, -1 },
    /*  2 */ { CODE_EPSILON, -1 },  // ε production for <statements>
    /*  3 */ { NT_INCREMENT_STMT, -1 },
    /*  4 */ { NT_DECREMENT_STMT, -1 },
    /*  5 */ { NT_DECLARE_STMT, -1 },
    /*  6 */ { CODE_INT, CODE_ID, CODE_AFFECTATION, NT_EXPRESSION, CODE_PV, -1 },
    /*  7 */ { CODE_CHAR, CODE_ID, CODE_AFFECTATION, CODE_STRING, CODE_PV, -1 },
    /*  8 */ { NT_TYPE, CODE_ID, CODE_PV, -1 },
    /*  9 */ { CODE_INT, -1 },
    /* 10 */ { CODE_CHAR, -1 },
    /* 11 */ { NT_OPERAND, NT_OPERATION, NT_OPERAND, -1 },
    /* 12 */ { CODE_PLUS, -1 },
    /* 13 */ { CODE_MINUS, -1 },
    /* 14 */ { CODE_MULTIPLY, -1 },
    /* 15 */ { CODE_DIVIDE, -1 },
    /* 16 */ { CODE_ID, CODE_PLUSPLUS, CODE_PV, -1 },
    /* 17 */ { CODE_ID, CODE_MINUSMINUS, CODE_PV, -1 },
    /* 18 */ { NT_OPERAND, NT_REL_OP, NT_OPERAND, -1 },
    /* 19 */ { CODE_EQ, -1 },
    /* 20 */ { CODE_NEQ, -1 },
    /* 21 */ { CODE_INF, -1 },
    /* 22 */ { CODE_SUP, -1 },
    /* 23 */ { CODE_LEQ, -1 },
    /* 24 */ { CODE_GEQ, -1 },
    /* 25 */ { CODE_AND, -1 },
    /* 26 */ { CODE_OR, -1 }
};

int Table_DAnalyse[NUMBER_OF_NON_TERMINALS][NUMBER_OF_TERMINALS] = {
    // Columns:       do   while   id   int   char   ;   {   }   (   )   =   +   -   *   /   ++   --   ==   !=   <   >   <=   >=   &&   ||   int_const   string   ,   .
    { /* Row for <do_while> */        0,  ERREUR, ERREUR,  ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <statements> */      1,  ERREUR,  ERREUR,  ERREUR, ERREUR, ERREUR, 2,  ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <statement> */       ERREUR, ERREUR, 3, 4, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <declare_stmt> */    ERREUR, ERREUR, ERREUR, 5, 6, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <type> */            ERREUR, ERREUR, 7, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <expression> */      8, ERREUR, 9, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <operand> */         10, ERREUR, 11, 12, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <operation> */       13, 14, 15, 16, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <increment_stmt> */  17, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <decrement_stmt> */  18, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <condition> */       ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, 19, 20, 21, 22, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <rel_op> */          23, 24, 25, 26, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR},
    { /* Row for <bool_op> */         ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, 27, 28, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR, ERREUR}
};


int analyseSyntaxique(ULPile* pile, UL* ul) {
    int i = 1;
    printf("\nPile: ");
    aff_ulPile(pile);
    printf("SuiteUL: ");
    aff_lexims(ul);
    printf("-------------------------------------------------------------------------------------\n");
    UL* current = ul;
    while ( ul->Code != FIN_SUITE_UL ||   pile->sommet->Code != FIN_SUITE_UL) {
       // printf("Iteration %d :\n", i++);
        UL* e1 = current;
        UL* e2 = pile->sommet;
 
     //   printf("SuiteUL: %s\tPile: %s\n", getNom(e1->Code, e1->Lexeme), getNom(e2->Code, e2->Lexeme));
 
        if (e1->Code == e2->Code) {
          //  printf("Depiler et suprimer de la SuiteUL: %s (Action1)\n", getNom(e1->Code, e1->Lexeme));
           // depiler(pile);
             pile  =pop_ul(pile);

           // supprimerUL(ul);
        } else if (e2->Code <= 200) { // C'est un non-terminal
            int ligne = e2->Code;
            int colonne = e1->Code - 200;
            int CodeRP = Table_DAnalyse[ligne][colonne];
 
            if (CodeRP != ERREUR) {
             //   printf("Table_DAnalyse[ %d, %d ] = %d\n", ligne, colonne, codeRP);
              //  printf("Depiler %s & Empiler RP=%d (Action2)\n", getNom(e2->code, e2->Lexeme), codeRP);
                //depiler(pile);
                pop_ul(pile);
                for (int i = 4; i >= 0; i--) {
                    int sym = RPs[CodeRP][i];
                    if (sym != -1 && sym != CODE_EPSILON) {
                        
                    }
                }
            } else {
                printf("Erreur syntaxique\n");
                return;
            }
        } else {
            printf("Erreur syntaxique\n");
            return;
        }
 
        printf("Pile: ");
        aff_ulPile(pile);
        printf("SuiteUL: ");
        aff_lexims(ul);
        printf("-------------------------------------------------------------------------------------\n");
    }
 
    printf("\nAnalyse Syntaxique Reussie\n");
    return 0;
}


int analyseur_syntaxique(UL *root,ULPile * pile) {

    if (analyseSyntaxique(root,pile) == 0) {
        printf("Le programme ne respecte pas la syntaxe attendue pour 'do-while'.\n");
        return 0;
    } else {
        printf("La structure do-while est syntaxiquement correcte.\n");
        return 1;

    }
}
