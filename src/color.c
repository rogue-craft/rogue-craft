#include "../config/config.h"


static uint16_t LAST_PAIR = 100;
static Cache CACHE;


static void new_cached(CachedColor *color, Color fore, Color back)
{
    memset(color, 0, sizeof(CachedColor));

    color->id = LAST_PAIR;
    color->fore = fore;
    color->back = back;
}

ColorPair color_add(Color fore, Color back)
{
    init_pair(LAST_PAIR, fore, back);

    CachedColor color;
    new_cached(&color, fore, back);
    cache_add(&CACHE, &color);

    return COLOR_PAIR(LAST_PAIR++);
}

static void load_color(CachedColor *color)
{
    init_pair(color->id, color->fore, color->back);

    LAST_PAIR = max(LAST_PAIR, color->id);
}

void color_init(void)
{
    cache_open_colors(&CACHE);

    if (cache_is_empty(CACHE_COLORS)) {
        cache_foreach(&CACHE, (Reader) load_color);
    }

    init_pair(COLOR_PAIR_RED_F, COLOR_RED, -1);
    init_pair(COLOR_PAIR_GREEN_F, COLOR_GREEN, -1);
    init_pair(COLOR_PAIR_GREEN_B, -1, COLOR_GREEN);
    init_pair(COLOR_PAIR_BLUE_F, COLOR_BLUE, -1);
    init_pair(COLOR_PAIR_YELLOW_F, COLOR_YELLOW, -1);
    init_pair(COLOR_PAIR_GRAY_F, 8, -1);
    init_pair(COLOR_PAIR_DARK_GRAY_F, 235, -1);
    init_pair(COLOR_PAIR_BROWN_F, 94, -1);
    init_pair(COLOR_PAIR_DARK_GREEN_F, 22, -1);
    init_pair(COLOR_PAIR_CLARET_F, 52, -1);
    init_pair(COLOR_PAIR_NONE, -1, -1);
    init_pair(COLOR_PAIR_DARK_GREEN_B, -1, 22);
    init_pair(COLOR_PAIR_BROWN_B, -1, 94);
    init_pair(COLOR_PAIR_ORANGE_B, -1, 202);
    init_pair(COLOR_PAIR_YELLOW_B, -1, COLOR_YELLOW);
}

uint16_t color_last(void)
{
    return LAST_PAIR;
}

void color_cleanup(void)
{
    cache_close(&CACHE);
}
