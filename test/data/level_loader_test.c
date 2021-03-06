#include "../unit_test.h"
#include "../../src/level/level.h"
#include "../../config/config.h"


static void assert_probability(void)
{
    mu_assert_int_eq(1, LEVEL_PROBABILITY.count);
    mu_assert_int_eq(10, LEVEL_PROBABILITY.items[0].chance);

    LevelConfig *cfg = LEVEL_PROBABILITY.items[0].value;
    mu_assert_int_eq(CELLULAR, cfg->type);

    mu_assert_int_eq(1, cfg->cells.hollow.count);
    mu_assert(cell_registry_get("hollow.default") == cfg->cells.hollow.items[0].value, "");

    mu_assert_int_eq(2, cfg->cells.solid.count);
    mu_assert(cell_registry_get("stone.cobble") == cfg->cells.solid.items[0].value, "");
    mu_assert(cell_registry_get("stone.mossy") == cfg->cells.solid.items[1].value, "");
}

MU_TEST(test_cache)
{
    level_unload();

    char *from = DIR_FIXTURE"/resources/levels/levels.json";
    char *to = DIR_FIXTURE"/resources/tmp/levels.json";

    rename(from, to);

    level_load();
    assert_probability();

    rename(to, from);
}

MU_TEST(test_load)
{
    cell_registry_load();
    level_load();

    assert_probability();

    level_unload();
    cell_registry_unload();
}

void run_level_loader_test(void)
{
    TEST_NAME("Level Loader");

    MU_RUN_TEST(test_load);

    MU_REPORT();
}
