/*
 * Copyright (C) 2022 Alireza Heidari. All rights reserved.
 */

#include "common.h"

#include "draw.h"

extern App app;

// -----------------------------------------------------------------
void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, BG_R, BG_G, BG_B , BG_A);
	SDL_RenderClear(app.renderer);
}

// -----------------------------------------------------------------

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

// -----------------------------------------------------------------

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);


	texture = IMG_LoadTexture(app.renderer, filename);
	return texture;
}

// -----------------------------------------------------------------

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	//dest.w *= 3;
	//dest.h *= 3;
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
// -----------------------------------------------------------------
