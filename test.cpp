// testr.cpp : Defines the entry point for the console application.
//


#include "profiler.h"


struct circular_buffer circ_buff;
int Level3Func1(int a)
{
	Sleep(a*1000);
	return 0;
}
int Level4Func1(int a)
{
	Sleep(a*1000);
	return 0;
}
int Level3Func2(int a)
{
	SP(Level4Func1) Level4Func1(a);EP(Level4Func1)
	SP(Level4Func2) Level4Func1(a);EP(Level4Func2)
	return 0;
}

int HelperFunc(int a)
{
	SP(Level3Func1) Level3Func1(a);  EP(Level3Func1)
	SP(Level3Func2) Level3Func2(a);  EP(Level3Func2)
	Sleep(a*1000);
	return 0;
}



//cout << #Tag << " " << (le##Tag.QuadPart - li##Tag.QuadPart)/TICKS_PER_MSEC << "msec \n"
int myfunc(int a)
{
	SP(Sleep)
	Sleep(a*1000);
	EP(Sleep)
	SP(HelperFunc) HelperFunc(a); EP(HelperFunc);
	return 0;
}

int main(int argc, char* argv[])
{
	PI

	SP(myfunc);
	myfunc(1);
	Sleep(1000);
	EP(myfunc);

	PP
	return 0;
}


