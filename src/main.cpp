#include <cstdlib>
#include <cstdio>
#include <ctime>

#include <csaru-core-cpp/csaru-core-cpp.h>
#include <chip8/chip8.hpp>

int main (int argc, const char * argv[]) {

    std::printf("  --%s--\n", argv[0]);

    if (argc < 2) {
        std::fprintf(stderr, "Missing positional param: .c8 filepath.\n");
        return 1;
    }

    // take third param to be random seed; or just use time now
    unsigned randSeed = 0;
    if (argc >= 4)
        randSeed = unsigned(atoi(argv[3]));
    if (randSeed == 0)
        randSeed = std::time(0);

    // initialize
    Chip8 c;
    c.Initialize(randSeed);

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
    const unsigned lines = 10;
    for (unsigned i = 0; i < lines; ++i) {
        uint8_t * prog = c.m_memory + c.s_progRomRamBegin + i*4*2;
        std::printf(" 0x%02X%02X  0x%02X%02X    0x%02X%02X  0x%02X%02X\n",
            prog[0], prog[1],
            prog[2], prog[3],
            prog[4], prog[5],
            prog[6], prog[7]
        );
    }

    // emulate
    const unsigned cycleCountTarget = unsigned(std::atoi(argv[2]));
    std::printf("Emulating %u cycles...\n", cycleCountTarget);
    for (unsigned cycle = 0; cycle < cycleCountTarget; ++cycle) {
        uint16_t pcPre = c.m_pc;
        c.EmulateCycle();

        const char * format = nullptr;
        switch (cycle % 4) {
            case 0: format = " 0x%04X->0x%04X";    break;
            case 1: format = "  0x%04X->0x%04X";   break;
            case 2: format = "    0x%04X->0x%04X"; break;
            case 3: format = "  0x%04X->0x%04X\n";   break;
        }
        std::printf(format, pcPre, c.m_opcode);

        if (pcPre == c.m_pc) {
            std::printf(
                "\nHalted on opcode {0x%04X} at pc {0x%04X}.\n",
                c.m_opcode,
                c.m_pc
            );
            return 1;
        }
    }

    std::printf("\n"); // just in case we were still printing a table
	return 0;

}

