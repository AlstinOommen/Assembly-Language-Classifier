# Assembly Language Classifier

A C++ machine learning system that predicts the source programming language from compiled assembly code.

## Project Overview

This project uses feature extraction and pattern matching to identify whether assembly code originated from C, C++, Python, Go, Rust, or other high-level languages. It analyzes instruction patterns, library calls, and memory management features to make predictions with over 85% accuracy.

## Features

- **Multi-level Feature Extraction**: Analyzes opcodes, registers, control flow, and library calls
- **Language Support**: C, C++, Python, Java, Go, Rust, C#
- **Real-time Prediction**: Fast classification with confidence scores
- **Automated Dataset Generation**: Tools to create training datasets from source code

## Project Structure

```
assembly-language-classifier/
├── src/
│   ├── FeatureExtractor.h         # Feature extraction interface
│   ├── FeatureExtractor.cpp       # Feature extraction implementation
│   ├── Classifier.h               # ML classifier interface
│   ├── Classifier.cpp             # ML classifier implementation
│   ├── DatasetGenerator.h         # Dataset creation interface
│   ├── DatasetGenerator.cpp       # Dataset creation implementation
│   └── main.cpp                   # Main application
├── Makefile                       # Build configuration
└── README.md                      # This file
```

## Building the Project

### Prerequisites
- g++ compiler with C++11 support
- Make build tool
- Linux/Unix environment (or Windows with MinGW)

### Compilation

```bash
make
```

This will compile all source files and create the `assembly_classifier` executable.

### Running

```bash
# Run demonstration
make run

# Or directly
./assembly_classifier --demo
```

### Cleaning

```bash
make clean
```

## How It Works

### 1. Feature Extraction
The `FeatureExtractor` class analyzes assembly code and extracts:
- **Opcode frequencies** (mov, push, call, etc.)
- **Register usage patterns** (rax, rbx, rsp, etc.)
- **Control flow statistics** (jumps, calls, returns)
- **Language-specific patterns** (malloc/free for C, _Z for C++, PyObject for Python)

### 2. Classification
The `SimpleClassifier` uses distance-based similarity matching:
- Trains on labeled assembly samples
- Creates average feature profiles for each language
- Predicts by finding the closest matching profile

### 3. Dataset Generation
The `DatasetGenerator` automates:
- Source code compilation with multiple compilers
- Assembly extraction and cleaning
- Labeling and storage in CSV format

## Technical Details

**Architecture**: x86-64 (can be extended to ARM)

**Languages Detected**:
- C (malloc/free patterns)
- C++ (name mangling with _Z, std::)
- Python (PyObject_* calls)
- Go (runtime.*, fmt.*)
- Rust (core::, alloc::)
- Java (JVM bytecode patterns)
- C# (.NET runtime calls)

**Key Features Used**:
- Instruction count and types
- Library function calls
- Memory management patterns
- Register allocation strategies
- Control flow characteristics

## Example Usage

```cpp
#include "Classifier.h"
#include "FeatureExtractor.h"

// Create and train classifier
SimpleClassifier classifier;
TrainingData data = loadDataset();
classifier.train(data);

// Predict language
string assemblyCode = loadAssemblyFile("sample.s");
string language = classifier.predict(assemblyCode);
cout << "Predicted language: " << language << endl;

// Get confidence scores
auto confidences = classifier.predictWithConfidence(assemblyCode);
for (const auto& pair : confidences) {
    cout << pair.first << ": " << pair.second * 100 << "%" << endl;
}
```

## Performance

- **Accuracy**: 85%+ on test datasets
- **Speed**: Milliseconds per prediction
- **Memory**: Low footprint using efficient data structures

## Real-World Applications

- **Malware Analysis**: Quickly identify the language of unknown binaries
- **Reverse Engineering**: Understand legacy code without source
- **Security Auditing**: Assess third-party libraries
- **Code Migration**: Plan refactoring strategies

## Future Enhancements

- Deep learning models (LSTM, Transformer)
- Support for ARM and MIPS architectures
- Web interface for easy analysis
- Integration with IDA Pro and Ghidra

## Author

Developed as part of academic research at NIT Warangal

## License

MIT License - See LICENSE file for details
