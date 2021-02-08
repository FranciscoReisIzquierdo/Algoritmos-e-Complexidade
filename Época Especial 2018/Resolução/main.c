#include <stdio.h>
#include <stdlib.h>
#define HSIZE 23
#define NV 5
#define BLUE 0
#define RED 1
#define YELLOW 2

/*
Grafo 1:
 :0-> 1;
 :1-> 2-> 3;
 :2-> 3;
 :3-> 1;
 :4-> 2;

Grafo 2:
 :0-> 1;
 :1;
 :2-> 3;
 :3-> 2;
 :4;
*/

typedef struct bucket{
    int key; int info;
    struct bucket *next;
}*Bucket;
typedef Bucket HashTable[HSIZE];

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
}*Abin;

typedef struct edge {
    int dest;
    struct edge *next;
};
typedef struct edge *GraphL[NV];

//Exercício 4
//NOTA: A função quantos1 é mais eficiente do que a quantos2 (acho eu)
//Usando Tabelas Hash
void initHashTable(HashTable h){
    for(int i= 0; i< HSIZE; h[i++]= NULL);
}

int hash(int key, int size){
    return key% size;
}

int update(HashTable h, int key, int info){
    int p= hash(key, HSIZE);
    int r;
    struct bucket *it, *newBucket;

    for(it= h[p]; it && it-> key!= key; it= it-> next);

    if(!it){
        newBucket= malloc(sizeof(struct bucket));
        newBucket-> key= key;
        newBucket-> info= info;
        newBucket-> next= h[p];
        h[p]= newBucket;
        r= 1;
    }
    else r= 2;
    return r;
}

int quantos1(int v[], int N){
    HashTable h;
    initHashTable(h);
    int count= 0, r;
    for(int i= 0; i< N; i++){
        r= update(h, v[i], i);
        if(r== 1) count++;
    }
    return count;
}

//Usando Árvores Binárias
int constroiAbin(Abin *a, int x){
    if(!(*a)){
        *a= malloc(sizeof(struct nodo));
        (*a)-> valor= x;
        (*a)-> esq= (*a)-> dir= NULL;
        return 1;
    }
    int r;
    if((*a)-> valor> x) r= constroiAbin(&((*a)-> esq), x);
    else if((*a)-> valor< x) r= constroiAbin(&((*a)-> dir), x);
    else return 2;
}

int quantos2(int v[], int N){
    int count= 0, r;
    Abin a= NULL;
    for(int i= 0; i< N; i++){
        r= constroiAbin(&a, v[i]);
        if(r== 1) count++;
    }
    return count;
}

//Exercício 6
int weakColor (GraphL g, int cores[], int k){
    struct edge *it;
    int flag= 1;
    for(int i= 0; i< NV && flag; i++){
        for(it= g[i]; it && flag; it= it-> next){
            if(cores[i]!= cores[it-> dest]) flag= 0;
        }
    }
    return flag;
}

//Exercício 7
/*
void setArray(int pais[], int N){
    for(int i= 0; i< N; pais[i++]= -1);
}

void AllPairs(GraphL g, int T[NV][NV]){
    int origem= 0, destino;
    int pais[NV];
    for(; origem< NV; origem++){
        int cost[NV];
        setArray(pais, NV);
        dijkstraSP (g, origem, pais, cost);
        for(destino= 0; destino< NV; destino++) T[origem][destino]= cost[destino];
    }
}
 */

int main() {
    int v[10]= {3, 6, 7, 4, 5, 8, 2, 3, 2, 5};
    int dif1= quantos1(v, 10);
    int dif2= quantos2(v, 10);
    printf("Numeros diferentes: %d\n", dif1);
    printf("Numeros diferentes: %d\n", dif2);

    GraphL g1;
    for(int i= 0; i< NV; g1[i++]= NULL);
    g1[0]= malloc(sizeof(struct edge));
    g1[0]-> dest= 1;
    g1[0]-> next= NULL;
    g1[1]= malloc(sizeof(struct edge));
    g1[1]-> dest= 2;
    g1[1]-> next= malloc(sizeof(struct edge));
    g1[1]-> next-> dest= 3;
    g1[1]-> next-> next= NULL;
    g1[2]= malloc(sizeof(struct edge));
    g1[2]-> dest= 3;
    g1[2]-> next= NULL;
    g1[3]= malloc(sizeof(struct edge));
    g1[3]-> dest= 1;
    g1[3]-> next= malloc(sizeof(struct edge));
    g1[3]-> next-> dest= 4;
    g1[3]-> next-> next= NULL;
    g1[4]= malloc(sizeof(struct edge));
    g1[4]-> dest= 2;
    g1[4]-> next= NULL;
    int cores1[NV];
    cores1[0]= RED;
    cores1[1]= RED;
    cores1[2]= RED;
    cores1[3]= BLUE;
    cores1[4]= YELLOW;


    GraphL g2;
    for(int i= 0; i< NV; g2[i++]= NULL);
    g2[0]= malloc(sizeof(struct edge));
    g2[0]-> dest= 1;
    g2[0]-> next= NULL;
    g2[2]= malloc(sizeof(struct edge));
    g2[2]-> dest= 3;
    g2[2]-> next= NULL;
    g2[3]= malloc(sizeof(struct edge));
    g2[3]-> dest= 2;
    g2[3]-> next= NULL;


    int cores2[NV];
    cores2[0]= cores2[1]= RED;
    cores2[2]= cores2[3]= YELLOW;
    cores2[4]= BLUE;

    int strength1= weakColor(g1, cores1, 3);
    int strength2= weakColor(g2, cores2, 3);
    if(strength1== 0) printf("Grafo 1 tem coloracao fraca\n");
    if(strength1== 1) printf("Grafo 1 nao tem coloracao fraca\n");
    if(strength2== 0) printf("Grafo 2 tem coloracao fraca\n");
    if(strength2== 1) printf("Grafo 2 nao tem coloracao fraca\n");

    return 0;
}