#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "moves.h"

const enum PieceType DEFAULT_LAYOUT[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN};

void initialiseBoard(Board board)
{
  int x, y, step;

  /* Add bottom (white) pieces */
  for (y = 0; y < 2; y++)
  {
    step = y * 8;
    for (x = 0; x < 8; x++)
    {
      Piece *newPiece = malloc(sizeof(Piece));
      newPiece->type = DEFAULT_LAYOUT[x + step];
      newPiece->colour = WHITE;
      newPiece->timesMoved = 0;

      board[y][x] = newPiece;
    }
  }

  /* Add top (black) pieces */
  for (y = 7; y > 5; y--)
  {
    step = -(y - 7) * 8;
    for (x = 0; x < 8; x++)
    {
      Piece *newPiece = malloc(sizeof(Piece));
      newPiece->type = DEFAULT_LAYOUT[x + step];
      newPiece->colour = BLACK;
      newPiece->timesMoved = 0;

      board[y][x] = newPiece;
    }
  }

  /* Fill all other squares to NULL */
  for (y = 2; y < 6; y++)
  {
    for (x = 0; x < 8; x++)
    {
      board[y][x] = NULL;
    }
  }
}

void printBoard(Board board)
{
  int x, y;
  char toPrint;
  Piece *square;

  for (y = 7; y >= 0; y--)
  {
    printf("  %d  ", y + 1);

    for (x = 0; x < 8; x++)
    {
      square = board[y][x];

      if (square == NULL)
      {
        toPrint = ' ';
      }
      else
      {
        switch (square->type)
        {
        case PAWN:
          toPrint = 'P';
          break;
        case ROOK:
          toPrint = 'R';
          break;
        case KNIGHT:
          toPrint = 'N';
          break;
        case BISHOP:
          toPrint = 'B';
          break;
        case QUEEN:
          toPrint = 'Q';
          break;
        case KING:
          toPrint = 'K';
          break;
        default:
          break;
        }

        if (square->colour == WHITE)
        {
          toPrint += 32;
        }
      }
      printf("|%c|", toPrint);
    }
    printf("%s", "\n");
  }
  printf("%s", "      A  B  C  D  E  F  G  H  \n");
}

void freeBoard(Board board)
{
  int x, y;
  Piece *square;

  for (y = 7; y >= 0; y--)
  {
    for (x = 0; x < 8; x++)
    {
      square = board[y][x];

      if (square != NULL)
      {
        free(square);
      }
    }
  }
}

int validLetter(char c)
{
  return (c <= 72 && c >= 65);
}

int validNumber(int n)
{
  return (n <= 56 && n >= 49);
}

int validateCoords(char *coords)
{
  if (coords[2] != 32)
  {
    printf("%s\n", "Please enter two valid coordinates separated by a space.");
    return 0;
  }

  if (!validLetter(coords[0]) || !validLetter(coords[3]))
  {
    printf("%s\n", "Please enter a valid letter A-F in upper case.");
    return 0;
  }

  if (!validNumber(coords[1]) || !validNumber(coords[4]))
  {
    printf("%s\n", "Please enter a valid number 1-8");
    return 0;
  }

  if (coords[0] == coords[3] && coords[1] == coords[4])
  {
    printf("%s\n", "Cannot move piece to same space!");
    return 0;
  }

  return 1;
}

Move parseCoords(char *coords)
{
  Move move;
  move.fromX = coords[0] - 65;
  move.fromY = coords[1] - 49;
  move.toX = coords[3] - 65;
  move.toY = coords[4] - 49;

  return move;
}

int validateTurn(Board board, Move move, Piece *piece, enum Colour player)
{
  if (piece == NULL) 
  {
    printf("%s", "Cannot move a non-existent piece!\n");
    return 0;
  }
  
  if (piece->colour != player) {
    printf("%s Player! That is not your piece!\n", player ? "WHITE" : "BLACK");
    return 0;
  }

  switch (piece->type)
  {
    case PAWN:
      return validatePawnMove(board, move, piece, player);
      break;
    default:
      break;
  }

  return 1;
}

void executeTurn(Board board, enum Colour player)
{
  Move move;
  Piece *piece;
  char inputCoords[7];

  printBoard(board);

  do
  {
    do
    {
      printf("%s Player - Please input your move in the format [A1 B1]: ", player ? "WHITE" : "BLACK");
      readInput(inputCoords, sizeof(inputCoords));
    } while (!validateCoords(inputCoords));

    move = parseCoords(inputCoords);
    piece = board[move.fromY][move.fromX];

  } while (!validateTurn(board, move, piece, player));

  piece->timesMoved++;

  board[move.toY][move.toX] = piece;
  board[move.fromY][move.fromX] = NULL;
}

void clearInputBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}

void readInput(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            clearInputBuffer();
        }
    }
}

int main(int argc, char **args)
{
  int gameOver = 0, turn = 1;
  Board board = {{NULL}};

  initialiseBoard(board);

  do
  {
    executeTurn(board, (turn % 2));
    system("clear");
    turn++;
  } while (!gameOver);

  freeBoard(board);

  return 0;
}
