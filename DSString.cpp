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

std::ostream &operator<<(std::ostream &output, const DSString &str){
    output << str.data;
    return output;
}



// Tokenizes the DSString into a vector of DSStrings based on whitespace characters 
std::vector<DSString> DSString::tokenize() {

    //store the length of the DSString to tokenize
    size_t lengthOfToken = len;

    //initialize a vector to hold the tokens
    std::vector<DSString> tokens;

    //initialize starting point of a potential token
    size_t startingPoint = 0;

    //iterate over each character in the DSString
    for(size_t i = 0; i < lengthOfToken; i++){
        //check if current character is a whitespace 
        if(isspace(data[i])){

            //if there is a non-empty token here, extract it
            if(i > startingPoint){
                //extract token using substring starting from startingPoint
                DSString word = this->substring(startingPoint, i - startingPoint);
             // Update the starting point for the next token to be right after the current whitespace.
                startingPoint = i+1;
            //add the extracted token to the tokens vector 
                tokens.push_back(word);
            }
        }
        
    }

    // After the loop, check if there's a token at the end of the string not followed by whitespace
    if(startingPoint < lengthOfToken){
        //extract the final token
        DSString word = this->substring(startingPoint, len - startingPoint);
        tokens.push_back(word);
    }

    return tokens;

}














