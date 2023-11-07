#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>

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
  
    map<string, set<string>> First;

    for (const vector<string>& rule : Rules) {
        string nonTerminal = rule[0];
        string production = rule[1];
        if (isalpha(production[0]) && !isupper(production[0])) {
            First[nonTerminal].insert(production.substr(0, 1));
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (const vector<string>& rule : Rules) {
            string nonTerminal = rule[0];
            string production = rule[1];

            for (size_t i = 0; i < production.length(); ++i) {
                string symbol = production.substr(i, 1);

                if (!isupper(symbol[0])) {
                    // If it's a terminal, add it to First[nonTerminal]
                    if (First[nonTerminal].insert(symbol).second) {
                        changed = true;
                    }
                    break;
                }
                else {
                    // If it's a non-terminal, add First[symbol] to First[nonTerminal]
                    for (const string& firstSymbol : First[symbol]) {
                        if (firstSymbol != "ε") {
                            if (First[nonTerminal].insert(firstSymbol).second) {
                                changed = true;
                            }
                        }
                    }
                    if (!First[symbol].count("ε")) {
                        break;
                    }
                }
            }
        }
    }

    vector<set<string>> FirstSets;
    for (const vector<string>& rule : Rules) {
        string nonTerminal = rule[0];
        FirstSets.push_back(First[nonTerminal]);
    }

    for (size_t i = 0; i < FirstSets.size(); ++i) {
        string nonTerminal = "Non-Terminal " + to_string(i);
        cout << "first(" << nonTerminal << ") = {";

        int symbolIndex = 0;
        for (const string& symbol : FirstSets[i]) {
            cout << symbol;
            if (symbolIndex < FirstSets[i].size() - 1) {
                cout << ", ";
            }
            symbolIndex++;
        }

        cout << "}" << endl;
    }

    return FirstSets;
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
