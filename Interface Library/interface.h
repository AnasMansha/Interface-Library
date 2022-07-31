#include<Windows.h>
#include<iostream>
#include<string>
#include<conio.h>
#include<vector>
using namespace std;

#define DEFAULT "Default"

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



//Interface library functions
void Tutorial();
void StartTutorial();
void MainScreen();
void SampleCodeScreen();
void CodeGeneratorScreen();
void NumOfInputSelector(string source);
void MenuOptionsSelector(int inputs);
void TitleSelector(string options, string c_options,string source);
void FormOptionsSelector(int inputs);
void ShowGeneratedCode(string options, string c_options, string source);

//extrautilities functions
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
void DisplayFancyBox(int row, int column, int width, int height, int style, string border_color = "default", char fill = ' ', string fill_color = "Black");
void RemoveBox(int row, int column, int width, int height, char back = ' ');
void DisplayBoxWithStr(int row, int column, int width, int height, char border, string Str, string str_color = "default", string border_color = "default", char fill = ' ', string fill_color = "Black");
void DisplayBoxWithMultilineStr(int row, int column, int width, int height, char border, string Str, string str_color = "default", string border_color = "default", char fill = ' ', string fill_color = "Black", bool Text_In_Middle = true);
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

class menu
{
private:
	vector<pair<pair<int, int>, pair<int, int>>> boxes;
	bool temp_menu;
	menu(int N)
	{
		if (N == 0)
			temp_menu = true;
		else temp_menu = false;
	}
protected:
	vector<string> options;
	vector<menu*> sub_menus;
	int display_type;
	int input_type;
	int max_display_types;
	int max_input_types;
	bool display_override;
	char border_char;
	int options_per_line;
	int inline_gap;
	int box_width;
	string title;
	string title_color;
	string text_color;
	string box_color;

	pair<int, int> mouse_input_start_point;
	void Init()
	{
		display_override = false;
		display_type = 1;
		input_type = 3;
		max_display_types = 2;
		max_input_types = 3;
		mouse_input_start_point.first = 0;
		mouse_input_start_point.second = 0;
		border_char = '=';
		temp_menu = false;
		options_per_line = 1;
		inline_gap = 10;
		box_width = -1;
		title = "None";
		title_color = "Yellow";
		text_color = "Green";
		box_color = "White";
	}
	void Display(bool cls = true)
	{
		if (display_override)
		{
			DisplayX(true);
			return;
		}
		if (cls)
			system("cls");
		switch (display_type)
		{
		case 1:
			DisplayA();
			break;
		case 2:
			DisplayB();
			break;
		}
		gotoRowCol(0, 0);
	}
	void DisplayA()
	{
		for (int i = 0; i < options.size(); i++)
		{
			cout << i + 1 << ": " << options[i] << endl;
		}
	}
	void DisplayB()
	{
		for (int i = 0; i < options.size(); i++)
		{
			cout << char('A' + i) << ": " << options[i] << endl;
		}
	}
	void DisplayX(bool input_in_progress = false)
	{
		if (input_in_progress)
			boxes.clear();

		int row = mouse_input_start_point.first;
		int column = mouse_input_start_point.second;
		int width;
		if (box_width == -1 || box_width < MaxOptionSize() + 4)
			width = MaxOptionSize() + 4;
		else
			width = box_width;
		//Title Display
		if (title != "None")
		{
			int total_width = (width * options_per_line) + (inline_gap * (options_per_line - 1));
			gotoRowCol(row, max(column, column + (total_width - title.length()) / 2));
			ChangeColor(title_color);
			cout << title;
			ChangeColor(DEFAULT);
			gotoRowCol(row + 1, column + (total_width - title.length()) / 2);
			ChangeColor(title_color);
			PrintNTimes(205, title.size());
			ChangeColor(DEFAULT);
			row = row + 3;
		}
		for (int i = 0; i < options.size(); i++)
		{


			DisplayBoxWithStr(row + (((i) / options_per_line) * 3), column + (i % options_per_line) * width + (i % options_per_line) * inline_gap, width, 3, border_char, options[i], "GREEN", box_color);
			//DisplayBoxWithStr(row + (i * 3) + i, column, width, 3, border_char, options[i], "GREEN", "WHITE");

			if (input_in_progress)
				boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(row + (((i) / options_per_line) * 3), column + (i % options_per_line) * width + (i % options_per_line) * inline_gap), pair<int, int>(width, 3)));
			//boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(row + (i * 3) + i, column), pair<int, int>(width, 3)));
		}
		gotoRowCol(boxes[boxes.size() - 1].first.first + 3, 0);
	}


	int inputA(bool display = true)
	{
		if (display)
			Display();
		cout << endl << "Enter choice: ";
		switch (display_type)
		{
		case 1:
			int intInput;
			cin >> intInput;
			return intInput;
		case 2:
			char charInput;
			cin >> charInput;
			return charInput;
		}
	}
	int inputB(bool display = true)
	{
		if (display)
			Display();
		switch (display_type)
		{
		case 1:
			int intInput;
			intInput = _getch();
			return intInput - 48;
		case 2:
			char charInput;
			charInput = _getch();
			return charInput - 96;
		}
	}
	int inputC(bool display = true)
	{
		if (display)
		{
			display_override = true;
			Display();
			display_override = false;
		}
		int r, c;
		while (true)
		{
			while ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)
			{
			}
			getRowColbyLeftClick(r, c);
			for (int i = 0; i < boxes.size(); i++)
			{
				if (r >= boxes[i].first.first && r <= boxes[i].first.first + boxes[i].second.second - 1
					&& c >= boxes[i].first.second && c <= boxes[i].first.second + boxes[i].second.first - 1)
				{
					RemoveLastDisplay();
					return i + 1;
				}
			}
		}
	}
	int StrToInputNum(string type)
	{
		Decapitalize(type);
		if (type == "enter" || type == "cin" || type == "consoleinput" || type == "console_input" || type == "default")
		{
			return  1;
		}
		else if (type == "buttonpress" || type == "button_press" || type == "automatic" || type == "onpress" || type == "uponbuttonpress" || type == "uponpressing" || type == "uponpress")
		{
			return  2;
		}
		else if (type == "mouse" || type == "mouse_click" || type == "mouseclick" || type == "cursor")
		{
			return 3;
		}
		else
			return 1;
	}
	void RemoveLastDisplay()
	{
		switch (display_type)
		{
		case 1:
		case 2:
			system("cls");
			break;
		case 3:
			for (int i = 0; i < boxes.size(); i++)
			{
				RemoveBox(boxes[i].first.first, boxes[i].first.second, boxes[i].second.first, boxes[i].second.second);
			}
			break;
		}
	}
	int MaxOptionSize()
	{
		int max = 0;
		for (int i = 0; i < options.size(); i++)
		{
			if (options[i].size() > max) max = options[i].size();
		}
		return max;
	}
	void TreeInputHelper(string& S)
	{
		do
		{
			if (S.size() > 0 && S[S.size() - 1] == '-') S.pop_back();
			int temp = Input(true);
			if (temp == options.size() && options[temp - 1] == "back")
			{
				S.pop_back();
				S.push_back('-');
				return;
			}
			S.push_back(to_char(temp));
			if (sub_menus.size() > temp - 1)
			{
				sub_menus[temp - 1]->push_back("back");
				sub_menus[temp - 1]->TreeInputHelper(S);
				sub_menus[temp - 1]->pop_back();
			}
		} while (S[S.size() - 1] == '-');
	}
	void TreeInputHelper(vector<int>& S)
	{
		do
		{
			if (S.size() > 0 && S[S.size() - 1] == -1) S.pop_back();
			int temp = Input(true);
			if (temp == options.size() && options[temp - 1] == "back")
			{
				S.pop_back();
				S.push_back(-1);
				return;
			}
			S.push_back(temp);
			if (sub_menus.size() > temp - 1)
			{
				sub_menus[temp - 1]->push_back("back");
				sub_menus[temp - 1]->TreeInputHelper(S);
				sub_menus[temp - 1]->pop_back();
			}
		} while (S[S.size() - 1] == -1);
	}
	bool IsPresent(vector<string>& S, string& F)
	{
		for (int i = 0; i < S.size(); i++)
		{
			if (S[i] == F) return true;
		}
		return false;
	}
