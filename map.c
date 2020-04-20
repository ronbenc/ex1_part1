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

//alocates a new string and copies given string data
static char* copyString(const char* str)
{
    char* newStr = malloc(strlen(str) + 1);
    if (newStr == NULL) return NULL;
    return strcpy(newStr, str);
}

//alocate a new node and assigns key adn value 
static Node nodeCreate(const char* key, const char* value)
{
    Node new_node = malloc(sizeof(struct node)); //create new node
    if(!new_node)
        return NULL;

    new_node->key = copyString(key);
    new_node->value = copyString(value);

    if(!new_node->key || !new_node->value)
        return NULL;
    
    return new_node;
}

static void nodeDestroy(Node node)
{
    assert(node);
    free(node->key);
    free(node->value);
    free(node);
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

Map mapCopy(Map map)
{
    Map new_map = mapCreate();
    if(new_map == NULL)
        return NULL;
    
    MAP_FOREACH(key_iterator, map)
    {
        Node prev_head = new_map->head;
        new_map->head = nodeCreate(map->current->key, map->current->value);     
        if(new_map->head == NULL)
            return NULL;

        new_map->head->next = prev_head;
    }
    new_map->current = NULL;
    return new_map;
}

int mapGetSize(Map map)
{
    if(map == NULL)
        return -1;
    
    Node save_curr = map->current;
    int len=0;;
    MAP_FOREACH(iterator, map)
    {
        len++;
    }
    map->current = save_curr;
    return len;
}

bool mapContains(Map map, const char* key)
{
    Node save_curr = map->current;
    bool flag = false;
    MAP_FOREACH(key_iterator, map)
    {
        if(strcmp(key_iterator, key) == 0)
        {
            flag = true;
            break; 
        }
    }
    map->current = save_curr;
    return flag;

}

MapResult mapPut(Map map, const char* key, const char* data)
{
    if(!map || !key || !data)
        return MAP_NULL_ARGUMENT;

    char* curr_value = mapGet(map, key);
    if(curr_value) //key exists in the list. we will update its value;
    {
        free(curr_value);
        curr_value = copyString(data);
        if(!curr_value)
            return MAP_OUT_OF_MEMORY;

        return MAP_SUCCESS;
    }

    // key doesn't exists in list. we will add it to the head adn assign key and value
    Node new_node = nodeCreate(key, data);

    if(!new_node)
    return MAP_OUT_OF_MEMORY;

    new_node->next = map->head;
    map->head = new_node;

    return MAP_SUCCESS;
}

char* mapGet(Map map, const char* key)
{
    if(map == NULL || key == NULL)
        return NULL; 

    Node save_curr = map->current;
    char* value = NULL;
    MAP_FOREACH(key_iterator, map)
    {
        if(strcmp(key_iterator, key) == 0)
        {
            value = map->current->value;
            break;
        }
    }

    map->current = save_curr;
    return value;   
}

MapResult mapRemove(Map map, const char* key)
{
    if(!map || !key)
        return MAP_NULL_ARGUMENT;

    // Concern#1: search the key and update both map->current and previous_node
    Node previous_node = NULL;

    map->current = map->head;
    while(map->current && strcmp(map->current->key, key))
    {
        previous_node = map->current;
        map->current = map->current->next;
    }

    if(!map->current)
        return MAP_ITEM_DOES_NOT_EXIST;

    // Concern#2: handle special case of key found at the head of the list
    if(previous_node)
    {
        assert(map->current != map->head);
        previous_node->next = map->current->next;
    } 
    else
    {
        assert(map->current == map->head);
        map->head = map->head->next;
    }

    // Concern #3: free the memory of the found node
    nodeDestroy(map->current);

    return MAP_SUCCESS;
}

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

    while (map->head)
    {
        Node tmp = map->head->next;
        nodeDestroy(map->head);
        map->head = tmp;
    }
    
    map->head = NULL;
    return MAP_SUCCESS;
}

void tmpMapPrint(Map map)
{
    MAP_FOREACH(key_iterator, map)
    {
        printf("%s, %s\n", key_iterator, map->current->value);
    }
}