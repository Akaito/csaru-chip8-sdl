#include <cstdio>

#include <csaru-core-cpp/csaru-core-cpp.h>
#include <chip8/chip8.hpp>

int main (int argc, const char * argv[]) {

    if (argc < 2) {
        std::fprintf(stderr, "Missing positional param: .c8 filepath.\n");
        return 1;
    }

    Chip8 c;
    c.Initialize();
    if (!c.LoadProgram(argv[1])) {
        std::fprintf(stderr, "Failed to load program {%s}.\n", argv[1]);
        return 1;
    }

	return 0;

}

