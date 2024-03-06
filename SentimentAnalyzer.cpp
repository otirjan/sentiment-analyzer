#include "SentimentAnalyzer.h"
#include "DSString.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>

void SentimentAnalyzer::train(const DSString& trainingDataFile) {
    std::ifstream file(trainingDataFile.toStdString()); // Convert DSString to std::string to open file
    if (!file.is_open()) {
        std::cerr << "Failed to open training data file: " << trainingDataFile << std::endl;
        return;
    }

    DSString line;
    std::string tempLine;
    while (std::getline(file, tempLine)) { // Read each line from the file

        line = tempLine.c_str(); // Convert std::string to DSString

        // Tokenize the line to extract sentiment, tweet ID, and tweet content
        auto tokens = line.tokenize(',');
        if (tokens.size() < 6) continue; // Ensure the line has sufficient tokens

        // Assuming the first token is the sentiment and the last token is the tweet content
        DSString sentiment = tokens[0];
        DSString id = tokens[1];
        //std::cout << "Processing Tweet ID: " << id << std::endl;

        DSString tweetContent = tokens[5];
        DSString cleanedTweet = tweetContent.cleanString(tweetContent); // Clean and use the last token as tweet content

        // Further tokenize the tweet content to analyze individual words
        auto words = cleanedTweet.tokenize(' ');
        for (auto& word : words) { 
            if (word.length() <= 2) continue; // Skip short words

            // Update word counts for sentiment analysis
            if (sentiment == "4") { // Positive sentiment
                positiveWordCounts[word]++;
            //std::cout << "Positive Word: " << word << " - Count: " << positiveWordCounts[word] << std::endl;
            } else if (sentiment == "0") { // Negative sentiment
                negativeWordCounts[word]++;
                //std::cout << "Negative Word: " << word << " - Count: " << negativeWordCounts[word] << std::endl;
            }
        }
    }

    // Close the file after processing
    file.close();
    std::cout << "Training completed with " << positiveWordCounts.size() << " positive and " 
              << negativeWordCounts.size() << " negative words identified." << std::endl;
    std::cout << "Positive Words Counts:" << std::endl;
for (const auto& pair : positiveWordCounts) {
    std::cout << pair.first << ": " << pair.second << std::endl;
}

std::cout << "Negative Words Counts:" << std::endl;
for (const auto& pair : negativeWordCounts) {
    std::cout << pair.first << ": " << pair.second << std::endl;
}
}



void SentimentAnalyzer::predict(const DSString& testingDataFile, const DSString& outputPredictionsFile) {
    std::ifstream testFile(testingDataFile.toStdString());
    std::ofstream outFile(outputPredictionsFile.toStdString());

    if (!testFile.is_open()) {
        std::cerr << "Failed to open testing data file: " << testingDataFile << std::endl;
        return;
    }

    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputPredictionsFile << std::endl;
        return;
    }

    std::string line;
    bool isFirstLine = true;  // Flag to track if it's on the first line of data file (the header)
    while (std::getline(testFile, line)) {
        //get rid of first line/header, ask if first token is id
        if (isFirstLine) {
        isFirstLine = false;  // Skip the first line and continue to the next iteration
        continue;
        }

        DSString DSline = line.c_str();  
        auto tokens = DSline.tokenize(',');  
    
        if (tokens.size() < 5) continue;  

        DSString id = tokens[0];  // id is 0th element in test file
        DSString tweetContent = tokens[4]; //tweet is 4th element in test file
        DSString cleanedTweet = tweetContent.cleanString(tweetContent);  // Clean and use the last token as tweet content

        int positiveScore = 0, negativeScore = 0;
        auto words = cleanedTweet.tokenize(' ');  // Tokenize the tweet content to analyze individual words
        for (const auto& word : words) {
            if (positiveWordCounts.find(word) != positiveWordCounts.end()) {
                positiveScore += positiveWordCounts[word];
            }
            if (negativeWordCounts.find(word) != negativeWordCounts.end()) {
                negativeScore += negativeWordCounts[word];
            }
        }
         // Predict sentiment: '4' for positive, '0' for negative
        DSString predictedSentiment = (positiveScore > negativeScore) ? "4" : "0";
        outFile << predictedSentiment << "," << id << std::endl;  // Write prediction to file
        std::cout << predictedSentiment << "," << id << std::endl;
    }
    testFile.close();
    outFile.close();
    std::cout << "Prediction completed. Results written to " << outputPredictionsFile << std::endl;
}


    



