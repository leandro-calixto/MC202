#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct
{
    char **matriz;
    int linhas, colunas;
    int saidaX, saidaY;              /* Coordenadas da saída do labirinto */
} labirinto;


labirinto* criar_labirinto(int linhas, int colunas) {
    
    int i;
    labirinto *entrada = malloc(sizeof(labirinto)); //Aloca a estrutura do labirinto
    
    if (entrada == NULL) {
        exit(1);
    }

    entrada->linhas = linhas;
    entrada->colunas = colunas;
    //Aloca o ponteiro das linhas
    entrada->matriz = malloc(linhas * sizeof(char *)); 
    
    if (entrada->matriz == NULL) {
        exit(1);
    }

    //Aloca todos os vetores das linhas
    for (i = 0; i < linhas; i++) {
        entrada->matriz[i] = malloc(colunas * sizeof(char)); 
        if (entrada->matriz[i] == NULL) {
            exit(1);
        }
    }

    return entrada;
}


void ler_labirinto(labirinto *l) {
   
    //entrar com o labirinto
    for (int i = 0; i < l->linhas; i++) {          //percorre todas as linhas
        for (int j = 0; j < l->colunas; j++) {
            scanf(" %c", &l->matriz[i][j]);        //O espaço antes de %c ignora espaços em branco
        }
            
        //encontrar a posição da "saida" do labirinto
        for (int j = 0; j < l->colunas; j++) {     
            if (l->matriz[i][j] == 'S') {
                l->saidaY = i;
                l->saidaX = j;
            }
        }
    }
}


void destruir_labirinto(labirinto *l) {

    //libera os vetores-linha
    for (int i = 0; i < l->linhas; i++) {  
        free(l->matriz[i]); 
    }

    //libera o vetor de colunas
    free(l->matriz);       
    free(l); 
}


int buscar_saida_recursivamente(char **matriz, int linhas, int colunas, int x_atual, int y_atual) {
    
    //retorno dessa função: => 0 = não deu; => 1 = caminho ok
    int controle = 0;

    //caso final: estamos no ponto de saída
    if (matriz[y_atual][x_atual] == 'S') {
        matriz[y_atual][x_atual] = 'X';
        return 1;
    }

    //analisa as posições válidas para a pesquisa "pos_val = [->, v, <-, ^]"
    int pos_val[4] = {0, 0, 0, 0};
    if (x_atual < colunas - 1 && matriz[y_atual][x_atual + 1] != '1' && matriz[y_atual][x_atual + 1] != 'P' && matriz[y_atual][x_atual + 1] != 'X' && matriz[y_atual][x_atual + 1] != 'T') {
        pos_val[0] = 1;
    }
    if (y_atual < linhas - 1 && matriz[y_atual + 1][x_atual] != '1' && matriz[y_atual + 1][x_atual] != 'P' && matriz[y_atual + 1][x_atual] != 'X' && matriz[y_atual + 1][x_atual] != 'T') {
        pos_val[1] = 1;
    }
    if (0 < x_atual && matriz[y_atual][x_atual - 1] != '1' && matriz[y_atual][x_atual - 1] != 'P' && matriz[y_atual][x_atual - 1] != 'X' && matriz[y_atual][x_atual - 1] != 'T') {
        pos_val[2] = 1;
    }
    if (0 < y_atual && matriz[y_atual - 1][x_atual] != '1' && matriz[y_atual - 1][x_atual] != 'P' && matriz[y_atual - 1][x_atual] != 'X' && matriz[y_atual - 1][x_atual] != 'T') {
        pos_val[3] = 1;
    }

    //chamamos a função recursivamente até encontrar a saida, nessa ordem
    while (pos_val[0] + pos_val[1] + pos_val[2] + pos_val[3] != 0) { 
        if (matriz[y_atual][x_atual] != 'P') {
            matriz[y_atual][x_atual] = 'X';
        }

        //caso para direita
        if (pos_val[0] == 1) {
            x_atual++;
            controle = buscar_saida_recursivamente(matriz, linhas, colunas, x_atual, y_atual);
            if (controle == 0) {
                matriz[y_atual][x_atual] = 'T';   //T de tentei nessa posição
                pos_val[0] = 0, x_atual--;
            }
            else {
                return 1;
            }
        }

        //caso para baixo
        if (pos_val[1] == 1) {
            y_atual++;
            controle = buscar_saida_recursivamente(matriz, linhas, colunas, x_atual, y_atual);
            if (controle == 0) {
                matriz[y_atual][x_atual] = 'T';
                pos_val[1] = 0, y_atual--;
            }
            else {
                return 1;
            }
        }

        //caso para esquerda
        if (pos_val[2] == 1) {
            x_atual--;
            controle = buscar_saida_recursivamente(matriz, linhas, colunas, x_atual, y_atual);
            if (controle == 0) {
                matriz[y_atual][x_atual] = 'T';
                pos_val[2] = 0, x_atual++;
            }
            else {
                return 1;
            }
        }

        //caso para cima
        if (pos_val[3] == 1) {
            y_atual--;
            controle = buscar_saida_recursivamente(matriz, linhas, colunas, x_atual, y_atual);
            if (controle == 0) {
                matriz[y_atual][x_atual] = 'T';
                pos_val[3] = 0, y_atual++;
            }
            else {
                return 1;
            }
        }
    }
    return 0;
}


labirinto* buscar_saida(labirinto *l, int x, int y) {  
    
    //copia a matriz l por outra a ser modificada
    labirinto *copia = criar_labirinto(l->linhas, l->colunas);
    copia->saidaX = l->saidaX;
    copia->saidaY = l->saidaY;
    for (int i = 0; i < l->linhas; i++) {
        for (int j = 0; j < l->colunas; j++) {
            copia->matriz[i][j] = l->matriz[i][j];
        }
    }
 
    //atualiza a matriz l com o caminho de saída
    buscar_saida_recursivamente(copia->matriz, copia->linhas, copia->colunas, x, y);

    //retirar os caminhos percorridos errados
    for (int i = 0; i < copia->linhas; i++) {
        for (int j = 0; j < copia->colunas; j++) {
            if (copia->matriz[i][j] == 'T') {
                copia->matriz[i][j] = '0';
            }
        }
    }

    return copia;
}


void imprimir_labirinto(labirinto *l) {
    
    for (int i = 0; i < l->linhas; i++) {
            for (int j = 0; j < l->colunas; j++) {
                printf("%c ", l->matriz[i][j]);
            }
            printf("\r\n");
        }
        printf("\r\n");
}


int main () {
    
    //Entrar com o tamanho do labirinto
    char tamanho[5];
    scanf("%s", tamanho);
    char *token = strtok(tamanho, "x");
    int linhas = atoi(token);
    token = strtok(NULL, "x");
    int colunas = atoi(token);

    labirinto *lab = criar_labirinto(linhas, colunas);      

    //Entrar com o labirinto
    ler_labirinto(lab);


    //encontra a posição da pessoa mais acima e a sua saída
    for (int i = 0; i < lab->linhas; i++) { 
        for (int j = 0; j < lab->colunas; j++) {     
            if (lab->matriz[i][j] == 'P') {

                //encontra a saída para essa pessoa
                labirinto *saida = buscar_saida(lab, j, i);

                //imprime a saida dessa pessoa
                imprimir_labirinto(saida);

                //retira a pessoa P do labirinto
                lab->matriz[i][j] = '0';

                //desaloca toda a memória utilizada nessa saída
                destruir_labirinto(saida);
            }
        }
    }

    //desaloca a memória utilizada para o comando inicial
    destruir_labirinto(lab);

    return 0;
}