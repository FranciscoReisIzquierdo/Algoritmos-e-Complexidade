#include <stdio.h>
#include <stdlib.h>
#define MAX 4


/*  Grafo em Matriz de Adjacência (Exercício 4):
    [[1, 1, -1, -1]
     [-1, 1, 1, 1]
     [-1, -1, 1, 1]
     [-1, 1, -1, 1]]
                                                  */

/*   Grafo em Listas de Adjacência (Exercício 5):
     :0-> 1;
     :1-> 0-> 2-> 3;
     :2-> 1;
     :3-> 1;
     NOTA: É fortemente ligado                    */


typedef enum balancefactor { LH , EH , RH } BalanceFactor;

typedef struct treenode {
    BalanceFactor bf;      // indicador de equilíbrio AVL
    int entry;             // inteiro guardado no nó
    int n_elems;           // número de elementos desta árvore
    struct treenode *esq, *dir;
} *Tree;

typedef int GraphM[MAX][MAX];

typedef struct edge {
    int dest;
    struct edge *next;
};
typedef struct edge *GraphL[MAX];


//Exercício 1
/*
i) {P}= {0<= a< b< N}
   {Q}= {(r== a- 1 || a<= r<= b) && (r== -1 -> forall (a<= i<= b) v[i]!= k) && ((a<= r<= b)-> v[r]== k)}

*not sure if it´s this*
ii) Invariante: a-1<= i <= b && forall (i< j<= b) v[j]!= k
    Variante: (Por exemplo) b+i

*not sure if it´s this*
iii) Melhor Caso: v[b]= k
     Pior Caso: forall(a<= i<= b) v[i]!= k
     Assim temos: Tsearch(a, b)= Ω(1) e O(b- a)

//Exercício 2
i)
 Caso de Paragem: N= 1;
 Melhor Caso: v[0]!= v[1]     T(N)= 1
 Pior Caso: forall(0<= i< N-1) v[i]== v[i+ 1]    T(N)= 1+ T(N-1)= 1+ 1+ T(N-2)=...= N-1+ T(N- (N-1))= N-1

ii)
|         Casos              |   Custo  | Probabilidade |
|       Melhor Caso          |     1    |  (1/p)^(N- 1) |
| v[0]== v[1] && v[1]!= v[2] |     2    |  (1/p)^(N- 1) |
|             .              |     3    |  (1/p)^(N- 1) |
|             .              |     .    |       .       |
|             .              |     .    |       .       |
|             .              |     .    |       .       |
|        Pior Caso           |   N- 1   |       .       |

 Assim T(N)médio= sum (i* probabilidade), i= 1 to N-1


//Exercício 3 i)
//(Não atualizo os campos bf, uma vez que não é necessário)
Tree rotateLeft(Tree t){
    int elems= t-> n_elems;
    int elems_right= t-> dir-> n_elems;

    Tree aux= NULL;
    Tree new= t-> dir;
    t-> dir= aux;
    aux= t;
    new-> esq= aux;
    new-> n_elems= elems;
    new-> esq-> n_elems= elems- elems_right;
    t= new;
    return t;
}

//Exercício 3 ii)
int rank(Tree t, int x){
    if(!t) return 0;
    if(x< t-> entry) return rank(t-> esq, x);
    if(x== t-> entry) return 1+ rank(t-> dir, x);
    else{
        if(t-> esq) return 2+ (t-> esq-> n_elems)+ rank(t-> dir, x);
        return 1+ rank(t-> dir, x);
    }
}


//Exercício 4
/*
Sendo N o nº de vértices temos:
Tmelhor_Caso(N)= N
Tpior_Caso(N)= N*(N+ E)   *not sure if it´s this*
*/

int depth_First_Matriz(GraphM g, int s, int n, int visitados[]){
    visitados[s]= 0;
    int i= 0, r= 1;
    for(; i< n; i++){
        if(g[s][i]!= -1 && visitados[i]== -1) r+= depth_First_Matriz(g, i, n, visitados);
    }
    return r;
}

