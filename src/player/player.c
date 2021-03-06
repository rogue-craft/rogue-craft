#include <time.h>
#include <util/timer.h>
#include "memory/memory.h"
#include "inventory/inventory.h"
#include "player.h"


static void init_modifiers(Player *player)
{
    Modifiers *modifiers = &player->state.modifiers;

    modifiers->traveled = 0;
    modifiers->dealt_damage = 0;
    modifiers->timestamp.fatigue = time(NULL);
    modifiers->timestamp.fatigue_damage = time(NULL);
}

static void add_default_state(Player *player)
{
    State *map = player->state.map;

    map[HEALTH] = (State) {
        .current = 100, .max = 100,
        .name = "Health", .style  = COLOR_PAIR(COLOR_RED_F)
    };

    map[STAMINA] = (State) {
        .current = 100, .max = 100,
        .name = "Stamina", .style = COLOR_PAIR(COLOR_GREEN_F)
    };

    map[HUNGER] = (State) {
        .current = 0, .max = 100,
        .name = "Hunger", .style = COLOR_PAIR(COLOR_YELLOW_F)
    };

    map[THIRST] = (State) {
        .current = 0, .max = 100,
        .name = "Thirst", .style = COLOR_PAIR(COLOR_BLUE_F)
    };

    TimerArgs args = {.ptr = {player, &PLAYER_STATE_CONFIG}};
    player->state.timer = timer_new(1000, player_state_update, args);
}

static void find_starting_point(Player *player)
{
    Level *level = player->level;
    Point point = level_rand_hollow(level);

    player->cell.occupied = level->cells[point.y][point.x];
    player->position.previous = point;
    player->position.current = point;
}

Player *player_new(Level *level)
{
    Player *player = mem_alloc(sizeof(Player));
    player->level = level;

    add_default_state(player);
    init_modifiers(player);

    player->attributes.speed = 1;
    player->attributes.eye_sight = 1;

    player->cell.prototype.type = PLAYER;
    player->cell.prototype.style = COLOR_PAIR(COLOR_RED_F);
    player->cell.prototype.chr = PLAYER_CHAR;
    player->cell.prototype.in_registry = true;

    find_starting_point(player);

    player->inventory = inventory_new(PLAYER_DEFAULT_INVENTORY_SIZE);
    player->sight = sight_new(level, player->position.current, player_eyesight(player));

    player_init_movement(player);

    return player;
}

void player_free(Player *player)
{
    timer_free(player->movement.timer);
    timer_free(player->state.timer);
    inventory_free(player->inventory);
    sight_free(player->sight);
    mem_dealloc(player);
}

void player_sight_update(Player *player)
{
    sight_update(player->sight, player->position.current, player_eyesight(player));
}
