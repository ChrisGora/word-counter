*** TST MODULE**

- This is a library module supporting Ternary Search Trees (TSTs)
- This implementation uses sentinels.

- Almost every test uses the 'compare' function.
- It's powerful but each call is not very readable.
- It's essentially just a list of instructions to follow.

L, M, R - follow left, middle or right pointer
Any int or (lowercase) char - assert it is saved in the current node
* - assert this is a sentinel
# - assert this is NOT a sentinel

- This allows you to check if the tree has the structure that you want it to have.
- eg.:

compare(t, "#aM#bM#c6M*");

1. # - assert not sentinel
2. a - assert tst->c == a
3. M - follow the middle pointer
4. # - assert not sentinel
5. b - assert tst->c == b
6. M - follow the middle pointer
7. # - assert not sentinel
8. c - assert tst->c == c
9. 6 - assert tst->x == 6
10. M - follow the middle pointer
11. * - assert it IS sentinel


- Included funtions amend and findNode in the .h file. These were initially
	static functions but having direct access to nodes was needed in the count
	program.
- I am aware that the insert and delete functions are iterative and therefore
	really messy. If I had more time I would probably redesign them and use
	recursion. They do work though, and the user doesn't need to know how (badly)
	the module is implemented.

- I included some pictures that I used of what the expected structure is after
	calling insert and then remove.

