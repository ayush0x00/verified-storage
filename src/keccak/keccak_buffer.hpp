#ifndef PMT_KECCAK_BUFFER_T
#define PMT_KECCAK_BUFFER_T

#include "keccak.h"

#include "inc/alias.hpp"

class KeccakBuffer {
    private:
        Keccak keccak_;

    public:
        KeccakBuffer();
        KeccakBuffer(const Keccak::Bits bits=Keccak::Bits::Keccak256);

        buffer_t operator()(const buffer_t& input);
};

#endif