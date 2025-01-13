$$
\begin{align}
stmt &\to 
\\
expr &\to 
\\
matrix &\to \text{TOK\_LBRACK} \ dimensions \ \text{TOK\_RBRACK}
\\
dimensions &\to sequence \ \text{TOK\_SEMICOLON} \ dimensions \ | \ sequence
\\
sequence &\to number \ sequence \ | \ number
\\
term &\to 
\\
primitive &\to \text{TOK\_SYMBOL} \ | \ number
\\
number &\to \text{TOK\_INT\_LIT} \ | \ \text{TOK\_FLOAT\_LIT}
\end{align}
$$