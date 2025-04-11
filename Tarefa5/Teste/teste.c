#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoArvore {
    int poder; // valor numérico que representa o poder de um monstro.
    struct NoArvore *esq, *dir; // ponteiros para subárvores esquerda e direita.
} NoArvore, *p_no_arvore;


typedef struct NoPilha {
    int poder; // valor numérico que representa o poder de um monstro.
    struct NoPilha *prox; // ponteiro para o próximo elemento na pilha.
} NoPilha, *p_no_pilha;


p_no_arvore cria_percursos() {

  // Alocar memória para um ponteiro de árvore e setar as componentes como zeradas
  p_no_arvore tree = malloc(sizeof(struct NoArvore));
  tree->poder = 0;
  tree->esq = NULL;
  tree->dir = NULL;

  return tree;
}


p_no_arvore insere_monstro(p_no_arvore raiz, int poder) {
  
  // Final de uma chamada recursiva
  if (raiz->poder == 0) {
    p_no_arvore inseri = cria_percursos();
    inseri->poder = poder;

    inseri->dir = cria_percursos();
    inseri->esq = cria_percursos();
    
    return inseri;
  }

  // Caso definido pelo enunciado como guia do problema
  if (poder < raiz->poder) {
    raiz->esq = insere_monstro(raiz->esq, poder);
  }
  else {
    raiz->dir = insere_monstro(raiz->dir, poder);
  }

  return raiz;
}


p_no_pilha cria_pilha() {

    // Alocar memória para um ponteiro de pilhas e seta-lo como nulo
    p_no_pilha out = malloc(sizeof(struct NoPilha));
    out->poder = -1;
    out->prox = NULL;

    return out;
}


void destroi_percursos(p_no_arvore raiz) {
    if (raiz == NULL) {
        return;
    }

    destroi_percursos(raiz->esq);
    destroi_percursos(raiz->dir);

    free(raiz);
}


p_no_pilha insere_na_pilha(p_no_pilha topo, int poder) {
    if (topo->poder == 0){
        topo->poder = poder;
        return topo;
    }
    else { 
    p_no_pilha novo = cria_pilha();
    novo->poder = poder;
    novo->prox = topo;
    return novo;
    }
}


p_no_pilha remove_da_pilha(p_no_pilha topo, int *poder) {
    if (topo == NULL) {
        return topo;
    }

    p_no_pilha temp = topo;
    *poder = topo->poder;
    topo = topo->prox;
    free(temp);
    return topo;
}


void destroi_pilha(p_no_pilha topo) {
    while (topo->prox != NULL) {
        p_no_pilha temp = topo;
        topo = topo->prox;
        free(temp);
    }
}


// Função para medir o tamanho da pilha
int tamanho_pilha(p_no_pilha topo) {
    int tamanho = 0;
    while (topo->poder != -1) {
        // Incrementa o tamanho da pilha até o primeiro marcador de outro caminho
        tamanho++; 
        topo = topo->prox;
    }
    return tamanho;
}


void imprime_pilha(p_no_pilha topo) {
    p_no_pilha temp = topo;
    int caminho_count = 0; 
    int block = tamanho_pilha(temp);

    // Conta a quantidade de caminhos e armazena os elementos, em ordem reversa, em uma nova pilha
    p_no_pilha pilha_reversa = cria_pilha();
    while (temp != NULL) {
        if (temp->poder == -1 && block > 0) {
            caminho_count++;
        }
        pilha_reversa = insere_na_pilha(pilha_reversa, temp->poder);
        temp = temp->prox;
    }

    // Imprime a quantidade de caminhos
    printf("%d", caminho_count);

    // Imprime os caminhos da pilha reversa
    temp = pilha_reversa;
    while (temp->prox != NULL && caminho_count != 0) {
        if (temp->poder == -1) {
            printf("\n"); // Inicia um novo caminho
        }
        else if (temp->prox->poder == -1) {
            printf("%d", temp->poder); // Final da linha
        } 
        else {
            printf("%d, ", temp->poder);
        }
        temp = temp->prox;
    }

    // Desaloca a memória da pilha reversa
    destroi_pilha(pilha_reversa);
}


