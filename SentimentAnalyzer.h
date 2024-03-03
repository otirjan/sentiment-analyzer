#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H

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

public:
    void readfile(const char*);
    DSString getLastElement(const DSString&); 
};
#endif