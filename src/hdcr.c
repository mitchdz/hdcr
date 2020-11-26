#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "hdcr.h"
#include "thresh.h"
#include "IO.h"


void printWelcomeMessage(char* input, char* output)
{
    printf("Hand Drawn Circuit Recognizer\n");
    printf("\t input: %s\n", input);
    printf("\t output: %s\n", output);
}

/*
 * hdcr steps:
 * 1) threshold image
 * 2) find center of each component
 * 3) determine what each component is
 * 4) follow the wires to the next component and connect
 * 5) print the linked list of connected components
 */
error_hdcr_t hdcr_run_program(
    char* inputImageFileName,
    char* outputImageFilName, 
    bool adaptiveThreshold,
    ADAPTIVE_THRESHOLD_TYPE att,
    uint8_t inputThreshold,
    uint8_t MOV, //MaxOutputValue
    uint8_t CGL, // ComponentGrayLevel
    bool verbose 
    )
{
    //TODO: error detection

    if (verbose) printWelcomeMessage(inputImageFileName, outputImageFilName);


    error_hdcr_t err;
    uint8_t threshold = 0;

    // read the input file and store it into IMAGE struct
    IMAGE img; 
    readPNGandClose(inputImageFileName, &img);
    
    if (verbose) {
        printf("%s is a %dx%d image\n", inputImageFileName, img.n_rows, img.n_cols);
    }

    // if no adaptive threshold defined and no input threshold, return error
    if (!adaptiveThreshold && inputThreshold==0) {
        err = E_hdcr_GENERIC_ERROR;
        printError(err, (char*)"no adaptive threshold, and no defined threshold");
        return err;
    }

    if (adaptiveThreshold) {
        adaptiveThresholdWithMethod(&img, att, &threshold);
    }
    else {
        threshold = inputThreshold;
    }

    // threshold the image
    threshold2DPseudoArray(img.raw_bits, img.n_rows, img.n_cols, threshold);

    // find number of circuit components


    // connect each component



    return E_hdcr_NOT_IMPLEMENTED;
}



error_hdcr_t  detectNumberOfCircuitComponents(IMAGE *img)
{
    return E_hdcr_NOT_IMPLEMENTED;
}