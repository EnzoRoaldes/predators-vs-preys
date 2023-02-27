#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20 
#define T_WAIT 40000

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.3;
int temps_repousse_herbe=-15;

int main(void) {
  srand(time(NULL));

  int tab_herbe[SIZE_X][SIZE_Y];
  for (int i = 0; i < SIZE_X; i++) {
    for (int j = 0; j < SIZE_Y; j++) {
      tab_herbe[i][j] = 0;
    }
  }

  /*
  Animal *animals = NULL;
  for (int i = 0; i < 10; i++) {
    ajouter_animal(rand()%20, rand()%50, 10, &animals);
  }
  afficher_ecosys(animals, NULL);
  printf("%d\n", length(animals));

  reproduce(&animals, 1);
  bouger_animaux(animals);
  afficher_ecosys(animals, NULL);
  printf("%d\n", length(animals));
  */
  
  Animal *proies = NULL;
  Animal *predateurs = NULL;
  for (int i = 0; i < NB_PROIES; i++) {
    ajouter_animal(rand()%20, rand()%50, 100, &proies);
  }
  for (int i = 0; i < NB_PREDATEURS; i++) {
    ajouter_animal(rand()%20, rand()%50, 100, &predateurs);
  }

  FILE *fichier = fopen("Evol_Pop.txt", "w");

  int j = 0;
  while ((proies != NULL && predateurs != NULL) && j < 500) {
    rafraichir_proies(&proies, tab_herbe);
    rafraichir_predateurs(&predateurs, &proies);
    rafraichir_monde(tab_herbe);
    fprintf(fichier, "%d %d %d\n", j, length(proies), length(predateurs));
    afficher_ecosys(proies, predateurs);
    usleep(100000);
    j++;
  }
  
  fclose(fichier);
  liberer_liste_animaux(proies);
  liberer_liste_animaux(predateurs);

  return 0;
}

