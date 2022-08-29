#ifndef PONG_GUI_H
#define PONG_GUI_H

#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_audio.h>
#include<stdio.h>

#include"vector2.h"

#define RIGHT 800
#define BOTTOM 600
#define MIDDLE BOTTOM / 2

struct ball_t {
    vector2* position;
    vector2* velocity;
} typedef ball;

struct game_t {
    ball pball;
    float plr1y;
    float plr2y;
    int plr1dir;
    int plr2dir;
} typedef game;

static void setup_game(game*);
static void setup_ball(ball*);
static void process_input(game*, int, int);
static void check_collision(game*);
static void move_bars(game*);
static void move_ball(game*);
static void draw_bars(game*);
static void draw_ball(game*);
static void draw_score();
static void draw_pause_menu();
void run_pong_gui();

#endif