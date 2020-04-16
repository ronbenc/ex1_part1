#include "map.h"
#include <stdio.h>

int main()
{
    Map map = mapCreate();
    mapPut(map, "123", "abc");
    mapPut(map, "456", "def");
    mapPut(map, "780", "ghi");
    mapPut(map, "111", "aaa");

    return 0;
}

