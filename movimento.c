/*
*Programmer: Carlos Negri (UFRGS - 00333174)
*Language: C/C++
*Subject: Física(IC)
*/

#include "data.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

const double FRIC = 0.1;
const double DT = 0.005;
const double TF = 53.0;

const int CHECKPOINT = 10;


void movement(PARTICULA particulas[], CONSTANTES constantes){

    double Con, Co, Cone, Ctwo;
    double desv_r;
    double desv_v;
    double Cvv, CvvTwo;
    
    double raioRelativo;
    double DT2 = pow(DT, 2);

    int i;

    VECTOR old;
    //VECTOR Fold[constantes.particulaMax];             //NAO USADO
    
    //FILE *arq;

    FILE *arqAnim;

    arqAnim = fopen("animation.txt", "w");          //Usando para criar o arquivo de animação


    //char nome[25];

    //int numArq = 0;
    int iteracao = 0;

	
    //QUERO NEM OLHAR PRA ESSA BAGUNÇA
    Con = FRIC * DT;
    Co = exp(-(Con));
    Cone = ((1 - Co) / Con);
    Ctwo = ((1 - Cone) / Con);
    desv_r = DT*sqrt((1/Con) * (2 - ((1/Con) * (3 - (4*Co) + (Co*Co)))));

    desv_v = sqrt(1 - pow(Co, 2));
    Cvv = (DT / Con / desv_v / desv_r) * (1 - Co) * (1 - Co);
    CvvTwo = sqrt(1 - pow(Cvv, 2));

    raioRelativo = constantes.raioEsfera - constantes.raioMaximo/2.0;


    for(double t = 0; t <= TF; t += DT){

        calculaForcas(particulas, constantes);     

        //LOOP POSICAO
        for(i = 0; i < constantes.particulaMax; ++i){
            old.x = particulas[i].posicao.x;
            old.y = particulas[i].posicao.y;
            old.z = particulas[i].posicao.z;

            particulas[i].gaussian.x = gausran();             
            particulas[i].gaussian.y = gausran();
            particulas[i].gaussian.z = gausran();


            particulas[i].posicao.x += Cone * DT * particulas[i].vel.x + Ctwo * DT2 * particulas[i].forcas.x + particulas[i].gaussian.x * desv_r;              //INICIAR F    
            particulas[i].posicao.y += Cone * DT * particulas[i].vel.y + Ctwo * DT2 * particulas[i].forcas.y + particulas[i].gaussian.y * desv_r;              //INICIAR F
            particulas[i].posicao.z += Cone * DT * particulas[i].vel.z + Ctwo * DT2 * particulas[i].forcas.z + particulas[i].gaussian.z * desv_r;              //INICIAR F



            /*if(fabs(particulas[i].posicao.x) > constantes.raioEsfera){                        //modelo antigo
                particulas[i].vel.x = - particulas[i].vel.x;
                particulas[i].posicao.x = old.x;
            }
             if(fabs(particulas[i].posicao.y) > constantes.raioEsfera){
                particulas[i].vel.y = - particulas[i].vel.y;
                particulas[i].posicao.y = old.y;
            }
             if(fabs(particulas[i].posicao.z) > constantes.raioEsfera){
                particulas[i].vel.z = - particulas[i].vel.z;
                particulas[i].posicao.z = old.z;
            }*/

            if(distCalc(particulas[i].posicao.x, particulas[i].posicao.y, particulas[i].posicao.z) >= raioRelativo){
                particulas[i].vel.x *= -1.0;
                particulas[i].vel.y *= -1.0;
                particulas[i].vel.z *= -1.0;

                //retornando a posicao antiga
                particulas[i].posicao.x = old.x;
                particulas[i].posicao.y = old.y;
                particulas[i].posicao.z = old.z;
            }
        }


        calculaForcas(particulas, constantes);     
        
        //LOOP VELOCIDADE
        for(i = 0; i < constantes.particulaMax; ++i){
            particulas[i].vel.x = Co * particulas[i].vel.x + (Cone - Ctwo) * DT * particulas[i].forcas.x + Ctwo * DT * particulas[i].forcas.x + desv_v * (Cvv * particulas[i].gaussian.x + CvvTwo * gausran());                 //era Fold no lugar do primeiro lennard
            particulas[i].vel.y = Co * particulas[i].vel.y + (Cone - Ctwo) * DT * particulas[i].forcas.y + Ctwo * DT * particulas[i].forcas.y + desv_v * (Cvv * particulas[i].gaussian.y + CvvTwo * gausran());
            particulas[i].vel.z = Co * particulas[i].vel.z + (Cone - Ctwo) * DT * particulas[i].forcas.z + Ctwo * DT * particulas[i].forcas.z + desv_v * (Cvv * particulas[i].gaussian.z + CvvTwo * gausran());

        //    Fold[i].x = particulas[i].forcas.x;
        //    Fold[i].y = particulas[i].forcas.y;
        //    Fold[i].z = particulas[i].forcas.z;

        }
    

        //BINARIO
        /*if(iteracao == 100){
            sprintf(nome, "mov%d.bin",numArq);
            arq = fopen(nome, "wb");
            fwrite(particulas, sizeof(PARTICULA), constantes.particulaMax, arq);
            fclose(arq);
            numArq++;
            iteracao = 0;
            
            for(i = 0; i < constantes.particulaMax; i++){                                                                                              //DEBUG
            printf("particula %d    X: %lf      Y: %lf      Z: %lf      Carga: %d       Raio: %lf\n", 
                i, particulas[i].posicao.x, particulas[i].posicao.y, particulas[i].posicao.z, particulas[i].carga, particulas[i].raio);
            }
        }

        else {
            iteracao++;
        }*/

        //ANIMACAO

        /*if(iteracao >= 10000){
            sprintf(nome, "mov_anim%d.txt",numArq);
            arq = fopen(nome, "w");
            fprintf(arq, "%d\n\n", constantes.particulaMax);

            for(i = 0; i < constantes.particulaMax; i++){
                if(i < constantes.particulaMax/2){
                    fprintf(arq, "Na ");
                }

                else{
                    fprintf(arq, "Cl ");
                }

                fprintf(arq, "%lf %lf %lf\n", particulas[i].posicao.x, particulas[i].posicao.y, particulas[i].posicao.z);
            }

            fprintf(arq, "\n");
            fclose(arq);
            numArq++;
            iteracao = 9990;
        }
        else{
            iteracao++;
        }*/

        //ARQUIVO UNICO

        if(iteracao >= 10000){
            fprintf(arqAnim, "%d\n\n", constantes.particulaMax);

            for(i = 0; i < constantes.particulaMax; i++){
                if(i < constantes.particulaMax/2){
                    fprintf(arqAnim, "Na ");
                }

                else{
                    fprintf(arqAnim, "Cl ");
                }

                fprintf(arqAnim, "%lf %lf %lf\n", particulas[i].posicao.x, particulas[i].posicao.y, particulas[i].posicao.z);
            }

            fprintf(arqAnim, "\n");
            iteracao = 9990;
        }
        else{
            iteracao++;
        }
    }
}