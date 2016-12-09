//************************************************************************
// Structure de liste de génotypes étant expliqués par un même haplotype
//************************************************************************
typedef struct type_lst_gen_exp type_lst_gen_exp;

struct type_lst_gen_exp{
  int num_geno;
  struct type_lst_gen_exp* next;
};

//************************************************************************
// Structure pour les haplotypes
//************************************************************************
typedef struct type_lst_haplo type_lst_haplo;

struct type_lst_haplo{
  int num_haplo1;
  char* haplo1;
  int num_haplo2;
  char* haplo2;
  int nbocc_haplo1;
  int nbocc_haplo2;
  double freq_haplo1;
  double freq_prec_haplo1;
  double freq_haplo2;
  double freq_prec_haplo2;
  type_lst_gen_exp* liste_gen_exp;
  struct type_lst_haplo* next;
};

typedef type_lst_haplo* TPtr_haplo;

///************************************************************************
// Structure pour les génotypes
//************************************************************************
typedef struct type_lst_gen type_lst_gen;

struct type_lst_gen{
  int num_geno;
  char* seq_geno;
  double proba_geno;
  double proba_prec_geno;
  type_lst_haplo* liste_haplo_geno;
  struct type_lst_gen* next;
};

typedef type_lst_gen* TPtr_geno;

//************************************************************************
// Pile permettant de récupérer les différents haplotypes dans l'arbre
//************************************************************************
typedef struct pile pile;

struct pile{
  char carac;
  struct pile *precedent;
};

//************************************************************************
// Arbre binaire servant à générer tous les haplotypes possibles d'un genotype
//************************************************************************
typedef struct arbre_haplo arbre_haplo;

struct arbre_haplo{
  char carac;
  struct arbre_haplo *gauche;
  struct arbre_haplo *droit;
};
