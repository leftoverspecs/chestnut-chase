#include <assets.h>

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <cassert>

int main() {
    std::ifstream file(ASSETS_DIRECTORY "/test.txt");
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    assert(!content.empty());
    return 0;
}
