#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

const enum PieceType DEFAULT_LAYOUT[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN};

void initialiseBoard(BOARD board)
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

void printBoard(BOARD board)
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

void freeBoard(BOARD board)
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

  return 1;
}

Move parseCoords(char *coords)
{
  Move move;
  move.fromX = coords[0] - 65;
  move.fromY = coords[1] - 8;
  move.toX = coords[3] - 65;
  move.toY = coords[4] - 8;

  return move;
}

int validateTurn(BOARD board, enum Colour player, char *coords)
{
  if (!validateCoords(coords))
  {
    return 0;
  }

  return 1;
}

void executeTurn(BOARD board, enum Colour player)
{
  char inputCoords[7];

  printBoard(board);

  printf("%s Player - Please input your move in the format [A1 B1]: ", player ? "WHITE" : "BLACK");
  readInput(inputCoords, sizeof(inputCoords));

  while (!validateTurn(board, player, inputCoords))
  {
    printf("%s: ", "Please input your move in the format [A1 B1]");
    readInput(inputCoords, sizeof(inputCoords));
  }
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
  BOARD board = {{NULL}};

  initialiseBoard(board);

  executeTurn(board, WHITE);

  freeBoard(board);

  return 0;
}
