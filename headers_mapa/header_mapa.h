#ifndef HEADER_MAPA_H_INCLUDED
#define HEADER_MAPA_H_INCLUDED

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

void imprimeparte(char desenho[4][7], int parte);
void imprimemapa(MapaPacMan *mapasPacMan);
void abreMapa(MapaPacMan *mapasPacMan);
void mostraMapa(MapaPacMan *mapasPacMan);
void liberaMapa(MapaPacMan *mapasPacMan);
void atualizaMapa(MapaPacMan *mapasPacMan,int x,int y);
void tiraFrutaMapa(MapaPacMan *mapasPacMan);

#endif // HEADER_MAPA_H_INCLUDED
