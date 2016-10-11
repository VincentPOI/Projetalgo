#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctionsGenotypesHaplotypes.h"


int main(int argc, char* argv[]){
  // Initialisation des variables, pour le cas sans paramètres
  int nb_individus=10, taille_genotypes=10, nb_max_loci_ambi=3, cpt_ind;
  //char* genoAlea=NULL;
  FILE* GenotypesAleatoires = NULL;
  printf("Test lancement programme\n");

  // Tests pour l'initialisation des variables avec paramètres
  if(argc==2){
    nb_individus=atoi(argv[1]);
  } else if(argc==3) {
    nb_individus=atoi(argv[1]);
    taille_genotypes=atoi(argv[2]);
  } else if(argc==4) {
    nb_individus=atoi(argv[1]);
    taille_genotypes=atoi(argv[2]);
    nb_max_loci_ambi=atoi(argv[3]);
  } else if(argc>4) {
    printf("Merci de vérifier le nombre d'arguments rentrés.\n");
  }
  printf("Ouverture fichier\n");
  GenotypesAleatoires = fopen("GenotypesAleatoires.txt", "w+");
  if (GenotypesAleatoires != NULL) {
    srand(time(NULL));
    // Le fichier est accessible
    printf("Fichier ouvert\n");
    for(cpt_ind=0;cpt_ind<nb_individus;cpt_ind++){
      fprintf(GenotypesAleatoires, "/ind %d geno\t    ", cpt_ind);
      //Fonction Génération Aléatoire de géno
      generationAleatoireGeno(taille_genotypes, nb_max_loci_ambi, GenotypesAleatoires, cpt_ind);
    }
    printf("Fermeture fichier\n");
    fclose(GenotypesAleatoires);
    printf("Fichier fermé\n");
  }
  else {
    // Impossible d'ouvrir le fichier
    printf("Impossible d'ouvrir le fichier GenotypesAleatoires.txt\n");
  }
  return 0;
}
