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

    len = strlen(str);
    data = new char[len + 1]; 
    data[len] = '\0';

    for (size_t i = 0; i < len; i++){
        data[i] = str[i];
    }
}; 

DSString::DSString(const DSString &str){ // copy constructor
    len = str.len;
    data = new char[len + 1];
    data[len] = '\0';

    for(size_t i = 0; i < len; i++){
        data[i] = str[i];
    }
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
            data[i] = str[i];
        }
    }
    return *this;
 }

size_t DSString::length() const{ //returns the length of the string
    return len; 
}

char &DSString::operator[](size_t index) const{
    return data[index];
}

DSString DSString::operator+(const DSString &line) const{ //adds the string from the line of data to the new string 
   int length = 1 + len + line.len;
    char *strContents = new char[length];
    strContents[length] = '\0';

    for ((size_t) i = 0; i < len; i++){
    strContents[i] = data[i];
    }
    
    for (size_t i = 0; i < line.len; i++) {
            strContents[i+len] = line.data[i];
        }

    DSString temporaryHolder = strContents;
    delete[] strContents;
    return temporaryHolder;

}

bool DSString::operator==(const DSString &lengthOfEqualsSign) const{

    if(len != lengthOfEqualsSign.len){
        return 0;
    }

    for(size_t i = 0; i < len; i++){
        if(data[i] != lengthOfEqualsSign[i]){
            return 0;
        }
    }
    return 1; 
}

bool DSString::operator<(const DSString &lengthOfLessThanSign) const{

    for(size_t i = 0; i < len; i++){

        if(i == lengthOfLessThanSign.length() - 1){ return 0; }
        if(data[i] < lengthOfLessThanSign[i]){ return 0; }
        else if(data[i] > lengthOfLessThanSign[i]) { return 1; }
        
    }//end for loop
    return 1;
}//end func

//returns a new string object that contains a sequence of characters from this string object.
DSString DSString::substring(const size_t start, const size_t numChars) const{

    char temporaryCString[numChars + 1];

    for(size_t i=0; i < numChars; i++){
        temporaryCString[i] = data[start  + i];
    }
    temporaryCString[numChars] = '\0'; 

    return temporaryCString;

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
}; 

char *DSString::c_str() const { return data;}

std::ostream &operator<<(std::ostream &output, const DSString &str){
    output << str.data;
    return output;
}










