#include "DSString.h"
#include <cstring>


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















