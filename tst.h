/* This is a library module supporting Ternary Search Trees (TSTs).
It allows the user to store strings and associated values.
The characters are stored in nodes.
Each node has 3 children: smaller (left), equal (middle) and larger (right).
This avoids using a large number of NULL pointers as with an R-way Trie
*/

struct tst;
typedef struct tst tst;

// Create a new empty TST and return a pointer to it.
tst *newTst();

// Insert a string into a TST. It is illegal to inser a string that already exists.
void insertString(tst *t, int x, char *c);

// Search for a string and return its associated value if found, or -1 if not found.
int search(tst *t, char *c);

// Remove a string by setting its value to NULL. If possible also remove any
// unused nodes.
void removeString(tst *t, char *c);
