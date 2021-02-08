#include <stdlib.h>
#include <stdio.h>

//NOTA: Aconselha-se à visualização da função update exercício 3 em http://pythontutor.com/c.html#code=%23include%20%3Cstdlib.h%3E%0A%23include%20%3Cstdio.h%3E%0A%0A%23define%20HSIZE%2023%0A%23define%20FREE%20-1%0A%23define%20NV%205%0A%23define%20WHITE%200%0A%23define%20GREY%201%0A%23define%20BLACK%202%0A%0Atypedef%20struct%20entry%7B%0A%20%20%20%20int%20probC%3B%20//%20-1%3A%20free%0A%20%20%20%20int%20key%3B%0A%20%20%20%20int%20value%3B%0A%7D%20HTable%20%5BHSIZE%5D%3B%0A%0Atypedef%20struct%20edgeG%7B%0A%20%20%20%20int%20peso%3B%0A%20%20%20%20int%20dest%3B%0A%20%20%20%20struct%20edgeG%20*prox%3B%0A%7D*Elist%3B%0A%0Atypedef%20Elist%20Graph%5BNV%5D%3B%0A%0Aint%20hash%28int%20key,%20int%20size%29%7B%0A%20%20%20%20return%20key%25%20size%3B%0A%7D%0A%0Aint%20find_probC%28HTable%20h,%20int%20key,%20int%20*number_probs%29%7B%0A%20%20%20%20int%20p%3D%20hash%28key,%20HSIZE%29%3B%0A%20%20%20%20int%20count%3D%20HSIZE,%20probs%3D%200%3B%0A%20%20%20%20for%28%3B%20count%3E%20HSIZE%20%26%26%20h%5Bp%5D.probC!%3D%20FREE%20%26%26%20h%5Bp%5D.key!%3D%20key%3B%20count--,%20probs%2B%2B%29%20p%3D%20%28p%2B%201%29%25%20HSIZE%3B%0A%20%20%20%20if%28count%3D%3D%200%29%20p%3D%20-1%3B%0A%20%20%20%20if%28h%5Bp%5D.probC%3D%3D%20FREE%29%20*number_probs%3D%20probs%3B%0A%20%20%20%20return%20p%3B%0A%7D%0A%0Aint%20update%28HTable%20h,%20int%20key,%20int%20value%29%7B%0A%20%20%20%20int%20number_probs,%20r%3B%0A%20%20%20%20int%20p%3D%20find_probC%28h,%20key,%20%26number_probs%29%3B%0A%0A%20%20%20%20if%28p%3D%3D%20-1%29%20r%3D%200%3B%20//Tabela%20cheia%20e%20key%20inexistente%0A%20%20%20%20else%20if%28h%5Bp%5D.probC!%3D%20FREE%20%26%26%20h%5Bp%5D.key%3D%3D%20key%29%7B%0A%20%20%20%20%20%20%20%20h%5Bp%5D.value%3D%20value%3B%20r%3D%201%3B%0A%20%20%20%20%7D%0A%20%20%20%20else%7B%0A%20%20%20%20%20%20%20%20h%5Bp%5D.probC%3D%20number_probs%3B%0A%20%20%20%20%20%20%20%20h%5Bp%5D.key%3D%20key%3B%0A%20%20%20%20%20%20%20%20h%5Bp%5D.value%3D%20value%3B%0A%20%20%20%20%20%20%20%20r%3D%202%3B%0A%20%20%20%20%7D%0A%20%20%20%20return%20r%3B%0A%7D%0A%0A%0Aint%20main%28%29%20%7B%0A%20%20HTable%20h%3B%0A%20%20h%5B0%5D.probC%3D%20h%5B1%5D.probC%3D%20h%5B3%5D.probC%3D%20h%5B4%5D.probC%3D%20h%5B6%5D.probC%3D%20h%5B7%5D.probC%3D%20h%5B9%5D.probC%3D%20h%5B10%5D.probC%3D%20FREE%3B%0A%20%20for%28int%20i%3D%2012%3B%20i%3C%2022%3B%20i%2B%2B%29%20h%5Bi%5D.probC%3D%20FREE%3B%0A%20%20%0A%20%20h%5B2%5D.probC%3D%20h%5B5%5D.probC%3D%20h%5B8%5D.probC%3D%20h%5B11%5D.probC%3D%20h%5B22%5D.probC%3D%200%3B%0A%20%20h%5B2%5D.key%3D%20140%3B%20h%5B5%5D.key%3D%20120%3B%20h%5B8%5D.key%3D%20140%3B%20h%5B22%5D.key%3D%20160%3B%0A%20%20h%5B2%5D.value%3D%20600%3B%20h%5B5%5D.value%3D%20700%3B%20h%5B8%5D.value%3D%20800%3B%20h%5B22%5D.value%3D%20900%3B%0A%20%20%0A%20%20int%20r%3D%20update%28h,%20180,%20690%29%3B%0A%20%20return%200%3B%0A%7D&mode=edit&origin=opt-frontend.js&py=c&rawInputLstJSON=%5B%5D

