#include <stdio.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/item.h>
#include <tc/emh.h>
#include <ce/ce.h>
#include <property/prop.h>

int check_property_condition(tag_t object_tag, const char* prop_name)
{
    int ifail = ITK_ok;
    tag_t condition_tag = NULLTAG;
    char* condition_name = NULL;
    logical is_read_only = FALSE;
    int parm_count = 0;
    tag_t* parm_tags = NULL;
    logical eval_result = FALSE;

    /* Check if property is read-only (often indicates a condition) */
    ifail = AOM_ask_is_read_only(object_tag, prop_name, &is_read_only);
    if (ifail != ITK_ok) return ifail;

    if (!is_read_only)
    {
        printf("Property '%s' has no read-only condition\n", prop_name);
        return ITK_ok;
    }

    /* Try to get the condition tag */
    ifail = CE_ask_property_condition(object_tag, prop_name, &condition_tag);
    if (ifail != ITK_ok || condition_tag == NULLTAG)
    {
        printf("No explicit condition found (might be implicit read-only)\n");
        return ITK_ok;
    }

    /* Get condition name */
    ifail = CE_ask_condition(condition_tag, &condition_name);
    if (ifail != ITK_ok) return ifail;

    printf("Property '%s' has condition: %s\n", prop_name, condition_name);

    /* Evaluate the condition */
    ifail = CE_evaluate_condition(condition_tag, parm_count, parm_tags, &eval_result);
    if (ifail != ITK_ok)
    {
        MEM_free(condition_name);
        return ifail;
    }

    printf("Condition evaluation result: %s\n", eval_result ? "TRUE" : "FALSE");

    /* Clean up */
    MEM_free(condition_name);

    return ITK_ok;
}

int ITK_user_main(int argc, char* argv[])
{
    int ifail = ITK_ok;
    tag_t item_rev = NULLTAG;  // Initialize with your object tag
    const char* prop_name = "release_status";  // Property to check

    

    /* Login to Teamcenter */
    ifail = ITK_auto_login();
    if (ifail != ITK_ok)
    {
        printf("Login failed with error %d\n", ifail);
        ITK_exit_module(FALSE);
        return ifail;
    }

    /* Check property condition */
    ifail = check_property_condition(item_rev, prop_name);
    if (ifail != ITK_ok)
    {
        char* error_text = NULL;
        EMH_ask_error_text(ifail, &error_text);
        printf("Error checking condition: %s\n", error_text);
        if (error_text) MEM_free(error_text);
    }

    /* Exit */
    ITK_exit_module(FALSE);
    return ITK_ok;
}