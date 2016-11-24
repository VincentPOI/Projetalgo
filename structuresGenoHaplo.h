typedef struct type_lst_haplo type_lst_haplo;

struct type_lst_haplo{
  int num_haplo1;
  int* haplo1;
  int num_haplo2;
  int* haplo2;
  int freq_haplo1;
  int freq_haplo2;
  struct type_lst_haplo* nxt;
};

typedef type_lst_haplo* TPtr_haplo;

typedef struct type_lst_gen type_lst_gen;

struct type_lst_gen{
  int num_geno;
  char* seq_geno;
  //type_lst_haplo* liste_haplo;
  struct type_lst_gen *next;
};

typedef type_lst_gen* TPtr_geno;
