#include "APIParte2.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_GREEDY (u32) 4294967295   // Valor que devuelve gredy en caso de error 
#define OK_ORDEN (char) 0               // Valores que devuelven las funciones de orden
#define ERROR_ORDEN (char) 1            // en caso de error o no

//  Estructura para las funciones de orden.
//  Se usa para ordenar los colores y poder mantener 
//  los indices del vertice que le correspondia.
//  - color = Color[i]  - indice = i
//  La estructura es de tamaño n ya que se copia el arreglo Color.

typedef struct ColorOrden {
    u32 color;
    u32 indice;
} ColorOrden;

//  Estructura para la funcion de OrdenJedi.
//  Se usa para anotar el valor F de cada color 
//  con los respectivos vertices que tienen el color.
//  - valorF = x * sum(Grado(i,G))  para todo i : Color[i] = x
//  - indicesVertices son los indices de los vertices con el color x
//  - cantidadV es la cantidad de vertices con ese color
//  La estructura es de tamaño r = Numero de colores.

typedef struct JediOrden {
    u32 valorF;
    u32* indicesVertices;
    u32 cantidadV;
} JediOrden;


// Funcion para buscar el primer color disponible en un arreglo 
// (Lo que realmente hace es buscar es el minimo numero 
//  que no esta en el arreglo). 
// La idea se saco de aca: 
// https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array/
// - arr = colorVecinos (arreglo que contiene el color de los vecinos de un vertice)
// - grado = grado del vertice

static u32 primerColorDisponible(u32* arr, u32 grado){

    // Flags
    int estaCero = 0;
    int estaUno = 0;

    for (u32 i = 0; i < grado; i++){
        if (arr[i] == 0){
            estaCero = 1;
            break;
        } 
    }

    // Si cero esta disponible devuelve 0
    if (estaCero == 0) return 0;
    
    for(u32 i = 0; i < grado; i++){
        if (arr[i] == 1){
            estaUno = 1;
            break;
        } 
    }

    // Si uno esta disponible devuelve 1
    if (estaUno == 0) return 1;

    // Cambia valores que no sirven a 1
    for (u32 i = 0; i < grado; i++){
        if (arr[i] == 0 || arr[i] >= grado) 
            arr[i] = 1;
    }

    // Actualiza los indices de acuerdo a los valores
    for (u32 i = 0; i < grado; i++){
        arr[(arr[i] - 1) % grado] += grado;
    }
    
    // Encontrar el indice con valor menor a grado
    for (u32 i = 0; i < grado; i++){
        if (arr[i] < grado)
            return i + 1;
    }
    
    // Si el arreglo tiene los colores 0 a n-1
    return grado;
}


u32 Greedy(Grafo G, u32* Orden, u32* Color)
{
    u32 n = NumeroDeVertices(G);
    u32 color = 0;               
    u32 cantidadColor = 0;           // Cantidad de colores  
    u32 sinColor = Delta(G) + 2;     // Va a tener como maximo Delta(G) + 1 colores
    
    for (u32 i = 0; i < n; i++) {
        Color[i] = sinColor;
    }

    Color[Orden[0]] = color;

    for (u32 i = 1; i < n; i++) { 
        u32 grado = Grado(Orden[i], G);
        u32* colorVecinos = malloc(sizeof(u32) * grado);

        // Si falla al asignar memoria devuelve error
        if (colorVecinos == NULL) return ERROR_GREEDY;

        for(u32 j=0; j<grado; j++){
            colorVecinos[j] =  Color[IndiceVecino(j, Orden[i], G)];
        }

        color = primerColorDisponible(colorVecinos, grado);
        Color[Orden[i]] = color;
        free(colorVecinos);
        if (color > cantidadColor) cantidadColor++;
    }

    cantidadColor++;
    return cantidadColor;
}


// Funciones para el comparatorImparPar

static int EsPar(u32 n){ return !(n % 2); }

static int auxComparator(u32 a, u32 b)
{
    if (a > b) return -1;
    return 1;
}

// Comparador para el qsort del OrdenImparPar

static int comparatorImparPar(const void *p, const void *q) 
{
    ColorOrden* a = (ColorOrden*) p;
    ColorOrden* b = (ColorOrden*) q;

    if ((EsPar(a->color) && EsPar(b->color)) 
                        || (!EsPar(a->color) && !EsPar(b->color))){
        return auxComparator(a->color, b->color);
    }   
    if (EsPar(a->color) && !EsPar(b->color)) {
        return 1;
    } else return -1;
}


