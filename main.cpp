/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Mon Oct 10 2016
    copyright            : (C) 2016 Jorge Elpidio Cruz Gálvez
    email                : jecruzgalvez@gmail.com
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "csprite.h"


#define ARRIBA    0
#define DERECHA   1
#define ABAJO     2
#define IZQUIERDA 3
#define NUM_MALOS	13
#define NUM_BOMBAS	10
#define NUM_ESCENARIOS	5
#define NUM_BLOQUES_H	17
#define NUM_BLOQUES_V	12

//VARIABLES PARA LA MUSICA DE FONDO Y EFECTOS DE SONIDO
Mix_Music *musica;
Mix_Chunk *explosion;
int canal1;	

long int frame=0;
int finalizar=0;
int escenario_actual = 0;
SDL_Surface	*ventana;

int escenarios [NUM_ESCENARIOS] [NUM_BLOQUES_V] [NUM_BLOQUES_H] = {
  {
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    2,1,3,3,3,3,1,3,1,1,1,1,1,1,1,1,2,
    2,1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,2,1,2,1,2,1,1,2,
    2,1,2,1,2,1,2,1,1,1,1,1,1,1,1,2,2,
    2,1,1,1,1,1,1,1,1,2,1,2,1,2,1,1,2,
    2,1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,2,1,2,1,2,1,1,2,
    2,1,2,1,2,1,2,1,1,1,1,1,1,1,1,2,2,
    2,1,1,1,1,1,1,1,1,2,1,2,1,2,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
  },
  {
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    2,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
  }
};

CFrame  fbloque;
CSprite	sbloque(10);

CFrame  fbueno;
CSprite sbueno(12);

CFrame  fmalo;
CSprite smalo(12);

CFrame  fbomba;
CSprite sbomba(10);




struct _bueno {
  int x, y, direccion, frame, colision;
} bueno;

struct _malo {
  int x, y, direccion, frame, colision, estado;
} malo[NUM_MALOS];

struct _bomba {
  int x, y, tiempo, frame, colision;
} bomba[NUM_BOMBAS];


int inicializa_sprites() {
  int x, y, z;
  //CARGA LOS FRAMES DE LOS BLOQUES
  fbloque.load("imagenes/bloque1.bmp");
  sbloque.addframe(fbloque);
  fbloque.load("imagenes/bloque2.bmp");
  sbloque.addframe(fbloque);
  fbloque.load("imagenes/bloque3.bmp");
  sbloque.addframe(fbloque);
  fbloque.load("imagenes/bloque4.bmp");
  sbloque.addframe(fbloque);
  fbloque.load("imagenes/bloque5.bmp");
  sbloque.addframe(fbloque);

  //CARGA LOS FRAMES DE LOS BUENOS
  fbueno.load("imagenes/bueno1.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno2.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno3.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno4.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno5.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno6.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno7.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno8.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno9.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno10.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno11.bmp");
  sbueno.addframe(fbueno);
  fbueno.load("imagenes/bueno12.bmp");
  sbueno.addframe(fbueno);
  //INICIALIZA LA POSICION DEL BUENO
  bueno.x=27;
  bueno.y=43;
  bueno.direccion=ABAJO;
  bueno.frame=6;

  //CARGA LOS FRAMES DE LOS MALOS
  fmalo.load("imagenes/malo1.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo2.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo3.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo4.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo5.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo6.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo7.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo8.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo9.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo10.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo11.bmp");
  smalo.addframe(fmalo);
  fmalo.load("imagenes/malo12.bmp");
  smalo.addframe(fmalo);
  //INICIALIZA LA POSICION DEL MALO
  srand( time(NULL) );
  for(z=0;z<NUM_MALOS;z++){
    do{
      x = rand()%(NUM_BLOQUES_H);
      y = rand()%(NUM_BLOQUES_V);
    }while( (x==0 && y==0) || escenarios[escenario_actual][y][x] == 2 );
		
    malo[z].x=x*50;
    malo[z].y=y*50;
    malo[z].direccion=ABAJO;
    malo[z].frame=6;
    malo[z].estado=1;
		

  }

  fbomba.load("imagenes/b0.bmp");
  sbomba.addframe(fbomba);
  fbomba.load("imagenes/b1.bmp");
  sbomba.addframe(fbomba);
  fbomba.load("imagenes/b2.bmp");
  sbomba.addframe(fbomba);
  fbomba.load("imagenes/b3.bmp");
  sbomba.addframe(fbomba);
  fbomba.load("imagenes/b3.bmp");
  sbomba.addframe(fbomba);
  fbomba.load("imagenes/b3.bmp");
  sbomba.addframe(fbomba);
  fbomba.load("imagenes/b3.bmp");
  sbomba.addframe(fbomba);

  for(z=0;z<NUM_BOMBAS;z++){
    bomba[z].tiempo=0;
    bomba[z].frame=0;

  }

}


