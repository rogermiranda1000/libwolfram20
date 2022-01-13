#include <gtest/gtest.h>
#include "ProgramLauncher.h"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

TEST(solve, PrevistedOutput) {
	ForkedPipeInfo fork_pipe;
	char *command = (char*)malloc(sizeof(char) * (1 + STATIC_STRING_LEN("../solve/solve")));
	strcpy(command, "../solve/solve");
	
	EXPECT_EQ(executeProgramLineWithPipe(&fork_pipe, &command, NULL, NULL), 0) << "[e] Error executing 'solve' program";
	char *result;
	readUntil(fdPipeInfo(fork_pipe, 0), &result, '\n'); // discard the first one (Searching ...)
	readUntil(fdPipeInfo(fork_pipe, 0), &result, '\n'); // get the result
	freeForkedPipeInfo(&fork_pipe);
	
	// Expect two strings not to be equal.
	EXPECT_STREQ("Solution: x = 5/3", result) << "Unexpected result: " << result;
	free(result);
}

int main(int argc, char *argv[], char *envp[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}