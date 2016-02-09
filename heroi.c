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

void movePacMan(Posicao *posicaoHeroi , MapaPacMan *mapasPacMan , Heroi *packman ,char tecla){

    int i,j,flag=0;
    int y = posicaoHeroi->y;
    int x = posicaoHeroi->x;

    if(posicaoHeroi->marcaAchouPersonagem==0){ // faz uma única vez e marca onde o pac estava na primeira vez

        for(i=0;i<mapasPacMan->linhas && flag!= 1;i++){

            for(j=0;j<mapasPacMan->colunas && flag!= 1;j++){

                if(mapasPacMan->mapa[i][j]==HEROI){

                    y = i;
                    x = j;
                    flag = 1;
                }
            }
        }

        posicaoHeroi->x = x;
        posicaoHeroi->y = y;

        posicaoHeroi->marcaAchouPersonagem=1;
    }

    // movimenta o pacman no plano cartesiano
    // y é a ordenada
    // x é a abscissa

    switchMovimentacao(posicaoHeroi, mapasPacMan , packman ,&tecla,x,y);

    printf("Posicao pack eixo x = %d \n",posicaoHeroi->x);
    printf("Posicao pack eixo y = %d \n",posicaoHeroi->y);

    moveFantasma(mapasPacMan);
    comeFantasma(packman,mapasPacMan,x,y);
    pegaPilula(packman,mapasPacMan,x,y);
}

void switchMovimentacao(Posicao *posicaoHeroi , MapaPacMan *mapasPacMan , Heroi *packman ,char *tecla, int x, int y){


        printf("tecla digitada = %c\n",*tecla);
        printf("Posicao pack eixo x = %d \n",posicaoHeroi->x);
        printf("Posicao pack eixo y = %d \n",posicaoHeroi->y);

        switch(*tecla){

        case ESQUERDA:
            if(podeAndar(mapasPacMan,posicaoHeroi->x-1,posicaoHeroi->y)){

                mapasPacMan->mapa[y][x-1] = HEROI;
                posicaoHeroi->x = x-1;

            }else return;

            break;

        case PRACIMA:
            if(podeAndar(mapasPacMan,posicaoHeroi->x,posicaoHeroi->y-1)){

                mapasPacMan->mapa[y-1][x] = HEROI;
                posicaoHeroi->y = y-1;

            }else return;

            break;

        case PRABAIXO:
            if(podeAndar(mapasPacMan,posicaoHeroi->x,posicaoHeroi->y+1)){

                mapasPacMan->mapa[y+1][x] = HEROI;
                posicaoHeroi->y = y+1;

            }else return;

            break;

        case DIREITA:
            if(podeAndar(mapasPacMan,posicaoHeroi->x+1,posicaoHeroi->y)){

                mapasPacMan->mapa[y][x+1] = HEROI;
                posicaoHeroi->x = x+1;

            }else return;

            break;

        // movimento que não existe, não faça nada
        default:return;
    }

    atualizaMapa(mapasPacMan,x,y);
    tiraVidas(packman,mapasPacMan,x,y);
    marcaPontos(mapasPacMan,packman,x,y);
}

void marcaPontos(MapaPacMan *mapasPacMan , Heroi *packman, int x,int y){

            /// ver se o pac consegue pontos
             if((mapasPacMan->mapa[y][x+1]=='*')){
                packman->pontos +=10;
                atualizaMapa(mapasPacMan,x+1,y);
                tiraFrutaMapa(mapasPacMan);
            }

            if((mapasPacMan->mapa[y][x-1]=='*')){
                packman->pontos +=10;
                atualizaMapa(mapasPacMan,x-1,y);
                tiraFrutaMapa(mapasPacMan);
            }

            if((mapasPacMan->mapa[y-1][x]=='*')){
                packman->pontos +=10;
                atualizaMapa(mapasPacMan,x,y-1);
                tiraFrutaMapa(mapasPacMan);
            }

            if((mapasPacMan->mapa[y+1][x]=='*')){
                packman->pontos +=10;
                atualizaMapa(mapasPacMan,x,y+1);
                tiraFrutaMapa(mapasPacMan);
            }
}

void moveFantasma(MapaPacMan *mapasPacMan){

    int yFantasma;
    int xFantasma;
    int flag=0,i,j;
    srand(time(0));
    int ondeFantasmaApareceNaProxima = rand() % 9;

     for(i=0;i<mapasPacMan->linhas;i++){

        for(j=0;j<mapasPacMan->colunas && flag != 1;j++){

            if(mapasPacMan->mapa[i][j]==FANTASMA){

                xFantasma = j;
                yFantasma = i;

                if(podeAndar(mapasPacMan,xFantasma+ondeFantasmaApareceNaProxima,yFantasma)){ // tenta a direita

                    mapasPacMan->mapa[yFantasma][xFantasma+ondeFantasmaApareceNaProxima] = FANTASMA;
                    atualizaMapa(mapasPacMan,xFantasma,yFantasma);
                }else{

                    if(podeAndar(mapasPacMan,xFantasma-ondeFantasmaApareceNaProxima,yFantasma)){ // tenta a esquerda

                        mapasPacMan->mapa[yFantasma][xFantasma-ondeFantasmaApareceNaProxima] = FANTASMA;
                        atualizaMapa(mapasPacMan,xFantasma,yFantasma);
                    }
                }

                flag = 1; // para o laço desse fantasma corrente
            }
        }

        flag = 0;
    }
}
