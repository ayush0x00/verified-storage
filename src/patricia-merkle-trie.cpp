#include <iostream>
#include <boost/array.hpp>

#include "utils/nibbles.hpp"
#include "utils/hex.hpp"
#include "includes/alias.hpp"
#include "includes/batchdbop.hpp"
#include "includes/db.hpp"
#include "includes/vtrie.hpp"

void say_hello(){
    std::cout << "Hello, from patricia-merkle-trie!\n";
}

int main() {
    say_hello();

    boost::array<int, 4> arr = {{1,2,3,4}};
    std::cout << "hi" << arr[0] << std::endl;

    std::string
    DBConnection db_connection = DBConnection("/tmp/testdb");
    std::string value {"Test"};
    if (db_connection.GetStatus().ok()) {
        db_connection.Put(StringToBytes(StringToHex("123")), StringToBytes(StringToHex(value)));
        db_connection.Put(StringToBytes(StringToHex("456")), StringToBytes(StringToHex(value + "1")));
        std::vector<uint64_t> value_;
        value_ = db_connection.Get(StringToBytes(StringToHex("456")));
        std::cout << BytesToString(value_) << std::endl;
    }
}
