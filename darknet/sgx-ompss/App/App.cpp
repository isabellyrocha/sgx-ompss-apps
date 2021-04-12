#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <thread>
#include <sgx_urts.h>
#include "App.h"
#include "ErrorSupport.h"

/* For romulus */
#define MAX_PATH FILENAME_MAX

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;
static int stack_val = 10;

/* Darknet variables */
data training_data, test_data;

/* Initialize enclave
 * Call sgx_create_enclave to initialize an enclave instance
 */
int initialize_enclave(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    /* Call sgx_create_enclave to initialize an enclave instance */
    /* Debug Support: set 2nd parameter to 1 */
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
    if (ret != SGX_SUCCESS)
    {
        print_error_message(ret);
        return -1;
    }

    return 0;
}

/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    char *data_cfg = argv[1];
    char *cfg = argv[2];
    char *weights = argv[3];
    char *image_file = argv[4];
    float thresh = find_float_arg(argc, argv, "-thresh", .25);    // 0.24

    printf("\nData CFG: %s", data_cfg);
    printf("\nCFG: %s", cfg);
    printf("\nWeights: %s", weights);
    printf("\nThreash: %f", thresh);
    printf("\nImage: %s", image_file);

    sgx_status_t ret;

    /* Initialize the enclave */
    if (initialize_enclave() < 0)
    {
        printf("Enter a character before exit ...\n");
        getchar();
        return -1;
    }
    printf("\nEnclave created..");

    //read cfg file
    list *sections = read_cfg(cfg);

    //read labels
    list *options = read_data_cfg(data_cfg);
    char *name_list = option_find_str(options, "names", 0);
    list *plist = get_paths(name_list);
    printf("\nConfigurations loaded..");

    //read image file
    //char *file = IMAGE;
    char buff[256];
    char *input = buff;
    strncpy(input, image_file, 256);
    image im = load_image_color(input, 0, 0);
    printf("\nInput image loaded..");

    //classify image in enclave
    //#pragma omp task in(sections, plist, weights, thresh, im)
    ecall_classify(global_eid, sections, plist, weights, thresh, im);
    printf("\nClassification complete..");

    //free data
    free_image(im);

    //destroy enclave
    sgx_destroy_enclave(global_eid);
    return 0;
}
