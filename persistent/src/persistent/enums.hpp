#ifndef UTILS_ENUMS_H
#define UTILS_ENUMS_H

enum ElementTypes {
    LONG = 0,
    UNINT64 = 1,
    STRING = 2,
    BUFFER = 3,
    BUFFERARRAY = 4
};

enum NodeType {
    BLANK_NODE = 0,
    BRANCH_NODE = 1,
    EXTENSION_NODE = 2,
    LEAF_NODE = 3
};

// enum EmbeddedNode {
//     BUFFER = 0,
//     BUFFER_ARRAY = 1
// };

enum NodeSize {
    BLANK_NODE_SIZE = 0,
    BRANCH_NODE_SIZE = 17,
    OTHER_NODE_SIZE = 2
};

#endif