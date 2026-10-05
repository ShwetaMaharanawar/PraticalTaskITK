#include "ass_header.h"


int ITK_user_main(int argc, char* argv[])
{

    int retcode = ITK_ok;

    char* userid = ITK_ask_cli_argument("-u=");
    char* password = ITK_ask_cli_argument("-p=");

    char* groupid = ITK_ask_cli_argument("-g=");
    retcode = ITK_init_module(userid, password, groupid);

    if (retcode != ITK_ok) {
        printf("\n Login Faild \n ");
        return -1;
    }
    printf("\n Login Done \n ");

    //create_item();
    // getRevisionItem();
    //pDescItemRevision();
    //find_itemRevision();
    //create_folder();
    //create_dataset_add_revision();
   //create_or_attach_dataset_to_revision();
    //upPropDespItemRevision();
    // find_itemR_workflow();
    //get_where_refer_data_on_any_dataset();
    //Print_values_multi_valued_preference();
    //Print_values_single_valued_preference();
    //print_release_status_iRevision();
    //Add_release_status_iRevision();
   // Remove_release_status_iRevision();
    //Item_revision_has_an_assembly_or_not();
    //Print_children_count_and_child_item_ids_of_any_assembly_Item();
   // print_child_items_release_status_of_any_assembly_item();
    //Print_logged_user_group_role();
    //Task_Fun();
    //datasetnameRef();
    //check_specific_value_available_in_LOV_values();
    //BOM_line_print_item_Main_AssemblySubMainassemblyChild();
    downloadNameRef();

    return 0;


}
