#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <iostream>
using namespace std;

template<typename ValueType>
class Trie
{
public:
    Trie()
    {
        m_head = new Node;
        m_head->m_prev = nullptr;
        m_head->m_key = "";
        m_head->m_vectorValues = {};
        m_head->m_nextNodes = {};
    }
    ~Trie()
    {
        cleanUp(m_head);
    }
    void reset()
    {
        cleanUp(m_head);
        m_head = new Node;
    }
    void insert(const std::string& key, const ValueType& value)
    {
        bool found = true;
        Node* p = m_head;
        unsigned long key_pos = 0;
        while (key_pos < key.size() && found) //iterate through the key
        {
            found = false;
            for (int i = 0; i < p->m_nextNodes.size(); i++) //move through the nodes
            {
                unsigned long nodeSize = p->m_nextNodes[i]->m_key.size();
                if (key.substr(key_pos, nodeSize) == p->m_nextNodes[i]->m_key)
                {
                    //cout << "found children! at " << key.at(key_pos) << endl;
                    p = p->m_nextNodes[i];
                    key_pos += nodeSize;
                    found = true;
                    break;
                }
            }
        }
        if (key_pos < key.size()) //you still have part of the key left but no nodes, so create new nodes and add them to the trie
        {
            while (key_pos < key.size())
            {
                Node* x = new Node;
                x->m_key = key.at(key_pos);
                x->m_prev = p;
                
                p->m_nextNodes.push_back(x);
                p = x;
                
                key_pos++;
            }
        }
        p->m_vectorValues.push_back(value);
        //print(m_head);
    }
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const
    {
        vector<ValueType> returns = {};
        Node* p = m_head; //start at the root node
        int key_pos = 0;
        
        while (key_pos < key.size()) //while you haven't reached the end of the key
        {
            if (key_pos == key.size()-1 && exactMatchOnly == false) //if the mismatch is the last node, insert all of their values
            {
                for (int i = 0; i < p->m_nextNodes.size(); i++)
                {
                    for (int j = 0; j < p->m_nextNodes[i]->m_vectorValues.size(); j++)
                    {
                        ValueType k = p->m_nextNodes[i]->m_vectorValues[j];
                        returns.push_back(k);
                    }
                }
                break;
            }
            int og_key_pos = key_pos;
            if (exactMatchOnly == false && key_pos > 0) //if its potentially a snip, insert non-snips for each of its children
            {

                for (int i = 0; i < p->m_nextNodes.size(); i++) //find with true match and changed key
                {
                    unsigned long nodeSize = p->m_nextNodes[i]->m_key.size();
                    if (key.substr(key_pos, nodeSize) != p->m_nextNodes[i]->m_key) //if the key isn't a mismatch
                    {
                        string temp_key = key;
                        temp_key.replace(key_pos, nodeSize, p->m_nextNodes[i]->m_key);
                        //cout << temp_key << " " << key << endl;
                        vector<ValueType> temp_returns = find(temp_key, true);
                        //for (int i = 0; i < temp_returns.size(); i++)
                            //cout << temp_returns[i] << " ";
                        //cout << endl;
                        returns.insert(returns.end(), temp_returns.begin(), temp_returns.end());
                    }
                }
            }

            for (int i = 0; i < p->m_nextNodes.size(); i++) //iterate through the children
            {
                unsigned long nodeSize = p->m_nextNodes[i]->m_key.size();
                if (key.substr(key_pos, nodeSize) == p->m_nextNodes[i]->m_key) //if the values match, keep going
                {
                    p = p->m_nextNodes[i];
                    key_pos += nodeSize;
                    break;
                }
            }
            if (og_key_pos == key_pos) //if you didn't move, break the loop
                break;
        }
        if (key_pos == key.size())
        {
            for (int i = 0; i < p->m_vectorValues.size(); i++) //if you reached the end, insert all of its values
            {
                returns.push_back(p->m_vectorValues[i]);
            }
        }
        return returns;
    }

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    
private:
    struct Node
    {
        vector<Node*> m_nextNodes;
        Node* m_prev;
        string m_key;
        vector<ValueType> m_vectorValues;
    };
    void cleanUp(Node* p)
    {
        if (p == nullptr)
        {
            return;
        }
        for (int i = 0; i < p->m_nextNodes.size(); i++)
        {
            /*
            cout << p->m_nextNodes[i]->m_key << " ";
            for (int j = 0; j < p->m_nextNodes[i]->m_vectorValues.size(); j++)
            {
                cout << "Node " << p->m_nextNodes[i]->m_key << " has " << p->m_nextNodes[i]->m_vectorValues.size() << " values." << endl;
                cout << p->m_nextNodes[i]->m_vectorValues[j] << " ";
           }
            cout << endl;
             */
            cleanUp(p->m_nextNodes[i]);
        }
        delete p;
    }
    void print(Node* p)
    {

        if (p == nullptr)
        {
            return;
        }
        for (int i = 0; i < p->m_nextNodes.size(); i++)
        {
            
             //cout << p->m_nextNodes[i]->m_key << " ";
             for (int j = 0; j < p->m_nextNodes[i]->m_vectorValues.size(); j++)
             {
             //cout << "Node " << p->m_nextNodes[i]->m_key << " has " << p->m_nextNodes[i]->m_vectorValues.size() << " values." << endl;
                 //cout << &p->m_nextNodes[i]->m_vectorValues[j] << " ";
             }
             //cout << endl;
            print(p->m_nextNodes[i]);
        }
    }
    Node* m_head;
};

#endif // TRIE_INCLUDED
