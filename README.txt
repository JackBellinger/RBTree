Cosc 320 Lab 8: Red-Black Tree + Timing
Jackson Bellinger 11/6/2018

In this lab, we implemented a Red-Black Tree, and timed its operations.
My class is mostly standard, but I used templates, and most of the functions are overloaded to work with either the root or a subtree.
To time the operations, I generated an array, and inserted each element, then searched for each element, and finally deleted each element.
I stored the elements in an array so that I could have consistent times for the operations, since if an element isn't present it'll just search down to the bottom. More importantly, I wanted to be able to test the worst case, and cases with random elements, and the best case.

          Best    Worst
Insert    O(logn) O(logn)
Search    O(logn) O(logn)
Delete    O(logn) O(logn)
Fixup     O(1)    O(logn)

I plotted the graph of the times, averaged over 10 samples, and all of the operations appear to be O(logn), at least for all of the sizes I tested.
(the nlogn and n^2 functions are multiplied by a small constant so that they're visible. 0.00001 * nlogn and 0.00000012 * n^2)

I would still like to encapsulate my timing and plotting code into it's own repository, so that I can just include it and not have to write custom testing code for each algorithm or data structure I want to test. However, when trying to do this, I realized I would need either some way to pass an arbitrary data structure to the timing function, in the case of trees, and function pointers, in the case of the sorting algorithms. I may just implement two different timing functions. Also, me and Billy were talking about creating a library of helper functions, including things like swap, sorting, some data structures, etc. Once I figure out the timing class I would like to add that to such a library.
Also, I was thinking about creating a base class for my data structures, that would let me define the comparison operators, ostream(tostring) and other functions commonly needed. That way I could use that class instead of templates, which would be easier to code, and would ensure that more data types could be added without having to edit them to have the requied operators, etc.

