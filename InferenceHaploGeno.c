#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctionsStructuresGenoHaplo.h"

// gcc -c fonctionsStructuresGenoHaplo.c
// gcc InferenceHaploGeno.c -o InferenceHaploGeno fonctionsStructuresGenoHaplo.o -Wall

int main(int argc, char* argv[]){
  int nb_iterations_max=10, nb_lignes=0, num_indiv, num_geno=0, lg_genotypes;
  float seuil=0.01;
  char carac;
  char* seq_geno;
  FILE* GenotypesAleatoires = NULL;
  TPtr_geno liste_geno = NULL;
  TPtr_haplo liste_haplo = NULL;

  // Tests pour l'initialisation des variables avec paramètres
  if(argc<2 || argc>4) {
    printf("Merci de vérifier le nombre d'arguments rentrés.\n");
    return 1;
  }
  printf("Vérification des arguments et tentative d'ouverture du fichier '%s'...\n", argv[1]);
  if(argc==2){
    GenotypesAleatoires = fopen(argv[1], "r");
    printf("Nombre d'itérations maximum défini : %d.\n", nb_iterations_max);
    printf("Seuil défini : %f.\n", seuil);
  } else if(argc==3) {
    GenotypesAleatoires = fopen(argv[1], "r");
    nb_iterations_max=atoi(argv[2]);
    printf("Nombre d'itérations maximum défini : %d.\n", nb_iterations_max);
    printf("Seuil défini : %f.\n", seuil);
  } else if(argc==4) {
    GenotypesAleatoires = fopen(argv[1], "r");
    nb_iterations_max=atoi(argv[2]);
    seuil=atof(argv[3]);
    printf("Nombre d'itérations maximum défini : %d.\n", nb_iterations_max);
    printf("Seuil défini : %f.\n", seuil);
  }

  // Fichier des génotypes ouvert
  if(GenotypesAleatoires != NULL){
    printf("Fichier '%s' ouvert.\n", argv[1]);
    while((carac=fgetc(GenotypesAleatoires)) != EOF)
    {
      // On compte le nombre d'individus dans le fichier
      if(carac=='\n')
      nb_lignes++;
    }
    printf("Nombre d'individus présents dans le fichier : %d.\n", nb_lignes);
    TPtr_geno* tab_adr_geno=malloc(nb_lignes*sizeof(TPtr_geno*));
    printf("Réinitialisation du pointeur en début de fichier...\n");

    // Réinitialisation du pointeur au début du fichier
    rewind(GenotypesAleatoires);

    printf("Pointeur placé en début de fichier.\n");
    printf("Lecture et stockage des génotypes...\n----------------------\n");
    // On affiche les individus ainsi que leurs génotype et la longueur de ceux-ci que l'on récupère pour la suite
    while(fscanf(GenotypesAleatoires,"%*s %d %*s %s", &num_indiv, seq_geno)==2){
      printf("Individu %d ;", num_indiv);
      printf(" Génotype : %s ;", seq_geno);
      lg_genotypes=strlen(seq_geno);
      printf(" Longueur du génotype : %d\n", lg_genotypes);
      ajouter_geno(&liste_geno, num_geno, seq_geno, lg_genotypes, &liste_haplo);
      tab_adr_geno[num_indiv]=liste_geno;
      afficher_tete_geno(liste_geno, lg_genotypes);
      num_geno=num_geno+1;
      printf("----------------------\n");
    }
    while(liste_haplo!=NULL){
      printf("Haplo %d : %s\n", liste_haplo->num_haplo2, liste_haplo->haplo2);
      printf("Haplo %d : %s\n", liste_haplo->num_haplo1, liste_haplo->haplo1);
      liste_haplo=liste_haplo->next;
    }
    //Traduction des génotypes en haplotypes + stockage

    //initialisation_freq_haplo(liste_haplo);
    //calcul_proba_geno(liste_geno, liste_haplo);
    //maximisation(liste_haplo);
    //estimation_esperance(liste_geno, liste_haplo);

    printf("Fermeture du fichier '%s'...\n", argv[1]);
    fclose(GenotypesAleatoires);
    printf("Fichier '%s' fermé.\n", argv[1]);
  }

  // Fichier des génotypes non trouvé/problème lors de l'ouverture
  if(GenotypesAleatoires == NULL){
    // Impossible d'ouvrir le fichier GenotypesAleatoires
    printf("Impossible d'ouvrir le fichier '%s' \n", argv[1]);
    return 1;
  }
  return 0;
}
