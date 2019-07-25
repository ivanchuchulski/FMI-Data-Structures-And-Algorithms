#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <forward_list>

using std::cout;
using std::cin;


int main() {
	
	//making streams faster
	std::ios_base::sync_with_stdio(false);

	unsigned N;
	std::string stone_text;
	std::stack<int> path;
	std::forward_list<int> output;

	cin >> N;
	cin.get();	//in order to get the getline for the string

	for (size_t i = 0; i < N; i++)
	{
		std::getline(cin, stone_text, '\n');
		int number_label = 0;
		char first_character = stone_text[0];

		stone_text.erase(0, stone_text.find_first_of(' ', 0));		//erasing the words
		number_label = std::stoi(stone_text);						//creating the value
			
		switch (first_character)
		{
		case 'w':
		{
			path.push(number_label);
			break;
		}

		case 'g' :
		{
			if (number_label > path.size() || number_label < 0)			//!! error
				;
			
			int to_insert = 0;	//!! may overflow !!, have to ask
			for (size_t i = 0; i < number_label; i++)
			{
				to_insert += path.top();
				path.pop();
			}

			path.push(to_insert);
			break;
		}

		case 'b' :
		{
			if (number_label > path.size() || number_label < 0)			//!! error
				;

			int to_insert = path.top();
			path.pop();

			for (size_t i = 1; i < number_label; i++)
			{
				if (path.top() > to_insert)
					to_insert = path.top();

				path.pop();
			}
			
			path.push(to_insert);
			break;
		}
		default:
			break;
		}

		stone_text.clear();
	}

	//putting the path in a list to correctly print it
	while (!path.empty())
	{
		output.push_front(path.top());
		cout << path.top() << " -> ";
		path.pop();
	}

	cout << '\n';

	//printing the path
	for (int& i : output)
		cout << i << ' ';

	std::system("pause");
	return 0;
}