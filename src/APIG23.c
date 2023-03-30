#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include "APIG23.h"

#define UNUSED(x) (void)(x)
#define MAX_BUF 128
#define MAX_VERTICES (u32) 4294967295
#define hash 1 // Cosito para hash

//Pruebita
#if hash

typedef struct node {
  int value;
  struct node* next;
} node;

node** create_hash_table(int n) {
  node** hash_table = malloc(n * sizeof(node*));
  for (int i = 0; i < n; i++) {
    hash_table[i] = NULL;
  }
  return hash_table;
}

void insert(node** hash_table, int value, int n) {
  int idx = value % n;
  if (hash_table[idx] == NULL) {
    // if the slot is empty, create a new node and add it to the slot
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    hash_table[idx] = new_node;
  } else {
    // if the slot is not empty, traverse the linked list and add the new node to the end
    node* cur_node = hash_table[idx];
    while (cur_node->next != NULL) {
      cur_node = cur_node->next;
    }
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    cur_node->next = new_node;
  }
}
#endif


/*  Funciones auxiliares para crear grafos */
static void agregar_vertice(Grafo G, u32 nombre_vertice)
{
    vertice nuevo_vertice = NULL;
    u32 num_vertice = G->num_vertices;
    u32 indice_vertice = nombre_vertice % num_vertice;
    u32 i = 0;

    while (i < num_vertice){
        if (G->vertices[indice_vertice].nombre == nombre_vertice){
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

}

static int LeerLado(char *buff, u32 *n, u32 *m){
    
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




Grafo ConstruirGrafo()
{
    /*
    //allocar memoria para la estructura principal
    Grafo g = NULL;
    g = malloc(sizeof(GrafoSt));
    g->num_vertices = 0;
    g->num_lados = 0;
    g->delta = 0;
    g->vertices = NULL;
    */



    char buff[1024];            // Buffer para linea
    char p;                     // Char para sscanf (Ignorar) 
    u32 n = 0;                  // Nro de vertices
    u32 m = 0;                  // Nro de lados
    u32 v1 = 0;                 // Aux para vertice 1
    u32 v2 = 0;                 // Aux para vertice 2

    if(!LeerLado(buff,&n,&m)){
        return NULL;
    }    

    printf("%u %u",n,m);
    
    // Falta agregar que si no lee m lineas debe devolver NULL la estructura
    for(u32 i = 0; i < m; i++){
        sscanf(buff, "%c %u %u",&p, &v1, &v2);
        // Debug  printf("\n\n%u %u\n\n", v1, v2);




        fgets(buff,1024,stdin);
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



