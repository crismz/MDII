#include "APIG23.h"
#include "APIParte2.h"
#include <stdio.h>
#include <stdlib.h>

void debugGrafo(Grafo g){
    printf("numvertices %u\n",g->num_vertices);
    printf("numlados %u\n",g->num_lados);
    printf("delta %u \n",g->delta);

    for(u32 i = 31; i < 51; i++){
        printf("Vertice %u : Vecino nro %u es %u\n", Nombre(0,g), i ,IndiceVecino(i, 0, g));
    }
}


int main (){

    Grafo g = ConstruirGrafo();
    //debugGrafo(g);
//    DestruirGrafo(g);
    u32 n;
    n = NumeroDeVertices(g);
    u32* Orden = malloc(n*sizeof(u32));
    u32* Color = malloc(sizeof(u32)*n);

    for (u32 i=0; i<n; i++) Orden[i] = i;

    OrdenImparPar(n, Orden, Color);
    u32 lol = Greedy(g, Orden, Color);
    //printf("\n\n\n\n\n %d \n\n\n\n\n", lol);
    
    return 0;
}
