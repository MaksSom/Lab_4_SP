#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

vector < vector <string> > rewriteRules(string file_text)
{
//create a vector of rules
// {A, A, B}
// {A, num, +, A}
}

vector < vector < string > > First_k(vector < vector <string> > Rules, int k)
{
//function first_k
//visualisation
// {A, ......}
// {B, ......}
}

vector < vector < string > > Follow_k(vector < pair < string, string >> Rules, int k)
{
//function follow_k
//visualisation
// {A, ......}
// {B, ......}
}

vector < vector < char > > LL_1(vector < vector < string > > first, vector < vector < string > > follow)
{
//visualisation
//{A, num, 2}
//{V, *, 6}
}

vector <int> sequenceOfRules()
{
//function sequenceOfRules
//
//Tree
}

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
