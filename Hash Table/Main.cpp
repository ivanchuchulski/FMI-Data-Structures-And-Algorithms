#include <iostream>

#include "HashTable.hpp"

using std::cout;
using std::cin;


int main() {


	{
		fmi::HashTable table1(7);

		fmi::Node n1{ 1, "1" };
		fmi::Node n2{ 2, "11" };
		fmi::Node n3{ 3, "111" };
		fmi::Node n11{ 11, "1" };

		table1.InsertItem(n1);
		table1.InsertItem(n2);
		table1.InsertItem(n3);
		table1.InsertItem(n11);

		table1.Delete(n1);

		fmi::HashTable copy_table(table1);
		
	}




	std::system("pause");
	return 0;
}