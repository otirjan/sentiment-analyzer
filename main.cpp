#include <iostream>
#include <istream>
#include "SentimentAnalyzer.h"
#include "DSString.h"

int main(int argc, char** argv)
{  
    std::cout << "I will be a sentiment analyzer!" << std::endl;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <training_data_file>" << std::endl;
        return 1;
    }
   
    
    DSString trainingDataFile = argv[1]; 
    DSString testingDataFile = argv[2];
    DSString outputPredictionsFile = argv[3];

    SentimentAnalyzer sa;
    sa.train(trainingDataFile);
    sa.predict(testingDataFile, outputPredictionsFile);

    

    return 0;
}