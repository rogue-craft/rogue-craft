#include <mem_pool.h>
#include "lighting.h"


static MemPool *POOL;


typedef struct LightedCell {
    Point point;
    Cell *original;
    Cell *current;
    struct LightedCell *next;
} LightedCell;

struct Lighting {
    Sight *sight;
    Style style;
    LightedCell *lighted;
};


size_t lighted_cell_size(void)
{
    return sizeof(LightedCell);
}

void lighted_cell_pool_init(void)
{
    POOL = pool_init(sizeof(LightedCell), 100);
}

void lighted_cell_pool_cleanup(void)
{
    pool_destroy(POOL);
}

static LightedCell *light_cell(Lighting *lighting, Cell *original)
{
    LightedCell *lighted = pool_alloc(POOL);
    profile_lighted_cell(++);

    lighted->original = original;
    lighted->current = cell_clone(original);
    lighted->current->lighted = true;
    lighted->current->style = lighting->style;

    lighted->next = lighting->lighted;
    lighting->lighted = lighted;

    return lighted;
}

static void light_cells(Lighting *lighting)
{
    Point point;
    Cell *original;
    LightedCell *lighted;
    Cell ***cells = lighting->sight->level->cells;
    Sight *sight = lighting->sight;

    for (uint16_t i = 0; i < sight->count; i++) {
        point = sight->points[i];
        original = cells[point.y][point.x];

        if (HOLLOW == original->type) {
            lighted = light_cell(lighting, original);
            lighted->point = point;
            cells[point.y][point.x] = lighted->current;
        }
    }
}

Lighting *lighting_new(Level *level, Point source, uint16_t radius, Style style)
{
    Lighting *lighting = allocate(sizeof(Lighting));
    Sight *sight = sight_new(level, source, radius, EDGES);
    lighting->sight = sight;
    lighting->style = style;
    lighting->lighted = NULL;

    light_cells(lighting);

    return lighting;
}

static void free_cells(Lighting *lighting)
{
    Point point;
    Cell ***cells = lighting->sight->level->cells;
    LightedCell *tmp, *head = lighting->lighted;

    while (head) {
        tmp = head;
        head = head->next;

        point = tmp->point;
        cells[point.y][point.x] = tmp->original;

        cell_free_custom(tmp->current);
        pool_release(POOL, tmp);
        profile_lighted_cell(--);
    }
    lighting->lighted = NULL;
}

void lighting_update(Lighting *lighting, Point source, uint16_t radius)
{
    if (UPDATED == sight_update(lighting->sight, source, radius)) {
        /** It's ok to 'throw away' all the LightedCells at each update,
         * because we'll just grab them from the pool anyway */
        free_cells(lighting);
        light_cells(lighting);
    }
}

void lighting_free(Lighting *lighting)
{
    sight_free(lighting->sight);
    free_cells(lighting);
    release(lighting);
}

