#include <iostream>
#include <string>
using namespace std;

class Stmt {
public:
    Stmt* nextStmt;
    virtual void printStmt() { cout << "Statement not printed yet!!\n"; }
};

class SimpleStmt : public Stmt {
public:
    SimpleStmt(Stmt* nxt = NULL) { nextStmt = nxt; }
};

class ElseBlock {
public:
    virtual void printStmt() { ; }
}; 

class Block : public ElseBlock {
public:
    Stmt* stmtsHead;

    // constructor
    Block (Stmt* head): stmtsHead(head) {}

    void printStmt();
};

class Expr : public SimpleStmt {
public:
    Expr* nextExpr;
};

class MultiDim {
public:
    Expr* expr;
    MultiDim* nextDim;

    MultiDim(Expr* e, MultiDim* nxt = NULL): expr(e), nextDim(nxt) {}

    void print();
};

class Atom : public Expr {
};

class Identifier : public Atom {
public:
    string name;
    MultiDim* multiDimList;

    Identifier(const string& n, MultiDim* mDim = NULL): name(n), multiDimList(mDim) {}

    void printStmt();
};

class Literal: public Atom {
};

class BoolLit : public Literal {
public:
    bool val;
    BoolLit(bool v) : val(v) {}

    void printStmt();
};

class IntLit : public Literal {
public:
    int val;
    IntLit(int v) : val(v) {}

    void printStmt();
};

class CharLit : public Literal {
public:
    char val;
    CharLit(char v) : val(v) {}

    void printStmt();
};

class FloatLit : public Literal {
public:
    float val;
    FloatLit(bool v) : val(v) {}

    void printStmt();
};

class StringLit : public Literal {
public:
    string val;
    StringLit(string& v) : val(v) {}

    void printStmt();
};

class FuncCall: public Expr {
public:
    string funcName;
    Expr* exprList;

    FuncCall(const string& fname, Expr* elist): funcName(fname), exprList(elist) {}

    void printStmt();
};

class UnaryExpr: public Expr {
public:
    string optrName;
    Expr* expr;

    UnaryExpr(const string& optr, Expr* e): optrName(optr), expr(e) {}

    void printStmt();
};

class Optr {
public:
    string optrName;
    Optr(const string& optr): optrName(optr) {}

    void print();
};

class LogicalOptr: public Optr {
public:
    LogicalOptr(const string& optr): Optr(optr) {}
};

class RelationalOptr: public Optr {
public:
    RelationalOptr(const string& optr): Optr(optr) {}
};

class ArithmeticOptr: public Optr {
public:
    ArithmeticOptr(const string& optr): Optr(optr) {}
};

class BitwiseOptr: public Optr {
public:
    BitwiseOptr(const string& optr): Optr(optr) {}
};

class AssignmentOptr: public Optr {
public:
    AssignmentOptr(const string& optr): Optr(optr) {}
};

class BinaryExpr: public Expr {
public:
    Expr* leftExpr;
    Optr* optr;
    Expr* rightExpr;

    BinaryExpr(Expr* lt, Optr* o, Expr* rt): leftExpr(lt), optr(o), rightExpr(rt) {}

    void printStmt();
};

class TernaryExpr: public Expr {
public:
    Expr* condition;
    Expr* expr1;
    Expr* expr2;

    TernaryExpr(Expr* cond, Expr* e1, Expr* e2): condition(cond), expr1(e1), expr2(e2) {}

    void printStmt();
};

class IdentifierList {
public:
    string name;
    IdentifierList* nextIdentifier;

    IdentifierList(const string& nm, IdentifierList* nxt = NULL): name(nm), nextIdentifier(nxt) {}

    void print();
};

class DataType {
public:
    MultiDim* dimHead;

    virtual void print() = 0; 
};

class PrimitiveType: public DataType {
public:
    string typeName;
    int opcode;

    PrimitiveType(const string& t, int code): typeName(t), opcode(code) {}

    void print();
};


class Keyword : public SimpleStmt {
public:
    string keyword;
    Keyword(string& kw): keyword(kw) {}

    void printStmt();
};

class PrintStmt: public SimpleStmt {
public:
    Expr* exprList;
    bool add_NL;

    PrintStmt(Expr* elist, bool NL = false): exprList(elist), add_NL(NL) {}

    void printStmt();
};

class ReturnStmt: public SimpleStmt {
public:
    Expr* expr;

    ReturnStmt(Expr* e): expr(e) {}

    void printStmt();
};

class IncludeStmt: public SimpleStmt {
public:
    string fileName;
    IncludeStmt(const string& fname): fileName(fname) {}

    void printStmt();
};

class DefineStmt: public SimpleStmt {
public:
    string macroName;
    Literal* lit;

    DefineStmt(const string& mName, Literal* l): macroName(mName), lit(l) {}

    void printStmt();
};

class VarDec: public SimpleStmt {
public:
    DataType* type;
    IdentifierList* identifiers;

    VarDec(DataType* t, IdentifierList* head): type(t), identifiers(head) {}

    void printStmt();
};

class InputStmt: public SimpleStmt {
public:
    Atom* atom;
    InputStmt(Atom* a): atom(a) {}

    void printStmt();
};

class ParameterList {
public:
    DataType* type;
    string paramName;
    ParameterList* nextParam;
    bool isRef;

    ParameterList(DataType* t, const string& name, ParameterList* nxt = NULL, bool ref = false):
        type(t), paramName(name), nextParam(nxt), isRef(ref) {}

    void print();
};

class CompoundStmt : public Stmt {
public:
    CompoundStmt (Stmt* nxt = NULL) { nextStmt = nxt; }
};

class IfStmt : public CompoundStmt, public ElseBlock {
public:
    Expr* condition;
    Block* ifBlock;
    ElseBlock* elseBlock;

    IfStmt(Expr* cond, Block* ifBlk, ElseBlock* elseBlk): condition(cond), ifBlock(ifBlk), elseBlock(elseBlk) {}

    void printStmt();
};

class IncrementStmt {
public:
    Expr* expr;
    IncrementStmt(Expr* e): expr(e) {}

    void print();
};

class ForStmt: public CompoundStmt {
public:
    Expr* initExpr;
    Expr* condition;
    IncrementStmt* incrStmt;
    Block* block;

    ForStmt(Expr* iexpr, Expr* cond, IncrementStmt* incr, Block* blk): initExpr(iexpr), condition(cond), incrStmt(incr), block(blk) {}

    void printStmt();
};

class WhileStmt: public CompoundStmt {
public:
    Expr* condition;
    Block* block;

    WhileStmt(Expr* cond, Block* blk): condition(cond), block(blk) {}

    void printStmt();
};

class FuncDef: public CompoundStmt {
public:
    DataType* type;
    string funcName;
    ParameterList* paramList;
    Block* block;

    FuncDef(DataType* t, const string& fName, ParameterList* pList, Block* blk):
        type(t), funcName(fName), paramList(pList), block(blk) {}
    
    void printStmt();
};
