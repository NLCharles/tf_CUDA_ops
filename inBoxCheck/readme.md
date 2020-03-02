## InBox check 2d
This program takes 2 inputs: <br/>
>>2d point matrix pts, nx2 <br/>
>>2d box, 4x2 <br/>
    
and returns a vector of length n ranging from {-1,0,1} <br/>
>>-1:outside box <br/>
>>1 :inside or on the edge of the box<br/>
>>0 :computation error for the element, which occurs only  when gpu computation errs<br/>

requirement:<br/>
>>CUDA-8.0 or higher<br/>
>>tensorflow 1.4.0 or higher<br/>
>>run compile after change the include and library path to your own tensorflow and cuda path<br/>
