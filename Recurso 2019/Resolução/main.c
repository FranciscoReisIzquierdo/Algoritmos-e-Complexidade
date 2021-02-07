#include <stdio.h>
#include <stdlib.h>
#define MAX 4

typedef struct edge {
    int dest;
    struct edge *next;
};
typedef struct edge *GraphL[MAX];


typedef struct avlNode {
    int valor;
    int bal; //1:Esq, -1:Dir
    struct avlNode *esq, *dir;
} *AVL;


//Exercício 2 b)
int altura (AVL a){
    if(!a) return 0;
    if(!a-> esq && !a-> dir) return 1;
    int esq= 1+ altura(a-> esq);
    int dir= 1+ altura(a-> dir);
    return esq> dir? esq: dir;
}

void converteLinear(AVL a, int x){
    if(a){
        if(a-> bal== 1){
            converteLinear(a-> esq, x- 1);
            converteLinear(a-> dir, x- 2);
        }
        else if(a-> bal== -1){
            converteLinear(a-> esq, x- 2);
            converteLinear(a-> dir, x- 1);
        }
        else{
            converteLinear(a-> esq, x- 1);
            converteLinear(a-> dir, x- 1);
        }
        a-> bal= x;
    }
}


void converte (AVL a) {
    if (a!=NULL) {
        int x= altura(a);
        converteLinear(a, x);
    }
}


//Exercício 3
// a)
int travessia_depthFirst(GraphL g, int o, int v[]){
    int alcancaveis= 1;
    v[o]= 1;
    struct edge *it;
    for(it= g[o]; it; it= it-> next){
        if(v[it-> dest]== 0) alcancaveis+= travessia_depthFirst(g, it-> dest, v);
    }
    return alcancaveis;
}


int travessia (GraphL g, int o, int v[]){
    int alcancaveis= 0;
    for(int i= 0; i< MAX; v[i++]= 0);

    alcancaveis= travessia_depthFirst(g, o, v);
    return alcancaveis;
}


//b)
void FechoT(GraphL g, int T[MAX][MAX]){
    int i= 0, j= 0, v[MAX];
    for(; i< MAX; i++){
        travessia(g, i, v);
        for(j= 0; j< MAX; j++){
            if(v[j]== 1) T[i][j]= 1;
            else T[i][j]= 0;
        }
    }
}


int main() {
    GraphL g;
    for(int i= 0; i< MAX; g[i++]= NULL);
    g[0]= malloc(sizeof(struct edge));
    g[0]-> dest= 1;
    g[0]-> next= NULL;
    g[1]= malloc(sizeof(struct edge));
    g[1]-> dest= 2;
    g[1]-> next= malloc(sizeof(struct edge));
    g[1]-> next-> dest= 3;
    g[1]-> next-> next= NULL;
    g[2]= malloc(sizeof(struct edge));
    g[2]-> dest= 3;
    g[2]-> next= NULL;
    g[3]= malloc(sizeof(struct edge));
    g[3]-> dest= 1;
    g[3]-> next= NULL;


    int v[MAX];
    //int alc= travessia(g, 1, v);
    //for(int i= 0; i< MAX; i++) printf("%d-> ", v[i]);

    int T[MAX][MAX];
    FechoT(g, T);

    for(int i= 0; i< MAX; i++) {
        for(int j= 0; j< MAX; j++){
            if(j!= MAX- 1) printf("%d-> ", T[i][j]);
            else printf("%d\n", T[i][j]);
        }
    }

    return 0;
}