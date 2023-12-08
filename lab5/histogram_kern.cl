__kernel void histogram(
    __global float *in,
    __global int *out)
    {
    // this is the index of the pixel we're working on
    int i = get_global_id(0);
    // get wether the index corresponds to a r, g or b value
    // if (i % 3 == 0) // if red channel
    //     out[(int) in[i]*255]++; // increment by one this shade of red
    // else if (i % 2 == 0)    // if blue channel
    //     out[(int)(in[i]*255)+512]++;    // incrrement by one this shade of blue
    // else    // if green chanel
    //     out[(int)(in[i]*255)+256]++;    // increment by one this shade of green

    // this is cool, but it could be **optimized**
    // int channel = i % 3;    // we'll get 0 for red, 1 for green and 2 for blue
    // int value = (int) (in[i] * 255.0f);
    // int offset = value + (channel << 8);    // << 8 multiplies by 256 (cause it shifts 8 bit positions)
    // out[offset] ++;

    out[(int) (in[i] * 255.0f) + (i % 3 << 8)] ++;  // << 8 multiplies by 256 (cause it shifts 8 bit positions)
}