#include <stdlib.h>
#include <stdio.h>



void printGrafo(int **grafo, int npont){
    int i,j;
    for (i=0; i<npont; i++) {
        for (j=0; i<npont; j++) {
            printf("%d", grafo[i][j]);
        }
        printf("/n");
    }

}

int** insertNode(int **grafo, int orig, int dest){
    if (grafo[orig][dest] != 0) {
        printf("Ja existe ligação");
    }else {
        grafo[orig][dest] = 1;
    }
    
    /*Mete a um os nós que estão ligados */

    return grafo;
}


int main(int argc, char *argv[])
{
	int npontos, nlig, i,j;
    int orig, dest;
    int problemas, nos, probno;
    int **Grafo;
    
    
    
    scanf("%d %d", &npontos, &nlig);
    printf("Numero de pontos e ligacoes: %d %d\n", npontos, nlig);

    
    Grafo = malloc(npontos * sizeof(int*));
    printf("CHEGUEI AQUI");
    for (i=0; i<npontos; i++)
    {   printf("CHEGUEI AQUI");
        Grafo[i] = malloc(npontos * sizeof(int));
    }

    printf("CHEGUEI AQUI");
    
    int probnos[npontos];
    


    /*Inicialização do Grafo em Matriz*/
    
    for(i=0; i<=npontos; i++){
        for (j=0; j<=npontos; j++) {
            Grafo[i][j]=0;
        }}
    
    printGrafo(Grafo, npontos);

	/* Insercao das ligaçoes na matriz de nos*/
	while (nlig > 0) {
        scanf("%d %d", &orig, &dest);
        printf("Origem %d - Destino %d\n", orig, dest);
        if(orig < dest /*&& orig >= 0 && dest <= npontos*/){
            insertNode(Grafo, orig, dest);
            nlig--;
        }else {
            printf("Erro: A origem é maior que o destino ou origem é menor que zero ou destino é maior que nº pontos");
        }
    }
    
    
        scanf("%d", &problemas);
            while (problemas > 0) {
            scanf("%d", &nos);
            while (probnos > 0) {
                scanf(" %d\n", &probno);
                probnos[probno] = 1;
                probno--;
            }
            problemas--;
        }
        
        
    
    printGrafo(Grafo, npontos);

	return 0;
}