void cambia_frames(char *nombre,int i){

  if(strcmp(nombre,"bueno")==0)
    if(bueno.frame ==3 * bueno.direccion + 2)
      bueno.frame = 3 * bueno.direccion;
    else	
      bueno.frame += 1;

  if(strcmp(nombre,"malo")==0)
    if(malo[i].frame == 3 * malo[i].direccion + 2)
      malo[i].frame = 3 * malo[i].direccion;
    else	
      malo[i].frame += 1;
}





void cambiaDireccionMalo(int z){
  switch(malo[z].colision){
  case 1: //ARRIBA
    malo[z].y-=1;
    do{
      malo[z].direccion=rand()%(4);
    }while(malo[z].direccion==ABAJO);	
    break;
  case 2: //ABAJO
    malo[z].y+=1;
    do{
      malo[z].direccion=rand()%(4);
    }while(malo[z].direccion==ARRIBA);
    break;
  case 3: //IZQUIERDA
    malo[z].x-=1;
    do{
      malo[z].direccion=rand()%(4);
    }while(malo[z].direccion==DERECHA);
    break;
  case 4: //DERECHA
    malo[z].x+=1;
    do{
      malo[z].direccion=rand()%(4);
    }while(malo[z].direccion==IZQUIERDA);
    break;
  }
  malo[z].frame = malo[z].direccion * 3;
}






void pinta_ventana(){
  int x, y, z;

  //PINTA LOS BLOQUES DE LA VENTANA
  for(x=0;x<NUM_BLOQUES_H;x++)
    for(y=0;y<NUM_BLOQUES_V;y++) {
      sbloque.selframe( escenarios[escenario_actual][y][x] );
      sbloque.setx(x*50-25);
      sbloque.sety(y*50+25);
      sbloque.draw(ventana);

      if(escenarios[escenario_actual][y][x] >= 2){
	//VERIFICA LAS COLISIONES DEL BUENO CON LAS CAJAS
	bueno.colision = sbueno.colisionMunecos(sbloque);
	if( bueno.colision > 0){
	  switch(bueno.colision){
	  case 1:
	    bueno.y-=1;
	    break;
	  case 2:
	    bueno.y+=1;
	    break;
	  case 3:
	    bueno.x-=1;
	    break;
	  case 4:
	    bueno.x+=1;
	    break;
	  }	
	}
	//VERIFICA LAS COLISIONES DE LOS MALOS CON LAS CAJAS
	for(z=0;z<NUM_MALOS;z++){
	  smalo.setx(malo[z].x);
	  smalo.sety(malo[z].y);
	  malo[z].colision = smalo.colisionMunecos(sbloque);
	  if( malo[z].colision > 0)
	    cambiaDireccionMalo(z);
	}					
      }
    }



  //PINTA LAS BOMBAS
  for(x=0;x<NUM_BOMBAS;x++){
    if(bomba[x].tiempo > 0){
      if(bomba[x].tiempo == 150)
	bomba[x].frame=1;
      if(bomba[x].tiempo == 100)
	bomba[x].frame=2;
      if(bomba[x].tiempo == 50){
	bomba[x].frame=3;
	canal1 = Mix_PlayChannel(-1,explosion,0);
      }
      if(bomba[x].tiempo <= 50){
	for(z=0;z<NUM_MALOS;z++){
	  smalo.setx(malo[z].x);
	  smalo.sety(malo[z].y);
	  sbomba.setx(bomba[x].x);
	  sbomba.sety(bomba[x].y);
	  if (smalo.colision(sbomba))
	    malo[z].estado=0;
	}			
      }



      //PINTA LAS BOMBAS		
      sbomba.setx(bomba[x].x);
      sbomba.sety(bomba[x].y);
      sbomba.selframe(bomba[x].frame);
      sbomba.draw(ventana);
      bomba[x].tiempo--;
    }
  }




  //PINTA EL BUENO
  sbueno.setx(bueno.x);	
  sbueno.sety(bueno.y);
  sbueno.selframe(bueno.frame);
  sbueno.draw(ventana);

  //VERIFICA LA COLISION DEL BUENO CON EL MALO
  for(x=0;x<NUM_MALOS;x++){
    smalo.setx(malo[x].x);
    smalo.sety(malo[x].y);
    if(sbueno.colision(smalo))
      finalizar=1;
  }

  //MUEVE EL MALO
  for(x=0;x<NUM_MALOS;x++){
    if (malo[x].estado){

      if ( malo[x].direccion == ARRIBA )
	if(malo[x].y == 0){
	  do{
	    malo[x].direccion=rand()%(4);
	  }while(malo[x].direccion==ARRIBA);
	  malo[x].frame = malo[x].direccion * 3;
	}
	else
	  malo[x].y-=1;
      if ( malo[x].direccion == DERECHA )
	if(malo[x].x == 480-20){
	  do{
	    malo[x].direccion=rand()%(4);
	  }while(malo[x].direccion==DERECHA);
	  malo[x].frame = malo[x].direccion * 3;
	}
	else
	  malo[x].x+=1;
      if ( malo[x].direccion == ABAJO )
	if(malo[x].y == 400-28){
	  do{
	    malo[x].direccion=rand()%(4);
	  }while(malo[x].direccion==ABAJO);
	  malo[x].frame = malo[x].direccion * 3;
	}
	else
	  malo[x].y+=1;
      if ( malo[x].direccion == IZQUIERDA )
	if(malo[x].x == 0){
	  do{
	    malo[x].direccion=rand()%(4);
	  }while(malo[x].direccion==IZQUIERDA);
	  malo[x].frame = malo[x].direccion * 3;
	}
	else
	  malo[x].x-=1;
      cambia_frames("malo",x);
    }
  }





  //PINTA EL MALO
  for(x=0;x<NUM_MALOS;x++){
    smalo.setx(malo[x].x);
    smalo.sety(malo[x].y);
    smalo.selframe(malo[x].frame);
    smalo.draw(ventana);
  }



  //MUESTRA LA VENTANA
  SDL_Flip(ventana);
}



