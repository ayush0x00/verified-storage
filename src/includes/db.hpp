#ifndef PMT_DB_H
#define PMT_DB_H

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
        buffer_t Get(const buffer_t &key);

        void Commit();
        void Put(const buffer_t &key, const buffer_t &value);
        void Delete(const buffer_t &key);

        void BatchProcess(const batchdboparray_t &ops_);

        std::map<buffer_t, buffer_t> ReadAll();

        bool operator!();
};

#endif