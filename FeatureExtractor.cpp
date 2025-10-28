#include "FeatureExtractor.h"
#include <sstream>
#include <algorithm>
#include <cctype>

FeatureExtractor::FeatureExtractor() {
    totalInstructions = 0;
}

void FeatureExtractor::reset() {
    opcodeCount.clear();
    registerCount.clear();
    totalInstructions = 0;
}

void FeatureExtractor::parseInstruction(const std::string& line) {
    if (line.empty() || line[0] == '#' || line[0] == '.') {
        return;
    }

    extractOpcodes(line);
    extractRegisters(line);
    totalInstructions++;
}

void FeatureExtractor::extractOpcodes(const std::string& line) {
    std::istringstream iss(line);
    std::string opcode;
    iss >> opcode;

    if (!opcode.empty()) {
        std::transform(opcode.begin(), opcode.end(), opcode.begin(), ::tolower);
        opcodeCount[opcode]++;
    }
}

void FeatureExtractor::extractRegisters(const std::string& line) {
    std::vector<std::string> registers = {"rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp",
                                         "eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp"};

    for (const auto& reg : registers) {
        if (line.find(reg) != std::string::npos) {
            registerCount[reg]++;
        }
    }
}

int FeatureExtractor::countLibraryCalls(const std::string& code, const std::string& pattern) {
    int count = 0;
    size_t pos = 0;
    while ((pos = code.find(pattern, pos)) != std::string::npos) {
        count++;
        pos += pattern.length();
    }
    return count;
}

int FeatureExtractor::countJumps(const std::string& code) {
    int jumpCount = 0;
    std::istringstream stream(code);
    std::string line;

    while (std::getline(stream, line)) {
        std::string lower = line;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        if (lower.find("jmp") != std::string::npos || 
            lower.find("je") != std::string::npos ||
            lower.find("jne") != std::string::npos ||
            lower.find("jg") != std::string::npos ||
            lower.find("jl") != std::string::npos) {
            jumpCount++;
        }
    }
    return jumpCount;
}

int FeatureExtractor::countCalls(const std::string& code) {
    int callCount = 0;
    std::istringstream stream(code);
    std::string line;

    while (std::getline(stream, line)) {
        std::string lower = line;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        if (lower.find("call") != std::string::npos) {
            callCount++;
        }
    }
    return callCount;
}

std::vector<double> FeatureExtractor::extractFeatures(const std::string& assemblyCode) {
    reset();

    std::istringstream stream(assemblyCode);
    std::string line;

    while (std::getline(stream, line)) {
        parseInstruction(line);
    }

    std::vector<double> features;

    features.push_back(totalInstructions);
    features.push_back(opcodeCount["mov"]);
    features.push_back(opcodeCount["push"]);
    features.push_back(opcodeCount["pop"]);
    features.push_back(opcodeCount["add"]);
    features.push_back(opcodeCount["sub"]);
    features.push_back(opcodeCount["call"]);
    features.push_back(countJumps(assemblyCode));
    features.push_back(countCalls(assemblyCode));

    features.push_back(countLibraryCalls(assemblyCode, "malloc"));
    features.push_back(countLibraryCalls(assemblyCode, "free"));
    features.push_back(countLibraryCalls(assemblyCode, "_Z"));
    features.push_back(countLibraryCalls(assemblyCode, "std::"));
    features.push_back(countLibraryCalls(assemblyCode, "PyObject"));
    features.push_back(countLibraryCalls(assemblyCode, "Py_"));
    features.push_back(countLibraryCalls(assemblyCode, "runtime."));
    features.push_back(countLibraryCalls(assemblyCode, "fmt."));

    features.push_back(registerCount["rax"]);
    features.push_back(registerCount["rbx"]);
    features.push_back(registerCount["rcx"]);

    return features;
}
