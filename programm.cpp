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

int findPos(vector < vector < string > > first, char a)
{
  for(int i = 0; i < first.size(); i++)
  {
    string b(1, a);
    //cout << "Checking " << first[i][0] << " " << " and " << b << " \n";
    if(first[i][0] == b)
      return i;
  }
  cout << a << endl;
  throw runtime_error("There are no first/follow for the character");
}

bool isTerminal(string a)
{
    return 'A' <= a.at(0) && a.at(0) <= 'Z' && a.size() == 1;
}

vector < string > getFirst(vector < vector < string > > first, string a)
{
      vector < string > res;
      if(isTerminal(a))
      {
          int i = 0;
          while(i < first.size())
          {
              if(first[i][0] == a)
                break;
              i++;
          }
          for(int j = 1; j < first[i].size(); j++)
            res.push_back(first[i][j]);
      }
      else
        res.push_back(a);

      return res;
}

vector < string > concan(vector < string > a, vector < string > b)
{
    vector < string > res;
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] != "eps")
            res.push_back(a[i]);
        else
            for(int j = 0; j < b.size(); j++)
                res.push_back(b[j]);
    }
    return res;
}

vector < vector < string > > LL_1(vector < vector < string > > first, vector < vector < string > > follow, vector < vector < string >> Rules)
{
//visualisation
//{A, num, 2}
//{V, *, 6}


// {A, A, B}
vector < vector < string > > ll1;

for(int i = 0; i < Rules.size(); i++)
{
    vector < string > res = {"eps"};
    for(int j = 1; j < Rules[i].size(); j++)
        res = concan(res, getFirst(first, Rules[i][j]));
    res = concan(res, getFirst(follow, Rules[i][0]));

    for(int j = 0; j < res.size(); j++)
        ll1.push_back({Rules[i][0], res[j], to_string(i+1)});
}

return ll1;
}


vector<int> sequenceOfRules(vector<vector<string>> ll1Table, string word, string startSymbol) {
//function sequenceOfRules
//
//Tree
    vector<int> sequence;

    stack<string> st;
    st.push("$"); 
    st.push(startSymbol);

    size_t wordIndex = 0;

    while (!st.empty()) {
        string stackTop = st.top();
        if (!isupper(stackTop[0])) {
            // Terminal on top of the stack
            if (stackTop == word.substr(wordIndex, stackTop.length())) {
                // Terminal matches, pop from stack and move to the next character in the word
                st.pop();
                wordIndex += stackTop.length();
            } else {
                sequence.clear();  // Clear the sequence as the current path is invalid
                break;
            }
        } else {
            // Non-terminal on top of the stack
            int row = findPos(ll1Table, stackTop[0]);
            int col = findPos(ll1Table[0], word[wordIndex]);
            int ruleNumber = stoi(ll1Table[row][col]);

            if (ruleNumber == 0) {
                // No production rule, mismatch
                sequence.clear();  // Clear the sequence as the current path is invalid
                break;
            } else {
                // Apply the production rule
                sequence.push_back(ruleNumber);

                // Pop non-terminal from the stack
                st.pop();

                // Push the right-hand side of the production rule onto the stack
                for (int i = ll1Table[ruleNumber][1].size() - 1; i > 0; i -= 2) {
                    string rhsSymbol = ll1Table[ruleNumber][1].substr(i - 1, 2);
                    st.push(rhsSymbol);
                }
            }
        }
    }

    return sequence;
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
