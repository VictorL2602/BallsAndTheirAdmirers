#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

// indstillinger til programvinduet
#define WIDTH 1000
#define HEIGHT 1000
#define TITLE "Balls and their admirers"
#define BALL_COUNT 100
#define FPS 144 // bare for sjov
#define VEL_MAX 5
#define RADIUS_MAX 20
#define RADIUS_MIN 5

// kuglernes farve
Color COLORS[] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN,
};

// Definition of Ball
// Ball stores state and other properties
// YOUR CODE HERE
// struct til at gemme data om en kugle
typedef struct Ball {
  float posx, posy;
  float velx, vely;
  float radius;
  Color color;
  struct Ball *follows;
} Ball;

// array med alle kugler
Ball balls[BALL_COUNT];

// Initialize all `balls`
// sætter tilfældige værdier for alle kugler
void init_balls_random() {
  // YOUR CODE HERE
  for (size_t i = 0; i < BALL_COUNT; i++) {
    balls[i].radius = GetRandomValue(RADIUS_MIN, RADIUS_MAX);
    balls[i].posx = GetRandomValue(balls[i].radius, WIDTH - balls[i].radius);
    balls[i].posy = GetRandomValue(balls[i].radius, HEIGHT - balls[i].radius);
    balls[i].color = COLORS[GetRandomValue(0, 20)];
    balls[i].velx = GetRandomValue(-VEL_MAX, VEL_MAX);
    balls[i].vely = GetRandomValue(-VEL_MAX, VEL_MAX);
  }
}

// Initializes a ball with random values
// vælger en tilfældig kugle som leder, hvor de andre kugler følger den
void init_ball_random(void) {

  size_t leader = GetRandomValue(0, BALL_COUNT - 1);

  for (size_t i = 0; i < BALL_COUNT; i++) {

    balls[i].follows = &balls[leader];
  }
}

// vælger en kugle
void draw_ball(Ball *p) {
  //
  DrawCircle(p->posx, p->posy, p->radius, p->color);
}

// tegner alle kugler og linjer til deres leder
void balls_draw(void) {
  for (size_t i = 0; i < BALL_COUNT; i++) {
    draw_ball(&balls[i]);
    // dette viser linjer ind til lederen så man kan følge med i animationen
    // (ekstra fordi jeg gerne ville se lederen)
    DrawLine(balls[i].posx, balls[i].posy, balls[i].follows->posx,
             balls[i].follows->posy, Fade(BLACK, 0.2f));
  }
}

// opdaterer kuglernes position og bevægelse
void update_pos(void) {

  float time = GetFrameTime(); // hvor lang tid siden sidste frame
  for (size_t i = 0; i < BALL_COUNT; i++) {
    // flyt kuglen
    balls[i].posx += balls[i].velx;
    balls[i].posy += balls[i].vely;

    // retning mod lederen
    float dx = balls[i].follows->posx - balls[i].posx;
    float dy = balls[i].follows->posy - balls[i].posy;

    // kuglens tiltrækning mod lederen
    float follow_factor = 0.005;
    balls[i].velx += dx * follow_factor * time;
    balls[i].vely += dy * follow_factor * time;

    // aftagende fart for kuglerne
    float dampening = 0.999f;
    balls[i].velx *= dampening;
    balls[i].vely *= dampening;

    // tjek for kollision mod vinduets vægge
    if (balls[i].posx < balls[i].radius) {
      balls[i].posx = balls[i].radius;
      balls[i].velx = -balls[i].velx;
    } else if (balls[i].posx > WIDTH - balls[i].radius) {
      balls[i].posx = WIDTH - balls[i].radius;
      balls[i].velx = -balls[i].velx;
    }
    if (balls[i].posy < balls[i].radius) {
      balls[i].posy = balls[i].radius;
      balls[i].vely = -balls[i].vely;
    } else if (balls[i].posy > HEIGHT - balls[i].radius) {
      balls[i].posy = HEIGHT - balls[i].radius;
      balls[i].vely = -balls[i].vely;
    }
  }
}

int main() {
  InitWindow(WIDTH, HEIGHT, TITLE); // start vinduet
  SetTargetFPS(FPS);                // sæt FPS

  init_balls_random(); // lav kuglerne
  init_ball_random();  // vælg leder

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

    update_pos(); // opdater kugler
    BeginDrawing();
    // update_elements();
    ClearBackground(RAYWHITE);
    balls_draw(); // tegn kugler
    EndDrawing();
  }
}