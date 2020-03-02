#include <iostream>
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/shape_inference.h"
#include "tensorflow/core/framework/common_shape_fns.h"
#include <cuda_runtime.h>

using namespace tensorflow;


REGISTER_OP("InBoxCheck")
    .Input("pts: float32")
    .Input("box: float32")
    .Output("indinbox: int32")
    .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
        ::tensorflow::shape_inference::ShapeHandle dims1; // n * 2:points
        c->WithRank(c->input(0), 2, &dims1);
        ::tensorflow::shape_inference::ShapeHandle dims2; // 8 * 2:box
        c->WithRank(c->input(1), 2, &dims2);
        ::tensorflow::shape_inference::ShapeHandle output = c->MakeShape({c->Dim(dims1, 0)});// 2n
        
        c->set_output(0, output);
        return Status::OK();
  });

void inBoxLauncher(const float *A, const float *B, int *C, int numElements);
class InBoxGPUOp: public OpKernel{
    public:
        explicit InBoxGPUOp(OpKernelConstruction* context):OpKernel(context){}
        void Compute(OpKernelContext * context)override{
            const Tensor& pts_tensor=context->input(0);
            const Tensor& box_tensor=context->input(1);
            auto pts_flat=pts_tensor.flat<float>();
            auto box_flat=box_tensor.flat<float>();
            const float *pts=&(pts_flat(0));
            const float *box=&(box_flat(0));
            OP_REQUIRES(context,pts_tensor.dims()==2,
                        errors::InvalidArgument("inBox expects pts (numpts*2) input shape"));
            OP_REQUIRES(context,box_tensor.shape().dim_size(0)==4 &&box_tensor.shape().dim_size(1)==2,
                        errors::InvalidArgument("inBox expects 4*2 box shape"));
            int numpts=pts_tensor.shape().dim_size(0);
            Tensor *out_tensor=NULL;
            OP_REQUIRES_OK(context,context->allocate_output(0,TensorShape{numpts},&out_tensor));
            auto out_flat=out_tensor->flat<int>();
            int *out=&(out_flat(0));
            Tensor temp_tensor;
            inBoxLauncher(pts, box, out,  numpts);
        }
};
REGISTER_KERNEL_BUILDER(Name("InBoxCheck").Device(DEVICE_GPU), InBoxGPUOp);










