##InBox check 2d
This program takes 2 inputs: 
    2d point matrix pts, nx2
    2d box, 4x2
and returns a vector of length n ranging from {-1,0,1}
-1:outside box
1 :inside or on the edge of the box
0 :computation error for the element, which occurs only when gpu computation errs

requirement:
CUDA-8.0 or higher
tensorflow 1.4.0 or higher
run compile after change the include and library path to your own tensorflow and cuda path
