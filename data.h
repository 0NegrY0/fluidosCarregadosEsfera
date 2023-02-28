/*
*Programmer: Carlos Negri (UFRGS - 00333174)
*Language: C/C++
*Subject: Física(IC)
*/

typedef struct str_vector{
    double x;
    double y;
    double z;
}VECTOR;

typedef struct str_particula{
    VECTOR posicao;
    VECTOR forcas;
    VECTOR vel;
    VECTOR gaussian;
    char Elemento[2];
    double raio;
    int carga;
    int id;
}PARTICULA;

typedef struct str_constantes{
    double raioEsfera;
    int particulaMax;
    double raioMaximo;
    double coefFric;
    double lambB;
    double time;
    double endTime;
}CONSTANTES;

double numeroAleatorio(double min, double max);

void colocaParticula(PARTICULA particulas[], CONSTANTES constantes);

int imprimeArquivo(PARTICULA particulas[], int colocados);

void movement(PARTICULA particulas[], CONSTANTES constantes);

double gausran();   

double distCalc(double x, double y, double z);

void calculaForcas(PARTICULA particulas[], CONSTANTES constantes);

VECTOR zeraVector(VECTOR forca);