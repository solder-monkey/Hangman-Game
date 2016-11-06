#ifndef SECRETWORD_H
#define SECRETWORD_H

#include <string>
#include <vector>

class SecretWord
{
    public:
        SecretWord(String word): _word = word;

        public bool guessLetter(char letter);

        virtual ~SecretWord();
    protected:
    private:
        String _word;
        int _lettersRemaining;
        vector<char> _guesses;
};

#endif // SECRETWORD_H
