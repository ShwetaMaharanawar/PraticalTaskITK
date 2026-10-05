#include "ass_header.h"

/*
get where referenced data on any dataset

get where referenced data on any dataset at one level
*/
void get_where_refer_data_on_any_dataset() {


	char* dataset_name = ITK_ask_cli_argument("-d=");

	tag_t dataset = NULLTAG;
	tag_t folder_tag = NULLTAG;
	//int num_of_references = 0;
	FL_sort_criteria_t sort_criteria = FL_fsc_by_name;
	tag_t* list_of_references = NULL;

	//1st Find dataset
	AE_find_dataset2(dataset_name,&dataset);

	if (dataset != NULLTAG) {
		printf("\nDataset Found: %s (Tag: %d)\n", dataset_name, dataset);
	}
	else {
		printf("\nDataset Not Found: %s\n", dataset_name);
		return;
	}
	/*
	//2nd Step Not working
	FL_ask_references(folder_tag, sort_criteria, &num_of_references, &list_of_references);

	// Print out the references if found
	if (num_of_references > 0) {
		printf("\nFound %d references:\n", num_of_references);
		for (int i = 0; i < num_of_references; i++) {
			// Assuming tag_t can be printed directly, modify as needed
			printf("Reference %d: %d\n", i + 1, list_of_references[i]);
		}
	}
	else {
		printf("\nNo references found for the dataset.\n");
	}

	
	if (list_of_references != NULL) {
		free(list_of_references);  
	}

	*/
	int num_referencers = 0;
	int* levels = NULL;
	tag_t* referencers = NULL;
	char** relations = NULL;

	int depth = 1;// Depth level to search for references
	int status =WSOM_where_referenced2(dataset, depth, &num_referencers, &levels, &referencers, &relations);
	if (status != 0) {
		printf("\nError retrieving references.\n"+status);
		return;
	}

	if (num_referencers > 0) {
		printf("\nFound %d referencers:\n", num_referencers);
		for (int i = 0; i < num_referencers; i++) {
			// Assuming referencers[i] can be printed as tag_t directly, modify if necessary
			printf("Referencer %d: %d\n", i + 1, referencers[i]);
			// Print the relation if required
			if (relations != NULL && relations[i] != NULL) {
				printf("Relation: %s\n", relations[i]);
			}
		}
	}
	else {
		printf("\nNo references found for the dataset.\n");
	}

	// Step 4: Clean up allocated memory if needed
	if (levels != NULL) {
		free(levels);
	}
	if (referencers != NULL) {
		free(referencers);
	}
	if (relations != NULL) {
		for (int i = 0; i < num_referencers; i++) {
			if (relations[i] != NULL) {
				free(relations[i]);
			}
		}
		free(relations);
	}



	return;
}