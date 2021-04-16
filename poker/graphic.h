//#pragma once

//unicode
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#include <math.h>


//definition-------------------------------------------------------------------------
//utility
int marginLeft(int** hand, int currentCard) {
    int count = 0;
    for (int i = 0; i < currentCard; ++i) {
        if (hand[i][1] == 8)
            count++;
    }
    return count;
}
void clearOption(int pos) {
    SetPosition(93, pos);
    cout << "          ";
    SetPosition(93, pos + 1);
    cout << "          ";
    SetPosition(93, pos + 2);
    cout << "          ";
}
void cleanup(int ***players,int *&point,int n){
    delete[] point;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 5; ++j) {
            delete[] players[i][j];
        }   
        delete[]players[i];
    }
    delete[] players;
}
int* seethefuture(int*& restDeck) {
    int* tempCard = new int[2];
    tempCard[0] = restDeck[0] / 13;
    tempCard[1] = restDeck[0] % 13;
    return tempCard;
}

//select card
//&_dealer
int pickCardof_Hard_Dealer(int* cardrest, int** hand) {
    //  cardrest: a card that you just picked
    // hand : current hand you are having
    // status: type of hand.

    sort(hand, desc);
    int** Dealer = new int* [5];
    for (int i = 0; i < 5; ++i) {
        Dealer[i] = new int[2];
        Dealer[i][0] = hand[i][0];
        Dealer[i][1] = hand[i][1];
    }

    int oldSta = getStatusOfHand(hand);     //save the old status
    int* oldR = maxRanks(hand, oldSta);     // save the old max value ranks sorted with desc 

    int newSta = 0;
    int* newR = new int[6];


    int** newhand = new int* [6];             // a hand with a card you just picked
    for (int i = 0; i < 6; i++) newhand[i] = new int[2];
    for (int i = 0; i < 5; i++) {
        newhand[i][0] = Dealer[i][0];
        newhand[i][1] = Dealer[i][1];
    }
    newhand[5][0] = cardrest[0];
    newhand[5][1] = cardrest[1];
    sortNewHand(newhand, desc);

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    if (oldSta == 8) {                       // if Four of a kind -> place the other
        for (int i = 0; i < 5; i++) {
            if (Dealer[i][1] != oldR[1]) {
                Dealer[i][0] = cardrest[0];
                Dealer[i][1] = cardrest[1];
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    int suit[4][7];                              // find better flush -- suit
    for (int i = 0; i < 4; i++) suit[i][6] = 0;
    int nSuit = 0;
    for (int i = 0; i < 6; i++) {
        nSuit = newhand[i][0];
        suit[nSuit][6]++;
        int x = suit[nSuit][6];
        suit[nSuit][x] = newhand[i][1];
        if (x == 5) {
            newSta = 6;
            newR = suit[nSuit];
            break;
        }
    }

    if (newSta > oldSta) {
        oldSta = newSta;
        for (int i = 0; i < 5; i++) {
            Dealer[i][0] = nSuit;
            Dealer[i][1] = newR[i];
        }
    }
    else if (newSta == oldSta) {
        for (int i = 0; i < 5; i++) {
            if (newR[i] > oldR[i]) Dealer[i][1] = newR[i];
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////

    int index = 0;
    for (int i = 0; i < 2; i++) {                                     // find better straight
        for (int j = 0; j < 4; j++) {
            if (newhand[i + j][1] - 1 == newhand[i + j + 1][1]) {
                if (j == 3) {
                    for (int d = 0; d < 5; d++) {
                        newR[d] = newhand[i + d][1];
                    }
                    newSta = 5;
                    index = i;
                    break;
                }
            }
            else break;
        }
    }

    if ((newSta > oldSta) || (newSta == oldSta && newR[0] > oldR[0])) {
        oldSta = newSta;
        for (int i = 0; i < 5; i++) {
            hand[i][0] = newhand[index][0];
            hand[i][1] = newR[i];
            index++;
        }
    }

    int b = 0;
    int bo2 = 0;
    int GT4 = -1;
    int GT3 = -1;
    int GT2[2] = { -1,-1 };
    for (int i = 0; i < 5; i++) {
        if (newhand[i][1] == newhand[i + 1][1]) b++;
        else b = 0;
        if (b == 3) {
            GT3 = -1;
            GT4 = newhand[i][1];
        }
        if (b == 2) {
            bo2--;
            GT2[bo2] = -1;
            if (GT3 < newhand[i][1]) {
                if (GT3 > -1) {
                    if (GT3 > GT2[0]) GT2[0] = GT3;
                    else if (GT3 > GT2[1]) GT2[1] = GT3;
                }
                GT3 = newhand[i][1];
            }
        }
        if (b == 1) {
            GT2[bo2] = newhand[i][1];
            bo2++;
        }
    }
    /// 
    int inew = 0;
    int sec[3] = { -2,-2,-2 };
    int isec = 0;
    if (GT4 > -1) {                                                // find Four a kind 
        for (int i = 0; i < 6; i++) {
            if (newhand[i][1] == GT4) {
                Dealer[inew][0] = newhand[i][0];
                Dealer[inew][1] = newhand[i][1];
                inew++;
            }
            if (newhand[i][1] != GT4 && sec[0] == -2) sec[0] = i;
        }
        Dealer[inew][0] = newhand[sec[0]][0];
        Dealer[inew][1] = newhand[sec[0]][1];
    }
    ///    
    if (GT3 > -1) {
        for (int i = 0; i < 6; i++) {
            if (newhand[i][1] == GT3) {
                Dealer[inew][0] = newhand[i][0];
                Dealer[inew][1] = newhand[i][1];
                inew++;
            }
            if (newhand[i][1] != GT3 && sec[isec] == -2) {
                sec[isec] = i;
                isec++;
            }
        }
        if (GT2[0] > -1) {                        //find Full house
            for (int i = 0; i < 6; i++) {
                if (newhand[i][1] == GT2[0]) {
                    Dealer[inew][0] = newhand[i][0];
                    Dealer[inew][1] = newhand[i][1];
                    inew++;
                }
            }
        }
        else {                                     // find Three of a kind
            Dealer[inew][0] = newhand[sec[0]][0];
            Dealer[inew][1] = newhand[sec[0]][1];
            inew++;
            Dealer[inew][0] = newhand[sec[1]][0];
            Dealer[inew][1] = newhand[sec[1]][1];
            inew++;
        }
    }

    ///
    if (GT2[0] > -1) {
        for (int i = 0; i < 6; i++) {
            if (newhand[i][1] == GT2[0]) {
                Dealer[inew][0] = newhand[i][0];
                Dealer[inew][1] = newhand[i][1];
                inew++;
            }

            if (newhand[i][1] != GT2[0] && newhand[i][1] != GT2[1] && sec[isec] == -2) {
                sec[isec] = i;
                isec++;
            }
        }
        if (GT2[1] > -1) {                                   // find two pair
            for (int i = 0; i < 6; i++) {
                if (newhand[i][1] == GT2[1]) {
                    Dealer[inew][0] = newhand[i][0];
                    Dealer[inew][1] = newhand[i][1];
                    inew++;
                }
            }
            Dealer[inew][0] = newhand[sec[0]][0];
            Dealer[inew][1] = newhand[sec[0]][1];
        }
        else {                                                // find a pair
            Dealer[inew][0] = newhand[sec[0]][0];
            Dealer[inew][1] = newhand[sec[0]][1];
            inew++;
            Dealer[inew][0] = newhand[sec[1]][0];
            Dealer[inew][1] = newhand[sec[1]][1];
            inew++;
            Dealer[inew][0] = newhand[sec[2]][0];
            Dealer[inew][1] = newhand[sec[2]][1];
            inew++;
        }

    }
    //////////////////////////////////////////////////////////////////////////////////////////
    if (inew == 0) {
        for (int i = 0; i < 5; i++) {
            Dealer[i][0] = newhand[i][0];
            Dealer[i][1] = newhand[i][1];
        }
    }

    int theSAME = 0;
    if (getStatusOfHand(Dealer) >= getStatusOfHand(hand)) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (hand[i][0] != Dealer[j][0] || hand[i][1] != Dealer[j][1]) theSAME++;
            }
            if (theSAME == 5) return i;
            theSAME = 0;
        }
    }

    for (int i = 0; i < 5; i++) {
        delete[]Dealer[i];
    }
    delete[] Dealer;

    for (int i = 0; i < 6; i++) {
        delete[]newhand[i];
    }
    delete[] newR;
    delete[] newhand;
    delete []oldR;
    return -1;
}
bool dealerChoseHard(int** dealer, int* tempCard, int times) {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 5;
    int chose = 0;
    int key;
    while (true) {
        SetColor(9 * 16);
        SetPosition(left + ceil(width / 2) - 12, top + ceil(length / 2) - 1);
        cout << "                                ";
        SetColor(7);
        SetPosition(left + ceil(width / 2) - 19, top + ceil(length / 2) - 2);
        cout << " I'm Dealer , this's my turn , " << times << " times ";

        //hands
        SetPosition(left + ceil(width / 2) - 13, top + ceil(length / 2) - 1);
        cout << " My hands :                      ";
        SetPosition(left + ceil(width / 2) - 1, top + ceil(length / 2) - 1);
        printOneCard(dealer[0][0], dealer[0][1], 0);
        for (int i = 1; i < 5; ++i) {
            SetPosition(left + ceil(width / 2) - 1 + i * 3 + marginLeft(dealer, i), top + ceil(length / 2) - 1);
            printOneCard(dealer[i][0], dealer[i][1], 0);
        }

        //clearfix
        SetColor(9 * 16);
        SetPosition(left + ceil(width / 2) - 8, top + ceil(length / 2));
        cout << "                        ";
        SetColor(7);

        //chose
        if (chose == 0)
            SetColor(7 * 16);
        SetPosition(left + ceil(width / 2) - 5, top + ceil(length / 2));
        cout << " YES ";
        SetColor(7);

        if (chose == 1)
            SetColor(7 * 16);
        SetPosition(left + ceil(width / 2), top + ceil(length / 2));
        cout << " NO ";
        SetColor(7);
        //yes =0   || no =1
                /// 
        if (pickCardof_Hard_Dealer(tempCard, dealer) > -1) chose = 0;
        else chose = 1;

        if (chose == 0)
            SetColor(7 * 16);
        SetPosition(left + ceil(width / 2) - 5, top + ceil(length / 2));
        cout << " YES ";
        SetColor(7);
        Sleep(1000);
        if (chose == 1)
            SetColor(7 * 16);
        SetPosition(left + ceil(width / 2), top + ceil(length / 2));
        cout << " NO ";
        SetColor(7);

        Sleep(1000);
        break;

    }
    if (chose == 1)
        return false;
    return true;
}
bool dealerChoseMedium(int **dealer,int ***players,int n,int times) {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 5;
    int chose = 0;
    int key;
    int colorBg = 9;
    while (true) {
        //clearfix
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 2) - 12, top + ceil(length / 2) - 1);
        cout << "                                ";
        SetColor(7);

        SetPosition(left + ceil(width / 2) - 19, top + ceil(length / 2) - 2);
        cout << " I'm Dealer , this's my turn , "<< times << " times ";

        //hands
        SetPosition(left + ceil(width / 2) - 13, top + ceil(length / 2) - 1);
        cout << " My hands :                   ";
        SetPosition(left + ceil(width / 2) - 1, top + ceil(length / 2) - 1);
        printOneCard(dealer[0][0], dealer[0][1], 0);
        for (int i = 1; i < 5; ++i) {
            SetPosition(left + ceil(width / 2) - 1 + i * 3 + marginLeft(dealer, i), top + ceil(length / 2) - 1);
            printOneCard(dealer[i][0], dealer[i][1], 0);
        }

        //clearfix
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 2) - 8, top + ceil(length / 2) );
        cout << "                        ";
        SetColor(7);

        //chose
        if (chose == 0)
            SetColor(7 * 16);
        SetPosition(left + ceil(width / 2) - 4, top + ceil(length / 2) );
        cout << " YES ";
        SetColor(7);

        if (chose == 1)
            SetColor(7 * 16);
        SetPosition(left + ceil(width / 2) + 1, top + ceil(length / 2) );
        cout << " NO ";
        
        int x;
        for (int i = 0; i < 2; ++i) {
            Sleep(1000);
            x = rand() % 2;
            if (i==2){
                x = getStatusOfHand(dealer)>bestStatus(players,n) ? 1 : 0;
            }
            if (x == 0) {
                chose = 0;
            }
            else {
                chose = 1;
            }

            if (chose == 0)
                SetColor(7 * 16);
            SetPosition(left + ceil(width / 2) - 4, top + ceil(length / 2));
            cout << " YES ";
            SetColor(7);

            if (chose == 1)
                SetColor(7 * 16);
            SetPosition(left + ceil(width / 2) + 1, top + ceil(length / 2));
            cout << " NO ";
            SetColor(7);
        }
        
        Sleep(900);
        break;
    }
    if (chose == 1)
        return false;
    return true;
}
bool dealerChoseEasy(int **dealer,int times) {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 5;
    int chose = 0;
    int key;
    int colorBg = 9;
    while (true) {
        //clearfix
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 2) - 12, top + ceil(length / 2) - 1);
        cout << "                                ";
        SetColor(7);

        SetPosition(left + ceil(width / 2) - 19, top + ceil(length / 2) - 2);
        cout << " I'm Dealer , this's my turn , "<< times << " times ";

        //hands
        SetPosition(left + ceil(width / 2) - 13, top + ceil(length / 2) - 1);
        cout << " My hands :                   ";
        SetPosition(left + ceil(width / 2) - 1, top + ceil(length / 2) - 1);
        printOneCard(dealer[0][0], dealer[0][1], 0);
        for (int i = 1; i < 5; ++i) {
            SetPosition(left + ceil(width / 2) - 1 + i * 3 + marginLeft(dealer, i), top + ceil(length / 2) - 1);
            printOneCard(dealer[i][0], dealer[i][1], 0);
        }

        //clearfix
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 2) - 8, top + ceil(length / 2) );
        cout << "                        ";
        SetColor(7);

        //chose
        if (chose == 0)
            SetColor(7 * 16);
        SetPosition(left + ceil(width / 2) - 4, top + ceil(length / 2) );
        cout << " YES ";
        SetColor(7);

        if (chose == 1)
            SetColor(7 * 16);
        SetPosition(left + ceil(width / 2) + 1, top + ceil(length / 2) );
        cout << " NO ";
        
        int x;
        for (int i = 0; i < 2; ++i) {
            Sleep(1000);
            x = rand() % 2;
            if (x == 0) {
                chose = 0;
            }
            else {
                chose = 1;
            }

            if (chose == 0)
                SetColor(7 * 16);
            SetPosition(left + ceil(width / 2) - 4, top + ceil(length / 2));
            cout << " YES ";
            SetColor(7);

            if (chose == 1)
                SetColor(7 * 16);
            SetPosition(left + ceil(width / 2) + 1, top + ceil(length / 2));
            cout << " NO ";
            SetColor(7);
        }
        
        Sleep(900);
        break;
    }
    if (chose == 1)
        return false;
    return true;
}
int dealerPickToPlace(int** dealer, int* tempCard) {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    int position = 1;
    int key;
    int colorBg = 9;

    //clearfix
    SetColor(colorBg * 16);
    SetPosition(left + ceil(width / 2) - 30, top + ceil(length / 2) - 1);
    cout << "                                                           ";
    SetColor(7);
    SetColor(colorBg * 16);
    SetPosition(left + ceil(width / 2) - 30, top + ceil(length / 2) +1);
    cout << "                                                           ";
    SetColor(7);


    SetPosition(left + ceil(width / 2) - 9, top + ceil(length / 2) - 1);
    cout << " I just pick up :     ";
    SetPosition(left + ceil(width / 2) +9, top + ceil(length / 2) - 1);
    printOneCard(tempCard[0], tempCard[1], 0);
    while (true) {
        //clearfix
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 2) - 25, top + ceil(length / 2) );
        cout << "                                                ";
        SetColor(7);

        SetPosition(left + ceil(width / 2) - 6, top + ceil(length / 2) );
        printOneCard(dealer[0][0], dealer[0][1], position == 1);
        for (int i = 1; i < 5; ++i) {
            SetPosition(left + ceil(width / 2) - 6 + i * 3 + marginLeft(dealer, i), top + ceil(length / 2) );
            printOneCard(dealer[i][0], dealer[i][1], position == (i + 1));
        }
        
        int x;
        for (int i = 0; i < 5; ++i) {
            Sleep(1000);
            if (i == 4) 
                x = dealerPickToPlaceHard(dealer,tempCard);
            else {
                x = rand() % 5;
            }
            position = x;

            //clearfix
            SetColor(colorBg * 16);
            SetPosition(left + ceil(width / 2) - 6, top + ceil(length / 2));
            cout << "                            ";
            SetColor(7);

            SetPosition(left + ceil(width / 2) - 6, top + ceil(length / 2));
            printOneCard(dealer[0][0], dealer[0][1], position == 0);
            for (int i = 1; i < 5; ++i) {
                SetPosition(left + ceil(width / 2) - 6 + i * 3 + marginLeft(dealer, i), top + ceil(length / 2));
                printOneCard(dealer[i][0], dealer[i][1], position == i);
            }
        }

        Sleep(900);
        break;
    }
    return position;
}
//&_player
bool playerChose(int **player,int x,int times){
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 5;
    int chose=0;
    int key;
    int colorBg = 9;
    while(true){
        SetColor(colorBg *16);
        SetPosition(left+ceil(width/2)-12,top+ceil(length/2)-1);
        cout<<"                                        ";
        SetColor(7);
        SetPosition(left+ceil(width/2)-25,top+ceil(length/2)-2);
        cout<<" Player "<<x<<" , you have "<<times<<" times to pick , will you ?? ";

        //clearfix
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 2) - 30, top + ceil(length / 2) - 1);
        cout << "                                                ";
        SetColor(7);


        //hands
        SetPosition(left + ceil(width / 2) - 16, top + ceil(length / 2) - 1);
        cout << " Your hands :                   ";
        SetPosition(left + ceil(width / 2) -2, top + ceil(length / 2) -1);
        printOneCard(player[0][0], player[0][1],0);
        for (int i = 1; i < 5; ++i) {
            SetPosition(left + ceil(width / 2) -2 + i * 3 + marginLeft(player, i), top + ceil(length / 2) -1);
            printOneCard(player[i][0], player[i][1],0);
        }

        //tutorial
        SetPosition(left+ceil(width/2)-18,top+ceil(length/2));
        cout<<" \"Use arrow and enter key to select\" ";

        //clearfix
        SetColor(colorBg *16);
        SetPosition(left+ceil(width/2)-8,top+ceil(length/2)+1);
        cout<<"                        ";
        SetColor(7);

        //chose
        if (chose==0)
            SetColor(7*16);
        SetPosition(left+ceil(width/2)-4,top+ceil(length/2)+1);
        cout<<" YES ";
        SetColor(7);

        if (chose==1)
            SetColor(7*16);
        SetPosition(left+ceil(width/2)+1,top+ceil(length/2)+1);
        cout<<" NO ";
        key=_getch();
        if (key==13)
            break;
        if (key==77){
            chose++;
        }
        if (key==75){
            chose--;
        }
        
        if (chose>1)
            chose=0;
        else if (chose<0)
            chose=1;   
    }
    if (chose==1)
        return false;
    return true;
}
int* pickOneCard(int *&restDeck) {
    int *tempCard=new int[2];
    tempCard[0]=restDeck[0]/13;
    tempCard[1]=restDeck[0] % 13;
    restDeck++;
    return tempCard;
}
int pickToPlace(int **hand,int *tempCard){
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 5;
    int position=1;
    int key;
    int colorBg = 9;
    //clearfix
    SetColor(colorBg * 16);
    SetPosition(left + ceil(width / 2) - 30, top + ceil(length / 2) - 2);
    cout << "                                                         ";
    SetColor(7);
    SetColor(colorBg * 16);
    SetPosition(left+ceil(width/2)-30,top+ceil(length/2)-1);
    cout<<"                                                           ";
    SetColor(7);

    SetPosition(left+ceil(width/2)-23,top+ceil(length/2)-1);
    cout<<" You just pick up :     ";
    SetPosition(left+ceil(width/2)-3,top+ceil(length/2)-1);
    printOneCard(tempCard[0],tempCard[1],0);
    SetPosition(left+ceil(width/2),top+ceil(length/2)-1);
    cout<<", you want to replace ? ";
    while (true){
        //clearfix
        SetColor(colorBg *16);
        SetPosition(left + ceil(width/2)-12, top +ceil(length/2)+1);
        cout<<"                       ";
        SetColor(7);

        SetPosition(left + ceil(width/2)-7, top +ceil(length/2)+1);
        printOneCard(hand[0][0], hand[0][1],position==1);
        for (int i = 1; i < 5; ++i) {
            SetPosition(left +ceil(width/2)-7 + i * 3 + marginLeft(hand, i), top + ceil(length/2)+1);
            printOneCard(hand[i][0], hand[i][1],position==(i+1));
        }
        key= _getch();
        if (key==13)
            break;
        if (key==77){
            position++;
        }
        if (key==75){
            position--;
        }
        if (position>5)
            position=1;
        else if (position<1)
            position=5;   
    }
    return position-1;
}


