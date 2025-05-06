#include "analyseur_syntaxique.h"
#include <string.h>
#include <stdio.h>

// === les non terminaux

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



static const int RPs[][10] = {
    /*  0 */ { CODE_DO, CODE_ACCOLADE_OUVRANTE, NT_STATEMENTS, CODE_ACCOLADE_FERMANTE, 
              CODE_WHILE, CODE_PARENTHESE_OUVRANTE, NT_CONDITION, CODE_PARENTHESE_FERMANTE, CODE_PV, -1 },
    /*  1 */ { NT_STATEMENT, NT_STATEMENTS, -1 },
    /*  2 */ { CODE_EPSILON, -1 },  // ε production for <statements>
    /*  3 */ { NT_INCREMENT_STMT, -1 },
    /*  4 */ { NT_DECREMENT_STMT, -1 },
    /*  5 */ { NT_DECLARE_STMT, -1 },
    /*  6 */ { CODE_INT, CODE_ID, CODE_AFFECTATION, CODE_INT_CONST, CODE_PV, -1 },
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
    /* 26 */ { CODE_OR, -1 },
    /* 27 */ {CODE_ID, -1 },
    /* 28 */ {CODE_INT_CONST, -1 },
    /* 29 */ {CODE_PLUSPLUS,CODE_ID ,CODE_PV, -1},
    /* 30 */ {CODE_MINUSMINUS,CODE_ID ,CODE_PV, -1},



};

int Table_DAnalyse[NUMBER_OF_NON_TERMINALS][NUMBER_OF_TERMINALS] = {
    // Columns:                        /*0*/do  /*1*/while  /*2*/id  /*3*/int  /*4*/char  /*5*/;  /*6*/{  /*7*/}  /*8*/(  /*9*/ )  /*10*/=  /*11*/+  /*12*/-  /*13*/ *  /*14*/ /  /*15*/++  /*16*/--  /*17*/==  /*18*/!=  /*19*/<  /*20*/>  /*21*/<=  /*22*/>=  /*23*/&&  /*24*/||  /*25*/int_const  /*26*/string  /*27*/,  /*28*/.
    { /* Row for <do_while> */       /*0*/ 0,    /*1*/ ERREUR, /*2*/ ERREUR, /*3*/ ERREUR, /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <statements> */     /*0*/ 1,    /*1*/ ERREUR, /*2*/ ERREUR, /*3*/ 1,      /*4*/ 1,      /*5*/ ERREUR, /*6*/ 2,      /*7*/ 2,      /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ 1, /*16*/ 1, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <statement> */      /*0*/ ERREUR, /*1*/ ERREUR, /*2*/ 3,      /*3*/ 5,      /*4*/ 5,      /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ 3, /*16*/ 4, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ 3,      /*20*/ 4,      /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <declare_stmt> */   /*0*/ ERREUR, /*1*/ ERREUR, /*2*/ ERREUR, /*3*/ 6,      /*4*/ 7,      /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <type> */           /*0*/ ERREUR, /*1*/ ERREUR, /*2*/ 7,      /*3*/ ERREUR, /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <expression> */     /*0*/ 8,      /*1*/ ERREUR, /*2*/ 9,      /*3*/ ERREUR, /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <operand> */        /*0*/ ERREUR, /*1*/ ERREUR, /*2*/ 27,     /*3*/ 12,     /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ 28, /*26*/ ERREUR,     /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <operation> */      /*0*/ ERREUR, /*1*/ ERREUR, /*2*/ ERREUR, /*3*/ ERREUR, /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ 19, /*18*/ 20,     /*19*/ 21,     /*20*/ 22,     /*21*/ 23,     /*22*/ 24,     /*23*/ ERREUR,     /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <increment_stmt> */ /*0*/ 17,     /*1*/ ERREUR, /*2*/ ERREUR, /*3*/ ERREUR, /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ 29, /*16*/ 30, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <decrement_stmt> */ /*0*/ 18,     /*1*/ ERREUR, /*2*/ ERREUR, /*3*/ ERREUR, /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <condition> */      /*0*/ ERREUR, /*1*/ ERREUR, /*2*/ 11,     /*3*/ ERREUR, /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ 19,     /*9*/ 20,     /*10*/ 21,     /*11*/ 22,     /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ 11,     /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <rel_op> */         /*0*/ ERREUR, /*1*/ ERREUR, /*2*/ 25,     /*3*/ 26,     /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ ERREUR, /*14*/ ERREUR, /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR },
    { /* Row for <bool_op> */        /*0*/ ERREUR, /*1*/ ERREUR, /*2*/ ERREUR, /*3*/ ERREUR, /*4*/ ERREUR, /*5*/ ERREUR, /*6*/ ERREUR, /*7*/ ERREUR, /*8*/ ERREUR, /*9*/ ERREUR, /*10*/ ERREUR, /*11*/ ERREUR, /*12*/ ERREUR, /*13*/ 27,     /*14*/ 28,     /*15*/ ERREUR, /*16*/ ERREUR, /*17*/ ERREUR, /*18*/ ERREUR, /*19*/ ERREUR, /*20*/ ERREUR, /*21*/ ERREUR, /*22*/ ERREUR, /*23*/ ERREUR, /*24*/ ERREUR, /*25*/ ERREUR, /*26*/ ERREUR, /*27*/ ERREUR, /*28*/ ERREUR }
};




