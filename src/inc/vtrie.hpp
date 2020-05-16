#ifndef PMT_VTRIE_H
#define PMT_VTRIE_H

#include <vector>
#include <map>

class VTrie
{
private:
    Node *root;
    
public:
    VTrie();
    ~VTrie();

    bool insert(std::string key, double value);
    bool update(std::string key, double value);
    bool delet(std::string key);
    double select(std::string key);
    double select(std::string rootHash, std::string key);
    std::string getRoot();
};

#endif