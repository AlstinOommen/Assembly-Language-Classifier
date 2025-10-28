#ifndef CLASSIFIER_H
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
