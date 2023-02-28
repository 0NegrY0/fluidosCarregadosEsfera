/*
*Programmer: Carlos Negri (UFRGS - 00333174)
*Language: C/C++
*Subject: Física(IC)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"

//PARTICULAS
const int PARTICULA_MAX = 101;              //ESFERA CENTRAL
const double RAIO_PARTICULA = 0.5;
const double RAIO_ESFERA = 16.0 * RAIO_PARTICULA;
const double COEF_FRIC = 0.1;
const double LAMB_B =  14.0 * RAIO_PARTICULA;
const double TIME = 0.005;
const double END_TIME = 30.0;






int main(){

    int i;

    //INICIACAO DAS PARTICULAS

    PARTICULA particulas[PARTICULA_MAX];
    CONSTANTES constantes;

    //DEFININDO OS VALORES INICIAIS PARA AS PARTICULAS
    for(i = 0; i < PARTICULA_MAX; i++){
        particulas[i].raio = 0.05;
        //particulas[i].carga = 0;
        particulas[i].posicao.x = 0;
        particulas[i].posicao.y = 0;
        particulas[i].posicao.z = 0;
        particulas[i].vel.x = 0;
        particulas[i].vel.y = 0;
        particulas[i].vel.z = 0;
        particulas[i].forcas.x = 0;
        particulas[i].forcas.y = 0;
        particulas[i].forcas.z = 0;
        particulas[i].id = i;

        if (i = 0){
            particulas[i].carga = 0;                //MUDAR
            particulas[i].Elemento[0] = 'C';
            particulas[i].Elemento[1] = 'u';
        }
        else if(i < PARTICULA_MAX/2){
            particulas[i].carga = +1;
            particulas[i].Elemento[0] = 'N';
            particulas[i].Elemento[1] = 'a';
        }

        else{
            particulas[i].carga = -1;
            particulas[i].Elemento[0] = 'C';
            particulas[i].Elemento[1] = 'l';
        }
    }



    //DEFININDO AS CONSTANTES USANDAS NO PROGRAMA
    constantes.particulaMax = PARTICULA_MAX;
    constantes.raioEsfera = RAIO_ESFERA;
    constantes.raioMaximo = RAIO_PARTICULA;
    constantes.coefFric = COEF_FRIC;
    constantes.endTime = END_TIME;
    constantes.lambB = LAMB_B;
    constantes.time = TIME;
    
    
    //CRIA PARTICULAS
    srand(time(NULL));      //seed

    colocaParticula(particulas, constantes);

    

    imprimeArquivo(particulas, PARTICULA_MAX);

    movement(particulas, constantes);

    return 0;
}
