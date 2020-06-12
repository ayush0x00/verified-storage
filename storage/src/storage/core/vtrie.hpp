#ifndef PMT_VTRIE_H
#define PMT_VTRIE_H

#include <boost/variant.hpp>

#include <storage/utils/aliasadvance.hpp>
#include <storage/utils/path.hpp>
#include <storage/utils/batchdbop.hpp>
#include <storage/db/db.hpp>
#include <storage/nodes/node.hpp>
#include <storage/nodes/leaf.hpp>
#include <storage/nodes/branch.hpp>
#include <storage/nodes/extension.hpp>

class VTrie {
    private:
        bool _is_defined;
        buffer_t _EMPTY_TRIE_ROOT;
        buffer_t _root;
        DBConnection _db;
        // Todo Add Semaphore for locking the resource under processing

        node_t LookupNode(const embedded_t &node);
        void PutNode(node_t &node);
        void FindValueNodes(); // Todo need to check what should be passed as parameter
        void FindDbNodes(); // Todo need to check what should be passed as parameter
        void UpdateNode(const buffer_t &key, const buffer_t &value, nibble_t &key_reminder, std::vector<node_t> &stack);
        void WalkTrie(const buffer_t &root); // Todo need to check what should be passed as parameter
        void SaveStack(nibble_t &key, std::vector<node_t> &stack, batchdboparray_t &op_stack);
        void DeleteNode(const buffer_t &key, const std::vector<node_t> &stack);
        void CreateInitilNode(const buffer_t &key, const buffer_t &value);
        embedded_t FormatNode(node_t &node, batchdboparray_t &op_stack, const bool top_level, const bool remove=false);

    public:
        VTrie();
        // ~VTrie();
        VTrie(const buffer_t &root);
        VTrie(DBConnection &db, const buffer_t &root);
        buffer_t GetRoot();
        void Root(const buffer_t &root);
        void SetRoot(const buffer_t &root);
        bool IsDefined();
        void IsDefined(const bool is_defined);
        DBConnection GetDB();
        void SetDB(const DBConnection &db);

        static VTrie FromProof(const buffer_array_t &proof_nodes, VTrie &proof_trie);
        buffer_array_t Prove(VTrie &trie, const buffer_t &key);
        buffer_t VerifyProof(const buffer_t &root_hash, const buffer_t &key, const buffer_array_t &proof_nodes);

        Path FindPath(const buffer_t &key);
        VTrie Copy();
        void Batch(const batchdboparray_t &op_stack);
        bool CheckRoot(const buffer_t &root);
        
        buffer_t Select(const buffer_t &key);
        buffer_t Select(const buffer_t &root_hash, const buffer_t &key);
        bool Put(const buffer_t &key, const buffer_t &value);
        bool Insert(const buffer_t &key, const buffer_t &value);
        bool Delet(const buffer_t &key);
        bool Update(const buffer_t &key, const buffer_t &value);

        // Operators
        // bool operator!();
};

#endif
