#include "ass_header.h"
/*
Print the children count and child item ids of any assembly item
*/

void Print_children_count_and_child_item_ids_of_any_assembly_Item() {

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

    // Step 3: Query the "ps_children" property to get child item tags
    const char* prop_name = "ps_children";
    int num = 0;            // Number of children
    tag_t* values = NULL;   // Array of child item tags

    AOM_ask_value_tags(revision_tag, prop_name, &num, &values);

    if (num == 0) {
        printf("No children found or error fetching child items....\n");
        return;
    }

    printf("Number of child items: %d\n", num);

    char* desc_name = NULL;
    for (int i = 0; i < num; ++i) {
        AOM_ask_value_string(values[i], "object_name", &desc_name);
        printf("Child Items : %s\n",desc_name);
    }
    

    // Step 5: Clean up memory used by values if necessary
    if (values != NULL) {
        // If AOM_ask_value_tags allocates memory for values, free it here
        // Adjust the function to properly free values as per your API
        free(values);  // Only free if allocated dynamically
    }



	return;

}