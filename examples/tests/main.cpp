#include <gtest/gtest.h>
#include "ProgramLauncher.h"

TEST(solve, PrevistedOutput) {
	ForkedPipeInfo fork_pipe;
	char *command = (char*)malloc(sizeof(char) * (1 + STATIC_STRING_LEN("../solve/build/solve")));
	strcpy(command, "examples/solve/solve"); // POV libwolfram20 root directory
	
	ASSERT_EQ(executeProgramLineWithPipe(&fork_pipe, &command, NULL, NULL), 0) << "[e] Error executing 'solve' program";
	char *result;
	readUntil(fdPipeInfo(fork_pipe, 0), &result, '\n'); free(result); // discard the first one (Searching ...)
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