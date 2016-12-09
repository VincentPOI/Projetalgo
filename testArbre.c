#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// typedef struct pile
// //une pile qui permet de récupérer les différents haplotypes dans l'arbre
// {
//   char carac;
//   struct pile *precedent;
// } pile;

// void pile_ajouter(pile **p_pile, char carac)
// {
//   pile *new_pile = malloc(sizeof *new_pile);
//   {
//     new_pile->carac = carac;
//     new_pile->precedent = *p_pile;
//     *p_pile = new_pile;
//   }
// }

// void pile_retirer(pile **p_pile)
// {
//   char ret = "\0";
//   if (p_pile != NULL)
//   {//stockage
//     pile *temp = (*p_pile)->precedent;
//     ret = (*p_pile)->carac;
//     free(*p_pile), *p_pile = NULL;
//     *p_pile = temp;
//   }
// }

// typedef struct arbre_haplo
// /*
// Structure de type arbre binaire qui sert à générer
// tout les haplotypes possibles d'un genotype.
// */
// {
//   char carac;
//   struct arbre_haplo *gauche;
//   struct arbre_haplo *droit;
// }arbre_haplo;

// void ajouter_noeud(arbre_haplo **Arbre, char val, int cas)
// /*
// Fonction récursive qui permet d'ajouter un noeud à un arbre.
// Elle prend en entrée :
// -Un arbre_haplo (Arbre);
// -Un char, valeur que doit prendre le nouveau noeud;
// -Un entier cas, qui prend la valeur 1 ou 2
//  le cas "1" correspond à un ajout sans ambiguitée
//  le cas "2" correspond à un ajout avec ambiguitée
// */
// {
//   if( *Arbre == NULL )
//   /*
//   si l'arbre est null donc que l'on est arrivé au bout du parcours récursif:
//   on peut donc ajouter un nouveau noeud.
//   */
//   {
//     *Arbre = (arbre_haplo*) malloc( sizeof( arbre_haplo ));//on lui alloue de la mémoire
//     (*Arbre)->carac = val;// définition de sa valeur
//     (*Arbre)->gauche =NULL;
//     (*Arbre)->droit = NULL;
//   }else if((*Arbre)->carac != 'S'){
//     /*
//     Sinon si l'arbre(le noeud) est non null on parcours l'arbre jusquà arriver au bout.
//     (on évite les 'S' afin de ne pas générer des branches ne contenant pas les ambiguitée')
//     */
//     if (cas == 1)
//     //cas 1: pas d'ambiguitée
//     {
//       if((*Arbre)->gauche == NULL && (*Arbre)->droit ==NULL){
//         /*
//         Cette condition verifie que le noeud est l'avant dernier et donc que le prochain
//         récursif créera le nouveau noeud et défénira sa valeur.
//         Dans le "cas" 1 (pas d'ambiguitée) il faut donc Mettre 'S'(STOP) dans le fils droit.
//         */
//         ajouter_noeud( &(*Arbre)->gauche , val, 1);
//         ajouter_noeud( &(*Arbre)->droit, 'S', 1);
//       }else{
//         /*
//         quand cette condition n'est pas vérifier on se contente de continuer à parcourir l'arbre.
//         */
//         ajouter_noeud( &(*Arbre)->gauche , val, 1);
//         ajouter_noeud( &(*Arbre)->droit , val, 1);
//       }
//
//     }
//     if (cas == 2){
//       //cas 2 pas d'ambiguitée, on continu d'appeler la fonction récursive jusqu'à
//       //arriver au bout de l'arbre et définir la valeur des noeuds.
//       ajouter_noeud( &(*Arbre)->gauche , '3', 2);
//       ajouter_noeud( &(*Arbre)->droit , '4', 2);
//     }
//   }
// }

