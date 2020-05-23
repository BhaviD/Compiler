/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BREAK = 258,
    CONTINUE = 259,
    INCLUDE = 260,
    DEFINE = 261,
    IF = 262,
    ELSE = 263,
    FOR = 264,
    WHILE = 265,
    SIGNED = 266,
    UNSIGNED = 267,
    BOOL = 268,
    LONG = 269,
    LL = 270,
    LLU = 271,
    RETURN = 272,
    VOID = 273,
    PRINT = 274,
    PRINTLN = 275,
    INPUT = 276,
    CHAR = 277,
    FLOAT = 278,
    INT = 279,
    STRING = 280,
    REFERENCE_OPR = 281,
    CHAR_LIT = 282,
    INT_LIT = 283,
    STRING_LIT = 284,
    FLOAT_LIT = 285,
    DELIMITER = 286,
    COMMA = 287,
    HASH_SYM = 288,
    PARANTHESIS = 289,
    CURLY_BRACET = 290,
    SQUARE_BRACET = 291,
    BOOL_LIT = 292,
    NOT_OPR = 293,
    LOGICAL_OPR = 294,
    RELATIONAL_OPR = 295,
    ARITHMETIC_OPR = 296,
    BITWISE_OPR = 297,
    ASSIGNMENT_OPR = 298,
    IDENTIFIER = 299,
    NO_MATCH = 300,
    TEMP = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "parser.y" /* yacc.c:1909  */

    char cval;
    int ival;
    string* sval;
    float fval;
    bool bval;

    Block* block;
    Stmt* stmt;
    Expr* expr;
    MultiDim* multidim;
    Identifier* ident;
    CompoundStmt* compStmt;
    SimpleStmt* simpleStmt;
    Keyword* keyword;
    PrintStmt* printStmt;
    ReturnStmt* returnStmt;
    IncludeStmt* incStmt;
    DefineStmt* defStmt;
    VarDec* varDec;
    InputStmt* inputStmt;
    Atom* atom;
    Literal* literal;
    BoolLit* boolean;
    IntLit* intLit;
    CharLit* charLit;
    FloatLit* floatLit;
    StringLit* str;
    IdentifierList* identList;

    FuncCall* funcCall;
    DataType* dataType;
    PrimitiveType* primitiveType;

    ParameterList* paramList;
    Optr* optr;

    IfStmt* ifStmt;
    ElseBlock* elseBlock;
    ForStmt* forStmt;
    IncrementStmt* incrStmt;
    WhileStmt* whileStmt;
    FuncDef* funcDef;

#line 146 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
