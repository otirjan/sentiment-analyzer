#include "SentimentAnalyzer.h"
#include "DSString.h"

DSString getLastElement(const DSString& data) { // some tweets have commas, so this helps read it in 
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
