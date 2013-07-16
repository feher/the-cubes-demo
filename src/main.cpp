// Description: Object selection demo
// Author: Gabor Fekete
// Version: 2013.07.04
// Copyright: Gabor Fekete
//

#include "thecubes.h"

#include <iostream>

using namespace std;

int main(void) {
    try {
        TheCubes(1024, 768).run();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
