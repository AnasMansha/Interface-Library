#include"form.h"
#include"menu.h"

class text
{
public:
	string txt;
	int row;
	int col;
	string color;
	int underline;
	string underline_color;
	

	text(string Text="None", int start_row = 0, int start_col = 0, string text_color = "default", int Underline = 0, string Underline_color = "default")
	{
		txt = Text;
		row = start_row;
		col  = start_col;
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

		if (underline==1)
		{
			gotoRowCol(row+1, col);
			ChangeColor(underline_color);
			PrintNTimes(to_character(196),txt.size());
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
			gotoRowCol(row+1, col);
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
	box(string Desc,int Start_Row, int Start_Col, int Width, int Height, char Border, string Border_Color, string Str, string Str_Color = "White:Black", char Fill=' ', string Fill_Color="black")
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
	box(string Desc,int Start_Row, int Start_Col, int Width, int Height, char Border, string Border_Color, char Fill = ' ', string Fill_Color = "black", string Str = "None", string Str_Color = "White:Black")
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
				DisplayBoxWithMultilineStr(sr, sc, width, height, border, str, str_color, border_color, fill, fill_color,middle_allign);
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
	void AddBox(box &B)
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
			if (Desc !="Box Not Found!") break;
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