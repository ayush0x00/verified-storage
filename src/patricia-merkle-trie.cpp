#include <iostream>
#include <boost/array.hpp>
#include <boost/variant.hpp>
// #include "utils/nibbles.hpp"
// #include "utils/hex.hpp"
// #include "core/alias.hpp"
// #include "core/constants.hpp"
// #include "core/db.hpp"
// #include "core/batchdbop.hpp"
// #include "core/vtrie.hpp"

void say_hello(){
    std::cout << "Hello, from patricia-merkle-trie!\n";
}

class Node {
    public:
        int number = 10;
};

class Leaf : public Node {};

class Branch : public Node {};

class Extension : public Node {};

enum NodeType {
    BLANK_NODE = 0,
    BRANCH_NODE = 1,
    EXTENSION_NODE = 2,
    LEAF_NODE = 3
};

int main() {
    say_hello();

    boost::array<int, 4> arr = {{1,2,3,4}};
    std::cout << "hi" << arr[0] << std::endl;

    boost::variant<Node, Branch, Extension, Leaf> test_;
    test_ = Leaf();
    std::cout << "Leaf: " << test_.which() << std::endl;
    std::cout << "Leaf: " << (test_.which() == LEAF_NODE) << std::endl;
    std::cout << "Leaf: " << test_.type().name() << std::endl;
    test_ = Branch();
    std::cout << "Branch: " << test_.which() << std::endl;
    std::cout << "Branch: " << (test_.which() == BRANCH_NODE) << std::endl;
    std::cout << "Branch: " << test_.type().name() << std::endl;
    test_ = Extension();
    std::cout << "Extension: " << test_.which() << std::endl;
    std::cout << "Extension: " << (test_.which() == EXTENSION_NODE) << std::endl;
    std::cout << "Extension: " << test_.type().name() << std::endl;
    test_ = Node();
    std::cout << "Node: " << test_.which() << std::endl;
    std::cout << "Node: " << (test_.which() == BLANK_NODE) << std::endl;
    std::cout << "Node: " << test_.type().name() << std::endl;
    // const std::string db_path_ {"/tmp/testdb"};
    // DBConnection db_connection = DBConnection(db_path_);
    // std::string value {"Test"};
    // if (db_connection.GetStatus().ok()) {
    //     db_connection.Put(StringToBytes(StringToHex("123")), StringToBytes(StringToHex(value)));
    //     db_connection.Put(StringToBytes(StringToHex("456")), StringToBytes(StringToHex(value + "1")));
    //     std::vector<uint64_t> value_;
    //     value_ = db_connection.Get(StringToBytes(StringToHex("456")));
    //     std::cout << BytesToString(value_) << std::endl;
    // }


}
