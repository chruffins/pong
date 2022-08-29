#include "pong_gui.h"

static void setup_game(game* g) {
    setup_ball(&(g->pball));
    g->plr1y = MIDDLE;
    g->plr2y = MIDDLE;
    g->plr1dir = 0;
    g->plr2dir = 0;
}

static void setup_ball(ball* b) {
    b->position = vector2_create(RIGHT/2, MIDDLE);
    b->velocity = vector2_create(5,5);
}

static void process_input(game* g, int down, int key) {
    // down = -1 or 1
    switch (key)
    {
    case 23:
        g->plr1dir -= down * 1;
        break;
    case 19:
        g->plr1dir += down * 1;
        break;
    case 84:
        g->plr2dir -= down * 1;
        break;
    case 85:
        g->plr2dir += down * 1;
        break;
    default:
        break;
    }
}

static void move_bars(game* g) {
    if (g->plr1dir > 0) {
        g->plr1y = fminf(g->plr1y + 10, BOTTOM-50);
    } else if (g->plr1dir < 0) {
        g->plr1y = fmaxf(g->plr1y - 10, 50);
    }
    if (g->plr2dir > 0) {
        g->plr2y = fminf(g->plr2y + 10, BOTTOM-50);
    } else if (g->plr2dir < 0) {
        g->plr2y = fmaxf(g->plr2y - 10, 50);
    }
}

bool in_range(float x, float a, float b) {
    return x >= a && x <= b;
}

static void check_collision(game* g) {
    // do top and bottom
    ball b = g->pball;
    vector2 future_pos = vector2_addv2(b.position, b.velocity);
    
    if (future_pos.y >= BOTTOM || future_pos.y <= 0) {
        b.velocity->y *= -1;
        if (rand() % 2 == 0) {
            vector2_smult(b.velocity, 1.05);
        }
    }
    if ((future_pos.x >= RIGHT - 15 && in_range(future_pos.y, g->plr2y - 50, g->plr2y + 50)) || (future_pos.x <= 15 && in_range(future_pos.y, g->plr1y - 50, g->plr1y + 50))) {
        b.velocity->x *= -1;
    }
    if (future_pos.x >= RIGHT || future_pos.x <= 0) {
        // give point actually
        printf("Fuck You");
        b.position->x = RIGHT / 2;
        b.position->y = MIDDLE;
        b.velocity->x *= -1;
    }
}

static void move_ball(game* g) {
    check_collision(g);
    vector2_iaddv2(g->pball.position, g->pball.velocity);
}

static void draw_bars(game* g) {
    // player 1 first
    al_draw_filled_rectangle(10, g->plr1y - 50, 15, g->plr1y + 50, al_map_rgb(255,255,255));
    al_draw_filled_rectangle(RIGHT - 15, g->plr2y - 50, RIGHT - 10, g->plr2y + 50, al_map_rgb(255,255,255));
}

static void draw_ball(game* g) {
    al_draw_circle(g->pball.position->x, g->pball.position->y, 5, al_map_rgb(255,255,255), 4);
}

void run_pong_gui() {
    // game logic
    game g;
    setup_game(&g);

    printf("test");

    // gui stuff
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(RIGHT, BOTTOM);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;
        else if((event.type == ALLEGRO_EVENT_KEY_DOWN))
            process_input(&g, 1, event.keyboard.keycode);
        else if((event.type == ALLEGRO_EVENT_KEY_UP)) {
            process_input(&g, -1, event.keyboard.keycode);
            //printf("%d\n", event.keyboard.keycode); // 23 - w 19 - s 
        }
        if(redraw && al_is_event_queue_empty(queue))
        {
            move_bars(&g);
            move_ball(&g);

            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_bars(&g);
            draw_ball(&g);

            //al_draw_filled_rectangle(10, MIDDLE - 50, 15, MIDDLE + 50, al_map_rgb(255,255,255));
            //al_draw_filled_rectangle(RIGHT - 15, MIDDLE - 50, RIGHT - 10, MIDDLE + 50, al_map_rgb(255,255,255));

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    printf("The lunatic is on the grass\n");
}