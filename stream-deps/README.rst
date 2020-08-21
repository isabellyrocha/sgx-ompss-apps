Stream Benchmark
----------------

The stream benchmark is part of the HPC Challenge benchmarks (http://icl.cs.utk.edu/hpcc/) and here
we present an implementation version without barriers. In this barrier-free version, 
functions that operate on one part of the array are interleaved and the OmpSs runtime keeps the correctness
by means of the detection of data-dependences.
