#include "Classifier.h"
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
