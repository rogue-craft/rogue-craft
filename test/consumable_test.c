#include "unit_test.h"
#include "../src/player/item.h"


MU_TEST(test_non_consumable)
{
    Item item;
    item.type = MELEE;

    mu_assert(IE_INVALID_ARGUMENT == item_consume(&item, NULL), "Should give Invalid Arg");
}

static Item create_item(bool persistent)
{
    return (Item) {
        .type = CONSUMABLE,
        .consumable = (Consumable) {
            .type = HEALTH,
            .persistent = persistent,
            .value = 10
        }
    };
}

void setup_player(Player *player)
{
    player->attr.hp.limit = 100;
    player->attr.hp.current = 90;
    player->attr.type_map[HEALTH] = &player->attr.hp;
}

MU_TEST(test_persistent)
{
    Item item = create_item(true);

    Player player;
    setup_player(&player);

    mu_assert(IE_CONSUMED == item_consume(&item, &player), "Item should be consumbed");
    mu_assert_int_eq(110, player.attr.hp.limit);
}

MU_TEST(test_non_persistent)
{
    Item item = create_item(false);
    Player player;
    setup_player(&player);

    mu_assert(IE_CONSUMED == item_consume(&item, &player), "Should be consumed");
    mu_assert_int_eq(100, player.attr.hp.current);
}

MU_TEST(test_partial_consume)
{
    Item item = create_item(false);
    Player player;
    setup_player(&player);
    player.attr.hp.current = 95;

    mu_assert(IE_REPEAT == item_consume(&item, &player), "Should be partially consumed");
    mu_assert_int_eq(100, player.attr.hp.current);
    mu_assert_int_eq(5, item.consumable.value);
}

void run_consumable_test(void)
{
    TEST_NAME("Consumable Item");

    MU_RUN_TEST(test_non_consumable);
    MU_RUN_TEST(test_persistent);
    MU_RUN_TEST(test_non_persistent);
    MU_RUN_TEST(test_partial_consume);

    MU_REPORT();
}
