# Language Interpreter
Language Interpreter for Banh Mi

This is an an esoteric interpreted language, based on one of the languages designed by one of my professors.
To prevent academic integrity violations I will not publicize the name of my professor (not that it would matter the design and overall structure of my interpreter doesn't follow the instructions).

The following will be a guide to the language and its functionalities:

## Types:

There are three data types that this language supports: literal integers, literal doubles, and string literals. 
Literal strings are indicated by enclosing *single* quotes `'` while integers and doubles are represented as normal.

## Input/Output:

Input is read from the terminal, and is processed by the interpreter. 
User input is only read in *after* the user finishes entering their program and indicates it with the terminating symbol, which is `.` (dot).

There are two methods to read input; `INNUM` reads in an integer or float, and `INSTR` reads in a string. 
Both methods store the read values in a variable parameter that is specified after the corresponding input keyword. 

Output can be printed to the terminal as well, using the `PRINT` keyword followed by the value to be output. 
If the value following `PRINT` is a variable, it will be evaluated to its corresponding value before being printed to the terminal.

## Variables:

The interpreter allows for the use of variables to store valid data types. Any variable that is used without being previously assigned is automatically given the value `0` (zero).To assign a new variable, use the `LET` keyword followed by the name of the variable (no spaces or special characters allowed), followed by it's value.

Examples:

`LET Integer 13`

`LET Double 26.2`

`LET String 'Matcha Latte'`

Additionally, you can assign the value of a variable to that of another variable. The `Base` variable will be assigned a copy of the value that is stored in the `Source` variable.

`LET Base Source`

## Labels:

Labels are one of the provided methods that can be used to mark certain lines of code. To create a label, simply start the line with a name (in the same fashion that you would declare a variable) and follow it with a colon.

Example:

`LABEL: LET int 13`

The label can be used by `GOTO` and `GOSUB` statements but otherwise has no impact on execution.

**Label names must be unique otherwise you will encounter naming collisions** (**the label closest to the end of entered code has priority**)

## Arithmetic:

Basic arithmetic operations (addition, subtraction, multiplication, division) are supported. For any operation, the first value following the operation must be a variable; the outcome of the operation will be stored inside that variable. The second value may either be a variable or literal value.

Operations between like types preserves that type; otherwise, a widening conversion will be applied to the smaller data type and the final outcome will have the same type as the larger data type. 

Numeric operations behave as expected. The addition operation performed on two strings will concatenate the second string to the end of the first string. The multiplication operation performed between an int `n` and string will result in the string being repeated `n` times.

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

int * int; int * double; double * int; double * double; int * string; string * int

Division:

`DIV X Y`

Division can be performed between any of the following combinations of types:

int / int; int / double; double / int; double / double

## Control Flow:

This language does not provide the ability to write functions. Instead, it offers the ability to jump between lines using `GOTO` or `GOSUB` commands.

There are two methods available to set the target:

1. Provide an integer target. For example, `GOTO 11` will jump 11 lines forward, and `GOTO -3` jumps three lines backwards. A variable holding the integral value can be used as well.

2. Provide a string target. For example, `GOTO 'TARO' ` jumps to the line labelled `'TARO'`. The string **must** be the name of an existing label. Execution will jump forwards or backward to that label.

The `GOSUB` command functions identically to the `GOTO` command, with one exception. If a `RETURN` command is encountered **after** a `GOSUB` command has been executed, execution will return to the `GOSUB` statement and continue on the line directly following it. Multiple `GOSUB` commands can be in play and execution returns to the one most recently executed. If a `RETURN` statement is encountered but there is no matching `GOSUB` command, an error will occur. 

To prevent infinite loops, the `END` command is designed to stop the program before encountering the `.` that typically indicates the end of the program.

## Conditionally Altering Control Flow:

Control flow can be used to 

## Spacing:

This language is unique because I have tokenized all of the significant inputs.
As a result, the language ignores excessive whitespace -- a minimum of one space is required to separate elements such as `LET`, `DIV`, variable names, literal values, etc.