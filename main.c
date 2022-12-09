/** pong game written in C using sdl2 library. */
/** written by: Alireza Heidari */

#include "common.h"
#include "defs.h"
#include "structs.h"

/** top level functions */
void			initialize(void);
void			cleanup(void);
void			doInput(void);
void			update(float);

/** ball functions */
Ball			makeBall(int);
void			updateBall(Ball *ball, float elapsed);
void			renderBall(Ball *ball);

/** player functions  */
Player			makePlayer(void);
void			updatePlayers(float elapsed);
void			renderPlayers(void);

void			updateScore(int player, int points);

/** void updateRound(Ball *ball); */

/** global variables */
SDL_Window		*win;
SDL_Renderer	*rend;

Ball			ball;
Player			player1;
Player			player2;

float			elapsed;
bool			served = false;
float			BALL_SPEED = 350;
const float		PLAYER_SPEED = 300.0f;
/** int game_round = 0; */

int	main(int argc, char *argv[])
{
	Uint32	lastTick;
	Uint32	currTick;
	Uint32	diff;

	// initialize SDL library
	initialize();
	// exit if error during init SDL
	atexit(cleanup);
	// initialize players and objects
	ball = makeBall(BALL_SIZE);
	lastTick = SDL_GetTicks();
	while (1)
	{
		doInput();
		currTick = SDL_GetTicks();
		diff = currTick - lastTick;
		elapsed = diff / 1000.0f;
		update(elapsed);
		lastTick = currTick;
	}
	return (0);
}

void	initialize(void)
{
	/*Initialize SDL.*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL_INIT_VIDEO failed: %s\n", SDL_GetError());
		exit(1);
	}
	/*Create the window where we will draw.*/
	win = SDL_CreateWindow("pongali", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!win)
	{
		fprintf(stderr, "window failed: %s\n", SDL_GetError());
		exit(1);
	}
	/*We must call SDL_CreatRenderer in order for the draw calls to affect this window. */
	rend = SDL_CreateRenderer(win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!rend)
	{
		fprintf(stderr, "renderer failed: %s\n", SDL_GetError());
		exit(1);
	}
	ball = makeBall(BALL_SIZE);
	player1 = makePlayer();
	player2 = makePlayer();
}

bool	coinFlip(void)
{
	time_t	t;

	srand((unsigned)time(&t));
	return (rand() % 2 == 1 ? true : false);
}

Ball	makeBall(int size)
{
    ball.xPosition = WINDOW_WIDTH / 2.0 - size / 2.0;
	ball.yPosition = WINDOW_HEIGHT / 2.0 - size / 2.0;
	ball.xSpeed = BALL_SPEED * (coinFlip() ? 1 : -1);
	ball.ySpeed = BALL_SPEED * (coinFlip() ? 1 : -1);
	ball.size = size;
	return (ball);
}

Player	makePlayer(void)
{
	Player player = {
		.yPosition = WINDOW_HEIGHT / 2.0,
	};
	return (player);
}

void	update(float elapsed)
{
    SDL_SetRenderDrawColor(rend, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, BACKGROUND_ALPHA);
	SDL_RenderClear(rend);
	updateBall(&ball, elapsed);
	updatePlayers(elapsed);
	/** if (player1.score == 5 || player2.score == 5) { */
	/**     updateRound(&ball); */
	/**      */
	/** } */
	renderBall(&ball);
	renderPlayers();
	// present the drawn frame in the backbuffer to the front buffer(user screen)
	SDL_RenderPresent(rend);
}

void	updateBall(Ball *ball, float elapsed)
{
	// space starts the ball
	if (!served)
	{
		ball->xPosition = WINDOW_WIDTH / 2.0;
		/** TODO: randomize the start y position of ball */
        ball->yPosition = WINDOW_HEIGHT / 2.0;
		return ;
	}
	ball->xPosition += ball->xSpeed * elapsed;
    ball->yPosition += ball->ySpeed * elapsed;
	/** left wall collisions */
	if (ball->xPosition < 0)
	{
		updateScore(2, 1);
		/** ball->xSpeed = fabs(ball->xSpeed); */
	}
	/** right wall collisions */
    if (ball->xPosition > WINDOW_WIDTH - BALL_SIZE)
	{
		updateScore(1, 1);
		/** ball->xSpeed = -fabs(ball->xSpeed); */
	}
	/** top wall collision */
    if (ball->yPosition < 0)
	{
		ball->ySpeed = fabs(ball->ySpeed);
	}
	/** bottom wall collision */
    if (ball->yPosition > WINDOW_HEIGHT - BALL_SIZE)
	{
		ball->ySpeed = -fabs(ball->ySpeed);
	}
}

