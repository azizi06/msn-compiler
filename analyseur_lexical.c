#include "analyseur_lexical.h"

int isIn(char c, const char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            return 1;
        }
        i++;
    }
    return 0;
}

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(filesize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';
    fclose(file);
    return buffer;
}

SU *SU_inserer_debut(SU *root, char *phrase) {
    SU *nsu = malloc(sizeof(SU));
    strcpy(nsu->data, phrase);
    nsu->suivant = root;
    return nsu;
}

void aff_su(SU *root) {
    if (root == NULL) {
        printf("\nAucune erreur lexicale.");
    } else {
        SU *current = root;
        while (current != NULL) {
            printf("\nErreur lexicale: %s", current->data);
            current = current->suivant;
        }
    }
}

void ignorer_commentaire(char *phrase, int *i) {
  // Si c'est un commentaire sur une seule ligne (//)
  if (phrase[*i] == '/' && phrase[*i + 1] == '/') {
      while (phrase[*i] != '\n' && phrase[*i] != '\0') {
          (*i)++;  // Ignorer le commentaire jusqu'à la fin de la ligne
      }
  }
  // Si c'est un commentaire multi-lignes (/* */)
  else if (phrase[*i] == '/' && phrase[*i + 1] == '*') {
      (*i) += 2;  // Passer les deux premiers caractères "/*"
      while (!(phrase[*i] == '*' && phrase[*i + 1] == '/')) {
          if (phrase[*i] == '\0') {
              break;  // Si on arrive à la fin de la chaîne sans fermer le commentaire
          }
          (*i)++;
      }
      (*i) += 2;  // Passer les caractères "*/"
  }
}

