#include "map.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Map_t
{
    char* key;
    char* value;
    struct Map_t* next;
};

static char* copyString(const char* str)
{
    char* newStr = malloc(strlen(str) + 1);
    if (newStr == NULL) return NULL;
    return strcpy(newStr, str);
}

Map mapCreate()
{
    Map map = malloc(sizeof(*map));
    if(!map)
    {
        return NULL;
    }

    map->next = NULL;
    return map;
}

void mapDestroy(Map map) //recursive
{
    Map nexDestroy = map->next;
    free(map); //first node is unpopulated so no need to free key and value
    for(map = map->next; map; map = map->next)
    {
        map = nexDestroy;
        free(map->key);
        free(map->value);
        nexDestroy = map->next;
    }
    
}


Map mapCopy(Map map);
int mapGetSize(Map map);
bool mapContains(Map map, const char* key);

MapResult mapPut(Map map, const char* key, const char* data)
{
    if(!map || !key || !data)
        return MAP_NULL_ARGUMENT;

    char* newValue = copyString(data);
    assert(newValue != NULL && strcmp(newValue, data) == 0);
    /*
    if(mapContains)// key exists 
    {
        MAP_FOREACH(iterator_key, map)
        {
            if(strcmp(key, iterator_key)==0)
            {
                free(mapGet(map, key));
                mapGet(map, key) = newValue;
                return MAP_SUCCESS;
            }
        }
    }
    */
    // key doesn't exist in list. we will add it to the head
    Map new_node = mapCreate(); //create new node
    if(!new_node)
    {
        return MAP_OUT_OF_MEMORY;
    }

    char* newKey = copyString(key);
    assert(newKey != NULL && strcmp(newKey, key) == 0);

    // assuming the head of the list is an unpopulated node.
    // populate the current head node and insert an unpopulated node in the head of the list.
    new_node->key = newKey;
    new_node->value = newValue;
    new_node->next = map->next;
    map->next = new_node;

    return MAP_SUCCESS;
}

char* mapGet(Map map, const char* key)
{
    if(!key)
        return NULL; 

    for(map = map->next; map && strcmp(key, map->key); map = map->next);

    if(map)
    {
        assert(map->value);
        return map->value;
    }

    return NULL;   
}

MapResult mapRemove(Map map, const char* key);

char* mapGetFirst(Map map)
{
    if(!map || !(map->next))
        return NULL;

    // skip the dummy node pointed by map
    return map->next->key;
}

char* mapGetNext(Map map)
{
    return mapGetFirst(map);
}

MapResult mapClear(Map map);

void tmpMapPrint(Map map)
{
    MAP_FOREACH(key_iterator, map)
    {
        char* currValue = mapGet(map, key_iterator);

        printf("%s, %s\n", key_iterator, currValue);
        // printf("%s\n", key_iterator);
    }

}