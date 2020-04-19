#include "map.h"
#include <stdio.h>

int main()
{
    Map map = mapCreate();
    mapPut(map, "123", "abc");
    mapPut(map, "456", "def");
    mapPut(map, "789", "ghi");
    mapPut(map, "789", "asdfghjkk");

    mapRemove(map, "789");
    if(mapContains(map, "789"))
    {
        printf("contains");
    }
    else
    {
        printf("not");
    }
    
    
    //mapDestroy(map);
   // printf("%d\n", mapGetSize(map));

    return 0;
}

