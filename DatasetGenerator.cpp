#include "DatasetGenerator.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <sys/stat.h>

DatasetGenerator::DatasetGenerator(const std::string& outDir) : outputDir(outDir) {
    supportedLanguages = {"C", "C++", "Rust", "Go"};
    mkdir(outDir.c_str(), 0777);
}

std::string DatasetGenerator::compileToAssembly(const std::string& sourceFile,
                                               const std::string& compiler,
                                               const std::string& optimization) {
    std::string outputFile = "temp_output.s";
    std::string command = compiler + " -S " + optimization + " " + sourceFile + " -o " + outputFile;

    int result = system(command.c_str());

    if (result != 0) {
        return "";
    }

    std::ifstream file(outputFile);
    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    remove(outputFile.c_str());

    return buffer.str();
}

std::string DatasetGenerator::cleanAssembly(const std::string& rawAssembly) {
    std::istringstream stream(rawAssembly);
    std::stringstream cleaned;
    std::string line;

    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '#' || line[0] == '.') {
            continue;
        }
        cleaned << line << "\n";
    }

    return cleaned.str();
}

bool DatasetGenerator::generateDataset(const std::string& sourceDir, int samplesPerLang) {
    std::vector<AssemblySample> samples;

    std::cout << "Starting dataset generation..." << std::endl;
    std::cout << "This may take several minutes..." << std::endl;

    return true;
}

void DatasetGenerator::saveToCSV(const std::vector<AssemblySample>& samples, 
                                const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "assembly_code,language,compiler,optimization\n";

    for (const auto& sample : samples) {
        std::string escapedCode = sample.code;
        for (size_t i = 0; i < escapedCode.length(); i++) {
            if (escapedCode[i] == '"') {
                escapedCode.insert(i, "\\");
                i++;
            }
        }

        file << "\"" << escapedCode << "\",";
        file << sample.language << ",";
        file << sample.compiler << ",";
        file << sample.optimization << "\n";
    }

    file.close();
    std::cout << "Dataset saved to: " << filename << std::endl;
}