int analyseSyntaxique(ULPile* pile, UL* ul) {
    printf("\n-----------------------------------PILE-----------------------------------------------");

    printf("\nPile: ");
    aff_ulPile(pile);
    printf("\n-------------------------------------------------------------------------------------\n");

    printf("\n------------------------------------SUIT UL----------------------------------------------");
    printf("SuiteUL: ");
    aff_lexims(ul);
    printf("\n-------------------------------------------------------------------------------------\n");

    int i = 0;

    while (pile->sommet->Code != FIN_SUITE_UL && ul->Code != FIN_SUITE_UL) {
        UL* e1 = ul;              // Token courant
        UL* e2 = pile->sommet;    // Sommet de la pile

        printf("%d  suite ul %d , pile %d\n", i, e1->Code, e2->Code);

        if (e2->Code == CODE_EPSILON) {
            pile = pop_ul(pile);
            //pile = pop_ul(pile);
           // pile = pop_ul(pile);


            //ul = ul->Suivant;
            continue;
        }

        if (e1->Code == e2->Code) {
            pile = pop_ul(pile);
            ul = ul->Suivant;
        }
        else if (e2->Code >= 200) {
            int ligne = e2->Code - 200;
            int colonne = e1->Code - 100;

            if (colonne < 0 || colonne >= NUMBER_OF_TERMINALS) {
                printf("Erreur : Code terminal [%d] hors limite\n", colonne);
                return 1;
            }

            int CodeRP = Table_DAnalyse[ligne][colonne];
            printf("\tla RP choisi %d",CodeRP);
            

            if (CodeRP != ERREUR) {
                pile = pop_ul(pile);

                // Empile les symboles de la règle en ordre inverse
                int longueur = 1;
                while (RPs[CodeRP][longueur] != -1) {
                    longueur++;
                }
                for (int j = longueur - 1; j >= 0; j--) {
                    int symbole = RPs[CodeRP][j];   
                    if(symbole != CODE_EPSILON){

                    }
                        pile = push_ul(pile, "", symbole, 0);
                    
                }
            }
            else {
                printf("Erreur syntaxique à la ligne %d, colonne %d\n", ligne, colonne);
                return 1;
            }
        }
        else {
            printf("Erreur : Symbole inattendu dans la pile.\n");
            return 1;
        }

        i++;
        printf("\n-----------------------------------PILE-----------------------------------------------");

    printf("\nPile: ");
    aff_ulPile(pile);
    printf("\n-------------------------------------------------------------------------------------\n");

    printf("\n------------------------------------SUIT UL----------------------------------------------");
    printf("SuiteUL: ");
    aff_lexims(ul);
    printf("\n-------------------------------------------------------------------------------------\n");

       
        printf("-------------------------------------------------------------------------------------\n");
    }

    if (ul->Code == FIN_SUITE_UL && pile->sommet->Code == FIN_SUITE_UL) {
        printf("Analyse syntaxique terminée avec succès.\n");
        return 0;
    }
    else {
        printf("Erreur : analyse incomplète ou pile non vide.\n");
        return 1;
    }
}



int analyseur_syntaxique(UL *root,ULPile * pile) {
aff_ulPile(pile);
//aff_lexims(root);
    if (analyseSyntaxique(pile,root) == 0) {
        printf("La structure do-while est syntaxiquement correcte yy.\n");
        return 0;
    } else {
        printf("Le programme ne respecte pas la syntaxe attendue pour 'do-while'.\n");
        return 1;

    }
}
