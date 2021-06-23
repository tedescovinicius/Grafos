#include <stdio.h>
#include <stdlib.h>

/*
 Estrutura responsável por armazenar os vértices. Struct Vertex armazena o véritce em si
	Já ListVertex é uma lista encadeada dos vértices.
*/
struct _vertex 
{
	int value
};
typedef struct _vertex Vertex;

struct _list_vertex
{
	Vertex *v;
	struct _list_vertex *next;
};
typedef struct _list_vertex ListVertex;

/*
 Estrutura responsável por armazenar as arestas. Struct Edge armazena a aresta, 
 	com vértice de origem e vértice de destino
Já ListEdge é uma lista simplesmente encadeada das arestas.
*/
struct _edge 
{
	Vertex origem;
	Vertex destino;
};
typedef struct _edge Edge;
struct _list_edge
{
	Edge *e;
	struct _list_edge *next;
};
typedef struct _list_edge ListEdge;

/*O Grafo, constituido da lista de vértices e arestas
	V-> Armazena a cabeça da lista dos vértices
	E-> Armazena a cabeça da lista de arestas
*/
typedef struct {
	ListVertex *V; //lista de vértices
	ListEdge *E; //Lista de arestas
} Graph;

Graph  *graphInit(){
	Graph *graph = malloc (sizeof(Graph));
	graph->E = NULL;
	graph->V = NULL;
	return graph;
}

//Funções Lista Vertices
ListVertex *insertVertex (ListVertex *head, int value){
	ListVertex *aux,*newElement = malloc (sizeof(ListVertex));
	newElement->v = malloc (sizeof(Vertex));
	newElement->v->value = value;

	if (head == NULL){
		head = newElement;
	}else{
		aux = head;
		while ( aux->next != NULL){ 
			aux=aux->next;
		}
		aux->next = newElement;
		newElement->next = NULL;		
	}

	return head;
}

void printListVertex(ListVertex *head){
	ListVertex *aux = head;
	printf("\n------List Vertex-------\n");
	while (aux != NULL){
		printf("(%d),", aux->v->value);
		aux= aux->next;
	}
	printf("\n-------------\n");
	
}

//Funções Lista Edges


/**
 * O que fazer:
 * 	1 - Fazer métodos inserção e print da lista de Edges
 *  2 - Ler um inteiro para saber se o grafo é orientado ou não.
 * 		- Se o grafo for regular:
 * 			-> Calcular o grau de todos os vértices;
 * 		- Se o grafo for orientado (dirigido):
 * 			-> Calcular o grau de entrada de todos os nodos;
 * 			-> Calcular o grau de saída de todos os nodos;
 * 			-> Listar os nodos que são fonte, eo nodos de sumidouro se existirem.
 * 
 */


int main(){
	Graph *graph = graphInit();

	graph->V = insertVertex(graph->V, 1);
	graph->V = insertVertex(graph->V, 2);
	graph->V = insertVertex(graph->V, 3);
	graph->V = insertVertex(graph->V, 4);

	printListVertex(graph->V);


	return 1;
}