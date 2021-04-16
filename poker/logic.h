//#pragma once

#include <iostream>
using namespace std;
//random
#include <time.h>
#include <stdlib.h>
//unicode
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <Windows.h>


//declaration------------------------------------------------------------------------------------------------
//utility 
bool asc(int a, int b);
bool desc(int a, int b);
void swap(int& a, int& b);
void sort(int** hand, bool(*compare)(int, int));
void sortNewHand(int** hand, bool(*compare)(int, int));
void swapPointer(int*& a, int*& b);
void printOneCard(int suit, int ranks, bool trash);
void pointsAllRounds(int* id, int n, int* winner);
int max4(int** hand);
int max3(int** hand);
int* maxRanks(int** hand, int point);
int* MaxRanks(int numbOfStatusOne, int** ranks,int **player);
int bestStatus(int*** players, int n);
bool isStraightOrFlush(int** hand);
bool isPairOrThree(int** hand, int i);


//required
void suffleCards(int Deck[][13]);
int isStraightFlush(int** hand);  //9
int isFourOfAKind(int** hand);    //8
int isFullHouse(int** hand);    //7
int isFlush(int** hand);//6
int isStraight(int** hand);//5
int isThreeOfAKind(int** hand);//4
int isTwoPairs(int** hand);//3
int isPair(int** hand);//2
int getHighestCard(int** hand);//1


void pickLuckCard(int** hand, int* &restDeck);
void pickSmartCard(int** hand, int* restDeck);
int** dealingForHand(int Deck[][13], int& x, int& y);
int*** dealingForHands(int deck[][13], int n,int *resdeck);
int getStatusOfHand(int** hand);
int* rankingHands(int*** hands, int n);
int *evaluateHands(int* points, int id);
int dealerPickToPlaceHard(int** dealer, int* tempCard);


void printRestDeck(int* rest);
void printAllCard(int Deck[][13]);


