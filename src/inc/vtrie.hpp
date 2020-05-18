#ifndef PMT_VTRIE_H
#define PMT_VTRIE_H

#include <stack>

#include "db.hpp"
#include "node.hpp"
#include "path.hpp"
#include "batchdbop.hpp"

class VTrie {
    private:
        std::vector<uint64_t> EMPTY_TRY_ROOT_;
        DBConnection db_;
        std::vector<uint64_t> root_;
        // Todo Add Semaphore for locking the resource under processing

        Node LookupNode(std::vector<std::vector<uint64_t>> node);
        void PutNode(Node node);
        void FindValueNodes(); // Todo need to check what should be passed as parameter
        void FindDbNodes(); // Todo need to check what should be passed as parameter
        void UpdateNode(std::vector<uint64_t> key, std::vector<uint64_t> value, std::vector<uint> key_reminder, Node stack[]);
        void WalkTree(std::vector<uint64_t> root); // Todo need to check what should be passed as parameter
        void SaveStack(std::vector<uint> key, std::stack<Node> stack, std::vector<BatchDBOp> op_stack);
        void DeleteNode(std::vector<uint64_t> k, Node stack[]);
        void CreateInitilNode(std::vector<uint64_t> key, std::vector<uint64_t> value);
        std::vector<std::vector<uint64_t>> FormatNode(Node node, bool top_level, std::vector<BatchDBOp> op_stack, bool remove=false);


    public:
        VTrie();
        ~VTrie();

        VTrie(DBConnection db, std::vector<uint64_t> root);
        std::vector<uint64_t> GetRoot();

        VTrie FromProof(std::vector<std::vector<uint64_t>> proof_nodes, VTrie proof_trie);
        std::vector<std::vector<uint64_t>> prove(VTrie trie, std::vector<uint64_t> key);
        std::vector<uint64_t> VerifyProof(std::vector<uint64_t> root_hash, std::vector<uint64_t> key, std::vector<std::vector<uint64_t>> proof_nodes);

        std::vector<uint64_t> Root();
        void Root(std::vector<uint64_t> root);
        void SetRoot(std::vector<uint64_t> root);
        Path FindPath(std::vector<uint64_t> key);
        VTrie Copy();
        void Batch(std::vector<BatchDBOp> op_stack);
        bool CheckRoot(std::vector<uint64_t> root);
        
        std::vector<uint64_t> select(std::vector<uint64_t> key);
        double select(std::vector<uint64_t> root_hash, std::vector<uint64_t> key);
        bool insert(std::vector<uint64_t> key, std::vector<uint64_t> value);
        bool delet(std::vector<uint64_t> key);
        bool update(std::string key, double value);
};

#endif