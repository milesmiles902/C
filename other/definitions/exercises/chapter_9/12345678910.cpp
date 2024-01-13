1.       A  B  C  D  E  F           ---7-----
      A     7  5        1           |       |
                                    A---2---B \
      B  2        7  3              |\\\     |\ \
      C     2           8           | \\\    2 \  \
      D  1           2  4           1  61\5\ |  \  |
      E  6        5                 |   \\   C  /  |
      F     1        8              D-5--E F-8 1   |
                                    |\-4--\ \  /   |
                                    |      3-\/    |
                                    |--7------------

2.    from        to      cost               1---=----3-------4
        1          2       10               / \       ||     ||
        1          3       15              /   2-------|     ||
        1          6        5             /            |     ||
        2          3        7            /             |     ||
        3          4        7           6--------------|     ||
        3          6        10          |\-------------------||
        4          5        7           ----------------------5
        6          4        5
        5          6        13

3.      1->2
         ->3
         ->6
      
        2->3
 
        3->4
         ->6
     
        4->5
     
        6->4
        
        5->6

              1
            / | \
           2  3  6
          /        
         3          
        /            
       4             
      /               
     5                 
    /     
   6      
            
3. The Big-O running time of Breadth First-Search buildGraph is O(n^3).
4. O(n)*O(n)=O(n*n)=O(n^2)
5. O(n)*O(n)*O(n)*O(n)=O(n^3)
6. O(n)*O(n)=O(n^2)
7. Graph from Part #1: 1 (10) 2, 2 (7) 3, 3 (7) 4, 4 (7) 5, 5 (13) 6
8. Read 1 email---->
   Write 1 email---> 1 Email ---> 1 friend    
   Send 1 email---->

   Read -> Write -> Send -> Email -> Friend

9. _N_
   | |O(n_i)=O(n^N)
    0

10. A Depth First Search is not suitable for Knights Tour because the distant neighbors require a second examination.

11. O(logn)*O(n)=O(nlogn)