//defination---------------------------------------------------------------------------
//utility
bool asc(int a, int b) {
    return a > b;
}
bool desc(int a, int b) {
    return a < b;
}
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
void swapPointer(int*& a, int*& b) {
    int* temp = a;
    a = b;
    b = temp;
}
void sort(int** hand, bool(*compare)(int, int) = desc) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (compare(hand[i][1], hand[j][1])) {
                int* t = hand[i];
                hand[i] = hand[j];
                hand[j] = t;
            }
        }
    }
}
void sortNewHand(int** hand, bool(*compare)(int, int) = desc) {
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 6; j++) {
            if (compare(hand[i][1], hand[j][1])) {
                int* t = hand[i];
                hand[i] = hand[j];
                hand[j] = t;
            }
        }
    }
    // sort newhand
}
void printOneCard(int suit, int ranks, bool isYellow = 1)
{
    int color = 7;
    if (isYellow == 1)
        color = 6;
    SetConsoleCP(437);
    //_setmode(_fileno(stdout), _O_U16TEXT);
    switch (suit)
    {
    case 0:
        //text and bg color with form bg*16+text
        SetColor(color * 16);
        cout<<char(6);
        break;
    case 1:
        SetColor(color * 16);
        cout<<char(5);
        break;
    case 2:
        SetColor(color * 16 + 4);
        cout<<char(4);
        break;
    case 3:
        SetColor(color * 16 + 4);
        //set_color(0 << 10 | 0 << 4 | 4);
        cout<<char(3);
        break;
    }

    //default unicode
    //_setmode(_fileno(stdout), _O_TEXT);
    switch (ranks) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        printf("%d", ranks + 2);
        break;
    case 9:
        printf("J");
        break;
    case 10:
        printf("Q");
        break;
    case 11:
        printf("K");

        break;
    case 12:
        printf("A");
        break;
    }

    //default text color
    SetColor(7);
}
void pointsAllRounds(int* id, int n, int* winner) {
    int j = 0;
    while (id[j] > -1) {
        winner[id[j]]++;         // tinh diem cho tung tran
        j++;
    }
}
int max4(int** hand) {
    for (int i = 0; i < 4; i++) {
        if (hand[i][1] == hand[i+1][1]) {
            return hand[i][1];
        }
    }
    return 0;
}
int max3(int** hand) {
    for (int i = 0; i < 3; i++) {
        if ((hand[i][1] == hand[i + 1][1]) && (hand[i][1] == hand[i + 2][1])) return hand[i][1];
    }
    return 0;
}
int* maxRanks(int** hand, int point) {
    int** clone = new int* [5];
    for (int i = 0; i < 5; ++i) {
        clone[i] = new int[2];
        clone[i][0] = hand[i][0];
        clone[i][1] = hand[i][1];
    }
    sort(clone);

    int* ranksArray = new int[5];
    for (int i = 0; i < 5; i++) ranksArray[i] = 0;
    int d3 = 0;
    int d2 = 1;
    switch (point) {
    case 8:
        ranksArray[0] = max4(clone);
        return ranksArray;
    case 4:
    case 7:
        ranksArray[0] = max3(clone);
        return ranksArray;
    case 9:
    case 5:
    case 6:
    case 1:
        for (int i = 0; i < 5; i++) ranksArray[i] = clone[i][1];
    case 3:
        for (int i = 0; i < 4; i++) {
            if (clone[i][1] == clone[i + 1][i]) {
                ranksArray[d3] = clone[i][1];
                d3++;
                i++;
                if (i == 3) {
                    ranksArray[2] = clone[i + 1][1];
                    break;
                }
            }
            else {
                ranksArray[2] = clone[i][1];
            }
        }
        return ranksArray;
    case 2:
        for (int i = 0; i < 4; i++) {
            if (clone[i][1] != clone[i + 1][1]) {
                ranksArray[d2] = clone[i][1];
                d2++;
            }
            else {
                ranksArray[0] = clone[i][1];
                i++;
            }            
        }
        return ranksArray;
    }    
    return 0;
}
int* MaxRanks(int numbOfStatusOne, int** ranks, int**player)
{
    int tie=0;
    int* winner = new int[numbOfStatusOne];
    for (int i = 0; i < numbOfStatusOne; i++) winner[i] = -1;

    int* max = ranks[0];
    winner[0] = player[0][0];
    for (int i = 1; i < numbOfStatusOne; i++) {
        for (int j = 0; j < 5; j++) {           //K A J Q
            if (max[j] > ranks[i][j]) break;
            if (max[j] < ranks[i][j]) {
                tie = 0;
                max = ranks[i];
                winner[tie] = player[i][0];
                tie++;
                break;
            }
            if (j == 4) {
                winner[tie] = player[i][0];
                tie++;
            }
        }
    }
    return winner;
}
int bestStatus(int*** players,int n) {
    int maxStatus = getStatusOfHand(players[1]);
    for (int i = 2; i < n; ++i) {
        if (getStatusOfHand(players[i]) > maxStatus)
            maxStatus = getStatusOfHand(players[i]);
    }
    return maxStatus;
}
bool isStraightOrFlush(int** hand) {
    sort(hand, desc);
    bool Straight = 0;
    bool Flush = 0;
    if (isFlush(hand) == 6)
        Flush = 1;
    if (isStraight(hand) == 5)
        Straight = 1;
    sort(hand, asc);
    return Straight || Flush;
}
bool isPairOrThree(int** hand, int i) {
    bool isPairOrThree = 0;
    if ((hand[i][1] == hand[i + 1 == 5 ? 0 : i + 1][1]) || (hand[i][1] == hand[i - 1 < 0 ? 4 : i - 1][1]))
        isPairOrThree = 1;
    return isPairOrThree;
}



