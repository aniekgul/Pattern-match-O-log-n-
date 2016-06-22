#include <fstream>
#include <iostream>
#include <map>
#include <string>
// add other includes if needed

using namespace std;

// complete this function
bool isSuffixOf (string smallString, string fullString) {
  //t n = fullString.length();
  //t k = smallString.length();
  //ol ret = 1;
  //r (int i=0; i < k && i < n; i++) {
  //if ( smallString[i] != fullString[n-k+i] ) { 
  //  ret = 0;
  //  break;
  //}
  //
  //turn ret;
  if (fullString.length() >= smallString.length()) {
        return (0 == fullString.compare (fullString.length() - smallString.length(), smallString.length(), smallString));
    } else {
        return false;
    }
}

class PatternMatchingDFA{
private:
  map<int, map<char, int> > transitions;
  string pattern;
  int States;
  map<char, int> distinct;

public:
  // complete this function
  // returns the integer m = the length of the pattern
  int length() {
    return pattern.length();
  }

  // complete this function
  // returns the number of pairwise distinct characters in the pattern
  int numberOfCharacters() {
    return distinct.size();
  }

  // implement this constructor
  PatternMatchingDFA(string& s) {
    //cout << "in constr" << endl;
    pattern = s;
    //cout << pattern << endl;
    States = pattern.length() + 1;
    for(int i = 0; i < States-1; i++) {
      if ( !distinct.count(pattern[i]) ) {
        distinct[pattern[i]] = 1;
      }
     }
     //cout << "size of distinct = " << distinct.size() << endl;
     for(int q = 0; q < States; q++) {
       for( map<char, int>::iterator it = distinct.begin(); it !=  distinct.end(); it++ ) {
         string x;
         if ( q > 0 ) { x = pattern.substr(0, q); }
         x.push_back((*it).first);
         int k = 0;
         int j = 1;
         string comp;
         //bool test = isSuffixOf(comp, x);
         while( j <= pattern.length() ) {
           comp = pattern.substr(0, j);
           if ( isSuffixOf(comp, x) ) {
             k = comp.length();
           }
           j++; 
         }
         transitions[q][(*it).first] = k;
       }
     }
     //cout << "done inin trans" << endl;
     printTrans();
     match();
  }
         
  void printTrans() {
    //cout << "in printtrans" << endl;
    ofstream outFile;
    outFile.open("a5delta.txt");
    for(int i = 0; i < States; i++) {
      for( map<char, int>::iterator it = distinct.begin(); it != distinct.end(); it++) {
        outFile << i << " " << (*it).first << " " << transitions[i][(*it).first] << endl;
      }
    }
    outFile.close();
  }

  void match() {
    ifstream inFile;
    inFile.open("a5text.txt");
    string text;
    char c;
    while ( inFile >> c ) {
      text.push_back(c);
    }
    inFile.close();
    ofstream outFile;
    outFile.open("a5matches.txt");
    int n = text.length();
    int q = 0;
    int m = this->length();
    for(int i = 0; i < n; i++) {
      q = this->transitions[q][text[i]];
      if ( q == m ) {
        outFile << i-(m-1) << endl;
      }
    }
    outFile.close();
  }
  // your code here
};

#ifndef TESTING
int main(int argc, char **argv){
  string s;
  ifstream inFile;
  inFile.open("a5pattern.txt");
  getline(inFile, s);
  inFile.close();
  //cout << "pattern = " << s << endl;
  PatternMatchingDFA k = PatternMatchingDFA(s);
  
  //cout << isSuffixOf("ab", "abab") << endl;

  return 0;
}
#endif
