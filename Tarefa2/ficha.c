#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100
#define MAX_AUT 15

typedef struct
{
  char * doi, ** autor;
  int ano, n_autores, volume;
} ficha;

ficha ** cria_fichario (int n) {
    // Aloca dinamicamente um vetor de ponteiros para fichas
    ficha **fichario = (ficha **)malloc(n * sizeof(ficha *));

    // Crie as fichas vazias com valores padrão
    for (int i = 0; i < n; i++) {
        fichario[i] = (ficha *)malloc(sizeof(ficha));        

        // Inicializa os campos da ficha com valores padrão ou lixo
        fichario[i]->doi = (char *)malloc(MAX_STR * sizeof(char));       
        strcpy(fichario[i]->doi, " ");
        fichario[i]->autor = (char **)malloc(MAX_STR * sizeof(char *));       //ponteiro para o nome dos autores
        for (int j = 0; j < MAX_AUT; j++) {                                   //vetor com espaço para os nomes
            fichario[i]->autor[j] = (char *)malloc(MAX_STR * sizeof(char));
        }
        fichario[i]->n_autores = 0;      
        fichario[i]->ano = 0;
        fichario[i]->volume = 0;
    }
    return fichario;
}

ficha * le_ficha() { 
    ficha *nova_ficha = (ficha *)malloc(sizeof(ficha));
    nova_ficha->doi = (char *)malloc(MAX_STR * sizeof(char));
    
    // Leitura dos campos da ficha
    scanf("%s", nova_ficha->doi);
    scanf("%d", &nova_ficha->n_autores);

    nova_ficha->autor = (char **)malloc(MAX_STR * sizeof(char *));
    for (int i = 0; i < nova_ficha->n_autores; i++) {
        nova_ficha->autor[i] = (char *)malloc(MAX_STR * sizeof(char));
        scanf("%s", nova_ficha->autor[i]);
    }

    scanf("%d", &nova_ficha->ano);
    scanf("%d", &nova_ficha->volume);

    return nova_ficha;
}

int insere_ficha(ficha **ptr_vetor, int n, ficha *ptr_artigo) {
    // Percorre todo o fichário em busca de um doi vazio
    for (int j = 0; j < n; j++) {                    
        if (strcmp(ptr_vetor[j]->doi, " ") == 0) { 
            // Copia os campos individualmente
            strcpy(ptr_vetor[j]->doi, ptr_artigo->doi);
            ptr_vetor[j]->n_autores = ptr_artigo->n_autores;
            ptr_vetor[j]->ano = ptr_artigo->ano;
            ptr_vetor[j]->volume = ptr_artigo->volume;
            
            // Copia os nomes dos autores individualmente
            for (int i = 0; i < ptr_artigo->n_autores; i++) {
                strcpy(ptr_vetor[j]->autor[i], ptr_artigo->autor[i]);
            }
            
            return 1;
        }
    }
    return -1;
}


void imprime_ficha(ficha *ptr_artigo) {
    printf("%s", ptr_artigo->doi);
    for (int i = 0; i < ptr_artigo->n_autores && i < 3; i++) {
      if (i == 0) {
         printf(" %s", ptr_artigo->autor[i]);
      } 
      else if (i == 2 && ptr_artigo->n_autores != 3) {
         printf(", %s,", ptr_artigo->autor[i]);
         }
      else if (i == 2 && ptr_artigo->n_autores == 3) {
        printf(", %s", ptr_artigo->autor[i]);
      }
      else {
         printf(", %s", ptr_artigo->autor[i]);
         }
      }
    if (ptr_artigo->n_autores > 3) {
      printf(" et al. (%d) %d\r\n", ptr_artigo->ano, ptr_artigo->volume);
    }
    else {
      printf(" (%d) %d\r\n", ptr_artigo->ano, ptr_artigo->volume);
    }
}


int busca_ficha (ficha ** ptr_vetor, int n, char * doi) {
   for (int i = 0; i < n; i++) {
      if ((strcmp(ptr_vetor[i]->doi, doi)) == 0) {
         return i;
         break;
      }
   }
   return -1;
}


