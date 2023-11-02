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
//visualisation
}

vector < vector < string > > Follow_k(vector < pair < string, string >> Rules, int k)
{
//function follow_k
//visualisation
}

vector < vector < char > > LL_1(vector < vector < string > > first, vector < vector < string > > follow)
{

//visualisation
}

//function sequenceOfRules
//Tree

//???
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
vector < vector < string > > follow = Follow_k(Rules, k);



return 0;
}
