#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int hora, minuto;
} Tempo;

typedef struct {
    char nome[20];
    // Gravidade do paciente. Quanto menor a gravidade, maior a prioridade!
    int chave;
    Tempo chegada;
} Item;

typedef struct {
    Item *v;
    int n, tamanho;
} FP;

typedef FP *p_fp;

// Cria a fila de prioridade com tamanho definido.
p_fp criar_filaprio(int tam) {
    p_fp fprio = malloc(sizeof(FP));
    fprio->n = 0;
    fprio->tamanho = tam;
    fprio->v = malloc(tam * sizeof(Item));

    for (int i = 0; i < tam; i++) {
        fprio->v[i].chave = 0;
    }

    return fprio;
}

// Insere um item na fila
void insere(p_fp fprio, Item item) {

    fprio->n++;
    
    Item armazena;
    int new_item = 1;
    armazena.chave = 0;
    for (int i = 0; i < fprio->n; i++) {

        // Caso base: não há pacientes na fila ou a prioridade de atendimento desse paciente é a menor até então
        if (fprio->n == 1 || (item.chave >= fprio->v[i-1].chave && fprio->v[i].chave == 0) && new_item == 1) {
            strcpy(fprio->v[i].nome, item.nome);
            fprio->v[i].chave = item.chave;
            fprio->v[i].chegada = item.chegada; 

            new_item = 0;
        }

        // Caso que a prioridade é maior do que os pacientes já em fila
        if (item.chave < fprio->v[i].chave && new_item == 1) {
            armazena = fprio->v[i];

            strcpy(fprio->v[i].nome, item.nome);
            fprio->v[i].chave = item.chave;
            fprio->v[i].chegada = item.chegada;
            i++; 

            new_item = 0;
        }

        // Arrumo o restante da fila
        if (armazena.chave != 0) {
            item = fprio->v[i];

            strcpy(fprio->v[i].nome, armazena.nome);
            fprio->v[i].chave = armazena.chave;
            fprio->v[i].chegada = armazena.chegada; 
            
            if (i + 1 == fprio->n) {
                armazena.chave = 0;
            }
            else {
                armazena = item;
            }
        }
    }
    

    return;
}

// Extrai o Item de maior prioridade
Item extrai_maximo(p_fp fprio){
    int j, max = 0;
    for (j = 1; j < fprio ->n; j++){ 
        if (fprio->v[max].chave < fprio->v[j]. chave)
            max = j;
    }    
    return fprio->v[max];
}

// Verifica se a fila está vazia
int vazia(p_fp fprio){
    if (fprio->v->chave == 0) {
        return 1;
    }
    else {
        return 0;
    } 
}

// Veirifica se a fila está cheia
int cheia(p_fp fprio){
    if (fprio->v != NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

// Atualiza a gravidade de um paciente e reordena a fila
void atualizar_gravidade(p_fp fprio, char nome[], int nova_gravidade){
    // Encontrar e ajustar a nova gravidade
    int i = 0;
    while (strcmp(fprio->v[i].nome, nome) != 0) { 
        i++;
    }
    fprio->v[i].chave = nova_gravidade;

    // Arrumar a nova posição de atendimento do paciente pelo método bubblesort
    // Quanto menor a gravidade, maior a prioridade!
    Item armazena_min;
    Item armazena_max;
    for (int i = 0; i < fprio->n - 1; i++) {
        for (int j = fprio->n - 1; j > i; j--) { 
            if (fprio->v[j].chave < fprio->v[i].chave) {
                armazena_min = fprio->v[j];
                armazena_max = fprio->v[i] ;
                fprio->v[i] = armazena_min;
                fprio->v[j] = armazena_max; 
            }
            else if (fprio->v[j].chave == fprio->v[i].chave &&
                     fprio->v[j].chegada.hora < fprio->v[i].chegada.hora) {

                armazena_min = fprio->v[j];
                armazena_max = fprio->v[i] ;
                fprio->v[i] = armazena_min;
                fprio->v[j] = armazena_max; 
            }
            else if (fprio->v[j].chave == fprio->v[i].chave &&
                     fprio->v[j].chegada.hora == fprio->v[i].chegada.hora &&
                     fprio->v[j].chegada.minuto < fprio->v[i].chegada.minuto) {
                        
                armazena_min = fprio->v[j];
                armazena_max = fprio->v[i] ;
                fprio->v[i] = armazena_min;
                fprio->v[j] = armazena_max; 
            }
        }
    }
}


// Libera a fila de memória
void destroi_fila(p_fp fprio){
    free(fprio->v);
}


int main() {

    int loop = 1, number, hour, min;
    char command[30], letter[2], name[20]; 

    // Leitura da capacidade de atendimento
    scanf(" %c %d", letter, &number);

    // Criação da fila com a restrição da capacidade médica
    p_fp fila_atendimento = criar_filaprio(number);

    while (loop == 1) {
        // Setar nula a entrada
        command[0] = '\0';

        // Leitura dos comandos
        scanf(" %[^\n]", command);

        if (strncmp(command, "I", 1) == 0){
            sscanf(command, "%*s %s %d %d:%d", name, &number, &hour, &min);
            Item ficha_paciente;
            strcpy(ficha_paciente.nome, name);
            ficha_paciente.chave = number;
            ficha_paciente.chegada.hora = hour;
            ficha_paciente.chegada.minuto = min;   

            if (fila_atendimento->n < fila_atendimento->tamanho) { 
                insere(fila_atendimento, ficha_paciente);
            }
            else {
                printf("Fila cheia\n");
            }
            
            // Setando as variáveis como nulas
            name[0] = '\0'; number = 0; hour = 0; min = 0;
        }

        else if (strncmp(command, "R", 1) == 0){
            if (vazia(fila_atendimento) == 1) {
                printf("Fila vazia\n");
            }
            else {
                printf("Atendimento: %s\n", fila_atendimento->v[0].nome);
                for (int i = 0; i < fila_atendimento->n - 1; i++) {
                    fila_atendimento->v[i] = fila_atendimento->v[i + 1];
                }
                fila_atendimento->n--;
            }
        } 
         
        else if (strncmp(command, "A", 1) == 0){
            sscanf(command, "%*s %s %d", name, &number);
            atualizar_gravidade(fila_atendimento, name, number);
        } 
    
        else if (strncmp(command, "P", 1) == 0){
            if(fila_atendimento->n == 0) {
                printf("Fila vazia\n");
            }

            else { 
                for (int i = 0; i < fila_atendimento->n; i++) { 
                    if (i < fila_atendimento->n) { 
                        printf("%d. Paciente: %s, Gravidade: %d, Chegada: %02d:%02d\n",
                        i + 1,
                        fila_atendimento->v[i].nome,
                        fila_atendimento->v[i].chave,
                        fila_atendimento->v[i].chegada.hora,
                        fila_atendimento->v[i].chegada.minuto);
                    }
                }            
            }
        }

        else if (strncmp(command, "F", 1) == 0){
            loop = 0;
        } 
    }  

    // Liberar a memória da árvore antes de finalizar o programa
    destroi_fila(fila_atendimento);

    return 0;
}
