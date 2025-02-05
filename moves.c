#include <stdio.h>
#include <stdlib.h>

#include "moves.h"

int getPlayerSwap(enum Colour player)
{
  int swap;

  switch (player)
  {
  case WHITE:
    swap = 0;
    break;
  case BLACK:
    swap = -1;
    break;
  default:
    return 0;
    break;
  }

  return swap;
}

int validatePawnMove(Board board, Move move, Piece *piece, enum Colour player)
{
  Piece *pieceAtDest = board[move.toY][move.toX];

  int swap = getPlayerSwap(player);

  if ((move.toY < move.fromY) + swap)
  {
    printf("%s", "Cannot move pawn backwards!\n");
    return 0;
  }

  if (move.toX != move.fromX)
  {
    if (abs(move.toY - move.fromY) > 1 || abs(move.toX - move.fromX) > 1 || pieceAtDest == NULL) 
    {
      printf("%s", "Invalid diagonal move!\n");
      return 0;
    }
  }

  if (abs(move.toY - move.fromY) > 2)
  {
    printf("%s", "Cannot move pawn more than 2 spaces!\n");
    return 0;
  }

  if (abs(move.toY - move.fromY) > 1 && piece->timesMoved > 0) 
  {
    printf("%s", "Cannot move pawn 2 spaces after its first move!\n");
    return 0;
  }

  return 1;
}
