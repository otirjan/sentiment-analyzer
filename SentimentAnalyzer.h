#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H


#include "DSString.h"
#include <map>
#include <vector>

class SentimentAnalyzer {
public:
    void train(const DSString& trainingDataFile);
    void predict(const DSString& testingDataFile, const DSString& outputResults);
    void evaluatePredictions(const DSString& testingSentDataFile, const DSString& outputAccuracy);

private:
    std::map<DSString, int> positiveWordCounts; // Counts of words in positive tweets
    std::map<DSString, int> negativeWordCounts; // Counts of words in negative tweets

    std::map<DSString, std::vector<DSString>> trainingData; // Map of tweet IDs to tweets and sentiments
    std::map<DSString, int> wordSentiments; // Map of words to their sentiment scores

  std::map<DSString, DSString> predictions; //map of tweet ids to their actual sentiment


};








#endif