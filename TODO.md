#### TODO:
* [PLAYER] Inventory improvements:
    * Shortcuts
        * From the full view set the shortcuts, but if it's not the Player's
        Inventory, the Item need to be added, if the shortcut already had an Item,
        it has to be replaced with the other.
    * Remove items
    * More inventory types (chest, bag etc.) (inventory_player_display, inventory_display)
* [PLAYER] Normalize the Player's speed
* [LEVEL] Lighting/Light source:
    * Portable type
    * More tests
* [LEVEL] Level JSON cache
* [MISC] Probability.items should be dynamic
* [MISC] Timers for periodic executions
* [UI] Multiple panels
* [BE AWARE] If there will be more than one thread, the static buffer in `environment.c` will cause problems
* [BUILD] DIR_FIXTURE as env var
* [BUILD] DEB package

#### Possible optimizations:
* Sight point lookup