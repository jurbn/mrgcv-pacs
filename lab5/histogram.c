////////////////////////////////////////////////////////////////////
// File: basic_environ.c
//
// Description: base file for environment exercises with openCL
//
//
////////////////////////////////////////////////////////////////////

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include "CImg-3.3.2/CImg.h"

using namespace cimg_library;

// check error, in such a case, it exits

void cl_error(cl_int code, const char *string)
{
    if (code != CL_SUCCESS)
    {
        printf("%d - %s\n", code, string);
        exit(-1);
    }
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    int err;                // error code returned from api calls
    size_t t_buf = 50;      // size of str_buffer
    char str_buffer[t_buf]; // auxiliary buffer
    size_t e_buf;           // effective size of str_buffer in use

    size_t global_size; // global domain size for our calculation
    size_t local_size;  // local domain size for our calculation

    const cl_uint num_platforms_ids = 10;                         // max of allocatable platforms
    cl_platform_id platforms_ids[num_platforms_ids];              // array of platforms
    cl_uint n_platforms;                                          // effective number of platforms in use
    const cl_uint num_devices_ids = 10;                           // max of allocatable devices
    cl_device_id devices_ids[num_platforms_ids][num_devices_ids]; // array of devices
    cl_uint n_devices[num_platforms_ids];                         // effective number of devices in use for each platform

    cl_device_id device_id;         // compute device id
    cl_context context;             // compute context
    cl_command_queue command_queue; // compute command queue

    // Get the available platforms:
    err = clGetPlatformIDs(num_platforms_ids, platforms_ids, &n_platforms);
    cl_error(err, "Error: Failed to Scan for Platforms IDs");
    
    // Get the devices ids of the first platform
    err = clGetDeviceIDs(platforms_ids[0], CL_DEVICE_TYPE_ALL, num_devices_ids, devices_ids[0], &(n_devices[0]));
    cl_error(err, "Error: Failed to Scan for Devices IDs");

    // Now, create a context for the first platform and the first device of the platform
    size_t platform_id_index = 0;
    // print the devices of the platform_id_index-th platform id's
    cl_context_properties properties[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platforms_ids[platform_id_index], 0};
    context = clCreateContext(properties, n_devices[platform_id_index], devices_ids[platform_id_index], NULL, NULL, &err);
    cl_error(err, "Failed to create a compute context\n");

    // The command queue is created for the first device of the platform
    size_t device_id_index = 0;
    cl_command_queue_properties proprt[] = {CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0};
    command_queue = clCreateCommandQueueWithProperties(context, devices_ids[platform_id_index][device_id_index], proprt, &err);
    cl_error(err, "Failed to create a command queue\n");
    printf("Command queue created\n");

    // Load kernel source code from file
    // calculate size of the file
    FILE *fileHandler = fopen("histogram_kern.cl", "r");
    fseek(fileHandler, 0, SEEK_END);
    size_t fileSize = ftell(fileHandler);
    rewind(fileHandler);
    // read kernel source into buffer
    char *sourceCode = (char *)malloc(fileSize + 1);
    sourceCode[fileSize] = '\0';
    fread(sourceCode, sizeof(char), fileSize, fileHandler);
    fclose(fileHandler);
    // create program from buffer
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&sourceCode, &fileSize, &err);
    cl_error(err, "Failed to create program with source\n");
    free(sourceCode);
    printf("Program created\n");

    // Build the executable and check errors
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t len;
        char buffer[2048];

        printf("Error: Some error at building process.\n");
        clGetProgramBuildInfo(program, devices_ids[platform_id_index][device_id_index], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);
        exit(-1);
    }
    printf("Program built\n");

    // Create a compute kernel with the program we want to run
    cl_kernel kernel = clCreateKernel(program, "histogram", &err);
    cl_error(err, "Failed to create kernel from the program\n");
    printf("Kernel created\n");

    // Create and initialize the input and output arrays at the host memory
    // firs, load the image
    CImg<unsigned char> img("image.jpg");                        // Load image file "image.jpg" at object img
    // show the og image
    img.display("Image");
    unsigned int numberOfPixels = img.width() * img.height();    // number of pixels of the image
    int arraySize = img.width() * img.height() * img.spectrum(); // number of elements of the array
    float *inputArrayHost = (float *)malloc(arraySize * sizeof(float));
    int *outputArrayHost = (int *)malloc(768 * sizeof(int));    // 768 = 256 * 3
    // fill the array with the image data
    for (int i = 0; i < arraySize; i++)
    {
        inputArrayHost[i] = (float)img.data()[i];
    }
    printf("Image loaded\n");

    // 6. Create OpenCL buffer visible to the OpenCl runtime
    cl_mem in_device_object = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * arraySize, NULL, &err);
    cl_error(err, "Failed to create memory buffer at device\n");
    cl_mem out_device_object = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * 768, NULL, &err);
    cl_error(err, "Failed to create memory buffer at device\n");
    printf("Memory buffers created\n");

    // 7. Write date into the memory object
    err = clEnqueueWriteBuffer(command_queue, in_device_object, CL_TRUE, 0, sizeof(float) * arraySize, inputArrayHost, 0, NULL, NULL);
    cl_error(err, "Failed to enqueue a write command\n");
    printf("Data written into the memory object\n");

    // 8. Set the arguments to the kernel OpenCL object as specified in the kernel code
    // this is: __global float *in, _global float *out, const unsigned int count
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &in_device_object);
    cl_error(err, "Failed to set argument 0\n");
    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &out_device_object);
    cl_error(err, "Failed to set argument 1\n");
    err = clSetKernelArg(kernel, 2, sizeof(int), &numberOfPixels);
    cl_error(err, "Failed to set argument 2\n");
    printf("Arguments set\n");

    // 9. Launch Kernel
    global_size = arraySize;
    err = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_size, NULL, 0, NULL, NULL);
    cl_error(err, "Failed to launch kernel to the device\n");
    printf("Kernel launched\n");

    // 10. Read data form device memory back to host memory
    err = clEnqueueReadBuffer(command_queue, out_device_object, CL_TRUE, 0, sizeof(int) * 768, outputArrayHost, 0, NULL, NULL);
    cl_error(err, "Failed to enqueue a read command\n");
    printf("Data read from the device\n");

    // create histogram.csv file
    FILE *histogramFile = fopen("histogram.csv", "w");
    fprintf(histogramFile, "Red,Green,Blue\n");
    for (int i = 0; i < 256; i++)
    {
        fprintf(histogramFile, "%d,%d,%d\n", outputArrayHost[i], outputArrayHost[i + 256], outputArrayHost[i + 512]);
    }
    fclose(histogramFile);

    // 12. Release all the OpenCL memory objects allocated along this program.
    clReleaseMemObject(in_device_object);
    clReleaseMemObject(out_device_object);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);
    printf("\nAll OpenCL objects released\n");

    return 0;
}
