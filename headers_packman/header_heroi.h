#ifndef HEADER_HEROI_H_INCLUDED
#define HEADER_HEROI_H_INCLUDED
#include "header_mapa.h"

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
#endif // HEADER_HEROI_H_INCLUDED
