#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool wordChecker(std::string str, std::string requirements, int place);
std::set<std::string> wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    int letterPlace);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string>::iterator words;
    std::set<std::string> cDict;

    for(words = dict.begin(); words != dict.end(); ++words) {

        bool valid = true;
        for(int i = 0; i < (*words).length(); ++i){
            if(isalpha((*words)[i]) == 0 || islower((*words)[i]) == 0) valid = false;
        }

        if (valid && ((*words).length() == in.length()) && wordChecker(*words, floating, 0)) cDict.insert(*words);
    }

    cDict = wordleHelper(in, floating, cDict, 0);

    return cDict;
}

// Define any helper functions here
std::set<std::string> wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    int letterPlace)
{

    if(letterPlace >= in.length()) return dict;
    if (in[letterPlace] == '-') return wordleHelper(in, floating, dict, letterPlace + 1);

    std::set<std::string>::iterator words;
    std::set<std::string> cDict;

    for(words = dict.begin(); words != dict.end(); ++words) {
        if(in[letterPlace] != '-' && (*words)[letterPlace] == in[letterPlace]) cDict.insert(*words);
    }

    return wordleHelper(in, floating, cDict, letterPlace + 1);
}



bool wordChecker(std::string str, std::string requirements, int place){

    if(place >= requirements.length()) return true;

    bool found = false;
    std::string newStr = str;
    
    for(int i = 0; i < str.length(); ++i){

        if(requirements[place] == str[i]) {
            found = true; 
            newStr.erase(i, 1);
            break;
        }
        
    }

    return found && wordChecker(newStr, requirements, place + 1);
}
