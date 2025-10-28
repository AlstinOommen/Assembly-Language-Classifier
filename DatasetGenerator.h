#ifndef DATASET_GENERATOR_H
#define DATASET_GENERATOR_H

#include <string>
#include <vector>
#include <fstream>

struct AssemblySample {
    std::string code;
    std::string language;
    std::string compiler;
    std::string optimization;
};

class DatasetGenerator {
private:
    std::string outputDir;
    std::vector<std::string> supportedLanguages;

    std::string compileToAssembly(const std::string& sourceFile, 
                                  const std::string& compiler,
                                  const std::string& optimization);
    std::string cleanAssembly(const std::string& rawAssembly);

public:
    DatasetGenerator(const std::string& outDir);
    bool generateDataset(const std::string& sourceDir, int samplesPerLang);
    void saveToCSV(const std::vector<AssemblySample>& samples, const std::string& filename);
};

#endif
