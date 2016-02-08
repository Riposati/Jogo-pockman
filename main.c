#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ESQUERDA 'a'
#define PRACIMA 'w'
#define PRABAIXO 's'
#define DIREITA 'd'
#define HEROI '@'
#define FANTASMA '&'
#define PILULA '$'

struct mapa{
    char **mapa;
    int linhas;
    int colunas;
    int quantidadeFrutasMapa;

}typedef MapaPacMan;

struct posicao{
    int x;
    int y;
    int marcaAchouPersonagem;
}typedef Posicao;

struct heroi{
    int qtdVidas;
    int pontos;
    int temPilula;
} typedef Heroi;

MapaPacMan mapasPacMan;
Posicao posicaoHeroi;
Heroi packman;

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

void imprimemapa() {
    int i,j,parte;

    for(i = 0; i < mapasPacMan.linhas; i++) {

        for(parte = 0; parte < 4; parte++) {
            for(j = 0; j < mapasPacMan.colunas; j++) {

                switch(mapasPacMan.mapa[i][j]) {
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

void inicializaHeroi(Heroi *heroi){

    heroi->qtdVidas = 5;
    heroi->pontos=0;
    heroi->temPilula = 0;
}

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
    fscanf(p,"%d",&mapasPacMan.quantidadeFrutasMapa);

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

    if(packman.qtdVidas==0) {
        puts("\n\nGAME OVER!!\n");
        printf("\aVOCE CONQUISTOU %d pontos, PARABENS!\n\n",packman.pontos);
        return 1;
    }else if(mapasPacMan.quantidadeFrutasMapa == 0){
        puts("\n\nVITORIA!\n");
        printf("\aVOCE CONQUISTOU %d pontos, PARABENS!\n\n",packman.pontos);
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
    if((mapasPacMan.mapa[y][x+1]==FANTASMA) || (mapasPacMan.mapa[y][x-1]==FANTASMA)){
        packman.qtdVidas--;
    }
}

void tiraFrutaMapa(){

    mapasPacMan.quantidadeFrutasMapa--;
}

void marcaPontos(int x,int y){

            /// ver se o pac consegue pontos
             if((mapasPacMan.mapa[y][x+1]=='*')){
                packman.pontos +=10;
                atualizaMapa(x+1,y);
                tiraFrutaMapa();
            }

            if((mapasPacMan.mapa[y][x-1]=='*')){
                packman.pontos +=10;
                atualizaMapa(x-1,y);
                tiraFrutaMapa();
            }

            if((mapasPacMan.mapa[y-1][x]=='*')){
                packman.pontos +=10;
                atualizaMapa(x,y-1);
                tiraFrutaMapa();
            }

            if((mapasPacMan.mapa[y+1][x]=='*')){
                packman.pontos +=10;
                atualizaMapa(x,y+1);
                tiraFrutaMapa();
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
    int ondeFantasmaApareceNaProxima = rand() % 9;

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
    comeFantasma(x,y);
    pegaPilula(x,y);
}

void exibeTutorialMovimentacao(){

    puts("\nCOMO JOGAR:");
    /*puts("@ - PACKMAN (VOCE)");
    puts("& - FANTASMAS");
    puts("* - FRUTAS COM PONTOS");
    puts("$ - BOMBAS");*/

    puts("Tecla W + enter = Para Cima");
    puts("Tecla A + enter = Para Esquerda");
    puts("Tecla S + enter = Para Baixo");
    puts("Tecla D + enter = Para Direita\n");
    printf("\nSUAS VIDAS ATE O MOMENTO JOGADOR -->>> %d\n",packman.qtdVidas);
    printf("\nVOCE TEM BOMBA -->>> %s\n\n",packman.temPilula ? "SIM" : "NAO");
}

void pegaPilula(int x,int y){

    if(mapasPacMan.mapa[y][x-1] ==PILULA){
        mapasPacMan.mapa[y][x-1] = '.';
        packman.temPilula = 1;
    }

    else if(mapasPacMan.mapa[y][x+1] ==PILULA){
        mapasPacMan.mapa[y][x+1] = '.';
        packman.temPilula = 1;
    }

    else if(mapasPacMan.mapa[y-1][x] ==PILULA){
        mapasPacMan.mapa[y-1][x] = '.';
        packman.temPilula = 1;
    }

    else if(mapasPacMan.mapa[y+1][x] ==PILULA){
        mapasPacMan.mapa[y+1][x] = '.';
        packman.temPilula = 1;
    }
}

void comeFantasma(int x,int y){

    if(packman.temPilula!=1)return;

    /// ver se tem fantasma perto do pac
    if((mapasPacMan.mapa[y][x+1]==FANTASMA)){
        mapasPacMan.mapa[y][x+1] = '.';
        packman.temPilula = 0;
        packman.pontos +=5;
    }

    else if(mapasPacMan.mapa[y][x-1]==FANTASMA){
        mapasPacMan.mapa[y][x-1] = '.';
        packman.temPilula = 0;
        packman.pontos +=5;
    }
}

void main(){

    //system("color ff");

    inicializaHeroi(&packman);
    abreMapa();
    imprimemapa();
    char movimentoJogador;

    do{

      exibeTutorialMovimentacao();
      scanf(" %c",&movimentoJogador);
      movePacMan(movimentoJogador);
      imprimemapa();

    }while(!fimJogo());

    liberaMapa();

    scanf("");
    system("pause");
}
