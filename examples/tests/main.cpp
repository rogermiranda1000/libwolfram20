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
	
	r << "-- cout --" << std::endl;
	r << fdToString(fdPipeInfo(fork_pipe, 1));
	r << "-- cerr --" << std::endl;
	r << fdToString(fdPipeInfo(fork_pipe, 2));
	
	return r.str();
}

char *getExamplePath(char *example) {
	char *command = (char*)malloc(sizeof(char) * (1 + STATIC_STRING_LEN("examples//build/") + 2*strlen(example))); // POV libwolfram20 root directory
	strcpy(command, "examples/");
	strcat(command, example);
	strcat(command, "/build/");
	strcat(command, example);
	return command;
}

TEST(solve, PrevistedOutput) {
	ForkedPipeInfo fork_pipe;
	char *command = getExamplePath("solve");
	
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