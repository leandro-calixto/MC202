#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100
#define MIN_STR 20

typedef struct
{
  char * doi, ** autor;
  int ano, n_autores, volume;
} ficha;


int busca_ficha (ficha ** ptr_vetor, int n, char * doi) {
   for (int i = 0; i < n; i++) {
      if ((strcmp(ptr_vetor[i]->doi, doi)) == 0) {
         return i;
         break;
      }
   }
   return -1;
}


ficha ** cria_fichario (int n) {
  // Aloca dinamicamente um vetor de ponteiros para fichas
  ficha **fichario = (ficha **)malloc(n * sizeof(ficha *));
  if (fichario == NULL) {
    perror("Erro ao alocar memória");
    exit(1);
  }
  // Crie as fichas vazias com valores padrão
  for (int i = 0; i < n; i++) {
      fichario[i] = (ficha *)malloc(sizeof(ficha));
      if (fichario[i] == NULL) {
         perror("Erro ao alocar memória");
         exit(1);
      }
      // Inicializa os campos da ficha com valores padrão
      strcpy(fichario[i]->doi, "");
      fichario[i]->n_autores = 0;
      fichario[i]->ano = 0;
      fichario[i]->volume = 0;
      fichario[i]->autor = (char **)malloc(MIN_STR * sizeof(char *));
      if (fichario[i]->autor == NULL) {
         perror("Erro ao alocar memória");
         exit(1);
      }
      for (int j = 0; j < MIN_STR; j++) {
         fichario[i]->autor[j] = NULL;
      }
   }
   return fichario;
}



void imprime_ficha(ficha *ptr_artigo) {
    printf("%s", ptr_artigo->doi);

    // Conta a quantidade de autores não vazios
    int count = 0;
    for (int i = 0; i < ptr_artigo->n_autores; i++) {
        if (ptr_artigo->autor[i] != NULL && ptr_artigo->autor[i][0] != '\0') {
            if (count == 0) {
                printf(" %s", ptr_artigo->autor[i]);
            } else {
                printf(", %s", ptr_artigo->autor[i]);
            }
            count++;
        }
    }

    printf(" %d %d\n", ptr_artigo->ano, ptr_artigo->volume);
}



int insere_ficha (ficha ** ptr_vetor, int n, ficha * ptr_artigo) {
   for (int i = 0; i < n; i++) {
      if (strlen((*ptr_vetor)[i].doi) == 0) { // Verifica se o DOI está vazio
         strcpy((*ptr_vetor)[i].doi, ptr_artigo->doi); // Copia o DOI para o vetor
         // Copie outros campos da ficha, se houverem
         return 1; // Inserção bem-sucedida
      }
   }
   return 0; // Não há índices disponíveis
}

ficha *le_ficha() {
    ficha *nova_ficha = (ficha *)malloc(sizeof(ficha));
    if (nova_ficha == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    char info[MAX_STR];
    char temp_autor[MAX_STR]; // Variável temporária para ler os sobrenomes dos autores
    fgets(info, sizeof(info), stdin);
    sscanf(info, "%s %[^\n] %d %d %d", nova_ficha->doi, temp_autor, &nova_ficha->n_autores, &nova_ficha->ano, &nova_ficha->volume);
    
    // Aloca memória para nova_ficha->doi e copia a string
    nova_ficha->doi = (char *)malloc(strlen(nova_ficha->doi) + 1);
    if (nova_ficha->doi == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    // Aloca memória para nova_ficha->autor e copia a string
    nova_ficha->autor = (char **)malloc(strlen(temp_autor) + 1);
    if (nova_ficha->autor == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    for (int i = 0; i < nova_ficha->n_autores; i++) {
      strcpy(nova_ficha->autor[i], temp_autor); // Copia o autor para nova_ficha->autor
    }
    
    return nova_ficha;
}


int remove_ficha (ficha ** ptr_vetor, int n, char * doi) {
   for (int i = 0; i < n; i++) {
      if (strcmp((ptr_vetor)[i]->doi, doi) == 0) { // Verifica se o DOI corresponde
         strcpy((ptr_vetor)[i]->doi, ""); // Define o DOI como string vazia
         return 1; // Remoção bem-sucedida
      }
   }
   return 0; // DOI não encontrado
}


void destroi_ficha(ficha * ptr_artigo) {
   free(ptr_artigo);
}


int main() {
    ficha **fichario = (ficha **)malloc(3 * sizeof(ficha *));

    // Alocar memória para cada ficha e seus campos
    for (int i = 0; i < 3; i++) {
        fichario[i] = (ficha *)malloc(sizeof(ficha));
        fichario[i]->doi = (char *)malloc(MAX_STR * sizeof(char));
        fichario[i]->autor = (char **)malloc(3 * sizeof(char *));
        for (int j = 0; j < 3; j++) {
            fichario[i]->autor[j] = (char *)malloc(MAX_STR * sizeof(char));
        }
    }

    // Atribuir valores às fichas individuais
    for (int i = 0; i < 3; i++) {
        strcpy(fichario[i]->doi, "DOI");  // Substitua "DOI" pelo valor desejado
        strcpy(fichario[i]->autor[0], "Calixto");  // Substitua "Calixto" pelo valor desejado
        strcpy(fichario[i]->autor[1], "Camargo");  // Substitua "Calixto" pelo valor desejado
        strcpy(fichario[i]->autor[2], "Silva");  // Substitua "Calixto" pelo valor desejado
        fichario[i]->ano = 2020 + i;
        fichario[i]->n_autores = i;
        fichario[i]->volume = 10 * i;
    }

    // Ou você pode usar um loop para percorrer todo o vetor e imprimir os valores
    for (int i = 0; i < 3; i++) {
        printf("%s %s, %s, %s, %d %d %d\n", fichario[i]->doi, fichario[i]->autor[0], fichario[i]->autor[1], 
        fichario[i]->autor[2], fichario[i]->n_autores, fichario[i]->ano, fichario[i]->volume);
    }

    // Certifique-se de liberar a memória alocada quando não precisar mais
    for (int i = 0; i < 3; i++) {
        printf(" %d\n", fichario[i]->autor[0][0]);
        free(fichario[i]->doi);
        for (int k = 0; k < 3; k++) {
            free(fichario[i]->autor[k]);
        }
        free(fichario[i]->autor);
        free(fichario[i]);
    }
    free(fichario);

    return 0;
}