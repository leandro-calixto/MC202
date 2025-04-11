/*

lab-01.c

MC202GH - Rascunho do programa do Laboratório 1.

msreis, 17 de julho de 2023.

*/

#include <stdio.h>

#define MAX 1000

/Função para encontrar o tamanho de um vetor de char/
int len(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

/Função para converter todas as letras maiúsculas em minúsculas/
void convert(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] - 'A' + 'a';
        }
        i++;
    }
}

/Função para contar a quantidade de repetições de m em s/
unsigned int busca_motivo (char s[], char m[]) {
    int count = 0, max_m = len(m), max_s = len(s) - 1, good, i, j, k, l;   
    for (i = 0; s[i] != '\0'; i++) {       /i fará o codigo percorrer toda a string s/
        k = 0;                              /k atualizará o indice de comparação da string i para cada m[j] repetido nela/
        for (j = 0; m[j] != '\0'; j++) {    /j fará o código percorrer todo o motivo/
            good = 0;                       /good é um break para o loop que atualiza o k/
            if (s[i + j + k] == m[j] && (j + 1) == max_m) {
                count++, i = i + j + k - 1;
            }
            else if (m[j] == '+') {
                while (good == 0) { 
                    if (s[i + j + k] == m[j - 1]){                       
                        if (s[i + j + k] == s[i + j + k + 1] && (i + j + k + 2) <= max_s) {  /no meio da string s com repetições ainda/
                            if (m[j - 1] == m[j + 1] && m[j + 2] == '+') {  /*sai no primeiro loop no caso [str1, +, str1, +]*/
                                good = 1, k++;
                            }
                            else if (m[j - 1] == m[j + 1]) { /caso [str1, +, str1, str1, ..., str1, str2] conta quantos str1 precisa deixar para o (for i) rodar e sai do loop/
                                l = 0;                        /*l guiará o indice do motivo nos casos [str1, +, str1, ..., str1, str2]*/
                                while (m[j + l + 1] == m[j + l + 2]) {  /l conta quantas strings repetidas tem para frente do + no motivo/
                                    l++;
                                }
                                for (int m = 0; m != l; m++) {     
                                    if (s[i + j + k + m] != m[j - 1]) {
                                        good = 1;
                                    }
                                }
                                if (good = 1) {       /caso em que as strings são diferentes/
                                    j = max_m - 1;
                                }
                                else {          /caso em que as strings são iguais/
                                    i = i + l, j = j + l, good = 1;
                                }
                            }
                        }
                        else if (s[i + j + k] == s[i + j + k + 1] && (i + j + k + 2) == max_s && (j + 1 == max_m)) {      /No final da string s/
                            good = 1, count++, i = i + j + k -1;                                 /sai do loop, conta + 1 no contador e deixa o laço do (for i) e do sair sozinho/
                        }
                        else if (s[i + j + k] != s[i + j + k + 1]) {              /quando a string seguinte for diferente da anterior/
                            good = 1;                                           /sai do loop/
                        } 
                    else {     /sai do loop no único caso em que já no começo do while as strings são diferentes. Para os outros casos, o código está saindo do loop nos  if e elses acima/
                        j = max_m - 1, good = 1;
                    }
                }
            }
            else if (s[i + j + k] == m[j - 1] && m[j] == '+' && (j + 1) == max_m) {
                count++, good = 1, i = i + j + k - 1;
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
      s[i] = '0';
    }
  }
  while (s[i] != EOF);
  s[i] = '\0';
  convert(s), convert(m);
  printf("%u\n", busca_motivo(s, m));
  return 0;
}