#include "unit_test.h"
#include "../src/player/player.h"
#include "fixture.h"
#include "../config/config.h"


static void assert_position(Player player, int y, int x)
{
    Point position = player.position.current;

    mu_assert_double_eq(y, position.y);
    mu_assert_double_eq(x, position.x);
}

MU_TEST(test_movement)
{
    Player player;
    player.level = fixture_level();
    player.cell.prototype.type = PLAYER;
    player.cell.prototype.in_registry = true;
    player.cell.previous = &player.level->registry.hollow.cells[0];
    player.position.previous = point_new(1, 1);
    player.position.current = point_new(1, 1);

    InputEvent event = {.player = &player, .input = KEY_NORTH};

    repeat(4,
           player_move(&event);
    )

    assert_position(player, 0, 1);

    event.input = KEY_SOUTH;
    player_move(&event);

    event.input = KEY_WEST;
    repeat(3,
           player_move(&event);
    )
    assert_position(player, 1, 0);

    Cell ***cells = player.level->cells;

    mu_assert(PLAYER == cells[1][0]->type, "The player should be there");

    mu_assert(
        HOLLOW == cells[1][1]->type &&
        HOLLOW == cells[1][2]->type,
        "Previous positions should be restored"
    );

    fixture_level_free(player.level);
}

void run_player_movement_test(void)
{
    TEST_NAME("Player Movement");

    MU_RUN_TEST(test_movement);

    MU_REPORT();
}
