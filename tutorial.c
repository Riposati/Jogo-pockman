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

void exibeTutorialMovimentacao(Heroi *packman){

    puts("\nCOMO JOGAR:");
    /*puts("@ - PACKMAN (VOCE)");
    puts("& - FANTASMAS");
    puts("* - FRUTAS COM PONTOS");
    puts("$ - BOMBAS");*/

    puts("Tecla W + enter = Para Cima");
    puts("Tecla A + enter = Para Esquerda");
    puts("Tecla S + enter = Para Baixo");
    puts("Tecla D + enter = Para Direita\n");
    printf("\nSUAS VIDAS ATE O MOMENTO JOGADOR -->>> %d\n",packman->qtdVidas);
    printf("\nVOCE TEM BOMBA -->>> %s\n\n",packman->temPilula ? "SIM" : "NAO");
}
