#ifndef HANGMAN_H_INCLUDED
#define HANGMAN_H_INCLUDED



#include <ncurses.h>
#include <string>

class TheHangman{
	public:
		TheHangman() {_missesRemaining = 6;}

                bool addMiss(){return --_missesRemaining; }
                int missesRemaining() {return _missesRemaining;}

		void draw(WINDOW *win){
                    wmove(win,2,0);
                    wprintw(win,"    /----\\\n    |    %c\n    |   %c%c%c\n    |   %c %c\n  __|__",
				_missesRemaining<6?'0' :' ',
				_missesRemaining<5?'/' :' ',
				_missesRemaining<4?'|' :' ',
				_missesRemaining<3?'\\':' ',
				_missesRemaining<2?'/' :' ',
				_missesRemaining<1?'\\':' ');
		}

	private:
		int _missesRemaining;
};


class SecretWord {
	public:
		SecretWord(std::string word){
			word.copy(_secretWord,10);
			for (int i=0; i<word.length(); ++i)
				_status[i] = '_';
			_lettersRemaining = word.length();
			_wordLength = word.length();
		}

		int guess(char letter){
			int lettersFound = 0;
			for (int i=0; i<_wordLength; ++i){
				if (letter==_secretWord[i] && _status[i]=='_'){
					_status[i] = letter;
					--_lettersRemaining;
					++lettersFound;
				}
			}

			return lettersFound;
		}

		int lettersRemaining(){return _lettersRemaining;}

		void draw(WINDOW *win){
			wmove(win,9,0);
			for (int i=0; i<_wordLength; i++)
				wprintw(win,"%c ",_status[i]);
		}

	private:
		char _secretWord[10];
		char _status[10];
		int _lettersRemaining;
		int _wordLength;
};


class Player {
	public:
        Player(){}
		Player(int playerNumber, std::string word){
			_word = new SecretWord(word);
			_counter = new TheHangman();
			_playerNumber = playerNumber;
			_win = newwin(30, 20, 0, (playerNumber-1)*25);
		}

		int guess(){
            draw('*');
            char letter = wgetch(_win);
			if (_word->guess(letter) == 0)
				_counter->addMiss();

			draw(' ');

			return _word->lettersRemaining();
		}

		bool hasWon() {return _word->lettersRemaining()==0;}
		bool hasLost() {return _counter->missesRemaining()==0;}

	private:
        void draw(char active){
            wmove(_win,0,2);
            wprintw(_win, "Player %d %c", _playerNumber,active);
			_word->draw(_win);
			_counter->draw(_win);
			wrefresh(_win);
        }

		WINDOW *_win;
		int _playerNumber;
		SecretWord *_word;
		TheHangman *_counter;
};



#endif // HANGMAN_H_INCLUDED
