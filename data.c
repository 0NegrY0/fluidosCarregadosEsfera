/*
*Programmer: Carlos Negri (UFRGS - 00333174)
*Language: C/C++
*Subject: Física(IC)
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "data.h"


double numeroAleatorio(double min, double max){
    double random = ((double) rand()) / RAND_MAX; 
    double range = (max - min) * random;           
    double number = min + range;                   
    return number;
}


void colocaParticula(PARTICULA particulas[], CONSTANTES constantes){
    int i = 0;      //particulas colocadas
    int j;
    double raioRelativo = constantes.raioEsfera - constantes.raioMaximo;

    bool particulaInserida = false;
    double distParcial = 0;

    VECTOR testePos;            //usada no teste com a esfera
    VECTOR distTestPos;         //usada no teste com as outras particulas

    //particulas[0].posicao.x = numeroAleatorio(-raioRelativo/2.0, raioRelativo/2.0);
    //particulas[0].posicao.y = numeroAleatorio(-raioRelativo/2.0, raioRelativo/2.0);
    //particulas[0].posicao.z = numeroAleatorio(-raioRelativo/2.0, raioRelativo/2.0);

    particulas[0].posicao.x = 0.0;
    particulas[0].posicao.y = 0.0;
    particulas[0].posicao.z = 0.0;

    while(i < constantes.particulaMax){
        do{
            testePos.x = numeroAleatorio(-raioRelativo, raioRelativo);
            testePos.y = numeroAleatorio(-raioRelativo, raioRelativo);
            testePos.z = numeroAleatorio(-raioRelativo, raioRelativo);

            //teste com outras particulas

            for(j = i; j >=0; j--){
                distTestPos.x = testePos.x - particulas[j].posicao.x;
                distTestPos.y = testePos.y - particulas[j].posicao.y;
                distTestPos.z = testePos.z - particulas[j].posicao.z;

                distParcial = distCalc(distTestPos.x, distTestPos.y, distTestPos.z);

                if(distParcial <= 2*constantes.raioMaximo){
                    particulaInserida = false;
                }
                else{
                    particulaInserida = true;
                }
            }
        }while(particulaInserida);


        //salvando distancia como definitiva e testando se esta dentro da esfera
        if (distCalc(testePos.x, testePos.y, testePos.z) < raioRelativo){
            i++;
            particulas[i].posicao.x = testePos.x;
            particulas[i].posicao.y = testePos.y;
            particulas[i].posicao.z = testePos.z;
        }
    }
}


int imprimeArquivo(PARTICULA particulas[], int colocados){
    FILE *arq;
    int i;

    arq = fopen("saida.txt", "w");
    
    if(arq == NULL){
        return 1;               //erro na abertura (ERRO 1)
    }
    
    else{
        fprintf(arq, "%d", colocados);
        fprintf(arq, "%s", "\n\n");

        for(i = 0; i < round(colocados/2.0); i++){
            fprintf(arq, "%s %lf %lf %lf %s", "Na", particulas[i].posicao.x, particulas[i].posicao.y, particulas[i].posicao.z, "\n");
        }
        for(i = round(colocados/2.0); i<colocados; i++){
            fprintf(arq, "%s %lf %lf %lf %s", "Cl", particulas[i].posicao.x, particulas[i].posicao.y, particulas[i].posicao.z, "\n");
        }
        return 0;
    }
}


// generate gaussian random_numbers
double gausran(){
    // generate gaussianrandom_numbers                                                                   
    double ran1,ran2,PI,R1,R2,res;
    ran1 = (double)rand()/RAND_MAX;
    ran2 = (double)rand()/RAND_MAX;
    PI   = 4.0*atan(1.0);
    R1   = -log(1.0-ran1);
    R2   = 2.0*PI*ran2;
    R1   = sqrt(2.0*R1);
    res  = R1*cos(R2);
    return res;
}


double distCalc(double x, double y, double z){
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}



VECTOR zeraVector(VECTOR forca){
    forca.x = 0;
    forca.y = 0;
    forca.z = 0;

    return forca;
}