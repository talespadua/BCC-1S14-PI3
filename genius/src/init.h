#ifndef INIT_H
#define INIT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#include "camera.h"

enum colors {VERDE = 1, VERMELHO = 2, AZUL = 3, AMARELO = 4};

ALLEGRO_DISPLAY *janela;
ALLEGRO_EVENT_QUEUE *fila_eventos;

//COISINHAS DO HASHIMOTO
unsigned char ***matriz;
camera *cam;
ALLEGRO_TIMER *timer ;
ALLEGRO_TIMER *contador ;
ALLEGRO_DISPLAY *display;
int largura ;
int altura;

//COREZINHAS
ALLEGRO_COLOR cor_verde;
ALLEGRO_COLOR cor_vermelha;
ALLEGRO_COLOR cor_azul;
ALLEGRO_COLOR cor_amarelo;

//MUSIQUINHAS
ALLEGRO_SAMPLE *sample1;
ALLEGRO_SAMPLE *sample2;
ALLEGRO_SAMPLE *sample3;
ALLEGRO_SAMPLE *sample4;

ALLEGRO_SAMPLE *moeda;
ALLEGRO_SAMPLE *peido;

//TELINHAS
ALLEGRO_BITMAP *buffer;
ALLEGRO_BITMAP *esquerda ;
ALLEGRO_BITMAP *direita;
ALLEGRO_BITMAP *menu;
ALLEGRO_BITMAP *fim;

//JOGADINHAS
int jogadas[50];
int jogadas_jogador[50];

bool inicializar();

#endif