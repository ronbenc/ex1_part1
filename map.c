#include "map.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    char* key;
    char* value;
    struct node* next;
} *Node;

struct Map_t
{
    Node head;
    Node current;
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

    map->head = NULL;
    map->current = NULL;

    return map;
}

void mapDestroy(Map map)
{
    mapClear(map);
    free(map);
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
    Node new_node = malloc(sizeof(struct node)); //create new node

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
    new_node->next = map->head;
    map->head = new_node;

    return MAP_SUCCESS;
}

char* mapGet(Map map, const char* key)
{
    if(!map || !key)
        return NULL; 

    MAP_FOREACH(key_iterator, map)
    {
        if(strcmp(key_iterator, key)==0)
        {
            return map->current->value;
        }       
    }

    return NULL;   
}

MapResult mapRemove(Map map, const char* key);

char* mapGetFirst(Map map)
{
    if(!map || !(map->head))
        return NULL;

    // update current for the iterator
    map->current = map->head;

    return map->head->key;
}

char* mapGetNext(Map map)
{
    if(!map || !(map->current) || !(map->current->next))
        return NULL;

    // update current for the iterator
    map->current = map->current->next;
 
    return map->current->key;
}

MapResult mapClear(Map map)
{
    if(!map)
        return MAP_NULL_ARGUMENT;

    while(map->head)
    {
        Node tmp = map->head->next;
        free(map->head->key);
        free(map->head->value);
        free(map->head);
        map->head = tmp;
    }

    map->current = NULL;

    return MAP_SUCCESS;
}

void tmpMapPrint(Map map)
{
    MAP_FOREACH(key_iterator, map)
    {
        printf("%s, %s\n", key_iterator, map->current->value);
    }
}