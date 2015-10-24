#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int SccCounter = 0;
int SizeCounter = 0;
int SharingGroups = 0;
int GroupCounterAux=0;
int GroupCounter = 1;

typedef struct Vertice {
	int v;
    int w;
    
} Vertice;

typedef struct node {
	int id;
	int index;
	int lowlink;
	int group;
	bool stacked;
	struct arco *adj;
}Node;

typedef struct arco {
	int value;
	struct arco *next;
}*Arco;

typedef struct grafo {
    int V;
    int E;
    struct node *nodes;
}*Grafo;

typedef struct stack {
	int id;
	struct stack* previous;
}Stack;

Stack *Top = NULL;
Grafo G = NULL;

Arco NEW(int v, Arco list) {
    Arco x = malloc(sizeof(struct arco));
    x->value = v;
    x->next = list;
    return x;
}

void GRAFOinsertV(Vertice e) {
    int v = e.v, w = e.w;
 	if(G->nodes[v-1].adj == NULL) {
	G->nodes[v-1].adj = malloc(sizeof(struct arco));
	G->nodes[v-1].adj->value = w;
	}
	else {
	 G->nodes[v-1].adj = NEW(w, G->nodes[v-1].adj);
	 
	}
	G->E++;
}


Grafo GRAFOinit(int V) {
    int v;
 
    G = malloc(sizeof(struct grafo));
    G->V = V;
    G->E = 0;
    G->nodes = malloc(V * sizeof(struct node));
    
   
    for (v = 0; v < V; v++) {
        G->nodes[v].id = v+1;
	G->nodes[v].index = 0;
	G->nodes[v].lowlink = 0;
	G->nodes[v].group = 0;
	G->nodes[v].stacked = false;
	G->nodes[v].adj = NULL;
	}
    
    return G;
}

void GrafoPrinter(int people) {	
	int i;	
	for(i=0; i < people; i++){
    	struct arco *aux = G->nodes[i].adj;

        while (aux != NULL) {
	printf("%d %d\n", G->nodes[i].id, aux->value);
	aux = aux->next;
        }
     
    }
}

void GrafoReader(Vertice *id, int ligs) {
	int orig, dest;
	
	while (ligs != 0) {
        scanf("%d %d", &orig, &dest);
        id->v = orig;
        id->w = dest;
        GRAFOinsertV(*id);
        ligs--;
        
    }
}


void pushStack(Node n) {
	Stack *ele = (Stack *)malloc(sizeof(struct stack));
	ele->id = n.id;
	G->nodes[n.id-1].stacked = true;
	n.stacked = true;
	ele->previous = Top;
	Top = ele;

		
}

int popStack() {
	
	int aux;
	Stack *temp;
	aux = Top->id;
	G->nodes[aux-1].stacked = false;
	temp = Top;
	Top = Top->previous;
	free(temp);

	return aux;
}

void strongconnect(Node n, int starter) {
	
	int Succ=0;
	int index = starter;
	int SizeCounterAux=0;
	
	
	n.index = index;
	n.lowlink = index;
	G->nodes[n.id-1].index = n.index;
	G->nodes[n.id-1].lowlink = n.lowlink;
	index++;
	pushStack(n);
	
		while(n.adj != NULL) {
		int auxId = n.adj->value;
		Node w = G->nodes[auxId-1];
		
		if(w.index == 0){
			strongconnect(w, index);
			w.lowlink = G->nodes[w.id-1].lowlink;
			w.index = G->nodes[w.id-1].index;
			
			if(n.lowlink > w.lowlink) {
				n.lowlink = w.lowlink;
				G->nodes[n.id-1].lowlink = w.lowlink;
				
			}
		}
		else if(w.stacked && (w.index < n.lowlink)) {
			n.lowlink = w.index;
			G->nodes[n.id-1].lowlink = w.index;
			
		}
		
							
			n.adj = n.adj->next;
	
	}

    if(n.lowlink == n.index) {
		do {
			
			if(Top != NULL) {
			Succ = popStack();
			}

			
			if(G->nodes[Succ-1].group < GroupCounter-1){
			
			GroupCounterAux = 1;
			}
			G->nodes[Succ-1].group = GroupCounter;
			if(Top != NULL) {
				G->nodes[Top->id-1].group =GroupCounter;
			}

			SizeCounterAux++;
		} while(n.id != Succ);
		
		if(SizeCounterAux > SizeCounter){
			SizeCounter = SizeCounterAux;
		}
		
		if(GroupCounterAux == 1){
			
			GroupCounterAux = 0;
			SharingGroups++;
		}
		GroupCounter++;
		SccCounter++;
							
	}					
}

int main(int argc, char *argv[])
{
	int npax, nlig, i;
	int index = 1;
		   
	Vertice *id = (struct Vertice*) malloc(sizeof(struct Vertice));

	scanf("%d %d", &npax, &nlig);
		    
	G = GRAFOinit(npax);

	
	GrafoReader(id, nlig);
	

	for(i=0; i < npax; i++) {
		if(G->nodes[i].index == 0) {
			strongconnect(G->nodes[i], index);
		}
	}
	printf("%d\n", SccCounter);
	printf("%d\n", SizeCounter);
	printf("%d\n", SccCounter - SharingGroups);				

	return 0;
}


