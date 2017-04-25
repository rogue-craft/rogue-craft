#include "../player/inventory.h"


#define SHORTCUT_LENGTH 13


static void display_shortcut(Inventory *inventory, WINDOW *win, uint16_t i)
{
    List *items = inventory->items;
    Item *item = items->get(items, i);

    styled_if(win, INVENTORY_SELECTED_STYLE, i == inventory->selected,
              wprintw(win, "| %d - ", i + 1);
    )

    if (item) {
        styled(win, item->style,
               wprintw(win, "%lc", item->chr);
        );
        wprintw(win, " %d ", item_value(item));
    }
}

void inventory_shortcut_display(Inventory *inventory)
{
    WINDOW *win = WINDOW_INVENTORY_SHORTCUT;

    wclear(win);
    wmove(win, 1, 1);

    int displayed = min(getmaxx(win) / SHORTCUT_LENGTH, INVENTORY_SHORTCUT_NUM);
    int length = getmaxx(win) / displayed;

    for (uint16_t i = 0; i < displayed; i++) {
        display_shortcut(inventory, win, i);
        wmove(win, 1, (i + 1) * length);
    }

    refresh_boxed(win);
}