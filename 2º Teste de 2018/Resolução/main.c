#include <stdio.h>
#include <stdlib.h>

typedef struct Abin{
    int valor;
    struct Abin *esq, *dir;
}*Btree;

#define NV 5
typedef struct aresta {
    int destino, peso;
    struct aresta *prox;
}*Grafo [NV];

/*
*NOTA: Exercícios 2 e 4 não resolvidos pois a matéria dos mesmo não foi abordada no ano letivo de 2020/2021*
*/

//Exercício 1:
//Também dava Tabela Hash
Btree constroi_Btree(Btree *t, int x, int *flag){
    if(!(*t)){
        *t= malloc(sizeof(struct Abin));
        (*t)-> valor= x;
        (*t)-> esq= (*t)-> dir= NULL;
        *flag= 0;
        return *t;
    }
    if((*t)-> valor> x) return (*t)-> esq= constroi_Btree(&((*t)-> esq), x, flag);
    else if((*t)-> valor< x) return (*t)-> dir= constroi_Btree(&((*t)-> dir), x, flag);
    else{
        *flag= 1;
        return *t;  
    }
}


int repetidos(int v[], int N){
    Btree t= malloc(sizeof(struct Abin));
    t-> valor= v[0];
    t-> esq= t-> dir= NULL;
    Btree raiz= t;
    int flag= 0;
    for(int i= 1; i< N && !flag; i++){
        t= raiz;
        t= constroi_Btree(&t, v[i], &flag);
    }
    return flag;
}


//Exercício 3
//Exercício 3 Otimizado:
int depth_First_Otimizado(Grafo g, int vertice, int visitados[], int original){
    struct aresta *it;
    int count= 1;
    for(it= g[vertice]; it; it= it-> prox){
        if(visitados[it-> destino]== -2){
            visitados[it-> destino]= vertice;
            count+= depth_First_Otimizado(g, it-> destino, visitados, original);
        }
        else if(visitados[it-> destino]>= 0 || visitados[it-> destino]== original) return -1;
    }
    return count;
}

int step_Two(Grafo g, int vertice){
    int visitados[NV];
    for(int i= 0; i< NV; i++) visitados[i]= -2;
    visitados[vertice]= -1;
    int alcancaveis= depth_First_Otimizado(g, vertice, visitados, vertice);
    return (alcancaveis== NV? 1: 0);
}

int isTree(Grafo g){
    int flag_two= 0;
    for(int i= 0; i< NV; i++){
        flag_two= step_Two(g, i);
        if(flag_two== 1) return i;
    }
    return -1;
}

//Exercício 3 não otimizado:
/*
int step_One(int vertice, Grafo g){
    struct aresta *it;
    int indice= 0;
    for(; indice< NV; indice++){
        if(indice!= vertice){
            it= g[indice];
            for(; it && it-> destino!= vertice; it= it-> prox);
            if(it && it-> destino== vertice) return 0;
        }
    }
    return 1;
}

int depth_First(Grafo g, int vertice, int visitados[]){
    struct aresta *it;
    int count= 1;
    for(it= g[vertice]; it; it= it-> prox){
        if(visitados[it-> destino]== -2){
            visitados[it-> destino]= vertice;
            count+= depth_First(g, it-> destino, visitados);
        }
        else if(visitados[it-> destino]>= 0) return -1;
    }
    return count;
}



int step_Two(Grafo g, int vertice){
    int visitados[NV];
    for(int i= 0; i< NV; i++) visitados[i]= -1;
    int alcancaveis= depth_First(g, vertice, visitados);
    return (alcancaveis== NV? 1: 0);
}



int isTree(Grafo g){
    int flag_one= 0, flag_two= 0;
    for(int i= 0; i< NV; i++){
        flag_one= step_One(i, g);
        if(flag_one== 1){
            flag_two= step_Two(g, i);
            if(flag_two== 1) return i;
        }
    }
    return -1;
}
*/
//Exercício 2 e 4 não demos esta matéria...

/*
Grafo 1: (Pesos são irrelevantes)
:0-> 1-> 2;
:1-> 3;
:2-> 3-> 4;
:3-> 4;
:4;

Grafo 2: (Pesos são irrelevantes)
:0-> 1-> 2;
:1-> 3;
:3-> 4;

*/


int main() {
    Grafo g1, g2;
    for(int i= 0; i< NV; g1[i]= NULL, g2[i++]= NULL);
    g1[0]= malloc(sizeof(struct aresta));
    g1[0]-> destino= 1;
    g1[0]-> prox= malloc(sizeof(struct aresta));
    g1[0]-> prox-> destino= 2;
    g1[0]-> prox-> prox= NULL;
    g1[1]= malloc(sizeof(struct aresta));
    g1[1]-> destino= 3;
    g1[1]-> prox= NULL;
    g1[2]= malloc(sizeof(struct aresta));
    g1[2]-> destino= 3;
    g1[2]-> prox= malloc(sizeof(struct aresta));
    g1[2]-> prox-> destino= 4;
    g1[2]-> prox-> prox= NULL;
    g1[3]= malloc(sizeof(struct aresta));
    g1[3]-> destino= 4;
    g1[3]-> prox= NULL;

    g2[0]= malloc(sizeof(struct aresta));
    g2[0]-> destino= 1;
    g2[0]-> prox= malloc(sizeof(struct aresta));
    g2[0]-> prox-> destino= 2;
    g2[0]-> prox-> prox= NULL;
    g2[1]= malloc(sizeof(struct aresta));
    g2[1]-> destino= 3;
    g2[1]-> prox= NULL;
    g2[3]= malloc(sizeof(struct aresta));
    g2[3]-> destino= 4;
    g2[3]-> prox= NULL;

    int vertice1= isTree(g1);
    int vertice2= isTree(g2);
    printf("Vertice Raiz: %d\n", vertice1);
    printf("Vertice Raiz: %d\n", vertice2);

/*
  int v[6]={4, 3, 1, 5, 2, 2};
  int flag= repetidos(v, 6);
  if(!flag) printf("Nao tem elementos repetidos\n);
  else printf("Tem elementos repetidos\n");
  */

    return 0;
}
