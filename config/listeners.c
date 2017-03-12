#include "../src/event.h"
#include "../src/player/item.h"
#include "../src/player/inventory.h"


Listener LISTENERS[EVENT_TYPE_NUM][EVENT_LISTENER_MAX] = {
    [EVENT_CLICK] = {
        (Listener) level_interact
    },
    [EVENT_INTERACTION] = {
        (Listener) player_hit,
        (Listener) item_pickup
    },
    [EVENT_INPUT] = {
        (Listener) inventory_shortcut_select,
        (Listener) mouse_handler
    }
};
