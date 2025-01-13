#include <array>
#include <bitset>
#include <csignal>
#include <iostream>

using linear_array = uint8_t;
using coordinate = uint8_t;
using piece = uint8_t;
using white_or_black = uint8_t;

constexpr uint8_t board_size = 4;
constexpr uint8_t n_squares = board_size * board_size;

/*
[1 2 3 4 5 6 7 8] bits in byte
1 bit - flags if a piece exists or not (1 exists and 0 does not)
2 bit - flags the color of the piece (1 is white 0 is black)
3 bit - flags if its pawn
4 bit - flags if its rook
5 bit - flags if its bishop
6 bit - flags if its knight
7 bit - flags if its queen
8 bit - flags if its king
*/
enum PieceTypes : piece {
  NO_PIECE = 0,
  HAS_PIECE = 1,
  COLOR = 2 << 0,
  PAWN = 2 << 1,
  ROOK = 2 << 2,
  BISHOP = 2 << 3,
  KNIGHT = 2 << 4,
  QUEEN = 2 << 5,
  KING = 2 << 6,
};

unsigned char val[256][3];

void fill_entry(uint8_t address, const char string[2]) {
  val[address][0] = string[0];
  val[address][1] = string[1];
}

unsigned char *get_entry(piece address) { return val[address]; }

void initialize_table() {
  for (size_t i = 0; i < 256; ++i)
    for (size_t j = 0; j < 3; ++j)
      val[i][j] = '\0';
  fill_entry(KING | HAS_PIECE | COLOR, "wK");
  fill_entry(KING | HAS_PIECE, "bK");
  fill_entry(QUEEN | HAS_PIECE | COLOR, "wQ");
  fill_entry(QUEEN | HAS_PIECE, "bQ");
  fill_entry(KNIGHT | HAS_PIECE | COLOR, "wN");
  fill_entry(KNIGHT | HAS_PIECE, "bN");
  fill_entry(BISHOP | HAS_PIECE | COLOR, "wB");
  fill_entry(BISHOP | HAS_PIECE, "bB");
  fill_entry(ROOK | HAS_PIECE | COLOR, "wR");
  fill_entry(ROOK | HAS_PIECE, "bR");
  fill_entry(PAWN | HAS_PIECE | COLOR, "wP");
  fill_entry(PAWN | HAS_PIECE, "bP");
  fill_entry(NO_PIECE, " O");
  fill_entry(HAS_PIECE, " B");
  fill_entry(HAS_PIECE|COLOR, " W");
}

constexpr uint16_t dummy_black = 560;
constexpr uint16_t dummy_white = 490;

struct coord {
  coordinate row;
  coordinate col;
};

inline coord convert(linear_array position) {
  coordinate col = position % board_size;
  coordinate row = position / board_size;
  return {row, col};
}

inline bool same_colors(piece a, piece b) {
  return ((a & COLOR) == (b & COLOR));
}

inline bool has_white_color(piece a) { return a & COLOR; }

inline bool has_black_color(piece a) { return (a & HAS_PIECE) && ~(a & COLOR); }

inline linear_array convert(coord coord) {
  return coord.row * board_size + coord.col;
}

inline piece black_piece(PieceTypes type) { return type | HAS_PIECE; }

inline piece white_piece(PieceTypes type) { return type | HAS_PIECE | COLOR; }

inline uint8_t has_piece(piece b) {
  if (b & HAS_PIECE)
    return 0xFF;
  return 0x00;
}

struct regular{
  piece p;
  coordinate originals;
  coordinate finals;
};

struct special{
  piece p1;
  piece p2;
  coordinate original1;
  coordinate final1;
  coordinate original2;
  coordinate final2;
};

class movement{
  union{
    regular reg;
    special special;
  } m;
  bool is_regular;

public:
  movement(piece pie,coordinate original, coordinate final){

  }

  movement(){
    
  }

  inline bool is_regular(){
    return is_regular;
  }

};

piece update_board(std::array<piece, n_squares>& previous,
             const std::array<piece, n_squares> tmp_has_piece) {
  uint8_t sum = 0;
  std::array<uint8_t, n_squares> changed{0};
  for (linear_array pos = 0; pos < n_squares; ++pos)
    if ((has_piece(previous[pos]) != has_piece(tmp_has_piece[pos])) ||
        !same_colors(previous[pos],
                     tmp_has_piece[pos])) // compare if piece moved or if color
                                          // of piece on square changed
    {
      changed[pos] = 1;
      sum += 1;
    }

    coord originalpos;
    coord finalpos;
    switch (sum) {
    case 2: // piece was eaten or moved
      for (linear_array pos = 0; pos < n_squares; ++pos)
        if (changed[pos]) {
          if (!has_piece(tmp_has_piece[pos]) && has_piece(previous[pos])) // if there was a white piece and now there is not then this is the original position
            originalpos = convert(pos);
          else
            finalpos = convert(pos);
        }
        previous[convert(finalpos)] = previous[convert(originalpos)];
        previous[convert(originalpos)] = NO_PIECE;
      break;
    default: // clearly a failure happened, no updating to take place
      return NO_PIECE;
      break;
  }
  return previous[convert(finalpos)];
}

struct Board {
  Board(){
    initialize_table();
  }

  std::array<piece, n_squares> m_board;
  size_t offset = 0;
  bool white_turn = true;

  void update(std::array<uint16_t, n_squares> measurments) {
    std::array<piece, n_squares> has_piece;
    for (size_t i = 0; i < n_squares; ++i)
      has_piece[i] = (measurments[i] > 550) ? HAS_PIECE : (measurments[i] < 500) ? COLOR | HAS_PIECE : NO_PIECE;
    piece moved_piece = update_board(m_board, has_piece);
    //m_board = has_piece;
  }

  Board &operator<<(piece type) {
    m_board[offset % n_squares] = type;
    ++offset;
    return *this;
  }
};

std::ostream &operator<<(std::ostream &os, const Board &obj) {
  for (int row = 0; row < board_size; ++row) {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", get_entry(obj.m_board[row * board_size + col]));
    std::printf("|\n");
  }
  return os;
}


int main() {
  Board board;
  board << black_piece(KING) << NO_PIECE << white_piece(KING) << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;


  std::cout << board << std::endl;
  std::array<uint16_t, n_squares> measurments{
      515, 515, dummy_white, 515, dummy_black, 515, 515, 515,
      515, 515, 515,         515, 515,         515, 515, 515};
  board.update(measurments);
  std::cout << board << std::endl;
  return 0;
}
