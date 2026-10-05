#include "ass_header.h"

void getRevisionItem() {
    // Get command line arguments for item id
    char* itemid = ITK_ask_cli_argument("-i=");
    
    
    int retcode = ITK_ok;
    tag_t itemtag = NULLTAG;
    
    tag_t* rev_tags = NULL;
    const char rev_id=0;
    int n_revs=0;
    
    //Step 1 : find item using ITK function: ITEM_Find_Item
    //itemid is a search id and itemtag gives the matching Item
    ITKCALL(ITEM_find_item(itemid, &itemtag));

    if (itemtag != NULLTAG)
    {
        //Item already exists Lets find the revisions
        
        // Step 2: Find item revisions using  ITEM_list_all_revs
        //itemtag is unique number and n_revs is integer no. which stored the no. occreances  of revision
        //rev_tags is a pointer variable which stored the reference of revision tag array
        ITEM_list_all_revs(itemtag, &n_revs, &rev_tags);

       

        if (n_revs !=0) {
            for (int i = 0; i < n_revs; i++) {

                WSO_description_t wsdesc_rev;

                WSOM_describe(rev_tags[i], &wsdesc_rev);

                printf("\nRevision ID: %s\n", wsdesc_rev.revision_id);
                printf("\nType: %s\n", wsdesc_rev.object_type);
                printf("\nOwners name: %s\n", wsdesc_rev.owners_name);

            }

            printf("\nTotal revision count: %d\n", n_revs);

        }
        
       
    }
    else {
        // Item not found
        printf("\nItem with ID %s not found.\n", itemid);
    }

	return;
}