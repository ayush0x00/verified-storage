#include<iostream>
#include "Node.hpp"
#include "Leaf.hpp"
#include "Extension.hpp"
#include "Branch.hpp"
#include "VTrie.hpp"

VTrie::VTrie()
{
    // Create an empty node
    root = new Node::Node();
    // Todo: Add leveldb integration to store all the entries in database 
}

VTrie::~VTrie()
{
}

bool VTrie::insert(std::string key, double value) {

}

bool update(std::string key, double value) {

}

bool delet(std::string key) {

}

double select(std::string key) {

}

double select(std::string rootHash, std::string key) {

}

std::string getRoot() {

}