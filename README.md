CMTreeMiner Ordered: an algorithm for mining closed and maximal frequent rooted ordered trees

Citation information:

[1] Yun Chi, Yirong Yang, Yi Xia, and Richard R. Muntz. Cmtreeminer: Mining both closed and maximal frequent subtrees. In PAKDD'04: Proceedings of the 8th Pacific-Asia in Knowledge Discovery and Data Mining, pages 63-73, Sydney, Australia, 2004. Springer.

[2] Yun Chi, Yi Xia, Yirong Yang, and Richard R. Muntz. Mining closed and maximal frequent subtrees from databases of labeled rooted trees. IEEE Trans. Knowl. Data Eng., 17(2):190-202, 2005.

1) The input should be text file in Professor Zaki's string encoding form: each line represents a transaction; the first two numbers are identical, they are tids; the 3rd number represents the length of the remaining string; the rest string is a depth-first traversal of the rooted ordered tree, where "-1" means a backtrack. For example, here is a database with 3 rooted ordered trees.

0 0 15 1 2 3 -1 4 -1 5 -1 -1 6 7 -1 8 -1 -1

1 1 15 1 2 3 -1 4 -1 5 -1 -1 6 7 8 -1 -1 -1

2 2 9 1 6 7 8 9 -1 -1 -1 -1

2) The above database is given in "example_rooted_ordered.txt". Notice that the trees have no edge labels.

3) Usage: CMOrderedTreeMiner support input_file output_file
where support is an integer, i.e., minimal number of occurrence

4) Output file contains the running time. It also contains the number of trees that have been checked by the algorithm, the number of closed trees, and the number of maximal trees, for each tree size.
