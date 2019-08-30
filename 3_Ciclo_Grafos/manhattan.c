//
//  main.c
//  manhattan
//
//  Created by Paulo Henrique on 19/11/16.
//  Copyright © 2016 Paulo Henrique. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <ncurses.h>

#define tam_x 15
#define tam_y 15
#define tam2_x 5
#define tam2_y 6
#define grande 999999999

int grafo[tam_x][tam_y];
int grafo2[tam2_x][tam2_y];


void imprimir(){
    int i,j;
    printf("\tGrade %d/%d\n",tam_x,tam_y);
    for(i=0; i<tam_x; i++){
        for(j=0;j<tam_x;j++){
            printf("%d\t",grafo[i][j]);
        }
        printf("\n");
    }
}

void imprimir2(){
    int i,j;
    printf("\tGrade %d/%d\n",tam2_x,tam2_y);
    for(i=0; i<tam2_y; i++){
        for(j=0;j<tam2_x;j++){
            printf("%d\t",grafo2[i][j]);
        }
        printf("\n");
    }
}


void imprimir_desenho(){
    int i,j;
    for(i=0; i<tam_x; i++){
        for(j=0;j<tam_x;j++){
            if(grafo[i][j] != -1){
                printf(" ˚\t");
            }
            if(grafo[i][j] == -1){
                printf("[ ]\t");
            }
        }
        printf("\n");
    }
}

void imprimir_desenho2(){
    int i,j;
    for(i=0; i<tam2_y; i++){
        for(j=0;j<tam2_x;j++){
            if(grafo2[i][j] != -1){
                printf(" ˚\t");
            }
            if(grafo2[i][j] == -1){
                printf("[ ]\t");
            }
        }
        printf("\n");
    }
    
}

float calulcar_distancia(int xatual,int yatual,int xfinal,int yfinal,int peso){
    float s1,s2,distancia;
    s1 = pow(xatual - xfinal,2);
    s2 = pow(yatual - yfinal, 2);
    distancia = s1 + s2;
    distancia = sqrtf(distancia);
    distancia = distancia + peso;
    return distancia;
}

float minimo(int a, int b, int c, int d, int e, int f, int g, int h){
    float vet[8], menor;
    int i;
    
    vet[0] = a;
    vet[1] = b;
    vet[2] = c;
    vet[3] = d;
    vet[4] = e;
    vet[5] = f;
    vet[6] = g;
    vet[7] = h;
    
    menor = vet[0];
    
    for(i = 0; i < 8; i++)
        if(vet[i] < menor)
            menor = vet[i];
    
    return menor;
}


