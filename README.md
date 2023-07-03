# Language Interpreter
Language Interpreter for Banh Mi

This is an an esoteric interpreted language, based on one of the languages designed by one of my professors.
To prevent academic integrity violations I will not publicize the name of the language or my professor.

The following will be a guide to the language and its functionalities:

## Types:

There are three data types that this language supports: literal integers, literal doubles, and string literals. 
Literal strings are indicated by enclosing *single* quotes `'` while integers and doubles are represented as normal.

## Input/Output:

## Variables:

## Labels:

## Arithmetic:

Basic arithmetic operations (addition, subtraction, multiplication, division) are supported.
Operations between like types preserves that type; otherwise, a widening conversion will be applied to the smaller data type. 

Addition:

`ADD X Y`

Addition can be performed between any of the following combinations of types:

int + int; int + double; double + int; double + double; string + string

Subtraction:

`SUB X Y`

Subtraction can be performed between any of the following combinations of types:

int - int; int - double; double - int; double - double

Multiplication:

`MULT X Y`

Multiplication can be performed between any of the following combinations of types:

int * int; int * double; double * int; double * double

Division:

`DIV X Y`

Division can be performed between any of the following combinations of types:

int / int; int / double; double / int; double / double

## Control Flow:

## Conditionally Altering Control Flow:

## Spacing:

This language is unique because I have tokenized all of the significant inputs.
As a result, the language ignores excessive whitespace -- a minimum of one space is required to separate tokens such as `LET` and `DIV`.