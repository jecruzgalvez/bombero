/***************************************************************************
                          csprite.h  -  description
                             -------------------
    begin                : Mon Sep 2 2002
    copyright            : (C) 2002 by Alberto Garcia Serrano
    email                : albgarse@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <SDL.h>
#include "csprite.h"

// Sprite Class implementation

void CFrame::load(char *path) {
//void CFrame::load() {
	img=SDL_LoadBMP(path);	

	// Asignamos el color transparente al color rojo.
	SDL_SetColorKey(img,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(img->format,255,0,255));
	img=SDL_DisplayFormat(img);

}

void CFrame::unload(){
	SDL_FreeSurface(img);
}



CSprite::CSprite(int nf) {
	sprite=new CFrame[nf];
	frames_totales=nf;
	frames_cargados=0;
}


CSprite::CSprite() {
	int	nf=1;
	sprite=new CFrame[nf];
	frames_totales=nf;
	frames_cargados=0;
}


int CSprite::finalize() {
 int i;
	
	for (i=0 ; i<=frames_totales-1 ; i++) 
		sprite[i].unload();
}


void CSprite::addframe(CFrame frame) {
	if (frames_cargados<frames_totales) {
		sprite[frames_cargados]=frame;
		frames_cargados++;
	}
}



void CSprite::selframe(int nf) {
	if (nf<=frames_totales) {	
		frame_actual=nf;
	}
}


void CSprite::draw(SDL_Surface *superficie) {
	SDL_Rect dest;

	dest.x=posx;
	dest.y=posy;
	SDL_BlitSurface(sprite[frame_actual].img,NULL,superficie,&dest);
}



int CSprite::colision(CSprite sp) {
int w1,h1,w2,h2,x1,y1,x2,y2;

	w1=getw();		// ancho del sprite1
	h1=geth();		// altura del sprite1
	w2=sp.getw();		// ancho del sprite2
	h2=sp.geth();		// alto del sprite2
	x1=getx();		// pos. X del sprite1
	y1=gety();		// pos. Y del sprite1
	x2=sp.getx();		// pos. X del sprite2
	y2=sp.gety();		// pos. Y del sprite2

	if (((x1+w1)>x2)&&((y1+h1)>y2)&&((x2+w2)>x1)&&((y2+h2)>y1)) {
		return TRUE;
	} else {
		return FALSE;
	}
}






int CSprite::colisionMunecos(CSprite sp) {
int w1,h1,w2,h2,x1,y1,x2,y2;
int arriba1,abajo1,izquierda1,derecha1;
int arriba2,abajo2,izquierda2,derecha2;

	x1=getx()+5;		// pos. X del sprite1
	y1=gety()+35;		// pos. Y del sprite1
	w1=34;			// ancho del sprite1
	h1=39;			// altura del sprite1


	arriba1    = y1;
	abajo1     = y1+h1;
	izquierda1 = x1;
	derecha1   = x1+w1;

	x2=sp.getx();		// pos. X del sprite2
	y2=sp.gety();		// pos. Y del sprite2
	w2=sp.getw();		// ancho del sprite2
	h2=sp.geth();		// alto del sprite2

	arriba2    = y2;
	abajo2     = y2+h2;
	izquierda2 = x2;
	derecha2   = x2+w2;
	
	//       A1         A2          B1       B2          C1          C2          D1       D2
	//     x1+w1   >    x2         y1+h1 >   y2         x2+w2  >     x          y2+h2     y1
	if ( derecha1>=izquierda2 && abajo1>=arriba2 && derecha2>=izquierda1 && abajo2>=arriba1 ) {
		
		if (abajo1==arriba2)    	 //ARRIBA
			return 1;
		if (abajo2==arriba1)			//ABAJO
			return 2;		
		if (derecha1==izquierda2)	//IZQUIERDA
			return 3;
		if (derecha2==izquierda1)	//DERECHA
			return 4;		
	}
	else {
		return 0;
	}
}