void	updatePlayers(float elapsed)
{
	const Uint8	*keyboardstate;

	/** player movements */
	keyboardstate = SDL_GetKeyboardState(NULL);
	if (keyboardstate[SDL_SCANCODE_SPACE])
	{
		served = true;
	}
	/** player 1 goes up */
	if (keyboardstate[SDL_SCANCODE_W] && player1.yPosition > PLAYER_HEIGHT/ 2.0)
	{
		player1.yPosition -= PLAYER_SPEED * elapsed;
	}
	/** player 1 goes down */
	if (keyboardstate[SDL_SCANCODE_S] && player1.yPosition < WINDOW_HEIGHT - PLAYER_HEIGHT / 2.0)
	{
		player1.yPosition += PLAYER_SPEED * elapsed;
	}
	/** player 2 goes up */
if (keyboardstate[SDL_SCANCODE_U] && player2.yPosition > PLAYER_HEIGHT / 2.0)
	{
		player2.yPosition -= PLAYER_SPEED * elapsed;
	}
	/** player 2 goes down */
	if (keyboardstate[SDL_SCANCODE_J] && player2.yPosition < WINDOW_HEIGHT - PLAYER_HEIGHT / 2.0)
	{
		player2.yPosition += PLAYER_SPEED * elapsed;
	}
	/** ball-player collisions */
	SDL_Rect ballRect = {
		.x = ball.xPosition,
		.y = ball.yPosition,
		.w = ball.size,
		.h = ball.size};
	SDL_Rect p1rect = {
		.x = PLAYER_MARGIN,
		.y = (int)(player1.yPosition) - PLAYER_HEIGHT / 2,
		.w = PLAYER_WIDTH,
		.h = PLAYER_HEIGHT};
	if (SDL_HasIntersection(&ballRect, &p1rect))
	{
		ball.xSpeed = fabs(ball.xSpeed);
	}
	SDL_Rect p2rect = {
		.x = WINDOW_WIDTH - PLAYER_MARGIN - PLAYER_WIDTH,
		.y = (int)(player2.yPosition) - PLAYER_HEIGHT / 2,
		.w = PLAYER_WIDTH,
		.h = PLAYER_HEIGHT};
	if (SDL_HasIntersection(&ballRect, &p2rect))
	{
		ball.xSpeed = -fabs(ball.xSpeed);
	}
}

void	updateScore(int player, int points)
{
	char	*fmt;
	int		len;
	char	buf[len + 1];

	served = false;
	if (player == 1)
	{
		player1.score += points;
	}
	if (player == 2)
	{
		player2.score += points;
	}
	fmt = "Player 1: %d | Player 2: %d";
	len = snprintf(NULL, 0, fmt, player1.score, player2.score);
	snprintf(buf, len + 1, fmt, player1.score, player2.score);
	SDL_SetWindowTitle(win, buf);
}

/** void updateRound(Ball *ball) */
/** { */
/**     [> served = false; <] */
/**     SPEED += 1; */
/** } */

void	renderBall(Ball *ball)
{
	int	size;

	size = ball->size;
    SDL_SetRenderDrawColor(rend, BALL_RED, BALL_GREEN, BALL_BLUE, BALL_ALPHA);
	SDL_Rect rect = {
		.x = ball->xPosition,
		.y = ball->yPosition,
        .w = size,
		.h = size};
	SDL_RenderFillRect(rend, &rect);
	SDL_RenderDrawRect(rend, &rect);
}

void	renderPlayers(void)
{
	/** render player 1 left and red */
	SDL_SetRenderDrawColor(rend, PLAYER_RED, PLAYER_GREEN, PLAYER_BLUE, PLAYER_ALPHA);
	SDL_Rect p1rect = {
		.x = PLAYER_MARGIN,
        .y = (int)(player1.yPosition) - PLAYER_HEIGHT / 2,
		.w = PLAYER_WIDTH,
		.h = PLAYER_HEIGHT};
	SDL_RenderFillRect(rend, &p1rect);
	SDL_RenderDrawRect(rend, &p1rect);
	/** render player 2 right and blue */
    SDL_SetRenderDrawColor(rend, PLAYER_RED, PLAYER_GREEN, PLAYER_BLUE, PLAYER_ALPHA);
	SDL_Rect p2rect = {
        .x = WINDOW_WIDTH - PLAYER_MARGIN - PLAYER_WIDTH,
        .y = (int)(player2.yPosition) - PLAYER_HEIGHT / 2,
		.w = PLAYER_WIDTH,
		.h = PLAYER_HEIGHT};
	SDL_RenderFillRect(rend, &p2rect);
	SDL_RenderDrawRect(rend, &p2rect);
}

void	doInput(void)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break ;
		default:
			break ;
		}
	}
}

void	cleanup(void)
{
	if (rend)
	{
		SDL_DestroyRenderer(rend);
	}
	if (win)
	{
		SDL_DestroyWindow(win);
	}
	SDL_Quit();
}