//required
void suffleCards(int Deck[][13])
{
    srand(time(0));

    //init
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 13; ++j)
            Deck[i][j] = i * 13 + j;
    }

    //suffle
    int x;
    for (int i = 0; i < 1000; ++i)
    {
        x = rand() % (52);
        int subRow = x / 13;
        int subCol = x % 13;
        swap(Deck[0][0], Deck[subRow][subCol]);
    }
}
int isStraightFlush(int** hand) {
    if (isStraight(hand) == 5 && isFlush(hand) == 6) return 9;
    return 0;
}
int isFourOfAKind(int** hand) {      // K K K K 8
    int d = 0;
    int bo4 = 0;
    for (int i = 0; i < 4; i++) {
        if (hand[i][1] == hand[i + 1][1]) d++;
        else d = 0;
        if (d == 3) return 8;
    }
    if (bo4 == 1) return 8;
    return 0;
}
int isFullHouse(int** hand) {
    int d = 0;
    int bo3 = 0, bo2 = 0;
    for (int i = 0; i < 4; i++) {
        if (hand[i][1] == hand[i + 1][1]) d++;
        else d = 0;
        if (d == 2) {
            bo3++;
            bo2--;
        }
        else if (d == 1) bo2++;

    }
    if (bo3 == 1 && bo2 == 1) return 7;
    return 0;
}
int isFlush(int** hand) {
    for (int i = 0; i < 4; i++) {
        if (hand[i][0] != hand[i + 1][0]) return 0;
    }
    return 6;
}
int isStraight(int** hand) {
    if (hand[0][1] == 12 && hand[4][1] == 0) {
        for (int i = 1; i < 4; i++) {
            if (hand[i][1] - 1 != hand[i + 1][1]) return 0;
        }
    }
    else {
        for (int i = 0; i < 4; i++) {
            if (hand[i][1] - 1 != hand[i + 1][1]) return 0;
        }
    }
    return 5;
}
int isThreeOfAKind(int** hand) {
    int d = 0;
    int bo3 = 0;
    for (int i = 0; i < 4; i++) {
        if (hand[i][1] == hand[i + 1][1]) d++;
        else d = 0;
        if (d == 2) bo3++;
    }
    if (bo3 == 1) return 4;
    return 0;
}
int isTwoPairs(int** hand) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (hand[i][1] == hand[i + 1][1]) {
            count++;
            i++;
        }
    }
    return count == 2 ? 3 : 0;
}
int isPair(int** hand) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (hand[i][1] == hand[i + 1][1]) {
            count++;
            i++;
        }
    }
    return count == 1 ? 2 : 0;
}
int getHighestCard(int** hand) {
    int rank[2];
    rank[0] = hand[0][0];
    rank[1] = hand[0][1];
    for (int i = 1; i < 5; ++i) {
        if (rank[1] < hand[i][1]) {
            rank[1] = hand[i][1];
            rank[0] = hand[i][0];
        }
    }
    return rank[0] * 13 + rank[1];
}
int** dealingForHand(int Deck[][13], int& x, int& y) {
    int** pPlayer = new  int* [5];
    for (int i = 0; i < 5; i++) pPlayer[i] = new int[2];

    for (int i = 0; i < 5; i++) {
        pPlayer[i][0] = Deck[x][y] / 13; //suit
        pPlayer[i][1] = Deck[x][y] % 13;   // rank
        y++;
        if (y == 13) {
            y = 0;
            x++;
        }
    }
    return pPlayer;
}
int*** dealingForHands(int Deck[][13], int n, int* restDeck) {
    int*** hands = new int** [n];
    int x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
        hands[i] = dealingForHand(Deck, x, y);
    }
    for (int i = 0; i < (52 - 5 * n); i++) {
        restDeck[i] = Deck[x][y];
        y++;
        if (y == 13) {
            y = 0;
            x++;
        }
    }
    return hands;
}
int getStatusOfHand(int** hand) {
    // rank
    int** clone = new int* [5];
    for (int i = 0; i < 5; ++i) {
        clone[i] = new int[2];
        clone[i][0] = hand[i][0];
        clone[i][1] = hand[i][1];
    }
    sort(clone);
    int max = isStraightFlush(clone);
    if (max == 0) max = isFourOfAKind(clone);
    if (max == 0) max = isFullHouse(clone);
    if (max == 0) max = isFlush(clone);
    if (max == 0) max = isStraight(clone);
    if (max == 0) max = isThreeOfAKind(clone);
    if (max == 0) max = isTwoPairs(clone);
    if (max == 0) max = isPair(clone);
    if (max == 0) max = 1;

    for (int i = 0; i < 5; ++i) {
        delete[]clone[i];
    }
    delete[]clone;
    return max;
}
int* rankingHands(int*** hands, int n) {
    int** players = new int* [n];        //new template players
    int** maxVal = new int*[n];           // max Ranks for each hand

    for (int i = 0; i < n; ++i) {
        players[i] = new int[2];
    }
    for (int i = 0; i < n; ++i) {
        players[i][0] = i;         //id of player
        players[i][1] = getStatusOfHand(hands[i]);        //point of this id
        maxVal[i] = maxRanks(hands[i],players[i][1]);
    }

    for (int i = 0; i < n - 1; ++i) {                            //arrange ascending player's points
        for (int j = i + 1; j < n; ++j) {
            if (players[i][1] < players[j][1]) {
                swapPointer(players[i], players[j]);
                swapPointer(maxVal[i], maxVal[j]);
            }
        }
    }

    int numbOfStatusOne = 1;
    for (int i = 1; i < n ; i++) {
        if (players[0][1]==players[i][1])   numbOfStatusOne++;         // count tie players
    }
    
    int* winner= MaxRanks(numbOfStatusOne, maxVal,players);
    for (int i = 0; i < n; ++i) {                                      //delete template players
        delete[] players[i];
        delete[] maxVal[i];
    }
    delete[] players;
    delete[] maxVal;
    return winner;
}
int *evaluateHands(int* points, int n) {
    int tie = 0;
    int iMax = 0;
    int *winner=new int[10];
    for (int i = 1; i < n; i++) {
        if (points[iMax] < points[i]) iMax = i;
    }
    for (int i = 0; i < n; i++) {
        if (points[i] == points[iMax]) {
            winner[tie] = i;
            tie++;
        }
    }

    if (points[iMax] == 0) {
        winner[0] = -1;
        return winner;
    }

    winner[tie] = -1;
    return winner;
}
int dealerPickToPlaceHard(int** dealer, int* tempCard) {
    sort(dealer, asc);
    int* duplicateTempCard = new int[2];
    duplicateTempCard[0] = tempCard[0];
    duplicateTempCard[1] = tempCard[1];
    int** duplicateDealer = new int* [5];
    for (int i = 0; i < 5; ++i) {
        duplicateDealer[i] = new int[2];
        duplicateDealer[i][0] = dealer[i][0];
        duplicateDealer[i][1] = dealer[i][1];
    }

    swapPointer(dealer[0], tempCard);
    int bestStatus = getStatusOfHand(dealer);
    int* maxValues = maxRanks(dealer, bestStatus);
    int curPos = 0;

    for (int i = 1; i < 5; ++i) {
        swapPointer(duplicateDealer[i], duplicateTempCard);
        int thisStatus = getStatusOfHand(duplicateDealer);
        int* thisMaxValues = maxRanks(duplicateDealer, thisStatus);
        if (thisStatus > bestStatus) {
            swapPointer(dealer[curPos], tempCard);
            swapPointer(dealer[i], tempCard);
            bestStatus = thisStatus;
            maxValues = thisMaxValues;
            curPos = i;
        }
        else if (thisStatus == bestStatus) {
            for (int j = 0; j < 5; ++j) {
                if (thisMaxValues[j] > maxValues[j]) {
                    swapPointer(dealer[curPos], tempCard);
                    swapPointer(dealer[i], tempCard);
                    bestStatus = thisStatus;
                    maxValues = thisMaxValues;
                    curPos = i;
                    break;
                }
                else if (thisMaxValues[j] < maxValues[j]) {
                    break;
                }
            }
        }
        swapPointer(duplicateDealer[i], duplicateTempCard);
    }
    for (int i = 0; i < 5; ++i) {
        delete[]duplicateDealer[i];
    }
    delete[]duplicateDealer;
    delete[]duplicateTempCard;
    swapPointer(dealer[curPos], tempCard);
    return curPos;
}





//testing
void printRestDeck(int* rest) {
    SetPosition(9, 20);
    int i = 0;
    while (rest[i] > -1) {
        printOneCard(rest[i] / 13, rest[i] % 13, 0);
        cout << " ";
        i++;
    }
}
void printAllCard(int Deck[][13]) {
    SetPosition(9, 23);
    cout << "----------------------------------------------------------";
    SetPosition(9, 24);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            printOneCard(Deck[i][j] / 13, Deck[i][j] % 13, 0);
            cout << " ";
        }
        SetPosition(9, 25+i);
    }
}
