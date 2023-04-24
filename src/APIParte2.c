#include "APIParte2.h"
#include "APIG23.h" 
#include <stdio.h>
#include <stdlib.h>

#define ERROR_NUM (u32) 4294967295

typedef struct ColorOrden {
    u32 color;
    u32 indice;
} ColorOrden;

typedef struct JediOrden {
    u32 valorF;
    u32* indicesVertices;
    u32 cantidadV;
} JediOrden;

u32 primerColorDisponible(u32* arr, u32 n){

    int estaCero = 0;
    int estaUno = 0;

    for (u32 i=0; i < n; i++){
        if (arr[i] == 0){
            estaCero = 1;
            break;
        } 
    }

    // Si cero esta disponible
    if(estaCero == 0) return 0;
    
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

        if (colorVecinos == NULL) return ERROR_NUM;

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
        return '0';
    }

    for (u32 i=0; i<n; i++){
        colorOrden[i].indice = i;
        colorOrden[i].color = Color[i];
    }

    qsort(colorOrden, n, sizeof(colorOrden), comparatorImparPar);

    for (u32 i=0; i<n; i++){
        Orden[i] = colorOrden[i].indice;
    }

    free(colorOrden);
    return '0';
}

static int comparatorOrdenNatural(const void *p, const void *q){
    ColorOrden* a = (ColorOrden*) p;
    ColorOrden* b = (ColorOrden*) q;

    if (a->color < b->color) return -1;
    return 1;
}

static int comparatorValorF(const void *p, const void *q){
    JediOrden* a = (JediOrden*) p;
    JediOrden* b = (JediOrden*) q;

    if (a->valorF > b->valorF) return -1;
    return 1;
}

static u32 contarColores (ColorOrden* colorOrden, u32 n){
    u32 r = 1;
    for(u32 i = 0; i < n-1; i++){
        if(colorOrden[i].color != colorOrden[i+1].color) r++; 
    }
    return r;
}

static void destruirJedi (JediOrden* jediOrden, u32 r){
    for (u32 i = 0; i < r; i++){
        if(jediOrden[i].indicesVertices != NULL)
            free(jediOrden[i].indicesVertices);
    }
    free(jediOrden);
    jediOrden = NULL;
    return;
}

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color){
    
    u32 n = NumeroDeVertices(G);
    u32 sumF = 0;

    ColorOrden* colorOrden = malloc(n * sizeof(ColorOrden));
    
    if (colorOrden == NULL) {
        return '1';
    }
    
    for(u32 i=0; i < n; i++) {
        colorOrden[i].indice = i;
        colorOrden[i].color = Color[i];
    }

    qsort(colorOrden, n, sizeof(ColorOrden), comparatorOrdenNatural);

    u32 r = contarColores(colorOrden, n);

    JediOrden* jediOrden = malloc(r * sizeof(JediOrden)); 

    if (jediOrden == NULL) {
        free(colorOrden);
        return '1';
    }

    u32 j = 0;

    for (u32 i = 0; i < r; i++){
        u32 contadorV = 0;
        sumF = Grado(colorOrden[j].indice, G);

        u32* iVertices = malloc(sizeof(u32));
        if(iVertices == NULL){
            free(colorOrden);
            destruirJedi(jediOrden, r);
        }

        iVertices[contadorV] =  colorOrden[j].indice;
        contadorV++;

        while (colorOrden[j].color == colorOrden[j+1].color){
            j++;
            sumF += Grado(colorOrden[j].indice, G);
            
            iVertices = realloc(iVertices, (contadorV+1) * sizeof(u32));
            if(iVertices == NULL){
                free(colorOrden);
                destruirJedi(jediOrden, r);
                return '1';
            }

            iVertices[contadorV] =  colorOrden[j].indice;
            contadorV++;
            
            if(j == n-1) break;
        }

        sumF *= colorOrden[j].color;
        j++;

        jediOrden[i].valorF = sumF;
        jediOrden[i].indicesVertices = iVertices;
        jediOrden[i].cantidadV = contadorV;

        iVertices = NULL;
    }


    qsort(jediOrden, r, sizeof(JediOrden), comparatorValorF);


    u32 v = 0;
    for (u32 i=0; i<r; i++){
        for(u32 j = 0; j < jediOrden[i].cantidadV; j++){
            Orden[v] = jediOrden[i].indicesVertices[j];
            v++;
        }
    }


    free(colorOrden);
    destruirJedi(jediOrden, r);

    return '0';
}