/*
 * Copyright (C) 2022 Alireza Heidari. All rights reserved.
 */

#include "common.h"
#include "input.h"

extern App app;

// static void return type used for doKeyUp
// Explain:
// using the "static" keyword before the 
// function name causes the function scope to 
// be local. hence it cannot be accessed by the 
// main.c or other files.
// only this file can access the doKeyUp()
// and doKeyDown functions.
//
//
static void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
       	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
	       	{
			app.up  = 0;
		}	

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
	       	{
			app.down  = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
	       	{
			app.right  = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
	       	{
			app.left  = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LCTRL)
	       	{
			app.fire  = 0;
		}
	}
}



static void doKeyDown(SDL_KeyboardEvent *event)

{
	if (event->repeat == 0)
       	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
	       	{
			app.up  = 1;
			
		}	

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
	       	{
			app.down  = 1;
			
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
	       	{
			app.right  = 1;
			
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
	       	{
			app.left  = 1;
			
		}
		if (event->keysym.scancode == SDL_SCANCODE_LCTRL)
	       	{
			app.fire  = 1;
			
		}
	}
}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;
			default:
				break;
		}
	}
}



