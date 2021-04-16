//standard library
#include <iostream>
using namespace std;

#include <string>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//setup function system of c++ to use 
#include "system.h"

//required function here !
#include "logic.h"

//draw anything in this game 
#include "graphic.h"

bool menu=1;

void* keyframe(void* arg)
{
    int left=40;
    int top=3;
    int length=0;
    int width=0;
    int colorBg=0*16+5;
    int time=500;
    pthread_detach(pthread_self());
    while (true) {
        if (menu==1){
            //frame_1
            Sleep(time);
            SetColor(7);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) + 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) + 1);
            cout<<" ";

            SetPosition(left + ceil(width / 2) + 9, top + ceil(length / 2) - 1);
            SetColor(8 + colorBg / 16 * 16);
            cout << char(5);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) );
            SetColor(4 + colorBg / 16 * 16);
            cout << char(4);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) );
            SetColor(4 + colorBg / 16 * 16);
            cout << char(3);
            SetPosition(left + ceil(width / 2) + 10, top + ceil(length / 2) + 1);
            SetColor(8 + colorBg / 16 * 16);
            cout << char(6);
        }
        if (menu==1){
            //frame_2
            Sleep(time);
            SetColor(7);
            SetPosition(left + ceil(width / 2) + 9, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) );
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) );
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 10, top + ceil(length / 2) + 1);
            cout<<" ";

            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) - 1);
            SetColor(8 + colorBg / 16 * 16);
            cout << char(5);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) - 1);      
            SetColor(4 + colorBg / 16 * 16);
            cout << char(4);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) + 1);         
            SetColor(4 + colorBg / 16 * 16);
            cout << char(3);  
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) + 1);         
            SetColor(8 + colorBg / 16 * 16);
            cout << char(6); 
        }
        if (menu==1){
            //frame_3
            Sleep(time);
            SetColor(7);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) + 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) + 1);
            cout<<" ";

            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) );
            SetColor(8 + colorBg / 16 * 16);
            cout << char(5);
            SetPosition(left + ceil(width / 2) + 10, top + ceil(length / 2) - 1);
            SetColor(4 + colorBg / 16 * 16);
            cout << char(4);
            SetPosition(left + ceil(width / 2) + 9, top + ceil(length / 2) + 1);
            SetColor(4 + colorBg / 16 * 16);
            cout << char(3);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) );
            SetColor(8 + colorBg / 16 * 16);
            cout << char(6);
        }
        if (menu==1){
            //frame_4
            Sleep(time);
            SetColor(7);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) );
            cout << " ";
            SetPosition(left + ceil(width / 2) + 10, top + ceil(length / 2) - 1);
            cout << " ";
            SetPosition(left + ceil(width / 2) + 9, top + ceil(length / 2) + 1);
            cout << " ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) );
            cout << " ";

            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) - 1);
            SetColor(4 + colorBg / 16 * 16);
            cout << char(4);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) - 1);      
            SetColor(8 + colorBg / 16 * 16);
            cout << char(6);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) + 1);         
            SetColor(8 + colorBg / 16 * 16);
            cout << char(5); 
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) + 1);         
            SetColor(4 + colorBg / 16 * 16);
            cout << char(3);
        }
        if (menu==1){
            //frame_5
            Sleep(time);
            SetColor(7);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) + 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) + 1);
            cout<<" ";

            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) );
            SetColor(4 + colorBg / 16 * 16);
            cout << char(4);
            SetPosition(left + ceil(width / 2) + 10, top + ceil(length / 2) - 1);      
            SetColor(8 + colorBg / 16 * 16);
            cout << char(6);
            SetPosition(left + ceil(width / 2) + 9, top + ceil(length / 2) + 1);         
            SetColor(8 + colorBg / 16 * 16);
            cout << char(5); 
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) );         
            SetColor(4 + colorBg / 16 * 16);
            cout << char(3);
        }
        if (menu==1){
            //frame_6
            Sleep(time);
            SetColor(7);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) );
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 10, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 9, top + ceil(length / 2) + 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) );
            cout<<" ";

            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) - 1);
            SetColor(8 + colorBg / 16 * 16);
            cout << char(6);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) - 1);      
            SetColor(4 + colorBg / 16 * 16);
            cout << char(3);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) + 1);         
            SetColor(4 + colorBg / 16 * 16);
            cout << char(4);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) + 1);         
            SetColor(8 + colorBg / 16 * 16);
            cout << char(5);
        }
        if (menu==1){
            //frame_7
            Sleep(time);
            SetColor(7);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) + 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) + 1);
            cout<<" ";

            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) );
            SetColor(8 + colorBg / 16 * 16);
            cout << char(6);
            SetPosition(left + ceil(width / 2) + 10, top + ceil(length / 2) - 1);      
            SetColor(4 + colorBg / 16 * 16);
            cout << char(3);
            SetPosition(left + ceil(width / 2) + 9, top + ceil(length / 2) + 1);         
            SetColor(4 + colorBg / 16 * 16);
            cout << char(4);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) );         
            SetColor(8 + colorBg / 16 * 16);
            cout << char(5);
        }
        if (menu==1){
            //frame_8
            Sleep(time);
            SetColor(7);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) );
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 10, top + ceil(length / 2) - 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 9, top + ceil(length / 2) + 1);
            cout<<" ";
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) );
            cout<<" ";

            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) - 1);
            SetColor(4 + colorBg / 16 * 16);
            cout << char(3);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) - 1);      
            SetColor(8 + colorBg / 16 * 16);
            cout << char(5);
            SetPosition(left + ceil(width / 2) + 8, top + ceil(length / 2) + 1);         
            SetColor(8 + colorBg / 16 * 16);
            cout << char(6);
            SetPosition(left + ceil(width / 2) + 11, top + ceil(length / 2) + 1);         
            SetColor(4 + colorBg / 16 * 16);
            cout << char(4);
        }                             
    }    
}

