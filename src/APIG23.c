#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include "APIG23.h"

#define MAX_BUF 128
#define MAX_VERTICES (u32) 4294967295

/*  Funciones auxiliares para crear grafos */

typedef struct edge {
    u32 v1;
    u32 v2;
} edge;


void destruirArreglo(edge* arr){
    free(arr);
    arr = NULL;
}

static void agregarVertice(Grafo g, u32 v, u32 index){
    g->vertices[index].nombre = v;
    g->vertices[index].grado = 0;
    g->vertices[index].vecinos = NULL;
}

static void agregarVecino(Grafo g, u32 indexVertice, u32 vecino, u32 indexVecino){
    g->vertices[indexVertice].vecinos = realloc(g->vertices[indexVertice].vecinos,
                                                 (indexVecino+1)*sizeof(u32)); 
    g->vertices[indexVertice].vecinos[indexVecino] = vecino;
}

static int LeerLineaP(char *buff, u32 *n, u32 *m){
    
    char p;                     // Char para sscanf (Ignorar) 
    char edge[5];               // String para sscanf (Ignorar)
    int findEdge = 0;
    
    while(buff[0] != 'e' && fgets(buff,1024,stdin) != NULL){
        if(buff[0] == 'p'){
            sscanf(buff, "%c %s %u %u",&p, edge, n, m);       
            findEdge = 1;
        }   
    }
    return findEdge;
}

int comparator(const void* p, const void* q){
    edge* edge1 = ((edge*) p);
    edge* edge2 = ((edge*) q);

    if(edge1->v1 > edge2->v1){
        return 1;
    } 
    else if (edge1->v1 < edge2->v1){
        return -1;
    } 
    else {
        if(edge1->v2 > edge2->v2){
            return 1;
        } 
        else{
            return -1;
        }   
    }
    /* El casteo hace que no funque para numeros u32 bordes
    int first = ((int)edge1->v1) - ((int)edge2->v1);
    int second = ((int)edge1->v2) - ((int)edge2->v2);

    if(first == 0){
        return second;
    }
    return first;
    */
}



Grafo ConstruirGrafo()
{
    char buff[1024];            // Buffer para linea
    char p;                     // Char para sscanf  
    u32 n = 0;                  // Nro de vertices
    u32 m = 0;                  // Nro de lados
    u32 v1 = 0;                 // Aux para vertice 1
    u32 v2 = 0;                 // Aux para vertice 2

    if(!LeerLineaP(buff,&n,&m)){
        return NULL;
    }    

    edge* arrayEdges = calloc(2*m, sizeof(edge));
    
    u32 j = m;

    for(u32 i = 0; i < m; i++){
        sscanf(buff, "%c %u %u",&p, &v1, &v2);
        
        // Revisa que la linea sea un lado
        if(p != 'e'){
            destruirArreglo(arrayEdges);
            return NULL;
        }

        arrayEdges[i].v1 = v1;
        arrayEdges[i].v2 = v2;
        arrayEdges[j].v1 = v2;
        arrayEdges[j].v2 = v1;

        j++;

        // Lee proxima linea y si es un EOF 
        // antes de leer las m lineas devuelve NULL 
        if((!fgets(buff,1024,stdin) && i != m-1)){
            destruirArreglo(arrayEdges);
            return NULL;
        }
    }
   
    qsort(arrayEdges, 2*m, sizeof(edge), comparator);

    /* Debug
    for(u32 i = 0; i < 2*m; i++){
        printf("%u %u\n", arrayEdges[i].v1, arrayEdges[i].v2);
    }
    */

    //allocar memoria para la estructura principal
    Grafo g = NULL;
    g = malloc(sizeof(GrafoSt));
    g->num_vertices = n;
    g->num_lados = m;
    g->delta = 0;
    g->vertices = calloc(n, sizeof(vertice));
    
    u32 delta = 0;
    u32 grado = 0;
    u32 indexArray = 0;
    u32 indexVertice = 0;
    u32 indexVecino = 0;
    
    for(u32 j = 0; j < n; j++){
        grado = 0;
        indexVecino = 0;

        agregarVertice(g, arrayEdges[indexArray].v1, indexVertice);
        agregarVecino(g, indexVertice, arrayEdges[indexArray].v2, indexVecino);
        
        grado++;
        indexVecino++;
        indexArray++;

        while (arrayEdges[indexVertice].v1 == arrayEdges[indexArray].v1)
        {
            agregarVecino(g, indexVertice, arrayEdges[indexArray].v2, indexVecino);
            grado++;
            indexVecino++;
            indexArray++;
        }
        
        g->vertices[indexVertice].grado = grado;
        indexVertice++;

        if(grado > delta){
            delta = grado;
        }
    }
    
    g->delta = delta;

    destruirArreglo(arrayEdges);

   return g;
}

u32 NumeroDeVertices(Grafo G)
{
    return G->num_vertices;
}

u32 NumeroDeLados(Grafo G)
{
    return G->num_lados;
}

u32 Nombre(u32 i, Grafo G)
{
    return G->vertices[i].nombre;
}

u32 IndiceVecino(u32 i, u32 j, Grafo G)
{
    if (i >= G->num_vertices || 
        (i < G->num_vertices && j >= G->vertices[i].grado)) 
        return MAX_VERTICES;

    return G->vertices[i].vecinos[j];
}



