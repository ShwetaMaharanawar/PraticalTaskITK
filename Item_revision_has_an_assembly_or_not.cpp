#include "ass_header.h"

void Item_revision_has_an_assembly_or_not() {

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
    //Step 3 : Object Type

    //Step 4 : Object is in assembly

    //Step 5: print assembly desc BOMview
    const char* prop_name = "structure_revisions";
    tag_t* assemblyTag = NULL;
    char* ass_desc = NULL;
    int count = 0;

    AOM_ask_value_tags(revision_tag,prop_name,&count,&assemblyTag);
    
    if (assemblyTag != 0) {
        // If no assembly associated, print message
        printf("\nItem revision has an assembly using tags.\n");
    }
    else {
        printf("\nItem revision does not have an assembly usings tags.\n");

    }
    tag_t assembly_tag = NULLTAG;
    AOM_ask_value_tag(revision_tag, prop_name, &assembly_tag);

    if (assembly_tag != NULLTAG) {
        // If no assembly associated, print message
        printf("\nItem revision has an assembly using tag.\n");
    }
    else {
        printf("\nItem revision does not have an assembly usings tag.\n");

    }


	return;
}

