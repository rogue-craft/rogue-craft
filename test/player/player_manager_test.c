#include "player/player.h"
#include "../unit_test.h"
#include "../fixture.h"


MU_TEST(test_new_player)
{
    Level *level = fixture_level();

    Player *player = player_new(level);
    Point prev = player->position.previous;
    Point curr = player->position.current;

    mu_assert(HOLLOW == level->cells[prev.y][prev.x]->type, "Starting left_upper should Hollow");

    mu_assert_int_eq(prev.y, curr.y);
    mu_assert_int_eq(prev.x, curr.x);

    player_free(player);
    fixture_level_free(level);
}

void run_player_manager_test(void)
{
    TEST_NAME("Player Manager");

    MU_RUN_TEST(test_new_player);

    MU_REPORT();
}
