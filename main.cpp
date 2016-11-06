#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <Hangman.h>
#include <string>

using namespace std;

void getPlayerList(Player *pList, int &numPlayers);

int main()
{
    initscr();
    curs_set(0);

    int players = 1;
    Player pList[3];
    getPlayerList(pList,players);

    noecho();

    while(true){
        for (int k=0; k<players; k++)
            pList[k].guess();
    }

    if (true)
        mvprintw(12,0,"You Have Won!");
    else
        mvprintw(12,0,"You Have Lost!");
    refresh();

    sleep(5);

    endwin();
    return 0;
}



void getPlayerList(Player *pList, int &numPlayers){
    WINDOW *win = newwin(30, 300, 0, 0);
    wprintw(win,"How Many Players? ");
    wrefresh(win);
    numPlayers = wgetch(win)-48;

    for (int k=0; k<numPlayers; k++)
    {
        char ch, pos(0);
        string word;
        werase(win);
        wprintw(win,"Player %d, please enter a challenge word: ",k+1);
        wrefresh(win);
        ch = wgetch(win);
        while(ch != '\n'){
            word.push_back(ch);
            ch = wgetch(win);
        }
        pList[k] = Player(k+1,word);
        werase(win);
    }
    wrefresh(win);
    delwin(win);
}
