# Nibble Processing

```c++
std::string test = "test";

    nibble_t nibble_ = StringToNibble(test);
    std::cout << "Nibble: " << GetBytes(nibble_) << std::endl;

    buffer_t buffer_ = NibbleToBuffer(nibble_);
    std::cout << "Buffer: " << GetBytes(buffer_) << std::endl;

    nibble_t nibble_1_ = StringToNibble("testa");
    std::cout << "Nibble: " << GetBytes(nibble_1_) << std::endl;
    std::cout << "Matching: " << MatchingNibbleLength(nibble_, nibble_1_) << std::endl;
    std::cout << "Key Matching: " << DoKeysMatch(nibble_, nibble_1_) << std::endl;

    nibble_t hex_nibble_ = AddHexPrefix(nibble_1_, false);
    std::cout << "Add Hex Prefix: " << GetBytes(hex_nibble_) << std::endl;

    std::cout << "Is Terminating: " << IsTerminator(hex_nibble_) << std::endl;

    hex_nibble_ = RemoveHexPrefix(hex_nibble_);
    std::cout << "Remove Hex Prefix: " << GetBytes(hex_nibble_) << std::endl;

```