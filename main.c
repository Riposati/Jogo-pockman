#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef _header_heroi _header_mapa _header_tuto

    #define _header_heroi
    #include "headers_packman/header_heroi.h"

    #define _header_mapa
    #include "headers_packman/header_mapa.h"

    #define _header_tuto
    #include "headers_packman/header_tutorial.h"
#endif

MapaPacMan mapasPacMan;
Posicao posicaoHeroi;
Heroi packman;

void main(){

    inicializaHeroi(&packman);
    abreMapa(&mapasPacMan);
    imprimemapa(&mapasPacMan);
    char movimentoJogador;

    do{

      exibeTutorialMovimentacao(&packman);
      scanf(" %c",&movimentoJogador);
      movePacMan(&posicaoHeroi,&mapasPacMan,&packman, movimentoJogador);
      imprimemapa(&mapasPacMan);

    }while(!fimJogo(&packman,&mapasPacMan));

    liberaMapa(&mapasPacMan);
    system("pause");
}
