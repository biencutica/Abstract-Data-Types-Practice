#include "Bag.h"
#include <iostream>

using namespace std;

int main() {

    //integers
    Bag<int> int_bag;
    int_bag.add(1);
    int_bag.add(2);
    int_bag.add(3);

    //doubles
    Bag<double> double_bag;
    double_bag.add(1.2);
    double_bag.add(3.4);
    double_bag.add(5.6);

    //strings
    Bag<std::string> string_bag;
    string_bag.add("Hello");
    string_bag.add("World");
    string_bag.add("!");

    // Print the contents of each bag
    std::cout << "Contents of int_bag:" << std::endl;
    int_bag.print();

    std::cout << "Contents of double_bag:" << std::endl;
    double_bag.print();

    std::cout << "Contents of string_bag:" << std::endl;
    string_bag.print();
    cout << "Code successfully run.";
    return 0;
}
