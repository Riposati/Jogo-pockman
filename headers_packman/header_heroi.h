#ifndef HEADER_HEROI_H_INCLUDED
#define HEADER_HEROI_H_INCLUDED

#ifndef _header_mapa

    #define _header_mapa
    #include "header_mapa.h"

#endif

struct heroi{
    int qtdVidas;
    int pontos;
    int temPilula;
} typedef Heroi;

struct posicao{
    int x;
    int y;
    int marcaAchouPersonagem;
}typedef Posicao;

void inicializaHeroi(Heroi *heroi);
int podeAndar(MapaPacMan *mapasPacMan, int x,int y);
int fimJogo(Heroi *packman,MapaPacMan *mapasPacMan);
void tiraVidas(Heroi *packman,MapaPacMan *mapasPacMan,int x,int y);
void pegaPilula(Heroi *packman,MapaPacMan *mapasPacMan,int x,int y);
void comeFantasma(Heroi *packman,MapaPacMan *mapasPacMan,int x,int y);
void movePacMan(Posicao *posicao , MapaPacMan *mapasPacMan , Heroi *packman ,char tecla);
void switchMovimentacao(Posicao *posicaoHeroi , MapaPacMan *mapasPacMan , Heroi *packman ,char *tecla, int x, int y);
void marcaPontos(MapaPacMan *mapasPacMan , Heroi *packman, int x,int y);
void moveFantasma(MapaPacMan *mapasPacMan);

#endif // HEADER_HEROI_H_INCLUDED
