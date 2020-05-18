#ifndef PMT_BATCH_DB_OP_H
#define PMT_BATCH_DB_OP_H

// #include <string>
#include <vector>

class BatchDBOp {
    private:
        std::string type_;
        std::vector<uint64_t> key_;
        std::vector<uint64_t> value_;
    
    public:
        BatchDBOp(const std::string &type, const std::vector<uint64_t> &key);
        BatchDBOp(const std::string &type, const std::vector<uint64_t> &key, const std::vector<uint64_t> &value);

        std::string GetType();
        void GetType(const std::string &type);
        
        std::vector<uint64_t> GetKey();
        void SetKey(const std::vector<uint64_t> &key);
        
        std::vector<uint64_t> GetValue();
        void SetValue(const std::vector<uint64_t> &value);

};

#endif
