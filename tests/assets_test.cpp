#include <test.txt.h>

#include <iostream>
#include <cassert>
#include <string>

int main() {
    std::string content(reinterpret_cast<const char *>(test), sizeof(test));
    assert(!content.empty());
    std::cout << content << '\n';
    return 0;
}
