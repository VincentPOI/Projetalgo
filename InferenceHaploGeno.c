#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
  int nb_iterations_max=10, nbLignes=0, numIndiv;
  float seuil=0.01;
  char carac;
  char* seqGeno;
  FILE* GenotypesAleatoires = NULL;

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

  if(GenotypesAleatoires != NULL){
    printf("Fichier '%s' ouvert.\n", argv[1]);
    while((carac=fgetc(GenotypesAleatoires)) != EOF)
    {
      //On compte le nombre d'individus dans le fichier
    	if(carac=='\n')
    		nbLignes++;
    }
    printf("Nombre d'individus présents dans le fichier : %d.\n", nbLignes);

    printf("Réinitialisation du pointeur en début de fichier...\n");
    rewind(GenotypesAleatoires);
    printf("Pointeur placé en début de fichier.\n");


    while(fscanf(GenotypesAleatoires,"%*s %d %*s %*s", &numIndiv)==1){
      printf("Individu %d ; ", numIndiv);
      //printf("longueur de génotype : %s\n", seqGeno);
    }

    /*while(fscanf(GenotypesAleatoires,"%s %d %s %s",&nom[i],&temps[i]) == 2){

    } */

    //Lecture des génotypes + stockage
    //Traduction des génotypes en haplotypes + stockage
    //Initialisation des fréquences des haplotypes
    //Calcul de probabilité des génotypes
    printf("Fermeture du fichier '%s'...\n", argv[1]);
    fclose(GenotypesAleatoires);
    printf("Fichier '%s' fermé.\n", argv[1]);
  }

  if(GenotypesAleatoires == NULL){
    // Impossible d'ouvrir le fichier GenotypesAleatoires
    printf("Impossible d'ouvrir le fichier '%s' \n", argv[1]);
    return 1;
  }
  return 0;
}
