#include "ass_header.h"
#include <ae/ae_errors.h>
#include <res/res_itk.h>

void Task_Fun() {

    //1St Task : Provide an item ID as input

    char* item_id = ITK_ask_cli_argument("-i=");  // Item key

    //This is for task 3

    char* revision_id = ITK_ask_cli_argument("-r=");   // Revision ID passed from command line

    char* dataset_id = ITK_ask_cli_argument("-d=");

    //2nd Task : Search for the item in Teamcenter

    tag_t item = 0;

    ITEM_find_item(item_id, &item);

    if (item != ITK_ok)

    {

        printf("Item id Found \n");

    }

    else {

        printf("Item id not Found \n");

    }

    //3rd Task : Create a new Text dataset with a dummy ID.

    /*

    While  creating dataset we need to attach it in revision.

    that's why we need to 1st find revision then we will add the dummydataset to revision.

    */

    tag_t revision_tag = NULLTAG;

    ITEM_find_rev(item_id, revision_id, &revision_tag);  // Finding revision tag using item and revision ID

    if (revision_tag == NULLTAG) {

        printf("Item revision not found....\n");

        return;  // If revision tag is not found, return

    }

    else {

        printf("Item revision found....\n");

    }

    tag_t typetag = NULLTAG;

    tag_t createinputtag = NULLTAG;

    tag_t relation_type_name = NULLTAG;

    tag_t relation_ob = NULLTAG;

    //get the type tag of the object type to created.

    TCTYPE_ask_type("Text", &typetag);


    //construct create input to store input values

    TCTYPE_construct_create_input(typetag, &createinputtag);

    if (createinputtag != NULLTAG)
    {

        //store input values in create input object

        AOM_set_value_string(createinputtag, "object_name", dataset_id);

        //create a new object

        TCTYPE_create_object(createinputtag, &typetag);

        //Save object in Database

        AOM_save(typetag);

        printf("\n Text created in Teamcenter...");

        //4th Task :Attach the newly created Text dataset under the corresponding Item Revision.

        GRM_find_relation_type("IMAN_specification", &relation_type_name);

        if (relation_type_name == NULLTAG) {

            printf("\nNo relation type found...");

            return;

        }

        //attach file to revision 

        GRM_create_relation(revision_tag, typetag, relation_type_name, NULLTAG, &relation_ob);

        GRM_save_relation(relation_ob);

        printf("\nForm attached to revision successfully...");

        // Task 5: Add a named reference file (test2.txt) to the dataset


        int checkout_status = RES_checkout2(typetag, "desc changed", NULL, "dir", RES_EXCLUSIVE_RESERVE);
        
        if (checkout_status == ITK_ok) {

            printf("\nReference file checked out successfully...");

        }

        else {

            printf("\nError checking out the reference file...");

        }
        
       // const char* reference_name = "Text";  // Define your reference name

        const char* os_full_path_name = "C:\\ShwetaTask\\test2.txt";  

        const char* destPath = "C:/ShwetaTask/NewText.txt";

       // int file_type_flag = SS_TEXT;  // You can change this to SS_BINARY for binary files

        AOM_refresh(typetag, true);

        ITKCALL(AE_import_named_ref(typetag,"Text", os_full_path_name, NULL, SS_TEXT));

        AOM_save(typetag);

        AOM_refresh(typetag, false);

        

        AOM_refresh(typetag, true);


        ITKCALL(AE_export_named_ref(typetag, "Text", destPath));

        AOM_refresh(typetag, false);


        return;

    }else
    {

        printf("\nItem Creation failed...");

        return;

    }

    return;

}