//human
void DrawPokerText(int left,int top,int colorBg=0*16+2, int length=0, int width=0) {
    SetColor(colorBg);
    SetPosition(left + ceil(width / 2) , top + ceil(length / 2) - 2);
    //cout << "OOO     OOOO    0  0   00000   000   ";
    cout << char(219) << char(219) << char(219)<<"     "<< char(219) << char(219) << char(219)<<char(219)<<"    "<<char(219)<<"  "<<char(219)<<"   "<< char(219) << char(219) << char(219) << char(219) <<"   " << char(219) << char(219) << char(219) << " ";

    SetPosition(left + ceil(width / 2) , top + ceil(length / 2) - 1);
    //cout << "O  O   O    O   0 0    0       0  0 ";
    cout << char(219) << "  " << char(219) << "   " << char(219);
    SetColor(4 + colorBg / 16 * 16);
    cout << char(3) << "  ";
    SetColor(8 + colorBg / 16 * 16);
    cout << char(6);
    SetColor(colorBg);
    cout << char(219) << "   " << char(219) << " " << char(219) << "    " << char(219) << "      " << char(219) << "  " << char(219) << "";


    SetPosition(left + ceil(width / 2) , top + ceil(length / 2));
    //cout << "OOO    O    O   00     00000   000  ";
    cout << char(219) << char(219) << char(219) << "    " ;
    SetColor(colorBg%16*16);
    cout << " ";
    SetColor(colorBg);
    cout << "    ";
    SetColor(colorBg);
    cout << char(219) << "   " << char(219) << char(219) << "     " << char(219) << char(219) << char(219) << char(219)  << "   " << char(219) << char(219) << char(219) << " ";


    SetPosition(left + ceil(width / 2) , top + ceil(length / 2) + 1);
    //cout << "O      O    O   0 0    0       0  0 ";
    cout << char(219) << "      " << char(219); 
    SetColor(8 + colorBg / 16 * 16);
    cout << char(6);
    SetColor(4 + colorBg / 16 * 16);
    cout << "  ";
    SetColor(4 + colorBg / 16 * 16);
    cout<< char(4);
    SetColor(colorBg);
    cout<< char(219) << "   " << char(219) << " " << char(219) << "    " << char(219) << "      " << char(219) << "  " << char(219) << "";



    SetPosition(left + ceil(width / 2) , top + ceil(length / 2) + 2);
    //cout << "O       OOOO    0  0   00000   0  0 ";
    cout << char(219) << "       " << char(219) << char(219) << char(219) << char(219) << "    " << char(219) << "  " << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << "  "<<char(219) << "";




    SetColor(7);
}
void DrawGUI(){
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    SetColor(7);
    SetPosition(left+ceil(width/2)-10,top+ceil(length/2));
    cout<<" Press Enter to Play ";
}
int MenuEasyOrHard() {
    int left = 28;
    int top = 7;
    int key;
    int i = 0;
    int j = 0;

    //clearfix
    SetColor(0);
    SetPosition(left, top + 5);
    cout << "                                                              ";
    SetPosition(left, top + 6);
    cout << "                                                              ";
    SetColor(6);

    SetConsoleCP(437);
    SetColor(13);
    SetPosition(left + 22, top + 5);
    cout << char(282);
    SetColor(6);

    SetPosition(left + 24, top + 5);
    SetColor(8);
    cout << char(5);
    SetColor(6);
    cout << " Easy";

    SetPosition(left + 24, top + 6);
    SetColor(4);
    cout << char(4);
    SetColor(6);
    cout << " Medium";

    SetPosition(left + 24, top + 7);
    SetColor(8);
    cout << char(6);
    SetColor(6);
    cout << " Hard";
    while (true) {
        key = _getch();
        if (key == 80) {
            SetPosition(left + 22, top + 5 + i);
            cout << "  ";
            i++;
        }
        //up
        else if (key == 72) {
            SetPosition(left + 22, top + 5 + i);
            cout << "  ";
            i--;
        }
        else if (key == 13) {
            return i;
        }

        if (i == 3)
            i = 0;
        else if (i == -1)
            i = 2;

        SetColor(13);
        SetPosition(left + 22, top + 5 + i);
        cout << char(282);
        SetColor(7);
    }
}
int MenuPlayerCanPickOrNot() {
    int left = 29;
    int top = 7;
    int key; 
    int i = 0;
    SetColor(0);
    SetPosition(left, top + 5);
    cout << "                                               ";
    SetPosition(left, top + 6);
    cout << "                                               ";
    SetColor(6);

    SetConsoleCP(437);
    SetColor(13);
    SetPosition(left + 3, top + 5);
    cout << char(282);
    SetColor(6);

    SetPosition(left + 5, top + 5);
    SetColor(4);
    cout << char(4);
    SetColor(6);
    cout << " Dealer can pick 3 cards from the deck";

    SetPosition(left + 5, top + 6);
    SetColor(8);
    cout << char(5);
    SetColor(6);
    cout << " Dealer & players can pick 3 cards from the deck";
    while (true) {
        key = _getch();
        if (key == 80) {
            SetPosition(left + 3, top + 5 + i);
            cout << "  ";
            i++;
        }
        //up
        else if (key == 72) {
            SetPosition(left + 3, top + 5 + i);
            cout << "  ";
            i--;
        }
        else if (key == 13) {
            return i;
        }

        if (i == 2)
            i = 0;
        else if (i == -1)
            i = 1;

        SetColor(13);
        SetPosition(left + 3, top + 5 + i);
        cout << char(282);
        SetColor(7);
    }
}
int DrawMenuSelect(bool &menu) {
    int left =25;
    int top=7;
    SetColor(6);
    DrawPokerText(40,3,0*16+5);
    SetColor(6);
    SetPosition(left+17, top);     //60 22
    cout << "\"Gambling is poverty ladder\"";
    SetPosition(left + 5, top+1);
    cout << "You are going to dept billion and three hundred million";
    SetPosition(left+5, top + 2);
    cout << "-------------------------------------------------------";
    SetPosition(left+25, top+3);
    cout << "Your choice ??";

    SetConsoleCP(437);
    SetColor(13);
    SetPosition(left + 22, top + 5);
    cout << char(282);
    SetColor(6);

    SetPosition(left + 24, top + 5);
    SetColor(4);
    cout << char(3);
    SetColor(6);
    cout << " With human";

    
    SetPosition(left + 24, top + 6);
    SetColor(8);
    cout << char(3);
    SetColor(6);
    cout << " With dealer";


    ShowCur(0);
    int i = 0;
    int keyCode;
    while (true) {
        ShowCur(0);
        keyCode = _getch();
        //down
        if (keyCode == 80) {
            SetPosition(left + 22, top+5 + i);
            cout << "  ";
            i++;
        }
        //up
        else if (keyCode == 72) {
            SetPosition(left + 22, top+5 + i);
            cout << "  ";
            i--;
        }
        //enter
        else if (keyCode == 13) {
            if (i == 1){
                int pickable=MenuPlayerCanPickOrNot();
                if (pickable == 0) {
                    i = 2;
                }
                else if (pickable == 1) {
                    int mode = MenuEasyOrHard();
                    switch (mode) {
                    case 0:
                        i = 4;
                        break;
                    case 1:
                        i = 5;
                        break;
                    case 2:
                        i = 6;
                        break;
                    }
                }
            }
            else if (i == 0) {}

            break;
        }

        
        if (i == 2)
            i = 0;
        else if (i == -1)
            i = 1;

        SetColor(13);
        SetPosition(left + 22, top+5 + i);
        cout << char(282);
        SetColor(7);
    }

    int n = 5;

    //clearfix
    for (int j = 0; j < 20; ++j) {
        SetPosition(left, top + 5 + j);
        cout << "                                                                                        ";
    }

    SetColor(7);
    SetPosition(left, top + 4 + 0);
    cout << "                           ";
    SetPosition(left, top + 3);
    SetColor(6);
    cout << "Your choice is ";
    switch (i) {
    case 0:
        cout << "With human (limit: 10 players)";
        break;
    case 2:
        cout << "Dealer can pick 3 cards (limit: 7 players)";
        break;
    case 4:
        cout << "Easy, Dealer & players can pick 3 cards (limit: 5 players)";
        break;
    case 5:
        cout << "Medium, Dealer & players can pick 3 cards (limit: 5 players)";
        break;
    case 6:
        cout << "Hard, Dealer & players can pick 3 cards (limit: 5 players)";
        break;
    }
    menu=0;

    do {       
        for (int j=1;j<=10;++j){
            SetColor(7);
            SetPosition(left, top + 5 + j);
            cout << "                           ";           
        }
        SetPosition(0,0);
        SetColor(6);
        SetPosition(left + 22, top+4);
        cout << "Number of player: ";
        Sleep(500);
        SetColor(6);
        if ((i == 0 && (n > 10 || n < 2)) || (i == 2 && (n > 7 || n < 1)) || (i >=4 && (n > 5 || n < 1)))
            SetColor(4);
        SetPosition(left + 40, top+4);
        ShowCur(1);
        cin>>n;
        SetColor(7);
    } while ((i == 0 && (n > 10 || n < 2)) || (i == 2 && (n > 7 || n < 1)) || (i >=4 && (n > 5 || n < 1)));

    ShowCur(0);
    SetColor(2);
    SetPosition(left + 22, top+4);
    cout << "Number of player: " << n;
    return n*10+i;
}
void DrawTable() {
    SetColor(9 * 16);
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    for (int i = 0; i < length; ++i) {
        width = 75;
        if (i == 0 || i == length - 1) {
            width -= 32;
            SetPosition(left + round((75 - width) / 2), top + i);
        }
        else if (i == 1 || i == length - 2) {
            width -= 4;
            SetPosition(left + 2, top + i);
        }
        else {
            SetPosition(left, top + i);
        }
        for (int j = 0; j < width; ++j) {
            cout << " ";
        }
    }
    SetColor(7);
}
void DrawHands(int*** hand, int n) {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    for (int i = 0; i < n; ++i)
        sort(hand[i], asc);
    if (1 <= n) {  
        bool StraightOrFlush=isStraightOrFlush(hand[0]);
        for (int i = 0; i < 5; ++i) {
            bool PairOrThree=isPairOrThree(hand[0],i);
            SetPosition(left + 2, top + i + ceil(length / 2) - 2);                 
            printOneCard(hand[0][i][0], hand[0][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (2 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[1]);
        for (int i = 0; i < 5; ++i) {
            bool PairOrThree=isPairOrThree(hand[1],i);
            SetPosition(left + width - 4, top + i + ceil(length / 2) - 2);
            printOneCard(hand[1][i][0], hand[1][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (3 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[2]);
        bool PairOrThree=isPairOrThree(hand[2],0);
        SetPosition(left + 5, top + 2);
        printOneCard(hand[2][0][0], hand[2][0][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree=isPairOrThree(hand[2],i);
            SetPosition(left + 5 + i * 3 + marginLeft(hand[2], i), top + 2);
            printOneCard(hand[2][i][0], hand[2][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (4 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[3]);
        bool PairOrThree=isPairOrThree(hand[3],0);
        SetPosition(left + 5 + (4 * 3 + 2 + 3), top + 1);
        printOneCard(hand[3][0][0], hand[3][0][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree=isPairOrThree(hand[3],i);
            SetPosition(left + 5 + i * 3 + (4 * 3 + 2 + 3) + marginLeft(hand[3], i), top + 1);
            printOneCard(hand[3][i][0], hand[3][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (5 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[4]);
        bool PairOrThree=isPairOrThree(hand[4],0);
        SetPosition(left + 5 + (4 * 3 + 2 + 3) * 2, top + 1);
        printOneCard(hand[4][0][0], hand[4][0][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree=isPairOrThree(hand[4],i);
            SetPosition(left + 5 + i * 3 + (4 * 3 + 2 + 3) * 2 + marginLeft(hand[4], i), top + 1);
            printOneCard(hand[4][i][0], hand[4][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (6 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[5]);
        bool PairOrThree=isPairOrThree(hand[5],0);
        SetPosition(left + 5 + (4 * 3 + 2 + 3) * 3, top + 2);
        printOneCard(hand[5][0][0], hand[5][0][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree=isPairOrThree(hand[5],i);
            SetPosition(left + 5 + i * 3 + (4 * 3 + 2 + 3) * 3 + marginLeft(hand[5], i), top + 2);
            printOneCard(hand[5][i][0], hand[5][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    //----------------------------------------------
    if (7 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[6]);
        bool PairOrThree=isPairOrThree(hand[6],0);
        SetPosition(left + 5, top - 3 + length);
        printOneCard(hand[6][0][0], hand[6][0][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree=isPairOrThree(hand[6],i);
            SetPosition(left + 5 + i * 3 + marginLeft(hand[6], i), top - 3 + length);
            printOneCard(hand[6][i][0], hand[6][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (8 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[7]);
        bool PairOrThree=isPairOrThree(hand[7],0);
        SetPosition(left + 5 + (4 * 3 + 2 + 3), top - 2 + length);
        printOneCard(hand[7][0][0], hand[7][0][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree=isPairOrThree(hand[7],i);
            SetPosition(left + 5 + i * 3 + (4 * 3 + 2 + 3) + marginLeft(hand[7], i), top - 2 + length);
            printOneCard(hand[7][i][0], hand[7][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (9 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[8]);
        bool PairOrThree=isPairOrThree(hand[8],0);
        SetPosition(left + 5 + (4 * 3 + 2 + 3) * 2, top - 2 + length);
        printOneCard(hand[8][0][0], hand[8][0][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree=isPairOrThree(hand[8],i);
            SetPosition(left + 5 + i * 3 + (4 * 3 + 2 + 3) * 2 + marginLeft(hand[8], i), top - 2 + length);
            printOneCard(hand[8][i][0], hand[8][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (10 <= n) {
        bool StraightOrFlush=isStraightOrFlush(hand[9]);
        bool PairOrThree=isPairOrThree(hand[9],0);
        SetPosition(left + 5 + (4 * 3 + 2 + 3) * 3, top - 3 + length);
        printOneCard(hand[9][0][0], hand[9][0][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree=isPairOrThree(hand[9],i);
            SetPosition(left + 5 + i * 3 + (4 * 3 + 2 + 3) * 3 + marginLeft(hand[9], i), top - 3 + length);
            printOneCard(hand[9][i][0], hand[9][i][1],StraightOrFlush==1 ? StraightOrFlush : PairOrThree);
        }
    }

}
void DrawPlayer(int n) {
    int colorText=8;
    int colorBg=8;
    SetColor(colorBg * 16);
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    //id 1
    if (1<=n){
        SetPosition(left - 2, top + floor(length / 2));
        cout << "  ";
        SetColor(colorText);
        SetPosition(left - 2 - 5, top + floor(length / 2));
        cout << "ID:1";
        SetColor(colorBg * 16);
    }
    
    //id 2
    if (2<=n){
        SetPosition(left + width, top + floor(length / 2));
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + width + 3, top + floor(length / 2));
        cout << "ID:2";
        SetColor(colorBg * 16);
    }
    //-----------------------------------------------------------------------------------
    //id 3
    if (3<=n){
        SetPosition(left + ceil(width / 4) - 7, top);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 4) - 8, top - 2);
        cout << "ID:3";
        SetColor(colorBg * 16);
    }
    

    //id 4
    if (4<=n){
        SetPosition(left + ceil(width / 2) - 9, top - 1);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 2) - 10, top - 3);
        cout << "ID:4";
        SetColor(colorBg * 16);
    }
    

    //id 5
    if (5<=n){
        SetPosition(left + ceil(width / 2) + 8, top - 1);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 2) + 7, top - 3);
        cout << "ID:5";
        SetColor(colorBg * 16);
    }
    

    //id 6
    if (6<=n){
        SetPosition(left + ceil(width / 4 * 3) + 8, top);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 4 * 3) + 7, top - 2);
        cout << "ID:6";
        SetColor(colorBg * 16);
    }
    
    //-----------------------------------------------------------------------------------------
    //id 7
    if (7<=n){
        SetPosition(left + ceil(width / 4) - 7, top - 1 + length);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 4) - 8, top - 1 + length + 2);
        cout << "ID:7";
        SetColor(colorBg * 16);
    }
    
    //id 8
    if (8<=n){
        SetPosition(left + ceil(width / 2) - 9, top + length);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 2) - 10, top + length + 2);
        cout << "ID:8";
        SetColor(colorBg * 16);
    }
    //id 9
    if (9<=n){
        SetPosition(left + ceil(width / 2) + 8, top + length);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 2) + 7, top + length + 2);
        cout << "ID:9";
        SetColor(colorBg * 16);
    }
    

    //id 10
    if (10<=n){
        SetPosition(left + ceil(width / 4 * 3) + 8, top - 1 + length);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 4 * 3) + 7, top - 1 + length + 2);
        cout << "ID:10";
        SetColor(colorBg * 16);
    } 
    SetColor(7);
}
void DrawEndGame(){
    SetColor(6);
    int left = 40;
    int top = 12;
    SetPosition(left,top);
    cout<<"Copyright: Nguyen Anh and Quoc Nam";
    SetPosition(left+8,top+1);
    cout<<"Thanks for playing";
}
 
//dealer
void HandlePlayer(int*** hand, int n, int*& restDeck) {
    int key;
    int colorText = 8;
    int colorBg = 8;
    SetColor(colorBg * 16);
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;

    for (int i = 1; i < n; ++i) {
        sort(hand[i], asc);
    }
    for (int player = 1; player < n; ++player) {
        for (int i = 0; i < 3; ++i) {
            bool chosen = playerChose(hand[player], player, 3 - i);
            if (chosen == true) {
                int* tempCard = pickOneCard(restDeck);
                int pos = pickToPlace(hand[player], tempCard);
                delete hand[player][pos];
                hand[player][pos] = tempCard;
                sort(hand[player], asc);
            }
            else
                break;
        }
    }

}
void DrawHandsForDealerMode(int*** hand, int n) {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    for (int i = 0; i < n; ++i)
        sort(hand[i], asc);
    //hand of dealer
    if (1 <= n) {
        bool StraightOrFlush = isStraightOrFlush(hand[0]);
        bool PairOrThree = isPairOrThree(hand[0], 0);
        SetPosition(left + ceil(width / 2) - 6, top + length - 2);
        printOneCard(hand[0][0][0], hand[0][0][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree = isPairOrThree(hand[0], i);
            SetPosition(left + ceil(width / 2) - 6 + i * 3 + marginLeft(hand[0], i), top + length - 2);
            printOneCard(hand[0][i][0], hand[0][i][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (2 <= n) {
        bool StraightOrFlush = isStraightOrFlush(hand[1]);
        for (int i = 0; i < 5; ++i) {
            bool PairOrThree = isPairOrThree(hand[1], i);
            SetPosition(left + 2, top + i + ceil(length / 2) - 2);
            printOneCard(hand[1][i][0], hand[1][i][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (3 <= n) {
        bool StraightOrFlush = isStraightOrFlush(hand[2]);
        for (int i = 0; i < 5; ++i) {
            bool PairOrThree = isPairOrThree(hand[2], i);
            SetPosition(left + width - 4, top + i + ceil(length / 2) - 2);
            printOneCard(hand[2][i][0], hand[2][i][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (4 <= n) {
        bool StraightOrFlush = isStraightOrFlush(hand[3]);
        bool PairOrThree = isPairOrThree(hand[3], 0);
        SetPosition(left + 5, top + 2);
        printOneCard(hand[3][0][0], hand[3][0][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree = isPairOrThree(hand[3], i);
            SetPosition(left + 5 + i * 3 + marginLeft(hand[3], i), top + 2);
            printOneCard(hand[3][i][0], hand[3][i][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (5 <= n) {
        bool StraightOrFlush = isStraightOrFlush(hand[4]);
        bool PairOrThree = isPairOrThree(hand[4], 0);
        SetPosition(left + ceil(width / 2) - 6, top + 1);
        printOneCard(hand[4][0][0], hand[4][0][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree = isPairOrThree(hand[4], i);
            SetPosition(left + ceil(width / 2) - 6 + i * 3 + marginLeft(hand[4], i), top + 1);
            printOneCard(hand[4][i][0], hand[4][i][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (6 <= n) {
        bool StraightOrFlush = isStraightOrFlush(hand[5]);
        bool PairOrThree = isPairOrThree(hand[5], 0);
        SetPosition(left + 5 + (4 * 3 + 2 + 3) * 3, top + 2);
        printOneCard(hand[5][0][0], hand[5][0][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree = isPairOrThree(hand[5], i);
            SetPosition(left + 5 + i * 3 + (4 * 3 + 2 + 3) * 3 + marginLeft(hand[5], i), top + 2);
            printOneCard(hand[5][i][0], hand[5][i][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (7 <= n) {
        bool StraightOrFlush = isStraightOrFlush(hand[6]);
        bool PairOrThree = isPairOrThree(hand[6], 0);
        SetPosition(left + 5, top - 3 + length);
        printOneCard(hand[6][0][0], hand[6][0][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree = isPairOrThree(hand[6], i);
            SetPosition(left + 5 + i * 3 + marginLeft(hand[6], i), top - 3 + length);
            printOneCard(hand[6][i][0], hand[6][i][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        }
    }
    if (8 <= n) {
        bool StraightOrFlush = isStraightOrFlush(hand[7]);
        bool PairOrThree = isPairOrThree(hand[7], 0);
        SetPosition(left + 5 + (4 * 3 + 2 + 3) * 3, top - 3 + length);
        printOneCard(hand[7][0][0], hand[7][0][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        for (int i = 1; i < 5; ++i) {
            PairOrThree = isPairOrThree(hand[7], i);
            SetPosition(left + 5 + i * 3 + (4 * 3 + 2 + 3) * 3 + marginLeft(hand[7], i), top - 3 + length);
            printOneCard(hand[7][i][0], hand[7][i][1], StraightOrFlush == 1 ? StraightOrFlush : PairOrThree);
        }
    }

}
void DrawDealerAndPlayer(int n) {
    int colorText = 8;
    int colorBg = 8;
    SetColor(colorBg * 16);
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    //dealer
    if (1 <= n) {
        SetColor(4 * 16 + 4);
        SetPosition(left + ceil(width / 2) , top + length);
        cout << "  ";
        SetColor(4);
        SetPosition(left + ceil(width / 2) - 2, top + length + 2);
        cout << "Dealer";
    }
    //id 1
    if (2 <= n) {
        SetColor(colorBg * 16);
        SetPosition(left - 2, top + floor(length / 2));
        cout << "  ";
        SetColor(colorText);
        SetPosition(left - 2 - 5, top + floor(length / 2));
        cout << "ID:1";
    }
    //id 2
    if (3 <= n) {
        SetColor(colorBg * 16);
        SetPosition(left + width, top + floor(length / 2));
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + width + 3, top + floor(length / 2));
        cout << "ID:2";
    }
    //-----------------------------------------------------------------------------------
    //id 3
    if (4 <= n) {
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 4) - 7, top);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 4) - 8, top - 2);
        cout << "ID:3";
    }

    //id 4
    if (5 <= n) {
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 2) , top - 1);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 2) - 1, top - 3);
        cout << "ID:4";
    }

    //id 5
    if (6 <= n) {
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 4 * 3) + 8, top);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 4 * 3) + 7, top - 2);
        cout << "ID:5";
    }
    if (7 <= n) {
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 4) - 7, top - 1 + length);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 4) - 8, top - 1 + length + 2);
        cout << "ID:6";
    }
    if (8 <= n) {
        SetColor(colorBg * 16);
        SetPosition(left + ceil(width / 4 * 3) + 8, top - 1 + length);
        cout << "  ";
        SetColor(colorText);
        SetPosition(left + ceil(width / 4 * 3) + 7, top - 1 + length + 2);
        cout << "ID:7";
    }
    SetColor(7);
}


//point
void Winner(int* point, int mode = 0) {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;

    SetColor(9 * 0 + 6);
    SetPosition(left + ceil(width / 2) - 9, top + ceil(length / 2));
    cout << " Winner player: ";
    int n = 0;
    while (point[n] > -1) {
        n++;
    }
    if (mode == 0) {
        cout << point[0] + 1 << " ";
    }
    else if (mode >= 2) {
        for (int i = 0; i < n; ++i) {
            if (point[i] == 0) {
                SetColor(4);
                cout << "Dealer ";
            }
            else {
                cout << point[i] << " ";
            }
        }
        
    }
    SetColor(7);
}
void WinnerTop(int* winner, int mode = 0) {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    SetColor(9 * 16);
    SetPosition(left + ceil(width / 2) - 11, top + ceil(length / 2));
    cout << "                                  ";

    SetColor(10);
    SetPosition(left + ceil(width / 2) - 16, top + ceil(length / 2));
    cout << " Winners of the POKER GAME: ";
    int n = 0;
    while (winner[n] > -1) {
        n++;
    }
    if (n == 0) {
        cout << "None ";
        return;
    }

    if (mode == 0) {
        for (int i = 0; i < n; ++i)
            cout << winner[i] + 1 << " ";
    }
    else if (mode >= 2) {
        for (int i = 0; i < n; ++i) {
            if (winner[i] == 0) {
                SetColor(4);
                cout << "Dealer ";
                SetColor(6);
            }
            else
                cout << winner[i] << " ";
        }
    }
    SetColor(7);
}
void DrawPoint(int* point, int n) {
    SetColor(6 * 16);
    for (int i = -1; i < n; ++i) {
        SetPosition(95, 6 + i);               //105              
        cout << "            ";
    }
    SetPosition(95, 5);
    cout << "   Point";                                                 //scores
    for (int i = 0; i < n; ++i) {
        SetPosition(97, 6 + i);
        cout << "id " << i + 1 << ":" << point[i];
    }
    SetColor(7);
}
void DrawOption() {
    int curOption = 19;

    SetPosition(93, curOption - 2);
    cout << "Press Enter to continue";
    SetPosition(93, curOption - 1);
    cout << "Press ESC to option";
}
void DrawPreResult() {
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    SetPosition(left + ceil(width / 2) - 17, top + ceil(length / 2));
    cout << " Now , Press Enter see the result ";
}
void DrawPointForDealerMode(int* point, int n) {
    SetColor(6 * 16);
    for (int i = -1; i < n; ++i) {
        SetPosition(95, 6 + i);               //105              
        cout << "            ";
    }
    SetPosition(95, 5);
    cout << "   Point";
    SetPosition(97, 6);
    cout << "Dealer:" << point[0] << " ";                                      //scores
    for (int i = 1; i < n; ++i) {
        SetPosition(97, 6 + i);
        cout << "id " << i << ":" << point[i];
    }
    SetColor(7);
}


//dealer mode
void HandleDealerEasy(int** dealer, int*& restDeck) {
    int key;
    int colorText = 8;
    int colorBg = 8;
    SetColor(colorBg * 16);
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    sort(dealer, asc);
    for (int i = 0; i < 3; ++i) {
        bool chosen = dealerChoseEasy(dealer, 3 - i);
        if (chosen == true) {
            int* tempCard = pickOneCard(restDeck);
            int pos = dealerPickToPlace(dealer, tempCard);
            delete dealer[pos];
            dealer[pos] = tempCard;
            sort(dealer, asc);
        }
        else
            break;
    }
}
void HandleDealerMedium(int** dealer, int*** players, int n, int*& restDeck) {
    int key;
    int colorText = 8;
    int colorBg = 8;
    SetColor(colorBg * 16);
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    sort(dealer, asc);
    for (int i = 0; i < 3; ++i) {

        bool chosen = dealerChoseMedium(dealer,players,n, 3 - i);
        if (chosen == true) {
            int* tempCard = pickOneCard(restDeck);
            int pos = dealerPickToPlace(dealer, tempCard);
            swapPointer(dealer[pos], tempCard);
            delete[]tempCard;
            sort(dealer, asc);
        }
        else
            break;
    }
}
void HandleDealerHard(int** dealer, int*** players, int n, int* &restDeck) {
    int key;
    int colorText = 8;
    int colorBg = 8;
    SetColor(colorBg * 16);
    int length = 13;
    int width = 75;
    int left = 8;
    int top = 4;
    sort(dealer, asc);
    for (int i = 0; i < 3; ++i) {
        int* tempCard = seethefuture(restDeck);
        bool chosen = dealerChoseHard(dealer, tempCard, 3 - i);
        if (chosen == true) {
            int pos = pickCardof_Hard_Dealer(tempCard, dealer);
            swapPointer(dealer[pos], tempCard);
            restDeck = &restDeck[1];
            sort(dealer, asc);
        }
        delete[] tempCard;
        if (chosen != true) break;
    }   
}

