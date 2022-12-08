// all structures defined here.
// Ball, Player vars are declared in main.c

typedef struct Ball{
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    int size;
}Ball;

typedef struct Player{
    int score; 
    float yPos;
}Player;