UL *analyseur_lexical(char *phrase, UL *root, SU **err_list) {
  int i = 0, ligne = 1;
  char current;

  while ((current = phrase[i]) != '\0') {

      // Ignorer les commentaires sur une ligne
      if (phrase[i] == '/' && phrase[i + 1] == '/') {
        i += 2;
        while (phrase[i] != '\n' && phrase[i] != '\0') {
            i++;
        }
        continue;
      }

      // Ignorer les commentaires multilignes
      if (phrase[i] == '/' && phrase[i + 1] == '*') {
        i += 2;
        while (!(phrase[i] == '*' && phrase[i + 1] == '/') && phrase[i] != '\0') {
            if (phrase[i] == '\n') ligne++;  // Ne pas oublier d'incrémenter la ligne
            i++;
        }
        if (phrase[i] == '*' && phrase[i + 1] == '/') {
            i += 2;
        } else {
            *err_list = SU_inserer_debut(*err_list, "Erreur: commentaire non ferme");
        }
        continue;
      }


      // Gérer les sauts de ligne
      if (current == '\n') {
          ligne++;
          i++;
          continue;
      }

      // Ignorer les espaces
      if (isspace(current)) {
          i++;
          continue;
      }

      // Gestion des identifiants et mots-clés
      if (isalpha(current)) {
          char buffer[LEXEME_SIZE] = {0};
          int j = 0;
          while (isalnum(phrase[i]) || phrase[i] == '_') {
              buffer[j++] = phrase[i++];
          }
          buffer[j] = '\0';

          if (strcmp(buffer, DO_KEYWORD) == 0)
              root = inserer_fin(root, buffer, CODE_DO, ligne);
          else if (strcmp(buffer, WHILE_KEYWORD) == 0)
              root = inserer_fin(root, buffer, CODE_WHILE, ligne);
          else if (strcmp(buffer, IF_KEYWORD) == 0)
              root = inserer_fin(root, buffer, CODE_IF, ligne);
          else if (strcmp(buffer, FOR_KEYWORD) == 0)
              root = inserer_fin(root, buffer, CODE_FOR, ligne);
          else if (strcmp(buffer, RETURN_KEYWORD) == 0)
              root = inserer_fin(root, buffer, CODE_RETURN, ligne);
          else if (strcmp(buffer, INT_KEYWORD) == 0)
              root = inserer_fin(root, buffer, CODE_INT, ligne);
          else
              root = inserer_fin(root, buffer, CODE_IDF, ligne); // Identifiant

          continue;
      }

      // Gestion des constantes entières
      if (isdigit(current)) {
          char buffer[LEXEME_SIZE] = {0};
          int j = 0;
          while (isdigit(phrase[i])) {
              buffer[j++] = phrase[i++];
          }
          buffer[j] = '\0';
          root = inserer_fin(root, buffer, CODE_INT_CONST, ligne);
          continue;
      }

      // Gestion des chaînes de caractères
      if (current == '"') {
          char buffer[BUFFER_SIZE] = {0};
          int j = 0;
          buffer[j++] = phrase[i++];

          while (phrase[i] != '"' && phrase[i] != '\0') {
              buffer[j++] = phrase[i++];
          }

          if (phrase[i] == '"') {
              buffer[j++] = phrase[i++];
              buffer[j] = '\0';
              root = inserer_fin(root, buffer, CODE_STRING, ligne);
          } else {
              *err_list = SU_inserer_debut(*err_list, "Erreur: chaine non fermee");
          }
          continue;
      }

      // Vérification des opérateurs d'incrémentation (++)
      if (current == '+') {
          if (phrase[i + 1] == '+') {
              root = inserer_fin(root, "++", PLUSPLUS, ligne);
              i += 2;  // Avancer de 2 caractères
          } else {
              root = inserer_fin(root, "+", PLUS, ligne);
              i++;
          }
          continue;
      }
      if (current == '-') {
        if (phrase[i + 1] == '-') {
            root = inserer_fin(root, "--", MINUSMINUS, ligne);
            i += 2;  // Avancer de 2 caractères
        } else {
            root = inserer_fin(root, "-", MINUS, ligne);
            i++;
        }
        continue;
      }
      if (current == '>') {
        root = inserer_fin(root, ">", SUP, ligne);
        i++;
        continue;
      }
    
    

      // Gestion des autres opérateurs et symboles
      if (current == '<') {
          root = inserer_fin(root, "<", CODE_INF, ligne);
          i++;
          continue;
      }

      if (current == ';') {
          root = inserer_fin(root, ";", CODE_PV, ligne);
          i++;
          continue;
      }

      if (current == '{' || current == '}') {
          char tmp[2] = {current, '\0'};
          root = inserer_fin(root, tmp, CODE_DELIM, ligne);
          i++;
          continue;
      }

      if (current == '(' || current == ')') {
          char tmp[2] = {current, '\0'};
          root = inserer_fin(root, tmp, CODE_PAR, ligne);
          i++;
          continue;
      }

      if (phrase[i] == '=' && phrase[i+1] == '=') {
          root = inserer_fin(root, EQ_OPERATOR, CODE_EQ, ligne);
          i += 2;
          continue;
      }

      if (phrase[i] == '!' && phrase[i+1] == '=') {
          root = inserer_fin(root, NEQ_OPERATOR, CODE_NEQ, ligne);
          i += 2;
          continue;
      }

      if (phrase[i] == '=') {
        root = inserer_fin(root, "=", CODE_AFFECT, ligne);  // CODE_AFFECT à définir si nécessaire
        i++;
        continue;
      }
    
      

      if (phrase[i] == '&' && phrase[i+1] == '&') {
          root = inserer_fin(root, AND_OPERATOR, CODE_AND, ligne);
          i += 2;
          continue;
      }

      if (phrase[i] == '|' && phrase[i+1] == '|') {
          root = inserer_fin(root, OR_OPERATOR, CODE_OR, ligne);
          i += 2;
          continue;
      }

      // Exemple de gestion des symboles
      if (current == '%') {
        root = inserer_fin(root, "%", CODE_MODULO, ligne);
        i++;  // Avancer d'un caractère
        continue;
      }

      if (current == ',') {
        root = inserer_fin(root, ",", CODE_VIRGULE, ligne);
        i++;  // Avancer d'un caractère
        continue;
      }
      // Gestion du caractère '.' (point)
      if (current == '.') {
        root = inserer_fin(root, ".", CODE_POINT, ligne);
        i++;  // Avancer d'un caractère
        continue;
      }



      // Si le caractère n'est pas reconnu, ajouter une erreur lexicale
      char err[50];
      snprintf(err, sizeof(err), "Erreur: caractere non reconnu '%c' (ligne %d)", current, ligne);
      *err_list = SU_inserer_debut(*err_list, err);
      i++;
  }

  root = inserer_fin(root, "#", FIN_SUITE_UL, ligne);
  return root;
}
