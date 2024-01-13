1. Draw the tree structure resulting from the following set of tree function calls:
   4            4                 4                           9          9
  |            |                 | |                         |          |
  3            3                 3 6                         4          4
               |                 |                          | |        | |
               5                 5                          3 6        3 6
                                                                       |
                                                                       11

2. (4*8)/6-3

  Prefix:           -
                 *     3
               4   /
                  8   6
                      
3. [1,2,3,4,5,6,7,8,9,10]

  Binary Tree:                       1
                                    /
                                   2
                                  /
                                 3
                                /
                               4
                              /
                             5
                            /
                           6
                          /
                         7
                        /
                       8
                      /
                     9
                    /
                   10

4. [10,9,8,7,6,5,4,3,2,1]

  Binary Tree:                       10
                                    /
                                   9
                                  /
                                 8
                                /
                               7
                              /
                             6
                            /
                           5
                          /
                         4
                        /
                       3
                      /
                     2
                    /
                   1

5. [1,3,4,6]

    Binary Heap:              1
                             / \
                            3   4
                           /
                          6

6. [1,3,4,6]
   Binary Heap:             
                              1
                             / \
                            3   4
                           /
                          6

7. 68, 88, 61, 89, 94, 50, 4, 76, 66, 82

                               68
                              /   \         
                            61      88
                           / \     /  \
                         4    50   94   89
                                    \   / \
                                    82 66 76

8. [1,3,4,6]
    
    Binary Search Tree:                  1
                                        / \
                                       3   4
                                            \
                                             6

9. [1,2,3,4,5,6,7,8,9,10]
  
   Binary Heap:    1        1       1      1        1       1      1         1        1        1
                            /       /\    /\        /\      /\     /\       /\        /\       /\
                           2       2  3  2  3      2  3    2  3   2  3     2  3      2  3     2  3
                                        /          /\     /\  /   /\ /\   /\  /\     /\ /\    /\ /\
                                       4          4 5    4 5 6   4 5 6 7 4 5 6 7    4 5 6 7  4 5 6 7 
                                                                         /         /\       /\ /
                                                                        8         8 9      8 9 10
10. [10,9,8,7,6,5,4,3,1]   10   9       8       7         6        5         4             3               2                1
                                 \     / \     / \       / \      / \       / \           / \             /\                /\
                                 10   9  10   8   9     7   8    6   7     5   6         4   5           3  4              2  3
                                             /         / \      / \  /    /\   /\       /\   /\         /\  /\            /\  /\
                                            10        9   10   8  9 10   7  8 9  10    6  7 8  9       5  6 7 8          4  5  6 7
                                                                                      /               /\                /\  /
                                                                                     10              9  10             8 9 10
                                                       
11. A check of a binary tree is required before methods: preorder, inorder, and postorder. The tree arrangement is unique to each type of traversal. 

12. BinaryTree a = new BinaryTree("language");
    a.insertLeft("compiled");
    a.insertRight("interpreted");
   (a.getLeftChild).insertLeft("C")
   (a.getLeftChild).insertRight("Java");
   (a.getRightChild).insertLeft("Python");
   (a.getRightChild).insertRight("Scheme");

13.        B(-2)                      E(1)
          /     \                    /    \
        A(0)    E(1)              B(-1)   D(0)
                /  \             /      /    \
              D(1)  F(0)       A(0)    C(0)  F(0)
              /
            C(0)                         

14. Left Rotation.               
