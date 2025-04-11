#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó na árvore de busca binária, representando cada elemento químico.
typedef struct No {
    int numero_atomico;
    char simbolo[3]; // Supondo um limite de 2 caracteres + terminador nulo para o símbolo.
    struct No *esq, *dir; // ponteiros para subárvores esquerda e direita.
} No, *p_no;

/* Operações da Árvore Binária de Busca (ABB) */


// Cria uma nova árvore vazia e retorna um ponteiro para a raiz.
p_no criar_arvore() {
    // Alocar memória para um ponteiro de pilhas e setá-lo como nulo
    p_no out = (p_no)malloc(sizeof(struct No));
    
    out->numero_atomico = -1;
    out->simbolo[0] = '\0'; // Inicializar o símbolo como uma string vazia
    out->esq = NULL; 
    out->dir = NULL;
    
    return out;
}


// Insere um novo elemento químico na árvore.
p_no inserir(p_no raiz, int numero_atomico, char *simbolo){

  // Final de uma chamada recursiva
  if (raiz->numero_atomico == -1) {
    raiz->numero_atomico = numero_atomico;
    strcpy(raiz->simbolo, simbolo);

    raiz->dir = criar_arvore();
    raiz->esq = criar_arvore();
    
    return raiz;
  }

  // Caso definido pelo enunciado como guia do problema
  if (numero_atomico < raiz->numero_atomico) {
    raiz->esq = inserir(raiz->esq, numero_atomico, simbolo);
  }
  else {
    raiz->dir = inserir(raiz->dir, numero_atomico, simbolo);
  }

  return raiz;
}


// Retorna o elemento com o menor número atômico na árvore.
p_no minimo(p_no raiz) {
    while (raiz->esq->numero_atomico != -1) {
        raiz = raiz->esq;
    }
    return raiz;
}


// Retorna o elemento com o maior número atômico na árvore.
p_no maximo(p_no raiz) {
    while (raiz->dir->numero_atomico != -1) {
        raiz = raiz->dir;
    }
    return raiz;
}


// Remove um elemento químico da árvore a partir do nome.
p_no remover(p_no raiz, char *simbolo) {
    p_no atual = raiz;
    if (atual->numero_atomico == -1) {
        // Árvore está vazia ou o elemento não está presente
        return raiz;
    }

    // Buscando recursivamente na esquerda ou na direita o elemento
    if (strcmp(simbolo, raiz->simbolo) != 0) {
        raiz->esq = remover(raiz->esq, simbolo);        
        raiz->dir = remover(raiz->dir, simbolo);
    }
    
    // Elemento encontrado
    else {
        // Caso 1: Nó sem filhos
        if (raiz->dir->numero_atomico == -1 && raiz->esq->numero_atomico == -1) {
            raiz->numero_atomico = -1;
            raiz->simbolo[0] = '\0';
            return raiz;
        }

        // Caso 2: Nó com apenas 1 filho
        else if (raiz->esq->numero_atomico == -1 && raiz->dir->numero_atomico != -1) {
            atual = raiz->dir;
            free(raiz);
            return atual;
        } 
        else if (raiz->dir->numero_atomico == -1 && raiz->esq->numero_atomico != -1) {
            atual = raiz->esq;
            free(raiz);
            return atual;
        }

        // Caso 3: Nó com dois filhos
        else { 
            // Encontro o Nó mais a esquerda do Nó a direita do elemento que vou retirar
            atual = minimo(raiz->dir);

            // Copio os dados do sucessor in-order para este nó
            strcpy(raiz->simbolo, atual->simbolo);
            raiz->numero_atomico = atual->numero_atomico;

            // Removo o sucessor in-order
            raiz->dir = remover(raiz->dir, atual->simbolo);
            return raiz;
        }

    }

    return atual;
}


// Busca um elemento químico na árvore pelo número atômico.
p_no buscar(p_no raiz, int numero_atomico) {
    if (raiz->numero_atomico == -1 || numero_atomico == raiz->numero_atomico){
        return raiz;
    }

    if (numero_atomico < raiz->numero_atomico) { 
        return buscar(raiz->esq, numero_atomico);
    }

    else { 
        return buscar(raiz->dir, numero_atomico);
    }
}


