#include "extrautilities.h"
#define TL to_character(218)
#define TR to_character(191)
#define BL to_character(192)
#define BR to_character(217)
#define LT to_character(195)
#define RT to_character(180)
#define UT to_character(194)
#define DT to_character(193)
#define CROSS to_character(197)
#define V1 to_character(179)
#define H1 to_character(196)

#define TL2 to_character(201)
#define TR2 to_character(187)
#define BL2 to_character(200)
#define BR2 to_character(188)
#define LT2 to_character(204)
#define RT2 to_character(185)
#define UT2 to_character(203)
#define DT2 to_character(202)
#define CROSS2 to_character(206)
#define V2 to_character(186)
#define H2 to_character(205)

void gotoRowCol(int rpos, int cpos)
{
	if (rpos < 0) rpos = 0;
	if (cpos < 0) cpos = 0;
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}   
void GetRowCol(int& rpos, int& cpos)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
	{
		COORD P = cbsi.dwCursorPosition;
		rpos = P.Y;
		cpos = P.X;
	}
	else
	{
		rpos = -1;
		cpos = -1;
	}
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void ResetConsoleFont()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   
	cfi.dwFontSize.Y = 24;                  
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void SetConsoleFont(int size)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = size;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void SetWindowsSize(int sr, int sc, int width, int height)
{
	HWND console = GetConsoleWindow();
	MoveWindow(console, sr, sc, width, height, TRUE);
}
void SetWindowsSize(string S)
{
	Decapitalize(S);
	if (S == "full screen" || S == "fullscreen")
	{
		int w, h;
		GetDesktopResolution(w, h);
		SetWindowsSize(0, 0, w ,  9*h/10);
	}
	else
	{
		int w, h;
		GetDesktopResolution(w, h);
		SetWindowsSize(0, 0, w / 1.35, (2.75 * h) / 3);
	}
}
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
void ChangeColor(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	if (k > 255)
		k = 1;
}
int GetColorId(string color)
{
	Decapitalize(color);
	if (FindInStr(color, ':') == -1)
	{
		int temp = 15;
		if (color == "black" || color == "null")
		{
			temp = 0;
		}
		if (color == "blue" || color == "aqua")
		{
			temp = 1;
		}
		if (color == "darkgreen" || color == "grass")
		{
			temp = 2;
		}
		if (color == "sky" || color == "lightblue")
		{
			temp = 3;
		}
		if (color == "red" || color=="darkred" || color == "blood")
		{
			temp = 4;
		}
		if (color == "purple"  || color == "magenta")
		{
			temp = 5;
		}
		if (color == "yellow" || color == "darkyellow" || color == "orange")
		{
			temp = 6;
		}
		if (color == "offwhite" || color == "lightwhite")
		{
			temp = 7;
		}
		if (color == "gray" || color == "grey" || color=="darkwhite")
		{
			temp = 8;
		}
		if (color == "navy" || color == "midblue")
		{
			temp = 9;
		}
		if (color == "green" || color == "lightgreen")
		{
			temp = 10;
		}
		if (color == "cyan")
		{
			temp = 11;
		}
		if (color == "lightred" || color == "brightred")
		{
			temp = 12;
		}
		if (color == "pink" || color == "pinky")
		{
			temp = 13;
		}
		if (color == "lightyellow" || color == "sunny" || color == "sun")
		{
			temp = 14;
		}
		if (color == "white" || color == "default")
		{
			temp = 15;
		}
		return temp;
	}
	vector<string> S = split(color, ':', 2);
	int foreground = GetColorId(S[0]);
	string temp = S[1];
	ReplaceCharInStr(temp, ':', ' ');
	int background = GetColorId(temp);
	return background * 16 + foreground;
}
void ChangeColor(string color)
{
	Decapitalize(color);
	ChangeColor(GetColorId(color));
}
void PrintNTimes(char Sym, int N)
{
	for (int i = 1; i <= N; i++)
	{
		cout << Sym;
	}
}
void PrintNTimesVertical(char Sym, int N, int r, int c)
{
	for (int i = 0; i < N; i++)
	{
		gotoRowCol(r + i, c);
		cout << Sym;
	}
}
void Decapitalize(string& S)
{
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i] >= 'A' && S[i] <= 'Z')
		{
			S[i] += 32;
		}
	}
}
void Capitalize(string& S)
{
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i] >= 'a' && S[i] <= 'z')
		{
			S[i] -= 32;
		}
	}
}
void DisplayFancyBox(int row, int column, int width, int height, int style, string border_color, char fill, string fill_color)
{
	ChangeColor(border_color);
	if (style == 1)
	{
		gotoRowCol(row, column);
		cout << to_character(201);
		gotoRowCol(row, column + width - 1);
		cout << to_character(187);
		gotoRowCol(row + height - 1, column);
		cout << to_character(200);
		gotoRowCol(row + height - 1, column + width - 1);
		cout << to_character(188);
		if (width > 2)
		{
			gotoRowCol(row, column + 1);
			PrintNTimes(to_character(205), width - 2);
			gotoRowCol(row + height - 1, column + 1);
			PrintNTimes(to_character(205), width - 2);
		}
		if (height > 2)
		{
			PrintNTimesVertical(to_character(186), height - 2, row + 1, column);
			PrintNTimesVertical(to_character(186), height - 2, row + 1, column + width - 1);
		}
	}
	else if (style == 0)
	{
		gotoRowCol(row, column);
		cout << to_character(218);
		gotoRowCol(row, column + width - 1);
		cout << to_character(191);
		gotoRowCol(row + height - 1, column);
		cout << to_character(192);
		gotoRowCol(row + height - 1, column + width - 1);
		cout << to_character(217);
		if (width > 2)
		{
			gotoRowCol(row, column + 1);
			PrintNTimes(to_character(196), width - 2);
			gotoRowCol(row + height - 1, column + 1);
			PrintNTimes(to_character(196), width - 2);
		}
		if (height > 2)
		{
			PrintNTimesVertical(to_character(179), height - 2, row + 1, column);
			PrintNTimesVertical(to_character(179), height - 2, row + 1, column + width - 1);
		}


	}
	if (!(fill == ' ' && fill_color == "Black"))
	{
		ChangeColor(fill_color);
		for (int i = 1; i < height - 1; i++)
		{
			gotoRowCol(row + i, column + 1);
			PrintNTimes(fill,width-2);
		}
	}
	ChangeColor("Default");
}
void DisplayBox(int row, int column, int width, int height, char border, string border_color, char fill, string fill_color)
{
	if (border == '-' || border == '=')
	{
		if (border == '-')
		{
			DisplayFancyBox(row, column, width, height, 0, border_color, fill, fill_color);
		}
		else if (border == '=')
		{
			DisplayFancyBox(row, column, width, height, 1, border_color, fill, fill_color);
		}
	}
	else
	{
		ChangeColor(border_color);
		gotoRowCol(row, column);
		PrintNTimes(border, width);
		gotoRowCol(row + height - 1, column);
		PrintNTimes(border, width);
		PrintNTimesVertical(border, height, row, column);
		PrintNTimesVertical(border, height, row, column + width - 1);
	}
	if (!(fill == ' ' && fill_color == "Black"))
	{
		ChangeColor(fill_color);
		for (int i = 1; i < height - 1; i++)
		{
			gotoRowCol(row + i, column + 1);
			PrintNTimes(fill, width - 2);
		}
	}
	ChangeColor("Default");
}
void RemoveBox(int row, int column, int width, int height, char back)
{
	for (int i = 0; i < height; i++)
	{
		gotoRowCol(row + i, column);
		PrintNTimes(back, width);
	}
}
void DisplayBoxWithStr(int row, int column, int width, int height, char border, string Str,string str_color, string border_color, char fill, string fill_color)
{
	DisplayBox(row, column, width, height, border, border_color, fill, fill_color);
	ChangeColor(str_color);
	if (Str.length() <= width - 2)
	{
		gotoRowCol(row + (height / 2), column + (width-Str.length())/2);
		cout << Str;
	}
	ChangeColor("Default");
}
void DisplayFancyBoxWithStr(int row, int column, int width, int height, int type, string Str, string str_color, string border_color, char fill, string fill_color)
{
	DisplayFancyBox(row, column, width, height, type, border_color,fill,fill_color);
	ChangeColor(str_color);
	if (Str.length() <= width - 2)
	{
		gotoRowCol(row + (height / 2), column + (width - Str.length()) / 2);
		cout << Str;
	}
	ChangeColor("Default");
}
void DisplayBoxWithMultilineStr(int row, int column, int width, int height, char border, string Str, string str_color, string border_color, char fill, string fill_color, bool Text_In_Middle)
{
	vector<string> ML = to_Multiline(Str, width - 2);
	if (ML.size() == 0 || ML.size()>height-2) return;
	DisplayBox(row, column, width, height, border, border_color, fill, fill_color);
	int start_r, start_c;
	if (Text_In_Middle)
		start_r = row + 1 + ((height - 2) - ML.size()) / 2;
	else
		start_r = row + 1;
	start_c = column+1;

	for (int i = 0; i < ML.size(); i++)
	{
		gotoRowCol(start_r + i, start_c);
		ChangeColor(str_color);
		cout << ML[i];
		ChangeColor("default");
	}
}
void DisplayFancyGrid(int start_row, int start_col, int Num_Boxes_vertical, int Num_Boxes_Horizontal, int Box_Size_Vertical, int Box_Size_Horizontal,char border, string border_color, char fill, string fill_color)
{
	for (int r = 0; r < Num_Boxes_vertical; r++)
	{
		for (int c = 0; c < Num_Boxes_Horizontal; c++)
		{
			DisplayBox(start_row + Box_Size_Vertical * r - r, start_col + Box_Size_Horizontal * c - c, Box_Size_Horizontal, Box_Size_Vertical, border, border_color, fill, fill_color);
		}
	}
	if (border == '-' || border == '=')
	{
		ChangeColor(border_color);
		for (int r = 1; r < Num_Boxes_vertical; r++)
		{
			for (int c = 1; c < Num_Boxes_Horizontal; c++)
			{
				gotoRowCol(start_row + Box_Size_Vertical * r - r, start_col + Box_Size_Horizontal * c - c);
				if (border == '-')
					cout << CROSS;
				else
					cout << CROSS2;
			}
		}
		for (int r = 1; r < Num_Boxes_vertical; r++)
		{
			gotoRowCol(start_row + Box_Size_Vertical * r - r, start_col);
			if (border == '-')
				cout << LT;
			else
				cout << LT2;
			gotoRowCol(start_row + Box_Size_Vertical * r - r, start_col + (Box_Size_Horizontal - 1) * Num_Boxes_Horizontal);
			if (border == '-')
				cout << RT;
			else
				cout << RT2;
		}
		for (int c = 1; c < Num_Boxes_Horizontal; c++)
		{
			gotoRowCol(start_row, start_col + Box_Size_Horizontal * c - c);
			if (border == '-')
				cout << UT;
			else
				cout << UT2;
			gotoRowCol(start_row + (Box_Size_Vertical - 1) * Num_Boxes_vertical, start_col + Box_Size_Horizontal * c - c);
			if (border == '-')
				cout << DT;
			else
				cout << DT2;
		}
		ChangeColor("Default");
	}
	
	
}
bool IsEven(int N)
{
	if (N % 2 == 0) return true;
	return false;
}
bool IsOdd(int N)
{
	if (N % 2 != 0) return true;
	return false;
}
char to_char(int N)
{
	if (N >= 0 && N <= 9) return char(48 + N);
	else return '0';
}
int to_int(string S)
{
	return stoi(S);
}
float to_float(string S)
{
	return stof(S);
}
float to_double(string S)
{
	return stod(S);
}
char to_character(int ascii)
{
	char c = ascii;
	return c;
}
void GetConsoleSize(int& r, int& c)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	c = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	r = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
vector<string> split(string S, char c,int max_splits)
{
	int splits = 0;
	vector<string> split;
	vector<int> index;
	if (S.size() == 0) return split;
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i] == c)
		{
			index.push_back(i);
			splits++;
		}
		if (max_splits != -1 && splits == max_splits) break;
	}
	if (index.size() == 0)
	{
		split.push_back(S);
		return split;
	}
	if (index[0] != 0)
	{
		split.push_back(S.substr(0, index[0]));
	}
	for (int i = 0; i < index.size() - 1; i++)
	{
		if (index[i + 1] - index[i] > 1)
		{
			split.push_back(S.substr(index[i] + 1, index[i + 1] - index[i] - 1));
		}
	}
	if (S.size() - index[index.size() - 1] > 0)
	{
		split.push_back(S.substr(index[index.size() - 1] + 1, S.size() - index[index.size() - 1]));
	}
	return split;
}
vector<string> to_Multiline(string S, int line_width)
{
	vector<string> M;
	string temp;
	vector<string> Splited = split(S, ' ');
	for (int i = 0; i < Splited.size(); i++)
	{
		if (Splited[i].size() > line_width) 
			return M;
	}
	int x = 0;
	for (int i = 0; i < Splited.size(); i++)
	{
		if (temp.size() + Splited[i].size() > line_width)
		{
			M.push_back(temp);
			temp.clear();
			i--;
		}
		else
		{
			temp=temp+Splited[i];
			if (temp.size() != line_width) temp.push_back(' ');
		}
	}
	if(temp.size()!=0)
		M.push_back(temp);
	return M;
}
void printvectorstring(const vector<string>& S, bool end_line)
{
	for (int i = 0; i < S.size(); i++)
	{
		cout << S[i] << " ";
		if (end_line) cout << endl;
	}
}
void ClearLastFromConsole()
{
	int r, c;
	GetRowCol(r, c);
	if (c != 0)
	{
		gotoRowCol(r, c - 1);
		cout << " ";
		gotoRowCol(r, c - 1);
	}
}
int FindInStr(const string& S, char c)
{
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i] == c) return i;
	}
	return -1;
}
int ReplaceCharInStr(string& S, char target, char replace)
{
	int count = 0;
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i] == target)
		{
			S[i] = replace;
			count++;
		}
	}
	return count;
}
void CopyToClipboard(string Data)
{
	Data.push_back(' ');
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, Data.size());
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), Data.c_str(), Data.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}
string GetClipboardData()
{
	// Try opening the clipboard
	if (!OpenClipboard(nullptr)) return "";

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr) return "";

	// Lock the handle to get the actual text pointer
	char* pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText == nullptr) return "";

	// Save text in a string class instance
	string text(pszText);

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	return text;
}
void OpenUrl(string S)
{
	wstring B(S.begin(), S.end());
	LPCWSTR A = B.c_str();
	ShellExecute(0, 0, A, 0, 0, SW_SHOW);
}