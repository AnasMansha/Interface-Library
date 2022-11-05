#pragma once
#include "Interface.h"



//interface class functions
void Tutorial()
{
	StartTutorial();
}
void StartTutorial()
{
	MainScreen();
}
void MainScreen()
{
	SetConsoleFont(40);
	SetWindowsSize("Fullscreen");

	menu M("Sample Code", "Code Generator", "Exit");
	M.SetOptionsPerLine(3);
	M.SetInlineGap(3);
	M.SetTitle("Main Menu");
	M.SetBoxWidth(20);
	int choice = M.Input();
	if (choice == 1)
	{
		SampleCodeScreen();
	}
	else if (choice == 2) CodeGeneratorScreen();
	else return;
}
void SampleCodeScreen()
{
	OpenUrl("https://docs.google.com/document/d/1DWvvn184y5YOITT1eSQhzdkjXL8K0U-ygvi3784Ujmw/edit?usp=sharing");
	return;
}
void CodeGeneratorScreen()
{
	menu M("Menu", "Form", "Back");
	M.SetTitle("Code Generator");
	M.SetOptionsPerLine(3);
	M.SetInlineGap(3);
	M.SetBoxWidth(20);
	int choice = M.Input();
	if (choice == 1) NumOfInputSelector("Menu");
	else if (choice == 2)  NumOfInputSelector("Form");
	else MainScreen();
}
void NumOfInputSelector(string source)
{
	menu M("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12");
	M.SetOptionsPerLine(3);
	M.SetInlineGap(3);
	M.SetLocation(0, 20);
	M.SetTitle("Number of Inputs");
	if (source == "Menu")
		MenuOptionsSelector(M.Input());
	else
		FormOptionsSelector(M.Input());
}
void MenuOptionsSelector(int inputs) 
{
	SetConsoleFont(30 - 1.28 * inputs);
	SetWindowsSize("Fullscreen");

	form F;
	F.SetTitle("Menu Generator");
	vector<string> S;
	S.resize(12, " ");
	string input_no;
	for (int i = 0; i < inputs; i++)
	{
		if (i < 9) input_no = ('1' + i);
		else input_no = "1" + ('1' + (i - 9));
		S[i] = "str:Enter Option " + input_no;
	}
	F.set(S[0], S[1], S[2], S[3], S[4], S[5], S[6], S[7], S[8], S[9], S[10], S[11]);
	F.SetSubmitText("Next");
	vector<string> Output=F.Input();
	string Generator = "menu M(";
	string Save = "menu M(";
	for (int i = 0; i < inputs; i++)
	{
		if (i != inputs - 1)
		{
			Generator = Generator + "\"" + Output[i] + "\", ";
			Save = Save + "\"" + Output[i] + "\", ";
		}
		
		else
		{
			Generator = Generator + "\"" + Output[i] + "\"); ";
			Save = Save + "\"" + Output[i] + "\");\n";
		}
	}
	TitleSelector(Generator,Save,"Menu");
	//DisplayBoxWithMultilineStr(0, 0, 40, 10, '-', Generator,"default","default",' ',"Black",false);
}
void FormOptionsSelector(int inputs) 
{
	SetConsoleFont(30 - 2.56 * inputs);
	SetWindowsSize("Fullscreen");

	form F;
	F.SetTitle("Menu Generator");
	vector<string> S;
	S.resize(24, " ");
	string input_no;

	int x = 0;
	for (int i = 0; i < inputs; i++)
	{
		if (i < 9) input_no = ('1' + i);
		else input_no = "1" + ('1' + (i - 9));
		S[x] = "str:Enter Option " + input_no;
		S[x + 1] = "mcqs:Data type:string,int,bool,date,password";
		x += 2;
	}
	F.set(S[0], S[1], S[2], S[3], S[4], S[5], S[6], S[7], S[8], S[9], S[10], S[11]);
	F.SetSubmitText("Next");
	vector<string> Output = F.Input();
	string Generator = "form F(";
	string Save = "form F(";
	
	x = 0;
	for (int i = 0; i < inputs; i++)
	{
		if (i != inputs - 1)
		{
			Generator = Generator + "\"" + Output[x+1] +":"+Output[x]+ "\", ";
			Save = Save + "\"" + Output[x + 1] + ":" + Output[x] + "\", ";
		}
		else
		{
			Generator = Generator + "\"" + Output[x + 1] + ":" + Output[x] + "\"); ";
			Save = Save + "\"" + Output[x + 1] + ":" + Output[x] + "\");\n";
		}
		x += 2;
	}
	TitleSelector(Generator, Save, "Form");
}
void TitleSelector(string options, string c_options, string source)
{
	form F;
	F.SetTitle("Title Selector");
	F.set("str:Title", "str:Title Color");
	F.SetSubmitText("Generate");
	vector<string> S=F.Input();
	if (source == "Menu")
	{
		options = options + " M.SetTitle(\"" + S[0] + "\", \"" + S[1] + "\");";
		c_options = c_options + " M.SetTitle(\"" + S[0] + "\", \"" + S[1] + "\");\n";
		options = options + " M.Input();";
		c_options = c_options + " M.Input();";
	}
	else
	{
		options = options + " F.SetTitle(\"" + S[0] + "\", \"" + S[1] + "\");";
		c_options = c_options + " F.SetTitle(\"" + S[0] + "\", \"" + S[1] + "\");\n";
		options = options + " F.Input();";
		c_options = c_options + " F.Input();";
	}
	ShowGeneratedCode(options,c_options,source);
}
void ShowGeneratedCode(string options, string c_options, string source)
{
	screen S;
	text T;
	if (source == "Menu")
	{
		T.Set("Menu generated through Code Generator", 0, 0, "YELLOW", 2,"YELLOW");
	}
	else
	{
		T.Set("Form generated through Code Generator", 0, 0, "YELLOW", 2, "YELLOW");
	}
	S.AddText(T);
	box B("Main Code", 3, 0, 40, 8, '-', "cyan", options, "white");
	B.multiline = true;
	S.AddBox(B);//19
	button CB(0, "Copy Code", 10, 21, 19, 3, '-', "cyan", "Copy to clipboard","red");
	button MM(1, "Main Menu", 12, 0, 16, 3, '-', "blue", "Main Menu","orange");
	button EX(2, "Exit", 15, 0, 16, 3, '-', "blue", "Exit","orange");


	//button AG(1,"Generate Another")
	S.AddClickBox(CB);
	S.AddClickBox(MM);
	S.AddClickBox(EX);

	S.Display();

	ChangeColor("cyan");
	gotoRowCol(10, 21);
	cout << to_character(194);
	gotoRowCol(10, 39);
	cout << to_character(180);
	gotoRowCol(14, 0);
	ChangeColor("default");

	int id = S.GetClickBoxId();
	if (id == 0)
	{
		CopyToClipboard(c_options);
		S.RemoveClickBox("Copy Code");
		box NB("Code Copied", 10, 21, 19, 3, '-', "cyan", "Code Copied!", "green");
		S.AddBox(NB);
		S.Remove();
		S.Display();
		ChangeColor("cyan");
		gotoRowCol(10, 21);
		cout << to_character(194);
		gotoRowCol(10, 39);
		cout << to_character(180);
		gotoRowCol(14, 0);
		ChangeColor("default");
		id = S.GetClickBoxId();
		S.Remove();
		if (id == 1) MainScreen();
		else return;
	}
	else if (id == 1)
	{
		S.Remove();
		MainScreen();
	}
	else
	{
		S.Remove();
		return;
	}
}

