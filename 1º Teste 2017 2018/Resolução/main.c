#include <stdio.h>

/*
//Exercício 1
a)
 Invariante: 0<= i<= N-1 && p>= 0 && q>= 0 && p<= q<= i
 Correção Parcial:
    Inicialização: {P}= {N> 0} i= 0; p= 0; q= 0; {I}
    Temos: 0<= i<= N-1 -> 0<= 0<= N-1 -> 1<= N-> Válido
           p<= q<= i -> 0<= 0<= 0-> Válido

    Utilidade: {I && i>= N-1} t= v[i]; v[i]= v[q]; v[q]= t; q++; {p< q}
    Temos: (0<= i<= N-1) && (p<= q<= i) && (i>= N-1) -> i== N-1 && p<= q<= i
           Ou seja: i== N-1 && p<= q<= i
                    q++ -> q= q+1, logo p<= q+1<= N-1 <=> p< q<= N-1 -> Válido
 */

// b)
void partition (int v[], int N, int *ep, int *eq){
    int i, p, q, t;
    i=p=q=0;
    while (i<N-1) {
        if (v[i] < v[N-1]) {
            t = v[i]; v[i] = v[q];
            v[q] = v[p]; v[p] = t;
            p++; q++;}
        else if (v[i] == v[N-1]) {
            t = v[i]; v[i] = v[q];
            v[q] = t; q++;
        }
        i++;
    }
    t=v[i]; v[i] = v[q];
    v[q] = t; q++;
    *ep = p; *eq = q;
}


void quickSort(int v[], int N){
    int p, q;
    if(N> 1){
        partition(v, N, &p, &q);
        quickSort(v, p);
        quickSort(v+ q, N- q);
    }
}

/*
 Melhor Caso: forall (0< i< N) v[i]== v[i- 1]
 T(N)partition= Θ(N);
 T(N)quickSort(N) (Melhor Caso)= Ω(N)
*/

/*
//Exercício 2
a)
 Variante: N- i- 1

b)
 Melhor Caso: forall(0<= i< N-1) v[i]!= v[i+ 1]
 Pior Caso: forall(0<= i< N-1) v[i]== v[i+ 1]

 T(N) (Pior Caso)= [sum i, i= 0 to N-1]= (N*(N-1))/2

*/

/*
//Exercício 3

 Melhor Caso: forall(0< i< N) v[i]> v[i- 1]
 Pior caso: forall(0< i< N) v[0]> v[i]

*not sure if the probability is this but, caso médio close to pior caso*
 *could be 1/N^(n- i) or 1/(N- 1)!  i don´t know what is the probability for sure*
 *if you know what is the probability in each case please tell me, this is killing me!!!*

  |   Casos     | Custo (nº de swaps)  |  Probabilidade  |
  | Melhor Caso |          0           |       1/N       |
  |             |          1           |       1/N       |
  |             |          2           |       1/N       |
  |             |          .           |         .       |
  |             |          .           |         .       |
  |             |          .           |         .       |
  |  Pior Caso  |         N- 1         |       1/N       |

  Assim: sum i* probabilidade, i= 0 to N-1

 */

int main() {
    int v[7]= {4, 3, 5, 1, 2, 6, 0};
    printf("Array (antes da quickSort): ");
    for(int i= 0; i< 7; i++){
        if(i== 6) printf("%d\n", v[i]);
        else printf("%d-> ", v[i]);
    }
    quickSort(v, 7);
    printf("Array (depois da quickSort): ");
    for(int i= 0; i< 7; i++){
        if(i== 6) printf("%d\n", v[i]);
        else printf("%d-> ", v[i]);
    }
    return 0;
}
