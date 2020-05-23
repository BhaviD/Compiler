%{
    #include <cstdio>
    #include <iostream>
    #include "AST.h"
    using namespace std;

    Block *programBlock; /* the top level root node of our final AST */

    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;

    extern int line_num;

    void yyerror(const char *s);
%}

/* Represents the many different ways we can access our data */
%union {
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
}

%token<sval> BREAK CONTINUE INCLUDE DEFINE IF ELSE FOR WHILE
%token<sval> SIGNED UNSIGNED BOOL LONG LL LLU
%token<sval> RETURN VOID PRINT PRINTLN INPUT
%token<sval> CHAR FLOAT INT STRING
%token REFERENCE_OPR


%token <cval> CHAR_LIT
%token <ival> INT_LIT
%token <sval> STRING_LIT
%token <fval> FLOAT_LIT
%token <cval> DELIMITER
%token <cval> COMMA
%token <cval> HASH_SYM
%token <cval> PARANTHESIS
%token <cval> CURLY_BRACET
%token <cval> SQUARE_BRACET
%token <bval> BOOL_LIT
%left <sval> NOT_OPR
%left <sval> LOGICAL_OPR
%left <sval> RELATIONAL_OPR
%left <sval> ARITHMETIC_OPR
%left <sval> BITWISE_OPR
%right <sval> ASSIGNMENT_OPR
%right '?' ':'
%token <sval> IDENTIFIER
%token <sval> NO_MATCH
%left TEMP

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
*/
%type <block> parser Block
%type <stmt> StmtList
%type <compStmt> CompoundStmt
%type <simpleStmt> SimpleStmt
%type <printStmt> PrintStmt PrintlnStmt
%type <returnStmt> ReturnStmt
%type <keyword> BreakStmt ContinueStmt
%type <incStmt> IncludeStmt
%type <defStmt> DefineStmt
%type <identList> IdentifierList
%type <varDec> VarDec
%type <inputStmt> InputStmt
%type <atom> Atom
%type <literal> Literal
%type <multidim> MultiDim
%type <expr> Expr ExprList UnaryExpr BinaryExpr TernaryExpr
%type <dataType> DataType
%type <funcCall> FuncCall
%type <primitiveType> PrimitiveType
%type <paramList> ParameterList
%type <optr> Optr
%type <ifStmt> IfStmt
%type <elseBlock> ElseBlock
%type <forStmt> ForStmt
%type <incrStmt> IncrementStmt
%type <whileStmt> WhileStmt
%type <funcDef> FuncDef

%start parser

%%
parser:
    StmtList { programBlock = new Block($1); cout << "done with parsing this file!!\n"; }
    ;

StmtList:
    %empty { $$ = (Stmt*)(NULL); }
    | CompoundStmt StmtList  { $$ = $1; $1->nextStmt = $2; }
    | SimpleStmt StmtList    { $$ = $1; $1->nextStmt = $2; }
    ;

SimpleStmt:
    PrintStmt DELIMITER      { $$ = $1; }
    | PrintlnStmt DELIMITER  { $$ = $1; }
    | ReturnStmt DELIMITER   { $$ = $1; }
    | ContinueStmt DELIMITER { $$ = $1; }
    | BreakStmt DELIMITER    { $$ = $1; }
    | IncludeStmt            { $$ = $1; }
    | DefineStmt             { $$ = $1; }
    | VarDec DELIMITER       { $$ = $1; }
    | InputStmt DELIMITER    { $$ = $1; }
    | Expr DELIMITER         { $$ = $1; }
    ;

Atom:
    IDENTIFIER MultiDim { $$ = new Identifier(*$1, $2); delete $1; }
    | Literal           { $$ = $1; }
    ;

Literal:
    BOOL_LIT     { $$ = new BoolLit($1); }
    | CHAR_LIT   { $$ = new CharLit($1); }
    | INT_LIT    { $$ = new IntLit($1); }
    | FLOAT_LIT  { $$ = new FloatLit($1); }
    | STRING_LIT { $$ = new StringLit(*$1); delete $1; }
    ;

PrintStmt:
    PRINT '(' ExprList ')' { $$ = new PrintStmt($3); }
    ;

PrintlnStmt:
    PRINTLN '(' ExprList ')' { $$ = new PrintStmt($3, true); }
    ;

ReturnStmt:
    RETURN Expr { $$ = new ReturnStmt($2); }
    ;

BreakStmt:
    BREAK { $$ = new Keyword(*$1); delete $1; }
    ;

ContinueStmt:
    CONTINUE { $$ = new Keyword(*$1); delete $1; }
    ;

IncludeStmt:
    '#' INCLUDE IDENTIFIER  { $$ = new IncludeStmt(*$3); delete $3; }
    ;

DefineStmt:
    '#' DEFINE IDENTIFIER Literal { $$ = new DefineStmt(*$3, $4); delete $3; }
    ;

InputStmt:
    INPUT '(' Atom ')'  { $$ = new InputStmt($3); }
    ;

IdentifierList:
    IDENTIFIER ',' IdentifierList { $$ = new IdentifierList(*$1, $3); delete $1; }
    | IDENTIFIER { $$ = new IdentifierList(*$1); delete $1; }
    ;