void* start(void* arg){

    //setup console
    //FullScreen();
    LPCSTR a = "Poker";
    SetConsoleTitle(a);
    int*** players;
    int* points=new int[1];
    int* restDeck;
    int Deck[4][13];
    int numbOfPlayer;
    int selected;

    bool option=0;   
    int mode=0;

    int posOption=19;
    int i=0;

    while (true) { 
        int key;
        if (menu==1){
            system("cls");
            selected = DrawMenuSelect(menu);
            numbOfPlayer=(selected%10 >=2) ? selected/10+1 : selected/10;
            mode=selected%10;
            points = new int[numbOfPlayer];
            for (int i = 0; i < numbOfPlayer; i++) points[i] = 0;
        }
        key = _getch(); 
        if (key==27){
            option=1;
            i=0;
        }       
        if (option == 1){
            SetPosition(95, posOption);
            cout << "Continue";
            SetPosition(95, posOption+1);
            cout << "Menu";
            SetPosition(95, posOption+2);
            cout << "Quit";

            //down
            if (key == 80) {
                SetPosition(93, posOption+i);
                cout <<"  ";
                i++;
            }
            //up
            else if (key == 72) {
                SetPosition(93, posOption+i);
                cout <<"  ";
                i--;
            }
            else if (key==13){
                if (i==0){
                    option=0;
                    clearOption(posOption);
                }
                else if (i==1){
                    clearOption(posOption);
                    SetPosition(0,0);
                    if (mode == 0)
                        DrawPoint(points, numbOfPlayer);
                    else if (mode >= 2)
                        DrawPointForDealerMode(points, numbOfPlayer);
                    WinnerTop(evaluateHands(points,numbOfPlayer),mode);
                    delete[]points;
                    menu=1;
                    i=0;
                    key=_getch();
                    continue;
                }             
                else if (i==2){
                    clearOption(posOption);
                    if (mode == 0)
                        DrawPoint(points, numbOfPlayer);
                    else if (mode >= 2)
                        DrawPointForDealerMode(points, numbOfPlayer);
                    WinnerTop(evaluateHands(points, numbOfPlayer),mode);
                    delete[]points;
                    system("cls");
                    DrawEndGame();
                    _getch();           
                    break;
                }        
            }

            if (i==3) 
                i=0;
            else if (i==-1)
                i=2;

            SetColor(13);
            SetPosition(93, posOption + i);
            cout << "->";
            SetColor(7);
        }             
        if (key == 13 && menu == 0 && mode == 0) {
            system("cls");  
            suffleCards(Deck);
            int restCard = 52 - 5 * numbOfPlayer;
            restDeck = new int[restCard];
            players = dealingForHands(Deck, numbOfPlayer, restDeck);
            DrawTable();
            DrawPlayer(numbOfPlayer);
            DrawOption();
            DrawPokerText(-9, 4, 9 * 16 + 0, 13, 75);      //left top color length width
            key = _getch();

            DrawTable();
            DrawGUI();
            //DrawPokerText();
            key= _getch();
            if (key==13){  
                DrawTable();
                DrawHands(players, numbOfPlayer);
                int* winner = rankingHands(players, numbOfPlayer);
                pointsAllRounds(winner, numbOfPlayer,points);
                Winner(winner);
                DrawPoint(points, numbOfPlayer);               
                cleanup(players,winner,numbOfPlayer); 
            }
            if (key==27){
                option=1;
                i=0;
            }
            if (option==1){
                
                SetPosition(95, posOption);
                cout << "Continue";
                SetPosition(95, posOption+1);
                cout << "Menu";
                SetPosition(95, posOption+2);
                cout << "Quit";

                //down
                if (key == 80) {
                    SetPosition(93, posOption+i);
                    cout <<"  ";
                    i++;
                }
                //up
                else if (key == 72) {
                    SetPosition(93, posOption+i);
                    cout <<"  ";
                    i--;
                }
                else if (key==13){
                    if (i==0){
                        option=0;
                        clearOption(posOption);
                        DrawHands(players, numbOfPlayer);                            
                        int* winner = rankingHands(players, numbOfPlayer);
                        pointsAllRounds(winner, numbOfPlayer,points);
                        Winner(winner,mode);
                        DrawPoint(winner, numbOfPlayer);               
                        cleanup(players,winner,numbOfPlayer); 
                    }
                    else if (i==1){
                        clearOption(posOption);
                        SetPosition(0,0);
                        DrawPoint(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer),mode);
                        menu=1;
                        i=0;
                        key=_getch();
                        continue;
                    }
                    else if (i==2){
                        clearOption(posOption);
                        DrawPoint(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer),mode);
                        delete[]points; 
                        system("cls");
                        DrawEndGame();  
                        _getch();               
                        break;
                    }        
                }

                if (i==3)
                    i=0;
                else if (i==-1)
                    i=1;

                SetColor(13);
                SetPosition(93, posOption + i);
                cout << "->";
                SetColor(7);
            }         
        } 
        
        if (key == 13 && menu == 0 && mode == 2) {
            system("cls");  
            suffleCards(Deck);
            int restCard = 52 - 5 * numbOfPlayer;
            restDeck = new int[restCard];
            players = dealingForHands(Deck, numbOfPlayer,restDeck);
            DrawTable();
            DrawPokerText(-9, 4, 9 * 16 + 0, 13, 75);     //left top color length width
            key = _getch();

            DrawTable();
            DrawDealerAndPlayer(numbOfPlayer);
            DrawPointForDealerMode(points, numbOfPlayer);
            DrawGUI();

            key = _getch();
            if (key == 13) {
                DrawOption();
                DrawTable();
                HandleDealerMedium(players[0], players, numbOfPlayer, restDeck);
                DrawTable();
                DrawPreResult();

                key=_getch();
                DrawTable();
                DrawHandsForDealerMode(players, numbOfPlayer);
                int* winner = rankingHands(players, numbOfPlayer);
                pointsAllRounds(winner, numbOfPlayer, points);
                Winner(winner, mode);
                DrawPointForDealerMode(points, numbOfPlayer);
                cleanup(players, winner, numbOfPlayer);
            }
            if (key == 27) {
                option = 1;
                i = 0;
            }
            if (option == 1) {
                SetPosition(95, posOption);
                cout << "Continue";
                SetPosition(95, posOption + 1);
                cout << "Menu";
                SetPosition(95, posOption + 2);
                cout << "Quit";

                //down
                if (key == 80) {
                    SetPosition(93, posOption + i);
                    cout << "  ";
                    i++;
                }
                //up
                else if (key == 72) {
                    SetPosition(93, posOption + i);
                    cout << "  ";
                    i--;
                }
                else if (key == 13) {
                    if (i == 0) {
                        option = 0;
                        clearOption(posOption);
                        DrawHandsForDealerMode(players, numbOfPlayer);
                        int* winner = rankingHands(players, numbOfPlayer);
                        pointsAllRounds(winner, numbOfPlayer, points);
                        Winner(winner, mode);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        cleanup(players, winner, numbOfPlayer);
                    }
                    else if (i == 1) {
                        clearOption(posOption);
                        SetPosition(0, 0);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer), mode);
                        delete[]points;
                        menu = 1;
                        i = 0;
                        key = _getch();
                        continue;
                    }
                    else if (i == 2) {
                        clearOption(posOption);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer), mode);
                        delete[]points;
                        system("cls");
                        DrawEndGame();
                        _getch();
                        break;
                    }
                }

                if (i == 3)
                    i = 0;
                else if (i == -1)
                    i = 2;

                SetColor(13);
                SetPosition(93, posOption + i);
                cout << "->";
                SetColor(7);
            }

        }

        if (key == 13 && menu == 0 && mode == 4) {
            system("cls");  
            suffleCards(Deck);
            int restCard = 52 - 5 * numbOfPlayer;
            restDeck = new int[restCard];
            players = dealingForHands(Deck, numbOfPlayer,restDeck);
            DrawTable();
            DrawPointForDealerMode(points, numbOfPlayer);
            DrawDealerAndPlayer(numbOfPlayer);
            DrawOption();
            DrawPokerText(-9, 4, 9 * 16 + 0, 13, 75);      //left top color length width
            key = _getch();

            DrawTable();
            DrawGUI();
            key= _getch();
            if (key==13){
                DrawOption();
                DrawTable();
                HandlePlayer(players,numbOfPlayer,restDeck);
                DrawTable();
                HandleDealerEasy(players[0], restDeck);
                DrawTable();    
                DrawPreResult();

                key= _getch();               
                DrawTable();
                DrawHandsForDealerMode(players,numbOfPlayer);
                int* winner = rankingHands(players, numbOfPlayer);
                pointsAllRounds(winner, numbOfPlayer,points);
                Winner(winner,mode);
                DrawPointForDealerMode(points, numbOfPlayer);               
                cleanup(players,winner,numbOfPlayer); 
            }
            if (key==27){
                option=1;
                i=0;
            }  
            if (option==1){
                SetPosition(95, posOption);
                cout << "Continue";
                SetPosition(95, posOption+1);
                cout << "Menu";
                SetPosition(95, posOption+2);
                cout << "Quit";

                //down
                if (key == 80) {
                    SetPosition(93, posOption+i);
                    cout <<"  ";
                    i++;
                }
                //up
                else if (key == 72) {
                    SetPosition(93, posOption+i);
                    cout <<"  ";
                    i--;
                }
                else if (key==13){
                    if (i==0){
                        option=0;
                        clearOption(posOption);
                        DrawHandsForDealerMode(players, numbOfPlayer);
                        int* winner = rankingHands(players, numbOfPlayer);
                        pointsAllRounds(winner, numbOfPlayer, points);
                        Winner(winner,mode);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        cleanup(players, winner, numbOfPlayer);
                    }
                    else if (i==1){
                        clearOption(posOption);
                        SetPosition(0,0);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points,numbOfPlayer),mode);
                        delete[]points;
                        menu=1;
                        i=0;
                        key=_getch();
                        continue;
                    }
                    else if (i==2){
                        clearOption(posOption);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer),mode);
                        delete[]points;
                        system("cls");
                        DrawEndGame();
                        _getch();
                        break;
                    }        
                }

                if (i==3)
                    i=0;
                else if (i==-1)
                    i=2;

                SetColor(13);
                SetPosition(93, posOption + i);
                cout << "->";
                SetColor(7);
            }    
        }
           
        if (key == 13 && menu == 0 && mode == 5) {
            system("cls");
            suffleCards(Deck);
            int restCard = 52 - 5 * numbOfPlayer;
            restDeck = new int[restCard];
            players = dealingForHands(Deck, numbOfPlayer, restDeck);
            DrawTable();
            DrawPointForDealerMode(points, numbOfPlayer);
            DrawDealerAndPlayer(numbOfPlayer);
            DrawOption();
            DrawPokerText(-9, 4, 9 * 16 + 0, 13, 75);      //left top color length width
            key = _getch();

            DrawTable();
            DrawGUI();
            key = _getch();
            if (key == 13) {
                DrawOption();
                DrawTable();
                HandlePlayer(players, numbOfPlayer, restDeck);
                DrawTable();
                HandleDealerMedium(players[0], players, numbOfPlayer, restDeck);
                DrawTable();
                DrawPreResult();

                key = _getch();
                DrawTable();
                DrawHandsForDealerMode(players, numbOfPlayer);
                int* winner = rankingHands(players, numbOfPlayer);
                pointsAllRounds(winner, numbOfPlayer, points);
                Winner(winner, mode);
                DrawPointForDealerMode(points, numbOfPlayer);
                cleanup(players, winner, numbOfPlayer);
            }
            if (key == 27) {
                option = 1;
                i = 0;
            }
            if (option == 1) {
                SetPosition(95, posOption);
                cout << "Continue";
                SetPosition(95, posOption + 1);
                cout << "Menu";
                SetPosition(95, posOption + 2);
                cout << "Quit";

                //down
                if (key == 80) {
                    SetPosition(93, posOption + i);
                    cout << "  ";
                    i++;
                }
                //up
                else if (key == 72) {
                    SetPosition(93, posOption + i);
                    cout << "  ";
                    i--;
                }
                else if (key == 13) {
                    if (i == 0) {
                        option = 0;
                        clearOption(posOption);
                        DrawHandsForDealerMode(players, numbOfPlayer);
                        int* winner = rankingHands(players, numbOfPlayer);
                        pointsAllRounds(winner, numbOfPlayer, points);
                        Winner(winner, mode);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        cleanup(players, winner, numbOfPlayer);
                    }
                    else if (i == 1) {
                        clearOption(posOption);
                        SetPosition(0, 0);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer), mode);
                        delete[]points;
                        menu = 1;
                        i = 0;
                        key = _getch();
                        continue;
                    }
                    else if (i == 2) {
                        clearOption(posOption);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer), mode);
                        delete[]points;
                        system("cls");
                        DrawEndGame();
                        _getch();
                        break;
                    }
                }

                if (i == 3)
                    i = 0;
                else if (i == -1)
                    i = 2;

                SetColor(13);
                SetPosition(93, posOption + i);
                cout << "->";
                SetColor(7);
            }
        }

        if (key == 13 && menu == 0 && mode == 6) {
            system("cls");
            suffleCards(Deck);
            int restCard = 52 - 5 * numbOfPlayer;
            restDeck = new int[restCard];
            players = dealingForHands(Deck, numbOfPlayer, restDeck);
            DrawTable();
            DrawPointForDealerMode(points, numbOfPlayer);
            DrawDealerAndPlayer(numbOfPlayer);
            DrawOption();
            DrawPokerText(-9, 4, 9 * 16 + 0, 13, 75);      //left top color length width
            key = _getch();

            DrawTable();
            DrawGUI();
            key = _getch();
            if (key == 13) {
                DrawOption();
                DrawTable();
                HandlePlayer(players, numbOfPlayer, restDeck);
                DrawTable();
                HandleDealerHard(players[0],players,numbOfPlayer,restDeck);
                DrawTable();
                DrawPreResult();

                key = _getch();
                DrawTable();
                DrawHandsForDealerMode(players, numbOfPlayer);
                int* winner = rankingHands(players, numbOfPlayer);
                pointsAllRounds(winner, numbOfPlayer, points);
                Winner(winner, mode);
                DrawPointForDealerMode(points, numbOfPlayer);
                cleanup(players, winner, numbOfPlayer);
            }
            if (key == 27) {
                option = 1;
                i = 0;
            }
            if (option == 1) {
                SetPosition(95, posOption);
                cout << "Continue";
                SetPosition(95, posOption + 1);
                cout << "Menu";
                SetPosition(95, posOption + 2);
                cout << "Quit";

                //down
                if (key == 80) {
                    SetPosition(93, posOption + i);
                    cout << "  ";
                    i++;
                }
                //up
                else if (key == 72) {
                    SetPosition(93, posOption + i);
                    cout << "  ";
                    i--;
                }
                else if (key == 13) {
                    if (i == 0) {
                        option = 0;
                        clearOption(posOption);
                        DrawHandsForDealerMode(players, numbOfPlayer);
                        int* winner = rankingHands(players, numbOfPlayer);
                        pointsAllRounds(winner, numbOfPlayer, points);
                        Winner(winner, mode);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        cleanup(players, winner, numbOfPlayer);
                    }
                    else if (i == 1) {
                        clearOption(posOption);
                        SetPosition(0, 0);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer), mode);
                        delete[]points;
                        menu = 1;
                        i = 0;
                        key = _getch();
                        continue;
                    }
                    else if (i == 2) {
                        clearOption(posOption);
                        DrawPointForDealerMode(points, numbOfPlayer);
                        WinnerTop(evaluateHands(points, numbOfPlayer), mode);
                        delete[]points;
                        system("cls");
                        DrawEndGame();
                        _getch();
                        break;
                    }
                }

                if (i == 3)
                    i = 0;
                else if (i == -1)
                    i = 2;

                SetColor(13);
                SetPosition(93, posOption + i);
                cout << "->";
                SetColor(7);
            }
        }
    }
    SetPosition(30, 30);
    return 0;
}

void game() {
   pthread_t animation;
   pthread_t play;
   pthread_create(&play, NULL, &start, NULL);
   pthread_create(&animation, NULL, &keyframe, NULL);
   pthread_join(play, NULL);
   pthread_join(animation, NULL);


}