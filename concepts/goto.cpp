#include <iostream>

void func(void* target){
    std::cout << "func" <<std::endl;
    goto *target;
}


int main() {
    void* target;
    bool flag = true;
l:
    std::cout << "label" <<std::endl;
    target = &&l;
    if (flag) {
        flag = false;
        func(target);
  }
}