#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100
#define MAX_AUT 15

typedef struct no *p_no;

struct no {
  char *doi, **autor;
  int ano, n_autores, volume;
  p_no prox;
};


p_no busca_ficha(p_no primeiro, char *doi) {
  p_no atual = primeiro; 
  while (atual != NULL) {
    if (strcmp(atual->doi, doi) == 0) {
      return atual;
    }
    atual = atual->prox;
  }
  return NULL;
}


void imprime_ficha(p_no primeiro) {
    printf("%s", primeiro->doi);
    for (int i = 0; i < primeiro->n_autores && i < 3; i++) {
      if (i == 0) {
         printf(" %s", primeiro->autor[i]);
      } 
      else if (i == 2 && primeiro->n_autores != 3) {
         printf(", %s,", primeiro->autor[i]);
         }
      else if (i == 2 && primeiro->n_autores == 3) {
        printf(", %s", primeiro->autor[i]);
      }
      else {
         printf(", %s", primeiro->autor[i]);
         }
      }
    if (primeiro->n_autores > 3) {
      printf(" et al. (%d) %d\r\n", primeiro->ano, primeiro->volume);
    }
    else {
      printf(" (%d) %d\r\n", primeiro->ano, primeiro->volume);
    }
}


p_no cria_fichario() {

    p_no fichario = malloc(sizeof(struct no)); 
    if (fichario == NULL) {
        exit(1);
    }
    fichario->doi = NULL; 
    fichario->autor = NULL;
    fichario->ano = 0;
    fichario->n_autores = 0;
    fichario->volume = 0;
    fichario->prox = NULL;

    return fichario;
}


p_no le_ficha() {
    p_no nova_ficha = cria_fichario();

    // Alocação de memória para doi e autor
    nova_ficha->doi = (char *)malloc(MAX_STR * sizeof(char));
    nova_ficha->autor = (char **)malloc(MAX_AUT * sizeof(char *));

    // Leitura dos campos da ficha
    scanf("%s", nova_ficha->doi);
    scanf("%d", &nova_ficha->n_autores);

    for (int i = 0; i < nova_ficha->n_autores; i++) {
        nova_ficha->autor[i] = (char *)malloc(MAX_STR * sizeof(char));
        scanf("%s", nova_ficha->autor[i]);
    }

    scanf("%d", &nova_ficha->ano);
    scanf("%d", &nova_ficha->volume);

    return nova_ficha;
}



p_no insere_ficha(p_no primeiro, p_no novo){

  //cria, aloca memória e copia a informação do novo para um ponteiro a se adicionar no primeiro
  p_no inseri = cria_fichario(); 

  inseri->doi = (char *)malloc((strlen(novo->doi) + 1) * sizeof(char));
  strcpy(inseri->doi, novo->doi);
  
  inseri->n_autores = novo->n_autores;
  inseri->autor = (char **)malloc(novo->n_autores * sizeof(char *));
  for (int i = 0; i < novo->n_autores; i++) {
      inseri->autor[i] = (char *)malloc((strlen(novo->autor[i]) + 1) * sizeof(char));
      strcpy(inseri->autor[i], novo->autor[i]);
  }

  inseri->ano = novo->ano;
  inseri->volume = novo->volume;

  if (primeiro == NULL) {
    primeiro = inseri;
  }
  else {
    p_no anterior = primeiro;
    primeiro = inseri;
    primeiro->prox = anterior;
  }

  return primeiro;
}


p_no remove_ficha(p_no primeiro, char *doi) {
  p_no começo = primeiro;
  p_no anterior = primeiro;
  p_no atual = primeiro; 

  //percorre todas as listas ligadas
  while (atual != NULL) {
    if (strcmp(atual->doi, doi) == 0) {
      
      //atualização dos ponteiros do fichario
      if (atual == começo) {
        começo = atual->prox;
      }
      else { 
        anterior->prox = atual->prox;
      }

      //apaga a ficha
      for(int i = 0;i < atual->n_autores; i++) { 
        free(atual->autor[i]);
      }
      free(atual->autor);
      free(atual->doi);

      return começo;
    }

    //controle para atualização da nova configuração
    anterior = atual;
    atual = atual->prox;
  }
  return NULL;
}


void destroi_fichas(p_no primeiro) {

    //recursivamente, libera a memória de todos os dados ligados 
    if (primeiro->prox != NULL) {
        destroi_fichas(primeiro->prox);
    }
    
    for(int i = 0;i < primeiro->n_autores; i++) { 
        free(primeiro->autor[i]);
    }
    free(primeiro->autor);
    free(primeiro->doi);
    free(primeiro);
}


int main () {   
  int loop = 1, fichas = 0;
  p_no fichario;

  while (loop == 1) {

    //leitura das entradas
    char *command = (char *)malloc(50 * sizeof(char *));
    scanf(" %[^\n]", command);

    if (command[0] == 'N'){
      fichario = NULL;
    }

    else if (command[0] == 'I'){

        sscanf(command, "I %d", &fichas);

        //loop para ler todas as fichas que vão entrar
        for (int k = 0; k < fichas; k++) {   

            //le a entrada    
            p_no nova_ficha = le_ficha();                         

            //aloca a entrada no fichario
            fichario = insere_ficha(fichario, nova_ficha);

            //desaloca a memoria utilizada para a entrada
            destroi_fichas(nova_ficha);       
        }
    } 
         

    else if (command[0] == 'P') {
      p_no atual = fichario;
      while (atual != NULL) {
        imprime_ficha(atual);
        atual = atual->prox;
      }
    }

    
    else if (command[0] == 'B') {

      //lê o doi da entrada
      char *DOI = (char *)malloc(50 * sizeof(char));
      sscanf(command, "B %s", DOI);

      p_no j = busca_ficha(fichario, DOI);
      if (j == NULL) {
          printf("DOI %s inexistente\r\n", DOI);
      }
      else {
          int k;
          for (k = 0; k < j->n_autores && k < 3; k++) {
            printf("%s ", j->autor[k]);
          }
          if (j->n_autores > 3) {
            printf("et al. (%d) %d\r\n", j->ano, j->volume);
          }
          else {
            printf("(%d) %d\r\n", j->ano, j->volume);
          } 
      }
      free(DOI);
    }

    else if (command[0] == 'R') {
      
      //lê o doi da entrada
      char *DOI = (char *)malloc(50 * sizeof(char));
      sscanf(command, "R %s", DOI);

      p_no j = busca_ficha(fichario, DOI);
      if (j == NULL) {
        printf("DOI %s inexistente\r\n", DOI);
      }
      else {
        fichario = remove_ficha(fichario, DOI);
        printf("DOI %s removido\r\n", DOI); 
      }
      free(DOI);
    }

    else if (command[0] == 'F') {
        loop = 0;
    }

    free(command);
  }                                                 

  //liberando toda a memória do fichario
  destroi_fichas(fichario);

  return 0;

}