nvcc inBoxcheck.cu -o inBoxcheck.o -c -O2 -DGOOGLE_CUDA=1 -x cu -Xcompiler -fPIC
g++ -std=c++11 tf_inBoxCheck.cpp inBoxcheck.o -o tf_inBoxCheck.so -shared -fPIC -I /home/cwman/software/anaconda3/envs/py27tf/lib/python2.7/site-packages/tensorflow/include -I /usr/local/cuda-8.0/include -I /home/cwman/software/anaconda3/envs/py27tf/lib/python2.7/site-packages/tensorflow/include/external/nsync/public -lcudart -L /usr/local/cuda-8.0/lib64/ -L/home/cwman/software/anaconda3/envs/py27tf/lib/python2.7/site-packages/tensorflow -ltensorflow_framework -O2 -D_GLIBCXX_USE_CXX11_ABI=0