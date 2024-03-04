#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H


#include "DSString.h"
#include <map>
#include <vector>

class SentimentAnalyzer {
public:
    void train(const DSString& trainingDataFile);
    void predict(const DSString& testDataFile, const DSString& resultsFile);
    void evaluatePredictions(const DSString& groundTruthFile, const DSString& resultsFile, const DSString& evaluationFile);

private:
    std::map<DSString, int> positiveWordCounts; // Counts of words in positive tweets
    std::map<DSString, int> negativeWordCounts; // Counts of words in negative tweets

    std::map<DSString, std::vector<DSString>> trainingData; // Map of tweet IDs to tweets and sentiments
    std::map<DSString, int> wordSentiments; // Map of words to their sentiment scores
};







/*
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include "DSString.h"
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class SentimentAnalyzer{
private:
   DSString cleanedTweetPos, cleanedTweetNeg;
    DSString DSposTweet;
    DSString DSnegTweet;
    vector <DSString> allPositiveTokens;
    vector <DSString> allNegativeTokens;
    vector <DSString> wordsPos;
    vector <DSString> wordsNeg;
    map<DSString, int> Words;

public:
    void readfile(const char*);
    DSString getFinalEntry(const DSString&); 
    void processTweets(); 
}; 
*/
#endif