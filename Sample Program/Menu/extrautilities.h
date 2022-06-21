#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
#include<conio.h>
#include<vector>
using namespace std;

void gotoRowCol(int rpos, int cpos);
void ResetConsoleFont();
void SetConsoleFont(int size);
void getRowColbyLeftClick(int& rpos, int& cpos);
void SetWindowsSize(int sr, int sc, int width, int height);
void SetWindowsSize(string S = "Default");
void GetDesktopResolution(int& horizontal, int& vertical);
void GetRowCol(int& rpos, int& cpos);
void ChangeColor(int k);
void ChangeColor(string color);
void PrintNTimes(char Sym, int N);
void Decapitalize(string& S);
void Capitalize(string& S);
void DisplayBox(int row, int column, int width, int height, char border, string border_color = "default", char fill = ' ', string fill_color = "Black");
void DisplayFancyBox(int row, int column, int width, int height, int style, string border_color = "default",char fill=' ',string fill_color="Black");
void RemoveBox(int row, int column, int width, int height,char back = ' ');
void DisplayBoxWithStr(int row, int column, int width, int height, char border, string Str,string str_color="default", string border_color = "default", char fill = ' ', string fill_color = "Black");
void DisplayBoxWithMultilineStr(int row, int column, int width, int height, char border, string Str, string str_color = "default", string border_color = "default", char fill = ' ', string fill_color = "Black", bool Text_In_Middle=true);
void DisplayFancyBoxWithStr(int row, int column, int width, int height, int style, string Str, string str_color = "default", string border_color = "default", char fill = ' ', string fill_color = "Black");
void DisplayFancyGrid(int start_row, int start_col, int Num_Boxes_vertical, int Num_Boxes_Horizontal, int Box_Size_Vertical, int Box_Size_Horizontal,
char border = '-', string border_color = "Default", char fill = ' ', string fill_color = "Black:Black");
bool IsEven(int N);
bool IsOdd(int N);
char to_char(int N);
int to_int(string S);
float to_float(string S);
float to_double(string S);
char to_character(int ascii);
void GetConsoleSize(int& r, int& c);
vector<string> split(string S, char c, int max_splits = -1);
vector<string> to_Multiline(string S, int line_width);
void printvectorstring(const vector<string>& S, bool end_line = false);
void ClearLastFromConsole();
int FindInStr(const string& S, char c);
int ReplaceCharInStr(string& S, char target, char replace);
void CopyToClipboard(string Data);
string GetClipboardData();
void OpenUrl(string S);