#include "ass_header.h"

/*
Update property Description on any item revision.
*/

void upPropDespItemRevision() {

    // Step 1: Get the item key, revision ID, and new description from the command line arguments
    char* search_id = ITK_ask_cli_argument("-i=");  // Item key 
    char* revision_id = ITK_ask_cli_argument("-r="); // Revision ID 
    char* new_description = ITK_ask_cli_argument("-d="); // New description 

    // Declaration for item revision tag
    tag_t revision_tag = NULLTAG;


    char* xmlString = NULL;
    char* result = NULL;
    // Step 2: Find the item revision using item key and revision ID
    ITEM_find_rev(search_id, revision_id, &revision_tag);  // Finding revision tag using item and revision ID
    if (revision_tag == NULLTAG) {
        printf("Item revision not found....\n");
        return;  
    }
    else {
        printf("Item revision found....\n");
    }

    // Step 3: Checkout the item revision to make it editable
    AIWS_CheckOut(revision_id,&result);

    if (result != NULL)
    {
        printf("Revision id not found");
        return ;
    }

    printf("Revision id found");

    

    // Step 5: Update the "Description" property with the new description
    AOM_set_value_string(revision_tag, "object_desc", new_description);

    printf("Description updated to: %s\n", new_description);

    // Step 6: Save the changes to the item revision
    AOM_save(revision_tag);
    printf("Changes saved successfully...\n");

    return;
}
