
#include <stdio.h>
#include <tcinit/tcinit.h>
#include<tccore\item.h>
#include<tccore\aom_prop.h>
#include<tccore\aom.h>
#include<tccore\tctype.h>


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
    printf("\n Login Done ");

    
    find_itemR_workflow();
    


    return 0;


}


void find_itemR_workflow() {

    // Step 1: Get the item key and revision ID from the command line arguments
    char* search_id = ITK_ask_cli_argument("-i=");  // Item key 
    char* revision_id = ITK_ask_cli_argument("-r=");   // Revision ID 

    tag_t revision_tag = NULLTAG;

    tag_t* workflow_tags = NULL;  // This will hold the workflow tags.
    int num_workflows = 0;  // Number of workflows.
    char* desc_name = NULL;

    // Step 2: Find Item revision
    ITEM_find_rev(search_id, revision_id, &revision_tag);  // Finding revision tag using item and revision ID
    if (revision_tag == NULLTAG) {
        printf("Item revision not found....\n");
        return;  // If revision tag is not found, return
    }
    else {
        printf("Item revision found....\n");
    }


    // Step 3: Check if the item revision is in any workflow
    //const char* prop_name = "WorkspaceObjectDefaultWorkflowTemplate";  // Adjust this depending on the actual property name.
    //const char* prop_name = "fnd0TaskPathName";
    const char* prop_name = "process_stage_list";

    int status = AOM_ask_value_tags(revision_tag, prop_name, &num_workflows, &workflow_tags);
    if (status != ITK_ok) {
        printf("Failed to retrieve workflow tags. Error code: %d\n", status);
        return;
    }
    if (num_workflows > 0) {
        printf("Item revision is in workflow(s):\n");

        for (int i = 0; i < num_workflows; i++) {

            //printf("Workflow tag: %d\n", workflow_tags[i]); 
            AOM_ask_value_string(workflow_tags[i], "object_name", &desc_name);
            printf("Description Name : %s\n", desc_name);
        }

    }
    else {
        printf("Item revision is not in any workflow.\n");
    }


    // Optional: Free memory for dynamically allocated strings
    if (workflow_tags != NULL) {
        free(workflow_tags);
    }



    return;

}