
# Now create the main application file and classifier
classifier_h = '''#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <string>
#include <map>
#include "FeatureExtractor.h"

struct TrainingData {
    std::vector<std::vector<double>> features;
    std::vector<std::string> labels;
};

class SimpleClassifier {
private:
    FeatureExtractor extractor;
    std::map<std::string, std::vector<double>> languageProfiles;
    std::vector<std::string> knownLanguages;
    
    double calculateSimilarity(const std::vector<double>& f1, 
                              const std::vector<double>& f2);
    
public:
    SimpleClassifier();
    void train(const TrainingData& data);
    std::string predict(const std::string& assemblyCode);
    std::map<std::string, double> predictWithConfidence(const std::string& assemblyCode);
};

#endif
'''

classifier_cpp = '''#include "Classifier.h"
#include <cmath>
#include <algorithm>
#include <iostream>

SimpleClassifier::SimpleClassifier() {
}

double SimpleClassifier::calculateSimilarity(const std::vector<double>& f1,
                                            const std::vector<double>& f2) {
    if (f1.size() != f2.size()) {
        return 0.0;
    }
    
    double distance = 0.0;
    for (size_t i = 0; i < f1.size(); i++) {
        double diff = f1[i] - f2[i];
        distance += diff * diff;
    }
    
    return 1.0 / (1.0 + sqrt(distance));
}

void SimpleClassifier::train(const TrainingData& data) {
    std::map<std::string, std::vector<std::vector<double>>> langFeatures;
    
    for (size_t i = 0; i < data.labels.size(); i++) {
        langFeatures[data.labels[i]].push_back(data.features[i]);
    }
    
    for (const auto& pair : langFeatures) {
        std::string lang = pair.first;
        const auto& features = pair.second;
        
        if (features.empty()) continue;
        
        std::vector<double> avgProfile(features[0].size(), 0.0);
        
        for (const auto& f : features) {
            for (size_t i = 0; i < f.size(); i++) {
                avgProfile[i] += f[i];
            }
        }
        
        for (auto& val : avgProfile) {
            val /= features.size();
        }
        
        languageProfiles[lang] = avgProfile;
        knownLanguages.push_back(lang);
    }
    
    std::cout << "Training complete. Learned " << languageProfiles.size() 
              << " language profiles." << std::endl;
}

std::string SimpleClassifier::predict(const std::string& assemblyCode) {
    std::vector<double> features = extractor.extractFeatures(assemblyCode);
    
    std::string bestLang;
    double bestSimilarity = -1.0;
    
    for (const auto& pair : languageProfiles) {
        double similarity = calculateSimilarity(features, pair.second);
        
        if (similarity > bestSimilarity) {
            bestSimilarity = similarity;
            bestLang = pair.first;
        }
    }
    
    return bestLang;
}

std::map<std::string, double> SimpleClassifier::predictWithConfidence(
    const std::string& assemblyCode) {
    
    std::vector<double> features = extractor.extractFeatures(assemblyCode);
    std::map<std::string, double> confidences;
    
    double totalSimilarity = 0.0;
    
    for (const auto& pair : languageProfiles) {
        double similarity = calculateSimilarity(features, pair.second);
        confidences[pair.first] = similarity;
        totalSimilarity += similarity;
    }
    
    if (totalSimilarity > 0) {
        for (auto& pair : confidences) {
            pair.second /= totalSimilarity;
        }
    }
    
    return confidences;
}
'''

# Create the main application
main_cpp = '''#include <iostream>
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
    
    cout << "\\nTesting predictions:\\n" << endl;
    
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
'''

# Create Makefile
makefile = '''CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

TARGET = assembly_classifier
OBJS = main.o FeatureExtractor.o Classifier.o DatasetGenerator.o

all: $(TARGET)

$(TARGET): $(OBJS)
\t$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp FeatureExtractor.h Classifier.h DatasetGenerator.h
\t$(CXX) $(CXXFLAGS) -c main.cpp

FeatureExtractor.o: FeatureExtractor.cpp FeatureExtractor.h
\t$(CXX) $(CXXFLAGS) -c FeatureExtractor.cpp

Classifier.o: Classifier.cpp Classifier.h FeatureExtractor.h
\t$(CXX) $(CXXFLAGS) -c Classifier.cpp

DatasetGenerator.o: DatasetGenerator.cpp DatasetGenerator.h
\t$(CXX) $(CXXFLAGS) -c DatasetGenerator.cpp

clean:
\trm -f $(OBJS) $(TARGET) *.s

run: $(TARGET)
\t./$(TARGET) --demo

.PHONY: all clean run
'''

# Save all files
files_created = []

with open('FeatureExtractor.h', 'w') as f:
    f.write(feature_extractor_h)
    files_created.append('FeatureExtractor.h')

with open('FeatureExtractor.cpp', 'w') as f:
    f.write(feature_extractor_cpp)
    files_created.append('FeatureExtractor.cpp')

with open('DatasetGenerator.h', 'w') as f:
    f.write(dataset_gen_h)
    files_created.append('DatasetGenerator.h')

with open('DatasetGenerator.cpp', 'w') as f:
    f.write(dataset_gen_cpp)
    files_created.append('DatasetGenerator.cpp')

with open('Classifier.h', 'w') as f:
    f.write(classifier_h)
    files_created.append('Classifier.h')

with open('Classifier.cpp', 'w') as f:
    f.write(classifier_cpp)
    files_created.append('Classifier.cpp')

with open('main.cpp', 'w') as f:
    f.write(main_cpp)
    files_created.append('main.cpp')

with open('Makefile', 'w') as f:
    f.write(makefile)
    files_created.append('Makefile')

print("\n✅ All C++ files created successfully!")
print("\nFiles created:")
for f in files_created:
    print(f"  ✓ {f}")
