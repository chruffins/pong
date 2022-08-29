#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_audio.h>
#include "pong_gui.h"

int main() {
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_init_primitives_addon();

    run_pong_gui();

    return 0;
}