#include "map.h"
#include <stdio.h>

int main()
{
    Map map = mapCreate();
    mapPut(map, "123", "abc");
    mapPut(map, "456", "def");
    //MAP_FOREACH(i, map)
    tmpMapPrint(map);
    mapDestroy(map);
    printf("destroyed");
    return 0;
}

