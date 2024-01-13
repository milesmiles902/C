/*
 * Question 1:
 * Base-10, 17, in Base-2, would be 1*2^4 + 0*2^3 + 0*2^2 + 0*2^1 + 1*2^0= 10001
 * Base-10, 45, in Base-2, would be 1*2^5 + 0*2^4 + 1*2^3 + 1*2^2 + 0*2^1 + 1*2^0 = 10110
 * Base-10, 96, in Base-2, would be 1*2^6 + 1*2^5 + 0*2^4 + 0*2^3 + 0*2^2 + 0*2^1 + 0*2^0 = 1100000
 *
 * Question 2:
 * Infix: (a+b)*(c+d)*(e+f); Prefix: **+ab+cd+ef
 * Infix: A+((B+C)*(D+E)); Prefix: +A*+BC+DE
 * Infix: A*B*C*D+E+F; Prefix: ++***ABCDEF 
 *
 * Question 3:
 * Infix: (a+b)*(c+d)*(e+f); Postfix: ab+cd+*ef+*
 * Infix: A+((B+C)*(D+E)); Postfix: ABC+DE+*+
 * Infix: A*B*C*D+E+F; Prefix: AB*C*D*E+F+
 *
 * Question 4:
 * Infix: (a+b)*(c+d)*(e+f); 
 *   Stack: a
 *          ab
 *          ab+
 *          ab+c
 *          ab+cd
 *          ab+cd+
 *          ab+cd+*
 *          ab+cd+*e
 *          ab+cd+*ef
 *          ab+cd+*ef+
 *          ab+cd+*ef+*
 * Infix: A+((B+C)*(D+E));
 *   Stack: AB
 *          ABC
 *          ABC+
 *          ABC+D
 *          ABC+DE
 *          ABC+DE+
 *          ABC+DE+*
 *          ABC+DE+*+
 * Infix: A*B*C*D+E+F
 *   Stack: A
 *          AB
 *          AB*C
 *          AB*C*D
 *          AB*C*D*
 *          AB*C*D*E
 *          AB*C*D*E+
 *          AB*C*D*E+F
 *          AB*C*D*E+F+      
 * Question 5:          
 * Postfix: 2 3 * 4 +; Infix: 2*3+4
 *   Stack: 2
 *          23
 *          2*34
 *          2*3+4
 * Postfix: 1 2 + 3 + 4 + 5 +; Infix: 1+2+3+4+5         
 *   Stack: 1
 *          12
 *          1+2
 *          1+23
 *          1+2+3
 *          1+2+34
 *          1+2+3+4
 *          1+2+3+45
 *          1+2+3+4+5
 * Postfix: 1 2 3 4 5 * + * +; Infix: 1+(2*(3+4*5))
 *          1
 *          12
 *          123
 *          1234
 *          12345
 *          1234*5
 *          123+4*5
 *          12*(3+4*5)
 *          1+2*(3+4*5)
 * Question 6:
 *   The Big-O performance would not change for a reversed Queue. 