ParameterList:
    %empty              { $$ = (ParameterList*)NULL; }
    | ',' ParameterList { $$ = $2; }
    | DataType REFERENCE_OPR IDENTIFIER ParameterList   { $$ = new ParameterList($1, *$3, $4, true); delete $3; }
    | DataType IDENTIFIER ParameterList                 { $$ = new ParameterList($1, *$2, $3); delete $2; }
    ;

VarDec:
    DataType IdentifierList { $$ = new VarDec($1, $2); }
    ;

PrimitiveType:
    VOID        { $$ = new PrimitiveType(*$1, VOID); delete $1; }
    | BOOL      { $$ = new PrimitiveType(*$1, BOOL); delete $1; }
    | CHAR      { $$ = new PrimitiveType(*$1, CHAR); delete $1; }
    | INT       { $$ = new PrimitiveType(*$1, INT); delete $1; }
    | UNSIGNED  { $$ = new PrimitiveType(*$1, UNSIGNED); delete $1; }
    | FLOAT     { $$ = new PrimitiveType(*$1, FLOAT); delete $1; }
    | LONG      { $$ = new PrimitiveType(*$1, LONG); delete $1; }
    | LL        { $$ = new PrimitiveType(*$1, LL); delete $1; }
    | LLU       { $$ = new PrimitiveType(*$1, LLU); delete $1; }
    | STRING    { $$ = new PrimitiveType(*$1, STRING); delete $1; }
    ;

MultiDim:
    %empty                  { $$ = (MultiDim*)NULL; }
    | '[' Expr ']' MultiDim { $$ = new MultiDim($2, $4); }
    ;

DataType:
    PrimitiveType MultiDim { $$ = $1; $1->dimHead = $2; }
    ;

Optr:
    LOGICAL_OPR         { $$ = new LogicalOptr(*$1); delete $1; }
    | RELATIONAL_OPR    { $$ = new RelationalOptr(*$1); delete $1; }
    | ARITHMETIC_OPR    { $$ = new ArithmeticOptr(*$1); delete $1; }
    | BITWISE_OPR       { $$ = new BitwiseOptr(*$1); delete $1; }
    | ASSIGNMENT_OPR    { $$ = new AssignmentOptr(*$1); delete $1; }
    ;

Block:
    '{' StmtList '}'    { $$ = new Block($2); }
    ;

FuncCall:
    IDENTIFIER '(' ExprList ')' { $$ = new FuncCall(*$1, $3); delete $1; }
    ;

Expr:
    Atom           { $$ = $1; }
    | FuncCall     { $$ = $1; }
    | UnaryExpr    { $$ = $1; }
    | BinaryExpr   { $$ = $1; }
    | TernaryExpr  { $$ = $1; }
    | '(' Expr ')' { $$ = $2; }
    ;

ExprList:
    %empty           { $$ = (Expr*)(NULL); }
    | ',' ExprList   { $$ = $2; }
    | Expr ExprList  { $$ = $1; $1->nextExpr = $2; }
    ;

UnaryExpr:
    '(' ARITHMETIC_OPR Expr ')'  { $$ = new UnaryExpr(*$2, $3); delete $2; }
    | '(' LOGICAL_OPR Expr ')'   { $$ = new UnaryExpr(*$2, $3); delete $2; }
    ;

BinaryExpr:
    Expr Optr Expr %prec TEMP  { $$ = new BinaryExpr($1, $2, $3); }
    ;

TernaryExpr:
    Expr '?' Expr ':' Expr  { $$ = new TernaryExpr($1, $3, $5); }
    ;

CompoundStmt:
    IfStmt      { ; }
    | ForStmt   { ; }
    | WhileStmt { ; }
    | FuncDef   { ; }
    ;

IfStmt:
    IF '(' Expr ')' Block ElseBlock { $$ = new IfStmt($3, $5, $6); }
    ;

ElseBlock:
    %empty        { $$ = (ElseBlock*)NULL; }
    | ELSE Block  { $$ = $2; }
    | ELSE IfStmt { $$ = $2; }
    ;

ForStmt:
    FOR '(' Expr DELIMITER Expr DELIMITER IncrementStmt ')' Block { $$ = new ForStmt($3, $5, $7, $9); }
    ;

IncrementStmt:
    %empty  { $$ = new IncrementStmt(NULL); }
    | Expr { $$ = new IncrementStmt($1); }
    ;

WhileStmt:
    WHILE '(' Expr ')' Block { $$ = new WhileStmt($3, $5); }
    ;

FuncDef:
    DataType IDENTIFIER '(' ParameterList ')' Block { $$ = new FuncDef($1, *$2, $4, $6); delete $2; }
    ;


%%

int main (int argc, char** argv) {
    // Open a file handle to a particular file:
    FILE *myfile = fopen(argv[1], "r");
    // Make sure it is valid:
    if (!myfile) {
        cout << "I can't open " << argv[1] << "!" << endl;
        return -1;
    }
    // Set Flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    // parse through the input until there is no more:
    do {
        yyparse();
    } while (!feof(yyin));

    programBlock->printStmt();
}

void yyerror(const char *s) {
    // cout << "EEK, parse error!  Message: " << s << endl;
    cout << "EEK, parse error on line " << line_num << "!  Message: " << s << endl;
    // might as well halt now:
    exit(-1);
}
