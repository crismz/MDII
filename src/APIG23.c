#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include "APIG23.h"

#define MAX_VERTICES (u32) 4294967295

/* Estructuras auxiliar */

typedef struct edge {
    u32 v1;
    u32 v2;
} edge;

typedef struct verticeIndice {
    u32 v;
    u32 index;
} verticeIndice;


/*  Funciones auxiliares para crear grafo */

static verticeIndice** creartablaHash(edge* arregloLados, u32 tableSize, u32 m){
    u32 hindex=0, hclave=0, vertCont=0;
    verticeIndice** tablaHash = calloc(tableSize, sizeof(verticeIndice*)); 

    hclave = arregloLados[0].v1 % tableSize;
    tablaHash[hclave] = malloc(sizeof(verticeIndice));
    tablaHash[hclave]->v = arregloLados[0].v1;
    tablaHash[hclave]->index = vertCont;
    vertCont++;

    for(u32 i = 1; i < 2*m; i++){
        if(arregloLados[i-1].v1 != arregloLados[i].v1){
            hclave = arregloLados[i].v1 % tableSize;
            for(u32 j=1; j<tableSize; j++){
                hindex = (hclave + j) % tableSize;
                if(tablaHash[hindex] == NULL){
                    tablaHash[hclave] = malloc(sizeof(verticeIndice));
                    tablaHash[hclave]->v = arregloLados[i].v1;
                    tablaHash[hclave]->index = vertCont;
                    vertCont++;
                    break;
                }
            }
        }       
    }
    return tablaHash;

}

static u32 buscarHash (verticeIndice** tablaHash, u32 vertice, u32 n){
    u32 tableSize = 3*n;
    u32 hindex = 0, vindex = 0;
    u32 hclave = vertice % tableSize;

    for(u32 i=0; i<tableSize; i++){
        hindex = (hclave + i) % tableSize;
        if(tablaHash[hindex]->v == vertice){
            vindex = tablaHash[hindex]->index;
            break;
        }
    }
    return vindex;
}

static void destruirHash(verticeIndice** tablaHash, u32 tableSize){
    for(u32 i = 0; i < tableSize; i++){
        free(tablaHash[i]);
        tablaHash[i] = NULL;
    }
    free(tablaHash);
    tablaHash = NULL;
}

// Funcion para leer la linea p
// Leemos stdin, se coloca en buff y se escanea del buff
static int LeerLineaP(u32 *n, u32 *m, char* buff){
    char p;                     // Char para sscanf 
    char edge[5];               // String para sscanf 
    int encontroEdge = 0;       // Actua como un booleano
    
    while(fgets(buff, 1024, stdin) != NULL && buff[0] != 'e'){
        if(buff[0] == 'p'){
            sscanf(buff, "%c %s %u %u",&p, edge, n, m);
            if(strcmp(edge,"edge") != 0) return 0;
            encontroEdge = 1;
        }   
    }

    return encontroEdge;
}

static void destruirArreglo(edge* arr){
    free(arr);
    arr = NULL;
}

// Funcion para construir estructura auxiliar
// Se hace del tamaño 2*m para que esten todos los lados 
// y los lados invertidos (es decir va a estar 1 2 y 2 1)
static edge* construirArregloLados(u32 m,char* buff){
    char p;                     // Char para sscanf  
    u32 v1 = 0;                 // Aux para vertice 1
    u32 v2 = 0;                 // Aux para vertice 2
    edge *arregloLados = calloc(2*m, sizeof(edge));    
    u32 j = m;

    for(u32 i = 0; i < m; i++){
        sscanf(buff, "%c %u %u",&p, &v1, &v2);
        
        // Revisa que la linea sea un lado
        if(p != 'e'){
            destruirArreglo(arregloLados);
            return NULL;
        }

        arregloLados[i].v1 = v1;
        arregloLados[i].v2 = v2;
        arregloLados[j].v1 = v2;
        arregloLados[j].v2 = v1;

        j++;

        // Lee proxima linea y si es un EOF 
        // antes de leer las m lineas devuelve NULL 
        if((!fgets(buff,1024,stdin) && i != m-1)){
            destruirArreglo(arregloLados);
            return NULL;
        }
    }

    return arregloLados;
}

