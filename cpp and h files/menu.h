#pragma once
#include"extrautilities.h"
#define DEFAULT "Default"

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
			int total_width = (width * options_per_line)+(inline_gap*(options_per_line-1));
			gotoRowCol(row, max(column,column + (total_width - title.length()) / 2));
			ChangeColor(title_color);
			cout << title;
			ChangeColor(DEFAULT);
			gotoRowCol(row+1, column + (total_width - title.length()) / 2);
			ChangeColor(title_color);
			PrintNTimes(205, title.size());
			ChangeColor(DEFAULT);
			row = row + 3;
		}
		for (int i = 0; i < options.size(); i++)
		{
			

			DisplayBoxWithStr(row + (((i) / options_per_line) * 3), column + (i % options_per_line) * width + (i % options_per_line)* inline_gap, width, 3, border_char, options[i], "GREEN", "WHITE");
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
			while((GetKeyState(VK_LBUTTON) & 0x8000) != 0)
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
			mouse_input_start_point.second = c/2-(MaxOptionSize()/2);
			if (mouse_input_start_point.second < 0) mouse_input_start_point.second = 0;
		}
	}
	void SetTreeMouseInputDisplayStart(int console_row, int console_column, bool set_middle=false)
	{
		if (set_middle)
		{
			int r, c;
			GetConsoleSize(r, c);
			mouse_input_start_point.first = 0;
			mouse_input_start_point.second = c/2-(MaxOptionSize()/2);
			if (mouse_input_start_point.second < 0) mouse_input_start_point.second = 0;
			for (int i = 0; i < sub_menus.size(); i++)
			{
				sub_menus[i]->SetTreeMouseInputDisplayStart(console_row, console_column,true);
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
			SetTreeMouseInputDisplayStart(0, 0,true);
		}
	}
	int  Input(bool display=true)
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
		for (int i = sub_menus.size()-1; i >= 0; i--)
		{
			if(sub_menus[i]->temp_menu==false)
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
	void removesubmenu(int amount=1)
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

