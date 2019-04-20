//
//  GenomeMatcherTester.cpp
//  project 4
//
//  Created by Andrew  on 3/13/19.
//  Copyright © 2019 Andrew . All rights reserved.
//

#include <stdio.h>
#include "GenomeMatcher.cpp"
using namespace std;

int main()
{
    vector<DNAMatch> matches;
    bool result;
    
    //own test cases
    {
    
    GenomeMatcher a(3);
    a.addGenome(Genome("Genome1", "ACTG"));
    a.addGenome(Genome("Genome2", "TCGACT"));
    a.addGenome(Genome("Genome3", "TCTCG"));
    

    result = a.findGenomesWithThisDNA("TCT", 3, false, matches); //standard false fragment
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = a.findGenomesWithThisDNA("ACG", 3, false, matches); //if mismatch is at end of fragment
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = a.findGenomesWithThisDNA("ACG", 3, true, matches); //standard true fragment
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = a.findGenomesWithThisDNA("CTC", 3, true, matches); //standard true fragment
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = a.findGenomesWithThisDNA("CGACT", 5, true, matches); //
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    cout << "working" << endl;
      
    }
    //carey test cases
    GenomeMatcher b(4);
    b.addGenome(Genome("Genome1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    b.addGenome(Genome("Genome2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    b.addGenome(Genome("Genome3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GAAG", 4, true, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GAATAC", 4, true, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GAATAC", 6, true, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GTATAT", 6, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GAATACG", 6, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = b.findGenomesWithThisDNA("GAAG", 3, true, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;

    matches.clear();
    result = b.findGenomesWithThisDNA("GAAG", 5, true, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    GenomeMatcher c(10);
    c.addGenome(Genome("yeti", "ACGTACGTAAAACCCCGGGGTTTTNANANANANA"));
    
    matches.clear();
    result = c.findGenomesWithThisDNA("AAAACCTCGGGGTTNN", 12, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = c.findGenomesWithThisDNA("AAAACCCCGGGGTTNN", 12, true, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    matches.clear();
    result = c.findGenomesWithThisDNA("AAAACCTCGGGGTTNN", 5, false, matches);
    cout << "result is : " << result << endl;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << matches[i].genomeName << " " << matches[i].position << " " << matches[i].length << endl;
    }
    cout << endl;
    
    //lucas test cases
    Trie<int> trie;
    trie.insert("hi", 1);
    trie.insert("hi", 2);
    trie.insert("ho", 3);
    trie.insert("hi", 4);
    trie.insert("ha", 5);
    trie.insert("ai", 6);
    bool match = false;
    vector<int> v;
    v = trie.find("ho", match);
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
    Genome g1("Genome 1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC");
    Genome g2("Genome 2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
    Genome g3("Genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA");
    GenomeMatcher gm(4);
    gm.addGenome(g1);
    gm.addGenome(g2);
    gm.addGenome(g3);
    result = gm.findGenomesWithThisDNA("GAAGGGTT", 4, true, matches);
    for (int i = 0; i < matches.size(); i++) {
        cout << matches[i].genomeName << " of length " << matches[i].length << " at position: " << matches[i].position << endl;
    }
    vector<GenomeMatch> results;
    Genome query("query", "GAAGGGTTTTTTCGGTAAAA");
    gm.findRelatedGenomes(query, 4, true, 0, results);
    for (int i = 0; i < results.size(); i++) {
        cout << results[i].genomeName << " with match percentage: " << results[i].percentMatch << endl;
    }
    return 0;

}