// Desaloca todos os nós da árvore.
void destruir_arvore(p_no raiz) {
    if (raiz == NULL) {
        return;
    }

    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);

    free(raiz);
}


// Função para imprimir os elementos da árvore em ordem crescente
void imprimir_em_ordem_crescente(p_no raiz, char *virgula) {
    if (raiz->numero_atomico != -1) {
        // Lado menor da árvore
        imprimir_em_ordem_crescente(raiz->esq, virgula);
        
        if (strcmp(virgula, "nao") == 0) {
            printf("%s", raiz->simbolo);
            strcpy(virgula, "sim");
        } else {
            printf(", %s", raiz->simbolo);
        }

        // Lado maior da árvore
        imprimir_em_ordem_crescente(raiz->dir, virgula);
    }
}


// Função para procurar um elemento específico
int procura_elemento(p_no raiz, char *simbolo) {
    int resultado = 0;
    if (raiz->numero_atomico != -1) {
        resultado = procura_elemento(raiz->esq, simbolo);
        if (resultado == 1) {
            return 1;
        }
        resultado = procura_elemento(raiz->dir, simbolo);
    }

    if (strcmp(raiz->simbolo, simbolo) == 0 || resultado == 1) {
        return 1;
    }
    else {
        return 0;
    }
}// Cria uma nova árvore vazia e retorna um ponteiro para a raiz.
p_no criar_arvore() {
    // Alocar memória para um ponteiro de pilhas e setá-lo como nulo
    p_no out = (p_no)malloc(sizeof(struct No));
    
    out->numero_atomico = -1;
    out->simbolo[0] = '\0'; // Inicializar o símbolo como uma string vazia
    out->esq = NULL; 
    out->dir = NULL;
    
    return out;
}


// Insere um novo elemento químico na árvore.
p_no inserir(p_no raiz, int numero_atomico, char *simbolo){

  // Final de uma chamada recursiva
  if (raiz->numero_atomico == -1) {
    raiz->numero_atomico = numero_atomico;
    strcpy(raiz->simbolo, simbolo);

    raiz->dir = criar_arvore();
    raiz->esq = criar_arvore();
    
    return raiz;
  }

  // Caso definido pelo enunciado como guia do problema
  if (numero_atomico < raiz->numero_atomico) {
    raiz->esq = inserir(raiz->esq, numero_atomico, simbolo);
  }
  else {
    raiz->dir = inserir(raiz->dir, numero_atomico, simbolo);
  }

  return raiz;
}


// Retorna o elemento com o menor número atômico na árvore.
p_no minimo(p_no raiz) {
    while (raiz->esq->numero_atomico != -1) {
        raiz = raiz->esq;
    }
    return raiz;
}


// Retorna o elemento com o maior número atômico na árvore.
p_no maximo(p_no raiz) {
    while (raiz->dir->numero_atomico != -1) {
        raiz = raiz->dir;
    }
    return raiz;
}


// Remove um elemento químico da árvore a partir do nome.
p_no remover(p_no raiz, char *simbolo) {
    p_no atual = raiz;
    if (atual->numero_atomico == -1) {
        // Árvore está vazia ou o elemento não está presente
        return raiz;
    }

    // Buscando recursivamente na esquerda ou na direita o elemento
    if (strcmp(simbolo, raiz->simbolo) != 0) {
        raiz->esq = remover(raiz->esq, simbolo);        
        raiz->dir = remover(raiz->dir, simbolo);
    }
    
    // Elemento encontrado
    else {
        // Caso 1: Nó sem filhos
        if (raiz->dir->numero_atomico == -1 && raiz->esq->numero_atomico == -1) {
            raiz->numero_atomico = -1;
            raiz->simbolo[0] = '\0';
            return raiz;
        }

        // Caso 2: Nó com apenas 1 filho
        else if (raiz->esq->numero_atomico == -1 && raiz->dir->numero_atomico != -1) {
            atual = raiz->dir;
            free(raiz);
            return atual;
        } 
        else if (raiz->dir->numero_atomico == -1 && raiz->esq->numero_atomico != -1) {
            atual = raiz->esq;
            free(raiz);
            return atual;
        }

        // Caso 3: Nó com dois filhos
        else { 
            // Encontro o Nó mais a esquerda do Nó a direita do elemento que vou retirar
            atual = minimo(raiz->dir);

            // Copio os dados do sucessor in-order para este nó
            strcpy(raiz->simbolo, atual->simbolo);
            raiz->numero_atomico = atual->numero_atomico;

            // Removo o sucessor in-order
            raiz->dir = remover(raiz->dir, atual->simbolo);
            return raiz;
        }

    }

    return atual;
}


