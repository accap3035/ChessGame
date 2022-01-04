#ifndef PIECES_ARRAY_H_
#define PIECES_ARRAY_H_
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include "ChessGlobalDefinitions.h" // for BoardSquare struct

typedef struct history_element_t {
	BoardSquare oldSquare;
	BoardSquare newSquare;
	char prevElementOnNewCell;
	bool isWhiteKingChecked;
	bool isBlackKingChecked;
} HistoryElement;

typedef struct array_list_t {
	HistoryElement * elements;
	int actualSize;
	int maxSize;
} PiecesArray;

// PiecesArray Errors // most functions will return one of this messages
typedef enum array_list_message_t {
	PIECES_ARRAY_SUCCESS,
	PIECES_ARRAY_INVALID_ARGUMENT,
	PIECES_ARRAY_FULL,
	PIECES_ARRAY_EMPTY
} PIECES_ARRAY_MESSAGE;

PiecesArray* piecesArrayCreate(int maxSize);

void piecesArrayDestroy(PiecesArray* src);

PIECES_ARRAY_MESSAGE piecesArrayAddAt(PiecesArray* src, HistoryElement elem, int index);

PIECES_ARRAY_MESSAGE piecesArrayAddFirst(PiecesArray* src, HistoryElement elem);

PIECES_ARRAY_MESSAGE piecesArrayAddLast(PiecesArray* src, HistoryElement elem);

PIECES_ARRAY_MESSAGE piecesArrayRemoveAt(PiecesArray* src, int index);

PIECES_ARRAY_MESSAGE piecesArrayRemoveFirst(PiecesArray* src);

PIECES_ARRAY_MESSAGE piecesArrayRemoveLast(PiecesArray* src);

HistoryElement piecesArrayGetAt(PiecesArray* src, int index);

HistoryElement piecesArrayGetFirst(PiecesArray* src);

HistoryElement piecesArrayGetLast(PiecesArray* src);

int piecesArrayMaxCapacity(PiecesArray* src);

int piecesArraySize(PiecesArray* src);

bool piecesArrayIsFull(PiecesArray* src);

bool piecesArrayIsEmpty(PiecesArray* src);

#endif
