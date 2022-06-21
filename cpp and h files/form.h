#pragma once
#include"extrautilities.h"

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
	int max_header_size;
	int header_display_type;
	char border_char;

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
			cout << header;
		}
		else if (header_display_type == 2)
		{
			c = c + (max_header_size - header.length()) / 2;
			gotoRowCol(r, c);
			cout << header;
		}
	}
	void RemoveHeader(int r, int c)
	{
		gotoRowCol(r, c);
		PrintNTimes(' ', max_header_size);
	}
	void DisplayBoxWithSC(int r, int c, int width, int height, char border_char,string text=" ")
	{
		if (text == " ")
		{
			if (border_char == '=')
			{
				DisplayFancyBox(r, c, width, height, 1);
			}
			else if (border_char == '-')
			{
				DisplayFancyBox(r, c, width, height, 0);
			}
			else
			{
				DisplayBox(r, c, width, height, border_char);
			}
		}
		else
		{
			if (border_char == '=')
			{
				DisplayFancyBoxWithStr(r, c, width, height, 1,text);
			}
			else if (border_char == '-')
			{
				DisplayFancyBoxWithStr(r, c, width, height, 0,text);
			}
			else
			{
				DisplayBoxWithStr(r, c, width, height, border_char,text);
			}
		}
	}
	void DisplayElement(string header, int type, int r, int c,int N)
	{
		switch (type)
		{
		case 1:
		case 2:
		case 4:
		case 5:
		case 7:
			DisplayBoxWithSC(r + 1, c, max_input_size + 2, 3, border_char);
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
			DisplayBoxWithSC(r + 1, c + (max_input_size - 3), 3, 3, border_char);
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c + (max_input_size - 3)), pair<int, int>(3, 3)));
			gotoRowCol(r + 2, c + (max_input_size - 3)+4);
			cout << "No";
			break;
		case 8:
			if (max_input_size < 15) max_input_size = 15;
			DisplayBoxWithSC(r + 1, c, 4, 3, border_char);
			DisplayBoxWithSC(r + 1, c+5, 4, 3, border_char);
			DisplayBoxWithSC(r + 1, c + 10, 4, 3, border_char);
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c), pair<int, int>(4, 3)));
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c+5), pair<int, int>(4, 3)));
			boxes.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c+10), pair<int, int>(4, 3)));
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
				mcq_box_locator[N].push_back(pair<int, int>(boxes.size()-1,i));
				cc +=  mcq_options[N][i].size() + 3;
			}
			if (cc > form_max_width) form_max_width = cc;
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
	void Display()
	{
		if (boundry_and_title)
		{
			sr += 6;
			sc += 2;
			for (int i = 0; i < headers.size(); i++)
			{
				DisplayElement(headers[i], input_types[i], sr + (5 * i), sc, i);
			}
			DisplaySubmitButton(5 * headers.size() + sr, sc);
			sr -= 6;
			sc -= 2;

			//Title
			DisplayFancyBoxWithStr(sr, sc, form_max_width + 3, 5, 1, title, title_color);

			//Border
			DisplayFancyBox(sr, sc, form_max_width + 3, 5 * (headers.size() + 2) + 2, 1);

			//Title-Border Integration
			gotoRowCol(sr + 4, sc + form_max_width + 2);
			cout << to_character(185);
			gotoRowCol(sr + 4, sc);
			cout << to_character(204);
		}
		else
		{
			for (int i = 0; i < headers.size(); i++)
			{
				DisplayElement(headers[i], input_types[i], sr + (5 * i), sc, i);
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
		for (int i = 0; i < S.size(); i++)
		{
			r = 5 * i + sr;
			c = sc;
			if ((order[i]=='X' && !IsValidDate(S[i])) || S[i].size() == 0)
			{
				Warning = true;
				if (header_display_type == 1)
				{
					gotoRowCol(r, c+headers[i].size()+1);
					cout << "!";
				}
				else if (header_display_type == 2)
				{
					c = c + (max_header_size - headers[i].length()) / 2;
					gotoRowCol(r, c+1 + headers[i].size());
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
		for (int i = 0; i < S.size(); i++)
		{
			r = 5 * i + sr;
			c = sc;
			if ((order[i]=='X' && IsValidDate(S[i])) || S[i].size() != 0)
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
			if (S.size() == 1 && S[0] == '-' && c=='0') return false;
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
				cout << c;
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
				cout << c;
				return 1;
			}
		}
	}
	void Highlight(int box_num, string text="")
	{
		int style;
		if (border_char == '-') style = 0;
		else if (border_char == '=') style = 1;
		else style = -1;
		if (style >= 0)
		{
			if (text != "")
			{
				DisplayFancyBoxWithStr(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, style,text,"YELLOW","GREEN");
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
				DisplayBoxWithStr(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, border_char,text, "YELLOW", "GREEN");
			}
			else
			{
				DisplayBox(boxes[box_num].first.first, boxes[box_num].first.second, boxes[box_num].second.first, boxes[box_num].second.second, border_char,"GREEN");
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
						UnHighlight(Highlighted_box[current_header],S[current_header]);
					}
					S[current_header] = mcq_options[current_header][temp];
					Highlight(current_box, S[current_header]);
					Highlighted_box[current_header] = current_box;
					continue;
				}
				if (current_type == 8)
				{
					gotoRowCol(boxes[current_box].first.first + 1, boxes[current_box].first.second + 1 + (S[current_header][8+HeaderToDateBoxNum(current_box)-1]-'0'));
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
									cout << "*";
								}
								else
								{
									cout << cc;
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
			DisplayFancyBoxWithStr(r + 1, c, submit_text.size() + 2, 3, 1, submit_text,submit_box_text_color);
		}
		else if (border_char == '-')
		{
			DisplayFancyBoxWithStr(r + 1, c, submit_text.size() + 2, 3, 0, submit_text, submit_box_text_color);

		}
		else
		{
			DisplayBoxWithStr(r + 1, c, submit_text.size() + 2, 3, border_char, submit_text, submit_box_text_color);
		}
		submit_box = pair<pair<int, int>, pair<int, int>>(pair<int, int>(r + 1, c), pair<int, int>(submit_text.size() + 2, 3));
	}
	void RemoveSubmitButton()
	{
		int r, c, w,h;
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

	void set(string S1, string S2 = " ", string S3 = " ", string S4 = " ", string S5 = " ", string S6 = " ", string S7 = " ", string S8 = " ", string S9 = " ", string S10 = " ", string S11 = " ", string S12 = " ", string S13=" ", string S14 = " ", string S15 = " ", string S16 = " ", string S17 = " ", string S18 = " ", string S19 = " ", string S20 = " ", string S21 = " ", string S22 = " ", string S23 = " ", string S24 = " ")
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
		max_input_size = 16;
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
	void SetSubmitText(const string &S,string color="Default")
	{
		if (S.size() != 0)
			submit_text = S;
		submit_box_text_color = color;
	}
	void SetFormLocation(int r, int c)
	{
		if (r >= 0 && c >= 0)
		{
			sr = r;
			sc = c;
		}
	}
	void SetTitle(string Title,string color="Default")
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
			if (headers[i] == Header && (order[i]=='I'))
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
			if (headers[i] == Header && (order[i] == 'S'|| order[i] == 'P'|| order[i] == 'X' || order[i] == 'M'))
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
};

