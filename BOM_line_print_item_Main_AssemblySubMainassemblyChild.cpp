#include "ass_header.h"

void BOM_line_print_item_Main_AssemblySubMainassemblyChild() {

    // Step 1: Get the item key and revision ID from the command line arguments
    char* search_id = ITK_ask_cli_argument("-i=");  // Item key
    char* revision_id = ITK_ask_cli_argument("-r="); // Revision ID

    tag_t item_tag = NULLTAG;
    tag_t revision_tag = NULLTAG;
    int BOMViews_Count = 0;
    tag_t* BOMViewR_count = NULL;
    tag_t NewWindo_tag = NULLTAG;
    tag_t top_bom_line = NULLTAG;
    int Number_child_lines = 0;
    tag_t* child_tag = NULL;
    int comp_count = 0;
    tag_t* comp_tag = NULL;
    char* comp_id = NULL;

    // Step 2: Find the item based on the search ID
    ITEM_find_item(search_id, &item_tag);
    if (item_tag == NULLTAG) {
        printf("\nItem not found...\n");
        return;
    }

    // Step 3: Find the revision based on the revision ID
    ITEM_find_rev(search_id, revision_id, &revision_tag);
    if (revision_tag == NULLTAG) {
        printf("Item revision not found...\n");
        return;  // If revision tag is not found, return
    }
    else {
        printf("Item revision found...\n");
    }

    // Step 4: Get the BOM Views associated with the item revision
    ITEM_rev_list_bom_view_revs(revision_tag, &BOMViews_Count, &BOMViewR_count);
    if (BOMViews_Count == 0) {
        printf("No BOM Views found for the item revision...\n");
        return;
    }

    // Step 5: Iterate through each BOM view
    for (int i = 0; i < BOMViews_Count; i++) {
        char* id = NULL;

        // Create a BOM window for the BOM view
        BOM_create_window(&NewWindo_tag);
        if (NewWindo_tag == NULLTAG) {
            printf("\nNo window found...\n");
            return;
        }

        // Set the top-level BOM line for the window
        BOM_set_window_top_line(NewWindo_tag, item_tag, revision_tag, BOMViewR_count[i], &top_bom_line);
        AOM_ask_value_string(top_bom_line, "object_string", &id);
        printf("\nBOM Root Line:\nItem ID: %s\n", id);

        if (top_bom_line == NULLTAG) {
            printf("\nNo top BOM line found...\n");
            return;
        }

        // Get the child lines (sub-assemblies) of the top BOM line
        BOM_line_ask_child_lines(top_bom_line, &Number_child_lines, &child_tag);
        if (Number_child_lines == 0) {
            printf("\nNo child lines found for the BOM...\n");
            return;
        }

        // Step 6: Iterate through each child (sub-assembly)
        printf("\nPrinting BOM sub-assemblies:\n");
        for (int i = 0; i < Number_child_lines; i++) {
            char* child_id = NULL;
            AOM_ask_value_string(child_tag[i], "object_string", &child_id);
            printf("\nSub-assembly Item ID: %s\n", child_id);

            // Get the components of the sub-assembly
            printf("\nComponents of %s:\n", child_id);
            BOM_line_ask_child_lines(child_tag[i], &comp_count, &comp_tag);
            if (comp_count == 0) {
                printf("\nNo components found for this sub-assembly.\n");
                continue;  // Skip if no components are found
            }

            // Step 7: Iterate through the components of the sub-assembly
            for (int k = 0; k < comp_count; k++) {
                if (comp_tag[k] == NULLTAG) {
                    printf("\nInvalid component tag found.\n");
                    continue;  // Skip invalid component tags
                }

                AOM_ask_value_string(comp_tag[k], "object_string", &comp_id);

                if (comp_id != NULL) {
                    printf("\nComponent Item ID: %s\n", comp_id);
                }
                else {
                    printf("\nComponent ID is NULL.\n");
                }
            }

            printf("-------------------------------------------\n");
        }
    }

    return;
}
