#include <iostream>

using namespace std;

int main() {
	string word;
	cin >> word;
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] > 'a' and word[i] < 'z')
			cout << word[i] << endl;
	}
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] > 'à' and word[i] < 'ÿ')
			cout << word[i] << endl;
	}
	return 0;
}