//extrautilities functions
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
		SetWindowsSize(0, 0, w, 9 * h / 10);
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
		if (color == "red" || color == "darkred" || color == "blood")
		{
			temp = 4;
		}
		if (color == "purple" || color == "magenta")
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
		if (color == "gray" || color == "grey" || color == "darkwhite")
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
	if (color[0] == ':')
	{
		color.erase(color.begin());
	}
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
			PrintNTimes(fill, width - 2);
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
void DisplayBoxWithStr(int row, int column, int width, int height, char border, string Str, string str_color, string border_color, char fill, string fill_color, bool ColorString)
{
	DisplayBox(row, column, width, height, border, border_color, fill, fill_color);
	ChangeColor(str_color);
	if (Str.length() <= width - 2)
	{
		gotoRowCol(row + (height / 2), column + (width - Str.length()) / 2);
		if (ColorString) DisplayColorString(Str);
		else cout << Str;
	}
	ChangeColor("Default");
}
void DisplayFancyBoxWithStr(int row, int column, int width, int height, int type, string Str, string str_color, string border_color, char fill, string fill_color, bool ColorString)
{
	DisplayFancyBox(row, column, width, height, type, border_color, fill, fill_color);
	ChangeColor(str_color);
	if (Str.length() <= width - 2)
	{
		gotoRowCol(row + (height / 2), column + (width - Str.length()) / 2);
		if (ColorString) DisplayColorString(Str);
		else cout << Str;
	}
	ChangeColor("Default");
}
int DisplayBoxWithMultilineStr(int row, int column, int width, int height, char border, string Str, string str_color, string border_color, char fill, string fill_color, bool Text_In_Middle, bool ColorString)
{
	vector<string> Div = split(Str, '\n');
	vector<string> ML;
	for (int i = 0; i < Div.size(); i++)
	{
		vector<string> temp= to_Multiline(Div[i], width - 2);
		for (int j = 0; j < temp.size(); j++)
		{
			ML.push_back(temp[j]);
		}   	
	}

	if (ML.size() == 0 || (height!=-1 && ML.size() > height - 2)) return -2;
	if (height == -1) height = ML.size() + 2;
	DisplayBox(row, column, width, height, border, border_color, fill, fill_color);
	int start_r, start_c;
	if (Text_In_Middle)
		start_r = row + 1 + ((height - 2) - ML.size()) / 2;
	else
		start_r = row + 1;
	start_c = column + 1;

	for (int i = 0; i < ML.size(); i++)
	{
		gotoRowCol(start_r + i, start_c);
		ChangeColor(str_color);
		if (ColorString) DisplayColorString(ML[i]);
		else cout << ML[i];
		ChangeColor("default");
	}
	return height;
}
void DisplayFancyGrid(int start_row, int start_col, int Num_Boxes_vertical, int Num_Boxes_Horizontal, int Box_Size_Vertical, int Box_Size_Horizontal, char border, string border_color, char fill, string fill_color)
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
void DisplayFancyGrid(int start_row, int start_col, int Num_Boxes_vertical, int Num_Boxes_Horizontal, vector<int> Box_Size_Vertical, vector<int> Box_Size_Horizontal, char border, string border_color, char fill, string fill_color)
{
	int CBSV = 0;
	int CBSH = 0;
	for (int r = 0; r < Num_Boxes_vertical; r++)
	{
		CBSH = 0;
		for (int c = 0; c < Num_Boxes_Horizontal; c++)
		{
			DisplayBox(start_row + CBSV, start_col + CBSH, Box_Size_Horizontal[c], Box_Size_Vertical[r], border, border_color, fill, fill_color);
			CBSH += Box_Size_Horizontal[c]-1;
		}
		CBSV += Box_Size_Vertical[r]-1;
	}
	if (border == '-' || border == '=')
	{
		CBSV = Box_Size_Vertical[0];
		ChangeColor(border_color);
		for (int r = 1; r < Num_Boxes_vertical; r++)
		{
			CBSH = Box_Size_Horizontal[0];
			for (int c = 1; c < Num_Boxes_Horizontal; c++)
			{
				gotoRowCol(start_row + CBSV-1, start_col + CBSH-1);
				if (border == '-')
					cout << CROSS;
				else
					cout << CROSS2;
				CBSH += Box_Size_Horizontal[c] - 1;
			}
			CBSV += Box_Size_Vertical[r] - 1;
		}
		CBSV = Box_Size_Vertical[0];
		for (int r = 1; r < Num_Boxes_vertical; r++)
		{
			gotoRowCol(start_row + CBSV - 1, start_col);
			if (border == '-')
				cout << LT;
			else
				cout << LT2;
			gotoRowCol(start_row + CBSV - 1, start_col + CBSH - 1);
			if (border == '-')
				cout << RT;
			else
				cout << RT2;
			CBSV += Box_Size_Vertical[r] - 1;
		}
		CBSH = Box_Size_Horizontal[0];
		for (int c = 1; c < Num_Boxes_Horizontal; c++)
		{
			gotoRowCol(start_row,start_col+ CBSH-1);
			if (border == '-')
				cout << UT;
			else
				cout << UT2;
			gotoRowCol(start_row + CBSV-1, start_col + CBSH-1);
			if (border == '-')
				cout << DT;
			else
				cout << DT2;
			CBSH += Box_Size_Horizontal[c] - 1;
		}
		ChangeColor("Default");
	}


}
void DisplayFancyGridWithStr(int start_row, int start_col, int Num_Boxes_vertical, int Num_Boxes_Horizontal, vector<int> Box_Size_Vertical, vector<int> Box_Size_Horizontal, vector<vector<string>> S, string string_color,
	char border, string border_color, char fill, string fill_color, bool ColorString)
{
	int CBSV = 0;
	int CBSH = 0;
	for (int r = 0; r < Num_Boxes_vertical; r++)
	{
		CBSH = 0;
		for (int c = 0; c < Num_Boxes_Horizontal; c++)
		{
			DisplayBoxWithStr(start_row + CBSV, start_col + CBSH, Box_Size_Horizontal[c], Box_Size_Vertical[r],border, S[r][c],string_color,border_color, fill, fill_color, ColorString);
			CBSH += Box_Size_Horizontal[c] - 1;
		}
		CBSV += Box_Size_Vertical[r] - 1;
	}
	if (border == '-' || border == '=')
	{
		CBSV = Box_Size_Vertical[0];
		ChangeColor(border_color);
		for (int r = 1; r < Num_Boxes_vertical; r++)
		{
			CBSH = Box_Size_Horizontal[0];
			for (int c = 1; c < Num_Boxes_Horizontal; c++)
			{
				gotoRowCol(start_row + CBSV - 1, start_col + CBSH - 1);
				if (border == '-')
					cout << CROSS;
				else
					cout << CROSS2;
				CBSH += Box_Size_Horizontal[c] - 1;
			}
			CBSV += Box_Size_Vertical[r] - 1;
		}
		CBSV = Box_Size_Vertical[0];
		for (int r = 1; r < Num_Boxes_vertical; r++)
		{
			gotoRowCol(start_row + CBSV - 1, start_col);
			if (border == '-')
				cout << LT;
			else
				cout << LT2;
			gotoRowCol(start_row + CBSV - 1, start_col + CBSH - 1);
			if (border == '-')
				cout << RT;
			else
				cout << RT2;
			CBSV += Box_Size_Vertical[r] - 1;
		}
		CBSH = Box_Size_Horizontal[0];
		for (int c = 1; c < Num_Boxes_Horizontal; c++)
		{
			gotoRowCol(start_row,start_col+ CBSH - 1);
			if (border == '-')
				cout << UT;
			else
				cout << UT2;
			gotoRowCol(start_row + CBSV - 1, start_col + CBSH - 1);
			if (border == '-')
				cout << DT;
			else
				cout << DT2;
			CBSH += Box_Size_Horizontal[c] - 1;
		}
		ChangeColor("Default");
	}
}
void DisplayFancyGridWithStr(int start_row, int start_col, int Num_Boxes_vertical, int Num_Boxes_Horizontal, int Box_Size_Vertical, int Box_Size_Horizontal, vector<vector<string>> S,
	string string_color, char border, string border_color, char fill, string fill_color, bool ColorString)
{
	for (int r = 0; r < Num_Boxes_vertical; r++)
	{
		for (int c = 0; c < Num_Boxes_Horizontal; c++)
		{
			DisplayBoxWithStr(start_row + Box_Size_Vertical * r - r, start_col + Box_Size_Horizontal * c - c, Box_Size_Horizontal, Box_Size_Vertical, border, S[r][c], string_color, border_color, fill, fill_color, ColorString);
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

void ProcessAction(string action, char current, string& current_color);
void DisplayColorString(string S);

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
vector<string> split(string S, char c, int max_splits)
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
vector<string> split(string S, string c, int max_splits)
{
	int splits = 0;
	vector<string> split;
	vector<int> index;
	if (S.size() == 0) return split;
	for (int i = 0; i < S.size(); i++)
	{
		for (int j = 0;j < c.size();j++)
		{
			if (S[i] == c[j])
			{
				index.push_back(i);
				splits++;
				break;
			}
			if (max_splits != -1 && splits == max_splits) break;
		}
		
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
			temp = temp + Splited[i];
			if (temp.size() != line_width) temp.push_back(' ');
		}
	}
	if (temp.size() != 0)
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
int length(int i)
{
	int length = 0;
	if (i < 0)
	{
		i *= -1;
		length++;
	}
	while (i != 0)
	{
		i = i / 10;
		length++;
	}
	return length;
}

void ProcessAction(string action, char current, string& current_color)
{
	if (action == "exec_color+clr_color")
	{
		ChangeColor(current_color);
		current_color.clear();
	}
	else if (action == "read_color")
	{
		current_color.push_back(current);
	}
	else if (action == "display") cout << current;
	else if (action == "display+display[") cout << "[" << current;
}
void DisplayColorString(string S)
{
	color C;
	string action;
	string current_color = "";
	node SS;
	node* S1;
	S1 = SS.GenerateColorChangeDfa();
	for (int i = 0;i < S.size();i++)
	{
		S1 = S1->Next(S[i], action);
		ProcessAction(action, S[i], current_color);
	}
	ChangeColor("Default");
	S1->clear();
}

