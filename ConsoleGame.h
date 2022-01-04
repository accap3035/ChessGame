#include <stdio.h>
#include "CommandParsing.h"
#include "GameHandler.h"
#define BLACK 0
#define WHITE 1
#define GAME_MODE_ONE_PLAYER 1
#define GAME_MODE_TWO_PLAYERS 2
#define GAME_DIFFICULTY_MIN_LEVEL 1
#define GAME_DIFFICULTY_MAX_LEVEL 5 
// Actually I can increase the level this will increase depth in alpha beta pruning
// and make more search on possible moves
// but I preferred to use 5 level for difficulty
typedef enum return_msg_e {
	CgMsgQuit,
	CgMsgStart,
	CgMsgMallocError,
	CgMsgReset,
	CgMsgLoad 
} CgMsg; 

typedef enum error_type_e {
	CgErrCmdInvalid,
} CgErrorType;

void consoleGameRun();