char OrdenImparPar(u32 n, u32* Orden, u32* Color)
{   
    ColorOrden* colorOrden = malloc(n * sizeof(ColorOrden));
    
    if (colorOrden == NULL) {   
        return OK_ORDEN;
    }

    for (u32 i = 0; i < n; i++){
        colorOrden[i].indice = i;
        colorOrden[i].color = Color[i];
    }

    qsort(colorOrden, n, sizeof(colorOrden), comparatorImparPar);

    for (u32 i = 0; i < n; i++){
        Orden[i] = colorOrden[i].indice;
    }

    free(colorOrden);
    return OK_ORDEN;
}


// Comparador para qsort de ColorOrden, ordena de forma natural

static int comparatorOrdenNatural(const void *p, const void *q){
    ColorOrden* a = (ColorOrden*) p;
    ColorOrden* b = (ColorOrden*) q;

    if (a->color < b->color) return -1;
    return 1;
}

// Comparador para qsort de JediOrden, ordena valorF de mayor a menor

static int comparatorValorF(const void *p, const void *q){
    JediOrden* a = (JediOrden*) p;
    JediOrden* b = (JediOrden*) q;

    if (a->valorF > b->valorF) return -1;
    return 1;
}

// Funcion para contar la cantidad de colores = r

static u32 contarColores (ColorOrden* colorOrden, u32 n){
    u32 r = 1;
    for (u32 i = 0; i < n-1; i++){
        if (colorOrden[i].color != colorOrden[i+1].color) r++; 
    }
    return r;
}

static void destruirJedi (JediOrden* jediOrden, u32 r){
    for (u32 i = 0; i < r; i++){
        if (jediOrden[i].indicesVertices != NULL)
            free(jediOrden[i].indicesVertices);
    }
    free(jediOrden);
    jediOrden = NULL;
    return;
}

// Funcion para calcular los valorF de cada color y armar el jediOrden

static JediOrden* calcularValoresF (Grafo G, u32 n, 
                                    u32 r, ColorOrden* colorOrden) {

    u32 valorF = 0;
    JediOrden* jediOrden = malloc(r * sizeof(JediOrden)); 

    //  Si falla al asignar memoria devuelve NULL 
    if (jediOrden == NULL) {
        free(colorOrden);
        return NULL;
    }

    // Contador de los vertices totales del grafo
    u32 j = 0;

    for (u32 i = 0; i < r; i++){
        // Contador de los vertices que comparten un color
        u32 contadorVert = 0;
        valorF = Grado(colorOrden[j].indice, G);

        // Arreglo con los vertices que comparten un color
        u32* iVertices = malloc(sizeof(u32));

        // Si falla al asignar memoria devuelve NULL 
        if (iVertices == NULL){
            free(colorOrden);
            destruirJedi(jediOrden, r);
            return NULL;
        }

        iVertices[contadorVert] =  colorOrden[j].indice;
        contadorVert++;

        while (j < n-1 && colorOrden[j].color == colorOrden[j+1].color){
            j++;
            valorF += Grado(colorOrden[j].indice, G);
            
            // Reasignas la memoria para guardar otro vertice
            iVertices = realloc(iVertices, (contadorVert+1) * sizeof(u32));
            // Si falla al asignar memoria devuelve NULL 
            if (iVertices == NULL){
                free(colorOrden);
                destruirJedi(jediOrden, r);
                return NULL;
            }

            iVertices[contadorVert] =  colorOrden[j].indice;
            contadorVert++;
        }

        valorF *= colorOrden[j].color;
        j++;

        // Asigna al color i del jediOrden su valorF, 
        // los vertices que tienen ese color y la cantidad
        jediOrden[i].valorF = valorF;
        jediOrden[i].indicesVertices = iVertices;
        jediOrden[i].cantidadV = contadorVert;

        iVertices = NULL;
    }
    
    return jediOrden;
}


char OrdenJedi(Grafo G, u32 *Orden, u32 *Color){
    
    u32 n = NumeroDeVertices(G);

    ColorOrden* colorOrden = malloc(n * sizeof(ColorOrden));
    
    if (colorOrden == NULL) {
        return ERROR_ORDEN;
    }
    
    for (u32 i = 0; i < n; i++) {
        colorOrden[i].indice = i;
        colorOrden[i].color = Color[i];
    }

    qsort(colorOrden, n, sizeof(ColorOrden), comparatorOrdenNatural);

    u32 r = contarColores(colorOrden, n);

    JediOrden* jediOrden = calcularValoresF(G, n, r, colorOrden);

    // Si fallo al crear jediorden devuelve error
    if (jediOrden == NULL) return ERROR_ORDEN;

    qsort(jediOrden, r, sizeof(JediOrden), comparatorValorF);

    u32 v = 0;
    for (u32 i = 0; i < r; i++){
        for (u32 j = 0; j < jediOrden[i].cantidadV; j++){
            Orden[v] = jediOrden[i].indicesVertices[j];
            v++;
        }
    }

    free(colorOrden);
    destruirJedi(jediOrden, r);

    return OK_ORDEN;
}
