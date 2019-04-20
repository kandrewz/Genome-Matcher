//
//  GenomeTester.cpp
//  project 4
//
//  Created by Andrew  on 3/13/19.
//  Copyright © 2019 Andrew . All rights reserved.
//

#include <stdio.h>
#include "Genome.cpp"
#include <iostream>
#include <fstream> // needed to open files
using namespace std;

void somefunc()
{
    // Specify the full path and name of the gene data file on your hard drive.
    string filename = "/Users/Andrew/Documents/programming/cs32/project4/data/random.txt";
    // Open the data file and get a ifstream object that can be used to read its
    // contents.
    ifstream strm(filename);
    if (!strm)
    {
        cout << "Cannot open " << filename << endl;
        return; }
    vector<Genome> vg;
    bool success = Genome::load(strm, vg); // Load the data via the stream. if (success)
    if (success)
    {
        cout << "Loaded " << vg.size() << " genomes successfully:" << endl;
        for (int k = 0; k != vg.size(); k++)
        {
            cout << vg[k].name() << endl;
        }
    } else
        cout << "Error loading genome data" << endl;
} // destructor for ifstream closes the file

int main()
{
    somefunc();
    
}
