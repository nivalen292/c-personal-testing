#include "stdafx.h"
#include "String.h"
#include <iostream>

int main() {
	String str = "pesho e velik pesho";
	std::cout << str.split("pesho").join("gosho") << std::endl;
    return 0;
}

