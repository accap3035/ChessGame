#include "PiecesArray.h"

PiecesArray* piecesArrayCreate(int maxSize) {
	if (maxSize <= 0) return NULL;

	PiecesArray *al = (PiecesArray*)(malloc(sizeof(PiecesArray)));
	if (al == NULL) return NULL;

	al->elements = (HistoryElement*)(malloc(sizeof(HistoryElement) * maxSize));
	// in case memory can not be allocated for elements
	if (al->elements == NULL) {
		free(al);
		return NULL;
	}

	al->maxSize = maxSize;
	al->actualSize = 0;

	return al;
}

void piecesArrayDestroy(PiecesArray* src) {
	if (src == NULL) return;

	free(src->elements);
	free(src);
}


PIECES_ARRAY_MESSAGE piecesArrayAddAt(PiecesArray* src, HistoryElement elem, int index) {
	if (src == NULL || index < 0 || index > src->actualSize) {
		return PIECES_ARRAY_INVALID_ARGUMENT;
	}

	if (src->actualSize == src->maxSize) return PIECES_ARRAY_FULL;

	// shift the array!
	for (int i = src->actualSize - 1; i >= index; i--) {
		(src->elements)[i + 1] = (src->elements)[i];
	}

	// insert new val
	(src->elements)[index] = elem;
	(src->actualSize)++;

	return PIECES_ARRAY_SUCCESS;
}

PIECES_ARRAY_MESSAGE piecesArrayAddFirst(PiecesArray* src, HistoryElement elem) {
	return piecesArrayAddAt(src, elem, 0);
}

PIECES_ARRAY_MESSAGE piecesArrayAddLast(PiecesArray* src, HistoryElement elem) {
	if ((void*)src == NULL) return PIECES_ARRAY_INVALID_ARGUMENT;

	if (src->actualSize == src->maxSize) return PIECES_ARRAY_FULL;

	return piecesArrayAddAt(src, elem, src->actualSize);
}

PIECES_ARRAY_MESSAGE piecesArrayRemoveAt(PiecesArray* src, int index) {
	if ((void*)src == NULL || index < 0 || index >= src->actualSize) {
		return PIECES_ARRAY_INVALID_ARGUMENT;
	}
	if (src->actualSize == 0) return PIECES_ARRAY_EMPTY;

	// shift the array!
	for (int i = index + 1; i < src->actualSize; i++) {
		(src->elements)[i - 1] = (src->elements)[i];
	}

	(src->actualSize)--;

	return PIECES_ARRAY_SUCCESS;
}

PIECES_ARRAY_MESSAGE piecesArrayRemoveFirst(PiecesArray* src) {
	if (src == NULL) return PIECES_ARRAY_INVALID_ARGUMENT;

	if (src->actualSize == 0) return PIECES_ARRAY_EMPTY;

	return piecesArrayRemoveAt(src, 0);
}

PIECES_ARRAY_MESSAGE piecesArrayRemoveLast(PiecesArray* src) {
	if ((void*)src == NULL) return PIECES_ARRAY_INVALID_ARGUMENT;

	if (src->actualSize == 0) return PIECES_ARRAY_EMPTY;

	return piecesArrayRemoveAt(src, src->actualSize - 1);
}

HistoryElement piecesArrayGetAt(PiecesArray* src, int index) {
	if (src == NULL || index < 0 || index >= src->actualSize) {
		return (HistoryElement) { .oldSquare = { -1, -1 } };
	}

	return src->elements[index];
}

HistoryElement piecesArrayGetFirst(PiecesArray* src) {
	return piecesArrayGetAt(src, 0);
}

HistoryElement piecesArrayGetLast(PiecesArray* src) {
	if (src == NULL) return (HistoryElement) { .oldSquare = { -1, -1 } };

	return piecesArrayGetAt(src, src->actualSize - 1);
}

int piecesArrayMaxCapacity(PiecesArray* src) {
	if (src == NULL) return -1;

	return src->maxSize;
}

int piecesArraySize(PiecesArray* src) {
	if (src == NULL) return -1;

	return src->actualSize;
}

bool piecesArrayIsFull(PiecesArray* src) {
	if (src == NULL) return false;

	return src->actualSize == src->maxSize;
}

bool piecesArrayIsEmpty(PiecesArray* src) {
	if (src == NULL) return false;

	return src->actualSize == 0;
}
