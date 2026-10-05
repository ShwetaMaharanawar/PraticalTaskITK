#include "ass_header.h"

void datasetnameRef() {

	char* item_id = ITK_ask_cli_argument("-i=");  // Item key

    tag_t itemtag = NULLTAG;
    tag_t revision_tag = NULLTAG;
    tag_t dstag = NULLTAG;
    tag_t createinputtag = NULLTAG;
    tag_t relation_type_name = NULLTAG;
    tag_t relation_ob = NULLTAG;
    tag_t new_dataset = NULLTAG;

    ITEM_find_item(item_id, &itemtag);

    if (itemtag != ITK_ok)
    {

        printf("Item id Found \n");


        ITEM_find_revision(itemtag,"A", &revision_tag);  // Finding revision tag using item and revision ID

        if (revision_tag != NULLTAG) {

            printf("Item revision  found....\n");

            AE_find_datasettype2("Text",&dstag);
            AE_create_dataset_with_id(dstag,"DataSetName",NULL,"00101",NULL, &new_dataset);
            AE_save_myself(new_dataset);

            GRM_find_relation_type("IMAN_specification", &relation_type_name);

            if (relation_type_name == NULLTAG) {

                printf("\nNo relation type found...");

                return;

            }

            //attach file to revision 

            GRM_create_relation(revision_tag,new_dataset, relation_type_name, NULLTAG, &relation_ob);

            GRM_save_relation(relation_ob);
            printf("\nDataSet attached to revision successfully...");

            //const char* os_full_path_name = "C:\\ShwetaTask\\test2.txt";

            const char* destPath = "C:/ShwetaTask/NewText.txt";

            // int file_type_flag = SS_TEXT;  // You can change this to SS_BINARY for binary files

            AOM_refresh(new_dataset, true);

            ITKCALL(AE_import_named_ref(new_dataset,"Text","C:\\ShwetaTask\\test2.txt",NULL,SS_TEXT));

            //AOM_save(typetag);

            AOM_refresh(new_dataset, false);

            //return;  

        }

        else {

            printf("Item revision not found....\n");


        }

    }else 
    {

        printf("Item id not Found \n");

    }



	return;
}