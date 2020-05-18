#include <leveldb/db.h>

#include <vector>
#include <map>

#include "batchdbop.hpp"

class DBConnection {
    private:
        std::string db_file_;
        leveldb:: DB* db_;
        leveldb::Status status_;
        std::map<std::string, std::string> uncommitted_;

    public:
        DBConnection();
        DBConnection(const std::string &db_file);
        leveldb::Status GetStatus();
        std::vector<uint64_t> Get(const std::vector<uint64_t> &key);

        void Commit();
        void Put(const std::vector<uint64_t> &key, const std::vector<uint64_t> &value);
        void Delete(const std::vector<uint64_t> &key);

        void BatchProcess(const std::vector<BatchDBOp> &ops_);

        std::map<std::vector<uint64_t>, std::vector<uint64_t>> ReadAll();
};
