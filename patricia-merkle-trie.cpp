#include <iostream>
#include <boost/array.hpp>

#include "src/utils/nibbles.hpp"
#include "src/utils/hex.hpp"
#include "src/includes/alias.hpp"
#include "src/includes/batchdbop.hpp"
#include "src/includes/db.hpp"
#include "src/includes/vtrie.hpp"

void say_hello(){
    std::cout << "Hello, from patricia-merkle-trie!\n";
}

int main() {
    say_hello();

    boost::array<int, 4> arr = {{1,2,3,4}};
    std::cout << "hi" << arr[0] << std::endl;

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
