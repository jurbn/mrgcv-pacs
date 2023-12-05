__kernel void flip(
    __global float *in,
    __global float *out,
    const unsigned int width){

    int i = get_global_id(0);
    // get the row of the element
    int row = i / width;
    // get the column of the element
    int col = i % width;
    // calculate the index of the element in the flipped array
    int index = row * width + (width - col - 1);
    // flip the element
    out[index] = in[i];
}