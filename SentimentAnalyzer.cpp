#include "SentimentAnalyzer.h"
#include "DSString.h"


DSString SentimentAnalyzer::getLastElement(const DSString& data) { // some tweets have commas, so this helps read it in 
    if (data.back() == '\"') {
        // Find the opening quotation mark for the last element
        size_t startQuote = data.find('\"', data.length() - 2);
        return data.substring(startQuote + 1, data.length() - startQuote - 2);
    } else {
        // Find the last comma and return everything after it
        size_t lastComma = data.find(',');
        return data.substring(lastComma + 1, data.length() - lastComma -1);
    }
}

void SentimentAnalyzer::readfile(const char* filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) { // Print if failed to open
        std::cerr << "Failed to open the file: " << filePath << std::endl;
        return;
    }

    DSString dsstringobject; 
    std::string tempLine; // Temporary std::string to hold input from getline

    // Maps with ID and Tweet, read in line by line
    std::map<DSString, DSString> idToSentiment; // Map of ID and Sentiments
    std::map<DSString, DSString> idToTweet; // Map of ID and Tweets

    while (std::getline(inputFile, tempLine)) { // Loop reads in file
        DSString data = DSString(tempLine.c_str()); // Convert std::string to DSString for processing

        std::istringstream lineStream(tempLine);
        std::string tempSentiment, tempId;

        // Using std::getline with std::string for parsing since istringstream works with std::string
        std::getline(lineStream, tempSentiment, ',');
        std::getline(lineStream, tempId, ',');

        DSString sentiment = DSString(tempSentiment.c_str());
        DSString id = DSString(tempId.c_str());

        DSString tweet = getLastElement(data); // getLastElement expects and returns DSString

        idToSentiment.insert(std::make_pair(id, sentiment));
        idToTweet.insert(std::make_pair(id, tweet));
    }
    inputFile.close();

    // Processing each tweet
    for (const auto& x : idToSentiment) {
        auto it = idToTweet.find(x.first); // Find id in idToTweet map
        if (it != idToTweet.end()){ // Check if ID exists in map
            if (x.second == "4") { 
                DSString DSposTweet = it->second; 
                DSString cleanedTweetPos = DSposTweet.cleanString(DSposTweet); // Cleans DSString
                std::vector<DSString> allPositiveTokens = cleanedTweetPos.tokenize(); // Tokenizes the DSString

                // Remove tokens with less than 3 characters
                //std::remove_if moves all short tokens to the end of the vector, then erase method erases them from the vector as a whole; consulted internet for how to use this.

                allPositiveTokens.erase(std::remove_if(allPositiveTokens.begin(), allPositiveTokens.end(),
                                                       [](const DSString& token) { return token.length() <= 2; }),
                                        allPositiveTokens.end()); 

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





}//end readfile


