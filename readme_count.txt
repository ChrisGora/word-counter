*** COUNT WORDS PROGRAM ***

### INFO

This program takes a file input.txt and counts how many times each word in the
file occurs. The user is then prompted to enter a word (key) and the program
will return the number of occurances (value)

### NORMAL USAGE

./count

Note that input.txt has to be located in the same directory.

### DEBUG MODE

./count d

This will follow all the tests. This also enables a ton of (very useful) printfs
Note that for the tests to be successful the original input.txt has to be used.

### MAKEFILE

A makefile has been included.

Use "make count" for normal usage
and "make countD" for tests / debugging 

### NOTES

- This makes a use of my TST module and also the list module.
- It uses a modified listC.h with item now being a char.
- Each char from the input.txt file is read into the list.
- Some characters have to be removed, eg '!', so a using a list seemed like 
	a good idea.
- Once a list is ready it is fed into a TST.
- Then an infinite loop of taking values and returning keys is started.

### WHAT WOULD I CHANGE

- Initially, my idea was to print or output a list of most frequent words but
	I ran out of time. 
