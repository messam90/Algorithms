/*
 * Internal.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int romanNumMap(char r){
    if (r == 'I')
        return 1;
    if (r == 'V')
        return 5;
    if (r == 'X')
        return 10;
    if (r == 'L')
        return 50;
    if (r == 'C')
        return 100;
    if (r == 'D')
        return 500;
    if (r == 'M')
        return 1000;

    return -1;
}

void justifyText(string& line, unsigned int wordsInLine, unsigned int maxLineLen){
	bool firstSpace = true;
	unsigned int orginalLineLength = line.length(), numSpaceFields = wordsInLine - 1;
	float spacesPerField = (float)(numSpaceFields != 0) ? ((float)(maxLineLen - orginalLineLength)/numSpaceFields) : (maxLineLen - orginalLineLength); //if a fracture is the result, left most space field gets extra space

	for(unsigned int index = 0; index < line.length() && numSpaceFields != 0; index++){
		if(line[index] == ' '){
			//start inserting spaces
			if(firstSpace){
				line.insert(line.begin() + index, ceil(spacesPerField), ' '); //a space is already there
				index += ceil(spacesPerField);
				firstSpace = false;
			}else{
				line.insert(line.begin() + index, floor(spacesPerField), ' '); //a space is already there
				index += floor(spacesPerField);
			}
		}
	}

	line.resize(maxLineLen);
}

