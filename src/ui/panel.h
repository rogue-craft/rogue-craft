#ifndef ROGUE_CRAFT_PANEL_H
#define ROGUE_CRAFT_PANEL_H


#include <panel.h>


typedef struct Inventory Inventory;

typedef struct Player Player;


typedef enum {
    PANEL_INVENTORY
} PanelType;

typedef struct {
    PanelType type;
    union {
        Inventory *inventory;
    };
} PanelInfo;

typedef struct {
    int input;
    Player *player;
    const PanelInfo *info;
} PanelInputEvent;


void panel_init(void);

PANEL *panel_push_new(WINDOW *win, const PanelInfo info);

bool panel_is_open(void);

void panel_hide(void);

void panel_show(void);

const PanelInfo *panel_describe_top(void);

void panel_close_top(int input, Player *player);

void panel_cleanup(void);


#endif
