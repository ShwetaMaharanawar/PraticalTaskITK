#pragma once
#include <stdio.h>
#include <tcinit/tcinit.h>
#include<tccore\item.h>
#include<tccore\aom_prop.h>
#include<tccore\aom.h>
#include<tccore\tctype.h>
#include<tccore\aom.h>
#include<tc/folder.h>
#include<fclasses\tc_date.h>
#include<tccore\grm.h>
#include<ai\aiws.h>
#include <common/emh_const.h>
#include<ae/dataset.h>
#include<tc/folder.h>
#include<tccore/workspaceobject.h>
#include <itk\te.h>
#include<tc\preferences.h>
#include <stdlib.h>
#include<ss/ss_errors.h>
#include<epm/epm.h>
#include<sa/role.h>
#include<ae/datasettype.h>
#include<lov/lov.h>
#include<bom/bom.h>

#define AE_finding_dataset

#define WSO_where_ref_any_depth   -1



void create_item();
void getRevisionItem();
void pDescItemRevision();
void find_itemRevision();
void create_folder();
void create_dataset_add_revision();
void upPropDespItemRevision();
void create_or_attach_dataset_to_revision();
void find_itemR_workflow();
void get_where_refer_data_on_any_dataset();
void Print_values_multi_valued_preference();
void Print_values_single_valued_preference();
void print_release_status_iRevision();
void Add_release_status_iRevision();
void Remove_release_status_iRevision();
void Item_revision_has_an_assembly_or_not();
void Print_children_count_and_child_item_ids_of_any_assembly_Item();
void print_child_items_release_status_of_any_assembly_item();
void Print_logged_user_group_role();
void Task_Fun();
void datasetnameRef();
void check_specific_value_available_in_LOV_values();
void BOM_line_print_item_Main_AssemblySubMainassemblyChild();
void downloadNameRef();