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

void inicializaHeroi(Heroi *heroi){

    heroi->qtdVidas = 5;
    heroi->pontos=0;
    heroi->temPilula = 0;
}

int podeAndar(MapaPacMan *mapasPacMan, int x,int y){

    if(mapasPacMan->mapa[y][x]=='.')
        return 1;
    else
        return 0;
}

int fimJogo(Heroi *packman,MapaPacMan *mapasPacMan){

    if(packman->qtdVidas==0) {
        puts("\n\nGAME OVER!!\n");
        printf("\aVOCE CONQUISTOU %d pontos, PARABENS!\n\n",packman->pontos);
        return 1;
    }else if(mapasPacMan->quantidadeFrutasMapa == 0){
        puts("\n\nVITORIA!\n");
        printf("\aVOCE CONQUISTOU %d pontos, PARABENS!\n\n",packman->pontos);
        return 1;
    }

    else return 0;
}

void tiraVidas(Heroi *packman,MapaPacMan *mapasPacMan,int x,int y){

    /// ver se tem fantasma perto do pac
    if((mapasPacMan->mapa[y][x+1]==FANTASMA) || (mapasPacMan->mapa[y][x-1]==FANTASMA)){
        packman->qtdVidas--;
    }
}

void pegaPilula(Heroi *packman,MapaPacMan *mapasPacMan,int x,int y){

    if(mapasPacMan->mapa[y][x-1] ==PILULA){
        mapasPacMan->mapa[y][x-1] = '.';
        packman->temPilula = 1;
    }

    else if(mapasPacMan->mapa[y][x+1] ==PILULA){
        mapasPacMan->mapa[y][x+1] = '.';
        packman->temPilula = 1;
    }

    else if(mapasPacMan->mapa[y-1][x] ==PILULA){
        mapasPacMan->mapa[y-1][x] = '.';
        packman->temPilula = 1;
    }

    else if(mapasPacMan->mapa[y+1][x] ==PILULA){
        mapasPacMan->mapa[y+1][x] = '.';
        packman->temPilula = 1;
    }
}

void comeFantasma(Heroi *packman,MapaPacMan *mapasPacMan,int x,int y){

    if(packman->temPilula!=1)return;

    /// ver se tem fantasma perto do pac
    if((mapasPacMan->mapa[y][x+1]==FANTASMA)){
        mapasPacMan->mapa[y][x+1] = '.';
        packman->temPilula = 0;
        packman->pontos +=5;
    }

    else if(mapasPacMan->mapa[y][x-1]==FANTASMA){
        mapasPacMan->mapa[y][x-1] = '.';
        packman->temPilula = 0;
        packman->pontos +=5;
    }
}
