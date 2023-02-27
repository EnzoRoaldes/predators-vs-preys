#include "arbre_lexicographique.h"
#include "liste.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PNoeud creer_noeud(char lettre){
  PNoeud pn=(PNoeud)malloc(sizeof(Noeud));
  if (pn==NULL) {
    printf("Impossible d'allouer un noeud\n");
    return NULL;
  }
 
  pn->lettre=lettre;
  pn->fin_de_mot=non_fin;
  pn->frere_suivant=NULL;
  pn->fils=NULL;
  return pn;
}

void inserer_lettre(PNoeud *racine, PNoeud *n_lettre, char lettre) {
  PNoeud prec=NULL;
  PNoeud n=*racine;
  if (n==NULL) {
    *racine=creer_noeud(lettre);
    *n_lettre=*racine;
    return;
  }

  while(n!=NULL) {
    if (n->lettre == lettre) {
      *n_lettre=n;
      return;
    }
    if (n->lettre>lettre) {
      // on doit inserer avant n
      if (prec==NULL) {
        // insertion en tete
        prec=creer_noeud(lettre);
        prec->frere_suivant=n;
        *racine=prec;
        *n_lettre=*racine;
      }
      else {
        *n_lettre=creer_noeud(lettre);
        prec->frere_suivant=*n_lettre;
        (*n_lettre)->frere_suivant=n;
      }
      return;
    }
    prec=n;
    n = n->frere_suivant;
  }
  *n_lettre=creer_noeud(lettre);
  prec->frere_suivant=*n_lettre;
}

PNoeud ajouter_mot(PNoeud racine, char *mot) {
  PNoeud n=NULL;
  if (strlen(mot)==0) {
    return NULL;
  }
  inserer_lettre(&racine,&n,mot[0]);
  if (strlen(mot)==1) {
    n->fin_de_mot=fin;
  }
  else {
    n->fils=ajouter_mot(n->fils,mot+1);
  }
  return racine;
}

int taille(PNoeud racine) {
  if (racine==NULL) {
    return 0;
  }
  else {
    return 1+taille(racine->frere_suivant);
  }
}

void afficher_mots(PNoeud n, char mot_en_cours[], int index) {
  if (n == NULL) {
    return;
  }

  if (n->fin_de_mot == fin) {
    mot_en_cours[index] = n->lettre;
    for (int i = index + 1; i < 30; i++) {
      mot_en_cours[i] = ' ';
    }
    printf("%s\n", mot_en_cours);
  }

  if (n->fils == NULL && n->frere_suivant == NULL) {
    return;
  }

  afficher_mots(n->frere_suivant, mot_en_cours, index);

  mot_en_cours[index] = n->lettre;
  afficher_mots(n->fils, mot_en_cours, index+1);
}

void afficher_dico(PNoeud racine) {
  char *mot_en_cours = malloc(sizeof(char)*30);
  afficher_mots(racine, mot_en_cours, 0);
}

void detruire_dico(PNoeud n) {

  if (n == NULL) {
    return;
  }

  if (n->fils == NULL && n->frere_suivant == NULL) {
    free(n);
    return;
  }

  detruire_dico(n->fils);
  detruire_dico(n->frere_suivant);
}

PNoeud chercher_lettre(PNoeud n, char lettre) {
  if (n==NULL) {
    return NULL;
  }
  if (n->lettre==lettre) {
    return n;
  }
  if (n->lettre>lettre) {
    return NULL;
  }
  return chercher_lettre(n->frere_suivant,lettre);
}

int rechercher_mot(PNoeud dico, char *mot) {
  PNoeud n=chercher_lettre(dico,mot[0]);
  if (n==NULL) {
    return 0;
  }
  if (strlen(mot)==1) {
    return n->fin_de_mot == fin;
  }
  return rechercher_mot(n->fils,mot+1);
}

PNoeud lire_dico(const char *nom_fichier) {
  Lm_mot *lm = lire_dico_Lmot(nom_fichier);

  PNoeud racine = NULL;
  while (lm != NULL) {
    racine = ajouter_mot(racine, lm->mot);
    lm = lm->suiv;
  }

  afficher_dico(racine);

  detruire_Lmot(lm);

  return racine;
}

PNoeud fichier2arbreLexico(const char *nom_fichier) {
  Lm_mot *lm = lire_dico_Lmot(nom_fichier);

  PNoeud racine = NULL;
  while (lm != NULL) {
    racine = ajouter_mot(racine, lm->mot);
    lm = lm->suiv;
  }
  detruire_Lmot(lm);

  return racine;
}