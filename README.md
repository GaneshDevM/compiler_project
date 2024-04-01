---

# Memory Instruction Counter LLVM Pass

This project implements an LLVM pass that counts memory and non-memory instructions in basic blocks of LLVM IR functions.

## Table of Contents

- [Introduction](#introduction)
- [Usage](#usage)
- [Building](#building)
- [Example](#example)
- [License](#license)

## Introduction

This LLVM pass, named `MemoryInstructionCounter`, is designed to analyze LLVM IR code and provide insights into the memory usage within functions. It counts both memory and non-memory instructions in each basic block of a function, helping developers and researchers understand memory access patterns and optimize code accordingly.

## Usage

To use this LLVM pass, follow these steps:

1. Compile the LLVM pass into a shared library using `clang++`:

   ```
   clang++ -shared -o memory-instruction-counter.so memory-instruction-counter.cpp `llvm-config --cxxflags --ldflags --libs` -fPIC
   ```

2. Compile your input source file into LLVM IR using `clang++` with the `-S` and `-emit-llvm` flags:

   ```
   clang++ -S -emit-llvm input.cpp -o input.ll
   ```

3. Apply the LLVM pass to the LLVM IR code using `opt` (the LLVM optimizer):

   ```
   opt -load ./memory-instruction-counter.so -memory-instruction-counter < input.ll > /dev/null -enable-new-pm=0
   ```

This will generate output showing the count of memory and non-memory instructions in each basic block of the input LLVM IR code.

## Building

To build the LLVM pass, ensure you have LLVM installed and configured properly. Then compile the `memory-instruction-counter.cpp` file into a shared library using `clang++`, linking against LLVM libraries and headers using `llvm-config`.


---

## Example Output

### Input: GCD Calculation Program

```cpp
#include <iostream>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1 = 48;
    int num2 = 18;
    std::cout << "GCD of " << num1 << " and " << num2 << " is: " << gcd(num1, num2) << std::endl;
    return 0;
}
```

### Output:

```
Function __cxx_global_var_init:
Basic Block ID: 1
Memory Instructions: 2
Non-Memory Instructions: 1

Function _Z3gcdii:
Basic Block ID: 2
Memory Instructions: 2
Non-Memory Instructions: 4
Basic Block ID: 3
Memory Instructions: 1
Non-Memory Instructions: 2
Basic Block ID: 4
Memory Instructions: 7
Non-Memory Instructions: 2
Basic Block ID: 5
Memory Instructions: 1
Non-Memory Instructions: 1

Function main:
Basic Block ID: 6
Memory Instructions: 15
Non-Memory Instructions: 4

Function _GLOBAL__sub_I_input.cpp:
Basic Block ID: 7
Memory Instructions: 1
Non-Memory Instructions: 1
```

The output above illustrates the analysis performed by the `Memory Instruction Counter` pass on the GCD calculation program. It shows the count of memory and non-memory instructions within each function and basic block of the program. 

For instance:
- The `gcd()` function contains multiple basic blocks, each with a count of memory and non-memory instructions.
- The `main()` function, responsible for invoking the `gcd()` function and printing the result, also has its memory and non-memory instruction counts displayed.

This output provides valuable insights into the memory usage and instruction composition of the GCD calculation program, aiding in understanding its internal workings and potential areas for optimization.


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
