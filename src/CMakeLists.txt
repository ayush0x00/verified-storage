add_library(
    hex.cpp
    nibbles.cpp
    nodeutils.cpp
    db.cpp
    batchdbop.cpp
    node.cpp
    leaf.cpp
    branch.cpp
    extension.cpp
    path.cpp
    vtrie.cpp
)

add_subdirectory(includes)
add_subdirectory(keccak)
add_subdirectory(rlp)
add_subdirectory(utils)
