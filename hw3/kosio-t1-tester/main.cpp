// Пример
// Tester.exe program1.exe program2.exe *.in

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

typedef unsigned long long uint64;

uint64 freq;

class Stopwatch
{
private:
	uint64 freq;
	uint64 start;
public:
	Stopwatch()
	{
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		freq = li.QuadPart;
		Restart();
	}

	void Restart()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		start = li.QuadPart;
	}

	uint64 ElapsedMillis()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return 1000ULL * (li.QuadPart - start) / freq;
	}
} stopwatch;

void testFile(char * file, char * prog1, char * prog2)
{
	string sFile = file;
	string sProg1 = prog1;
	string sProg2 = prog2;

	string out1 = prog1;
	out1 += ".out";

	string out2 = prog2;
	out2 += ".out";

	string cmd1 = sProg1 + " < \"" + sFile + "\" >> " + out1;
	string cmd2 = sProg2 + " < \"" + sFile + "\" >> " + out2;

	uint64 time;

	system(string("echo " + sFile + " >> " + out1).c_str());

	stopwatch.Restart();
	system(cmd1.c_str());
	time = stopwatch.ElapsedMillis();

	system(string("echo " + to_string(time) + " ms >> " + out1).c_str());
	system(string("echo. >>" + out1).c_str());

	system(string("echo " + sFile + " >> " + out2).c_str());
	stopwatch.Restart();
	system(cmd2.c_str());
	time = stopwatch.ElapsedMillis();

	system(string("echo " + to_string(time) + " ms >> " + out2).c_str());
	system(string("echo. >>" + out2).c_str());
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Incorrect number of arguments (should be 3)" << endl;
		return 0;
	}

	char * prog1 = argv[1];
	char * prog2 = argv[2];
	char * ext = argv[3];

	string out1 = prog1;
	out1 += ".out";

	string out2 = prog2;
	out2 += ".out";

	DeleteFile(out1.c_str());
	DeleteFile(out2.c_str());

	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(ext, &data)) != INVALID_HANDLE_VALUE)
	{
		do 
		{
			testFile(data.cFileName, prog1, prog2);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	//system("pause");
	return 0;
}