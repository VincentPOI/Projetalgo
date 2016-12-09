#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fonctionsStructuresGenoHaplo.h"

//************************************************************************
// Fonction d'ajout d'haplotype entrant dans l'explication d'un génotype
//************************************************************************
void ajouter_haplo_geno(TPtr_geno p_nouveau_geno, TPtr_haplo* adr_liste_haplo_geno, char** matrice_haplo, int i, int pownb) {
  TPtr_haplo p_nouveau_hap1 = (type_lst_haplo*)malloc(sizeof(type_lst_haplo));
  TPtr_haplo p1 = *adr_liste_haplo_geno;
  p_nouveau_hap1->num_haplo1 = (p_nouveau_geno->num_geno)+i;
  p_nouveau_hap1->haplo1 = matrice_haplo[i];
  p_nouveau_hap1->num_haplo2 = (p_nouveau_geno->num_geno)+i+1;
  if(pownb=1){
    p_nouveau_hap1->haplo2 = matrice_haplo[i];
  }else{
    p_nouveau_hap1->haplo2 = matrice_haplo[(pownb/2)+i-1];
  }
  p_nouveau_hap1->freq_haplo1 = 0;
  p_nouveau_hap1->freq_prec_haplo1 = 0;
  p_nouveau_hap1->freq_haplo2 = 0;
  p_nouveau_hap1->freq_prec_haplo2 = 0;
  p_nouveau_hap1->nbocc_haplo1 = 1;
  p_nouveau_hap1->nbocc_haplo2 = 1;
  p_nouveau_hap1->next = p1;
  *adr_liste_haplo_geno=p_nouveau_hap1;

  // type_lst_gen_exp* liste_gen_exp;
}
//************************************************************************
// Fonction de vérification de redondance d'haplotype
//************************************************************************
int haplo_existe(TPtr_geno* adr_liste_geno, TPtr_haplo* adr_liste_haplo){
  TPtr_haplo p2 = *adr_liste_haplo;
  TPtr_geno p1 = *adr_liste_haplo;
  while(p2!=NULL){
    if(p2->haplo1==p1->liste_haplo_geno->haplo1){
      return 1;
    }
    if(p2->haplo2==p1->liste_haplo_geno->haplo1){
      return 1;
    }
    if(p2->haplo1==p1->liste_haplo_geno->haplo2){
      return 1;
    }
    if(p2->haplo2==p1->liste_haplo_geno->haplo2){
      return 1;
    }
  }
  p2=p2->next;
}
return 0;
}


//************************************************************************
// Fonction d'ajout d'haplotype
//************************************************************************
void ajout_haplo(TPtr_geno* adr_liste_geno, TPtr_haplo* adr_liste_haplo){

  TPtr_geno p1 = *adr_liste_geno;
  TPtr_haplo p_nouveau_hap2 = (type_lst_haplo*)malloc(sizeof(type_lst_haplo));
  TPtr_haplo p2 = *adr_liste_haplo;
  int cpt=0, trouve;
  while(p1 != NULL){
    trouve = haplo_existe(p1, p2);
    if(trouve==0){
      p_nouveau_hap2->num_haplo1 = cpt;
      p_nouveau_hap2->haplo1 = p1->liste_haplo_geno->haplo1;
      p_nouveau_hap2->num_haplo2 = cpt+1;
      p_nouveau_hap2->haplo2 = p1->liste_haplo_geno->haplo2;
      p_nouveau_hap2->freq_haplo1 = 0;
      p_nouveau_hap2->freq_prec_haplo1 = 0;
      p_nouveau_hap2->freq_haplo2 = 0;
      p_nouveau_hap2->freq_prec_haplo2 = 0;
      p_nouveau_hap1->nbocc_haplo1 = 1;
      p_nouveau_hap1->nbocc_haplo2 = 1;
      p_nouveau_hap2->next = p2;
      *adr_liste_haplo=p_nouveau_hap2;
      cpt++;
    }
    p1=p1->next;
  }
}

