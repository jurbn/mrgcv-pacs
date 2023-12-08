__kernel void histogram(
    __global float *in,
    __global int *out,
    const unsigned int numberOfPixels)
    {
    // this is the index of the pixel we're working on
    int i = get_global_id(0);
    // channel will be 0 if red (0-255), 1 if green (256-511), 2 if blue (512-767)
    int channel = (int) (i / (numberOfPixels / 3.0f));  // if i is 0-255, channel will be 0, if i is 256-511, channel will be 1, if i is 512-767, channel will be 2
    int value = (int) in[i];
    int offset = value + (channel << 8);    // << 8 multiplies by 256 (cause it shifts 8 bit positions)
    out[offset] ++;
}