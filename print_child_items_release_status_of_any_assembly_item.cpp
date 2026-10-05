#include "ass_header.h"

// Function to print child items and their release status recursively
void print_child_items_release_status_of_any_assembly_item() {

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

    // Step 4: Process each child item
    for (int i = 0; i < num; ++i) {
        char* desc_name = NULL;
        AOM_ask_value_string(values[i], "object_name", &desc_name);
        printf("Child Item %d: %s\n", i + 1, desc_name);

        const char* prop_name_release_status = "release_status_list";
        int status_count = 0;
        tag_t* status_tags = NULL;

        // Fetch release status list for each child item
        AOM_ask_value_tags(values[i], prop_name_release_status, &status_count, &status_tags);

        if (status_count > 0) {
            printf("Child item %d is in the following release(s):\n", i + 1);

            // Print each release status for the child item
            for (int j = 0; j < status_count; j++) {
                char* release_name = NULL;
                AOM_ask_value_string(status_tags[j], "object_name", &release_name);
                printf("Release status: %s\n", release_name);
            }
        }
        else {
            printf("Child item %d is not in release mode..\n", i + 1);
        }
    }

    return;
}