void creaBomba() {
  int i, libre=-1;

  //¿HAY BOMBAS LIBRES?
  for (i=0; i<NUM_BOMBAS; i++) {
    if (bomba[i].tiempo==0)
      libre=i;
  }
  //SI HAY BOMBA LIBRE
  if (libre>=0) {
    bomba[libre].x=sbueno.getx()-2;
    bomba[libre].y=sbueno.gety()+27;
    bomba[libre].tiempo = 200;
    bomba[libre].frame = 0;
  }
}




int main(int argc, char *argv[]) {
  SDL_Event	evento;
  Uint8        *tecla;
  SDL_Rect	rectangulo;
  int contador;

  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0) {
    printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
    return 1;
  }

  ventana = SDL_SetVideoMode(800,600,24,SDL_HWSURFACE);
  if (ventana == NULL) {
    printf("No se puede inicializar el modo gráfico: \n",SDL_GetError());
    return 1;
  }



  if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096) < 0)
    {
      printf("Error al cargar el audio: %s\n",SDL_GetError());
      exit(1);
    }

  //CERRAR EL AUDIO
  atexit(Mix_CloseAudio);

  //CARGAR LA MUSICA

  musica =    Mix_LoadMUS("sonidos/fondo.mp3");
  explosion = Mix_LoadWAV("sonidos/explosion.wav");
	
  if(musica == NULL){
    printf("Error al cargar la musica: %s",SDL_GetError());
    exit(1);
  }

  if(explosion == NULL)
    {
      printf("Error al cargar el sonido: %s",SDL_GetError());
      exit(1);
    }


    



  Mix_HaltMusic();
  Mix_PlayMusic(musica,-1); 

  atexit(SDL_Quit);
  inicializa_sprites();
  srand(time(NULL));


  //	if(!SDL_WM_ToggleFullScreen(ventana))
  //		printf("No se puede cambiar a pantalla completa: %s",SDL_GetError());






  while (finalizar == 0) {

    frame++;


    //CAMBIA ALEATORIAMENTE LA DIRECCION DE ALGUN MALO
    malo[rand()%NUM_MALOS].colision=rand()%4;			
    cambiaDireccionMalo(rand()%NUM_MALOS);


    //LEER LA ENTRADA
    tecla=SDL_GetKeyState(NULL);
    if ( tecla[SDLK_UP]){
      if(bueno.direccion != ARRIBA){
	bueno.direccion=ARRIBA;
	bueno.frame=0;
      }
      bueno.y-=1;
      cambia_frames("bueno",0);
    }
    else if ( tecla[SDLK_DOWN]){
      if(bueno.direccion != ABAJO){
	bueno.direccion=ABAJO;
	bueno.frame=6;
      }
      bueno.y+=1;
      cambia_frames("bueno",0);
    }
    else if ( tecla[SDLK_LEFT]){
      if(bueno.direccion != IZQUIERDA){
	bueno.direccion=IZQUIERDA;
	bueno.frame=9;
      }
      bueno.x-=1;
      cambia_frames("bueno",0);
    }
    else if ( tecla[SDLK_RIGHT]){
      if(bueno.direccion != DERECHA){
	bueno.direccion=DERECHA;
	bueno.frame=3;
      }
      bueno.x+=1;
      cambia_frames("bueno",0);
    }

    if( tecla[SDLK_SPACE])
      if(escenario_actual < 4){
	bueno.x=10;
	bueno.y=10;
	escenario_actual++;
	SDL_Delay(100);
      }

    if( tecla[SDLK_a] )
      creaBomba();		
		

    //PROCESAR LA ENTRADA

    //LOGICA DEL JUEGO


    //OTRAS TAREAS

    //MOSTRAR EL FRAME EN LA VENTANA
    pinta_ventana();

    SDL_Delay(10);

    while (SDL_PollEvent(&evento)) {
      if (evento.type == SDL_QUIT) 
	finalizar=1;
      if (evento.type == SDL_KEYDOWN)
	if (evento.key.keysym.sym == SDLK_ESCAPE)
	  finalizar=1;
    }

    //	  SDL_Delay(50);
  }

  return 0;
}
