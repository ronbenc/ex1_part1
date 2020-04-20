#include "map.h"
#include <stdio.h>
#include <assert.h>
#include "test_utilities.h"

int main()
{
    Map map = mapCreate();

    char* key1 = "key1";
    mapPut(map, key1, "123");
    const char *super_long_string =
        "Hi— I’m Ted Mosby. And exactly 45 days from now you and I are "
        "going to meet and we’re going to fall in love and we’re going to "
        "get married and we’re going to have 2 kids and we’re going to "
        "love them and each other so much. All that is 45 days away, but "
        "I’m here now I guess because… I want those extra 45 days with "
        "you. I want each one of them. Look and if I can’t have them I’ll "
        "take the 45 seconds before your boyfriend shows up and punches me "
        "in the face, because… I love you. I’m always gonna love you, til "
        "the end of my days and beyond. You’ll see.Hi— I’m Ted Mosby. And "
        "exactly 45 days from now you and I are "
        "going to meet and we’re going to fall in love and we’re going to "
        "get married and we’re going to have 2 kids and we’re going to "
        "love them and each other so much. All that is 45 days away, but "
        "I’m here now I guess because… I want those extra 45 days with "
        "you. I want each one of them. Look and if I can’t have them I’ll "
        "take the 45 seconds before your boyfriend shows up and punches me "
        "in the face, because… I love you. I’m always gonna love you, til "
        "the end of my days and beyond. You’ll see.Hi— I’m Ted Mosby. And "
        "exactly 45 days from now you and I are "
        "going to meet and we’re going to fall in love and we’re going to "
        "get married and we’re going to have 2 kids and we’re going to "
        "love them and each other so much. All that is 45 days away, but "
        "I’m here now I guess because… I want those extra 45 days with "
        "you. I want each one of them. Look and if I can’t have them I’ll "
        "take the 45 seconds before your boyfriend shows up and punches me "
        "in the face, because… I love you. I’m always gonna love you, til "
        "the end of my days and beyond. You’ll see.Hi— I’m Ted Mosby. And "
        "exactly 45 days from now you and I are "
        "going to meet and we’re going to fall in love and we’re going to "
        "get married and we’re going to have 2 kids and we’re going to "
        "love them and each other so much. All that is 45 days away, but "
        "I’m here now I guess because… I want those extra 45 days with "
        "you. I want each one of them. Look and if I can’t have them I’ll "
        "take the 45 seconds before your boyfriend shows up and punches me "
        "in the face, because… I love you. I’m always gonna love you, til "
        "the end of my days and beyond. You’ll see.Hi— I’m Ted Mosby. And "
        "exactly 45 days from now you and I are "
        "going to meet and we’re going to fall in love and we’re going to "
        "get married and we’re going to have 2 kids and we’re going to "
        "love them and each other so much. All that is 45 days away, but "
        "I’m here now I guess because… I want those extra 45 days with "
        "you. I want each one of them. Look and if I can’t have them I’ll "
        "take the 45 seconds before your boyfriend shows up and punches me "
        "in the face, because… I love you. I’m always gonna love you, til "
        "the end of my days and beyond. You’ll see.";
    ASSERT_TEST(mapPut(map, key1, super_long_string) == MAP_SUCCESS);
    ASSERT_TEST(strcmp(mapGet(map, key1), super_long_string) == 0);
    
    return 0;
}

