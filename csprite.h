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


#ifndef CSPRITE_H_
#define CSPRITE_H_

#define TRUE 1
#define FALSE 0

// CFrame representa un frame independiente de un sprite.
class CFrame {
public:
	SDL_Surface *img;
	void load(char *path);
	void unload();
};


// La clase CSprite está formada por un array de frames;
class CSprite {
private:
	int posx,posy;
	int frame_actual;
	int frames_totales;
	int frames_cargados;

public:
	CFrame *sprite;
	CSprite(int nf);
	CSprite();
	
	void setx(int x) {posx=x;}
	void sety(int y) {posy=y;}
	void addx(int x) {posx+=x;}
	void addy(int y) {posy+=y;}
	int getx() {return posx;}
	int gety() {return posy;}
	int getw() {return sprite[frame_actual].img->w;}
	int geth() {return sprite[frame_actual].img->h;}

	void addframe(CFrame frame);
	void selframe(int nf);
	int total_frames() {return frames_cargados;}
	int actual_frame() {return frame_actual;}	

	int finalize();
	void draw(SDL_Surface *superficie);	
	int colision(CSprite sp);
	int colisionMunecos(CSprite sp);
	int colision_circulos(CSprite sp);



};


#endif /* CSPRITE_H_ */


