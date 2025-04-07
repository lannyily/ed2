#ifndef MUSICA_H
#define MUSICA_H

typedef struct Musica {
    char titulo[20];
    int quantMinutos;

    struct Musica* Esq;
    struct Musica* Dir;
}Musica;

#endif