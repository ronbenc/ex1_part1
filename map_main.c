#include "map.h"
#include <stdio.h>

int main()
{
    Map map = mapCreate();
    mapPut(map, "123", "abc");
    mapPut(map, "456", "def");
    mapPut(map, "780", "ghi");
    mapPut(map, "111", "aaa");
    
    printf("%s\n", mapGet(map, "123"));
    //Itay made a nonsubstantial edit
    int i = 5;
    
    return 0;
}

