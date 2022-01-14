#include <gtest/gtest.h>
#include <unistd.h>				// fd
#include <iostream>
#include <sstream>				// stringstream
#include "ProgramLauncher.h"	// executeProgramLineWithPipe & ForkedPipeInfo

std::string fdToString(int fd) {
	std::stringstream r;
	
	char *result;
	while (readUntil(fd, &result, '\n') > 0) {
		r << result << std::endl;
		free(result);
	}
	
	return r.str();
}

std::string flushFd(ForkedPipeInfo fork_pipe) {
	std::stringstream r;
	
	for (size_t n = 0; n < fork_pipe.pipe_num; n++) {
		r << "-- FD " << n << " --" << std::endl;
		r << fdToString(fdPipeInfo(fork_pipe, n));
	}
	
	return r.str();
}

TEST(solve, PrevistedOutput) {
	ForkedPipeInfo fork_pipe;
	char *command = (char*)malloc(sizeof(char) * (1 + STATIC_STRING_LEN("../solve/build/solve")));
	strcpy(command, "examples/solve/solve"); // POV libwolfram20 root directory
	
	ASSERT_EQ(executeProgramLineWithPipe(&fork_pipe, &command, NULL, NULL), 0) << "[e] Error executing 'solve' program" << std::endl << flushFd(fork_pipe);
	char *result;
	discard(fdPipeInfo(fork_pipe, 1), '\n'); // discard the first line (Searching ...)
	readUntil(fdPipeInfo(fork_pipe, 1), &result, '\n'); // get the result
	
	// Expect two strings not to be equal.
	EXPECT_STREQ("Solution: x = 5/3", result) << "[w] Unexpected result: " << result;
	freeForkedPipeInfo(&fork_pipe);
	free(result);
}

int main(int argc, char *argv[], char *envp[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}