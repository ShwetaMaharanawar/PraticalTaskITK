#include "ass_header.h"
//#define PREF_invalid_preference_name
//#define PREF_missing_preference_name
//#define PF_NOTFOUND

/*
Print values of a multi valued preference
*/
void Print_values_multi_valued_preference() {

    int count = 0;          // Will hold the number of values returned
    char** values = NULL;   // Will hold the array of values
    const char* preference_name = "Create_WorkspaceObject_mru_list";
    // Call PREF_ask_char_values to fetch the values of the preference
    int result = PREF_ask_char_values(preference_name, &count, &values);

    // Handle the result codes
    if (result == ITK_ok) {
        if (count > 0) {
            printf("Preference '%s' has the following values:\n", preference_name);
            for (int i = 0; i < count; i++) {
                printf("%d: %s\n", i + 1, values[i]);
            }
        }
        else {
            printf("No values found for preference '%s'.\n", preference_name);
        }
    }
    else if (result == PREF_invalid_preference_name) {
        printf("Invalid preference name provided: '%s'.\n", preference_name);
    }
    else if (result == PREF_missing_preference_name) {
        printf("Missing preference name.\n");
    }
    else if (result == PF_NOTFOUND) {
        printf("Preference '%s' not found.\n", preference_name);
    }
    else {
        printf("Unknown error occurred while fetching preference values.\n");
    }

    // Free the allocated memory for values (if any)
    if (values != NULL) {
        MEM_free(values);  // Assuming MEM_free is used to deallocate the container memory
    }

	return;
}