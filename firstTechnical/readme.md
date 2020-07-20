# First Technical Interview

This is the first interview I got right out of school and I'm glad they gave me a take home problem instead of hackerrank style challenge. 

## The Problem

Write a program to parse and evaluate arithmetic expressions.


Your problem should support addition and multiplication at a minimum.


You input will be text similar to the following:


1 + 1


(3 + 4) * 6


(1 * 4) + (5 * 2)


Your output should be the computed value of the expression.


Write your program in an Object Oriented fashion and be prepared to show us your code and discuss your solution. Do not use the "Shunting Yard" algorithm.

## Solution

Reading the assignment I was reminded of a program that I had written for a class when we were learning about prefix notation. The program would parse an equation into a binary tree and then solve it using a recursive function. My first task was to parse the equation into a tree form so that my future recursive funtion could handle it.

The job listing was for a position writing cpp which I'm not an expert in, but I wanted to try it out in cpp first. I ran into an issue when I wanted to find the root of the tree I was working in. In cpp you get an error trying to reference memory that you haven't allocated yet (in hindsight it should have been obvious) but that threw me. The Broken cpp file is the beginning of my cpp atempt before I abandoned ship for my Javascript solution.

It was much easier to implement in js because undefined values read as falsy, so now instead of throwing an error when checking for a parent node it just returns false. 

## Outcome

They hired another person farther along in the process than I was and I was sent back to the drawing board.
