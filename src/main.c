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
    u32 n;
    n = NumeroDeVertices(g);
    u32* Orden = malloc(n*sizeof(u32));
    u32* Color = malloc(sizeof(u32)*n);

    for (u32 i=0; i<n; i++) Orden[i] = i;
    
    u32 lol = Greedy(g, Orden, Color);

    //for(u32 i = 0; i < n; i++) printf("%u " ,Orden[i]);
    //printf("\n");
    //for(u32 i = 0; i < n; i++) printf("%u " ,Nombre(Orden[i], g));
    //printf("\n Orden \n\n");

    printf("\n\n X %u \n\n", lol);

    OrdenImparPar(n, Orden, Color);

    //for(u32 i = 0; i < n; i++) printf("%u " ,Color[i]);
    //printf("\n Color \n\n");


    lol = Greedy(g, Orden, Color);
    
    /*
    for(u32 i = 0; i < n; i++) printf("%u " ,Orden[i]);
    printf("\n");
    for(u32 i = 0; i < n; i++) printf("%u " ,Nombre(Orden[i], g));
    printf("\n Orden \n\n");
    
    for(u32 i = 0; i < n; i++) printf("%u " ,Color[i]);
    printf("\n Color \n\n");
    */
    //printf("\n\n X %u \n\n", lol);
    
    
    for(u32 i = 0; i < 500; i++){
        OrdenImparPar(n, Orden, Color);
        lol = Greedy(g, Orden, Color);
        printf("\n\n X %u  nro %d \n\n", lol, (i+3));
    }
    
    printf("\n\n X %u \n\n", lol);
    
    DestruirGrafo(g);
    free(Orden);
    free(Color);

    return 0;
}
