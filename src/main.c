#include "APIG23.h"

int main ()
{
    char a[1024];
    int n = 0;
    int m = 0;
    char p;
    char edge[5];

    while(fgets(a,1024,stdin) != NULL){
        printf("\n %s",a);
        if(a[0] == 'p'){
            sscanf(a, "%c %s %d %d",&p, edge, &n,&m);
            printf("\n\n\n %d %d \n\n\n",n,m);
        }
    }


    //Grafo G = ConstruirGrafo();
    return 0;
}
