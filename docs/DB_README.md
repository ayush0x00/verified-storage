# LevelDB connection and operations

## Classname

```c++
DBConnection
```

### Create database connection

```c++
DBConnection db_connection = DBConnection("/tmp/testdb");
```

### Put key-value pairs in the database

This will cache the key value pairs in the map.

*This won't write in to the database.*

```c++
std::string value {"Test"};
if (db_connection.GetStatus().ok()) {
    db_connection.Put(StringToBytes(StringToHex("123")), StringToBytes(StringToHex(value)));
    db_connection.Put(StringToBytes(StringToHex("456")), StringToBytes(StringToHex(value + "1")));
    std::vector<uint64_t> value_;
    value_ = db_connection.Get(StringToBytes(StringToHex("456")));
    std::cout << BytesToString(value_) << std::endl;
}
```

### Commit the changes to the database

*This will read cache and write it into the database. Cache will be cleared after writing.*

```c++
if (db_connection.GetStatus().ok()) {
    db_connection.Commit();
}
```

### Get Key-value pair by Key

```c++
if (db_connection.GetStatus().ok()) {
    std::vector<uint64_t> value_;
    value_ = db_connection.Get(StringToBytes(StringToHex("123")));
    std::cout << BytesToString(value_) << std::endl;
}
```

### Delete Key value pairs by key

*If the pair is in cache it will delete from cache, if not found in cache, it will delete from database.*

```c++
if (db_connection.GetStatus().ok()) {
    db_connection.Delete(StringToBytes(StringToHex("123")));
    std::vector<uint64_t> value_;
    value_ = db_connection.Get(StringToBytes(StringToHex("123")));
    std::cout << BytesToString(value_) << std::endl;
}
```

### Read all the key-value pairs from the database

```c++
std::map<std::vector<uint64_t>, std::vector<uint64_t>> key_values_;

key_values_ = db_connection.ReadAll();
std::map<std::vector<uint64_t>, std::vector<uint64_t>>::iterator it_;
for(it_ = key_values_.begin(); it_ != key_values_.end(); it_++) {
    std::cout << BytesToString(it_->first) << ": " << BytesToString(it_->second) << std::endl;
}
```
