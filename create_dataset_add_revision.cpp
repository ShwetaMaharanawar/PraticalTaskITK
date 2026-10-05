#include "ass_header.h"

/*
Create dataset and attach dataset to any revision with IMAN_specification relation
*/

void create_dataset_add_revision() {

	// Step 1: Get the item key and revision ID from the command line arguments
	char* search_id = ITK_ask_cli_argument("-i=");  // Item key passed from command line
	char* revision_id = ITK_ask_cli_argument("-r=");   // Revision ID passed from command line
    char* name = ITK_ask_cli_argument("-n=");
	
	tag_t revision_tag = NULLTAG;

    tag_t typetag = NULLTAG;
    tag_t createinputtag = NULLTAG;

    tag_t relation_type_name = NULLTAG;
    tag_t relation_ob = NULLTAG;

	//Step 2: Find Item revision

	ITEM_find_rev(search_id, revision_id, &revision_tag);  // Finding revision tag using item and revision ID
	if (revision_tag == NULLTAG) {
		printf("Item revision not found....\n");
		return;  // If revision tag is not found, return
	}
	else {
		printf("Item revision found....\n");
	}

	
  

    

    //Step  get the type tag of the object type to created.
    TCTYPE_ask_type("Text", &typetag);

   
        //Step  construct create input to store input values
        TCTYPE_construct_create_input(typetag, &createinputtag);

        if (createinputtag != NULLTAG)
        {
            //Step  store input values in create input object
            
            AOM_set_value_string(createinputtag, "object_name", name);

            //Step  create a new object
            TCTYPE_create_object(createinputtag, &typetag);

            //Step  Save object in Database
            AOM_save(typetag);

            printf("\n Text created in Teamcenter...");

            GRM_find_relation_type("IMAN_specification", &relation_type_name);
            if (relation_type_name == NULLTAG) {

                printf("\nNo relation type found...");

                return;

            }
            GRM_create_relation(revision_tag,typetag,relation_type_name, NULLTAG, &relation_ob);

            GRM_save_relation(relation_ob);

            printf("\nForm attached to revision successfully...");

            return;
        }
        else
        {
            printf("\nItem Creation failed...");
            return;
        }

    

	return;
}

