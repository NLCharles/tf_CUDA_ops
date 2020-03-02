## InBox check 2d
<font size=5>This program takes 2 inputs: </font><br/>
>pts, shape :nx2 ,input points to perform in or out box check<br/>
>box, shape :4x2 ,bounding box<br/>
    
<font size=5>and returns a vector of length n ranging from {-1,0,1} </font><br/>
>-1:outside box <br/>
>1 :inside or on the edge of the box<br/>
>0 :computation error for the element, which occurs only  when gpu computation errs<br/>

requirement:<br/>
>CUDA-8.0 or higher<br/>
>tensorflow 1.4.0 or higher<br/>
<font size=5>run compile after change the include and library path to your own tensorflow and cuda path<br/></font>
