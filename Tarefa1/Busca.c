#include <stdio.h>
#define MAX 1000

/*Função para converter todas as letras maiúsculas em minúsculas*/
void converte(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] - 'A' + 'a';
        }
        i++;
    }
}

/*Função para encontrar o tamanho de um vetor de char*/
int len(char s[]) {
    int i, j = 0;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

/*Função para criar uma cópia de um vetor char*/
int copy(char m[]){
    int max_m = len(m);
    char current_m[max_m];
    int e;
    for (e = 0; m[i] != '\0'; e++){
        current_m[e] = m[e];
    }
    current_m[e] = '\0';
    return m[0];
}

/*Função para remover o primeiro caracter '-'*/
void remove(char m[], char caracter){
    int i, j;
    for (i = 0; m[i] != '\0'; i++) {
        if (m[i] == caracter) {
            for (j = i; m[j] != '\0'; j++) {
                m[j] = m[j + 1];
                }
            break;
        }
    }
}

/*Função para inserir um caracter específico em uma posição específica de um vetor char*/
void insert(char m[], int position, char caracter) {
    int length = len(m);
    for (int i = length; i >= position; i--) {
        m[i + 1] = m[i];
    }
    m[length] = caracter;
}

/*Função para substituir os caracteres do motivo por padrões a serem buscados*/
int busca(char *s, char *m, char caracter, int begin, int *good, int *max_value) {
    int position = -1;
    int max_m = len(m);
    
    for (int i = 0; i < max_m; i++) {
        if (m[i] == '+') {
            position = i;
            break;
        }
    }
    
    if (caracter == '+') {
        remove(new_m, '+');

        /*Definindo o tamanho da matriz que dará as opções de padrões a procurar na string s*/
        int linha = 1;
        for (int j = 0; s[begin + (*max_value) - 1] == s[begin + (*max_value)]; j++) {
            (*max_value)++;
            linha++;
        }
        int coluna = len(new_m) + linha;
        char *new_m_combinations[linha][coluna];
        char *new_m[coluna] = copy(m);
        
        if (begin > 0 && s[begin - 1] == s[begin]) {
            for (int k = 0; k <= linha; k++) {
                new_m = insert(new_m, position, m[begin - 1]);
                new_m_combinations[k] = new_m;
                position++;
                (*max_value) += 1;
            }
            (*good) += 1;
        }
        (*max_value) += 1;
    }
    return position;
}

int busca_motivo(char *s, char *m) {
    int count = 0, max_s = len(s), max_m = len(m);
    
    for (int i = 0; i < max_s; i++) {
        char current_m[max_m] = m, list[MAX];
        int begin = i, j = 0, loop = 0, good = 1, max_value = 1, a = 0;

        while (begin < max_s && good > 0) {
            if ('a' <= current_m[j] && current_m[j] <= 'z') {
                if (s[begin] == current_m[j] && (j + 1) == max_m) {
                    good = 0;
                    count++;
                } else if (s[begin] == current_m[j] && (j + 1) < max_m) {
                    begin++;
                    j++;
                } else if (s[begin] != current_m[j]) {
                    if (a > 0) {
                        a--;
                        current_m = list[a];
                    } else {
                        good = 0;
                    }
                }
            }
            
            if (current_m[j] == '+') {
                int position = busca(s, m, current_m[j], begin, &good, &max_value, list);
                a = max_value - 1;
                current_m = list[a];
            }
        }
    }
    
    return count;
}

int main() {
    char s[] = "tccaaatcaattcatccccaa";
    char m[] = "tc+a";
    convert(s);    
    int result = busca_motivo(s, m);
    printf("%d\n", result);
    
    return 0;
}