#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "arbre_binaire.h"
#include "fonctions_entiers.h"

int main(void) {

  PArbreBinaire abr = creer_arbre(1,
    dupliquer_int,
    copier_int,
    detruire_int,
    afficher_int,
    comparer_int,
    ecrire_int,
    lire_int);

  int r;
  for (int i = 0; i < 20; i++) {
    r = rand() % 100;
    ajouter_abr(abr, &r);
  }

  afficher_ab_infixe(abr);
  printf("\n");

  PNoeudBinaire temp;
  for (int i = 0; i < 100; i++) {
    temp = chercher_abr(abr, &i);
    if (temp != NULL) {
      int *data = (int *) temp->data;
      printf("%d\n", *data);
    }
  }

  ecrire_ab(abr, "fichier.txt");
  PArbreBinaire abr_ = creer_arbre(0,
    dupliquer_int,
    copier_int,
    detruire_int,
    afficher_int,
    comparer_int,
    ecrire_int,
    lire_int);
  lire_abr(abr_, "fichier.txt");

  afficher_ab_infixe(abr_);
  printf("\n");

  detruire_ab(abr);
  detruire_ab(abr_);
  
  return 0;
}
