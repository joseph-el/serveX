# pragma once

# include <iostream>

using namespace std;

template<typename Iterator, typename Func>
bool every(Iterator first, Iterator last, Func func) {
    while (first != last) {
        if (!func(*first))
            return false;
        ++first;
    }
    return (true);
}
