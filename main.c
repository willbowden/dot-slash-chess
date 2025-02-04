#include <stdio.h>
#include <stdlib.h>

enum PieceType
{
  PAWN,
  ROOK,
  KNIGHT,
  BISHOP,
  QUEEN,
  KING
};

enum Colour
{
  BLACK,
  WHITE
};

typedef struct ChessPiece
{
  enum PieceType type;
  enum Colour colour;
} Piece;

typedef struct ChessPiece *BOARD[8][8];

const enum PieceType DEFAULT_LAYOUT[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN};

void initialiseBoard(BOARD board)
{
  int x, y, step;
  struct ChessPiece *newPiece;

  /* Add bottom pieces */
  for (y = 0; y < 2; y++)
  {
    step = y * 8;
    for (x = 0; x < 8; x++)
    {
      struct ChessPiece *newPiece = malloc(sizeof(struct ChessPiece));
      newPiece->type = DEFAULT_LAYOUT[x + step];
      newPiece->colour = WHITE;

      board[x][y] = newPiece;
    }
  }

  for (y = 0; y < 2; y++)
  {
    step = y * 8;
    for (x = 7; x >= 0; x--)
    {
      newPiece = malloc(sizeof(struct ChessPiece));
      newPiece->type = DEFAULT_LAYOUT[x + step];
      newPiece->colour = WHITE;

      board[x][y] = newPiece;
    }
  }

  for (y = 2; y < 6; y++)
  {
    for (x = 0; x < 8; x++)
    {
      board[x][y] = NULL;
    }
  }
}

void printBoard(BOARD board)
{
  int x, y;
  char toPrint;
  struct ChessPiece *square;

  for (y = 7; y >= 0; y--)
  {
    for (x = 7; x >= 0; x--)
    {
      square = board[x][y];

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
      printf("| %c |", toPrint);
    }

    printf("%s", "\n");
  }
}

int main(int argc, char **args)
{
  BOARD board = {{NULL}};

  initialiseBoard(board);

  printBoard(board);

  return 0;
}
