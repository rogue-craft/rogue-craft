#ifndef ROGUECRAFT_DEFAULTS_H
#define ROGUECRAFT_DEFAULTS_H


#include "../src/color.h"
#include "../src/level/cell.h"
#include "../src/level/level.h"
#include "../src/player/player.h"
#include "../src/player/item.h"
#include "../src/randomization.h"
#include "../src/event.h"


extern Listener LISTENERS[EVENT_TYPE_NUM][EVENT_LISTENER_MAX];


/**
 * CONFIGS
 */
#define CONFIG_LEVELS "levels"
#define CONFIG_ITEMS "items"
#define CONFIG_CELLS "cells"

/**
 * PLAYER
 */
#define PLAYER_CHAR                     '@'
#define PLAYER_DEFAULT_INVENTORY_SIZE   20
#define PLAYER_DEFAULT_EYESIGHT         6

extern PlayerStateConfig PLAYER_STATE_CONFIG;


/**
 * INVENTORY
 */
#define INVENTORY_SHORTCUT_FIRST '1'
#define INVENTORY_SHORTCUT_NUM 5
#define INVENTORY_SELECTED_STYLE COLOR_PAIR(COLOR_RED_F)


/**
 * KEYBINDINGS
 */
#define KEY_NORTH       'w'
#define KEY_EAST        'd'
#define KEY_SOUTH       's'
#define KEY_WEST        'a'
#define KEY_ESCAPE       KEY_F(2)
#define KEY_INVENTORY   'i'
#define KEY_USE         'f'

/**
 * MATERIAL
 */
extern uint16_t MATERIAL_STRENGTH[MATERIAL_NUM];


/**
 * LEVEL
 */
#define LEVEL_ITEM_COUNT(level) \
    (uint16_t) ((level->size.height * level->size.width) / 200);


extern Probability LEVEL_PROBABILITY;


/**
 * ITEMS
 */
extern Probability ITEM_TYPE_PROBABILITY;

extern Probability ITEM_CONSUMABLE_PROBABILITY;

extern Probability ITEM_TOOL_PROBABILITY;

extern Probability ITEM_LIGHT_SOURCE_PROBABILITY;


#endif
