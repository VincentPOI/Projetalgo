#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctionsGenotypesHaplotypes.h"

//************************************************************************
// Procédure de génération aléatoire des génotypes et des haplotypes
//************************************************************************
void generationAleatoireGeno(int taille_genotypes, int nb_max_loci_ambi, FILE* GenotypesAleatoires, int cpt_ind){
  int i, cpt_loci_ambi=0;
  int* genoAlea=malloc(taille_genotypes*sizeof(int)+1);
  int* haplo1=malloc(taille_genotypes*sizeof(int)+1);
  int* haplo2=malloc(taille_genotypes*sizeof(int)+1);
  if(!genoAlea&&!haplo1&&!haplo2){
    return;
  }
  for(i=0;i<taille_genotypes;i++){
    if(cpt_loci_ambi==nb_max_loci_ambi){
      genoAlea[i]=rand()%2;
      //printf("if %d : %d \n", cpt_loci_ambi, genoAlea[i]);
    } else {
      genoAlea[i]=rand()%3;
      //printf("else %d : %d \n", cpt_loci_ambi, genoAlea[i]);
      if(genoAlea[i]==2){
        cpt_loci_ambi++;
        //printf("cpt %d : %d \n", cpt_loci_ambi, genoAlea[i]);
      }
    }
    fprintf(GenotypesAleatoires, "%d", genoAlea[i]);
    if(genoAlea[i]==1){
      haplo1[i]=1;
      haplo2[i]=1;
    } else if(genoAlea[i]==0){
      haplo1[i]=0;
      haplo2[i]=0;
    } else {
      if(rand()%2==0){
        haplo1[i]=1;
        haplo2[i]=0;
      } else if(rand()%2==1){
        haplo1[i]=0;
        haplo2[i]=1;
      }
    }
  }
  fprintf(GenotypesAleatoires, "\n/ind %d real haplo 1 ", cpt_ind);
  for(i=0;i<taille_genotypes;i++){
    fprintf(GenotypesAleatoires, "%d", haplo1[i]);
  }
  fprintf(GenotypesAleatoires, "\n/ind %d real haplo 2 ", cpt_ind);
  for(i=0;i<taille_genotypes;i++){
    fprintf(GenotypesAleatoires, "%d", haplo2[i]);
  }
  fprintf(GenotypesAleatoires, "\n");
  free(genoAlea); // savabuguetcsur
  free(haplo1);
  free(haplo2);
}
//************************************************************************
//************************************************************************
