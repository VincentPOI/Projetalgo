#include <stdio.h>
#include <stdlib.h>
#include "fonctionsStructuresGenoHaplo.h"

//************************************************************************
// Fonction d'ajout de génotype
//************************************************************************
void ajouter_geno(TPtr_geno* adr_liste_geno, int num_geno, char* seq_geno/*type_lst_haplo* new_liste_haplo*/) {
  /* Création d'un nouveau génotype*/
  TPtr_geno p_nouveau = (type_lst_gen*)malloc(sizeof (type_lst_gen));
  TPtr_geno p = *adr_liste_geno;
  p_nouveau->num_geno = num_geno;
  p_nouveau->seq_geno = seq_geno;
  p_nouveau->next = p;
  *adr_liste_geno=p_nouveau;
}

//
// //************************************************************************
// // Fonction d'ajout d'haplotype
// //************************************************************************
// type_lst_haplo* ajouter_haplo(type_lst_haplo* liste_haplo, int* new_liste_haplo) {
//   //Création d'un nouveau génotype
//   type_lst_haplo* nouveau = malloc(sizeof (type_lst_haplo));
//   nouveau->haplo = new_liste_haplo;
//   // Insertion de l'élément au début de la liste
//   nouveau->nxt = liste_haplo;
// }
//

//************************************************************************
// Procédure d'affichage de la liste chaînée de génotypes
//************************************************************************
void afficher_tete_geno(TPtr_geno liste_geno, int lg_genotypes) {
  int i;
  TPtr_geno p;
  p = liste_geno;
  printf("Liste chaînée : Génotype %d; ", p->num_geno);
  for(i=0;i<lg_genotypes;i++){
    printf("%c", p->seq_geno[i]);
  }
  printf("\n");
}
//
// //************************************************************************
// // Procédure d'initialisation de la fréquence des haplotypes
// //************************************************************************
// void initialisation_freq_haplo(TPtr_geno* adr_liste_geno, TPtr_haplo* adr_liste_haplo, int nb_haplo){
//   TPtr_geno p1 = *adr_liste_geno;
//   TPtr_haplo p2 = *adr_liste_haplo;
//   while(p1!=NULL){
//     while(p2!=NULL){
//       liste_haplo->freq_haplo1=1/nb_haplo;
//       liste_haplo->freq_haplo2=1/nb_haplo;
//       p2=p2->next;
//     }
//     p1=p1->next;
//   }
// }
//
// //************************************************************************
// // Procédure de calcul de la probabilité des génotypes
// //************************************************************************
// void calcul_proba_geno(TPtr_geno* adr_liste_geno, TPtr_haplo* adr_liste_haplo){
//   TPtr_geno p1 = *adr_liste_geno;
//   TPtr_haplo p2 = *adr_liste_haplo;
//   double f1, f2, p_part;
//   while(p1!=NULL){
//     p1->proba_geno=0;
//     while(p2!=NULL){
//       f1=p2->freq_haplo1;
//       f2=p2->freq_haplo2;
//       if(f1==f2){
//         p_part=f1*f2;
//       } else {
//         p_part=2*f1*f2;
//       }
//       p1->proba=p1->proba+p_part;
//     }
//   }
// }
//
//
//
// //************************************************************************
// // Procédure de maximisation
// //************************************************************************
// void maximisation(TPtr_geno* adr_liste_geno, TPtr_haplo* adr_liste_haplo){
//   TPtr_geno p1 = *adr_liste_geno;
//   TPtr_haplo p2 = *adr_liste_haplo;
//   while(p1!=NULL){
//
//   }
// }
//
