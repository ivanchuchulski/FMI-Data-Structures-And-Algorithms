#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

bool isValidLeft(int number)
{
	int lastnumber = number % 10;
	if (lastnumber - 2 < 0)
	{
		return false;
	}
	return true;
}

bool isValidRight(int number)
{
	int lastnumber = number % 10;
	if (lastnumber + 2 > 9)
	{
		return false;
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	queue<int>q;
	int n;
	cin >> n;

	if (n < 10)
	{
		for (int i = 1; i <= n; i++)
		{
			cout << i << " ";
		}
	}
	else
	{

		for (int i = 1; i < 10; i++)
		{
			q.push(i);
		}
		while (q.front() <= n)
		{

			if (isValidLeft(q.front()))
			{
				q.push(q.front() * 10 + (q.front() % 10 - 2));
			}
			if (isValidRight(q.front()))
			{
				q.push(q.front() * 10 + (q.front() % 10 + 2));
			}

			cout << q.front() << " ";
			q.pop();
		}
		system("pause");
		return 0;
	}
}