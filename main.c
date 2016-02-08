#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef _header_heroi _header_mapa _header_tuto

    #define _header_heroi
    #include "headers_mapa/header_heroi.h"

    #define _header_mapa
    #include "headers_mapa/header_mapa.h"

    #define _header_tuto
    #include "headers_mapa/header_tutorial.h"
#endif

MapaPacMan mapasPacMan;
Posicao posicaoHeroi;
Heroi packman;

void marcaPontos(int x,int y){

            /// ver se o pac consegue pontos
             if((mapasPacMan.mapa[y][x+1]=='*')){
                packman.pontos +=10;
                atualizaMapa(&mapasPacMan,x+1,y);
                tiraFrutaMapa(&mapasPacMan);
            }

            if((mapasPacMan.mapa[y][x-1]=='*')){
                packman.pontos +=10;
                atualizaMapa(&mapasPacMan,x-1,y);
                tiraFrutaMapa(&mapasPacMan);
            }

            if((mapasPacMan.mapa[y-1][x]=='*')){
                packman.pontos +=10;
                atualizaMapa(&mapasPacMan,x,y-1);
                tiraFrutaMapa(&mapasPacMan);
            }

            if((mapasPacMan.mapa[y+1][x]=='*')){
                packman.pontos +=10;
                atualizaMapa(&mapasPacMan,x,y+1);
                tiraFrutaMapa(&mapasPacMan);
            }
}

void switchMovimentacao(char tecla, int x, int y){

        switch(tecla){

        case ESQUERDA:
            if(podeAndar(&mapasPacMan,posicaoHeroi.x-1,posicaoHeroi.y)){

                mapasPacMan.mapa[y][x-1] = HEROI;
                posicaoHeroi.x = x-1;

            }else return;

            break;

        case PRACIMA:
            if(podeAndar(&mapasPacMan,posicaoHeroi.x,posicaoHeroi.y-1)){

                mapasPacMan.mapa[y-1][x] = HEROI;
                posicaoHeroi.y = y-1;

            }else return;

            break;

        case PRABAIXO:
            if(podeAndar(&mapasPacMan,posicaoHeroi.x,posicaoHeroi.y+1)){

                mapasPacMan.mapa[y+1][x] = HEROI;
                posicaoHeroi.y = y+1;

            }else return;

            break;

        case DIREITA:
            if(podeAndar(&mapasPacMan,posicaoHeroi.x+1,posicaoHeroi.y)){

                mapasPacMan.mapa[y][x+1] = HEROI;
                posicaoHeroi.x = x+1;

            }else return;

            break;

        // movimento que não existe, não faça nada
        default:return;
    }

    atualizaMapa(&mapasPacMan,x,y);
    tiraVidas(&packman,&mapasPacMan,x,y);
    marcaPontos(x,y);
}

void moveFantasma(){

    int yFantasma;
    int xFantasma;
    int flag=0,i,j;
    srand(time(0));
    int ondeFantasmaApareceNaProxima = rand() % 9;

     for(i=0;i<mapasPacMan.linhas;i++){

        for(j=0;j<mapasPacMan.colunas && flag != 1;j++){

            if(mapasPacMan.mapa[i][j]==FANTASMA){

                xFantasma = j;
                yFantasma = i;

                if(podeAndar(&mapasPacMan,xFantasma+ondeFantasmaApareceNaProxima,yFantasma)){ // tenta a direita

                    mapasPacMan.mapa[yFantasma][xFantasma+ondeFantasmaApareceNaProxima] = FANTASMA;
                    atualizaMapa(&mapasPacMan,xFantasma,yFantasma);
                }else{

                    if(podeAndar(&mapasPacMan,xFantasma-ondeFantasmaApareceNaProxima,yFantasma)){ // tenta a esquerda

                        mapasPacMan.mapa[yFantasma][xFantasma-ondeFantasmaApareceNaProxima] = FANTASMA;
                        atualizaMapa(&mapasPacMan,xFantasma,yFantasma);
                    }
                }

                flag = 1; // para o laço desse fantasma corrente
            }
        }

        flag = 0;
    }
}

void movePacMan(char tecla){

    int i,j,flag=0,flag2=0;
    int y = posicaoHeroi.y;
    int x = posicaoHeroi.x;

    if(posicaoHeroi.marcaAchouPersonagem==0){ // faz uma única vez e marca onde o pac estava na primeira vez

        for(i=0;i<mapasPacMan.linhas && flag!= 1;i++){

            for(j=0;j<mapasPacMan.colunas && flag!= 1;j++){

                if(mapasPacMan.mapa[i][j]==HEROI){

                    y = i;
                    x = j;
                    flag = 1;
                }
            }
        }

        posicaoHeroi.x = x;
        posicaoHeroi.y = y;

        posicaoHeroi.marcaAchouPersonagem=1;
    }

    // movimenta o pacman no plano cartesiano
    // y é a ordenada
    // x é a abscissa

    switchMovimentacao(tecla,x,y);
    moveFantasma();
    comeFantasma(&packman,&mapasPacMan,x,y);
    pegaPilula(&packman,&mapasPacMan,x,y);
}

void main(){

    inicializaHeroi(&packman);
    abreMapa(&mapasPacMan);
    imprimemapa(&mapasPacMan);
    char movimentoJogador;

    do{

      exibeTutorialMovimentacao(&packman);
      scanf(" %c",&movimentoJogador);
      movePacMan(movimentoJogador);
      imprimemapa(&mapasPacMan);

    }while(!fimJogo(&packman,&mapasPacMan));

    liberaMapa(&mapasPacMan);
    system("pause");
}
