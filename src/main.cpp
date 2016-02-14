#include <csaru-core-cpp/csaru-core-cpp.h>
#include <chip8/chip8.hpp>

int main (int argc, const char * argv[]) {

	std::printf("%d\n", argc);
	for (int i = 0; i < argc; ++i)
		std::printf("  %s\n", argv[i]);

	return 0;

}

