#include <iostream>
#include "BinarySearchTree.h"  // 假设 BinarySearchTree 类定义在这个头文件中

void testBinarySearchTree() {
    BinarySearchTree<int> bst;

    // 测试插入功能
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    // 测试打印树结构
    std::cout << "Initial Tree:" << std::endl;
    bst.printTree();

    // 测试删除功能
    bst.remove(7);
    std::cout << "Tree after removing 7:" << std::endl;
    bst.printTree();

    bst.remove(5);
    std::cout << "Tree after removing 5:" << std::endl;
    bst.printTree();

    bst.insert(1);
    bst.insert(4);
    bst.remove(3);
    std::cout << "Tree after removing 3:" << std::endl;
    bst.printTree();
    
    bst.remove(10);
    std::cout << "Tree after removing 10:" << std::endl;
    bst.printTree();
}

int main() {
    testBinarySearchTree();
    return 0;
}