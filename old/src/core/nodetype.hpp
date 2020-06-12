#ifndef PMT_NODE_TYPE_H
#define PMT_NODE_TYPE_H

enum NodeType {
    BLANK_NODE = 0,
    BRANCH_NODE = 1,
    EXTENSION_NODE = 2,
    LEAF_NODE = 3
};

enum EmbeddedNode {
    BUFFER = 0,
    BUFFER_ARRAY = 1
};

enum NodeSize {
    BLANK_NODE_SIZE = 0,
    BRANCH_NODE_SIZE = 17,
    OTHER_NODE_SIZE = 2
};

#endif