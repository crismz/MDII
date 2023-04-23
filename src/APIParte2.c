#include "APIParte2.h"
#include "APIG23.h" 
#include <stdio.h>
#include <stdlib.h>

typedef struct ColorOrden {
    u32 color;
    u32 indice;
} ColorOrden;

u32 primerColorDisponible(u32* arr, u32 n){

    int estaCero = 0;
    
    for (u32 i=0; i < n; i++){
        if (arr[i] == 0){
            estaCero = 1;
            break;
        } 
    }

    // Si cero esta disponible
    if(estaCero == 0) return 0;

    int estaUno = 0;
    
    for (u32 i=0; i < n; i++){
        if (arr[i] == 1){
            estaUno = 1;
            break;
        } 
    }

    // Si uno esta disponible
    if(estaUno == 0) return 1;

    // Cambiando valores que no sirven a 1
    for (u32 i = 0; i < n; i++){
        if (arr[i] == 0 ||arr[i] > n) 
            arr[i] = 1;
    }

    // Se actualizan los indices de acuerdo a los valores
    for (u32 i = 0; i < n; i++){
        arr[(arr[i] - 1) % n] += n;
    }
    

    // Encontrar el indice con valor menor a n
    for (u32 i = 0; i < n; i++){
        if (arr[i] <= n)
            return i + 1;
    }
    
    // Si el arreglo tiene los colores 0 a n-1
    return n + 1;
}


u32 Greedy(Grafo G, u32* Orden, u32* Color)
{
    u32 n = NumeroDeVertices(G);
    u32 color = 0;
    u32 numCrom = 0;
    u32 sinColor = Delta(G) + 2;
    
    for (u32 i=0; i < n; i++) {
        Color[i] = sinColor;
    }

    Color[Orden[0]] = color;

    for (u32 i=1; i<n; i++) { 
        u32 grado = Grado(Orden[i], G);
        u32* colorVecinos = malloc(sizeof(u32) * grado);

        for(u32 j=0; j<grado; j++){
            colorVecinos[j] =  Color[IndiceVecino(j, Orden[i], G)];
        }


        color = primerColorDisponible(colorVecinos, grado);
        
        Color[Orden[i]] = color;

        free(colorVecinos);

        if(color > numCrom) numCrom++;
    }

    numCrom++;
    return numCrom;
}


static int EsPar(u32 n){ return !(n % 2); }

static int auxComparator(u32 a, u32 b)
{
    if (a > b) return -1;
    return 1;
}

static int comparator(const void *p, const void *q) 
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
    ColorOrden* ColorStruct = malloc(n * sizeof(ColorOrden));
    
    if (ColorStruct == NULL) {
        free(ColorStruct);    
        return (char) 1;
    }

    for (u32 i=0; i<n; i++){
        ColorStruct[i].indice = i;
        ColorStruct[i].color = Color[i];
    }

    qsort(ColorStruct, n, sizeof(ColorStruct), comparator);

    for (u32 i=0; i<n; i++){
        Orden[i] = ColorStruct[i].indice;
    }

    free(ColorStruct);
    return (char) 0;
}

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color){
    


    return 1;
}

/*
orden = [1,0,2,3]
color = [3,5,4,6] -> [6,5,4,3] 
      = [0,1,2,3]  


*/
