#include <string>
#include <cstdlib>
#include "output.hpp"

namespace nodes {


enum BasicType {
    TVOID, TSTRING, TBYTE, TINT, TBOOL, TID
};


class Node {
private:
    BasicType type;

public:
    Node(BasicType inType): type(inType) {}
    BasicType getType(){
        return type;
    }
};

class Num: public Node {
private:
    int value;
public:
    Num(int inNum): Node(TINT), value(inNum) {}
};

class ByteNum: public Node {
private:
    int value;
public:
    ByteNum(int inNum): Node(TBYTE), value(inNum) {}
};

class IDNode: public Node {
private:
    std::string value;
public:
    IDNode(const char* inID): Node(TSTRING), value(inID) {}
};

// This is the "Int", "Byte" words etc.
class Type: public Node {
private:

public:
    Type(BasicType inType) : Node(inType) {}
};

class Var: public Node {
private:
    std::string varName;
public:
    std::string getVarName() {
        return varName;
    }
    Var(BasicType inType, const char* inName): Node(inType), varName(inName) {}
};

class String: public Node {
private:
    std::string value;
public:
    String(const char* inValue): Node(TSTRING), value(inValue) {}
    std::string getString(){
        return value;
    }
};

class True: public Node {
private:
    bool value;

public:
    True(): Node(TBOOL), value(true) {}
    // Not necessary, could be just one Bool type...
    bool getBool(){
        return value;
    }
};

class False: public Node {
private:
    bool value;

public:
    False(): Node(TBOOL), value(false) {}
    bool getBool(){
        return value;
    }
};

class Expression: public Node {
private:

public:
    Expression(BasicType inType): Node(inType) {}
};

class AndExpression: public Node {
public:
    AndExpression() : Node(TBOOL) {}
};

class OrExpression: public Node {
public:
    OrExpression() : Node(TBOOL){}
};

class RelOpExpression: public Node {
public:
    RelOpExpression() : Node(TBOOL){}
};




// Decide if byte or int
class MulDivExpression: public Node {
    MulDivExpression(BasicType inType): Node(inType) {}
};

class PlusMinusExpression: public Node {
    PlusMinusExpression(BasicType inType): Node(inType) {}
};

// Check if need to add more nodes for If, While etc.


} // namespace nodes
