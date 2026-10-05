#include "ass_header.h"

/*
Create a dataset if it does not exist and attach it to an item revision.
If the dataset exists,
do not create it, just attach it to the item revision.
*/
void create_or_attach_dataset_to_revision() {
    // Step 1: Get the item key and revision ID from the command line arguments
    char* search_id = ITK_ask_cli_argument("-i=");  // Item key 
    char* revision_id = ITK_ask_cli_argument("-r=");   // Revision ID 
    char* name = ITK_ask_cli_argument("-n=");  // Dataset name 

    tag_t revision_tag = NULLTAG;
    tag_t typetag = NULLTAG;
    tag_t createinputtag = NULLTAG;

    tag_t relation_type_name = NULLTAG;
    tag_t relation_ob = NULLTAG;

    // Step 2: Find Item revision
    ITEM_find_rev(search_id, revision_id, &revision_tag);  // Finding revision tag using item and revision ID
    if (revision_tag == NULLTAG) {
        printf("Item revision not found....\n");
        return;  // If revision tag is not found, return
    }
    else {
        printf("Item revision found....\n");
    }

    // Step 3: Check if dataset already exists
    AE_finding_dataset(name);

    if (name != NULL) {
        printf("Dataset is already in revision\n");
    }
    else {
        printf("Dataset is not in revision\n");
    }

    // Step 4: Get the type tag of the object to be created
    TCTYPE_ask_type("Text", &typetag);

    // Step 5: Construct create input to store input values
    TCTYPE_construct_create_input(typetag, &createinputtag);

    if (createinputtag != NULLTAG) {
        // Step 6: Store input values in the create input object
        AOM_set_value_string(createinputtag, "object_name", name);

        // Step 7: Create a new object
        TCTYPE_create_object(createinputtag, &typetag);

        // Step 8: Save object in Database
        AOM_save(typetag);

        printf("\nText created in Teamcenter...\n");

        // Step 9: Find relation type and create the relation
        GRM_find_relation_type("IMAN_specification", &relation_type_name);
        if (relation_type_name == NULLTAG) {
            printf("\nNo relation type found...\n");
            return;
        }

        GRM_create_relation(revision_tag, typetag, relation_type_name, NULLTAG, &relation_ob);
        GRM_save_relation(relation_ob);

        printf("\nForm attached to revision successfully...\n");

        return;
    }
    else {
        printf("\nItem creation failed...\n");
        return;
    }

    return;
}