#define HSIZE 23
#define FREE -1
#define NV 5
#define WHITE 0
#define GREY 1
#define BLACK 2

typedef struct entry{
    int probC; // -1: free
    int key;
    int value;
} HTable [HSIZE];

typedef struct edgeG{
    int peso;
    int dest;
    struct edgeG *prox;
}*Elist;

typedef Elist Graph[NV];

/*
//Exercício 1
 Invariante: 0<= i<= N-1 && r<= i && forall(r<= k<= i) v[k]<= v[i]
 Condições de verificação (Mostrar que é válido):

 Inicialização: {P}= {N== N== N0} r= 0; i= 0; {I} ........
 Preservação: {I && i< N0- 1} ciclo {I} .......
 Utilidade: {I && i>= N0- 1} ... {Q}= {forall(r<= k<= N0- 1) v[k]<= v[k+ 1]} .......

*/


int hash(int key, int size){
    return key% size;
}

int find_probC(HTable h, int key, int *number_probs){
    int p= hash(key, HSIZE);
    int count= HSIZE, probs= 0;
    for(; count> 0 && h[p].probC!= FREE && h[p].key!= key; count--, probs++) p= (p+ 1)% HSIZE;
    if(count== 0) p= -1;
    if(h[p].probC== FREE) *number_probs= probs;
    return p;
}

int update(HTable h, int key, int value){
    int number_probs, r;
    int p= find_probC(h, key, &number_probs);

    if(p== -1) r= 0; //Tabela cheia e key inexistente
    else if(h[p].probC!= FREE && h[p].key== key){
        h[p].value= value; r= 1;
    }
    else{
        h[p].probC= number_probs;
        h[p].key= key;
        h[p].value= value;
        r= 2;
    }
    return r;
}


/*
//Exercício 4
//Nota: A função "addEdgeFringe" e "updateFringe" irão sempre trabalhar com a orla ordenada (crescentemente) pelos pesos dos vértices adjacentes
//Nota: Não consegui definir as funções supramencionadas

int dijkstraSP(Graph g, int v, int cost[], int ant[]){
  int alc= 0, color[NV], newcost, fringesize;
  for(int i= 0; i< NV; color[i++]= WHITE);
  cost[v]= 0;
  Elist it;
  struct fringe *f, ff;
  f= &ff;
  initFringe(f); fringesize= 0; //Inicia a orla vazia
  addEdgeFringe(f, v, cost); fringesize++; //Adiciona o vértice à orla que está ordenada pelos pesos dos caminhos
  color[v]= GREY;
  while(fringesize> 0){
    v= getEdge(f, cost); fringesize--; //Retira da orla o vértice adjacente com menor peso
    alc++;
    color[v]= BLACK;
    for(it= g[v]; it; it= it-> prox){
        newcost= cost[v]+ it-> peso;
        if(color[v]== WHITE || (color[v]== GREY && cost[it-> dest]> newcost)){
            ant[it-> dest]= v;
            cost[it-> dest]= newcost;
            if(color[v]== WHITE){
                addEdgeFringe(f, it-> dest, cost); fringesize++;
            }
            else updateFringe(f, it-> dest, cost);
        }
    }
  }
  return alc;
}


int aproxMeio(Graph g, int o, int d){
    int cam= 0, cost[NV], pais[NV], alcancaveis;
    for(int i= 0; i< NV; pais[i++]= -1);
    alcancaveis= dijkstraSP(g, o, cost, pais);
    if(pais[d]== o) return o; //Só existe uma aresta o-> d
    if(pais[d]== -1) return -1; //Não existe caminho de do vértice o até ao vértice d

    int vertice= d, ponto_medio= cost[d]/ 2;
    Elist it;
    while(cam<= ponto_medio) {
        for (it = g[pais[vertice]]; it->dest != vertice; it = it->prox);
        cam += it->peso;
        vertice = pais[vertice];
    }
    return vertice;
}
 */

//Exercício 5 a) T(N)= [sum i* N, i= 0 to log2(N- 2)]    b) (está resolvido nos apontamentos do JBB slide 36 Complexidade (função quickSelect))

int main() {
    HTable h;
    h[0].probC= h[1].probC= h[3].probC= h[4].probC= h[6].probC= h[7].probC= h[9].probC= h[10].probC= FREE;
    for(int i= 12; i< 22; i++) h[i].probC= FREE;
    h[2].probC= h[5].probC= h[8].probC= h[11].probC= h[22].probC= 0;
    h[2].key= 140; h[5].key= 120; h[8].key= 140; h[22].key= 160;
    h[2].value= 600; h[5].value= 700; h[8].value= 800; h[22].value= 900;

    int r= update(h, 180, 690);

    return 0;
}
