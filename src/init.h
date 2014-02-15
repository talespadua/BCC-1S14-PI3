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

ALLEGRO_JOYSTICK *joystick;
ALLEGRO_DISPLAY *janela;
ALLEGRO_EVENT_QUEUE *fila_eventos;
ALLEGRO_BITMAP *teste;

bool inicializar();

#endif