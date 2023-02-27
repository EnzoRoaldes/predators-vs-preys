//PIERRE & ENZO

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compte_mots_chaine(char *str) {
  if (str[0] == '\0') {
    return 0;
  }
    int res = 0;
    if (str[0] != ' ') res++;
    int i = 1;
    while (str[i] != '\0') {
        if (str[i-1] == ' ' && str[i] != ' ') {
            res++;
        }
        i++;
    }
    return res;
}


int compte_mots_tab_chaine(char **tab_str) {
  /* a completer exercice 3, question 2 */
  int res = 0;
  while (tab_str[res] != NULL) {
    res++;
  }
  return res;
}

char **decompose_chaine(char *chaine)
{

  /* Fonction vue en TD, exercice 2, question 7 */

  char *pc= chaine;
  int nb_mots=0;
  char **ptab;
  char *psrc_mot;
  int ind_mot=0;

  //comptages des mots
  nb_mots=compte_mots_chaine(chaine);
	
  if (nb_mots == 0)
    return NULL;
  // allocation du tableau

  ptab = malloc((nb_mots + 1) * sizeof(char *));
  ptab[nb_mots] = NULL;
	
  // copie des mots
	
  pc=chaine;
  while (*pc)
    {
      if(*pc == ' ')
        {
          pc++;
          continue;
        }

      psrc_mot = pc;

      while((*pc != ' ') && (*pc)) pc++;

      //allocation du mot
      ptab[ind_mot] = malloc((pc - psrc_mot + 1)* sizeof(char));
      //copie du mot
      memcpy(ptab[ind_mot], psrc_mot, pc - psrc_mot);
      //insertion du marqueur de fin de chaine
      *(ptab[ind_mot] + (pc - psrc_mot)) = '\0';

      ind_mot++;
    }
	

  return ptab;
}

char *compose_chaine(char **ptab_mots)
{
  int nb_char = 0;
  int i = 0;
  for (i = 0; ptab_mots[i]; i++) { // nbr de caracteres 
    nb_char += strlen(ptab_mots[i]);
  }
  nb_char += i - 1; // nbr espaces
  char *res = malloc(nb_char*sizeof(char));

  int j = 0;
  for (int n = 0; ptab_mots[n]; n++) {
    for (int m = 0; ptab_mots[n][m] != '\0'; m++) {
      res[j] = ptab_mots[n][m];
      j++;

    }
    res[j] = ' ';
    j++;
  }
  res[j-1] = '\0';

  return res;
}
		
void detruit_tab_mots(char **ptab_mots)
{

  /* Fonction vue en TD, exercice 2, question 5 */

  int i=0;

  if (ptab_mots)
    while(ptab_mots[i])
      free(ptab_mots[i++]);

  free(ptab_mots);
}

void affiche_tab_mots(char **ptab_mots)
{
  for(int i = 0; ptab_mots[i]; i++) {
    for (int j = 0; ptab_mots[i][j] != '\0'; j++) { 
      printf("%c", ptab_mots[i][j]);
    }
    if (ptab_mots[i+1]) {
      printf(" et ");
    }
  }
  printf("\n");
}

void initialise_tab(int tab[], int len) {
  for (int i = 0; i < len; i++) {
    tab[i] = -1;
  }
}

int est_dans_tab(int val, int tab[], int len) {
  for (int i = 0; i < len; i++) {
    if (val == tab[i]) {
      return 1;
    }
  }
  return 0;
}

char **reduit_tab_mots(char **ptab_mots)
{
  int est_egal;
  int len = compte_mots_tab_chaine(ptab_mots);
  int index_pas_refaire[len];
  initialise_tab(index_pas_refaire, len);

  for (int i = 0; ptab_mots[i]; i++) {
    if (est_dans_tab(i, index_pas_refaire, len)) {
      continue;
    }
    for (int j = i+1; ptab_mots[j]; j++) {
      est_egal = 1;
      int k;
      for (k = 0; ptab_mots[i][k] != '\0' && ptab_mots[j][k] != '\0'; k++) {
        if (ptab_mots[i][k] != ptab_mots[j][k]) {
          est_egal = 0;
          break;
        }
      }

      if (ptab_mots[i][k] == '\0' && ptab_mots[j][k] == '\0' && est_egal == 1) {
        free(ptab_mots[j]);
        ptab_mots[j] = ptab_mots[i];
        index_pas_refaire[j] = j; 
      }

    }
  }

  free(index_pas_refaire);
  return ptab_mots;

}

int main() {


  /* EXERCICE 3:
  char *c = "Bonjour a tous test";
  char *c1 = "";
  printf("%d\n%d\n", compte_mots_chaine(c), compte_mots_chaine(c1));

  char **tab = decompose_chaine(c);

  printf("%d\n", compte_mots_tab_chaine(tab));

  affiche_tab_mots(tab);

  char *chaine = compose_chaine(tab);
  printf("%s\n", chaine);

  free(c);
  free(c1);
  free(chaine);
  detruit_tab_mots(tab);
  */

  //EXERCICE 4:
  char *c = "Bonjour test salut non oui non non nonnon non oui OUI OUI oui Bonjour Bonjour a b c d e a a a a";
  char **tab = decompose_chaine(c);
  affiche_tab_mots(tab);
  tab = reduit_tab_mots(tab);
  affiche_tab_mots(tab);

  //QUESTION 2:
  detruit_tab_mots(tab);
    //pas de soucis sur la fonction destruction de mémoire, on aura juste des free(NULL) parfois
    //car le pointeur aura deja été libéré avant si on a un mot plusieurs fois.

  return 1;
}
