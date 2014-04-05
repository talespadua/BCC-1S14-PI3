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
#include "func.h"

#define ALTURA  800
#define LARGURA 600
#define FPS 60

 struct Game
 {
 	int mute;
 	int level;
  	ALLEGRO_SAMPLE *som;
 	ALLEGRO_FONT *fonte;
 	ALLEGRO_FONT *fonte_menu;
 	ALLEGRO_FONT *fonte_logo;
 	ALLEGRO_TIMER *timer;
 	ALLEGRO_DISPLAY *janela;
 	ALLEGRO_EVENT_QUEUE *fila_eventos;
 	ALLEGRO_SAMPLE *song;
 	ALLEGRO_SAMPLE_INSTANCE *songInstance;
 	ALLEGRO_FONT *fonteKeys;
 	ALLEGRO_JOYSTICK *joystick;

	ALLEGRO_BITMAP *teste; //teste
 };

 struct Game game;

bool inicializar();

#endif