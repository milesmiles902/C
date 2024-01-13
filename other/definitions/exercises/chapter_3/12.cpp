//program that detects palindromes.

/*
The Advanced Palindrome Checker
By: David Reynoso and David Andrejsin
*/

using namespace std;
#include <deque>
#include <fstream> // for file handling
#include <iostream>
#include <string>
#include "stdlib.h" // for the system command
#include <algorithm> // provides an algorithm for easier removal of characters from a string

string processor(string aString) {
    // goes through string and finds uppercase letters and converts
    // them to lower case, also finds special characters and gets rid of them
    // ultimately, prepares a string for a correct palindrome evaluation
    int strLen = aString.length();
    string str = "";
    for (int i = 0; i < strLen; i++) {
        str += tolower(aString[i]);
    }
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str.erase(remove(str.begin(), str.end(), '.'), str.end());
    str.erase(remove(str.begin(), str.end(), '?'), str.end());
    str.erase(remove(str.begin(), str.end(), '!'), str.end());
    str.erase(remove(str.begin(), str.end(), ','), str.end());
    str.erase(remove(str.begin(), str.end(), ';'), str.end());
    str.erase(remove(str.begin(), str.end(), ':'), str.end());
    str.erase(remove(str.begin(), str.end(), '#'), str.end());
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    str.erase(remove(str.begin(), str.end(), '\''), str.end());
    // we had to use a backslash to espace the function of '
    str.erase(remove(str.begin(), str.end(), '-'), str.end());
    str.erase(remove(str.begin(), str.end(), '('), str.end());
    str.erase(remove(str.begin(), str.end(), ')'), str.end());

    return str;
}

bool palchecker(string aString) {
    // an algorithm that checks whether a string is a palindrome
    aString = processor(aString); // calls a function that prepares the string for a proper evaluation of the palindrome

    deque<char> chardeque;
    int strLen = aString.length();
    for (int i = 0; i < strLen; i++) {
    //pushes each char in the string to the deque.
        chardeque.push_back(aString[i]);
    }

    bool stillEqual = true;

    while (chardeque.size() > 1 && stillEqual) {
        char first = chardeque.front();
        chardeque.pop_front();
        char last = chardeque.back();
        chardeque.pop_back();
        if (first != last) { //if the two opposite positions of the
             //word is not the same, then it is not
             //a palindrome.
            stillEqual = false;
        }
    }
    return stillEqual;
}

int main() {
    cout << palchecker("Radar") << endl;
    cout << palchecker("Are we not pure? 'No sir!' Panama's moody Noriega brags. 'It is garbage!' Irony dooms a man; a prisoner up to new era.") << endl;
    cout << palchecker("Barge in! Relate mere war of 1991 for a were-metal Ernie grab!") << endl;
    cout << palchecker("not a palindrome") << endl;
}
