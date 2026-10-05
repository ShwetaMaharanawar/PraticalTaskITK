#include "ass_header.h"

void find_itemRevision() {


    // Step 1: Get the item key and revision ID from the command line arguments
    char* search_id = ITK_ask_cli_argument("-i=");  // Item key passed from command line
    char* revision_id = ITK_ask_cli_argument("-r=");   // Revision ID passed from command line

    tag_t item_tag = NULLTAG;  // To store the item tag
    tag_t revision_tag = NULLTAG;   // To store the revision tag

    if (search_id == NULL || revision_id == NULL) {
        printf("\nItem key or revision ID is missing...\n");
        return;
    }

    // Step 2: Use ITEM_find_rev to find the revision tag based on the item key and revision ID
    ITEM_find_rev(search_id, revision_id, &revision_tag);  // Finding revision tag using item and revision ID
    if (revision_tag == NULLTAG) {
        printf("Item revision not found....\n");
        return;  // If revision tag is not found, return
    }
    else {
        printf("Item revision found....\n");
    }

    // Step 3: Retrieve the item associated with the revision tag using ITEM_ask_item_of_rev
    ITEM_ask_item_of_rev(revision_tag, &item_tag);
    if (item_tag == NULLTAG) {
        printf("\nItem not found...\n");
        return;  // If item tag is not found, return
    }
    else {
        printf("Item found....\n");
    }

    return;
}
