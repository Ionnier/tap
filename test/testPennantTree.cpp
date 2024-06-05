//
// Created by Dragos BAHRIM on 16.04.2024.
//
#include <iostream>
#include <Bag.h>
using namespace std;

int main() {
//    BinaryTree<int> x(1, new BinaryTree<int>(2), new BinaryTree<int>(3));
//    BinaryTree<int> y(5, new BinaryTree<int>(6), new BinaryTree<int>(7));
//    BinaryTree<int> e(10, &x, &y);
//    auto s = PennantTree<int>::init(&e, 15);
//    auto l = PennantTree<int>::reunion(s, s);
//    auto p = l->split();
//    cout << *p.first;
//    cout << *p.second;
    Bag<int> g;
    g.insert(10);
//    g.insert(20);
//    g.insert(30);
//    g.insert(40);
//    g.insert(50);
//    g.insert(60);

//    Bag<int> e;
//    e.insert(1);

//    cout << *Bag<int>::reunion(&g, &e);

    cout << g;
    cout << "Hsad\n";
    cout << *Bag<int>::split(&g);
    cout << g;


//    cout << g;
    return 0;
}

