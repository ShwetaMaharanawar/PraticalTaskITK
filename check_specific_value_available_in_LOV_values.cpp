#include "ass_header.h"

void check_specific_value_available_in_LOV_values() {

	//char* LOV_name = ITK_ask_cli_argument("-l=");

	int n_lovs = NULL;
	tag_t* lov = NULL;
	char** lov_values = NULL;
	int n_values = NULL;


	LOV_find("BillCodes",&n_lovs,&lov);

	if (n_lovs != NULL) {
	
		for (int i = 0; i < n_lovs; i++) {
		
			LOV_ask_values_string(lov[i], &n_values, &lov_values);

			for (int j = 0; j < n_values; j++) {

				printf("\n LOV values  %s \n", lov_values[j]);

			}
		} 
	
	}
	else {
	
		printf("NO LOV found for a given data");
		return;
	}


	return;
}