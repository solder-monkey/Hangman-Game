#include "SecretWord.h"
#include <string>
#include <vector>

SecretWord::SecretWord(string word)
{
    _lettersRemaining = word.length();
    _guesses = new vector<char>();
}

SecretWord::public bool guessLetter(char letter)
{
    if (_guesses.containts(letter))
        return false;

    _guesses.add(letter);

}

SecretWord::~SecretWord()
{
    //dtor
}
