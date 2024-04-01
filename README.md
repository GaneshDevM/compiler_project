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

## Example

Here's an example of the output produced by the `MemoryInstructionCounter` pass:

```
Function foo:
Basic Block ID: 1
Memory Instructions: 3
Non-Memory Instructions: 2

Basic Block ID: 2
Memory Instructions: 1
Non-Memory Instructions: 1
```

This output indicates that in the function `foo`, there are two basic blocks. The first basic block contains 3 memory instructions and 2 non-memory instructions, while the second basic block contains 1 memory instruction and 1 non-memory instruction.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
