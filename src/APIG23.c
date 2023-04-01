#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include "APIG23.h"

#define MAX_BUF 128
#define MAX_VERTICES (u32) 4294967295

/*  Funciones auxiliares para crear grafos */
static void agregarVertice(Grafo g, u32 v, u32 *index){
    vertice new_vertice = malloc(sizeof(vertice));
    new_vertice->nombre = v;
    new_vertice->grado = 0;
    new_vertice->vecinos = NULL;
    g->vertices[*index] = *new_vertice;
    *index++;
}

static void agregarVecino(Grafo g, u32 v, u32 vecino, u32 index){

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

typedef struct edge {
    u32 v1;
    u32 v2;
} edge;

int comparator(const void* p, const void* q){
    edge* edge1 = ((edge*) p);
    edge* edge2 = ((edge*) q);
    int first = ((int)edge1->v1) - ((int)edge2->v1);
    int second = ((int)edge1->v2) - ((int)edge2->v2);

    if(first == 0){
        return second;
    }
    return first;
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
    
    edge arrayEdges[m];


    for(u32 i = 0; i < m; i++){
        sscanf(buff, "%c %u %u",&p, &v1, &v2);
        
        // Revisa que la linea sea un lado
        if(p != 'e'){
            return NULL;
        }

        arrayEdges[i].v1 = v1;
        arrayEdges[i].v2 = v2;

        // Lee proxima linea y si es un EOF 
        // antes de leer las m lineas devuelve NULL 
        if((!fgets(buff,1024,stdin) && i != m-1)){
            return NULL;
        }
    }

    qsort(arrayEdges, m, sizeof(edge), comparator);

    //Para debug
    for(u32 i = 0; i < m; i++){
        printf("%u %u\n", arrayEdges[i].v1, arrayEdges[i].v2);
    }
    

   
    //allocar memoria para la estructura principal
    Grafo g = NULL;
    g = malloc(sizeof(GrafoSt));
    g->num_vertices = n;
    g->num_lados = m;
    g->delta = 0;
    g->vertices = calloc(n, sizeof(vertice));

    u32 delta = 0;
    u32 grado = 0;
    u32 indexVert = 0;

    for(u32 j = 0; j < n; j++){
        agregarVertice(g, arrayEdges[j].v1, &indexVert);
    }
    


   return NULL;
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



