# Greedy Money Count
[Language C]
A variant of the Greedy algorithm applied to a problem of money counting.

It has been inspired by Francesco Bruschi assignment (Prof. at Polimi).

What does the program do?
The main function is "spiccioli" that takes two arguments: an integer and a string.

Example:
spiccioli(20,"a:9,b:2,c:1") ---> output "aab"

The string represent assignment, each letter represents a coin and the number next to it is its value.  
We have to find the shortest sequence of letter that makes the given integer (20).
In this case: aab = a + a + b = 9 + 9 + 2 = 20.
Other important notes:
- the rest must be exactly zero;
- the output string must be in alphabetic order before being outputed.
