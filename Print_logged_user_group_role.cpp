#include "ass_header.h"

// Function to print the logged-in user's group and role
void Print_logged_user_group_role() {
    char* group_name_string = NULL;
    tag_t group_tag = NULL;      
    tag_t current_role_tag = NULLTAG;  
    char* group_name = NULL;        
    char* role_name = NULL;        

    POM_ask_group(&group_name_string,&group_tag);
    
    SA_ask_current_role(&current_role_tag);
    if (current_role_tag == NULLTAG) {
        printf("Failed to retrieve the user's role.\n");
        return;
    }

    
    AOM_ask_name(current_role_tag, &role_name);
    if (role_name == NULL) {
        printf("Failed to retrieve the role name.\n");
        return;
    }

    printf("Logged-in user is part of the group: %s\n", group_name_string);
    printf("Logged-in user has the role: %s\n", role_name);

    return;
}
