/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: vincent
 *
 * Created on 17 octobre 2016, 13:46
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct type_lst_haplo type_lst_haplo;

struct type_lst_haplo {
    int haplo;
    struct type_lst_haplo* nxt;
};

typedef struct type_lst_gen type_lst_gen;

struct type_lst_gen {
    int geno;
    type_lst_haplo* liste_haplo;
    struct type_lst_gen* nxt;
};

type_lst_gen* ajouter_geno(type_lst_gen* liste, int nvGeno, type_lst_haplo* nvListe_haplo) {
    /* Création d'un nouveau génotype*/
    type_lst_gen* nouveau = malloc(sizeof (type_lst_gen));
    nouveau->geno = nvGeno;
    nouveau->liste_haplo = nvListe_haplo;

    /* Insertion de l'élément au début de la liste */
    nouveau->nxt = liste;
}

type_lst_haplo* ajouter_haplo(type_lst_haplo* liste, int nvHaplo) {
    /* Création d'un nouveau génotype*/
    type_lst_haplo* nouveau = malloc(sizeof (type_lst_haplo));
    nouveau->haplo = nvHaplo;
    /* Insertion de l'élément au début de la liste */
    nouveau->nxt = liste;
}

void afficher_geno(type_lst_gen* liste) {
    type_lst_gen *tmp = liste;
    type_lst_haplo* tmp2;
    while (tmp != NULL) {
        printf("genotype n°%d: ", tmp->geno);
        for (tmp2 = tmp; tmp2 != NULL; tmp2 = tmp2->nxt) {
        printf("%d,", tmp2->haplo);
    }
        tmp = tmp->nxt;
    }
}

void afficher_haplo(type_lst_haplo* liste) {
    type_lst_haplo* temp;
    for (temp = liste; temp != NULL; temp = temp->nxt) {
        printf("%d\n", temp->haplo);
    }
}

int main() {
    type_lst_gen* ma_liste = NULL;
    type_lst_haplo* listehaplo = NULL;
    afficher_geno(ma_liste);
    return 0;
}
