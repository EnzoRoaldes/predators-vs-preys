#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre_binaire.h"
#include "fonctions_string.h"

int main(void) {

    PArbreBinaire abr = creer_arbre(1,
    dupliquer_str,
    copier_str,
    detruire_str,
    afficher_str,
    comparer_str,
    ecrire_str,
    lire_str);

  FILE *f = fopen("french_za_reordered", "r");
  char res[100];
  res[strlen(res)-1] = '\0';
  fgets(res, 100, f);
  
  while (fgets(res, 100, f) != NULL) {
    res[strlen(res)-1] = '\0';
    ajouter_abr(abr, res);
  }

  PNoeudBinaire temp;

  temp = chercher_abr(abr, "qualite");
  if (temp != NULL) {
    FILE *fw = fopen((char *) temp->data, "w");
    abr->ecrire(temp->data, fw);
    fclose(fw);
    FILE *fr = fopen((char *) temp->data, "r");
    printf("%s\n", (char *) abr->lire(fr));
    fclose(fr);
  }

  temp = chercher_abr(abr, "licencie");
  if (temp != NULL) {
    FILE *fw = fopen((char *) temp->data, "w");
    abr->ecrire(temp->data, fw);
    fclose(fw);
    FILE *fr = fopen((char *) temp->data, "r");
    printf("%s\n", (char *) abr->lire(fr));
    fclose(fr);
  }

  temp = chercher_abr(abr, "qsddgskjhqhijk");
  if (temp != NULL) {
    char *data = (char *) temp->data;
    printf("%s\n", data);
  }

  detruire_ab(abr);

  return 0;
}
