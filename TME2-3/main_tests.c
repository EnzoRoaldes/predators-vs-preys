#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;

int main(void) {
  srand(time(NULL));
  Animal *predateurs = NULL;
  Animal *proies = NULL;
  int nb = 5;
  for (int i = 0; i < nb; i++) {
    ajouter_animal(rand()%20, rand()%50, rand()%101, &predateurs);
    ajouter_animal(rand()%20, rand()%50, rand()%101, &proies);
  }
  int nb_pred = compte_animal_rec(predateurs);
  int nb_proi = compte_animal_rec(proies);
  assert(nb_pred == nb && nb_proi == nb);

  afficher_ecosys(proies, predateurs);

  Animal *tmp = predateurs->suivant->suivant;
  enlever_animal(&predateurs, tmp);
  enlever_animal(&predateurs, predateurs);
  afficher_ecosys(proies, predateurs);

  tmp = predateurs->suivant->suivant;
  enlever_animal(&predateurs, tmp);
  enlever_animal(&predateurs, predateurs);
  enlever_animal(&predateurs, predateurs);
  afficher_ecosys(proies, predateurs);

  liberer_liste_animaux(proies);
  liberer_liste_animaux(predateurs);

  printf("TEST\n");

  return 0;
}