public:
	menu()
	{
		Init();
	}
	menu(string S1, string S2 = " ", string S3 = " ", string S4 = " ", string S5 = " ", string S6 = " ", string S7 = " ", string S8 = " ", string S9 = " ", string S10 = " ", string S11 = " ", string S12 = " ")
	{
		Init();
		set(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12);
	}
	void set(string S1, string S2 = " ", string S3 = " ", string S4 = " ", string S5 = " ", string S6 = " ", string S7 = " ", string S8 = " ", string S9 = " ", string S10 = " ", string S11 = " ", string S12 = " ")
	{
		options.clear();
		options = { S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12 };
		for (int i = options.size() - 1; i >= 0 && options[i] == " "; i--)
		{
			options.pop_back();
		}
	}
	void set(const vector<string>& S)
	{
		options = S;
	}
	void push_back(string S)
	{
		if (!IsPresent(options, S))
			options.push_back(S);
	}
	void SetTitle(string Title, string Title_Color = "Yellow")
	{
		title = Title;
		title_color = Title_Color;
	}
	void SetTextColor(string Color)
	{
		text_color = Color;
	}
	void SetBoxColor(string Color)
	{
		box_color = Color;
	}
	void pop_back()
	{
		options.pop_back();
	}
	void SetDisplayType(int type)
	{
		if (type > 0 && type <= max_display_types)
		{
			display_type = type;
		}
	}
	void SetInputType(int type)
	{
		if (type > 0 && type <= max_input_types)
		{
			input_type = type;
		}
	}
	void SetDisplayType(string type)
	{
		Decapitalize(type);
		if (type == "123" || type == "numeric" || type == "numbers" || type == "number")
		{
			display_type = 1;
		}
		else if (type == "abc" || type == "alphabets" || type == "alphabet" || type == "alphabetic" || type == "english")
		{
			display_type = 2;
		}
	}
	void SetInputType(string type)
	{
		input_type = StrToInputNum(type);
	}
	void SetOptionsPerLine(int num)
	{
		if (num <= 0) return;
		options_per_line = num;
	}
	void SetInlineGap(int gap)
	{
		if (gap < 0) return;
		inline_gap = gap;
	}
	void SetLocation(int console_row, int console_column)
	{
		mouse_input_start_point.first = console_row;
		mouse_input_start_point.second = console_column;
	}
	void SetLocation(string S)
	{
		Decapitalize(S);
		if (S == "default")
		{
			mouse_input_start_point.first = 0;
			mouse_input_start_point.second = 0;
		}
		else if (S == "middle")
		{
			int r, c;
			GetConsoleSize(r, c);
			mouse_input_start_point.first = 0;
			mouse_input_start_point.second = c / 2 - (MaxOptionSize() / 2);
			if (mouse_input_start_point.second < 0) mouse_input_start_point.second = 0;
		}
	}
	void SetTreeMouseInputDisplayStart(int console_row, int console_column, bool set_middle = false)
	{
		if (set_middle)
		{
			int r, c;
			GetConsoleSize(r, c);
			mouse_input_start_point.first = 0;
			mouse_input_start_point.second = c / 2 - (MaxOptionSize() / 2);
			if (mouse_input_start_point.second < 0) mouse_input_start_point.second = 0;
			for (int i = 0; i < sub_menus.size(); i++)
			{
				sub_menus[i]->SetTreeMouseInputDisplayStart(console_row, console_column, true);
			}
		}
		else
		{
			mouse_input_start_point.first = console_row;
			mouse_input_start_point.second = console_column;
			for (int i = 0; i < sub_menus.size(); i++)
			{
				sub_menus[i]->SetTreeMouseInputDisplayStart(console_row, console_column);
			}
		}
	}
	void SetTreeMouseInputDisplayStart(string S)
	{
		Decapitalize(S);
		if (S == "default")
		{
			SetTreeMouseInputDisplayStart(0, 0);
		}
		else if (S == "middle")
		{
			SetTreeMouseInputDisplayStart(0, 0, true);
		}
	}
	int  Input(bool display = true)
	{
		switch (input_type)
		{
		case 1:
			return inputA(display);
			break;
		case 2:
			return inputB(display);
			break;
		case 3:
			return inputC(display);
			break;
		}
	}
	void SetBoxWidth(int width)
	{
		if (width < 0) return;
		box_width = width;
	}
	void clearsubmenu()
	{
		sub_menus.clear();
	}
	void setsubmenu(menu m1, menu m2 = 0, menu m3 = 0, menu m4 = 0, menu m5 = 0, menu m6 = 0, menu m7 = 0, menu m8 = 0, menu m9 = 0)
	{
		sub_menus.clear();
		sub_menus.push_back(new menu(m1));
		sub_menus.push_back(new menu(m2));
		sub_menus.push_back(new menu(m3));
		sub_menus.push_back(new menu(m4));
		sub_menus.push_back(new menu(m5));
		sub_menus.push_back(new menu(m6));
		sub_menus.push_back(new menu(m7));
		sub_menus.push_back(new menu(m8));
		sub_menus.push_back(new menu(m9));
		for (int i = sub_menus.size() - 1; i >= 0; i--)
		{
			if (sub_menus[i]->temp_menu == false)
				break;
			else
			{
				delete sub_menus[i];
				sub_menus.pop_back();
			}
		}
	}
	void setsubmenu(const vector<menu*>& sub_menu)
	{
		sub_menus = sub_menu;
	}
	void addsubmenu(menu m)
	{
		sub_menus.push_back(new menu(m));
	}
	void removesubmenu(int amount = 1)
	{
		if (sub_menus.size() >= amount)
		{
			for (int i = 0; i < amount; i++)
				sub_menus.pop_back();
		}
	}
	void TakeTreeInput(string& str)
	{
		string S;
		TreeInputHelper(S);
		str = S;
	}
	void SetTreeInputType(string type)
	{
		SetTreeInputType(StrToInputNum(type));
	}
	void SetTreeInputType(int N)
	{
		input_type = N;
		for (int i = 0; i < sub_menus.size(); i++)
		{
			sub_menus[i]->SetInputType(N);
		}
	}
	vector<int> TakeTreeInput()
	{
		vector<int> V;
		TreeInputHelper(V);
		return V;
	}
};
class form
{
	//1 = string		str
	//2 = integer		int
	//3 = char			char
	//4 = float			float
	//5 = double		double
	//6 = boolean		bool
	//7 = password		str
	//8 = date			str
	//9 = mcqs			int
protected:
	//form customization variables
	int sr;
	int sc;
	int form_max_width;
	int form_max_height;
	string title;
	string title_color;
	string submit_box_text_color;
	bool boundry_and_title;


	//box loc variables
	vector<pair<pair<int, int>, pair<int, int>>> boxes;
	pair<pair<int, int>, pair<int, int>> submit_box;

