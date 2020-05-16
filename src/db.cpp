#include "inc/db.hpp"

#include <leveldb/write_batch.h>
#include <string>

#include "utils/hex.hpp"

#include <iostream>



DBConnection::DBConnection(const std::string& db_file) {
    db_file_ = db_file;

    leveldb::Options options;
    options.create_if_missing = true;
    
    status_ = leveldb::DB::Open(options, db_file, &db_);
}

leveldb::Status DBConnection::GetStatus() {
    return status_;
}

std::vector<uint64_t> DBConnection::Get(const std::vector<uint64_t>& key) {
    std::string value_ {""};
    std::vector<uint64_t> result;
    const std::string key_ = BytesToString(key);

    auto iterator_ = uncommitted_.find(key_);

    if(iterator_ != uncommitted_.end()) {
        result = StringToBytes(StringToHex(iterator_->second));
    } else {
        status_ = db_->Get(leveldb::ReadOptions(), key_, &value_);

        if(status_.ok()) {
            result = StringToBytes(StringToHex(value_));
        } else {
            // Todo use try catch to throw error
        }
    }

    return result;
}

void DBConnection::Put(const std::vector<uint64_t>& key, const std::vector<uint64_t>& value) {
    const std::string key_ = BytesToString(key);
    std::string value_ = BytesToString(value);

    uncommitted_.insert(std::make_pair(key_, value_));
    
    // status_ = db_->Put(leveldb::WriteOptions(), key_, value_);
}

void DBConnection::Delete(const std::vector<uint64_t>& key) {
    const std::string key_ = BytesToString(key);

    auto iterator_ = uncommitted_.find(key_);

    if(iterator_ != uncommitted_.end()) {
        uncommitted_.erase(key_);
    } else {
        status_ = db_->Delete(leveldb::WriteOptions(), key_);
    }
}

void DBConnection::Commit() {
    leveldb::WriteBatch bacth_;
    leveldb::WriteOptions opt_;
    opt_.sync = true;
   
    std::map<std::string, std::string>::iterator it_;
    for(it_ = uncommitted_.begin(); it_ != uncommitted_.end(); it_++) {
        bacth_.Put(it_->first, it_->second);
    }
    status_ = db_->Write(opt_, &bacth_);
    uncommitted_.clear();
}

std::map<std::vector<uint64_t>, std::vector<uint64_t>> DBConnection::ReadAll() {
    std::map<std::vector<uint64_t>, std::vector<uint64_t>> key_values_;

    leveldb::Iterator *it = db_->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        auto key_ = it->key().ToString();
        auto value_ = it->value().ToString();
        key_values_.insert(std::make_pair(StringToBytes(StringToHex(key_)), StringToBytes(StringToHex(value_))));
    }
    delete it;

    return key_values_;
}

int main() {
    DBConnection db_connection = DBConnection("/tmp/testdb");

    std::string value {"Test"};
    if (db_connection.GetStatus().ok()) {
        db_connection.Put(StringToBytes(StringToHex("123")), StringToBytes(StringToHex(value)));
        db_connection.Put(StringToBytes(StringToHex("456")), StringToBytes(StringToHex(value + "1")));
        std::vector<uint64_t> value_;
        value_ = db_connection.Get(StringToBytes(StringToHex("456")));
        std::cout << BytesToString(value_) << std::endl;
    }

    if (db_connection.GetStatus().ok()) {
        db_connection.Commit();
    }

    if (db_connection.GetStatus().ok()) {
        std::vector<uint64_t> value_;
        value_ = db_connection.Get(StringToBytes(StringToHex("123")));
        std::cout << BytesToString(value_) << std::endl;
    }

    if (db_connection.GetStatus().ok()) {
        db_connection.Delete(StringToBytes(StringToHex("123")));
        std::vector<uint64_t> value_;
        value_ = db_connection.Get(StringToBytes(StringToHex("123")));
        std::cout << BytesToString(value_) << std::endl;
    }

    std::map<std::vector<uint64_t>, std::vector<uint64_t>> key_values_;
    std::cout << "Here" << std::endl;
    key_values_ = db_connection.ReadAll();
    std::map<std::vector<uint64_t>, std::vector<uint64_t>>::iterator it_;
    for(it_ = key_values_.begin(); it_ != key_values_.end(); it_++) {
        std::cout << BytesToString(it_->first) << ": " << BytesToString(it_->second) << std::endl;
    }
}
