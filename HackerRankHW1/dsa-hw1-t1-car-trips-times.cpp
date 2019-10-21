#include <iostream>
#include <cstdlib>		// for system()


struct CarTrip
{
	int start_hour;
	int start_minutes;
	int finish_hour;
	int finish_minutes;

	friend std::istream& operator>>(std::istream& inS, CarTrip& obj)
	{
		inS >> obj.start_hour >> obj.start_minutes >> obj.finish_hour >> obj.finish_minutes;

		return inS;
	}

	int TripMinutes()
	{
		int mins = 0;

		if (finish_hour < start_hour)
		{
			if (start_hour >= 12)
			{
				int corr_start_hour = start_hour - 12;
				int corr_finish_hour = finish_hour + 12;

				mins = (corr_finish_hour * 60 + finish_minutes) - (corr_start_hour * 60 + start_minutes);
			}

			else
			{
				int corr_finish_hour = finish_hour + 12 + 12;

				mins = (corr_finish_hour * 60 + finish_minutes) - (start_hour * 60 + start_minutes);
			}
		}

		else
		{
			mins = (finish_hour * 60 + finish_minutes) - (start_hour * 60 + start_minutes);

			if (mins < 0)
					mins += 60 * 24;
		}

		return mins;
	}

};

bool IsValidTrip(const CarTrip& trip)
{
	if (trip.start_hour < 0 || trip.start_hour >= 24)
		return false;

	else if (trip.finish_hour < 0 || trip.finish_hour >= 24)
		return false;

	else if (trip.start_minutes < 0 || trip.start_minutes >= 60)
		return false;

	else if (trip.finish_minutes < 0 || trip.finish_minutes >= 60)
		return false;

	//all checks have been passed
	else
		return true;
}

int FindMaxTrip(int a, int b, int c)
{
	int max = a > b ? a : b;

	return (c > max ? c : max);
}

int FindMinTrip(int a, int b, int c)
{
	int min = a < b ? a : b;

	return (c < min ? c : min);
}

void PrintHour(int minutes)
{
	int hours = minutes / 60;
	minutes %= 60;

	if (minutes <= 9)
		std::cout << hours << ":0" << minutes << '\n';

	else
		std::cout << hours << ':' << minutes << '\n';

}

int main() {

	CarTrip a, b, c;

	std::cin >> a >> b >> c;

	bool a_valid = IsValidTrip(a);
	bool b_valid = IsValidTrip(b);
	bool c_valid = IsValidTrip(c);

	//wrong input
	if (!a_valid || !b_valid || !c_valid)
	{
		std::cout << "0:00\n";
		std::cout << "0:00\n";

		system("pause");
		return 0;
	}

	int a_trip = a.TripMinutes();
	int b_trip = b.TripMinutes();
	int c_trip = c.TripMinutes();

	int longest = FindMaxTrip(a_trip, b_trip, c_trip);
	int shortest = FindMinTrip(a_trip, b_trip, c_trip);

	PrintHour(shortest);
	PrintHour(longest);

	system("pause");
	return 0;
}
