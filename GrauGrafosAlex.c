Skip to content
Why GitHub? 
Team
Enterprise
Explore 
Marketplace
Pricing 
Search

Sign in
Sign up
alexzarp
/
Grafos
00
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
Grafos/grauVertice.c
@alexzarp
alexzarp algoritmo guloso
Latest commit 2d60e59 on 9 Mar
 History
 1 contributor
334 lines (257 sloc)  7.24 KB
 
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int val;
} Vertice;
//lista duplamente encadeada com todos os vértices
struct tp_list_vet {
	Vertice *v;
	struct tp_list_vet *ant;
	struct tp_list_vet *prox;
};
typedef struct tp_list_vet ListaVertices;



typedef struct {
	Vertice *origem;
	Vertice *destino;
} Aresta;

//lista encadeada de ListaListaArestas
struct tp_list_edges {
	Aresta *e;
	struct tp_list_edges *prox; //8 bytes de memoria
	struct tp_list_edges *ant;
};
typedef struct tp_list_edges ListaArestas;



//armazenar o começo das listas.
typedef struct {
	ListaVertices *primeiroV;
	ListaVertices *ultimoV;

	ListaArestas *primeiroA;
	ListaArestas *ultimoA;
} Grafo;


Grafo *inicializaGrafo(){
	Grafo *G = malloc(sizeof(Grafo));
	
	G->primeiroV = NULL;
	G->ultimoV = NULL;

	G->primeiroA = NULL;
	G->ultimoA = NULL;

	return G;
}

void liberaMemoria(Grafo *G){
	ListaVertices *auxV = G->primeiroV;
	ListaArestas *auxA = G->primeiroA;
	
	while(auxV != NULL){
		auxV = G->primeiroV->prox;
		free(G->primeiroV);
		G->primeiroV = auxV;
	}

	while(auxA != NULL){
		auxA=G->primeiroA->prox;
		free(G->primeiroA);
		G->primeiroA = auxA;
	}


	free(G);

	printf("\nMemoria liberada\n");
}

void imprimeListaVertices(Grafo *g){
	ListaVertices *aux = g->primeiroV;

	printf("****** Lista de Vértices ********\n\t{");
	while(aux != NULL){
		printf("%d", aux->v->val);
		if (aux != g->ultimoV){
			printf(", ");
		}
		aux=aux->prox;
	}
	printf("}\n");
}

void imprimeAresta(Grafo *g){
	ListaArestas *aux = g->primeiroA;

	printf("****** Lista de ListaArestas ********\n\t{");
	while(aux != NULL){
		printf("(%d,%d)", aux->e->origem->val, aux->e->destino->val);
		if (aux != g->ultimoA){
			printf(", ");
		}
		aux=aux->prox;
	}
	printf("}\n");
}

Vertice *getVertice(Grafo *g, int valor){
	ListaVertices *aux = g->primeiroV;

	while(aux != NULL){  //complexidade O(n)
		if (aux->v->val == valor){
			return aux->v;
		}
		aux=aux->prox;
	}

	return NULL;
} 

void insereVertice(Grafo *G, int val){
	Vertice *newV;
	ListaVertices *auxV;

	//vertice
	newV = malloc(sizeof(Vertice)); //cria vértice
	newV->val = val;

	//Elemento da lista
	auxV = malloc(sizeof(ListaVertices)); //Elemento para por na lista.
	auxV->ant = NULL;
	auxV->prox = NULL;
	auxV->v = newV;

	//Encadeamento na lista do auxV
	if (G->primeiroV == NULL){ //lista Vazia
		G->primeiroV = auxV;
		G->ultimoV = auxV; 
	} else { //faz o encadeamento
		G->ultimoV->prox = auxV; //O proximo do ultimo ser o novo elemento
		auxV->ant = G->ultimoV; //anterior do novo elemento ser o ultimo
		G->ultimoV = auxV;  //o novo elemento vira o ultimo
	}
}
/**
 * Nesta função havia um erro, não haviamos criado a aresta com dois vértices, e sim com dois int. Foi corrigido e há uma observação.
 */
void insereAresta(Grafo *G, int origem, int destino){
	Aresta *newA;
	ListaArestas *auxA;
	Vertice *o, *d;
	
	//Aresta
	newA = malloc(sizeof(Aresta)); //Cria a Aresta
	/**
	 * Perceba que aqui estamos criando um novo vértice para representar a origem, 
	 * 	poderiamos buscar um vértice já existente em nossa lista, e caso não encontrar apresentar um erro. 
	 * Nesta tarefa isso não faz diferença. A função getVertice busca um vertice, caso deseje utilizar.
	 * ex -> 
	 * 		o = getVertice(G ,origem);
	 *		newA->origem = o;
	 */
	o = malloc(sizeof(Vertice));
	o->val = origem;
	newA->origem = o;

	d = malloc(sizeof(Vertice));
	d->val = destino;
	newA->destino = d;
	//fim da aresta.


	//Elemento da lista de Arestas
	auxA = malloc(sizeof(ListaArestas));
	auxA->ant = NULL;
	auxA->prox = NULL;
	auxA->e = newA;

	//encadeamento na lista de Arestas.
	if (G->primeiroA == NULL){ //lista Vazia
		G->primeiroA = auxA;
		G->ultimoA = auxA; 
	} else { //faz o encadeamento
		//printf("Não é o primeiro\n");
		G->ultimoA->prox = auxA; //O proximo do ultimo ser o novo elemento
		auxA->ant = G->ultimoA; //anterior do novo elemento ser o ultimo
		G->ultimoA = auxA;  //o novo elemento vira o ultimo
		//printf("Feito\n");
	}
}

