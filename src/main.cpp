#include<bits/stdc++.h>
#include "lib/common.hpp"
#include "lib/generator.hpp"

using namespace std;

int main() {

	ofstream MyFile("points.txt");

    SetGenerator gen;
    const auto rects = gen.rects(5);
    for (auto &&r : rects) {
        MyFile << r.upper_left.x << " " << r.upper_left.y << " : "
                  << r.lower_right.x << " " << r.lower_right.y << endl;
    }
    MyFile.close();
    return EXIT_SUCCESS;
}
