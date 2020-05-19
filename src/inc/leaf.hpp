#ifndef PMT_LEAF_NODE_H
#define PMT_LEAF_NODE_H

#include <array>

#include "node.hpp"

class Leaf : public Node {
    private:
        std::vector<uint> nibbles_;

    public:
        // Leaf();
        // ~Leaf();

        Leaf(std::vector<uint> nibbles, std::vector<uint64_t> value);

        static std::vector<uint> EncodeKey(const std::vector<uint>& input);
        static std::vector<uint> DecodeKey(const std::vector<uint>& input);
        
        std::vector<uint> GetKey();
        void SetKey(std::vector<uint> input);
        std::vector<uint> EncodedKey();

        std::vector<std::vector<uint64_t>> Leaf::Raw();
};

#endif