	//special type variabbles
	vector<vector<string>> mcq_options;
	vector<pair<int, int>> mcqs_type_loc;
	vector<vector<pair<int, int>>> mcq_box_locator;
	vector<pair<int, int>> date_type_loc;

	//output variables
	vector<string> S;
	vector<string> str_output;
	vector<int> int_output;
	vector<char> char_output;
	vector<float> float_output;
	vector<double> double_output;
	vector<bool> boolean_output;

	//customization variables
	int max_input_size;
	int inputs_per_line;
	vector<int> spacing;
	vector<int> custom_input_size;
	int ColumnGap;
	int max_header_size;
	int header_display_type;
	char border_char;
	char fill_char;
	string border_color;
	string header_color;
	string box_color;
	string submit_box_color;
	string input_color;
	string fill_color;

	//processing variables
	string order;
	string submit_text;
	vector<int> input_types;
	vector<string>headers;
	vector<string> temp;
	vector<int> Highlighted_box;

	int HeaderToDateBoxNum(int N)
	{
		for (int i = 0; i < date_type_loc.size(); i++)
		{
			if (date_type_loc[i].first == N) return date_type_loc[i].second;
		}
		cout << "Exception in data handling: Failed to find must_have_data in date_type_loc";
		return -1;
	}
	int CoorToBoxNum(int r, int c)
	{
		int row, col, width, height;
		for (int i = 0; i < boxes.size(); i++)
		{
			row = boxes[i].first.first;
			col = boxes[i].first.second;
			width = boxes[i].second.first;
			height = boxes[i].second.second;
			if (r >= row && r <= row + height - 1 && c >= col && c <= col + width - 1)
			{
				return i;
			}
		}
		return -1;
	}
	bool getRowColbyLeftClickBoolean(int& rpos, int& cpos)
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
		} while (GetKeyState(VK_LBUTTON) < 0);
		if (GetKeyState(VK_LBUTTON) < 0) return true;
		else return false;
	}
	int BoxNumToHeader(int N)
	{
		int count = -1;
		for (int i = 0; i < order.size(); i++)
		{
			if (order[i] == 'X')
			{
				count += 3;
			}
			else if (order[i] == 'B')
			{
				count += 2;
			}
			else if (order[i] == 'M')
			{
				count += mcq_options[i].size();
			}
			else
			{
				count += 1;
			}
			if (count >= N) return i;
		}
	}
	void ExtractRowCol(pair<pair<int, int>, pair<int, int>>& box, int& r, int& c)
	{
		r = box.first.first;
		c = box.first.second;
	}
	void ExtractWidthHeight(pair<pair<int, int>, pair<int, int>>& box, int& w, int& h)
	{
		w = box.second.first;
		h = box.second.second;
	}
	char to_char(int type)
	{
		switch (type)
		{
		case 1:
			return 'S';
		case 2:
			return 'I';
		case 3:
			return 'C';
		case 4:
			return 'F';
		case 5:
			return 'D';
		case 6:
			return 'B';
		case 7:
			return 'P';
		case 8:
			return 'X';
		case 9:
			return 'M';
		}
	}
	int type_to_int(string S)
	{
		if (S == "integer" || S == "int") return 2;
		if (S == "string" || S == "sentence" || S == "word" || S == "default") return 1;
		if (S == "char" || S == "character") return 3;
		if (S == "float" || S == "decimal") return 4;
		if (S == "bigint" || S == "double") return 5;
		if (S == "bool" || S == "boolean") return 6;
		if (S == "password" || S == "hidden" || S == "pass") return 7;
		if (S == "date") return 8;
		if (S == "mcqs" || S == "mcq" || S == "multiple choice questions") return 9;
		return 1;
	}
	void ProcessInput(string S, int& Type, string& Header)
	{
		string type;
		int count = 0;
		if (S.size() == 0)
		{
			Type = 1;
			Header = S;
			return;
		}
		for (int i = 0; i < S.size(); i++)
		{
			if (S[i] == ':') count++;
		}
		if (count == 0)
		{
			Type = 1;
			Header = S;
			return;
		}
		count = 0;
		while (S[count] != ':')
		{
			type.push_back(S[count]);
			count++;
		}
		Decapitalize(type);
		Type = type_to_int(type);
		Header = S.substr(count + 1, S.size() - 1);
	}
	void DisplayHeader(string header, int r, int c)
	{
		if (header_display_type == 1)
		{
			gotoRowCol(r, c);
			ChangeColor(header_color);
			cout << header;
			ChangeColor("default");

		}
		else if (header_display_type == 2)
		{
			c = c + (max_header_size - header.length()) / 2;
			gotoRowCol(r, c);
			ChangeColor(header_color);
			cout << header;
			ChangeColor("default");
		}
	}
	void RemoveHeader(int r, int c)
	{
		gotoRowCol(r, c);
		PrintNTimes(' ', max_header_size);
	}
	void DisplayBoxWithSC(int r, int c, int width, int height, char border_char, string text = " ")
	{
		if (text == " ")
		{
			if (border_char == '=')
			{
				DisplayFancyBox(r, c, width, height, 1, box_color);
			}
			else if (border_char == '-')
			{
				DisplayFancyBox(r, c, width, height, 0, box_color);
			}
			else
			{
				DisplayBox(r, c, width, height, border_char, box_color);
			}
		}
		else
		{
			if (border_char == '=')
			{
				DisplayFancyBoxWithStr(r, c, width, height, 1, text);
			}
			else if (border_char == '-')
			{
				DisplayFancyBoxWithStr(r, c, width, height, 0, text);
			}
			else
			{
				DisplayBoxWithStr(r, c, width, height, border_char, text);
			}
		}
	}
	int IndexToCol(int i)
	{
		return i % inputs_per_line;
	}
	int GetTotalCols()
	{
		return inputs_per_line;
	}
	int GetElementSize(int i)
	{
		switch (input_types[i])
		{
		case 1:
		case 2:
		case 4:
		case 5:
		case 7:
			if (custom_input_size.size() == 0) return max(max_input_size + 2, headers[i].size());
			else return max(custom_input_size[i] + 2, headers[i].size());
		case 3:
			return max(3, headers[i].size());
		case 6:
			return max(10, headers[i].size());
		case 8:
			return max(14, headers[i].size());
			break;
		case 9:
			int cc = 0;
			for (int j = 0; j < mcq_options[i].size(); j++)
			{
				if (j == 0)
					cc += mcq_options[i][j].size() + 2;
				else
					cc += mcq_options[i][j].size() + 3;
			}
			return max(cc, headers[i].size());
		}
	}
	void ProcessSpacing()
	{
		int total_cols = GetTotalCols();
		spacing.resize(total_cols, 0);
		int size;
		for (int i = 0; i < headers.size(); i++)
		{
			size = GetElementSize(i);
			if (size > spacing[IndexToCol(i)])
				spacing[IndexToCol(i)] = size;
		}
	}
	int CalculateFormMaxWidth(bool SpacingProcessed = false)
	{
		if (!SpacingProcessed)
			ProcessSpacing();
		int size = 2;
		for (int i = 0; i < spacing.size(); i++)
		{
			if (i == 0)
				size += spacing[i];
			else
				size += spacing[i] + ColumnGap;
		}
		return size;
	}
	int CalculateFormMaxHeight()
	{
		return ceil(float(headers.size()) / inputs_per_line) * 5 + 2;
	}
	void DisplayElement(string header, int type, int r, int c, int N, int input_size)
	{
		switch (type)
		{
		case 1:
		case 2:
		case 4:
		case 5:
		case 7:
			DisplayBoxWithSC(r + 1, c, input_size + 2, 3, border_char);
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c), pair<int, int>(max_input_size + 2, 3)));
			break;
		case 3:
			DisplayBoxWithSC(r + 1, c, 3, 3, border_char);
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c), pair<int, int>(3, 3)));
			break;
		case 6:
			DisplayBoxWithSC(r + 1, c, 3, 3, border_char);
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c), pair<int, int>(3, 3)));
			gotoRowCol(r + 2, c + 4);
			cout << "Yes";
			DisplayBoxWithSC(r + 1, c + (input_size - 3), 3, 3, border_char);
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c + (max_input_size - 3)), pair<int, int>(3, 3)));
			gotoRowCol(r + 2, c + (input_size - 3) + 4);
			cout << "No";
			break;
		case 8:
			DisplayBoxWithSC(r + 1, c, 4, 3, border_char);
			DisplayBoxWithSC(r + 1, c + 5, 4, 3, border_char);
			DisplayBoxWithSC(r + 1, c + 10, 4, 3, border_char);
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c), pair<int, int>(4, 3)));
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c + 5), pair<int, int>(4, 3)));
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c + 10), pair<int, int>(4, 3)));
			date_type_loc.push_back(pair<int, int>(boxes.size() - 3, 1));
			date_type_loc.push_back(pair<int, int>(boxes.size() - 2, 2));
			date_type_loc.push_back(pair<int, int>(boxes.size() - 1, 3));
			gotoRowCol(r + 2, c + 1);
			cout << "DD";
			gotoRowCol(r + 2, c + 6);
			cout << "MM";
			gotoRowCol(r + 2, c + 11);
			cout << "YY";
			break;
		case 9:
			int cc = 0;
			for (int i = 0; i < mcq_options[N].size(); i++)
			{
				DisplayBoxWithSC(r + 1, c + cc, mcq_options[N][i].size() + 2, 3, border_char, mcq_options[N][i]);
				boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c + cc), pair<int, int>(mcq_options[N][i].size() + 2, 3)));
				mcq_box_locator[N].push_back(pair<int, int>(boxes.size() - 1, i));
				cc += mcq_options[N][i].size() + 3;
			}
			break;
		}
		DisplayHeader(header, r, c);
		ChangeColor("DeFauLt");
	}
	int BoxToMcqNum(int header, int box_num)
	{
		for (int i = 0; i < mcq_box_locator[header].size(); i++)
		{
			if (mcq_box_locator[header][i].first == box_num)
				return mcq_box_locator[header][i].second;

		}
		cout << "\nException: Unable to find must_have_mcq_num in BoxToMcqNum(int,int)\n";
	}
	vector<int> GetCommulativeSpacing()
	{
		vector<int> CSpacing = spacing;
		for (int i = 1; i < CSpacing.size(); i++)
		{
			CSpacing[i] += CSpacing[i - 1];
		}
		return CSpacing;
	}
	vector<int> GetInputStartCols()
	{
		vector<int> CSpacing = GetCommulativeSpacing();
		vector<int> StartCols;
		StartCols.push_back(0);
		int count = 1;
		for (int i = 0; i < CSpacing.size() - 1; i++)
		{
			StartCols.push_back(CSpacing[i] + count * ColumnGap);
			count++;
		}
		return StartCols;
	}
	void Display()
	{
		ProcessSpacing();
		form_max_width = max(form_max_width, CalculateFormMaxWidth());
		form_max_height = max(form_max_height, CalculateFormMaxHeight());

		//fill char
		for (int r = sr; r <= sr + form_max_height + 10; r++)
		{
			gotoRowCol(r, sc);
			ChangeColor(fill_color);
			PrintNTimes(fill_char, form_max_width + 2);
		}

		vector<int> StartCols = GetInputStartCols();
		if (boundry_and_title)
		{

			sr += 6;
			sc += 2;
			for (int i = 0; i < headers.size(); i++)
			{
				if (custom_input_size.size() == 0)
					DisplayElement(headers[i], input_types[i], sr + (5 * (i / inputs_per_line)), sc + StartCols[IndexToCol(i)], i, max_input_size);
				else
					DisplayElement(headers[i], input_types[i], sr + (5 * (i / inputs_per_line)), sc + StartCols[IndexToCol(i)], i, custom_input_size[i]);
			}
			DisplaySubmitButton(form_max_height + sr, sc);
			sr -= 6;
			sc -= 2;

			//Title
			DisplayFancyBoxWithStr(sr, sc, form_max_width + 3, 5, 1, title, title_color, border_color);

			//Border
			DisplayFancyBox(sr, sc, form_max_width + 3, form_max_height + 11, 1, border_color);

			//Title-Border Integration
			ChangeColor(border_color);
			gotoRowCol(sr + 4, sc + form_max_width + 2);
			cout << to_character(185);
			gotoRowCol(sr + 4, sc);
			cout << to_character(204);
			ChangeColor("default");

		}
		else
		{
			for (int i = 0; i < headers.size(); i++)
			{
				if (custom_input_size.size() == 0)
					DisplayElement(headers[i], input_types[i], sr + (5 * (i / inputs_per_line)), sc + StartCols[IndexToCol(i)], i, max_input_size);
				else
					DisplayElement(headers[i], input_types[i], sr + (5 * (i / inputs_per_line)), sc + StartCols[IndexToCol(i)], i, custom_input_size[i]);
			}
			DisplaySubmitButton(5 * headers.size() + sr, sc);
		}

	}
	void Init()
	{
		sr = 0;
		sc = 0;
		title = "Form";
		title_color = "Default";
		max_input_size = 20;
		max_header_size = 24;
		form_max_width = 24;
		header_display_type = 1;
		border_char = '-';
		submit_text = "Sumbit";
		submit_box_text_color = "Default";
		boundry_and_title = true;
		border_color = "white";
		header_color = "white";
		box_color = "white";
		submit_box_color = "white";
		input_color = "white";
		inputs_per_line = 1;
		max_input_size = 24;
		max_header_size = 24;
		ColumnGap = 2;
		fill_char = ' ';
		fill_color = "Black";
	}
	bool IsInSubmitBox(int r, int c)
	{
		if (r >= submit_box.first.first && r <= submit_box.first.first + submit_box.second.second &&
			c >= submit_box.first.second && c <= submit_box.first.second + submit_box.second.first)
			return true;
		return false;
	}
	bool IsValidDate(string S)
	{
		if (S[0] == S[1] && S[1] == '0') return false;
		if (S[3] == S[4] && S[4] == '0') return false;
		if (S[6] == S[7] && S[7] == '0') return false;
		return true;
	}
	bool DisplayWarning(vector<string>& S)
	{
		if (boundry_and_title)
		{
			sr += 6;
			sc += 2;
		}
		bool Warning = false;
		int r, c;
		ChangeColor("Red");
		vector<int> temp = GetInputStartCols();
		for (int i = 0; i < S.size(); i++)
		{
			r = (5 * (i / inputs_per_line)) + sr;
			c = sc + temp[IndexToCol(i)];
			if ((order[i] == 'X' && !IsValidDate(S[i])) || S[i].size() == 0)
			{
				Warning = true;
				if (header_display_type == 1)
				{
					gotoRowCol(r, c + headers[i].size() + 1);
					cout << "!";
				}
				else if (header_display_type == 2)
				{
					c = c + (max_header_size - headers[i].length()) / 2;
					gotoRowCol(r, c + 1 + headers[i].size());
					cout << "!";
				}
			}
		}
		ChangeColor("White");
		if (boundry_and_title)
		{
			sr -= 6;
			sc -= 2;
		}
		return Warning;
	}
	void RemoveWarning(vector<string>& S)
	{
		int r, c;
		if (boundry_and_title)
		{
			sr += 6;
			sc += 2;
		}
		vector<int> temp = GetInputStartCols();
		for (int i = 0; i < S.size(); i++)
		{
			r = (5 * (i / inputs_per_line)) + sr;
			c = sc + temp[IndexToCol(i)];
			if ((order[i] == 'X' && IsValidDate(S[i])) || S[i].size() != 0)
			{
				if (header_display_type == 1)
				{
					gotoRowCol(r, c + headers[i].size() + 1);
					cout << " ";
				}
				else if (header_display_type == 2)
				{
					c = c + (max_header_size - headers[i].length()) / 2;
					gotoRowCol(r, c + 1 + headers[i].size());
					cout << " ";
				}
			}
		}
		if (boundry_and_title)
		{
			sr -= 6;
			sc -= 2;
		}
	}
	bool IsValidFloatStr(string S)
	{
		if (S.size() > 1 && S[0] == '0' && S[1] != '.') return false;
		if (S.size() <= 38) return true;
		int x = S.find('.');
		if (x == string::npos && S.size() <= 38) return true;
		if (x < 38 && S.size() - x <= 38) return true;
		return false;
	}
	bool IsValidDoubleStr(string S)
	{
		if (S.size() > 1 && S[0] == '0' && S[1] != '.') return false;
		if (S.size() <= 308) return true;
		int x = S.find('.');
		if (x == string::npos && S.size() <= 308) return true;
		if (x < 308 && S.size() - x <= 308) return true;
		return false;
	}
	bool IsValidInput(string S, char c, int type)
	{
		switch (type)
		{
		case 3:
		case 1:
		case 6:
		case 7:
			return true;
		case 2:
			if (S.size() == 0 && c == '-') return true;
			if (S.size() == 1 && S[0] == '0') return false;
			if (S.size() == 1 && S[0] == '-' && c == '0') return false;
			if (c >= '0' && c <= '9')
			{
				if (S.size() < 9) return true;
			}
			return false;
		case 4:
			if (S.size() == 0 && c == '-') return true;
			if (c == '.' && S.find('.') == string::npos) return true;
			if (c >= '0' && c <= '9')
			{
				S.push_back(c);
				return IsValidFloatStr(S);
			}
			return false;
		case 5:
			if (S.size() == 0 && c == '-') return true;
			if (c == '.' && S.find('.') != string::npos) return true;
			if (c >= '0' && c <= '9')
			{
				S.push_back(c);
				return IsValidDoubleStr(S);
			}
			return false;
		}
	}
	int UpdateDate(string& S, char c, int type)
	{
		char first_char, second_char;
		first_char = S[(type - 1) * 3];
		second_char = S[(type - 1) * 3 + 1];
		if (c == 8)
		{
			if (first_char == '0' && second_char == '0') return 0;
			if (first_char == '0' && second_char != '0')
			{
				S[(type - 1) * 3 + 1] = '0';
				ClearLastFromConsole();
				return -1;
			}
			else if (first_char != '0')
			{
				S[(type - 1) * 3 + 1] = S[(type - 1) * 3];
				S[(type - 1) * 3] = '0';
				ClearLastFromConsole();
				return -1;
			}
		}
		else
		{
			if (first_char != '0') return 0;
			if (first_char == '0' && second_char == '0')
			{
				if (c == '0') return 0;
				S[(type - 1) * 3 + 1] = c;
				ChangeColor(input_color);
				cout << c;
				ChangeColor("default");
				cout << " ";
				ClearLastFromConsole();
				return 1;
			}
			if (first_char == '0')
			{
				if (type == 1)
				{
					if (second_char >= '4') return 0;
					if (second_char == '3' && c >= '2') return 0;
				}
				else if (type == 2)
				{
					if (second_char >= '2') return 0;
					if (second_char == '1' && c >= '3') return 0;
				}
				else if (type == 3)
				{

				}
				S[(type - 1) * 3] = S[(type - 1) * 3 + 1];
				S[(type - 1) * 3 + 1] = c;
				ChangeColor(input_color);
				cout << c;
				ChangeColor("default");
				return 1;
			}
		}
	}
	void Highlight(int box_num, string text = "")
	{
		int style;
		if (border_char == '-') style = 0;
		else if (border_char == '=') style = 1;
		else style = -1;
		if (style >= 0)
		{
			if (text != "")
			{
				DisplayFancyBoxWithStr(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, style, text, "YELLOW", "GREEN");
			}
			else
			{
				DisplayFancyBox(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, style, "GREEN");
			}
		}
		else
		{
			if (text != "")
			{
				DisplayBoxWithStr(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, border_char, text, "YELLOW", "GREEN");
			}
			else
			{
				DisplayBox(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, border_char, "GREEN");
			}
		}

	}
	void UnHighlight(int box_num, string text = "")
	{
		int style;
		if (border_char == '-') style = 0;
		else if (border_char == '=') style = 1;
		else style = -1;
		if (style >= 0)
		{
			if (text != "")
			{
				DisplayFancyBoxWithStr(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, style, text);
			}
			else
			{
				DisplayFancyBox(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, style);
			}
		}
		else
		{
			if (text != "")
			{
				DisplayBoxWithStr(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, border_char, text);
			}
			else
			{
				DisplayBox(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, border_char);
			}
		}
	}
	vector<string> TakeInput()
	{
		bool selected = false;
		int last_selected_box = -1;
		if (headers.size() == 0) return S;
		for (int i = 0; i < headers.size(); i++)
			S.push_back("");
		int current_box = 0;
		int current_type = input_types[0];
		int current_header = 0;
		char cc = '0';
		int temp;
		int r = 0, c = 0;
		bool clicked = true;
		Display();
		for (int i = 0; i < order.size(); i++)
		{
			if (order[i] == 'X')
			{
				S[i] = "00-00-00000";
			}
		}
		do
		{
			if (clicked)
			{
				while (getRowColbyLeftClickBoolean(temp, temp))
				{

				}
			}
			while (GetKeyState(VK_LBUTTON) >= 0 && !_kbhit())
			{
			}
			if (GetKeyState(VK_LBUTTON) < 0)
			{
				clicked = true;
				getRowColbyLeftClickBoolean(r, c);
				if (IsInSubmitBox(r, c))
				{
					RemoveWarning(S);
					if (DisplayWarning(S))
					{
						continue;
					}
					else
					{
						break;
					}
				}
				selected = true;
				current_box = CoorToBoxNum(r, c);
				if (current_box == -1)
				{
					if (last_selected_box != -1) current_box = last_selected_box;
					else
						selected = false;
					continue;
				}
				last_selected_box = current_box;
				current_header = BoxNumToHeader(current_box);
				current_type = input_types[current_header];
				if (current_type == 6)
				{
					gotoRowCol(boxes[current_box].first.first + 1, boxes[current_box].first.second + 1);
					cout << "O";
					if (current_box != 0 && input_types[BoxNumToHeader(current_box - 1)] == 6 && boxes[current_box - 1].first.first == boxes[current_box].first.first)
					{
						gotoRowCol(boxes[current_box - 1].first.first + 1, boxes[current_box - 1].first.second + 1);
						cout << " ";
						S[current_header] = "false";
					}
					else
					{
						gotoRowCol(boxes[current_box + 1].first.first + 1, boxes[current_box + 1].first.second + 1);
						cout << " ";
						S[current_header] = "true";
					}
					continue;
				}
				if (current_type == 9)
				{
					temp = BoxToMcqNum(current_header, current_box);
					if (Highlighted_box[current_header] != -1)
					{
						UnHighlight(Highlighted_box[current_header], S[current_header]);
					}
					S[current_header] = mcq_options[current_header][temp];
					Highlight(current_box, S[current_header]);
					Highlighted_box[current_header] = current_box;
					continue;
				}
				if (current_type == 8)
				{
					gotoRowCol(boxes[current_box].first.first + 1, boxes[current_box].first.second + 1 + (S[current_header][8 + HeaderToDateBoxNum(current_box) - 1] - '0'));
				}
				else
				{
					gotoRowCol(boxes[current_box].first.first + 1, boxes[current_box].first.second + 1 + S[current_header].size());
				}
				Sleep(250);
			}
			else
			{
				clicked = false;
				if (!selected) continue;
				cc = _getch();
				if (current_type == 6) continue;
				else if (current_type == 8)
				{
					int tr, tc;
					GetRowCol(tr, tc);
					if (cc == 8 || (cc >= '0' && cc <= '9' && tc != boxes[current_box].first.second + boxes[current_box].second.first - 1))
					{
						int temp;
						int num = HeaderToDateBoxNum(current_box);
						temp = UpdateDate(S[current_header], cc, num);
						if (temp == -1) S[current_header][8 + num - 1]--;
						else if (temp == 1) S[current_header][8 + num - 1]++;
					}
				}
				else if (cc == 8)
				{
					if (S[current_header].size() != 0 && current_type != 6 && S[current_header].size() != 0)
					{
						ClearLastFromConsole();
						S[current_header].pop_back();
					}
				}
				else
				{
					if (cc >= 32 && cc <= 126)
					{
						if (IsValidInput(S[current_header], cc, current_type))
						{
							if (S[current_header].size() != boxes[current_box].second.first - 2)
							{
								if (current_type == 7)
								{
									ChangeColor(input_color);
									cout << "*";
									ChangeColor("default");
								}
								else
								{
									ChangeColor(input_color);
									cout << cc;
									ChangeColor("default");
								}
								S[current_header].push_back(cc);
							}
						}
					}
				}
			}
		} while (true);
		for (int i = 0; i < order.size(); i++)
		{
			if (order[i] == 'X')
			{
				S[i].pop_back();
				S[i].pop_back();
				S[i].pop_back();
			}
		}
		system("cls");
		DisassembleOutput();
		return S;
	}
	void DisplaySubmitButton(int r, int c)
	{
		if (border_char == '=')
		{
			DisplayFancyBoxWithStr(r + 1, c, submit_text.size() + 2, 3, 1, submit_text, submit_box_text_color, submit_box_color);
		}
		else if (border_char == '-')
		{
			DisplayFancyBoxWithStr(r + 1, c, submit_text.size() + 2, 3, 0, submit_text, submit_box_text_color, submit_box_color);

		}
		else
		{
			DisplayBoxWithStr(r + 1, c, submit_text.size() + 2, 3, border_char, submit_text, submit_box_text_color, submit_box_color);
		}
		submit_box = pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c), pair<int, int>(submit_text.size() + 2, 3));
	}
	void RemoveSubmitButton()
	{
		int r, c, w, h;
		ExtractRowCol(submit_box, r, c);
		ExtractWidthHeight(submit_box, w, h);
		RemoveBox(r, c, w, h);
	}
	void DisassembleOutput()
	{
		if (order.size() != S.size()) return;
		for (int i = 0; i < order.size(); i++)
		{
			switch (order[i])
			{
			case 'S':
			case 'P':
			case 'X':
			case 'M':
				str_output.push_back(S[i]);
				break;
			case 'I':
				int_output.push_back(stoi(S[i]));
				break;
			case 'C':
				char_output.push_back(S[i][0]);
				break;
			case 'F':
				float_output.push_back(stof(S[i]));
				break;
			case 'D':
				double_output.push_back(stod(S[i]));
				break;
			case 'B':
				if (S[i] == "true")
				{
					boolean_output.push_back(true);
				}
				else
				{
					boolean_output.push_back(false);
				}
				break;
			default:
				system("cls");
				cout << "Exception in output disassembling detected! Please report to the author...";
				exit(0);
			}
		}
	}
