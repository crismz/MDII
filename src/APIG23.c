#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include "APIG23.h"

#define UNUSED(x) (void)(x)
#define MAX_BUF 128
#define MAX_VERTICES (u32) 4294967295

/*  Funciones auxiliares para crear grafos */
static void agregar_vertice(Grafo G, u32 nombre_vertice)
{
    vertice nuevo_vertice = NULL;
    u32 num_vertice = G->num_vertices;
    u32 indice_vertice = nombre_vertice % num_vertice;
    u32 i = 0;

    while (i < num_vertice){
        if (G->vertices[indice_vertice]->nombre == nombre_vertice){
            // ya existe
            //return G->vertices[indice_vertice];
            return;
        } else {
            indice_vertice++;
            if (indice_vertice == num_vertice)
                indice_vertice = 0;
        }
    }  
    // Creamos el Vertice nuevo
    nuevo_vertice = malloc(sizeof(VerticeSt));
    nuevo_vertice->nombre = nombre_vertice;
    // TODO: vecinos
    nuevo_vertice->vecinos = NULL;
    return;
}

static void agregar_vecino(Grafo G, vertice v1, vertice v2)
{
    /* agrega a v1->vecinos el nombre de v2
     * TODO:
     *  -podemos usar el grado para indexar??
     *  -realloc???
     *  -casos
     */
    assert(v1->nombre != v2->nombre);
    u32 grado = G->grados[v1->nombre % G->num_vertices];
    v1->vecinos[grado] = v2->nombre;    
}

Grafo ConstruirGrafo()
{
    FILE *file = stdin;
    // Salteamos los comentarios
    char buf[MAX_BUF];
    while (buf[0] == 'c'){
        // ignoramos las lineas que comienzan con c
        fgets(buf, MAX_BUF, file); 
    }

    //allocar memoria para la estructura principal
    Grafo g;
    g = malloc(sizeof(GrafoSt));
    g->num_vertices = 0;
    g->num_lados = 0;
    g->delta = 0;
    g->vertices = NULL;
    g->nombres = NULL;
    g->grados = NULL;

    agregar_vertice(g, 1);
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
    return G->nombres[i];
}

u32 IndiceVecino(u32 i, u32 j, Grafo G)
{
    if (i >= G->num_vertices || 
        (i < G->num_vertices && j >= G->grados[i])) 
        return MAX_VERTICES;

    return G->vertices[i]->vecinos[j];
}



