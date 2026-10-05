#include "ass_header.h" 

void create_folder() {
    // Get folder type, name, and description from command line arguments
    char* name = ITK_ask_cli_argument("-n=");
    char* type = ITK_ask_cli_argument("-t=");
    char* desc = ITK_ask_cli_argument("-d=");

    // Get item type, name, and item id from command line arguments
    char* item_type = ITK_ask_cli_argument("-item_type=");  // Item type
    char* item_name = ITK_ask_cli_argument("-item_name=");  // Item name
    char* item_id = ITK_ask_cli_argument("-item_id=");  // Item id

    // Declare tags for folder and item
    tag_t folder_type = NULLTAG;
    tag_t create_input = NULLTAG;
    tag_t business_object = NULLTAG;
    
    // Find the folder type

    TCTYPE_find_type(type,"Folder", &folder_type);
    
    if (TCTYPE_find_type(type, "Folder", &folder_type) !=ITK_ok ||folder_type == NULLTAG) {
        printf("\nFolder type not present...");
        return;
    }
    
    printf("Folder type present\n");

    // Construct input for creating the folder
    TCTYPE_construct_create_input(folder_type, &create_input);
    AOM_set_value_string(create_input, "object_name", name);
    AOM_set_value_string(create_input, "object_desc", desc);

    // Create the folder
    TCTYPE_create_object(create_input, &business_object);
    if (business_object == NULLTAG) {
        printf("\nFolder not created...");
        return;
    }

    // Save the created folder
    AOM_save(business_object);
    printf("\nFolder created...\n");

    //Now create an item to add to the folder
    // Now create an item to add to the folder
    tag_t item_tag = NULLTAG;
    tag_t create_item_input = NULLTAG;
    tag_t item_business_object = NULLTAG;
    tag_t item_type_tag = NULLTAG;

    // Find the item type
    if (TCTYPE_find_type(item_type, "Item", &item_type_tag) != ITK_ok || item_type_tag == NULLTAG) {
        printf("\nItem type not found...");
        return;
    }

    // Construct create input for the item
    TCTYPE_construct_create_input(item_type_tag, &create_item_input);

    if (create_item_input == NULLTAG) {
        printf("\nItem Creation failed...");
        return;
    }

    // Set item details
    AOM_set_value_string(create_item_input, "item_id", item_id);
    AOM_set_value_string(create_item_input, "object_name", item_name);
    AOM_set_value_string(create_item_input, "description", "Item created and added to folder");

    // Create the item
    TCTYPE_create_object(create_item_input, &item_business_object);

    if (item_business_object == NULLTAG) {
        printf("\nFailed to create item...\n");
        return;
    }

    // Save the created item
    AOM_save(item_business_object);
    printf("\nItem with id: %s created...\n", item_id);

    // Now insert the item into the folder
    FL_insert(business_object, item_business_object, 2); // 2 is for "Child" relationship

    // Save the folder again after inserting the item
    AOM_save(business_object);
    printf("\nItem inserted into folder...\n");

    
    return;
}