int descobrir(int iniciox,int inicioy,int finalx,int finaly, int tamx,int tamy){
    int contx=0,conty=0,contd;
    int x = iniciox,y = inicioy;
    int cont = 0;
    int vetor[8], numero;
    
    
    printf("Aqui\n");
    
    while(cont < tamx + tamy){
        
        if(grafo2[x+1][y+1] != -1 && x < tamx && y < tamy){
            vetor[0] = calulcar_distancia(x+1, y+1, finalx, finaly, 1);
        }
        else if(grafo2[x+1][y-1] != -1 && x < tamx && y < tamy){
            vetor[1] = calulcar_distancia(x+1, y-1, finalx, finaly, 1);
        }
        else if(grafo2[x+1][y] != -1 && x < tamx && y < tamy){
            vetor[2] = calulcar_distancia(x+1, y, finalx, finaly, 1);
        }
        else if(grafo2[x][y+1] != -1 && x < tamx && y < tamy){
            vetor[3] = calulcar_distancia(x, y+1, finalx, finaly, 1);
        }
        else if(grafo2[x][y-1] != -1 && x < tamx && y < tamy){
            vetor[4] = calulcar_distancia(x, y-1, finalx, finaly, 1);
        }
        else if(grafo2[x-1][y+1] != -1 && x < tamx && y < tamy){
            vetor[5] = calulcar_distancia(x-1, y+1, finalx, finaly, 1);
        }
        else if(grafo2[x-1][y] != -1 && x < tamx && y < tamy){
            vetor[6] = calulcar_distancia(x-1, y, finalx, finaly, 1);
        }
        else if(grafo2[x-1][y-1] != -1 && x < tamx && y < tamy){
            vetor[7] = calulcar_distancia(x-1, y-1, finalx, finaly, 1);
        }
        
        numero = minimo(vetor[0], vetor[1], vetor[2], vetor[3], vetor[4], vetor[5], vetor[6], vetor[7]);
        
        if(numero == vetor[0]){
            grafo2[x][y] = 10;
            x = x+1;
            y = y+1;
        }
        if(numero == vetor[1]){
            grafo2[x][y] = 10;
            x = x+1;
            y = y-1;
        }
        if(numero == vetor[2]){
            grafo2[x][y] = 10;
            x = x+1;
        }
        if(numero == vetor[3]){
            grafo2[x][y] = 10;
            y = y+1;
        }
        if(numero == vetor[4]){
            grafo2[x][y] = 10;
            y = y-1;
        }
        if(numero == vetor[5]){
            grafo2[x][y] = 10;
            x = x-1;
            y = y+1;
        }
        if(numero == vetor[6]){
            grafo2[x][y] = 10;
            x = x-1;
        }
        if(numero == vetor[7]){
            grafo2[x][y] = 10;
            x = x-1;
            y = y-1;
        }

        cont++;
    }
    
    
        return 0;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao,x,y,cont=0;
    int iniciox, inicioy, finalx,finaly;
    
    //printf("Digite:\n1 - Grafo Pré-Pronto 1\n2 - Grafo Pré-Pronto 2\n3 - Inserir Grafo\n0 - Sair\n");
    //scanf("%d",&opcao);
    opcao = 2;
    switch (opcao) {
        case 1:
            iniciox = 0;
            inicioy = 0;
            finalx = 15;
            finaly = 15;
            int contxx=0,contyy=0;
            printf("\n\n");
            
            for (y=0; y<tam_y; y++,cont++){
                //printf("%d\t",cont+1);
                for(x=0; x<tam_x; x++){
                    if(y == 3 && x == 6){
                        grafo[y][x] = -1;
                    }
                    if(y == 1 && x == 10){
                        grafo[y][x] = -1;
                    }
                    if(y == 1 && x == 11){
                        grafo[y][x] = -1;
                    }
                    if(y == 1 && x == 12){
                        grafo[y][x] = -1;
                    }
                    if(y == 2 && x == 12){
                        grafo[y][x] = -1;
                    }
                    if(y == 2 && x == 13){
                        grafo[y][x] = -1;
                    }
                    if(y == 3 && x == 11){
                        grafo[y][x] = -1;
                    }
                    if(y == 7 && x == 4){
                        grafo[y][x] = -1;
                    }
                    if(y == 7 && x == 5){
                        grafo[y][x] = -1;
                    }
                    if(y == 6 && x == 13){
                        grafo[y][x] = -1;
                    }
                    if(y == 6 && x == 12){
                        grafo[y][x] = -1;
                    }
                    if(y == 7 && x == 13){
                        grafo[y][x] = -1;
                    }
                    if(y == 7 && x == 12){
                        grafo[y][x] = -1;
                    }
                    if(y == 12 && x == 1){
                        grafo[y][x] = -1;
                    }
                    if(y == 13 && x == 1){
                        grafo[y][x] = -1;
                    }
                    if(y == 13 && x == 2){
                        grafo[y][x] = -1;
                    }
                    if(y == 12 && x == 7){
                        grafo[y][x] = -1;
                    }
                    if(y == 12 && x == 13){
                        grafo[y][x] = -1;
                    }
                    
                }
            }
            
            for (y=0; y<tam_y; y++,contyy++){
                for(x=0; x<tam_x; x++,contxx++){
                    if(grafo[y][x] != -1){
                        if(grafo[y][x] < contxx + contyy)
                            grafo[y][x] = contxx + contyy;
                    }
                    
                }
                contxx = 0;
            }
            
            
            for (y=0; y<tam2_y; y++,contyy++){
                for(x=0; x<tam2_x; x++,contxx++){
                    if(x == y && grafo[y][x] != -1)
                        if(grafo[y][x] < contxx + contyy)
                            grafo[y][x] = contxx;
                    
                    if(x == y && grafo[y-1][x-1] == -1)
                        grafo[y][x] = contxx*2;
                    
                }
                contxx = 0;
            }
            
            
            
            
            imprimir();
            printf("\n\n");
            //imprimir_desenho();
            
            printf("\n\n");
            
            break;
            
        case 2:
            iniciox = 0;
            inicioy = 0;
            finalx = 4;
            finaly = 5;
            
            printf("\n\n");
            for (y=0; y<tam2_y; y++){
                for(x=0; x<tam2_x; x++){
                    if(y == 2 && x == 1){
                        grafo2[y][x] = -1;
                    }
                    if(y == 3 && x == 1){
                        grafo2[y][x] = -1;
                    }
                    if(y == 3 && x == 3){
                        grafo2[y][x] = -1;
                    }
                    if(y == 4 && x == 3){
                        grafo2[y][x] = -1;
                    }
                    
                }
            }
            
            
            
            /*
            for (y=0; y<tam2_y; y++,conty++){
                for(x=0; x<tam2_x; x++,contx++){
                    if(x == 0)
                        if(grafo2[y][x] != -1){
                            if(grafo2[y][x] < contx + conty)
                                grafo2[y][x] = conty + contx;
                        }
                    
                    if(grafo2[y][x] == -1)
                        grafo2[y+1][x+1] = conty + contx;
                    
                    
                    if(grafo2[y][x] != -1)
                        if(grafo2[y-1][x-1] < contx + conty)
                            grafo2[y][x] = grafo2[y][x] + contx;
                    
                }
                contx = 0;
            }*/
       
            //grafo2[partida_y][partida_x] = 10;
            int geral;
            imprimir2();
            
            geral = descobrir(iniciox,inicioy,finalx,finaly,tam2_x,tam2_y);
            printf("Total de passos: %d\n",geral);
            printf("\n\n");
            //imprimir_desenho2();
            printf("\n\n");
            break;
    }
    
}


