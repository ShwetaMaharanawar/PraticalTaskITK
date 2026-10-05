
#include "ass_header.h"


void create_item() {
    char* itemid= ITK_ask_cli_argument("-i=");
    char* name= ITK_ask_cli_argument("-n=");
    char* type= ITK_ask_cli_argument("-t=");

    int retcode = ITK_ok;
    tag_t itemtag = NULLTAG;
    tag_t typetag = NULLTAG;
    tag_t createInputTAg = NULLTAG;

    //Step 3 : find item using ITK function: ITEM_Find_Item
    ITKCALL(ITEM_find_item(itemid, &itemtag));

    if (itemtag != NULLTAG)
    {
        //Item already exists
        WSO_description_t wsdesc;

        //Step 5: Fetch item details using ITK function:
        WSOM_describe(itemtag, &wsdesc);

        printf("\nItem with Id: %s alreaady exists...", itemid);
        //Step 6: display object details on commandpromt
        printf("\nObject Name: %s", wsdesc.object_name);
        printf("\nObject Type : %s", wsdesc.object_type);
        printf("\nOwner Name: %s", wsdesc.owners_name);
        printf("\nObject Desc: %s", wsdesc.description);
        printf("\nCreation date: %s", wsdesc.date_modified);
    }
    else
    {
        tag_t typetag = NULLTAG;
        tag_t createinputtag = NULLTAG;

        //Item not found... create a new item

        //Step 6.1 get the type tag of the object type to created.
        TCTYPE_ask_type(type, &typetag);

        //validate the type tag
        //if type is vaild only the we should proceed

        if (typetag != NULLTAG)
        {
            //Step 6.2: construct create input to store input values
            TCTYPE_construct_create_input(typetag, &createinputtag);

            if (createinputtag != NULLTAG)
            {
                //Step 6.3: store input values in create input object
                AOM_set_value_string(createinputtag, "item_id", itemid);
                AOM_set_value_string(createinputtag, "object_name", name);

                //Step 6.4: create a new object
                TCTYPE_create_object(createinputtag, &itemtag);

                //Step 6.5: Save object in Database
                AOM_save(itemtag);

                printf("\nItem id: %s created in Teamcenter...", itemid);

            }
            else
            {
                printf("\nItem Creation failed...");
                return;
            }
        }
        else
        {
            printf("\nCreate input failed... cannot create item. ");

            return;
        }
    }

    return;

}