int count_reachable(GraphM g, int s, int n){
    int visitados[MAX];
    for(int i= 0; i< n; i++) visitados[i]= -1;
    int r= depth_First_Matriz(g, s, n, visitados);
    return r;
}


//Exercício 5
int travessia(GraphL g, int origem , int destino, int n, int visitados[]){
    if(origem== destino) return 1;
    visitados[origem]= 1;
    int flag= -1;

    struct edge *it;
    for(it= g[origem]; it && flag== -1; it= it-> next){
        if(visitados[it-> dest]== -1) flag= travessia(g, it-> dest, destino, n, visitados);
    }
    if(!it && flag== -1) return 0;
    else return 1;
}


int consulta(GraphL g, int origem, int destino, int n){
    int visitados[n];
    for(int i= 0; i< n; visitados[i++]= -1);

    return travessia(g, origem, destino, n, visitados);
}


int stronglyConnected (GraphL g, int n){
    int flag1= 1, flag2= 1, result= 1;
    int origem= 0;
    for(; origem< n && result; origem++){
        for(int destino= origem+ 1; destino< n && result; destino++){
            flag1= consulta(g, origem, destino, n);
            flag2= consulta(g, destino, origem, n);
            result= flag1 && flag2;
        }
    }
    return result;
}


int main() {
    /*
    Tree a= malloc(sizeof(struct treenode));
    a-> bf= RH;
    a-> entry= 30;
    a-> n_elems= 4;
    a-> esq= malloc(sizeof(struct treenode));
    a-> esq-> bf= EH;
    a-> esq-> entry= 10;
    a-> esq-> n_elems= 0;
    a-> esq-> esq= a-> esq-> dir= NULL;
    a-> dir= malloc(sizeof(struct treenode));
    a-> dir-> bf= RH;
    a-> dir-> entry= 40;
    a-> dir-> n_elems= 2;
    a-> dir-> esq= NULL;
    a-> dir-> dir= malloc(sizeof(struct treenode));
    a-> dir-> dir-> bf= EH;
    a-> dir-> dir-> entry= 50;
    a-> dir-> dir-> n_elems= 2;
    a-> dir-> dir-> esq= NULL;
    a-> dir-> dir-> dir= malloc(sizeof(struct treenode));
    a-> dir-> dir-> dir-> bf= RH;
    a-> dir-> dir-> dir-> entry= 60;
    a-> dir-> dir-> dir-> n_elems= 0;
    a-> dir-> dir-> dir-> dir= a-> dir-> dir-> dir-> esq= NULL;

    a-> dir= rotateLeft(a-> dir);
    //A árvore já está balanceada

    int equal_Or_lower= rank(a, 55);
    */

    /*
    GraphM g= {{1, 1, -1, -1}, {-1, 1, 1, 1}, {-1, -1, 1, 1}, {-1, 1, -1, 1}};
    int atingiveis= count_reachable(g, 3, MAX);
    */


    GraphL g;
    for(int i= 0; i< MAX; g[i++]= NULL);
    g[0]= malloc(sizeof(struct edge));
    g[0]-> dest= 1;
    g[0]-> next= NULL;
    g[1]= malloc(sizeof(struct edge));
    g[1]-> dest= 0;
    g[1]-> next= malloc(sizeof(struct edge));
    g[1]-> next-> dest= 2;
    g[1]-> next-> next= malloc(sizeof(struct edge));
    g[1]-> next-> next-> dest= 3;
    g[1]-> next-> next-> next= NULL;
    g[2]= malloc(sizeof(struct edge));
    g[2]-> dest= 1;
    g[2]-> next= NULL;
    g[3]= malloc(sizeof(struct edge));
    g[3]-> dest= 1;
    g[3]-> next= NULL;

    int strong= stronglyConnected(g, MAX);
    if(!strong) printf("O grafo nao e fortemente ligado\n");
    else printf("O grafo e fortemente ligado\n");

    return 0;
}
