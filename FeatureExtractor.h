#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

class FeatureExtractor {
private:
    std::map<std::string, int> opcodeCount;
    std::map<std::string, int> registerCount;
    int totalInstructions;

    void parseInstruction(const std::string& line);
    void extractOpcodes(const std::string& line);
    void extractRegisters(const std::string& line);

public:
    FeatureExtractor();
    std::vector<double> extractFeatures(const std::string& assemblyCode);
    void reset();

    int countLibraryCalls(const std::string& code, const std::string& pattern);
    int countJumps(const std::string& code);
    int countCalls(const std::string& code);
};

#endif
