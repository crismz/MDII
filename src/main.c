#include "APIG23.h"

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
    DestruirGrafo(g);

    return 0;
}
