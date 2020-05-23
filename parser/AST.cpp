#include <iostream>
#include "AST.h"
using namespace std;

int level;

void indent() { cout << string(4*level, ' '); }

void Block::printStmt() {
    Stmt* currStmt = stmtsHead;
    while (currStmt) {
        currStmt->printStmt();
        currStmt = currStmt->nextStmt;
        if (currStmt) cout << endl;
    }
}

void MultiDim::print() {
    indent(); cout << '[' << endl;
    ++level;
    expr->printStmt();
    --level;
    indent(); cout << ']' << endl;
}

void Identifier::printStmt() {
    indent(); cout << '(' << endl;
    indent(); cout << name << endl;

    MultiDim* currDim = multiDimList;
    while (currDim) {
        currDim->print();
        currDim = currDim->nextDim;
    }
    indent(); cout << ')' << endl;
}

void BoolLit::printStmt() {
    indent(); cout << (val ? "(true)" : "(false)") << endl;
}

void IntLit::printStmt() {
    indent(); cout << '(' << val << ')' << endl;
}

void CharLit::printStmt() {
    indent(); cout << '(' << val << ')' << endl;
}

void FloatLit::printStmt() {
    indent(); cout << '(' << val << ')' << endl;
}

void StringLit::printStmt() {
    indent(); cout << '(' << val << ')' << endl;
}

void FuncCall::printStmt() {
    indent(); cout << "FUNC_CALL" << endl;
    ++level;
    indent(); cout << "(" << endl;

    ++level;
    indent(); cout << funcName << endl;
    indent(); cout << '(' << endl;

    Expr* currExpr = exprList;
    ++level;
    while (currExpr) {
        currExpr->printStmt();
        currExpr = currExpr->nextExpr;
    }
    --level;

    indent(); cout << ')' << endl;
    
    --level;
    indent(); cout << ')' << endl;

    --level;
}

void UnaryExpr::printStmt() {
    indent(); cout << "( " << optrName << endl;
    ++level;
    expr->printStmt();
    --level;
    indent(); cout << ")";
}

void Optr::print() { indent(); cout << optrName << endl; }

void BinaryExpr::printStmt() {
    indent(); cout << "BINARY EXPRESSION" << endl;

        ++level;
        indent(); cout << '(' << endl;

            ++level;
            leftExpr->printStmt();
            optr->print();
            rightExpr->printStmt();
            --level;

        indent(); cout << ')' << endl;
        --level;
}

void TernaryExpr::printStmt() {
    indent(); cout << "TERNARYs EXPRESSION" << endl;
        ++level;
        indent(); cout << '(' << endl;

            ++level;
            condition->printStmt();
            indent(); cout << '?' << endl;
            expr1->printStmt();
            indent(); cout << ':' << endl;
            expr2->printStmt();
            --level;

        indent(); cout << ')' << endl;
        --level;
}

void Keyword::printStmt() {
    indent(); cout << keyword << endl;
}

void PrintStmt::printStmt() {
    indent(); cout << (add_NL ? "PRINTLN" : "PRINT") << endl;
    ++level;
    indent(); cout << "(" << endl;

    Expr* currExpr = exprList;
    ++level;
    while (currExpr) {
        currExpr->printStmt();
        currExpr = currExpr->nextExpr;
    }
    --level;

    indent(); cout << ")" << endl;
    --level;
}

void ReturnStmt::printStmt() {
    indent(); cout << "RETURN" << endl;
    ++level;
    indent(); cout << '(' << endl;

    ++level;
    expr->printStmt();
    --level;

    indent(); cout << ')' << endl;
    --level;
}

void IncludeStmt::printStmt() {
    indent(); cout << "INCLUDE (" << fileName << ")" << endl;
}

void DefineStmt::printStmt() {
    indent(); cout << "DEFINE" << endl;
    ++level;
    indent(); cout << '(' << macroName << ')' << endl;
    lit->printStmt();
    --level;
}

void IdentifierList::print() {
    indent(); cout << '(' << name << ')' << endl;
}

void PrimitiveType::print() {
    indent(); cout << typeName << endl;
    MultiDim* currDim = dimHead;
    while (currDim) {
        currDim->print();
        currDim = currDim->nextDim;
    }
}

void VarDec::printStmt() {
    indent(); cout << "VAR_DEC" << endl;
    ++level;
    indent(); cout << '(' << endl;

    ++level;
    type->print();
    IdentifierList* currIdentifier = identifiers;
    while (currIdentifier) {
        currIdentifier->print();
        currIdentifier = currIdentifier->nextIdentifier;
    }
    --level;

    indent(); cout << ')' << endl;
    --level;
}

void InputStmt::printStmt() {
    indent(); cout << "INPUT" << endl;
    ++level;
    indent(); cout << '(' << endl;

    ++level;
    atom->printStmt();
    --level;

    indent(); cout << ')' << endl;
    --level;
}

void ParameterList::print() {
    indent(); cout << '(' << endl;
        ++level;
        type->print();
        indent(); cout << '(' << paramName << (isRef ? "&)" : ")") << endl;
        --level;
    indent(); cout << ')' << endl;
}

void IfStmt::printStmt() {
    indent(); cout << "IF" << endl;
        ++level;
        indent(); cout << '(' << endl;

    ++level;

    condition->printStmt();

    indent(); cout << '(' << endl;
    ++level;
    ifBlock->printStmt();
    --level;
    indent(); cout << ')' << endl;
    
    --level;

    indent(); cout << ')' << endl;
    --level;

    if (!elseBlock)
        return;
    
    indent(); cout << "ELSE" << endl;

    ++level;
    indent(); cout << '(' << endl;

    ++level;
    elseBlock->printStmt();
    --level;

    indent(); cout << ')' << endl;
    --level;
}

void IncrementStmt::print() {
    expr->printStmt();
}

void ForStmt::printStmt() {
    indent(); cout << "FOR" << endl;
        ++level;
        indent(); cout << '(' << endl;
            ++level;
            initExpr->printStmt();
            condition->printStmt();
            incrStmt->print();
                ++level;
                indent(); cout << '(' << endl;
                    ++level;
                    block->printStmt();
                    --level;
                indent(); cout << ')' << endl;
                --level;
            --level;
        indent(); cout << ')' << endl;
        --level;
}

void WhileStmt::printStmt() {
    indent(); cout << "WHILE" << endl;
        ++level;
        indent(); cout << '(' << endl;
            ++level;
            condition->printStmt();
                ++level;
                indent(); cout << '(' << endl;
                    ++level;
                    block->printStmt();
                    --level;
                indent(); cout << ')' << endl;
                --level;
            --level;
        indent(); cout << ')' << endl;
        --level;
}

void FuncDef::printStmt() {
    indent(); cout << "FUNC_DEF" << endl;
        ++level;
        indent(); cout << '(' << endl;
            ++level;
            type->print();
            indent(); cout << '(' << funcName << ')' << endl;

            if (paramList) {
            indent(); cout << '(' << endl;
                ++level;
                ParameterList* currParam = paramList;
                while (currParam) {
                    currParam->print();
                    currParam = currParam->nextParam;
                }
                --level;
            indent(); cout << ')' << endl;
            }

                ++level;
                indent(); cout << '(' << endl;
                    ++level;
                    block->printStmt();
                    --level;
                indent(); cout << ')' << endl;
                --level;

            --level;
        indent(); cout << ')' << endl;
        --level;
}
