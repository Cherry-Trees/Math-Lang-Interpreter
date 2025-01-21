$$
\begin{align}
query &\to stmt \ \text{SEMICOLON}
\\
stmt &\to assign \ | \ procedure \ | \ if \ | \ for \ | \ while
\\
assign &\to lvalue \ \text{ASSIGN\_OP} \ rvalue
\\
lvalue &\to \text{ID} \ [\text{LPAREN} \ [paramlist] \ \text{RPAREN} \ | \ \text{LBRACK} \ subscripts \ \text{RBRACK}] \ [typesuffix]
\\
paramlist &\to param \ \text{COMMA} \ paramlist \ | \ param
\\
param &\to \text{ID} \ [typesuffix]
\\
typesuffix &\to \text{COLON} \ type
\\
type &\to \text{INT} \ | \ \text{REAL}
\\
subscripts &\to rvalue \ [\text{COMMA} \ rvalue]
\\
rvalue &\to factor \ \text{ADD\_OP} \ rvalue \ | \ factor
\\
factor &\to power \ \text{MUL\_OP} \ factor \ | \ power
\\
power &\to term \ \text{EXP\_OP} \ power \ | \ term \ | \ \text{LPAREN} \ rvalue \ \text{RPAREN}
\\
term &\to var \ | \ matrix
\\
var &\to \text{ID} \ [\text{LPAREN} \ [arglist] \ \text{RPAREN}] \ [\text{LBRACK} \ arglist(2) \ \text{RBRACK}] \ [typesuffix]
\\
arglist &\to rvalue \ \text{COMMA} \ arglist \ | \ rvalue
\\
matrix &\to number \ | \ \text{LBRACK} \ dimensions \ \text{RBRACK}
\\
number &\to \text{INT\_LIT} \ | \ \text{REAL\_LIT}
\\
dimensions &\to arglist \ \text{SEMICOLON} \ dimensions \ | \ arglist
\\
procedure &\to \text{PROCEDURE} \ \text{ID} \ \text{LPAREN} \ [paramlist] \ \text{RPAREN} \ \text{COLON} \ [body] \ \text{ENDPROCEDURE}
\\
body &\to query \ body \ | \ query
\\
if &\to \text{IF} \ \text{LPAREN} \ bool \ \text{RPAREN} \ \text{COLON} \ [body] \ \text{ENDIF}
\\
bool &\to and \ \text{OROP} \ bool \ | \ and
\\
and &\to relation \ \text{ANDOP} \ and \ | \ relation
\\
relation &\to [\text{NOTOP}] \ rvalue \ \text{RELOP} \ relation \ | \ [\text{NOTOP}] \ rvalue \ | \ \text{LPAREN} \ bool \ \text{RPAREN}
\\
for &\to \text{FOR} \ param \ \text{IN} \ \text{LPAREN} \ term \ \text{RPAREN} \ \text{COLON} \ [body] \ \text{ENDFOR}
\\
while &\to \text{WHILE} \ \text{LPAREN} \ bool \ \text{RPAREN} \ \text{COLON} \ [body] \ \text{ENDWHILE}
\end{align}
$$
