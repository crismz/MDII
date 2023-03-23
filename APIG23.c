#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "APIG23.h"

#define UNUSED(x) (void)(x)
#define MAX_NAMESIZE 200
#define MAX_VERTICES (u32)4294967295

Grafo ConstruirGrafo()
{
    //allocar memoria para la estructura principal
    Grafo g;
    g = malloc(sizeof(GrafoSt));
    g->num_vertices = 0;
    g->num_lados = 0;
    g->delta = 0;
    g->vertices = NULL;
    g->nombres = NULL;
    g->grados = NULL;
    
    FILE *file;
    char* filename = NULL;
    //TODO: error checking
    filename = fgets(filename, sizeof(filename), stdin);
    file = fopen(filename, "r");
    if (file) {
        while (fgetc(file) != EOF)
            ;
    }
    else {
        printf("Archivo no encontrado.");
        exit(1);
    }

    fclose(file);
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
    return G->nombres[i];
}

u32 IndiceVecino(u32 i, u32 j, Grafo G)
{
    if (i > G->num_lados) return MAX_VERTICES;
    
}