// Função para encontrar todos os caminhos na árvore e armazenar os caminhos mais longos na pilha "caminhos"
p_no_pilha busca(p_no_arvore raiz, int vida_personagem, p_no_pilha caminhos, p_no_pilha caminhos_mais_longos) {
    if (raiz->poder == 0) {
        return caminhos_mais_longos;
    }

    // Empilha o nó atual na pilha "caminhos"
    caminhos = insere_na_pilha(caminhos, raiz->poder);

    // Subtrai o poder do monstro do poder do personagem
    vida_personagem -= raiz->poder;

    // Se chegou a um nó folha e a vida do personagem é positiva, verifica se é um caminho mais longo
    if (raiz->esq->poder == 0 && raiz->dir->poder == 0 && vida_personagem > 0) {
        // Variável para atualização dos caminhos
        p_no_pilha novo;
        novo = caminhos;

        // Atualiza a pilha de caminhos mais longos
        if (tamanho_pilha(caminhos) > tamanho_pilha(caminhos_mais_longos)) {
            
            // Se o caminho atual é mais longo quanto o mais longo encontrado até agora
            destroi_pilha(caminhos_mais_longos);
            caminhos_mais_longos = cria_pilha(caminhos_mais_longos);
            while (novo->poder != -1) {
                caminhos_mais_longos = insere_na_pilha(caminhos_mais_longos, novo->poder);
                novo = novo->prox;
            }
        }
        // Atualiza a pilha de caminhos mais longos
        else if (tamanho_pilha(caminhos) == tamanho_pilha(caminhos_mais_longos)) {
            // Marque o final do caminho anterior com -1 na pilha "caminhos_mais_longos"
            caminhos_mais_longos = insere_na_pilha(caminhos_mais_longos, -1);

            // Se o caminho atual é tão longo quanto o mais longo encontrado até agora
            while (novo->poder != -1) {
                caminhos_mais_longos = insere_na_pilha(caminhos_mais_longos, novo->poder);
                novo = novo->prox;
            }
        }
        // Desempilhe o nó atual para retroceder na árvore
        caminhos = remove_da_pilha(caminhos, &(raiz->poder));

        return caminhos_mais_longos;
    }

    // Continue a busca nos nós filhos
    caminhos_mais_longos = busca(raiz->esq, vida_personagem, caminhos, caminhos_mais_longos);
    caminhos_mais_longos = busca(raiz->dir, vida_personagem, caminhos, caminhos_mais_longos);

    // Desempilhe o nó atual para retroceder na árvore
    caminhos = remove_da_pilha(caminhos, &(raiz->poder));

    return caminhos_mais_longos;
}


void busca_caminhos(p_no_arvore raiz, int vida_personagem) {
    // Cria uma pilha para armazenar os caminhos encontrados
    p_no_pilha caminho = cria_pilha();
    p_no_pilha caminhos_mais_longos = cria_pilha();

    // Encontra todos os caminhos na árvore e armazena na pilha "caminhos"
    caminhos_mais_longos = busca(raiz, vida_personagem, caminho, caminhos_mais_longos);

    // Imprime os caminhos mais longos
    imprime_pilha(caminhos_mais_longos);

    // Desaloca a memória da pilha de caminhos
    destroi_pilha(caminho);
    destroi_pilha(caminhos_mais_longos);
}


int main () {

  // Inicializar uma árvore binária para os monstros
  p_no_arvore ghost_tree = cria_percursos();

  // Ler o número de monstro da floresta
  int numero_monstro, monstro, power;
  scanf("%d", &numero_monstro);

  // Colocando todos os monstros na árvore binária
  for (int i = 0; i < numero_monstro; i++) {

    // Ler o poder dos monstros
    scanf("%d", &monstro);

    if (i == 0) {
      ghost_tree->poder = monstro;
      ghost_tree->dir = cria_percursos();
      ghost_tree->esq = cria_percursos();
    }

    else {      
      ghost_tree = insere_monstro(ghost_tree, monstro);
    }
  }

  // Meu poder de luta
  scanf("%d", &power);

  // Percorre todos os caminhos da árvore, em ordem crescente, buscando as saidas
  // Imprime os caminhos mais longos da arvore
  busca_caminhos(ghost_tree, power);

  destroi_percursos(ghost_tree);
  
  return 0;
}
