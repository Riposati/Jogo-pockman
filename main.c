#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ESQUERDA 'a'
#define PRACIMA 'w'
#define PRABAIXO 's'
#define DIREITA 'd'
#define HEROI '@'
#define FANTASMA 'F'

struct mapa{
    char **mapa;
    int linhas;
    int colunas;
}typedef MapaPacMan;

struct posicao{
    int x;
    int y;
    int marcaAchouPersonagem;
}typedef Posicao;

MapaPacMan mapasPacMan;
Posicao posicaoHeroi;
int qtdVidas = 5;
int pontos = 0;

void abreMapa(){

    int i;
    FILE *p;

    p = fopen("mapa_packman.txt","r");

    if(p == 0){

        printf("Algum problema na leitura do arquivo!\n");
        exit(1);
    }

    fscanf(p,"%d",&mapasPacMan.linhas);
    fscanf(p,"%d",&mapasPacMan.colunas);

    mapasPacMan.mapa = (char *) malloc(sizeof(char) * mapasPacMan.linhas);

    for(i=0;i<mapasPacMan.linhas;i++){
        mapasPacMan.mapa[i] = (char *) malloc(sizeof(char) * mapasPacMan.colunas);
    }

    for(i=0;i<mapasPacMan.linhas;i++){
        fscanf(p,"%s",mapasPacMan.mapa[i]);
    }

    fclose(p);
}

void mostraMapa(){

    int i;

    for(i=0;i<mapasPacMan.linhas;i++){
        printf("%s\n",mapasPacMan.mapa[i]);
    }
}

void liberaMapa(){

    int i;

    for(i=0;i<mapasPacMan.linhas;i++){
        free(mapasPacMan.mapa[i]);
    }

   /// printf("memoria livre\n");
}

int fimJogo(){

    if(qtdVidas==0) {
        puts("\n\nGAME OVER!!\n");
        printf("\aVOCE CONQUISTOU %d pontos, PARABENS!\n\n",pontos);
        return 1;
    }

    else return 0;
}

int podeAndar(int x,int y){

    if(mapasPacMan.mapa[y][x]=='.')
        return 1;
    else
        return 0;
}

void atualizaMapa(int x,int y){

     mapasPacMan.mapa[y][x] = '.';
}

void tiraVidas(int x,int y){

    /// ver se tem fantasma perto do pac
    if((mapasPacMan.mapa[y][x+1]=='F') || (mapasPacMan.mapa[y][x-1]=='F')){
        qtdVidas--;
    }
}

void marcaPontos(int x,int y){

            /// ver se o pac consegue pontos
             if((mapasPacMan.mapa[y][x+1]=='*')){
                pontos +=10;
                atualizaMapa(x+1,y);
            }

            if((mapasPacMan.mapa[y][x-1]=='*')){
                pontos +=10;
                atualizaMapa(x-1,y);
            }

            if((mapasPacMan.mapa[y-1][x]=='*')){
                pontos +=10;
                atualizaMapa(x,y-1);
            }

            if((mapasPacMan.mapa[y+1][x]=='*')){
                pontos +=10;
                atualizaMapa(x,y+1);
            }
}

void switchMovimentacao(char tecla, int x, int y){

        switch(tecla){

        case ESQUERDA:
            if(podeAndar(posicaoHeroi.x-1,posicaoHeroi.y)){

                mapasPacMan.mapa[y][x-1] = HEROI;
                posicaoHeroi.x = x-1;

            }else return;

            break;

        case PRACIMA:
            if(podeAndar(posicaoHeroi.x,posicaoHeroi.y-1)){

                mapasPacMan.mapa[y-1][x] = HEROI;
                posicaoHeroi.y = y-1;

            }else return;

            break;

        case PRABAIXO:
            if(podeAndar(posicaoHeroi.x,posicaoHeroi.y+1)){

                mapasPacMan.mapa[y+1][x] = HEROI;
                posicaoHeroi.y = y+1;

            }else return;

            break;

        case DIREITA:
            if(podeAndar(posicaoHeroi.x+1,posicaoHeroi.y)){

                mapasPacMan.mapa[y][x+1] = HEROI;
                posicaoHeroi.x = x+1;

            }else return;

            break;

        // movimento que não existe, não faça nada
        default:return;
    }

    atualizaMapa(x,y);
    tiraVidas(x,y);
    marcaPontos(x,y);
}

void moveFantasma(){

    int yFantasma;
    int xFantasma;
    int flag=0,i,j;
    srand(time(0));
    int ondeFantasmaApareceNaProxima = rand() % 5;

     for(i=0;i<mapasPacMan.linhas;i++){

        for(j=0;j<mapasPacMan.colunas && flag != 1;j++){

            if(mapasPacMan.mapa[i][j]==FANTASMA){

                xFantasma = j;
                yFantasma = i;

                if(podeAndar(xFantasma+ondeFantasmaApareceNaProxima,yFantasma)){ // tenta a direita

                    mapasPacMan.mapa[yFantasma][xFantasma+ondeFantasmaApareceNaProxima] = FANTASMA;
                    atualizaMapa(xFantasma,yFantasma);
                }else{

                    if(podeAndar(xFantasma-ondeFantasmaApareceNaProxima,yFantasma)){ // tenta a esquerda

                        mapasPacMan.mapa[yFantasma][xFantasma-ondeFantasmaApareceNaProxima] = FANTASMA;
                        atualizaMapa(xFantasma,yFantasma);
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
}

void exibeTutorialMovimentacao(){
    puts("\nCOMO JOGAR:\n");
    puts("\n@ - PACKMAN (VOCE)\n");
    puts("F - FANTASMAS\n");
    puts("* - FRUTAS COM PONTOS\n");

    puts("Tecla W + enter = Para Cima");
    puts("Tecla A + enter = Para Esquerda");
    puts("Tecla S + enter = Para Baixo");
    puts("Tecla D + enter = Para Direita\n");
    printf("SUAS VIDAS ATE O MOMENTO JOGADOR -->>> %d\n",qtdVidas);
}

void main(){

    system("color ff");

    abreMapa();
    mostraMapa();
    char movimentoJogador;

    do{

      exibeTutorialMovimentacao();
      scanf(" %c",&movimentoJogador);
      movePacMan(movimentoJogador);
      mostraMapa();

    }while(!fimJogo());

    liberaMapa();
    system("pause");
}
