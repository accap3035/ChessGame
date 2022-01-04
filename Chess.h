#ifndef CHESS_H_
#define CHESS_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "PiecesArray.h"
#include "ChessGlobalDefinitions.h"

/*
Game Summary:
This module is an encapsulation of the game. It contains the gameboard, history,
current player, and boolean indicators regarding whether the king of each player is threatened.

A game should be handled with the GameHandler module, which wraps it with the settings and handles 
the game flow. 
*/

#define BOARD_ROWS_NUMBER 8
#define BOARD_COLUMNS_NUMBER 8
#define BOARD_EMPTY_CELL '_'

// Pieces defintions - lowercase
#define PIECE_PAWN 'p'
#define PIECE_BISHOP 'b'
#define PIECE_ROOK 'r'
#define PIECE_KNIGHT 'n'
#define PIECE_QUEEN 'q'
#define PIECE_KING 'k'

#define BOARD_WHITE_FIRST_ROW_INITAL_PIECES "rnbqkbnr"
#define BOARD_WHITE_SECOND_ROW_INITIAL_PIECES "pppppppp"
#define BOARD_BLACK_FIRST_ROW_INITAL_PIECES "RNBQKBNR"
#define BOARD_BLACK_SECOND_ROW_INITIAL_PIECES "PPPPPPPP"

/*
An enum for the current player.
*/
typedef enum game_player_e {
	White,
	Black
} GamePlayer;

typedef char GameBoard[BOARD_ROWS_NUMBER][BOARD_COLUMNS_NUMBER];

typedef enum square_type_e {
	BoardSquareInvalidMove,
	BoardSquareValidMove,
	BoardSquareCaptureMove,
	BoardSquareThreatMove,
	BoardSquareCaptureAndThreatMove,
	BoardSquareKingThreatMove
} BoardSquareMoveType;

typedef BoardSquareMoveType MovesBoardWithTypes[BOARD_ROWS_NUMBER][BOARD_COLUMNS_NUMBER];

typedef struct game_t {
	GameBoard gameBoard;
	GamePlayer currentPlayer;
	bool isBlackKingChecked;
	bool isWhiteKingChecked;
	PiecesArray * history;
} Game;

/**
* Type used for returning error codes from game functions.
*/
typedef enum game_message_t {
	GAME_MOVE_INVALID,
	GAME_MOVE_SUCCESS,
	GAME_MOVE_FAILED_KING_THREAT,
	GAME_MOVE_SUCCESS_CAPTURE,
	GAME_MOVE_FAILED_THREAT_CAPTURE,
	GAME_INVALID_SQUARE,
	GAME_INVALID_PIECE,
	GAME_INVALID_ARGUMENT,
	GAME_UNDO_NO_HISTORY,
	GAME_UNDO_SUCCESS,
	GAME_SUCCESS
} GAME_MESSAGE;

/*
Check winner function return messages.
*/
typedef enum game_check_winner_message_t {
	GAME_CHECK_WINNER_CURRENT_PLAYER_LOSE,
	GAME_CHECK_WINNER_DRAW,
	GAME_CHECK_WINNER_CONTINUE
} GAME_CHECK_WINNER_MESSAGE;

/*
Creates a game instance, with the initial Checkmate game state.
*/
Game * gameCreate(int historySize);
	
/*
Destroys the game instance and frees all memory.
*/
void gameDestroy(Game * game);

/*
Returns true if the square s is on the board.
*/
bool gameIsSquareValid(BoardSquare s);

/*
Moves the piece from square FROM to sqaure TO. Checks if the move is valid and also checks the parameters.
Will return:
	GAME_MOVE_SUCCESS
	GAME_MOVE_SUCCESS_CAPTURE
	GAME_MOVE_INVALID
	GAME_MOVE_FAILED_KING_THREAT
	GAME_MOVE_FAILED_THREAT_CAPTURE
*/
GAME_MESSAGE gameSetMove(Game * game, BoardSquare from, BoardSquare to);

/*
Sets a move with without performing any checks and even if the move causes a threat.
Saves the move to history.
*/
void gameForceSetMove(Game * game, BoardSquare from, BoardSquare to);

/*
Undo the previous move.
*/
GAME_MESSAGE gameUndoPrevMove(Game * game);

GAME_MESSAGE gamePrintBoard(Game * game);

/*
A wrapper that calls gameGetLegalMoves and then gameGetMovesByTypes. 
Checks parameters.
Returns:
	GAME_INVALID_SQUARE
	GAME_INVALID_PIECE
	GAME_SUCCESS
*/
GAME_MESSAGE gameGetMovesWrapper(Game * game, BoardSquare s, MovesBoardWithTypes movesBoardWithTypes);

/*
Updates movesBoard with the legal moves of the piece in square s. Assumes all arguments are valid
and movesBoard is initialized to false. Doesn't check threats.
*/
void gameGetLegalMoves(GameBoard gameBoard,
	bool movesBoard[BOARD_ROWS_NUMBER][BOARD_COLUMNS_NUMBER], BoardSquare s);

/*
Gets a moves board with all the legal moves of the piece in square s, and sets the moves types
in the movesBoardWithTypes board.
*/
void gameGetMovesByTypes(Game * game, bool movesBoard[BOARD_ROWS_NUMBER][BOARD_COLUMNS_NUMBER],
	MovesBoardWithTypes movesBoardWithTypes, BoardSquare s);

/*
Determines whether the king of the given player is in check state.
Checks the game board and not the game states.
*/
bool gameBoardKingIsChecked(GameBoard gameBoard, GamePlayer player);

GamePlayer gameGetCurrentPlayer(Game * game);

GamePlayer gameGetOtherPlayer(Game * game);

/*
Checks if the current player is checked.
*/
bool gameIsCurrentPlayerChecked(Game * game);

/*
Check if there is a winner or it's a draw (i.e, checks if the current player is losing or 
has no more moves but is not threatened).
Returns:
	GAME_CHECK_WINNER_CONTINUE
	GAME_CHECK_WINNER_CURRENT_PLAYER_LOSE
	GAME_CHECK_WINNER_DRAW
*/
GAME_CHECK_WINNER_MESSAGE gameCheckWinner(Game * game);

bool gameIsPieceOfCurrentPlayer(Game * game, BoardSquare s);

/*
Gets the TEXT of the current player (i.e white or black).
*/
char * gameGetCurrentPlayerColorText(Game * game);

/*
Changes the current player.
*/
void gameChangePlayer(Game * game);

/*
Return true if the move is valid (i.e, doesn't creates a king's threat
or invalid according to the rules.
*/
bool gameIsValidMove(BoardSquareMoveType moveType);

/*
Prints the game board to the given file.
*/
void gamePrintGameBoardToFileHandler(FILE * fh, Game * game);

#endif
