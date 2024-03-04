#include "DSString.h"



/* 
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project. 
 * 
 * Note that c-strings don's store an explicit length but use `\0` as the terminator symbol
 * but your class should store its length in a member variable. 
 * DDO NOT USE C-STRING FUNCTIONS <string.h> or <cstring>.
 */  


DSString::DSString(){ // default constructor

data = new char[1];
len = 0; 
data[0] = '\0';

}

DSString::DSString(const char *str){ //constructor that converts a cstring

//manual calculation of c-string length
    len = 0;
    while (str[len] != '\0'){
        len++;
    }
    data = new char[len + 1]; //allocate memory for c-string and the null terminator
    for (size_t i = 0; i < len; i++){
        data[i] = str[i]; //copy characters
    }
    data[len] = '\0';//ensure data is null-terminated
}

DSString::DSString(const DSString &str){ // copy constructor
    len = str.len;
    data = new char[len + 1];
    for(size_t i = 0; i < len; i++){
        data[i] = str.data[i];
    }
    data[len] = '\0';
}//end func

DSString::~DSString(){ //destructor
    delete[] data;
}

DSString &DSString::operator=(const DSString &str){ //assignment operator
    if(this != &str) {
        delete[] data;

        len = str.len;
        data = new char[len + 1];
        data[len] = '\0';

        for (size_t i = 0; i < len; i++){
            data[i] = str.data[i];
        }
    }
    return *this;
 }
//consider changing this to the swap method


size_t DSString::length() const{ //returns the length of the string
    return len; 
}

char &DSString::operator[](size_t index){
    return data[index];
}

DSString DSString::operator+(const DSString &line) const{ //adds the string from the line of data to the new string 
   int newLength = len + line.len; //calculate the new length
    char *newContents = new char[newLength + 1]; //allocate memory for new c-string

    for (size_t i = 0; i < len; i++){
    newContents[i] = data[i]; //copy this string's data
    }
    
    for (size_t i = 0; i < line.len; i++) {
            newContents[len + i] = line.data[i]; //concatenate the other string's data
        }

    newContents[newLength] = '\0'; //null terminate the new string

    DSString result(newContents); //use the constructor to create a new DSString
    delete[] newContents; //clean up the temporary c-string
    return result;

}

bool DSString::operator==(const DSString &lengthOfEqualsSign) const{

    if(len != lengthOfEqualsSign.len){
        return false;
    }

    for(size_t i = 0; i < len; i++){
        if(data[i] != lengthOfEqualsSign.data[i]){
            return false;
        }
    }
    return true; 
}

bool DSString::operator<(const DSString &lengthOfLessThanSign) const{

    
        //iterate up to the shorter of the two string lengths
        size_t minLength = std::min(len, lengthOfLessThanSign.len);

    for(size_t i = 0; i < minLength; i++){
        if(data[i] < lengthOfLessThanSign.data[i]){ return true; }
        else if(data[i] > lengthOfLessThanSign.data[i]) { return false; }
    }//end for loop
    // If all characters so far were equal between the substrings being compared, the shorter string is "less than" the longer one
    return len < lengthOfLessThanSign.len;
}//end func

//returns a new string object that contains a sequence of characters from this string object.
DSString DSString::substring(const size_t start, const size_t numChars) const{

    //char temporaryCString[numChars + 1];
    char* temporaryCString = new char[numChars + 1];

    for(size_t i=0; i < numChars; i++){
        temporaryCString[i] = data[start  + i];
    }
    temporaryCString[numChars] = '\0'; 

    DSString result(temporaryCString);
    return result;
    delete[] temporaryCString;
    temporaryCString = nullptr; //avoid dangling pointer

}//end 


//Returns a new string object with all characters in lowercase
DSString DSString::toLower() const{

    DSString temporaryHolder(data);
    
    for(size_t i = 0; i < len; i++){
        
        if(data[i] >= 'A' && data[i] <= 'Z'){ //check if the character is uppercase 
            temporaryHolder[i] = data[i] + 32; //convert to lowercase by adding 32 to its ASCII value
        } else {
            temporaryHolder[i] = data[i]; //if its not uppercase, just copy the character
        }
    }
    return temporaryHolder;
}

char *DSString::c_str() const { return data;}

// Construct std::string from DSString's data and length
std::string DSString::toStdString() const {
    return std::string(this->data, this->len);  
}

std::ostream &operator<<(std::ostream &output, const DSString &str){
    output << str.data;
    return output;
}

char DSString::back() const {
    return data[len - 1];
}


size_t DSString::find(char ch, size_t pos) const{
    
    if (len == 0) return npos; //checks if string is empty

    // if pos>= len, then i = len - 1 aka the last valid index of the string. 
    // ^ this ensures you don't start the search beyond the string's bounds
    // if pos>=len is false, then i = pos. Pos is thus a valid index to start the search from
    for (size_t i = (pos >= len ? len - 1 : pos); i != npos; --i){
        
        if(data[i] == ch) return i; // If the current character matches `ch`, return the current position `i`
        if (i == 0) break;
    }
    // If the character `ch` is not found, return `npos`
    return npos;
}

//lowercase all words and remove punctuation
DSString DSString::cleanString(const DSString& original) {
    DSString result; // New DSString object to hold the cleaned string
    DSString lowercased = original.toLower(); // Convert the original string to lowercase

    for (size_t i = 0; i < lowercased.length(); i++) {
        char currentChar = lowercased[i];
        if (!ispunct(currentChar) && !isdigit(currentChar) && currentChar != '\'') {
            char tempStr[2] = {currentChar, '\0'}; // Create a temporary C-string
            result = result + DSString(tempStr); // Use the DSString constructor that accepts a const char*
        }
    }

    return result;
}




// Tokenizes the DSString into a vector of DSStrings based on commas
std::vector<DSString> DSString::tokenize(char delimiter){

    //size_t lengthOfToken = len;
    std::vector<DSString> tokens;
    size_t startingPoint = 0;

    //iterate over each character in the DSString
    for(size_t i = 0; i <= len; ++i){
        //check if current character is a comma or end of token
        if(data[i] == delimiter|| i == len){

            //ensure token length is positive
            if(i > startingPoint){
                
                DSString word = this->substring(startingPoint, i - startingPoint); //extract token using substring starting from startingPoint
                
                tokens.push_back(word); //add the extracted token to the tokens vector 
            }
                startingPoint = i+1; // Update the start index to the next character after the whitespace/comma
        }
        
    }
    return tokens;

} 













