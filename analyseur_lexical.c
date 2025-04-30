#include "analyseur_lexical.h"
int isIn(char c, const char str[])
{
  int i = 0;
  while (str[i] != '\0')
  {
    if (str[i] == c)
    {
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


  
  SU *SU_inserer_debut(SU *root, char *phrase);
  void aff_su(SU *root);

  SU *SU_inserer_debut(SU *root, char *phrase)
{
  SU *nsu = malloc(sizeof(SU));
  strcpy(nsu->data, phrase);
  nsu->suivant = root;
  return nsu;
}
void aff_su(SU *root)
{
  if (root == NULL)
  {
    printf("\naucun err lexical");
  }
  else
  {
    SU *current = root;
    while (current != NULL)
    {
      printf("\n%s", current->data);
      current = current->suivant;
    }
  }
}