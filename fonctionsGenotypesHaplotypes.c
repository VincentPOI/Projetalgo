#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctionsGenotypesHaplotypes.h"

//************************************************************************
// Procédure de génération aléatoire des génotypes et des haplotypes hello
//************************************************************************
void generationAleatoireGeno(int taille_genotypes, int nb_max_loci_ambi, FILE* GenotypesAleatoires, FILE* GenoHaploAleatoires, int cpt_ind){
  int i, cpt_loci_ambi=0, /*cpt_loci_ambi_prec=-1, cpt_distrib_normale=1*/;
  int* genoAlea=malloc(taille_genotypes*sizeof(int)+1);
  int* haplo1=malloc(taille_genotypes*sizeof(int)+1);
  int* haplo2=malloc(taille_genotypes*sizeof(int)+1);
  if(!genoAlea&&!haplo1&&!haplo2){
    return;
  }
  fprintf(GenotypesAleatoires, "/ind %d geno ", cpt_ind);
  fprintf(GenoHaploAleatoires, "/ind %d geno ", cpt_ind);
  for(i=0;i<taille_genotypes;i++){
    /*if(cpt_loci_ambi!=0){
      cpt_loci_ambi_prec=cpt_loci_ambi;
    }*/
    if(cpt_loci_ambi==nb_max_loci_ambi){
      genoAlea[i]=rand()%2;
      //printf("if %d : %d \n", cpt_loci_ambi, genoAlea[i]);
    } else {
      genoAlea[i]=rand()%3;
      //printf("else %d : %d \n", cpt_loci_ambi, genoAlea[i]);
      if(genoAlea[i]==2){
        if((rand()%nb_max_loci_ambi)+1 == nb_max_loci_ambi) {
          // (rand()%nb_max_loci_ambi)+1 == nb_max_loci_ambi
          // PROBLEME ICI POUR PONDERER la probabilité d'avoir un 2; pondération dépendante du nombre de loci amibigus :
          // plus celui-ci est élevé, moins les chances d'avoir un 2 sont fortes et donc ceux-ci seront plus dispersés
          // néanmoins, dans une séquence de faible taille, les 2 peuvent se faire rares, surtout si le rapport
          // nb_max_loci_ambi/taille_genotypes est élevé
          //
          //i<(taille_genotypes/nb_max_loci_ambi)*cpt_distrib_normale && i>=(taille_genotypes/nb_max_loci_ambi)*(cpt_distrib_normale-1)
          // PROBLEME ICI POUR PONDERER la probabilité d'avoir un 2; si aucune insertion dans un des ensembles bornées,
          //alors les suivants n'auront pas non plus de 2
          cpt_loci_ambi++;
          //cpt_distrib_normale++;
        } else {
          genoAlea[i]=rand()%2;
        }
        //printf("cpt %d : %d \n", cpt_loci_ambi, genoAlea[i]);
      }
      /*if(i>=(taille_genotypes/nb_max_loci_ambi)*(cpt_distrib_normale)&&cpt_loci_ambi==cpt_loci_ambi_prec){
        cpt_distrib_normale++;
      }*/
    }
    if(i<(taille_genotypes-1)){
      // Test si on atteint la fin de la séquence
      fprintf(GenotypesAleatoires, "%d", genoAlea[i]);
    }
    else if(i==(taille_genotypes-1)){
      // Si la fin de la séquence est atteinte, on inclut un retour chariot
      fprintf(GenotypesAleatoires, "%d\n", genoAlea[i]);
    }
    fprintf(GenoHaploAleatoires, "%d", genoAlea[i]);
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
      } else {
        haplo1[i]=0;
        haplo2[i]=1;
      }
    }
  }
  fprintf(GenoHaploAleatoires, "\n/ind %d real haplo 1 ", cpt_ind);
  for(i=0;i<taille_genotypes;i++){
    fprintf(GenoHaploAleatoires, "%d", haplo1[i]);
  }
  fprintf(GenoHaploAleatoires, "\n/ind %d real haplo 2 ", cpt_ind);
  for(i=0;i<taille_genotypes;i++){
    fprintf(GenoHaploAleatoires, "%d", haplo2[i]);
  }
  fprintf(GenoHaploAleatoires, "\n");
  free(genoAlea);
  free(haplo1);
  free(haplo2);
}
//************************************************************************
//************************************************************************
