#include <cstdlib>
#include <cstdio>

#include <csaru-core-cpp/csaru-core-cpp.h>
#include <chip8/chip8.hpp>

int main (int argc, const char * argv[]) {

    std::printf("  --%s--\n", argv[0]);

    if (argc < 2) {
        std::fprintf(stderr, "Missing positional param: .c8 filepath.\n");
        return 1;
    }

    // initialize
    Chip8 c;
    c.Initialize();

    // load program
    if (!c.LoadProgram(argv[1])) {
        std::fprintf(stderr, "Failed to load program {%s}.\n", argv[1]);
        return 1;
    }
    std::printf("Loaded program: %s\n", argv[1]);

    if (argc < 3) {
        std::fprintf(stderr, "Missing second positinal param: cycles to emulate.\n");
        return 1;
    }

    // dump program head
    /*
    const unsigned lines = 10;
    for (unsigned i = 0; i < lines; ++i) {
        std::printf(" 0x%02X%02X  0x%04X    0x%04X  0x%04X\n",
            ops[0], ops[1], ops[1], ops[2], ops[3]
        );
    }
    */

    // emulate
    const unsigned cycleCount = unsigned(std::atoi(argv[2]));
    std::printf("Emulating %u cycles...\n", cycleCount);
    for (unsigned i = 0; i < cycleCount; ++i) {
        c.EmulateCycle();

        std::printf("Ran opcode 0x%04X\n", c.m_opcode);
        std::printf("  pc:\t0x%04X\n", c.m_pc);
    }

	return 0;

}

