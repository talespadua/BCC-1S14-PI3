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

ALLEGRO_JOYSTICK *joystick;
ALLEGRO_DISPLAY *janela;
ALLEGRO_EVENT_QUEUE *fila_eventos;
ALLEGRO_BITMAP *teste;
unsigned char ***matriz;
camera *cam;
ALLEGRO_TIMER *timer ;
ALLEGRO_TIMER *contador ;
ALLEGRO_DISPLAY *display;

ALLEGRO_COLOR cor;

int largura ;
int altura;

ALLEGRO_BITMAP *buffer;
ALLEGRO_BITMAP *esquerda ;
ALLEGRO_BITMAP *direita;

bool inicializar();

#endif