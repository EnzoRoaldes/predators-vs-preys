#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

int length(Animal *liste) {
  int res = 0;
  Animal *temp = liste;
  while (temp != NULL) {
    temp = temp->suivant;
    res++;
  }
  return res;
}

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
  assert(x >= 0 && x < SIZE_X);
  assert(y >= 0 && y < SIZE_Y);

  Animal *ani = creer_animal(x, y, energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, ani);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  Animal *tmp = *liste;
  if (*liste == animal) {
    *liste = (*liste)->suivant;
    free(tmp);
    return;
  }

  Animal *deb = *liste;

  while (deb->suivant) {
    if (deb->suivant == animal) {
      tmp = deb->suivant;
      deb->suivant = deb->suivant->suivant;
      free(tmp);
      return;
    }
    deb = deb->suivant;
  }
  return;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal *tmp = liste;
  while (liste != NULL) {
    liste = liste->suivant;
    free(tmp);
    tmp = liste;
  }

  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred=0,nbproie=0;
  Animal *pa=NULL;

  for(i = 0; i < SIZE_X; i++) {
    for(j = 0; j < SIZE_Y; j++) {
      ecosys[i][j] = ' ';
    }
  }

  pa = liste_proie;
  while(pa) {
    ++nbproie;
    ecosys[pa->x][pa->y] = '*';
    pa = pa->suivant;
  }

  pa = liste_predateur;
  while(pa) {
    ++nbpred;
    if (ecosys[pa->x][pa->y] == ' ') ecosys[pa->x][pa->y] = 'O';
    else ecosys[pa->x][pa->y] = '@';
    pa = pa->suivant;
  }


  printf("+");
  for(j = 0; j < SIZE_Y; j++) printf("-");
  printf("+\n");

  for(i = 0; i < SIZE_X; i++) {
    printf("|");
    for(j = 0; j < SIZE_Y; j++) putchar(ecosys[i][j]);
    printf("|\n");
  }

  printf("+");
  for(j = 0; j < SIZE_Y; j++) printf("-");
  printf("+\n");

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  Animal *temp = la;
  while (temp != NULL) {
    if ((((float)rand()) / RAND_MAX) <= p_ch_dir) {
      temp->dir[0] = rand() % 3 - 1;
      temp->dir[1] = rand() % 3 - 1;
    }

    temp->x = (temp->x + temp->dir[0] + SIZE_X) % SIZE_X;
    temp->y = (temp->y + temp->dir[1] + SIZE_Y) % SIZE_Y;
  
    temp = temp->suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *temp = *liste_animal;
  while (temp != NULL) {
    if (((((float)rand()) / RAND_MAX) <= p_reproduce) && temp->energie >= 10) { // un animal avec moins de 10 d'énergie se reproduit pas
      ajouter_animal(temp->x, temp->y, (temp->energie)/2, liste_animal);
      temp->energie = (temp->energie)/2;
    }
    temp = temp->suivant;
  }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie);
  Animal *temp = *liste_proie;
  while (temp != NULL) {
    temp->energie = temp->energie - 1;
    if (monde[temp->x][temp->y] > 0) {
      temp->energie = temp->energie + monde[temp->x][temp->y];
      monde[temp->x][temp->y] = temps_repousse_herbe;
    }
    if (temp->energie <= 0) {
      enlever_animal(liste_proie, temp);
    }
    temp = temp->suivant;
  }
  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *proie_en_XY(Animal *l, int x, int y) {
  Animal *temp = l;
  while (temp != NULL) {
    if (temp->x == x && temp->y == y) {
      return temp;
    }
    temp = temp->suivant;
  }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur);
  Animal *temp = *liste_predateur;
  while (temp != NULL) {
    temp->energie = temp->energie - 1;
    Animal *proie_mange = proie_en_XY(*liste_proie, temp->x, temp->y);
    if (proie_mange != NULL) {
      temp->energie += proie_mange->energie;
      enlever_animal(liste_proie, proie_mange);
    }
    if (temp->energie <= 0) {
      enlever_animal(liste_predateur, temp);
    }
    temp = temp->suivant;
  }
  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for (int i = 0; i < SIZE_X; i++) {
    for (int j = 0; j < SIZE_Y; j++) {
      monde[i][j]++;
    }
  }
}

