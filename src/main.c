#include "APIG23.h"

void debugGrafo(Grafo g){
    printf("numvertices %u\n",g->num_vertices);
    printf("numlados %u\n",g->num_lados);
    printf("delta %u \n",g->delta);

    printf("Vertice %u\n", g->vertices[0].nombre);
    printf("Vecino %u\n", IndiceVecino(0,0,g));
    printf("Vecino %u\n", IndiceVecino(0,1,g));
    printf("Vecino %u\n", IndiceVecino(0,2,g));
    printf("Vertice %u\n", g->vertices[1].nombre);
    printf("Vertice %u\n", g->vertices[2].nombre);
    printf("Vertice %u\n", g->vertices[3].nombre);
}


int main ()
{
    Grafo g = ConstruirGrafo();
    debugGrafo(g);

    return 0;
}
