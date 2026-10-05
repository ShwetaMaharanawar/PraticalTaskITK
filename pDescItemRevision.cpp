#include "ass_header.h"
/*print description and lastmodified date property values
of Item and Item revision  */

void pDescItemRevision() {

    // Get command line arguments for item id
    char* itemid = ITK_ask_cli_argument("-i=");


    int retcode = ITK_ok;
    tag_t itemtag = NULLTAG;

    //added declaration for ITK function modified_date
    tag_t obj= 0;
    date_t modified_date;

    // Added declaration for item  tag
    char* name = NULL;
    char* desc = NULL;
    char* lastModified;

    // Added declaration for AOM_get_value_string
    tag_t object_tag = NULLTAG;
    const char prop_name=NULL;
    char* value = 0;

    // Added declaration for revision tag
    tag_t* rev_tags = NULL;
    int n_revs = 0;
    tag_t item = NULLTAG;
    char* rev_name = NULL;


    //Step 1 : find item using ITK function: ITEM_Find_Item
    //itemid is a search id and itemtag gives the matching Item
    ITKCALL(ITEM_find_item(itemid, &itemtag));
   
    if (itemtag != NULLTAG)
    {
        //Item already exists
        
       // Step 2: Fetch item details using ITK function: AOM_ask_modified_date
        // Changed obj to itemtag
       
        // Step 3: Display object details on command prompt
        //USe ITK function :AOM_ask_value_string
        //AOM_ask_value_string(object_tag,"object_name", &value);
        AOM_ask_value_string(itemtag, "object_desc", &desc);
        AOM_ask_value_string(itemtag, "object_name", &value);
        AOM_ask_value_date(itemtag, "last_mod_date", &modified_date);

        

        // Print item details
        printf("Item Name: %s\n", value);
        printf("Item Description: %s\n", desc);

        DATE_date_to_string(modified_date,"%y/%m/%d",&lastModified);
        printf("Last Modified Date: %s\n", lastModified);

        // Lets find the revisions
        // Step 4: Find item revisions using ITEM_find_revision
        ITEM_list_all_revs(itemtag, &n_revs, &rev_tags);
       
    
        if  (n_revs > 0) {
            // Assuming rev_tag is an array of tags, iterate through them
            // Iterate through revisions
            for (int i = 0; i < n_revs; i++) {
                date_t rev_modified_date;
                char* rev_desc = NULL;
                char* rev_date = NULL;

                // Fetch revision details
                AOM_ask_value_string(rev_tags[i], "object_name", &rev_name);
                AOM_ask_value_date(rev_tags[i],"last_mod_date", &rev_modified_date);
                AOM_ask_value_string(rev_tags[i], "object_desc", &rev_desc);

                DATE_date_to_string(rev_modified_date, "%y/%m/%d", &rev_date);

                // Print revision details
                printf("Revision: %d\n",i+1);
                printf("Revision Name: %s\n", rev_name);
                printf("Revision Description: %s\n", rev_desc);
                printf("Revision Last Modified Date: %s\n", rev_date);

                // Free memory for revision description
                if (rev_desc) {
                    free(rev_desc);
                }
            }

            
        }else
        {
            printf("\nItem revision not found\n");
        }
        // Free memory for item details
        if (value) {
            free(value);
        }
        if (desc) {
            free(desc);
        }
        if (lastModified) {
            free(lastModified);
        }
    }
    else
    {
        printf("\nItem not found");
    }

    

	return;

}