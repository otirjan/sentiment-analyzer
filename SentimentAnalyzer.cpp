#include "SentimentAnalyzer.h"
#include "DSString.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>

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



void SentimentAnalyzer::predict(const DSString& testingDataFile, const DSString& outputPrediction) {
    std::ifstream testFile(testingDataFile.toStdString());
    std::ofstream outFile(outputPrediction.toStdString());

    if (!testFile.is_open()) {
        std::cerr << "Failed to open testing data file: " << testingDataFile << std::endl;
        return;
    }

    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputPrediction << std::endl;
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
        predictions[id] = predictedSentiment; 
        outFile << predictedSentiment << "," << id << std::endl;  // Write prediction to file
        std::cout << predictedSentiment << "," << id << std::endl;
    }
    testFile.close();
    outFile.close();
    std::cout << "Prediction completed. Results written to " << outputPrediction << std::endl;
}

    

void SentimentAnalyzer::evaluatePredictions(const DSString& testingSentDataFile, const DSString& outputAccuracy) {
    // Open the test dataset file for reading
    std::string filePath = testingSentDataFile.toStdString();
    std::ifstream testFile(filePath);

    // Check if the test dataset file was successfully opened
    if (!testFile.is_open()) {
        std::cerr << "Failed to open test dataset file: " << testingSentDataFile << std::endl;
        return;
    }

    std::string line;
    bool isFirstLine = true;  
    int correctPredictions = 0, totalTweets = 0;  // Variables to track correct predictions and total tweets
    std::vector<std::string> incorrectPredictions; 

    // Loop through each line in the test dataset
    while (std::getline(testFile, line)) {
        if (isFirstLine) {
            isFirstLine = false;  // Skip the header line
            continue;
        }

        DSString DSline = line.c_str();
        auto tokens = DSline.tokenize(',');  // Tokenize the line to extract sentiment and tweet ID

         // Check if the line has exactly 2 tokens (sentiment and ID)
        if (tokens.size() != 2) {
            std::cerr << "Unexpected number of entries in line: " << line << std::endl;
            continue;
        }

         DSString actualSentiment = tokens[0];  // Actual sentiment is the first token
        DSString tweetID = tokens[1];  // Tweet ID is the second token

         // Compare the actual sentiment with the predicted sentiment
        auto predIt = predictions.find(tweetID);  // Find the predicted sentiment for the current tweet ID
        if (predIt != predictions.end()) {
            totalTweets++;  // Increment the total number of tweets processed
            if (predIt->second == actualSentiment) {
                correctPredictions++;  // Increment the number of correct predictions
            } else {
                // Write details of incorrect predictions to the output file
                std::string incorrectPrediction = predIt->second.toStdString() + ", " + actualSentiment.toStdString() + ", " + tweetID.toStdString();
                incorrectPredictions.push_back(incorrectPrediction);
            }
        }
    }
    testFile.close();

        // Now open the output file and write accuracy and incorrect predictions
    std::ofstream outFile(outputAccuracy.toStdString());
    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputAccuracy << std::endl;
        return;
    }
    // Calculate the accuracy of predictions
    double accuracy = (totalTweets > 0) ? static_cast<double>(correctPredictions) / totalTweets : 0.0;
    //write accuracy at beginning of file

    outFile << std::fixed << std::setprecision(3) << accuracy << std::endl;

    for (const auto& prediction : incorrectPredictions) {
    outFile << prediction << std::endl;  // Writes "predicted sentiment, actual sentiment, tweet ID"
    }

    outFile.close();
    std::cout << "Evaluation completed. Results written to " << outputAccuracy << std::endl;
}



/*
    std::ofstream outFileAgain(outputAccuracy.toStdString());
    // Write the calculated accuracy to the output file with 3 decimal places of precision
    outFileAgain << std::fixed << std::setprecision(3) << accuracy << std::endl;

    // Close the files
    
    outFile.close();
    outFileAgain.close();

    // Log completion message to console
    std::cout << "Evaluation completed. Results written to " << outputAccuracy << std::endl;

}
*/


