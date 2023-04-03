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
    printf("Vecino %u\n", IndiceVecino(1,0,g));
    printf("Vecino %u\n", IndiceVecino(1,1,g));
    printf("Vecino %u\n", IndiceVecino(1,2,g));
    printf("Vertice %u\n", g->vertices[2].nombre);
    printf("Vecino %u\n", IndiceVecino(2,0,g));
    printf("Vecino %u\n", IndiceVecino(2,1,g));
    printf("Vecino %u\n", IndiceVecino(2,2,g));
    printf("Vertice %u\n", g->vertices[3].nombre);
    printf("Vecino %u\n", IndiceVecino(3,0,g));
    printf("Vecino %u\n", IndiceVecino(3,1,g));
    printf("Vecino %u\n", IndiceVecino(3,2,g));
    printf("Vertice %u\n", g->vertices[4].nombre);
    printf("Vecino %u\n", IndiceVecino(4,0,g));
    printf("Vecino %u\n", IndiceVecino(4,1,g));
    printf("Vecino %u\n", IndiceVecino(4,2,g));
    printf("Vecino %u\n", IndiceVecino(4,3,g));
}


int main ()
{
    Grafo g = ConstruirGrafo();
    //debugGrafo(g);
    DestruirGrafo(g);

    return 0;
}
