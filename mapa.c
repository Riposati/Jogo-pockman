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

char desenhoparede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoheroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhopilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhovazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

char desenhofantasma[4][7] = {
	{" .-.  " },
	{"| OO| " },
	{"|   | " },
	{"'^^^' " }
};

char desenhofruta[4][7] = {
	{" .-. " },
	{" *** " },
	{" *** " },
	{"'.-.'" }
};

void imprimeparte(char desenho[4][7], int parte) {
    printf("%s", desenho[parte]);
}

void imprimemapa(MapaPacMan *mapasPacMan) {
    int i,j,parte;

    for(i = 0; i < mapasPacMan->linhas; i++) {

        for(parte = 0; parte < 4; parte++) {
            for(j = 0; j < mapasPacMan->colunas; j++) {

                switch(mapasPacMan->mapa[i][j]) {
                    case FANTASMA:
                        imprimeparte(desenhofantasma, parte);
                        break;
                    case HEROI:
                        imprimeparte(desenhoheroi, parte);
                        break;
                    case PILULA:
                        imprimeparte(desenhopilula, parte);
                        break;
                    case '*':
                        imprimeparte(desenhofruta, parte);
                        break;
                    case '|':
                    case '-':
                        imprimeparte(desenhoparede, parte);
                        break;
                    case '.':
                        imprimeparte(desenhovazio, parte);
                        break;
                }

            }
            printf("\n");
        }

    }
}

void abreMapa(MapaPacMan *mapasPacMan){
    int i;
    FILE *p;

    p = fopen("mapa_packman.txt","r");

    if(p == 0){

        printf("Algum problema na leitura do arquivo!\n");
        exit(1);
    }

    fscanf(p,"%d",&mapasPacMan->linhas);
    fscanf(p,"%d",&mapasPacMan->colunas);
    fscanf(p,"%d",&mapasPacMan->quantidadeFrutasMapa);

    mapasPacMan->mapa = (char *) malloc(sizeof(char) * mapasPacMan->linhas);

    for(i=0;i<mapasPacMan->linhas;i++){
        mapasPacMan->mapa[i] = (char *) malloc(sizeof(char) * mapasPacMan->colunas);
    }

    for(i=0;i<mapasPacMan->linhas;i++){
        fscanf(p,"%s",mapasPacMan->mapa[i]);
    }

    fclose(p);
}

void mostraMapa(MapaPacMan *mapasPacMan){

    int i;

    for(i=0;i<mapasPacMan->linhas;i++){
        printf("%s\n",mapasPacMan->mapa[i]);
    }
}

void liberaMapa(MapaPacMan *mapasPacMan){

    int i;

    for(i=0;i<mapasPacMan->linhas;i++){
        free(mapasPacMan->mapa[i]);
    }

   /// printf("memoria livre\n");
}


void atualizaMapa(MapaPacMan *mapasPacMan , int x,int y){

     mapasPacMan->mapa[y][x] = '.';
}

void tiraFrutaMapa(MapaPacMan *mapasPacMan){

    mapasPacMan->quantidadeFrutasMapa--;
}


