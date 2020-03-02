// This is the naive implementation of in box check with all matrices squeezed to vector
__global__ void inBoxKernel(const float *A, const float *B, int *C, int numElements){
    int i = (blockDim.x * blockIdx.x + threadIdx.x)*2;
    float t11;
    float t12;
    float t21;
    float t22;
    if (i/2 < numElements)
    {
        if ((A[i]<B[0] || (A[i] >B[4]))||((A[i+1]>B[3]) || (A[i+1] <B[7])))
            {
                C[i/2]=-1;
            }
        else
        {
           t11=(A[i]-B[0])*(B[2]-B[0])+(A[i+1]-B[1])*(B[3]-B[1]);
           t12=(A[i]-B[4])*(B[6]-B[4])+(A[i+1]-B[5])*(B[7]-B[5]);
           t21=(A[i]-B[2])*(B[4]-B[2])+(A[i+1]-B[3])*(B[5]-B[3]);
           t22=(A[i]-B[6])*(B[2]-B[6])+(A[i+1]-B[7])*(B[1]-B[7]);
           if (t11>=1e-20 && t12>=1e-20 && t21>=1e-20 && t22>=1e-20) 
           {
                C[i/2]=1;
           }
           else
           {
                C[i/2]=-1;
           }
        }
    }
}

void inBoxLauncher(const float *A, const float *B, int *C, int numElements){
    int threadsPerBlock = 512;
    int blocksPerGrid =(numElements - 1) / threadsPerBlock +1;
    inBoxKernel<<<blocksPerGrid,threadsPerBlock>>>(A, B, C, numElements);
}


