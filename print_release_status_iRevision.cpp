#include "ass_header.h"
/*
Print the release status of a given item revision.
*/

void print_release_status_iRevision() {

    // Step 1: Get the item key and revision ID from the command line arguments
    char* search_id = ITK_ask_cli_argument("-i=");  // Item key 
    char* revision_id = ITK_ask_cli_argument("-r=");   // Revision ID 

    tag_t revision_tag = NULLTAG;

    tag_t* workflow_tags = NULL;  // This will hold the workflow tags.
    int num_workflows = 0;  // Number of workflows.
    char* release_name = NULL;

    // Step 2: Find Item revision
    ITEM_find_rev(search_id, revision_id, &revision_tag);  // Finding revision tag using item and revision ID
    if (revision_tag == NULLTAG) {
        printf("Item revision not found....\n");
        return;  // If revision tag is not found, return
    }
    else {
        printf("Item revision found....\n");
    }


    // Step 3: Check if the item revision is in release status
    
    const char* prop_name = "release_status_list";

    int status = AOM_ask_value_tags(revision_tag, prop_name, &num_workflows, &workflow_tags);
    if (status != ITK_ok) {
        printf("Failed to retrieve workflow tags. Error code: %d\n", status);
        return;
    }
    if (num_workflows > 0) {
        printf("Item revision is in  release(s):\n");

        for (int i = 0; i < num_workflows; i++) {

            //printf("Workflow tag: %d\n", workflow_tags[i]); 
            AOM_ask_value_string(workflow_tags[i], "object_name", &release_name);
            printf("Release status : %s\n", release_name);
        }

    }
    else {
        printf("Item revision is not in release mode..\n");
    }


    // Optional: Free memory for dynamically allocated strings
    if (workflow_tags != NULL) {
        free(workflow_tags);
    }




	return;
}