#include"interface.h"
int main()
{
	form F("Str:Name","int:Age","Pass:Password","Str:Email");
	F.Input();
	return 0;
}