#include <gtest/gtest.h>
#include <unistd.h>
#include "ProgramLauncher.h"

std::string fdToString(int fd) {
	std::string r("");
	
	char *result;
	while (readUntil(fd, &result, '\n') > 0) {
		r += std::string(result) + "\n";
		free(result);
	}
	
	return r;
}

TEST(solve, PrevistedOutput) {
	ForkedPipeInfo fork_pipe;
	char *command = (char*)malloc(sizeof(char) * (1 + STATIC_STRING_LEN("../solve/build/solve")));
	strcpy(command, "examples/solve/solve"); // POV libwolfram20 root directory
	
	ASSERT_EQ(executeProgramLineWithPipe(&fork_pipe, &command, NULL, NULL), 0) << "[e] Error executing 'solve' program" << std::endl << fdToString(fdPipeInfo(fork_pipe, 2));
	char *result;
	discard(fdPipeInfo(fork_pipe, 1), '\n'); // discard the first line (Searching ...)
	readUntil(fdPipeInfo(fork_pipe, 1), &result, '\n'); // get the result
	
	// Expect two strings not to be equal.
	EXPECT_STREQ("Solution: x = 5/3", result) << "[w] Unexpected result: " << result << std::endl << fdToString(fdPipeInfo(fork_pipe, 2));
	freeForkedPipeInfo(&fork_pipe);
	free(result);
}

int main(int argc, char *argv[], char *envp[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}