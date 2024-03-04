#include "SentimentAnalyzer.h"
#include "DSString.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

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
        std::cout << "Processing Tweet ID: " << id << std::endl;

        DSString tweetContent = tokens[5];
        DSString cleanedTweet = tweetContent.cleanString(tweetContent); // Clean and use the last token as tweet content

        // Further tokenize the tweet content to analyze individual words
        auto words = cleanedTweet.tokenize(' ');
        for (auto& word : words) { 
            if (word.length() <= 2) continue; // Skip short words

            // Update word counts for sentiment analysis
            if (sentiment == "4") { // Positive sentiment
                positiveWordCounts[word]++;
            std::cout << "Positive Word: " << word << " - Count: " << positiveWordCounts[word] << std::endl;
            } else if (sentiment == "0") { // Negative sentiment
                negativeWordCounts[word]++;
                std::cout << "Negative Word: " << word << " - Count: " << negativeWordCounts[word] << std::endl;
            }
        }
    }

    // Close the file after processing
    file.close();
    std::cout << "Training completed with " << positiveWordCounts.size() << " positive and " 
              << negativeWordCounts.size() << " negative words identified." << std::endl;
}






/*
DSString SentimentAnalyzer::getFinalEntry(const DSString& data) { // some tweets have commas, so this helps read it in 
    if (data.back() == '\"') {
        // Find the opening quotation mark for the final entry
        size_t startQuote = data.find('\"', data.length() - 2);
        return data.substring(startQuote + 1, data.length() - startQuote - 2);
    } else {
        // Find the last comma and return everything after it
        size_t lastComma = data.find(',');
        return data.substring(lastComma + 1, data.length() - lastComma -1);
    }
}

    // Processing each tweet
    for (const auto& x : idToSentiment) {
        auto it = idToTweet.find(x.first); // Find id in idToTweet map
        if (it != idToTweet.end()){ // Check if ID exists in map
        std::cout << "Processing tweet with ID " << x.first << ". Initial token count: " << allPositiveTokens.size() << std::endl;
            if (x.second == "4") { 
                DSString DSposTweet = it->second; 
                DSString cleanedTweetPos = DSposTweet.cleanString(DSposTweet); // Cleans DSString
                std::vector<DSString> allPositiveTokens = cleanedTweetPos.tokenize(); // Tokenizes the DSString

                // Remove tokens with less than 3 characters
                //std::remove_if moves all short tokens to the end of the vector, then erase method erases them from the vector as a whole; consulted internet for how to use this.

                allPositiveTokens.erase(std::remove_if(allPositiveTokens.begin(), allPositiveTokens.end(),
                                                       [](const DSString& token) { return token.length() <= 2; }),
                                        allPositiveTokens.end()); 
                std::cout << "Token count after cleaning: " << allPositiveTokens.size() << std::endl;
                // Inserts all tokenized words from sentences into a global vector that saves them all
                wordsPos.insert(wordsPos.end(), allPositiveTokens.begin(), allPositiveTokens.end());
            }

            if (x.second == "0") { 
                DSString DSnegTweet = it->second; 
                DSString cleanedTweetNeg = DSnegTweet.cleanString(DSnegTweet); 
                std::vector<DSString> allNegativeTokens = cleanedTweetNeg.tokenize();

                allNegativeTokens.erase(std::remove_if(allNegativeTokens.begin(), allNegativeTokens.end(),
                                                       [](const DSString& token) { return token.length() <= 2; }),
                                        allNegativeTokens.end()); 

                wordsNeg.insert(wordsNeg.end(), allNegativeTokens.begin(), allNegativeTokens.end());
            }

        }
    }

//train!
for (const DSString& word : wordsPos) { // Iterates through positive words vector
    auto it = Words.find(word); // Looks for the word in the 'Words' map
    if (it == Words.end()) {
        Words[word] = 1; // If the word is not found, add it with a sentiment value of 1
    } else {
        it->second++; // If the word is found, increment its sentiment value
    }
}

for (const DSString& word : wordsNeg) { 
    auto it = Words.find(word); 
    if (it == Words.end()) {
        Words[word] = -1; 
    } else {
        it->second--; // If the word is found, decrement its sentiment value
    }
}


//testing readfile functionality
std::cout << "pos words: ";
for (const auto& word : wordsPos) {
    std::cout << word << " ";
}

std::cout << "neg words: ";
for (const auto& word : wordsNeg) {
    std::cout << word << " ";
}
std::cout << std::endl;

std::cout << "Processed " << idToTweet.size() << " tweets." << std::endl;
std::cout << "Positive words count: " << wordsPos.size() << ", Negative words count: " << wordsNeg.size() << std::endl;
    
    // Check for a specific ID (assuming IDs are unique)
    DSString specificId = "2243873058";  // Example ID you expect to find
    auto it = idToTweet.find(specificId);
    if (it != idToTweet.end()) {
        std::cout << "Tweet with ID " << specificId << ": " << it->second << std::endl;
    } else {
        std::cout << "Tweet with ID " << specificId << " not found." << std::endl;
    }
}

//end readfile
*/




