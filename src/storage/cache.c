#include <unistd.h>
#include "cache.h"


#define path_of(name) ({                            \
    char _path[MAX_PATH];                            \
    sprintf(_path, "%s/%s.cache", DIRECTORY, name);  \
    _path;                                           \
})


static char *DIRECTORY;


void cache_init(char *dir)
{
    dir_check(dir);

    DIRECTORY = dir;
}

bool cache_exists(char *name)
{
    return file_exists(path_of(name));
}

bool cache_valid(Cache *cache, time_t value_modified)
{
    struct stat stats;
    stat(cache->path, &stats);

    return value_modified <= stats.st_mtim.tv_sec;
}

void cache_open(Cache *cache, char *name, size_t entry_size)
{
    cache->entry_size = entry_size;
    memcpy(cache->path, path_of(name), MAX_PATH);
    cache->file = file_open(cache->path, "ab+");
}

void cache_add(Cache *cache, void *entry)
{
    if (1 != fwrite(entry, cache->entry_size, 1, cache->file)) {
        fatal("Something went wrong while writing [%s] cache", cache->path);
    }
}

void cache_foreach(Cache *cache, Reader reader)
{
    char entry[cache->entry_size];

    rewind(cache->file);

    while (1 == fread(&entry, cache->entry_size, 1, cache->file)) {
        reader(&entry);
    }
}

void cache_clear(Cache *cache)
{
    fflush(cache->file);
    ftruncate(fileno(cache->file), 0);
}

void cache_delete(char *name)
{
    char *path = path_of(name);

    if (file_exists(path) && 0 != unlink(path)) {
        fatal("Unable to unlink [%s]", path);
    }
}

void cache_close(Cache *cache)
{
    fclose(cache->file);
    cache->file = NULL;
}