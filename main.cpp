#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "FeatureExtractor.h"
#include "Classifier.h"
#include "DatasetGenerator.h"

using namespace std;

void printHeader() {
    cout << "========================================" << endl;
    cout << "  Assembly Language Classifier" << endl;
    cout << "  Predicting Source Languages from ASM" << endl;
    cout << "========================================" << endl << endl;
}

void demonstrateClassification() {
    cout << "Running demonstration..." << endl << endl;

    string cCode = R"(
        push rbp
        mov rbp, rsp
        sub rsp, 16
        call malloc
        mov [rbp-8], rax
        call free
        mov rsp, rbp
        pop rbp
        ret
    )";

    string cppCode = R"(
        push rbp
        mov rbp, rsp
        sub rsp, 16
        call _Znwm
        mov [rbp-8], rax
        call _ZdlPv
        mov rsp, rbp
        pop rbp
        ret
    )";

    string pythonCode = R"(
        push rbp
        mov rbp, rsp
        call PyObject_CallMethod
        mov [rbp-8], rax
        call Py_INCREF
        call Py_DECREF
        mov rsp, rbp
        pop rbp
        ret
    )";

    string goCode = R"(
        push rbp
        mov rbp, rsp
        call runtime.newobject
        mov [rbp-8], rax
        call runtime.gcWriteBarrier
        call fmt.Println
        mov rsp, rbp
        pop rbp
        ret
    )";

    TrainingData trainData;

    FeatureExtractor extractor;

    for (int i = 0; i < 50; i++) {
        trainData.features.push_back(extractor.extractFeatures(cCode));
        trainData.labels.push_back("C");
    }

    for (int i = 0; i < 50; i++) {
        trainData.features.push_back(extractor.extractFeatures(cppCode));
        trainData.labels.push_back("C++");
    }

    for (int i = 0; i < 50; i++) {
        trainData.features.push_back(extractor.extractFeatures(pythonCode));
        trainData.labels.push_back("Python");
    }

    for (int i = 0; i < 50; i++) {
        trainData.features.push_back(extractor.extractFeatures(goCode));
        trainData.labels.push_back("Go");
    }

    SimpleClassifier classifier;
    classifier.train(trainData);

    cout << "\nTesting predictions:\n" << endl;

    cout << "Sample 1 (C code):" << endl;
    string pred1 = classifier.predict(cCode);
    cout << "Predicted: " << pred1 << endl;
    auto conf1 = classifier.predictWithConfidence(cCode);
    cout << "Confidences:" << endl;
    for (const auto& p : conf1) {
        cout << "  " << p.first << ": " << (p.second * 100) << "%" << endl;
    }
    cout << endl;

    cout << "Sample 2 (C++ code):" << endl;
    string pred2 = classifier.predict(cppCode);
    cout << "Predicted: " << pred2 << endl;
    auto conf2 = classifier.predictWithConfidence(cppCode);
    cout << "Confidences:" << endl;
    for (const auto& p : conf2) {
        cout << "  " << p.first << ": " << (p.second * 100) << "%" << endl;
    }
    cout << endl;

    cout << "Sample 3 (Python code):" << endl;
    string pred3 = classifier.predict(pythonCode);
    cout << "Predicted: " << pred3 << endl;
    auto conf3 = classifier.predictWithConfidence(pythonCode);
    cout << "Confidences:" << endl;
    for (const auto& p : conf3) {
        cout << "  " << p.first << ": " << (p.second * 100) << "%" << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    printHeader();

    if (argc > 1 && string(argv[1]) == "--demo") {
        demonstrateClassification();
    } else {
        cout << "Usage:" << endl;
        cout << "  " << argv[0] << " --demo    : Run demonstration" << endl;
        cout << "  " << argv[0] << " --help    : Show this help" << endl;
    }

    return 0;
}
