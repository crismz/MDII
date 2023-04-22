#include "APIParte2.h"
#include "APIG23.h" 
#include <stdio.h>
#include <stdlib.h>

u32 Greedy(Grafo G, u32* Orden, u32* Color)
{
    u32 n = NumeroDeVertices(G);
    u32 color = 0;
    u32 sinColor = Delta(G) + 2;

    for (u32 i=0; i < n; i++) {
        Color[i] = sinColor;
    }

    Color[Orden[0]] = color;
    for (u32 i=1; i<n; i++) {
        u32 grado = Grado(Orden[i], G);
        u32 flag = 1;
        u32 min = 0, aux = 0;
        while (flag) {
            for (u32 j=0; j<grado; j++) {
                if (aux == Color[IndiceVecino(j, i, G)]){
                    aux += 1;
                }
            }
            if (min == aux) flag = 0;
            else min = aux;
        }
        Color[Orden[i]] = min;
        if (min > color) color++;
    }

    return color+1;
}


static int comparator(const void *p, const void *q) 
{
    return ( *(u32*) p - *(u32*) q );
}

int EsPar(u32 n){ return !(n % 2); }

char OrdenImparPar(u32 n, u32* Orden, u32* Color)
{   
    qsort(Color, n, sizeof(u32), comparator);

    return 1;
}

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color){
    return 1;
}