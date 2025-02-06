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
  short unsigned int timesMoved;
} Piece;

typedef struct ChessMove
{
  int fromX;
  int fromY;
  int toX;
  int toY;
} Move;

typedef struct ChessPiece *Board[8][8];

typedef struct ChessGame
{
  Board board;
  
} Game;

void initialiseBoard(Board board);
void printBoard(Board board);
void freeBoard(Board board);

int validLetter(char c);
int validNumber(int n);
int validateCoords(char *coords);

Move parseCoords(char *coords);

int validateTurn(Board board, Move move, Piece *piece, enum Colour player);
void executeTurn(Board board, enum Colour player);

void clearInputBuffer();
void readInput(char *buffer, int size);
