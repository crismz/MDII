#include "APIG23.h"
#include "APIParte2.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_NUM (u32) 4294967295

void debugGrafo(Grafo g){
    printf("numvertices %u\n",g->num_vertices);
    printf("numlados %u\n",g->num_lados);
    printf("delta %u \n",g->delta);

    for(u32 i = 31; i < 51; i++){
        printf("Vertice %u : Vecino nro %u es %u\n", Nombre(0,g), i ,IndiceVecino(i, 0, g));
    }
}


int main (){

    Grafo g = ConstruirGrafo();
    u32 n;
    n = NumeroDeVertices(g);
    u32* Orden = malloc(n*sizeof(u32));
    u32* Color1 = malloc(n*sizeof(u32));
    u32* Color2 = malloc(n*sizeof(u32));
    char error;

    for (u32 i=0; i<n; i++){
        Orden[i] = i;
    }
    
    Greedy(g, Orden, Color1);
    Greedy(g, Orden, Color2);


    u32 contador = 0;
    int flag = 0;
    u32 numC1 = 0;
    u32 numC2 = 0;


    for(u32 i=0; i < 500; i++){
        if(contador % 16 == 0) flag = flag ? 0 : 1; 
        if (flag){
            error = OrdenImparPar(n, Orden, Color1);

            if(error == '1') {
                printf("Error en alocacion de memoria");
                break;
            }
            
            numC1 = Greedy(g, Orden, Color1);

            if(numC1 == ERROR_NUM) {
                printf("Error en alocacion de memoria");
                break;
            }

            error = OrdenJedi(g, Orden, Color2);
            
            if(error == '1') {
                printf("Error en alocacion de memoria");
                break;
            }

            numC2 = Greedy(g, Orden, Color2);
            
            if(numC2 == ERROR_NUM) {
                printf("Error en alocacion de memoria");
                break;
            }
        }
        else {
            error = OrdenImparPar(n, Orden, Color2);

            if(error == '1') {
                printf("Error en alocacion de memoria");
                break;
            }
            
            numC2 = Greedy(g, Orden, Color2);
            if(numC2 == ERROR_NUM) {
                printf("Error en alocacion de memoria");
                break;
            }

            error = OrdenJedi(g, Orden, Color1);
            
            if(error == '1') {
                printf("Error en alocacion de memoria");
                break;
            }
            numC1 = Greedy(g, Orden, Color1);
            
            if(numC1 == ERROR_NUM) {
                printf("Error en alocacion de memoria");
                break;
            }
        }
        contador++;
    }

    printf("X1 = %u, X2 = %u", numC1, numC2);

    DestruirGrafo(g);
    free(Orden);
    free(Color1);
    free(Color2);

    return 0;
}
