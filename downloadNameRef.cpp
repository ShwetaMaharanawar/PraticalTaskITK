#include "ass_header.h"

void downloadNameRef()
{

    // Step 1: Get the item key and revision ID from the command line arguments
    char* search_id = ITK_ask_cli_argument("-i=");  // Item key
    char* revision_id = ITK_ask_cli_argument("-r="); // Revision ID

    tag_t revision_tag = NULLTAG;

    // Step 2: Find Item revision
    int result1 = ITEM_find_rev(search_id, revision_id, &revision_tag);
    if (result1 != ITK_ok || revision_tag == NULLTAG) {
        printf("Item revision not found....\n");
        return;  // If revision tag is not found, return
    }
    else {
        printf("Item revision found....\n");
    }




	return;
}