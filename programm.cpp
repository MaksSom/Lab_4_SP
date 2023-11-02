#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

vector < pair < string, string > > rewriteRules(string file_text)
{
//create a vector of rules
}

vector < vector < string > > First_k(vector < pair < string, string >> Rules, int k)
{
//function first_k
}
  
int main()
{
ifstream file("Example.txt");

if(!file.is_open()) 
{
cout << "File can't be opened" << endl;
return 0;
}

string file_text;
for(string a; getline(file, a); )
{
  file_text += a + "\n";
}

vector < pair < string, string > > Rules = rewriteRules(file_text);
//cin k
vector < vector < string > > first = First_k(Rules, k);



return 0;
}
