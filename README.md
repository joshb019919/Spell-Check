Load a dictionary of words into a hash with collisions resolved via linked-lists.
Spellcheck input text words against that hash.

### Usage: ./speller [DICTIONARY] text ###

The program was required to not leak memory, and none of the distro files were allowed to be altered save for adding function prototypes.  I implemented load, hash, size, check, and unload in dictionary.c

This is a program based on [specifications](https://cs50.harvard.edu/x/2020/psets/5/speller/ "Spell Check") given by HarvardX's online cs50 course.