// Busca um elemento químico na árvore pelo número atômico.
p_no buscar(p_no raiz, int numero_atomico) {
    if (raiz->numero_atomico == -1 || numero_atomico == raiz->numero_atomico){
        return raiz;
    }

    if (numero_atomico < raiz->numero_atomico) { 
        return buscar(raiz->esq, numero_atomico);
    }

    else { 
        return buscar(raiz->dir, numero_atomico);
    }
}


// Desaloca todos os nós da árvore.
void destruir_arvore(p_no raiz) {
    if (raiz == NULL) {
        return;
    }

    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);

    free(raiz);
}


// Função para imprimir os elementos da árvore em ordem crescente
void imprimir_em_ordem_crescente(p_no raiz, char *virgula) {
    if (raiz->numero_atomico != -1) {
        // Lado menor da árvore
        imprimir_em_ordem_crescente(raiz->esq, virgula);
        
        if (strcmp(virgula, "nao") == 0) {
            printf("%s", raiz->simbolo);
            strcpy(virgula, "sim");
        } else {
            printf(", %s", raiz->simbolo);
        }

        // Lado maior da árvore
        imprimir_em_ordem_crescente(raiz->dir, virgula);
    }
}


// Função para procurar um elemento específico
int procura_elemento(p_no raiz, char *simbolo) {
    int resultado = 0;
    if (raiz->numero_atomico != -1) {
        resultado = procura_elemento(raiz->esq, simbolo);
        if (resultado == 1) {
            return 1;
        }
        resultado = procura_elemento(raiz->dir, simbolo);
    }

    if (strcmp(raiz->simbolo, simbolo) == 0 || resultado == 1) {
        return 1;
    }
    else {
        return 0;
    }
}


int main() {

    p_no tree = criar_arvore();
    int loop = 1, numero_atomico;
    char virgula[] = "nao", command[10], simbolo[3]; 

    while (loop == 1) {

        // Leitura das entradas
        scanf(" %[^\n]", command);

        if (strncmp(command, "C", 1) == 0){
            sscanf(command, "%*s %d %2s", &numero_atomico, simbolo);
            tree = inserir(tree, numero_atomico, simbolo);
        }

        else if (strncmp(command, "V", 1) == 0){
            sscanf(command, "%*s %2s", simbolo);
            tree = remover(tree, simbolo);
        } 
         
        else if (strncmp(command, "E", 1) == 0){
            char virgula[] = "nao";
            imprimir_em_ordem_crescente(tree, virgula);
            printf("\n");
        } 
    
        else if (strncmp(command, "I", 1) == 0){
            sscanf(command, "%*s %d %2s", &numero_atomico, simbolo);
            int encontrado = procura_elemento(tree, simbolo);
            
            if (encontrado == 1) {
                printf("Sim\n");
            }
            else {
                printf("Nao\n");
            }
        }

        else if (strncmp(command, "MAX", 3) == 0){
            p_no max = tree;
            max = maximo(tree);            
            printf("%s\n", max->simbolo);
        }

        else if (strncmp(command, "MIN", 3) == 0){
            p_no min = tree;
            min = minimo(tree);            
            printf("%s\n", min->simbolo);
        }

        else{
            loop = 0;
        }

        // Limpar a entrada
        command[0] = '\0';
    }  
    // Liberar a memória da árvore antes de finalizar o programa
    destruir_arvore(tree);
    return 0;
}
