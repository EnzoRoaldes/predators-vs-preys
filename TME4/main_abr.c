#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "abr.h"
#include <time.h>

int main(int argc, char **argv)
{

  char *nom_dico = "french_za";
  Lm_mot *l = lire_dico_Lmot(nom_dico);
  Nd_mot *arbre = Lm2abr(l);
  
  for (long long i = 0; i < atoi(argv[2]); i++) {
    chercher_Nd_mot(arbre, argv[1]);
  }
  
  detruire_abr_mot(arbre);
  return 0;
}
