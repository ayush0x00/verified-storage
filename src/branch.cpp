#include "inc/branch.hpp"

#include <map>

#include "utils/hex.hpp"

Branch::Branch() {
    std::vector<uint64_t> vector;
    branches_.reserve(16);
}

Node Branch::FromBuffer(std::vector<std::vector<uint64_t>>& input) {
    input.resize(17);
    Branch node = Branch();
    // Todo Create template for slicing stl array slice it instead of looping
    for(std::string::size_type i = 0; i < input.size() - 1; i++) {
        node.SetBranch(i, input[i]);
    }
    node.SetValue(input[input.size()-1]);

    return node;
}

void Branch::SetBranch(const int loc, std::vector<uint64_t> input) {
    branches_[loc] = input;
}

std::vector<uint64_t> Branch::GetBranch(const int input) {
    auto branch_ = branches_[input];
    if(!branch_.empty() && branch_.size()) {
        return branch_;
    } else {
        return EmptyByte();
    }
}

std::vector<std::vector<uint64_t>> Branch::GetBranches() {
    return branches_;
}

std::vector<std::vector<uint64_t>> Branch::Raw() {
    std::vector<std::vector<uint64_t>> raw_;
    for(auto branch_ : branches_) {
        raw_.push_back(branch_);
    }
    raw_.push_back(value_);

    return raw_;
}

std::map<int, std::vector<uint64_t>> Branch::GetChildren() {
    std::map<int, std::vector<uint64_t>> children_;
    for(std::string::size_type i = 0; i <  16; i++) {
        auto branch_ = branches_[i];
        if(branch_.empty() && branch_.size()) {
            children_.insert(std::pair<int, std::vector<uint64_t>>(i, branch_));
        }
    }

    return children_;
}
