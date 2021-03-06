#include <iostream>
#include <string>
#include "HashMap.h";

using namespace std;

struct MyKeyHash {
	unsigned int operator()(const long& key) const
	{
		return key;
	}
};

int main()
{
	HashMap<long, string, MyKeyHash> map(10);
	map.put(13, "ala");

	map.print();
	cout << endl;

	map.put(23, "ola");

	map.print();
	cout << endl;

	map.remove(13);

	map.print();
	cout << endl;
}