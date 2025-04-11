/*

lab-01.c

MC202GH - Rascunho do programa do Laboratório 1.

msreis, 17 de julho de 2023.

*/

#include <stdio.h>

#define MAX 1000

/*Função para encontrar o tamanho de um vetor de char*/
int len(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

/*Função para converter todas as letras maiúsculas em minúsculas*/
void convert(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] - 'A' + 'a';
        }
        i++;
    }
}

/*Função para contar a quantidade de repetições de m em s*/
unsigned int busca_motivo (char s[], char m[]) {
    int count = 0, max_m = len(m), max_s = len(s) - 1, good, i, j, k;   
    for (i = 0; s[i] != '\0'; i++) {
        k = 0;
        for (j = 0; m[j] != '\0'; j++) {
            good = 0;
            if (s[i + j + k] == m[j] && (j + 1) == max_m) {
                count++;
            }
            else if (s[i + j + k] == m[j - 1] && m[j] == '+' && (j + 1) == max_m) {
                count++, good = 1;
            }
            else if (m[j] == '+') {
                while (good == 0) { 
                    if (s[i + j + k] == m[j - 1]){
                        if (s[i + j + k] == s[i + j + k + 1] && (i + j + k + 2) == max_s) {
                            good = 1, k--;
                        }
                        else if (s[i + j + k] == s[i + j + k + 1] && (i + j + k + 2) <= max_s) {
                            k++;
                        }
                        else if (s[i + j + k] != s[i + j + k + 1]) {
                            good = 1, k--;
                        }
                        } 
                    else {
                        j = max_m - 1, good = 1;
                    }
                }
            }  
            else if (s[i + j] != m[j] && m[j] != '+') {
                j = max_m - 1;
            } 
        }
    }
    return count;
}
  

int main () {
  char s[MAX], m[MAX];
  int i = 0;
  scanf("%s ", m);

  do  {
    s[i] = getchar ();
    if (s[i] != EOF)
    {
      i++;
    }
  }
  while (s[i] != EOF);
  s[i] = '\0';
  convert(s);
  printf("%u\n", busca_motivo(s, m));
  return 0;
}