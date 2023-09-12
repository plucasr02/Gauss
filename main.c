#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPSILON 0.000001

double **criaMatriz(int l, int c) {
  /* Se houver memória disponível, cria uma matriz de double com l  linhas e c
  colunas e devolve um ponteiro a matriz; caso contrário, devolve null */

  double **m;
  int i, j;
  m = malloc(sizeof(double *) * l);
  if (m == NULL) { // falta de memória
    return NULL;
  }
  for (i = 0; i < l; i++) {
    m[i] = malloc(sizeof(double) * c);
  }
  if (m[i] == NULL) { /*falta de memória*/
    for (j = 0; j < i; j++) {
      free(m[j]);
    }
    free(m);
    return NULL;
  }
  return m;
} // fim criaMatriz

void leMatriz(double **m, int l, int c) {
  /* Lê valores p/ a matriz M, que é uma matriz de double com l linhas e c
   * colunas alocadas dinamicamente*/

  int i, j;
  for (i = 0; i < l; i++) {
    for (j = 0; j < c; j++) {
      printf("m[%d][%d]: ", i + 1, j + 1);
      scanf("%lf", &m[i][j]);
    }
  } // fim leMatriz
}

void imprimeMatriz(double **m, int l, int c) {
  /* imprime o conteúdo da matriz m, que é uma matriz de double com l linhas e c
   * colunas alocada dinamicamente*/
  int i, j;
  for (i = 0; i < l; i++) {
    for (j = 0; j < c; j++) {
      printf("%10.3lf ", m[i][j]);
    }
    printf("\n");
  }
} // fim imprimeMatriz


int sRetro(double **m, int n, double x[]){
  /*  Recebe m, a matriz aumentada de um SL TS com n variante. Se o SL for
   * determinado, armazena em x a solucçao do SL e devolve o; Se for
   * indeterminado, armazena em x uma solucão do SL e devolve em 1; Se for
   * incompatível, devolve 2
   */
  int i, j, tipo = 0;
  double soma;
  for (i = n - 1; i >= 0; i--) {
    soma = 0;
    for (j = i + 1; j < n; j++) {
      soma += m[i][j] * x[j];
    }
    if (m[i][i] == 0) {
      if (fabs(m[i][n] - soma) < EPSILON) { // x[i] é variável livre
        x[i] = 0;
        tipo = 1;
      } else // sl uncompatível
      {
        return 2;
      } 
    } else
    { x[i] = (m[i][n] - soma) / m[i][i];}
  }
  return tipo; // fim do sRetro
}


void Gauss(double **m, int n){
  /*Recebe m, a matriz aumentada de SL com n variáveis e transforma m na matriz aumentada de um SL RS equivalente*/
  int i, j, k; double mult, *aux; 
  for (i = 0; i < n-1; i++){
    if (m[i][i] == 0) {
      j = i+1;
      while (j<n && m[j][i]==0){
        j++;}
      if(j<n) /*trocando as linhas i e j*/
      {aux=m[i]; m[i]=m[j]; m[j]=aux;}
    }
    if (m[i][i]!= 0){
      for (j = i+1; j < n; j++){
        mult = -m[j][i]/m[i][i];
        m[j][i]=0;
        for (k=i+1; k<=n; k++)
          {m[j][k] += mult*m[i][k];}
      }
    }
  }
}/* Fim Gauss*/
  
int main(){
  int n, tipo, i;
  double **m, *x;
  printf("Quantidade de variáveis: ");
  scanf("%d", &n);
  m = criaMatriz(n, n + 1);
  x = malloc(sizeof(double) * n);
  if (m == NULL || x == NULL) { // falta de memória
    
    printf("falta de memória\n");
     return 1;
  }
  leMatriz(m, n, n + 1);
  imprimeMatriz(m, n, n + 1);
  Gauss(m, n);
  printf("matriz triangularizada\n");
  imprimeMatriz(m, n, n+1);
  tipo = sRetro(m, n, x);
  if (tipo == 2) {
    printf("SL incompatível\n");
  } else {
    printf("SL %sdeterminado\n", tipo ? "in" : "");
    for (i = 0; i < n; i++) {
      printf("x[%d] =  %10.3lf\n", i + 1, x[i]);
    }
}
return 0;
}