/*
*Programmer: Carlos Negri (UFRGS - 00333174)
*Language: C/C++
*Subject: Física(IC)
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "data.h"


void calculaForcas(PARTICULA particulas[], CONSTANTES constantes){                 

    VECTOR d;
    VECTOR f;

    //LENNARD============================================================================             
    double cutwca = pow(2.0, 1.0/6.0);
    int i, j;
    //unsigned int set = 0;
    double dist;
    double cfive;
    //===================================================================================

    //ELETROESTATICA=====================================================================
    double pfel;
    double cadm =  (10.0*constantes.raioMaximo) / constantes.raioMaximo;              //constante força eletroestatica - adimensionalizadora
    //===================================================================================

    //double Lx = 2 * constantes.raioEsfera;
    //double Ly = 2 * constantes.raioEsfera;
    //double Lz = 2 * constantes.raioEsfera;
    
    //zera forcas
    for(i = 0; i< constantes.particulaMax; i++){
        particulas[i].forcas.x = 0.0;
        particulas[i].forcas.y = 0.0;
        particulas[i].forcas.z = 0.0;
    }



    for(i = 0; i < constantes.particulaMax; ++i){
        for(j = i + 1; j < constantes.particulaMax; ++j){
            d.x = particulas[i].posicao.x - particulas[j].posicao.x; 
            //d.x = d.x - round(d.x/Lx * Lx);                                   

            d.y = particulas[i].posicao.y - particulas[j].posicao.y; 
            //d.y = d.y - round(d.y/Ly * Ly);                                   

            d.z = particulas[i].posicao.z - particulas[j].posicao.z; 
            //d.z = d.z - round(d.z/Lz * Lz);                                   


            dist = distCalc(d.x, d.y, d.z); 

            //LENNARD==============================================================================
            cfive = 0.0;
            if(dist < cutwca){
                cfive = 5.0 * (-6.0 / pow(dist, 7) + 12.0 / pow(dist, 13));

                if(dist <= 0.8){
                    cfive = 5.0 * (-6.0 / pow(0.8, 7) + 12.0 / pow(0.8, 13));
                }
            }

            
            f.x += cfive*d.x/dist;
            f.y += cfive*d.y/dist;
            f.z += cfive*d.z/dist;


            //ELETROESTATICA=======================================================================
            pfel = cadm * (particulas[i].carga * particulas[j].carga) / pow(dist, 3);       // parametro da força eletrostática

            f.x += pfel * d.x;
            f.y += pfel * d.y;
            f.z += pfel * d.z;


            //SOMA DAS FORCAS======================================================================

            particulas[i].forcas.x += f.x;            
            particulas[i].forcas.y += f.y;
            particulas[i].forcas.z += f.z;
            
            
            particulas[j].forcas.x += -f.x;       
            particulas[j].forcas.y += -f.y;
            particulas[j].forcas.z += -f.z; 


            f = zeraVector(f);
        }
    }
}

VECTOR zeraVector(VECTOR forca){
    forca.x = 0;
    forca.y = 0;
    forca.z = 0;

    return forca;
}