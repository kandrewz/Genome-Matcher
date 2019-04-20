#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
    int m_sequenceLength;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
    m_sequenceLength = m_sequence.size();
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
    string temp_name = "";
    string temp_sequence = "";
    string curLine = "";
    int linenum = 0;
    if(!genomeSource)
    {
        cerr << "loading text file error" << endl;
        return false;
    }
    genomes.clear();
    while (getline(genomeSource, curLine)) //keep getting lines from the genomeSource file
    {
        if (curLine == "") //checking for empty line
            return false;
        if (linenum == 0 && curLine.at(0) != '>') //checking for first line is name line
            return false;
        linenum++;
        
        if (curLine.at(0) == '>') //name line
        {
            if (curLine == "") //contains no other characters in name line
                return false;
            if (temp_name != "")
            {
                if (temp_sequence == "") //checking for no empty base line
                    return false;
                genomes.push_back(Genome(temp_name, temp_sequence)); //pushing back genome object when reach new sequence
                temp_sequence = "" ;
            }
            temp_name = curLine.substr(1);
            if (temp_name == "") //checking name isn't empty
                return false;
        }
        else
        {
            for (int i = 0; i < curLine.size(); i++) //checking only A C G T N characters
            {
                char x = curLine.at(i);
                switch(x)
                {
                    case 'A':
                    case 'C':
                    case 'G':
                    case 'T':
                    case 'N':
                        break;
                    case 'a':
                        curLine.at(i) = 'A';
                        break;
                    case 'c':
                        curLine.at(i) = 'C';
                        break;
                    case 'g':
                        curLine.at(i) = 'G';
                        break;
                    case 't':
                        curLine.at(i) = 'T';
                        break;
                    case 'n':
                        curLine.at(i) = 'N';
                        break;
                    default:
                        return false;
                }
            }
            temp_sequence += curLine; //makign sequence
        }
    }
    genomes.push_back(Genome(temp_name, temp_sequence)); //pushing back the last genome
    return true;  // This compiles, but may not be correct
}

int GenomeImpl::length() const
{
    return m_sequenceLength;  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_name;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position + length > m_sequenceLength) //extract substring of length length at position position
        return false;
    fragment = m_sequence.substr(position, length);
    return true;  // This compiles, but may not be correct
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
