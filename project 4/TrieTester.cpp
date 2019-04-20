//
//  TrieTester.cpp
//  
//
//  Created by Andrew  on 3/12/19.
//

#include <stdio.h>
#include "Trie.h"
#include <iostream>
using namespace std;
int main()
{
    Trie<int> tester;
    tester.insert("hit", 10);
    tester.insert("hit", 20);
    tester.insert("hit", 30);
    tester.insert("hip", 40);
    tester.insert("pit", 10);
    tester.insert("hat", 100);
    tester.reset();
    cout << "insert works" << endl;
    cout << endl;
    
    
    tester.insert("hit", 10);
    tester.insert("hit", 20);
    tester.insert("hit", 30);
    tester.insert("hip", 40);
    tester.insert("pit", 10);
    tester.insert("hat", 100);
    tester.insert("hop", 500);
    vector<int> t1 = tester.find("hit", true);
    cout << "t1 is: " ;
    for (int i = 0; i < t1.size(); i++)
    {
        cout << t1[i] << " " ;
    }
    cout << endl;
    vector<int> t2 = tester.find("hit", false);
    cout << "t2 is: " ;
    for (int i = 0; i < t2.size(); i++)
    {
        cout << t2[i] << " " ;
    }
    cout << endl;
    vector<int> t3 = tester.find("cat", false);
    cout << "next line should be 'nothing'" << endl;
    for (int i = 0; i < t3.size(); i++)
    {
        cout << t3[i] << " " ;
     }
    cout << "nothing" << endl;
    vector<int> t4 = tester.find("ha", true);
    cout << "t4 is: ";
    for (int i = 0; i < t4.size(); i++)
    {
        cout << t4[i] << " " ;
    }
    cout << endl;
    vector<int> t5 = tester.find("hattt", true);
    cout << "t5 is: ";
    for (int i = 0; i < t5.size(); i++)
    {
        cout << t5[i] << " " ;
    }
    cout << endl;
    vector<int> t6 = tester.find("hic", false);
    cout << "t6 is: ";
    for (int i = 0; i < t6.size(); i++)
    {
        cout << t6[i] << " " ;
    }
    cout << endl;
    cout << "find works" << endl;
    cout << endl;
}
