# CFG for Programming Language



 ### Identifiers:
 IdentifierList $\,\to\,$ Identifier [, IdentifierList]* | $\epsilon$<br>
 Identifier $\,\to\,$ (Letter | _ ) (Letter | _ | Digit)*<br>
 Letter $\,\to\,$ [a-zA-Z]<br>
 Digit $\,\to\,$ [0-9]<br>
 NonZeroDigit $\,\to\,$ [1-9]<br>
 Fraction $\,\to\,$ "." Digit+
 
 ### Keywords:
 
 Keyword $\,\to\,$ include, if, else, for, while, int, char, signed, unsigned, bool, return, void, string, print, println, input, true, false
 
 ### Literals:
 Literal $\,\to\,$ StringLiteral | IntegerLiteral | FloatLiteral<br>
 StringLiteral $\,\to\,$ "\<any ASCII character except newline or the quote>"<br>
 IntegerLiteral $\,\to\,$ DecimalInteger<br>
 DecimalInteger $\,\to\,$ NonZeroDigit Digit* | [0]<br>
 FloatLiteral $\,\to\,$ IntegerLiteral Fraction
 
 ### Operators:
 Optr $\,\to\,$ LogicalOptr | RelationalOptr | ArithmeticOptr | BitwiseOptr | AssignmentOptr<br>
 LogicalOptr $\,\to\,$ and | or | not<br>
 RelationalOptr $\,\to\,$ < | > | == | <= | >= | !=<br>
 ArithmeticOptr $\,\to\,$ + | - | * | / | %<br>
 BitwiseOptr $\,\to\,$ << | >> | & | [ | ] | ~<br>
 AssignmentOptr $\,\to\,$ = | += | *= | /= | %= | &= | |= | <<= | >>=<br>
 IndexOptr $\,\to\,$ [ParenthesisExpr]

 
 ### Expressions:
 Atom $\,\to\,$ Identifier | Literal | FuncCall<br>
 AtomList $\,\to\,$ Atom AtomList | Atom"," AtomList | $\epsilon$<br>
 ParenthesisExpr $\,\to\,$ (ParenthesisExpr) [Optr ParenthesisExpr]* | Expr<br>
 Expr $\,\to\,$ UnaryExpr | BinaryExpr | TernaryExpr<br>
 UnaryExpr $\,\to\,$ Atom | "-" Atom | "+" Atom | "~" Atom | "-" UnaryExpr | "+" UnaryExpr | "~" UnaryExpr | Identifier IndexOptr<br>
 BinaryExpr $\,\to\,$ ParenthesisExpr Optr ParenthesisExpr
 TernaryExpr $\,\to\,$ "("ParenthesisExpr "?" ParenthesisExpr ":" ParenthesisExpr")"
 
 ### Function Call
 FuncCall  $\,\to\,$ Identifier (AtomList)
 
 ### Data Types
 DataType $\,\to\,$  PrimitiveType | CompoundType<br>
 PrimitiveType $\,\to\,$ bool | char | int | float | long long<br>
 CompoundType $\,\to\,$ PrimitiveType[ParenthesisExpr] | PrimitiveType[ParenthesisExpr] [ParenthesisExpr]
 
 ### Variables:
 VariableList $\,\to\,$ DataType Identifier [, VariableList]* | DataType& Identifier [, VariableList]* | $\epsilon$<br>
 VarDec $\,\to\,$ DataType IdentifierList
 
 ### Comments:
 Comment $\,\to\,$ //\<any character except newline>
 
 ### Statements:
 Delim $\,\to\,$ ;<br>
 StmtList $\,\to\,$ SimpleStmt StmtList | CompoundStmt StmtList | $\epsilon$<br>
 SimpleStmt $\,\to\,$ ExprStmt Delim | PrintStmt Delim | ReturnStmt Delim | ContinueStmt Delim | BreakStmt Delim| IncludeStmt Delim | VarDec Delim | FuncCall Delim<br>
 ExprStmt $\,\to\,$ ParenthesisExpr<br>
 PrintStmt $\,\to\,$ "print ("AtomList")"<br>
 PrintlnStmt $\,\to\,$ "println ("AtomList")"<br>
 InputStmt $\,\to\,$ "input ("[Identifier | Identifier IndexOptr]")"<br>
 ReturnStmt $\,\to\,$ "return "ParenthesisExpr<br>
 BreakStmt $\,\to\,$ "break"<br>
 ContinueStmt $\,\to\,$ "continue"<br>
 IncludeStmt $\,\to\,$ "#include "[StringLiteral, "<"Identifier">"]<br>
 DefineStmt $\,\to\,$ "#define" Identifier Literal<br>
 CompoundStmt $\,\to\,$ IfStmt | ForStmt | WhileStmt<br>
 IfStmt $\,\to\,$ "if ("ParenthesisExpr")" Block | "if("ParenthesisExpr")" Block "else" Block | "if("ParenthesisExpr")" Block "else" IfStmt <br>
 ForStmt $\,\to\,$ "for ("ParenthesisExpr"; " ParenthesisExpr"; "ParenthesisExpr")" Block<br>
 WhileStmt $\,\to\,$ "while ("ParenthesisExpr")" Block<br>
 
 ### Blocks:
 Block $\,\to\,$ { StmtList }
 
 ### Functions:
 FuncDef $\,\to\,$ ReturnType Identifier(VariableList) Block<br>
 ReturnType $\,\to\,$ PrimitiveType<br>
