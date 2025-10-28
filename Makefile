CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

TARGET = assembly_classifier
OBJS = main.o FeatureExtractor.o Classifier.o DatasetGenerator.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp FeatureExtractor.h Classifier.h DatasetGenerator.h
	$(CXX) $(CXXFLAGS) -c main.cpp

FeatureExtractor.o: FeatureExtractor.cpp FeatureExtractor.h
	$(CXX) $(CXXFLAGS) -c FeatureExtractor.cpp

Classifier.o: Classifier.cpp Classifier.h FeatureExtractor.h
	$(CXX) $(CXXFLAGS) -c Classifier.cpp

DatasetGenerator.o: DatasetGenerator.cpp DatasetGenerator.h
	$(CXX) $(CXXFLAGS) -c DatasetGenerator.cpp

clean:
	rm -f $(OBJS) $(TARGET) *.s

run: $(TARGET)
	./$(TARGET) --demo

.PHONY: all clean run