// arbre_haplo* generate_tree_from_geno(char* geno, int lgGenotype, int *nb_Amb)
// /*
// Fonction qui prend en paramètre:
// -une chaine de caractère contenant un génotype(geno);
// -un entier, la longueur du génotype (lgGenotype);
// -un entier qui peermet de compter le nombre d'ambiguitée dans le génotype (nb_amb);
// et qui retourne :
// -une structure de type arbre_haplo qui contient tout les haplotype possibles
// */
// {
//   int i;
//   int cpt=0;//compteur qui compte les ambiguitées
//   arbre_haplo *Arbre = NULL;//création de l'arbre que l'on initialise à NULL.
//   ajouter_noeud(&Arbre,'D',1);//ajout du premier noeud 'D' (Depart),pour gérerle cas où le premier caractère du genotype est une ambiguitéee
//   for(i = 0; i<lgGenotype;i++){
//     //parcours de chaque position du genotype.
//     if(geno[i] == '0' || geno[i] == '1'){
//       // si la position du genotype est égal à 0 ou à 1 ce n'est pas une ambiguitée,
//       //on apelle la fonction ajouter_noeud dans le cas 1
//       ajouter_noeud(&Arbre,geno[i],1);
//     }else if(geno[i]  == '2'){
//       //si la position du genotype est égal à 2 c'est une ambiguitée,
//       //on incrémente le compteur d'ambiguitée et on apelle la fonction ajouter_noeud dans le cas 2
//       cpt++;
//       ajouter_noeud(&Arbre,'0',2);
//     }
//   }
//   *nb_Amb = cpt;
//   return Arbre;
// }



// void parcours_Arbre(arbre_haplo *Arbre){
//   if(Arbre)
//   {
//     printf("%c, ", Arbre->carac);
//     parcours_Arbre(Arbre->gauche);
//     parcours_Arbre(Arbre->droit);
//   }
// }
//
//
// int pile_to_array(pile *pile, int i,char *haplo){
//   //Fonction récursive qui permet de convertir une pile de caractères en un tableau.
//   if(pile)
//   {
//     if(pile->carac!='D' && pile->carac!="\0"){
//       // on rempli la pile avec la valeur du noeud de l'arbre sauf si on est sur le premier noeud 'D'(départ);
//       haplo[i]=pile->carac;
//       i++;
//     }
//     i =  pile_to_array(pile->precedent,i,haplo);
//   }
//   return i;
// }
//
// int tree_to_matrix(arbre_haplo *Arbre, pile **pile, char **haplo, int lgGenotype, int pos){
//   //Fonction récursive qui permet de tranformer l'arbre d'haplotype en une matrice deux dimension.
//   int i;
//   if(Arbre){
//     pile_ajouter(&(*pile),Arbre->carac);
//     if (Arbre->carac != 'S' && Arbre->gauche==NULL && Arbre->droit==NULL)
//     //la pile n'est transformé en tableau que si on est au bout de l'arbre.
//     {
//       i=pile_to_array(*pile, 0, haplo[pos]);
//       pos++;
//     }
//     pos = tree_to_matrix(Arbre->gauche,&(*pile), haplo, lgGenotype, pos);
//     pos = tree_to_matrix(Arbre->droit,&(*pile), haplo, lgGenotype, pos);
//     pile_retirer(&(*pile));
//   }
//   return pos;
// }


int main(){
  int nb_Amb;
  int i;
  int j;
  char geno[] = "2222222222";

  arbre_haplo *Arbre = generate_tree_from_geno(geno, 10, &nb_Amb);


  int pownb = (int)(pow(2.0,(double)(nb_Amb)));
  char **matrice_haplo = (char**) malloc(sizeof(char*)*pownb);
  for (i = 0; i < pownb; i++) {
    matrice_haplo[i] = (char*) malloc(sizeof(char)*10);
  }

  pile* pile =  malloc(sizeof *pile);
  int pos = tree_to_matrix(Arbre, &pile, matrice_haplo,10,0);
  for (j = 0; j < pownb; j++) {
    for(i=0;i<10;i++){
      printf("Haplo[%d][%d] %c\n",j,i,matrice_haplo[j][i]);
    }
  }
  return 0;
}
