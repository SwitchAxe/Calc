# calc
a simple C calculator

# building
clone the git repo in a directory of your choice and compile it:
    
    git clone https://github.com/SwitchAxe/Calculator.git
    make bin

# USAGE

./calc "expression" OR command-line argument (see below)

# COMMAND-LINE ARGS

calc supports a grand total of three (3) command-line arguments! either -i, -l or -f (but only one at a time) can be added to ./calc to change its behaviour.

-i stands for input and makes the program ask once for an expression, calculates it, returns its value back and then exits. the syntax is the following:  

    ./calc -i

-l stands for loop and makes the program a loop that exits when the special expression "exit" is written. in this loop, you can write expressions that evaluate to results. the syntax is the following:  

    ./calc -l 

-f stands for file and lets you specify a file from which the expression will be read. the syntax is the following:  

    ./calc -f file

## important!

if you wish to run calc without arguments, be sure to put the expression in between double quotes (" "). i have no clue about how the program might act if you forget this, so please don't.

# CREDITS

special thanks go to [Marco Trosi](https://www.github.com/MarcoTrosi) for the precious help in writing several functions of this project. without him, i would have spent probably a year writing what was written in a month.
