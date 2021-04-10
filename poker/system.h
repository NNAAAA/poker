#pragma once

#include <iostream>
#include "windows.h"

//press from keyboard
#include <conio.h>

//defination
void SetColor(int text){
    HANDLE bg = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( bg , text );
}
void ShowCur(bool CursorVisibility){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    SetConsoleCursorInfo(handle, &ConCurInf);
}
void FullScreen(){  
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD NewSBSize = GetLargestConsoleWindowSize(out);  
    NewSBSize.Y += 3;  
    NewSBSize.X -= 2;  
    SMALL_RECT DisplayArea = { 0, 0, 0, 0 };  
    SetConsoleScreenBufferSize(out, NewSBSize);  
    DisplayArea.Right = NewSBSize.X - 1;  
    DisplayArea.Bottom = NewSBSize.Y - 1;  
    SetConsoleWindowInfo(out, TRUE, &DisplayArea);  
}  
void SetPosition(SHORT posX, SHORT posY){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
}




