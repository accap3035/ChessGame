#ifndef EXTENDED_MINIMAX_H
#define EXTENDED_MINIMAX_H

#include <limits.h>
#include "Chess.h"

typedef struct move_t {
	BoardSquare oldSquare;
	BoardSquare newSquare;
} Move;

typedef struct move_and_value_t {
	Move move;
	int value;
} MoveAndValue;

Move minimaxSuggestMove(Game * game, int level);
#endif