*** LIST MODULE**

- This implementation uses sentinels.
- It keeps the length of the list in the list structure.
- The current position is set as being just after the believed position.
- The structure keeps the pointers to sentinels as well as actual first and last
	valid position. (note that senEnd and end are the same)
- For my own needs in the 'count' program I added a getLength function. This has
	not been tested due to its simplicity.
- There are some tests that some "manual" asserts on pointers and some that use 
	the 'compare' function.
- compare checks the current position is what we expect and then cycles through
	all the pointers from start to end (and vice versa) checking that the 
	required element is actually there at each step. This tests virtually every
	pointer in the list.
- I decided to mostly ditch the idea of symmetry in my code and instead tried to
	make it as DRY as possible. Hence both insertAfter and deleteAfter have only
	two lines. It's possible to change get and set functions as well but you then
	have to go back and forward again and therefore it no longer seemed as nice 
	and intuitive. 
- I have tested for errors semi-manually. The conditions for an error are 
	automatically created, but I manually had to check if the error did happen.
 