//************************************************************************
// Fonction d'ajout de génotype
//************************************************************************
void ajouter_geno(TPtr_geno* adr_liste_geno, int num_geno, char* seq_geno, int lg_genotypes) {
  /* Création d'un nouveau génotype*/
  int nb_Amb, i, j, k;
  TPtr_haplo liste_haplo_geno = NULL;

  TPtr_geno p_nouveau_geno = (type_lst_gen*)malloc(sizeof (type_lst_gen));
  TPtr_geno p = *adr_liste_geno;
  p_nouveau_geno->num_geno = num_geno;
  p_nouveau_geno->seq_geno = seq_geno;
  p_nouveau_geno->proba_geno = 0;
  p_nouveau_geno->proba_prec_geno = 0;

  arbre_haplo *Arbre = generate_tree_from_geno(p_nouveau_geno->seq_geno, lg_genotypes, &nb_Amb);
  int pownb = (int)(pow(2.0,(double)(nb_Amb)));
  char **matrice_haplo_tmp = (char**) malloc(sizeof(char*)*pownb);
  char **matrice_haplo = (char**) malloc(sizeof(char*)*pownb);
  for (i = 0; i < pownb; i++) {
    matrice_haplo_tmp[i] = (char*) malloc(sizeof(char)*lg_genotypes);
    matrice_haplo[i] = (char*) malloc(sizeof(char)*lg_genotypes);
  }
  pile* pile =  malloc(sizeof *pile);
  int pos = tree_to_matrix(Arbre, &pile, matrice_haplo_tmp,lg_genotypes,0);
  for (i = 0; i < pownb; i++) {
    for(j=0, k=lg_genotypes-1; j!=lg_genotypes && k>-1; j++, k--){
      matrice_haplo[i][j]=matrice_haplo_tmp[i][k];
    }
    printf("Haplotype[%d] : %s.\n", i, matrice_haplo[i]);
    ajouter_haplo_geno(p_nouveau_geno, &liste_haplo_geno, matrice_haplo, i, pownb);
  }
  free(matrice_haplo_tmp);

  p_nouveau_geno->liste_haplo_geno=liste_haplo_geno;

  p_nouveau_geno->next = p;
  *adr_liste_geno=p_nouveau_geno;
}

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

//************************************************************************
// Procédure d'ajout d'haplotype dans la pile
//************************************************************************
void pile_ajouter(pile **p_pile, char carac) {
  pile *new_pile = malloc(sizeof *new_pile);
  {
    new_pile->carac = carac;
    new_pile->precedent = *p_pile;
    *p_pile = new_pile;
  }
}

//************************************************************************
// Procédure de retrait d'haplotype dans la pile
//************************************************************************
void pile_retirer(pile **p_pile) {
  char ret = '\0';
  if (p_pile != NULL)
  {//stockage
    pile *temp = (*p_pile)->precedent;
    ret = (*p_pile)->carac;
    free(*p_pile), *p_pile = NULL;
    *p_pile = temp;
  }
}

//************************************************************************
// Procédure récursive d'ajout de noeud (haplo) à un arbre
//************************************************************************
void ajouter_noeud(arbre_haplo** Arbre, char val, int cas) {
/*
Fonction récursive qui permet d'ajouter un noeud à un arbre.
Elle prend en entrée :
-Un arbre_haplo (Arbre);
-Un char, valeur que doit prendre le nouveau noeud;
-Un entier cas, qui prend la valeur 1 ou 2
 le cas "1" correspond à un ajout sans ambiguitée
 le cas "2" correspond à un ajout avec ambiguitée
*/
  if( *Arbre == NULL )
  /*
  si l'arbre est null donc que l'on est arrivé au bout du parcours récursif:
  on peut donc ajouter un nouveau noeud.
  */
  {
    *Arbre = (arbre_haplo*) malloc( sizeof( arbre_haplo ));//on lui alloue de la mémoire
    (*Arbre)->carac = val;// définition de sa valeur
    (*Arbre)->gauche =NULL;
    (*Arbre)->droit = NULL;
  }else if((*Arbre)->carac != 'S'){
    /*
    Sinon si l'arbre(le noeud) est non null on parcours l'arbre jusquà arriver au bout.
    (on évite les 'S' afin de ne pas générer des branches ne contenant pas les ambiguitée')
    */
    if (cas == 1)
    //cas 1: pas d'ambiguitée
    {
      if((*Arbre)->gauche == NULL && (*Arbre)->droit ==NULL){
        /*
        Cette condition verifie que le noeud est l'avant dernier et donc que le prochain
        récursif créera le nouveau noeud et défénira sa valeur.
        Dans le "cas" 1 (pas d'ambiguitée) il faut donc Mettre 'S'(STOP) dans le fils droit.
        */
        ajouter_noeud( &(*Arbre)->gauche , val, 1);
        ajouter_noeud( &(*Arbre)->droit, 'S', 1);
      }else{
        /*
        quand cette condition n'est pas vérifier on se contente de continuer à parcourir l'arbre.
        */
        ajouter_noeud( &(*Arbre)->gauche , val, 1);
        ajouter_noeud( &(*Arbre)->droit , val, 1);
      }

    }
    if (cas == 2){
      //cas 2 pas d'ambiguitée, on continu d'appeler la fonction récursive jusqu'à
      //arriver au bout de l'arbre et définir la valeur des noeuds.
      ajouter_noeud( &(*Arbre)->gauche , '1', 2);
      ajouter_noeud( &(*Arbre)->droit , '0', 2);
    }
  }
}

