typedef unsigned int u32;

typedef struct 
{
    u32 nombre;         // Nombre de vertice
    u32 grado;          // Grado de vertice
    u32 *vecinos;       // Vecino de vertice
} VerticeSt;

typedef struct 
{
    u32 num_vertices;                       // Numero de vertices totales
    u32 num_lados;                          // Numero de lados
    u32 delta;                              // Maximo grado

    VerticeSt* vertices;                     // Arreglo con los vertices        

} GrafoSt;


/*

vecino(j, i, G) = G->vertices[i]->vecinos[j];








*/
