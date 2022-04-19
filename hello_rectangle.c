#define USING_NAMESPACE_P8G
#include "p8g.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PARTICLE_COUNT 20

#define WIDTH 400
#define HEIGHT 400

time_t t;

typedef struct _Particle {
  float x, y;
  float vx, vy;
} Particle;

Particle particles[PARTICLE_COUNT];

bool outOfBoundsX(Particle *p) {
  return p->x < 0 || p->x > WIDTH;
}

bool outOfBoundsY(Particle *p) {
  return p->y < 0 || p->y > HEIGHT;
}

void applyForce(Particle *p, float fx, float fy) {
  p->vx += fx;
  p->vy += fy;
}

void draw(void) {
  background(100);

  for (int i = 0; i < PARTICLE_COUNT; i++) {
    Particle *p = &particles[i];

    applyForce(p, 0, 0.1);

    p->x += p->vx;
    p->y += p->vy;

    if (outOfBoundsX(p)) {
      p->vx = p->vx * -0.9;
      p->x += p->vx;
    }

    if (outOfBoundsY(p)) {
      p->vy = p->vy * -0.9;
      p->y += p->vy;
    }

    ellipse(p->x, p->y, 10, 10);
  }
}

int main(void) {
  srand((unsigned) time(&t));

  for (int i = 0; i < PARTICLE_COUNT; i++) {
    particles[i].x = rand() % WIDTH;
    particles[i].y = rand() % HEIGHT;

    particles[i].vx = (rand() % 10 - 5) / 10.0;
    particles[i].vy = (rand() % 10 - 5) / 10.0;
  }

  run(WIDTH, HEIGHT, "Hello particle!");
  return 0;
}