public:
	form()
	{
		Init();
	}
	form(string S1, string S2 = " ", string S3 = " ", string S4 = " ", string S5 = " ", string S6 = " ", string S7 = " ", string S8 = " ", string S9 = " ", string S10 = " ", string S11 = " ", string S12 = " ")
	{
		set(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12);
		Init();
	}

	void set(vector<string> inputs)
	{
		clear();
		int type;
		string header;
		mcq_box_locator.resize(inputs.size());
		for (int i = 0; i < inputs.size(); i++)
		{
			ProcessInput(inputs[i], type, header);
			input_types.push_back(type);
			if (header.size() > max_header_size)
			{
				max_header_size = header.size();
			}
			headers.push_back(header);
			order.push_back(to_char(type));
			if (type == 9)
			{
				vector<string> options;
				vector<string> header_option_pair;
				header_option_pair = split(header, ':', 1);
				header = header_option_pair[0];

				headers.pop_back();
				headers.push_back(header);

				options = split(header_option_pair[header_option_pair.size() - 1], ',');
				mcq_options.push_back(options);
				int header_num = i;
			}
			else
			{
				vector<string> T;
				mcq_options.push_back(T);
			}
		}
		Highlighted_box.resize(order.size(), -1);
	}
	void set(string S1, string S2 = " ", string S3 = " ", string S4 = " ", string S5 = " ", string S6 = " ", string S7 = " ", string S8 = " ", string S9 = " ", string S10 = " ", string S11 = " ", string S12 = " ", string S13 = " ", string S14 = " ", string S15 = " ", string S16 = " ", string S17 = " ", string S18 = " ", string S19 = " ", string S20 = " ", string S21 = " ", string S22 = " ", string S23 = " ", string S24 = " ")
	{
		clear();
		int type;
		string header;
		temp.push_back(S1);
		temp.push_back(S2);
		temp.push_back(S3);
		temp.push_back(S4);
		temp.push_back(S5);
		temp.push_back(S6);
		temp.push_back(S7);
		temp.push_back(S8);
		temp.push_back(S9);
		temp.push_back(S10);
		temp.push_back(S11);
		temp.push_back(S12);
		temp.push_back(S13);
		temp.push_back(S14);
		temp.push_back(S15);
		temp.push_back(S16);
		temp.push_back(S17);
		temp.push_back(S18);
		temp.push_back(S19);
		temp.push_back(S20);
		temp.push_back(S21);
		temp.push_back(S22);
		temp.push_back(S23);
		temp.push_back(S24);
		for (int i = temp.size() - 1; i >= 0; i--)
		{
			if (temp[i] == " ") temp.pop_back();
			else break;
		}
		if (temp.size() == 0) return;
		mcq_box_locator.resize(temp.size());
		for (int i = 0; i < temp.size(); i++)
		{
			ProcessInput(temp[i], type, header);
			input_types.push_back(type);
			if (header.size() > max_header_size)
			{
				max_header_size = header.size();
			}
			headers.push_back(header);
			order.push_back(to_char(type));
			if (type == 9)
			{
				vector<string> options;
				vector<string> header_option_pair;
				header_option_pair = split(header, ':', 1);
				header = header_option_pair[0];

				headers.pop_back();
				headers.push_back(header);

				options = split(header_option_pair[header_option_pair.size() - 1], ',');
				mcq_options.push_back(options);
				int header_num = i;
			}
			else
			{
				vector<string> T;
				mcq_options.push_back(T);
			}
		}
		Highlighted_box.resize(order.size(), -1);
	}
	void clear()
	{
		boxes.clear();
		temp.clear();
		headers.clear();
		input_types.clear();
		str_output.clear();
		int_output.clear();
		char_output.clear();
		float_output.clear();
		double_output.clear();
		order.clear();
		mcq_options.clear();
		mcqs_type_loc.clear();
		mcq_box_locator.clear();
		date_type_loc.clear();
		Highlighted_box.clear();
		spacing.clear();
		custom_input_size.clear();
		max_input_size = 24;
		max_header_size = 24;
	}
	vector<string> Input()
	{
		if (S.size() != 0)
		{
			return S;
		}
		return TakeInput();
	}

	void SetBorderChar(char c)
	{
		border_char = c;
	}
	void SetBorderChar(string S)
	{
		Decapitalize(S);
		if (S == "fancy" || S == "facny1" || S == "facny_1") border_char = '-';
		if (S == "facny2" || S == "facny_2") border_char = '=';
	}
	void SetSubmitText(const string& S, string color = "Default", string box_color = "white")
	{
		if (S.size() != 0)
			submit_text = S;
		submit_box_text_color = color;
		submit_box_color = box_color;
	}
	void SetFormLocation(int r, int c)
	{
		if (r >= 0 && c >= 0)
		{
			sr = r;
			sc = c;
		}
	}
	void SetTitle(string Title, string color = "Default")
	{
		title = Title;
		title_color = color;
	}
	void DisableFormBoundaryAndTitle()
	{
		boundry_and_title = false;
	}
	void EnableFormBoundaryAndTitle()
	{
		boundry_and_title = true;
	}
	vector<string> GetAllOutputs()
	{
		return S;
	}
	void GetOutput(int& Target, string Header)
	{
		for (int i = 0; i < headers.size(); i++)
		{
			if (headers[i] == Header && (order[i] == 'I'))
			{
				Target = stoi(S[i]);
				return;
			}
		}
	}
	void GetOutput(string& Target, string Header)
	{
		for (int i = 0; i < headers.size(); i++)
		{
			if (headers[i] == Header && (order[i] == 'S' || order[i] == 'P' || order[i] == 'X' || order[i] == 'M'))
			{
				Target = S[i];
				return;
			}
		}
	}
	void GetOutput(char& Target, string Header)
	{
		for (int i = 0; i < headers.size(); i++)
		{
			if (headers[i] == Header && order[i] == 'C')
			{
				Target = S[i][0];
				return;
			}
		}
	}
	void GetOutput(float& Target, string Header)
	{
		for (int i = 0; i < headers.size(); i++)
		{
			if (headers[i] == Header && order[i] == 'F')
			{
				Target = stof(S[i]);
				return;
			}
		}
	}
	void GetOutput(double& Target, string Header)
	{
		for (int i = 0; i < headers.size(); i++)
		{
			if (headers[i] == Header && order[i] == 'D')
			{
				Target = stod(S[i]);
				return;
			}
		}
	}
	void GetOutput(bool& Target, string Header)
	{
		for (int i = 0; i < headers.size(); i++)
		{
			if (headers[i] == Header && order[i] == 'B')
			{
				if (S[i] == "true")
					Target = true;
				else
					Target = false;
				return;
			}
		}
	}
	void SetBorderColor(string color)
	{
		border_color = color;
	}
	void AdminTests(int Password)
	{
		if (Password * Password != 1024) return;
		for (int i = 0; i < str_output.size(); i++)
		{
			cout << str_output[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < int_output.size(); i++)
		{
			cout << int_output[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < char_output.size(); i++)
		{
			cout << char_output[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < float_output.size(); i++)
		{
			cout << float_output[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < double_output.size(); i++)
		{
			cout << double_output[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < boolean_output.size(); i++)
		{
			cout << boolean_output[i] << " ";
		}
		cout << endl;
	}
	void SetHeaderColor(string color)
	{
		header_color = color;
	}
	void SetBoxColor(string color)
	{
		box_color = color;
	}
	void SetInputColor(string color)
	{
		input_color = color;
	}
	void SetFormMaxWidth(int width)
	{
		form_max_width = width;
	}
	void SetMaxInputSize(int size)
	{
		max_input_size = size;
	}
	void SetInputsPerLine(int inputs)
	{
		if (inputs > 0) inputs_per_line = inputs;
	}
	void SetInlineGap(int gap)
	{
		if (gap >= 0) ColumnGap = gap;
	}
	bool SetCustomInputSize(vector<int> InputSizes)
	{
		if (InputSizes.size() != headers.size()) return false;
		custom_input_size = InputSizes;
		return true;
	}
	void SetFillColor(string color, char fill_char = -37)
	{
		fill_color = color;
		this->fill_char = fill_char;
	}
};
class color
{
public:
	string black;
	string blue;
	string darkgreen;
	string lightblue;
	string red;
	string purple;
	string yellow;
	string offwhite;
	string grey;
	string navy;
	string green;
	string cyan;
	string lightred;
	string pink;
	string lightyellow;
	string white;

	color()
	{
		black = ":black";
		blue = ":blue";
		darkgreen = ":darkgreen";
		lightblue = ":lightblue";
		red = ":red";
		purple = ":purple";
		yellow = ":yellow";
		offwhite = ":offwhite";
		grey = ":grey";
		navy = ":navy";
		green = ":green";
		cyan = ":cyan";
		lightred = ":lightred";
		pink = ":pink";
		lightyellow = ":lightyellow";
		white = ":white";
	}
};
class text
{
public:
	string txt;
	int row;
	int col;
	string color;
	int underline;
	string underline_color;


	text(string Text = "None", int start_row = 0, int start_col = 0, string text_color = "default", int Underline = 0, string Underline_color = "default")
	{
		txt = Text;
		row = start_row;
		col = start_col;
		color = text_color;
		underline = Underline;
		underline_color = Underline_color;
	}
	void Set(string Text = "None", int start_row = 0, int start_col = 0, string text_color = "default", int Underline = 0, string Underline_color = "default")
	{
		txt = Text;
		row = start_row;
		col = start_col;
		color = text_color;
		underline = Underline;
		underline_color = Underline_color;
	}
	void Display()
	{
		gotoRowCol(row, col);
		ChangeColor(color);
		cout << txt;
		ChangeColor("default");

		if (underline == 1)
		{
			gotoRowCol(row + 1, col);
			ChangeColor(underline_color);
			PrintNTimes(to_character(196), txt.size());
			ChangeColor("default");
		}
		else if (underline == 2)
		{
			gotoRowCol(row + 1, col);
			ChangeColor(underline_color);
			PrintNTimes(to_character(205), txt.size());
			ChangeColor("default");
		}
	}
	void Remove()
	{
		gotoRowCol(row, col);
		PrintNTimes(' ', txt.size());
		if (underline)
		{
			gotoRowCol(row + 1, col);
			PrintNTimes(' ', txt.size());
		}
	}
};
class box
{
public:
	int sr;
	int sc;
	int width;
	int height;
	char border;
	char fill;
	string str_color;
	string border_color;
	string fill_color;
	string str;
	string desc;
	bool multiline;
	bool middle_allign;

	box()
	{
		sr = 0;
		sc = 0;
		width = 5;
		height = 3;
		border = '-';
		fill = ' ';
		str = "None";
		fill = ' ';
		str_color = "white";
		border_color = "white";
		fill_color = "black";
		desc = "undefined";
		multiline = false;
		middle_allign = false;
	}
	box(string Desc, int Start_Row, int Start_Col, int Width, int Height, char Border, string Border_Color, string Str, string Str_Color = "White:Black", char Fill = ' ', string Fill_Color = "black")
	{
		sr = Start_Row;
		sc = Start_Col;
		width = Width;
		height = Height;
		border = Border;
		border_color = Border_Color;
		str = Str;
		str_color = Str_Color;
		fill = Fill;
		fill_color = Fill_Color;
		desc = Desc;
		multiline = false;
		middle_allign = false;
	}
	box(string Desc, int Start_Row, int Start_Col, int Width, int Height, char Border, string Border_Color, char Fill = ' ', string Fill_Color = "black", string Str = "None", string Str_Color = "White:Black")
	{
		sr = Start_Row;
		sc = Start_Col;
		width = Width;
		height = Height;
		border = Border;
		border_color = Border_Color;
		str = Str;
		str_color = Str_Color;
		fill = Fill;
		fill_color = Fill_Color;
		desc = Desc;
		multiline = false;
		middle_allign = false;
	}
	void Display()
	{
		if (str == "None") DisplayBox(sr, sc, width, height, border, border_color, fill, fill_color);
		else
		{
			if (multiline == false)
				DisplayBoxWithStr(sr, sc, width, height, border, str, str_color, border_color, fill, fill_color);
			else
				DisplayBoxWithMultilineStr(sr, sc, width, height, border, str, str_color, border_color, fill, fill_color, middle_allign);
		}
	}
	void Remove()
	{
		RemoveBox(sr, sc, width, height);
	}
	void MakeMultiline()
	{
		multiline = true;
	}
	void MiddleAllign()
	{
		middle_allign = true;
	}
};
class clickbox
{
public:
	int id;
	box b;
	clickbox(int Id, string Desc, int Start_Row, int Start_Col, int Width, int Height, char Border, string Border_Color, string Str, string Str_Color = "White:Black", char Fill = ' ', string Fill_Color = "black")
	{
		id = Id;
		b.sr = Start_Row;
		b.sc = Start_Col;
		b.width = Width;
		b.height = Height;
		b.border = Border;
		b.border_color = Border_Color;
		b.str = Str;
		b.str_color = Str_Color;
		b.fill = Fill;
		b.fill_color = Fill_Color;
		b.desc = Desc;
		b.desc = Desc;
	}
	clickbox(int Id, string Desc, int Start_Row, int Start_Col, int Width, int Height, char Border, string Border_Color, char Fill = ' ', string Fill_Color = "black", string Str = "None", string Str_Color = "White:Black")
	{
		id = Id;
		b.sr = Start_Row;
		b.sc = Start_Col;
		b.width = Width;
		b.height = Height;
		b.border = Border;
		b.border_color = Border_Color;
		b.str = Str;
		b.str_color = Str_Color;
		b.fill = Fill;
		b.fill_color = Fill_Color;
		b.desc = Desc;
	}
	/*clickbox(string Desc, int Start_Row, int Start_Col, int Width, int Height, char Border, string Border_Color, string Str, string Str_Color = "White:Black", char Fill = ' ', string Fill_Color = "black")
	{
		id = -1;
		b.sr = Start_Row;
		b.sc = Start_Col;
		b.width = Width;
		b.height = Height;
		b.border = Border;
		b.border_color = Border_Color;
		b.str = Str;
		b.str_color = Str_Color;
		b.fill = Fill;
		b.fill_color = Fill_Color;
		b.desc = Desc;
		b.desc = Desc;
	}
	clickbox(string Desc, int Start_Row, int Start_Col, int Width, int Height, char Border, string Border_Color, char Fill = ' ', string Fill_Color = "black", string Str = "None", string Str_Color = "White:Black")
	{
		id = -1;
		b.sr = Start_Row;
		b.sc = Start_Col;
		b.width = Width;
		b.height = Height;
		b.border = Border;
		b.border_color = Border_Color;
		b.str = Str;
		b.str_color = Str_Color;
		b.fill = Fill;
		b.fill_color = Fill_Color;
		b.desc = Desc;
	}*/

	//clickbox(box Box, int Id, string Desc="undefined")
	//{
	//	id = Id;
	//	b = Box;
	//	b.desc = Desc;

	//}
	void Display()
	{
		b.Display();
	}
	void Remove()
	{
		b.Remove();
	}
	bool IsInBox(int r, int c)
	{
		if (r >= b.sr && r <= b.sr + b.height && c >= b.sc && c <= b.sc + b.width) return true;
		return false;
	}
};
class screen
{
private:
	int lcr, lcc;

	void GetAndUpdateClick()
	{
		getRowColbyLeftClick(lcr, lcc);
	}
	int GetClickedId()
	{
		for (int i = 0; i < ClickBoxes.size(); i++)
		{
			if (ClickBoxes[i]->IsInBox(lcr, lcc)) return ClickBoxes[i]->id;
		}
		return -1;
	}
	string GetClickedDesc()
	{
		for (int i = 0; i < ClickBoxes.size(); i++)
		{
			if (ClickBoxes[i]->IsInBox(lcr, lcc)) return ClickBoxes[i]->b.desc;
		}
		return "Box Not Found!";
	}
public:
	vector<box*> Boxes;
	vector<clickbox*> ClickBoxes;
	vector<text*> Text;
	screen()
	{
		lcr = -1;
		lcc = -1;
	}
	void AddBox(box& B)
	{
		Boxes.push_back(&B);
	}
	void AddClickBox(clickbox& CB)
	{
		ClickBoxes.push_back(&CB);
	}
	void AddText(text& T)
	{
		Text.push_back(&T);
	}
	void RemoveText(int index)
	{
		Text.erase(Text.begin() + index);
	}
	void Display()
	{
		for (int i = 0; i < Boxes.size(); i++) Boxes[i]->Display();
		for (int i = 0; i < ClickBoxes.size(); i++) ClickBoxes[i]->Display();
		for (int i = 0; i < Text.size(); i++) Text[i]->Display();
	}
	void Remove()
	{
		for (int i = 0; i < Boxes.size(); i++) Boxes[i]->Remove();
		for (int i = 0; i < ClickBoxes.size(); i++) ClickBoxes[i]->Remove();
		for (int i = 0; i < Text.size(); i++) Text[i]->Remove();
	}
	int GetClickBoxId()
	{
		if (ClickBoxes.size() == 0) return -1;
		int id;
		while (true)
		{
			GetAndUpdateClick();
			id = GetClickedId();
			if (id != -1) break;
		}
		return id;
	}
	string GetClickBoxDesc()
	{
		if (ClickBoxes.size() == 0) return "Box Not Found!";
		string Desc;
		while (true)
		{
			GetAndUpdateClick();
			Desc = GetClickedDesc();
			if (Desc != "Box Not Found!") break;
		}
		return Desc;
	}
	void RemoveClickBox(int id)
	{
		for (int i = 0; i < ClickBoxes.size(); i++)
		{
			if (ClickBoxes[i]->id == id)
			{
				ClickBoxes.erase(ClickBoxes.begin() + i);
				return;
			}
		}
	}
	void RemoveClickBox(string Desc)
	{
		for (int i = 0; i < ClickBoxes.size(); i++)
		{
			if (ClickBoxes[i]->b.desc == Desc)
			{
				ClickBoxes.erase(ClickBoxes.begin() + i);
				return;
			}
		}
	}
	void RemoveBox(int index)
	{
		if (index < 0 || index >= Boxes.size()) return;
		Boxes.erase(Boxes.begin() + index);
	}
	void RemoveBox(string Desc)
	{
		for (int i = 0; i < Boxes.size(); i++)
		{
			if (Boxes[i]->desc == Desc)
			{
				Boxes.erase(Boxes.begin() + i);
				return;
			}
		}
	}
};
