#include <stdio.h>
#include <stdlib.h>
#include "arbre_lexicographique.h"


int main(int argc, char **argv)
{
  
  //lire_dico("french_za");
  PNoeud racine = fichier2arbreLexico("french_za");

    for (long long i = 0; i < atoi(argv[2]); i++) {
      rechercher_mot(racine, argv[1]);
  }

  detruire_dico(racine);
  return 0;
}