//************************************************************************
// Fonction de génération d'arbre d'haplotypes à partir d'un génotype
//************************************************************************
arbre_haplo* generate_tree_from_geno(char* geno, int lgGenotype, int *nb_Amb) {
/*
Fonction qui prend en paramètre:
-une chaine de caractère contenant un génotype(geno);
-un entier, la longueur du génotype (lgGenotype);
-un entier qui peermet de compter le nombre d'ambiguitée dans le génotype (nb_amb);
et qui retourne :
-une structure de type arbre_haplo qui contient tout les haplotype possibles
*/
  int i;
  int cpt=0;//compteur qui compte les ambiguitées
  arbre_haplo *Arbre = NULL;//création de l'arbre que l'on initialise à NULL.
  ajouter_noeud(&Arbre,'D',1);//ajout du premier noeud 'D' (Depart),pour gérerle cas où le premier caractère du genotype est une ambiguitéee
  for(i = 0; i<lgGenotype;i++){
    //parcours de chaque position du genotype.
    if(geno[i] == '0' || geno[i] == '1'){
      // si la position du genotype est égal à 0 ou à 1 ce n'est pas une ambiguitée,
      //on apelle la fonction ajouter_noeud dans le cas 1
      ajouter_noeud(&Arbre,geno[i],1);
    }else if(geno[i]  == '2'){
      //si la position du genotype est égal à 2 c'est une ambiguitée,
      //on incrémente le compteur d'ambiguitée et on apelle la fonction ajouter_noeud dans le cas 2
      cpt++;
      ajouter_noeud(&Arbre,'0',2);
    }
  }
  *nb_Amb = cpt;
  return Arbre;
}

//************************************************************************
// Procédure de parcours d'un arbre binaire
//************************************************************************
void parcours_Arbre(arbre_haplo *Arbre) {
  if(Arbre)
  {
    printf("%c, ", Arbre->carac);
    parcours_Arbre(Arbre->gauche);
    parcours_Arbre(Arbre->droit);
  }
}

//************************************************************************
// Fonction de conversion de la pile en tableau de caractères
//************************************************************************
int pile_to_array(pile *pile, int i,char *haplo) {
  //Fonction récursive qui permet de convertir une pile de caractères en un tableau.
  if(pile)
  {
    if(pile->carac!='D' && pile->carac!='\0'){
      // on rempli la pile avec la valeur du noeud de l'arbre sauf si on est sur le premier noeud 'D'(départ);
      haplo[i]=pile->carac;
      i++;
    }
    i =  pile_to_array(pile->precedent,i,haplo);
  }
  return i;
}

//************************************************************************
// Fonction de conversion de l'abre d'haplotypes en matrice d'haplotypes
//************************************************************************
int tree_to_matrix(arbre_haplo *Arbre, pile **pile, char **haplo, int lgGenotype, int pos) {
  //Fonction récursive qui permet de tranformer l'arbre d'haplotype en une matrice deux dimension.
  int i;
  if(Arbre){
    pile_ajouter(&(*pile),Arbre->carac);
    if (Arbre->carac != 'S' && Arbre->gauche==NULL && Arbre->droit==NULL)
    //la pile n'est transformé en tableau que si on est au bout de l'arbre.
    {
      i=pile_to_array(*pile, 0, haplo[pos]);
      pos++;
    }
    pos = tree_to_matrix(Arbre->gauche,&(*pile), haplo, lgGenotype, pos);
    pos = tree_to_matrix(Arbre->droit,&(*pile), haplo, lgGenotype, pos);
    pile_retirer(&(*pile));
  }
  return pos;
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
//       // Ajout conditions pour changer freq dans la liste d'haplotypes uniques
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


// ************************************************************************
// Procédure de création de liste d'haplo avec geno liés
// ************************************************************************
// void liste_haplo_geno(){
//   TPtr_geno p1 = *adr_liste_geno;
//   TPtr_haplo p2 = *adr_liste_haplo_geno;
//   while (p1!=NULL){
//     while(p1->liste_haplo != NULL){
//       if( liste_haplo_geno->hh!= p1->liste_haplo->haplo1){
//         ajouter_haplo(liste_haplo_geno,p1->liste_haplo->haplo1);
//         liste_haplo_geno->liste_gen_exp->num_geno=p1->num_geno;
//         liste_haplo_geno->liste_gen_exp=liste_haplo_geno->liste_gen_exp->next;
//       }
//       p1->liste_haplo=p1->liste_haplo->next;
//     }
//     p1=p1->next;
//   }
// } PAS BON


//
// //************************************************************************
// // Procédure de maximisation
// //************************************************************************
// void maximisation(TPtr_geno* adr_liste_geno, TPtr_haplo* adr_liste_haplo){
//   TPtr_geno p1 = *adr_liste_geno;
//   TPtr_haplo p2 = *adr_liste_haplo;
//   while(p1!=NULL){
//
//
//   }
// }
//