//função vai imprimir todas as ListaArestas que o vertice X aparece como origem
//   Ex: X = 2, imprime todas as ListaArestas em que X aparece como origem.
void imprimeListaArestasOrigem( Grafo *g, int valor){
	ListaArestas *aux = g->primeiroA; //primeira aresta

	while(aux != NULL){
			//(vertice(aresta))	
		if (((aux->e)->origem)->val == valor) //pegando a origem de uma aresta
			printf("\tA(%d, %d)\n", aux->e->origem->val, aux->e->destino->val);

		aux = aux->prox;
	}

}

void imprimeListaArestasDestino( Grafo *g, int valor){
	ListaArestas *aux = g->primeiroA; //primeira aresta

	while(aux != NULL){
			//(vertice(aresta))	
		if (((aux->e)->destino)->val == valor) //pegando a origem de uma aresta
			printf("\tA(%d, %d)\n", aux->e->origem->val, aux->e->destino->val);

		aux = aux->prox;
	}

}


//val é o nome do nodo
int grauVertice(Grafo *g, int val){ 
	//Numero de vezes que ele aparece como destino ou origem
	int grau = 0;
	ListaArestas *navArestasIndo = g->primeiroA;
	ListaArestas *navArestasVindo = g->ultimoA;

	while (navArestasIndo != g->ultimoA) {
		if (navArestasIndo->e->destino->val == val){//←Esse é o val do parâmetro
			grau++;
		}
		if (navArestasIndo->e->origem->val == val){
			grau++;
		}

		if (navArestasVindo->e->destino->val == val){
			grau++;
		}
		if (navArestasVindo->e->origem->val == val){
			grau++;
		}
		// \o/ \o/ \o/ \o/ \o /\o/ \o/
		// EEEEEOOooooEEoooEEEeeeOOOoo
		navArestasIndo = navArestasIndo->prox;
		navArestasVindo = navArestasVindo->ant;
	}
	
	
	return grau;
	//isso só conta grafos não dirigidos
}


//Grafo Dirigido
int grauEntradaVertice(Grafo *g, int val){ //todas as vezes que ele é destino
	int grau = 0;
	ListaArestas *aux = g->primeiroA; //primeira aresta

	while(aux != NULL){
			//(vertice(aresta))	
		if (aux->e->destino->val == val) //pegando a origem de uma aresta
			grau++;

		aux = aux->prox;
	}

	
	return grau;
}

//Grafo Dirigido.
int grauSaidaVertice(Grafo *g, int val){ //todas as vezes que ele origem
	//número de vezes que ele aparece como origem.
	int grau;
	ListaArestas *navArestas = g->primeiroA;

	while (navArestas != NULL){
		if (navArestas->e->origem->val == val){
			grau++;
		}

		navArestas = navArestas->prox;
	}

	return grau;
}


int main(){
	Grafo *G; //armazena o conjunto de ListaVertices e ListaArestas

	//ListaVertices *primeiroV, *ultimoV;
	//ListaArestas *primeiraA, *ultimaA;
	
	int i,n, val, origem, destino;
	int grafoDirigido;

	printf("O grafo é dirgido? (0 - Não, 1 - Sim):");
	scanf("%d", &grafoDirigido); //numero de ListaVertices.


	//incializa o grafo
	G = inicializaGrafo();


	printf("Digite o número de vértices:");
	scanf("%d", &n); //numero de ListaVertices.

	for(i=0;i<n;i++){
		scanf("%d", &val);
		insereVertice(G,val);
	}

	printf("\nDigite o número de ListaArestas:");
	scanf("%d", &n); //numero de ListaArestas.

	printf("\nDigite as ListaArestas nmo formato Origem,Destino\n"); // O(n)
	for(i=0;i<n;i++){ //O(n)---O(m) -> número de ListaArestas que terei
		scanf("%d,%d", &origem, &destino);
		insereAresta(G, origem,destino);
	}

	imprimeListaVertices(G);
	imprimeAresta(G);

	if (grafoDirigido==1){
		//possui grau entrada e grau de saida.
		printf("Grau de entrada %d: %d", 2, grauEntradaVertice(G,2));
		printf("Grau de saída %d: %d", 2, grauSaidaVertice(G,2));
	} else{
		printf("Grau %d: %d", 1, grauVertice(G,1));
	}

	liberaMemoria(G);
	

	return 0;
}
© 2021 GitHub, Inc.
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
Loading complete