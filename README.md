Build using `make re` to recompile without debugger. Use `make debug` to recompile with fsanitizer.



Run using `./leak_test X` where X is a number ranging from 1 to 9 included.

To run with valgrind, use `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./leak_test X`

Remember to never use valgrind on a program compiled using fsanitizer.



Run tests without and with various debugging tools and observe the differences :)
