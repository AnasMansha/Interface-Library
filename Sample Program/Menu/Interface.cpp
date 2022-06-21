#include "Interface.h"
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
	clickbox CB(0, "Copy Code", 10, 21, 19, 3, '-', "cyan", "Copy to clipboard","red");
	clickbox MM(1, "Main Menu", 12, 0, 16, 3, '-', "blue", "Main Menu","orange");
	clickbox EX(2, "Exit", 15, 0, 16, 3, '-', "blue", "Exit","orange");


	//clickbox AG(1,"Generate Another")
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
