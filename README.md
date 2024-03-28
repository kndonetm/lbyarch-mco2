# MCO2

## Benchmarking Results
Below are the benchmarking results for the dot product operation for vectors of size $2^{20}$, $2^{24}$, and $2^{29}$. $2^{29}$ was used as the largest vector size for the test results due to the hardware being unable to support vectors of size $2^{30}$ or higher.

The columns of each benchmark result refer to the following:

- C Time: Time (in seconds) to run the dot product operation, written in C.
- ASM Time: Time (in seconds) to run the dot product operation, written in x86-64 Assembly.
- C Answer: Result of the C dot product operation. This column is used as a reference to check the correctness of the corresponding Assembly operation.
- ASM Answer: Result of the Assembly dot product operation. 

### Debug Mode
#### Benchmarking results for vectors of size 2^20 in debug mode
![Debug 2^20 results](/images/debug_20.png)

#### Benchmarking results for vectors of size 2^24 in debug mode
![Debug 2^24 results](/images/debug_24.png)

#### Benchmarking results for vectors of size 2^29 in debug mode
![Debug 2^29 results](/images/debug_29.png)

### Release Mode
#### Benchmarking results for vectors of size 2^20 in release mode
![Release 2^20 results](/images/release_20.png)

#### Benchmarking results for vectors of size 2^24 in release mode
![Release 2^24 results](/images/release_24.png)

#### Benchmarking results for vectors of size 2^29 in release mode
![Release 2^29 results](/images/release_29.png)

## Analysis
For all three benchmarks conducted in debug mode, the Assembly program performed significantly better than in debug mode, while the opposite is true for all three benchmarks in release mode. Without optimizations and with debug hooks in place, the C program incurred a significant overhead, most likely due to the values in C being repeatedly stored to and retrieved from memory. However, in release mode, the compiler was allowed to optimize the C code, leading to better performance compared to handwritten Assembly code. This may be because the C code could use vector SIMD operations to speed up the calculations, among other optimizations, to reduce the number of calculations needed to achieve the final output. The assembly code, on the other hand, is stuck to using scalar SIMD operations for floating point calculations.
