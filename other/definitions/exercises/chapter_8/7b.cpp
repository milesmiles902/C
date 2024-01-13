string printexp(BinaryTree *tree){
    string sVal;
    if (tree){
        sVal = printexp(tree->getLeftChild());
        sVal = sVal + tree->getRootVal();
        sVal = sVal + printexp(tree->getRightChild());
    }
    return sVal;
}
