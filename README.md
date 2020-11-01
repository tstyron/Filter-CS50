# Filter-CS50
Filters images

Relevant: this program filters images. One relevant piece of this program is the definition of a structure RBGTRIPLE –this definition occurs within bmp.h.
The structure RGBTRIPLE is effectively a pixel. Within each structure, there is a red, blue, and green value (each with a min value of 0 and max of 255). 

Another relevant pieceof this program is the two dimensional array: images[i][j]. Each "image" is an array of "height" many rows and "width" RGBTRIPLEs (pixels).

So, if "image" represents an entire picture i.e. jpg or bmp, then image[0][0] is the upper-left corner pixel, image[0][1] is the pixel to the right of it
image[0][2] is two pixels to the right of it i.e. the second pixel of the first row of pixels, and so on.

Similarly, image[1][0] would be the first pixel of the second row of pixels, image[1][1] would be the second pixel in the second row of pixels and so on. 

The code for each filter (Grayscale, Sepia, Mirror, and Blur) is contained within "helpers.c". Within helpers.c, each filter is defined as its own function which
are implemented within "filter.c". None of the code within filter.c needs changing.

The only fault with this program is that the filter "Blur" is not currently working. 

The issue is that the function "blur" cannot accurately blur any pixels on the right edge or bottom edge of the image. Pixels touching the top edge, left edge, and
no edge are currently blurred by the function without fault.

Therefore, the function "blur" contained within helpers.c is the only code that needs to be debugged.

For your reference, this is how Blur should work on any given pixel: A pixel is correctly blurred when it takes the average of its own RGB values as well as the 
pixels surrounding it (those within one row and one column), and sets its own RGB values to the average.

However, the code for any given pixel is not the same. For example, a pixel in a corner only has 3 pixels within one row and one column of itself. Similarly, 
a pixel on an edge (but not a corner) has 5 pixels surrounding it, and a pixel touching no edge has 8 pixels surrounding it.

Each pixel, as it iterates through the function, passes through "else if" conditions to determine the location of the pixel. All of the pixels pass through the 
correct condition, meaning an upper-right corner pixel will pass through the correct "else if" condition, this is true for all pixels. 

Therefore, the error in blurring right edge and bottom edge pixels must be caused by some fault in the conditions themselves. This means that the averaging of the
surrounding RGB values (and its own RGB values) within the conditions (those conditions being upper-right corner pixels, bottom-right corner pixels, bottom-left
corner pixels, bottom edge pixels, and right edge pixels) must be faulty.
