#include <iostream> 
#include <string> 
#include <sstream> 
using namespace std; 
int main() 
{ 
	setlocale( LC_ALL,"Russian" ); 
	size_t K; string s, s1, word; 
	cout << "String:\n"; 
	getline(cin, s); cout << "K="; 
	cin >>K; stringstream words(s); 
	while (words >> word)
	{ 
		if (word.size()>K)
			s1+=word+" ";
	} 
	cout <<s1<<endl;
	system("pause");
	return 0; }