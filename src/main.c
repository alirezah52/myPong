/*
 * Copyright (C) 2022 Alireza Heidari. All rights reserved.
 */

#include "common.h"

#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"

// why no extern keyword is used here for the structs
// but extern had to be used in the draw.c or init.c?  
App app;
Entity player;
Entity bullet;

int main(int argc, char *argv[])
{
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	memset(&bullet, 0, sizeof(Entity));

	initSDL();
	atexit(cleanup);

	player.x = 50;
	player.y = 50;
	player.texture = loadTexture("gfx/player.png");

	bullet.texture = loadTexture("gfx/playerBullet.png");

	while (1)
	{
		prepareScene();

		doInput();


		if (app.up && (player.y >= 4)) {
			player.y -= 8; 
		}
		if (app.down && player.y <= (SCREEN_HEIGHT-64)) {
			player.y += 8; 
		}
		if (app.right && player.x <= (SCREEN_WIDTH-64)) {
			player.x += 8; 
		}
		if (app.left && (player.x >= 4)) {
			player.x -= 8; 
		}

		if (app.fire && bullet.health == 0) {
			bullet.x = player.x + 48;	
			bullet.y = player.y + 18;	
			bullet.dx = 1;
			bullet.dy = 0;
			bullet.health = 1;
		}

		bullet.x += bullet.dx;
		bullet.y += bullet.dy;

		if (bullet.x > SCREEN_WIDTH) {
			bullet.health = 0;
			
		}
		blit(player.texture, player.x, player.y);
		if (bullet.health > 0) {
			blit(bullet.texture, bullet.x, bullet.y);
		}

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}