static void agregarVertice(Grafo g, u32 v, u32 index){
    g->vertices[index].nombre = v;
    g->vertices[index].grado = 0;
    g->vertices[index].vecinos = NULL;
}

static void agregarVecino(Grafo g, u32 indexVertice, u32 vecino, u32 indexVecino, verticeIndice** tablaHash, u32 n){
    g->vertices[indexVertice].vecinos = realloc(g->vertices[indexVertice].vecinos,
                                                 (indexVecino+1)*sizeof(u32)); 
    
    u32 vecinoIndexado = buscarHash(tablaHash, vecino, n);
    g->vertices[indexVertice].vecinos[indexVecino] = vecinoIndexado;
}

// Funcion para el qsort
static int comparator(const void* p, const void* q){
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
}

/* Fin de funciones auxiliares para crear grafo */


Grafo ConstruirGrafo()
{
    char buff[1024];            // Buffer para linea
    u32 n = 0;                  // Nro de vertices
    u32 m = 0;                  // Nro de lados

    if(!LeerLineaP(&n, &m, buff)){
        return NULL;
    }    

    edge* arregloLados = construirArregloLados(m, buff);
    if(!arregloLados) return NULL;

    qsort(arregloLados, 2*m, sizeof(edge), comparator);

    verticeIndice** tablaHash = creartablaHash(arregloLados, 3*n, m);

    Grafo g = NULL;
    g = malloc(sizeof(GrafoSt));
    g->num_vertices = n;
    g->num_lados = m;
    g->delta = 0;
    g->vertices = calloc(n, sizeof(VerticeSt));
    
    u32 delta = 0;
    u32 grado = 0;
    u32 indexArray = 0;
    u32 indexVecino = 0;
    
    for(u32 j = 0; j < n; j++){
        grado = 0;
        indexVecino = 0;

        agregarVertice(g, arregloLados[indexArray].v1, j);  
        agregarVecino(g, j, arregloLados[indexArray].v2, indexVecino, tablaHash, n);

        grado++;
        indexVecino++;
        indexArray++;

        while (g->vertices[j].nombre == arregloLados[indexArray].v1)
        {   
            agregarVecino(g, j, arregloLados[indexArray].v2, indexVecino, tablaHash, n);
            grado++;
            indexVecino++;
            indexArray++;
            if(indexArray == 2*m) break;            // Para el caso del ultimo lado(caso borde)
        }

        g->vertices[j].grado = grado;

        if(grado > delta){
            delta = grado;
        }
    }
    
    g->delta = delta;

    destruirHash(tablaHash, 3*n);
    destruirArreglo(arregloLados);

    return g;
}

void DestruirGrafo(Grafo G){
    for(u32 i = 0; i < G->num_vertices; i++){
        free(G->vertices[i].vecinos);
        G->vertices[i].vecinos = NULL;
    }
    free(G->vertices);
    G->vertices = NULL;
    free(G);
    G = NULL;
}

u32 NumeroDeVertices(Grafo G)
{
    return G->num_vertices;
}

u32 NumeroDeLados(Grafo G)
{
    return G->num_lados;
}

u32 Delta(Grafo G)
{
    return G->delta;
}

u32 Nombre(u32 i, Grafo G)
{
    return G->vertices[i].nombre;
}

u32 Grado(u32 i, Grafo G)
{
    return G->vertices[i].grado;
}

u32 IndiceVecino(u32 j, u32 i, Grafo G)
{
    if (i >= G->num_vertices || 
        (i < G->num_vertices && j >= G->vertices[i].grado)) 
        return MAX_VERTICES;

    return G->vertices[i].vecinos[j];
}
