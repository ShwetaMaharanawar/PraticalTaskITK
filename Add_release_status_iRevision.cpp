#include "ass_header.h"


/*
Add a release status to a given item revision.
*/

void Add_release_status_iRevision() {
    // Step 1: Get the item key and revision ID from the command line arguments
    char* search_id = ITK_ask_cli_argument("-i=");  // Item key
    char* revision_id = ITK_ask_cli_argument("-r="); // Revision ID

    tag_t revision_tag = NULLTAG;
    tag_t release_status = NULLTAG;
    const char* status_type = "Released"; //The new status type to create. 

    // Step 2: Find Item revision
    int result = ITEM_find_rev(search_id, revision_id, &revision_tag);
    if (result != ITK_ok || revision_tag == NULLTAG) {
        printf("Item revision not found....\n");
        return;  // If revision tag is not found, return
    }
    else {
        printf("Item revision found....\n");
    }

    // Step 3: Create release status
    //release_status : The newly created release status object
    result = RELSTAT_create_release_status(status_type, &release_status);
    if (result != ITK_ok || release_status == NULLTAG) {
        printf("Failed to create release status....\n");
        return;
    }

    // Step 4: Set the release status type
    result = RELSTAT_set_release_status_type(release_status, status_type);
    if (result != ITK_ok) {
        printf("Failed to set release status type....\n");
        return;
    }

    // Step 5: Add release status to the item revision
    tag_t ws_objects[] = { revision_tag }; //The set of objects to get a release_status object.
    //count : The number of objects to get a release_status object.
    int count = sizeof(ws_objects) / sizeof(ws_objects[0]);//number of elements in the array.
    //int count = 0;
    logical retain_released_date = TRUE;  //Whether to retain the released date

    result = RELSTAT_add_release_status(release_status, count, ws_objects, retain_released_date);
    if (result != ITK_ok) {
        printf("Failed to add release status....\n");
        return;
    }

    printf("Release status added successfully.\n");

    return;
}