int remove_ficha (ficha ** ptr_vetor, int n, char * doi) {
   for (int i = 0; i < n; i++) {
      if (strcmp((ptr_vetor)[i]->doi, doi) == 0) { // Verifica se o DOI corresponde
         strcpy((ptr_vetor)[i]->doi, " "); // Define o DOI como string vazia
         ptr_vetor[i]->n_autores = 0;
         ptr_vetor[i]->ano = 0;                          //setando tudo
         ptr_vetor[i]->volume = 0;  
         for (int j = 0; j < MAX_AUT; j++) {               
            strcpy(ptr_vetor[i]->autor[j], "");
         }
         return 1; // Remoção bem-sucedida
         break;
      }
   }
   return 0; // DOI não encontrado
}

void destroi_ficha(ficha * ptr_artigo) {
    //libera a memoria alocada para a ficha entrada
    free(ptr_artigo->doi);
    for (int l = 0; l < ptr_artigo->n_autores; l++) {
        free(ptr_artigo->autor[l]);
    }
    free(ptr_artigo->autor);
    free(ptr_artigo);
}

int main () {   
  int num_ficha = 0, loop = 1, fichas = 0;
  ficha **fichario = NULL;

  do {

    //leitura das entradas
    char *command = (char *)malloc(50 * sizeof(char *));
    scanf(" %[^\n]", command);

    if (command[0] == 'N'){
      sscanf(command, "N %d", &num_ficha);
      fichario = cria_fichario(num_ficha);
    }

    else if (command[0] == 'I'){

        sscanf(command, "I %d", &fichas);

        int j = 0, k;
        for (k = 0; k < fichas; k++) {                               //loop para ler todas as fichas que vão entrar
            ficha *entrada = le_ficha();                             //le as entradas 
            j = insere_ficha(fichario, num_ficha, entrada);     //se existe vaga no fichario, aloca as entradas nele
            if (j == -1) {
              printf("Erro ao inserir DOI %s\r\n", entrada->doi);
            }
            destroi_ficha(entrada);          
        }
    } 
         

    else if (command[0] == 'P') {
        for (int i = 0; i < num_ficha; i++){ 
            if (strcmp(fichario[i]->doi, " ") != 0) {    
                imprime_ficha(fichario[i]);
            }
        }
    } 
    
    else if (command[0] == 'B') {

      //lê o doi da entrada
      char *DOI = (char *)malloc(50 * sizeof(char));
      sscanf(command, "B %s", DOI);

      int j = busca_ficha(fichario, num_ficha, DOI);
      if (j == -1) {
          printf("DOI %s inexistente\r\n", DOI);
      }
      else {
          int k;
          for (k = 0; k < fichario[j]->n_autores && k < 3; k++) {
            printf("%s ", fichario[j]->autor[k]);
          }
          if (fichario[j]->n_autores > 3) {
            printf("et al. (%d) %d\r\n", fichario[j]->ano, fichario[j]->volume);
          }
          else {
            printf("(%d) %d\r\n", fichario[j]->ano, fichario[j]->volume);
          } 
      }
      free(DOI);
    }

    else if (command[0] == 'R') {
      
      //lê o doi da entrada
      char *DOI = (char *)malloc(50 * sizeof(char));
      sscanf(command, "R %s", DOI);

      int j = busca_ficha(fichario, num_ficha, DOI);
      if (j == -1) {
        printf("DOI %s inexistente\r\n", DOI);
      }
      else {
        remove_ficha(fichario, num_ficha, DOI);
        printf("DOI %s removido\r\n", DOI); 
      }
      free(DOI);
    }

    else if (command[0] == 'F') {
        loop = 0;
    }

    free(command);
  } while (loop == 1);                                                

  //liberando toda a memória do fichario
  for (int i = 0; i < num_ficha; i++) {
    destroi_ficha(fichario[i]);
  }
  free(fichario);

  return 0;

}
