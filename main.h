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

typedef struct ChessPiece *BOARD[8][8];

void initialiseBoard(BOARD board);
void printBoard(BOARD board);
void freeBoard(BOARD board);

int validLetter(char c);
int validNumber(int n);
int validateCoords(char *coords);

Move parseCoords(char *coords);

int validateTurn(BOARD board, enum Colour player, char *coords);
void executeTurn(BOARD board, enum Colour player);

void clearInputBuffer();
void readInput(char *buffer, int size);
