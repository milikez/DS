#include "List.h"
#include <cassert>
#include <iterator>

// 测试默认构造函数
void testDefaultConstructor() {
    List<int> list;
    assert(list.size() == 0);
    assert(list.empty());
    list.printList();   // expect empty line
}

// 测试初始化列表构造函数
void testInitializerListConstructor() {
    List<int> list = {1, 2, 3, 4, 5};
    assert(list.size() == 5);
    assert(*(list.begin()) == 1 && *(--list.end()) == 5);
    list.printList();   // expect: 1 2 3 4 5
}

// 测试拷贝构造函数
void testCopyConstructor() {
    List<int> list1 = {1, 2, 3, 4, 5};
    List<int> list2(list1);
    assert(list2.size() == 5);
    assert(*list2.begin() == 1 && *(--list2.end()) == 5);
    list1.printList();  // expect: 1 2 3 4 5
    list2.printList();  // expect: 1 2 3 4 5
}

// 测试移动构造函数
void testMoveConstructor() {
    List<std::string> list1 = {"one", "two", "three"};
    List<std::string> list2(std::move(list1));
    assert(list1.size() == 0);
    assert(list2.size() == 3);
    assert(*list2.begin() == "one" && *(--list2.end()) == "three");
    // list1.printList(); 尝试访问会导致程序崩溃，因为 head 和 tail 都被指向 nullptr 而不是一个有效的节点
    list2.printList();  // expect: one two three
}

// 测试赋值运算符
void testAssignmentOperator() {
    List<int> list1 = {1, 2, 3, 4, 5};
    List<int> list2;
    list2 = list1;
    assert(list2.size() == 5);
    assert(*list2.begin() == 1 && *(--list2.end()) == 5);
    list1.printList();  // expect: 1 2 3 4 5
    list2.printList();  // expect: 1 2 3 4 5
}

// 测试移动赋值运算符
void testMoveAssignmentOperator() {
    List<std::string> list1 = {"one", "two", "three"};
    List<std::string> list2;
    list2 = std::move(list1);
    assert(list1.size() == 0);
    assert(list2.size() == 3);
    assert(*list2.begin() == "one" && *(--list2.end()) == "three");
    // list1.printList();
    list2.printList();  // expect: one two three
}

// 测试插入和删除函数
void testInsertAndErase() {
    List<int> list = {4, 5, 6};
    
    // 插入元素
    list.insert(list.end(), 1);
    list.insert(list.end(), 2);
    list.insert(list.end(), 1 + 2); // 右值
    assert(list.size() == 6);
    assert(*list.begin() == 4 && *(--list.end()) == 3);
    list.printList();   // expect: 4 5 6 1 2 3

    // 删除元素
    list.erase(list.begin());
    list.erase(list.begin());
    list.erase(--list.end());
    assert(list.size() == 3);
    assert(*list.begin() == 6 && *(--list.end()) == 2);
    list.printList();   // expect: 6 1 2

    // 再次插入元素
    list.insert(list.begin(), 0 + 0);   // 右值
    list.insert(++list.begin(), 7);
    assert(list.size() == 5);
    assert(*list.begin() == 0 && *(++list.begin()) == 7);
    list.printList();   // expect: 0 7 6 1 2

    // 删除指定范围的数据节点
    list.erase(++list.begin(), --list.end());
    assert(list.size() == 2);
    assert(*list.begin() == 0 && *(--list.end()) == 2);
    list.printList();   // expect: 0 2

    // 清除所有元素
    list.clear();
    assert(list.size() == 0);
    list.printList();   // expect empty line
}

// 测试push和pop函数
void testPushAndPop() {
    List<float> list = {0.1, 0.2, 0.3, 0.4};

    // 插入数据到list头部
    list.push_front(-0.1);
    list.push_front(1.0 - 1.2); // 右值
    assert(list.size() == 6);
    list.printList();   // expect: -0.2 -0.1 0.1 0.2 0.3 0.4

    // 插入数据到list尾部
    list.push_back(0.5);
    list.push_back(0.3 + 0.3);  // 右值
    assert(list.size() == 8);
    list.printList();   // expect: -0.2 -0.1 0.1 0.2 0.3 0.4 0.5 0.6

    // 删除第1个节点的数据
    list.pop_front();
    list.pop_front();
    assert(list.size() == 6);
    list.printList();   // expect: 0.1 0.2 0.3 0.4 0.5 0.6

    // 删除最后1个节点的数据
    list.pop_back();
    assert(list.size() == 5);
    list.printList();   // expect: 0.1 0.2 0.3 0.4 0.5
}

// 测试迭代器
void testIterators() {
    List<int> list = {1, 2, 3, 4, 5};

    // 测试 iterator
    auto it = list.begin();
    auto cit = list.begin();
    assert(it == cit);
    assert(*it == 1);
    assert(*cit == 1);
    ++it;
    cit++;
    assert(*it == 2);
    assert(*cit == 2);
    --it;
    cit--;
    assert(it == cit);
    assert(*it == 1);
    assert(*cit == 1);

    // 测试 const_iterator
    // 使用const_iterator遍历List
    for (List<int>::const_iterator c_it = list.begin(); c_it != list.end(); ++c_it) {
        std::cout << *c_it << " "; 
    }
    std::cout << std::endl;     // expect: 1 2 3 4 5
    
    // 使用const_iterator验证特定值
    List<int>::const_iterator c_cit = --list.end();
    for (int i = 5; i > 0; --i, --c_cit) {
        assert(*c_cit == i); // 再次使用operator*来获取当前节点的数据
    }

    // 测试返回值为 const 的情况
    const List<int>& constList = list;
    assert(constList.front() == 1);
    assert(constList.back() == 5);

}

// 测试边界条件
void testBoundaryConditions() {
    List<int> list;
    assert(list.size() == 0);
    assert(list.empty());
    list.push_back(1);
    assert(list.size() == 1);
    assert(!list.empty());
    list.push_back(2);
    list.push_front(0);
    assert(list.size() == 3);
    assert(list.front() == 0);
    assert(list.back() == 2);
    list.pop_front();
    list.pop_back();
    assert(list.size() == 1);
    assert(list.front() == 1);
    assert(list.back() == 1);
}

// bug 复现
void bug1() {
    List<int> list;
    printf("front = %d\n", list.front());
    printf("back = %d\n", list.back());
}

void bug2() {
    List<int> list {1, 2, 3};
    list.erase(list.end()); 
}

int main() {
    testDefaultConstructor();
    testInitializerListConstructor();
    testCopyConstructor();
    testMoveConstructor();
    testAssignmentOperator();
    testMoveAssignmentOperator();
    testInsertAndErase();
    testPushAndPop();
    testIterators();
    testBoundaryConditions();
    std::cout << "All tests passed!" << std::endl;

    // bug2();
    // bug1();

    return 0;
}