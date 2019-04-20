#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Trie.h" //SHOULD I HAVE THIS HERE
#include <unordered_map>
#include <map>
#include <algorithm>
#include "Genome.cpp"
using namespace std;


bool compareGenomeMatch(const GenomeMatch& a, const GenomeMatch& b)
{
    if (a.percentMatch == b.percentMatch)
    {
        return a.genomeName < b.genomeName;
    }
    else
        return a.percentMatch > b.percentMatch;
}
class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    struct GenomePositionPair
    {
        int genomeIndex;
        int position;
    };
    int m_minSearchLength;
    vector<Genome> m_collection;
    Trie<GenomePositionPair> m_index; //first int is position of genome in m_collection, second int is position of the sequence in that genome
    
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
    // This compiles, but may not be correct
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_collection.push_back(genome); //add the genome to your genome collection
    string genome_sequence;
    GenomePositionPair pair;
    for (int i = 0; i < genome.length() - m_minSearchLength + 1; i++) //for each of the substrings of minsearch length
    {
        genome.extract(i, m_minSearchLength, genome_sequence);
        //cout << genome_sequence << " " << "Genome_position: " << m_collection.size() << " " << "Position_in_genome: " << i << endl;
        pair.genomeIndex = m_collection.size()-1;
        pair.position = i;
        m_index.insert(genome_sequence, pair); //push them into the index trie
    }
    // This compiles, but may not be correct
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if (fragment.size() < minimumLength) return false;
    if (minimumLength < m_minSearchLength) return false;
    bool matchFound = false;
    
    vector<GenomePositionPair> gen_matches = m_index.find(fragment.substr(0, m_minSearchLength), exactMatchOnly); //finding a starting position
    //find all starting positions of valid fragments of minsearch length
    matches.clear();
    unordered_map<string, DNAMatch> matchMap;
    for (int i = 0; i < gen_matches.size(); i++) //for all the valid fragments
    {
        string sequenceCompare;
        int fragmentBound = fragment.size();
        int sequenceBound = m_collection[gen_matches[i].genomeIndex].length() - gen_matches[i].position;
        int totalBound = min(fragmentBound, sequenceBound); //find the bound of the sequence/fragment
        if (m_collection[gen_matches[i].genomeIndex].extract(gen_matches[i].position, totalBound, sequenceCompare))
            //if you can extract the fragment
        {
            bool snip = exactMatchOnly;
            bool validSequence = true;
            for (int j = 0; j < minimumLength && j < totalBound; j++) //keep checking until you reach minimum length
            {
                if (sequenceCompare.at(j) != fragment.at(j)) //checking for snips
                {
                    if (!snip) //if exactMatchOnly is false and theres a mismatch, set exactMatchOnly to true
                    {
                        snip = true;
                    }
                    else //if theres a mismatch, it isnt a valid sequence
                    {
                        validSequence = false;
                        break;
                    }
                }
            }
            if (validSequence) //you reached minimum length, so its a DNAmatch, insert it
            {
                matchFound = true;

                DNAMatch temp;
                temp.genomeName = m_collection[gen_matches[i].genomeIndex].name();
                temp.position = gen_matches[i].position;
                temp.length = minimumLength;
                for (int j = minimumLength; j < totalBound; j++) //keep increasing length until you reach the bound
                {
                    if (sequenceCompare.at(j) == fragment.at(j))
                    {
                        temp.length++;
                    }
                    else if (!snip)
                    {
                        temp.length++;
                        snip = false;
                    }
                    else break;
                }
                
                if (matchMap.find(temp.genomeName) == matchMap.end()) //add the match into an unordered map for O(1) change speed
                {
                    matchMap[temp.genomeName] = temp;
                }
                else
                {
                    if (temp.length > matchMap[temp.genomeName].length) //if you find one of longer length, change it
                    {
                        matchMap[temp.genomeName].length = temp.length;
                        matchMap[temp.genomeName].position = temp.position;
                    }
                    //already keeps one of earliest position by how algorithm works
                }
                matchFound = true;
            }
        }
    }
    for (auto x: matchMap) //push the mapMatches into matches, aka you are only pushing in the "best" match for each genome
    {
        matches.push_back(x.second);
    }
    return matchFound;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < m_minSearchLength) return false;
    results.clear();
    bool matchFound = false;
    int query_pos = 0;
    double total_queries = 0;
    string query_extract;
    vector<DNAMatch> matches;
    unordered_map<string, double> m_matches;
    for (int i = 0; i < m_collection.size(); i++)
    {
        m_matches[m_collection[i].name()] = 0;
    }
    while (query.extract(query_pos, fragmentMatchLength, query_extract)) //keep extracting fragments from the query of fragmentMatchLength
    {
        total_queries++;
        matches.clear();
        if (findGenomesWithThisDNA(query_extract, fragmentMatchLength, exactMatchOnly, matches)) //if you can find the query
        {
            matchFound = true;
            for (int i = 0; i < matches.size(); i++) //add the number of matches to a map for that o(1) look up time
            {
                string s = matches[i].genomeName ;
                m_matches[s] += 1;
            }
        }
        query_pos += fragmentMatchLength;
        query_extract = "";
    }
    double percentMatch;
    for (int i = 0; i < m_collection.size(); i++)
    {
        percentMatch = m_matches[m_collection[i].name()] / total_queries * 100; //find percentage of matches for each genome
        if (percentMatch >= matchPercentThreshold) //if its greater than the threshold, add it to the results
        {
            GenomeMatch temp;
            temp.genomeName = m_collection[i].name();
            temp.percentMatch = percentMatch;
            results.push_back(temp);
        }
    }
    sort(results.begin(), results.end(), compareGenomeMatch); //sort the results by percentage then name
    return matchFound;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
