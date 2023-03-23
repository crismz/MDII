#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;

typedef struct 
{
    u32 indice;
    u32 *vecinos;
} vertice;

typedef struct 
{
    u32 *nombres;                           // Arreglo con los nombres de los vertices      
    u32 *grados;                            // Arreglo con los grados de los vertices
    u32 num_vertices;                       // Numero de vertices totales
    u32 num_lados;                          // Numero de lados
    u32 delta;                              // Maximo grado

    vertice* vertices;                     // Arreglo con los vertices        

} GrafoSt;


/*

vecino(j, i, G) = G->vertices[i]->vecinos[j];








*/