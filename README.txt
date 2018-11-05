Cosc 320 Lab 7: BST Timing
Jackson Bellinger 10/030/2018

In this lab, we implemented a Binary Search Tree, and timmed it's operations.
My class is mostly standard, but I used templates, and most of the functions are overloaded to work with either the root or a subtree.
To time the operations, I generated an array, and inserted each element, then searched for each element, and finally deleted each element.
I stored the elements in an array so that I could have consistent times for the operations, since if an element isn't present it'll just search down to the bottom. More importantly, I wanted to be able to test the worst case, and cases with random elements, and the best case.

          Best    Worst
Insert    O(logn) O(n)
Search    O(logn) O(n)
Delete    O(logn) O(n)
^(including searching for the element to delete)

When I tested the bst with random elements and sorted elements, the theoretical Big(O) seemed to be correct for the best/average case and worst case, respectively.

I would like to encapsulate my timing and plotting code into it's own repository, so that I can just include it and not have to write custom testing code for each algorithm or data structure I want to test. I also want to add textfile output so I don't have to copy from the terminal.
