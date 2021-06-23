#include <stdio.h>
#include <stdlib.h>

struct _vertex {
    int value;
};
typedef struct _vertex Vertex;


struct _list_vertex{
    Vertex *v;
    struct _list_vertex *next;
    struct _list_vertex *prev;
};
typedef struct _list_vertex ListVertex;

typedef struct {
    Vertex *origem;
    Vertex *destino;
}Edge;

struct _list_edge{
    Edge *e;
    struct _list_edge *next;
    struct _list_edge *prev;
};
typedef struct _list_edge ListEdge;

typedef struct {
    ListVertex *origemV; 
    ListVertex *destinoV; 

    ListEdge *origemE; 
    ListEdge *destinoE;
} Graph;


Graph *graphInit(){
    Graph *graph = malloc (sizeof(Graph));

    graph->origemV = NULL;
    graph->destinoV = NULL;

    graph->origemE = NULL;
    graph->destinoE = NULL;

    return graph;
}


//Funções Lista Vertices
void insertVertex (Graph *G, int value){
    Vertex *newV;
    ListVertex *auxV;

    newV = malloc(sizeof(Vertex));
    newV->value = value;

    auxV = malloc(sizeof(ListVertex));
    auxV->prev = NULL;
    auxV->next = NULL;
    auxV->v = newV;

    if(G->origemV == NULL){
        G->origemV = auxV;
        G->destinoV = auxV;
    }else{
        G->destinoV->next = auxV;
        auxV->prev = G->destinoV;
        G->destinoV= auxV;
    }

}

void insertEdges (Graph *G, int origem, int destino){ 
    ListEdge *auxA;
    Edge *newE;
    Vertex *o, *d;

    newE = malloc(sizeof(Edge));

    o = malloc(sizeof(Vertex));
    o->value = origem;
    newE->origem = o;

    
    d = malloc(sizeof(Vertex));
    d->value = destino;
    newE->destino = d;


    auxA = malloc(sizeof(ListEdge));
    auxA->prev = NULL;
    auxA->next = NULL;
    auxA->e = newE;


    if (G->origemE == NULL){
        G->origemE = auxA;
        G->destinoE = auxA;
    }else{
        G->destinoE->next = auxA;
        auxA->prev = G->destinoE;
        G->destinoE = auxA;      
    }
};


void printListVertex(Graph *g){
    ListVertex *aux = g->origemV;

    printf("\n------List Vertex-------\n");
    while (aux != NULL){
        printf("(%d),", aux->v->value);
        if(aux != g->destinoV){
            printf(", ");
        }
        aux= aux->next;
    }
    printf("\n-------------\n");
    
}

void printlistEdge (Graph *g){
    ListEdge *aux = g->origemE;

    printf("\n------List Arestas-------\n");
    while (aux != NULL){
        printf("Aresta de Origem, (%d), ", aux->e->origem->value);
        printf("Aresta de Destino, (%d), ", aux->e->destino->value);
        aux= aux->next;
    }
    printf("\n-------------\n");
    
}

//Funções Lista Edges
/**
 * O que fazer:
 *     1 - Fazer métodos inserção e print da lista de Edges
 *  2 - Ler um inteiro para saber se o grafo é orientado ou não.
 *         - Se o grafo for regular:
 *             -> Calcular o grau de todos os vértices;
 *         - Se o grafo for orientado (dirigido):
 *             -> Calcular o grau de entrada de todos os nodos;
 *             -> Calcular o grau de saída de todos os nodos;
 *             -> Listar os nodos que são fonte, eo nodos de sumidouro se existirem.
 * 
 */



int main(){
    Graph *G;

    int i,n, val, origem, destino;

    G = graphInit();

    insertVertex(G,1);
    // insertVertex(G,2);
    // insertVertex(G,3);
    // insertVertex(G,4);

    // Vertex *ori = malloc(sizeof(Vertex));
    // ori->value = 5;

    // Vertex *des = malloc(sizeof(Vertex));
    // des->value = 5;

    // graph->E = insertEdges(graph->E,ori,des);
    insertEdges(G,1,2);

    printlistEdge(G);

    //printListVertex(graph->V);


    return 0;
}
