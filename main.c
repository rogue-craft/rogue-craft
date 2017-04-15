#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <parson.h>
#include "src/level/level.h"
#include "src/level/camera.h"
#include "config/config.h"
#include "src/player/inventory.h"
#include "src/loop.h"
#include "src/environment.h"


static void init(void)
{
    setlocale(LC_ALL, "en_US.UTF-8");
    srand((unsigned) time(NULL));
    json_set_allocation_functions((JSON_Malloc_Function) allocate, release);

    profiler_init();
    ncurses_init();
    mouse_init();
    panel_init();

    list_node_pool_init();
    item_pool_init();
    cell_pool_init();
    lighted_cell_pool_init();

    color_init();
    item_load();
    cell_load();
    level_load();

}

static void cleanup(Player *player)
{
    ncurses_cleanup();
    panel_cleanup();
    item_pool_cleanup();
    level_free(player->level);
    cell_pool_cleanup();
    lighted_cell_pool_cleanup();

    player_free(player);
    item_unload();
    cell_unload();
    level_unload();
    color_cleanup();

    list_node_pool_cleanup();
    profiler_cleanup();
}


static void check_env(void)
{
    if (!has_mouse()) {
        fatal("Your terminal or ncurses version has no mouse support.")
    }

    if (!has_colors() || !can_change_color()) {
        fatal("Please make sure that your terminal has 256 color support.");
    }
}

Player *load_player(void)
{
    Camera camera;
    Size size = size_new(300, 300);
    Level *level = level_new(size);
    Player *player = player_new(level, &camera);
    player_position_on_level(player);

    return player;
}

int main(int arc, char *argv[])
{
    env_setup(arc, argv);

    init();
    check_env();

    Player *player = load_player();
    loop_run(player);
    cleanup(player);

    return 0;
}
