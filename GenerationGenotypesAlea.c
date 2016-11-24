#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctionsGenotypesHaplotypes.h"
#include "fonctionsStructuresGenoHaplo.h"

/*
gcc -c fonctionsGenotypesHaplotypes.c
gcc GenerationGenotypesAlea.c -o GenerationGenotypesAlea fonctionsGenotypesHaplotypes.o -Wall
./GenerationGenotypesAlea
*/
int main(int argc, char* argv[]){
  // Initialisation des variables, pour le cas sans paramètres
  int nb_individus=10, taille_genotypes=10, nb_max_loci_ambi=3, cpt_ind;
  //char* genoAlea=NULL;
  FILE* GenotypesAleatoires = NULL;
  FILE* GenoHaploAleatoires = NULL;
  printf("Lancement du programme...\n");

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
  printf("Ouverture des fichiers...\n");
  GenotypesAleatoires = fopen("GenotypesAleatoires.txt", "w+");
  GenoHaploAleatoires = fopen("GenoHaploAleatoires.txt", "w+");
  if (GenotypesAleatoires != NULL && GenoHaploAleatoires != NULL) {
    srand(time(NULL));
    // Les fichiers sont accessibles
    printf("Fichiers ouverts.\n");
    for(cpt_ind=0;cpt_ind<nb_individus;cpt_ind++){
      //Fonction de génération aléatoire de génotypes et d'haplotypes
      generationAleatoireGeno(taille_genotypes, nb_max_loci_ambi, GenotypesAleatoires, GenoHaploAleatoires, cpt_ind);
    }
    printf("Fermeture des fichiers...\n");
    fclose(GenotypesAleatoires);
    fclose(GenoHaploAleatoires);
    printf("Fichiers fermés.\n");
  }
  else {
    if(GenotypesAleatoires == NULL){
      // Impossible d'ouvrir le fichier GenotypesAleatoires
      printf("Impossible d'ouvrir le fichier 'GenotypesAleatoires.txt'\n");
    }
    else if(GenoHaploAleatoires == NULL){
      // Impossible d'ouvrir le fichier GenotypesAleatoires
      printf("Impossible d'ouvrir le fichier 'GenoHaploAleatoires.txt'\n");
    }
  }
  return 0;
}
