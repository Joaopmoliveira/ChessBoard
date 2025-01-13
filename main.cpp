#include <array>
#include <iostream>
#include <cstdint>

using linear_array = uint8_t;
using coordinate = int;
using square = uint16_t;

constexpr coordinate board_size = 4;
constexpr linear_array n_squares = board_size * board_size;
constexpr coordinate pawn_original_row_square = 1;

/*
[1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16] bits in byte
1 bit - flags the color is white
2 bit - flags the color is black
3 bit - flags if its pawn
4 bit - flags if its rook
5 bit - flags if its bishop
6 bit - flags if its knight
7 bit - flags if its queen
8 bit - flags if its king
*/
enum PieceTypes : square
{
  NO_PIECE = 0,                   // 0000 0000 0000 0000 
  WHITE = 1,                      // 0000 0000 0000 0001
  BLACK = 2 << 0,                 // 0000 0000 0000 0010
  PAWN = 2 << 1,                  // 0000 0000 0000 0100
  ROOK = 2 << 2,                  // 0000 0000 0000 1000
  BISHOP = 2 << 3,                // 0000 0000 0001 0000
  KNIGHT = 2 << 4,                // 0000 0000 0010 0000
  QUEEN = 2 << 5,                 // 0000 0000 0100 0000
  KING = 2 << 6,                  // 0000 0000 1000 0000
  // < ----- special move flags ------- >
  EN_PASSANT = 2 << 7,            // 0000 0001 0000 0000
  FIRST = 2 << 8,                 // 0000 0010 0000 0000
  // < ----- utility flags ------- >
  DETECTED_BLACK_PIECE = 2 << 9,  // 0000 0010 0000 0000
  DETECTED_WHITE_PIECE = 2 << 10, // 0000 0100 0000 0000
  ATTACKED_SQUARE = 2 << 11,      // 0000 1000 0000 0000
  LEGAL_SQUARE = 2 << 12,         // 0001 0000 0000 0000
};

square bits_of_type_of_piece(square p)
{
  return ((p << 8) >> 10) << 2;
}

/* TO IGNORE ---------------------------------- > */
unsigned char val[256][3];

void fill_entry(uint8_t address, const char string[2])
{
  val[address][0] = string[0];
  val[address][1] = string[1];
}

inline square update_move(square p)
{
  if (p & FIRST)
    return p ^ FIRST;
  return p;
}

unsigned char *get_entry(square address)
{
  return val[(address << 8) >> 8];
}

void initialize_table()
{
  for (size_t i = 0; i < 256; ++i)
    for (size_t j = 0; j < 3; ++j)
      val[i][j] = '\0';
  fill_entry(KING | WHITE, "wK");
  fill_entry(KING | BLACK, "bK");
  fill_entry(QUEEN | WHITE, "wQ");
  fill_entry(QUEEN | BLACK, "bQ");
  fill_entry(KNIGHT | WHITE, "wN");
  fill_entry(KNIGHT | BLACK, "bN");
  fill_entry(BISHOP | WHITE, "wB");
  fill_entry(BISHOP | BLACK, "bB");
  fill_entry(ROOK | WHITE, "wR");
  fill_entry(ROOK | BLACK, "bR");
  fill_entry(PAWN | WHITE, "wP");
  fill_entry(PAWN | BLACK, "bP");
  fill_entry(NO_PIECE, " O");
  fill_entry(BLACK, " B");
  fill_entry(WHITE, " W");
}

constexpr uint16_t dummy_black = 560;
constexpr uint16_t dummy_white = 490;

/*  ---------------------------------- TO IGNORE > */

struct coord
{
  coordinate row;
  coordinate col;

  coord() : row{0}, col{0} {}
  coord(int in_row, int in_col) : row{in_row}, col{in_col} {}
};

inline coord convert(linear_array position)
{
  coordinate col = position % board_size;
  coordinate row = position / board_size;
  return {row, col};
}

inline linear_array convert(coord coord)
{
  return coord.row * board_size + coord.col;
}

inline bool valid_coord(coord in)
{
  return (in.row >= 0 && in.row < board_size) && (in.col >= 0 && in.col < board_size);
}

inline bool same_colors(square a, square b)
{
  return ((a & WHITE) & (b & WHITE)) | ((a & BLACK) & (b & BLACK));
}

inline bool has_white_color(square a) { return a & WHITE; }

inline bool has_black_color(square a) { return (a & BLACK); }

inline square black_piece(PieceTypes type) { return type | BLACK | FIRST; }

inline square white_piece(PieceTypes type) { return type | WHITE | FIRST; }

inline square has_piece(square b)
{
  if (b)
    return 0xFFFF;
  return 0x0000;
}

template <PieceTypes mark_type>
inline void mark_as(square &square)
{
  static_assert(mark_type == ATTACKED_SQUARE || mark_type == LEGAL_SQUARE, "mark is not valid");
  square |= mark_type;
}

template <PieceTypes mark_type>
inline bool is_marked_as(square square)
{
  static_assert(mark_type == ATTACKED_SQUARE || mark_type == LEGAL_SQUARE, "mark is not valid");
  return square & mark_type;
}

inline square has_detected_piece(square b)
{
  return (b & DETECTED_BLACK_PIECE) | (b & DETECTED_WHITE_PIECE);
}

inline square color_and_detected_color_match(square b)
{
  return ((b & WHITE) & (b & DETECTED_BLACK_PIECE)) | ((b & BLACK) & (b & DETECTED_BLACK_PIECE));
}

void clear_utility_flags(std::array<square, n_squares> &raw_board)
{
  for (auto &v : raw_board)
    v = (v << 6) >> 6;
}

void print_attacked_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row,col})] & ATTACKED_SQUARE ? "X" : "O");
    std::printf("|\n");
  }
}

void print_legal_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row,col})] & LEGAL_SQUARE ? "X" : "O");
    std::printf("|\n");
  }
}

void print_enpassant_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row,col})] & EN_PASSANT ? "X" : "O");
    std::printf("|\n");
  }
}

void print_first_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row,col})] & FIRST ? "X" : "O");
    std::printf("|\n");
  }
}

void print_detected_piece_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row,col})] & (DETECTED_BLACK_PIECE | DETECTED_WHITE_PIECE) ? "X" : "O");
    std::printf("|\n");
  }
}

void print_detected_black_piece_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row,col})] & DETECTED_BLACK_PIECE ? "X" : "O");
    std::printf("|\n");
  }
}

void print_detected_white_piece_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row,col})] & DETECTED_WHITE_PIECE ? "X" : "O");
    std::printf("|\n");
  }
}

struct movement
{
  square moved_piece;
  coord origin;
  coord end;
};

template <PieceTypes mark_type>
void fill_rook_move(coord location, std::array<square, n_squares> &raw_board)
{
  square piece_to_move = raw_board[convert(location)];
  for (coordinate row = location.row + 1; row < board_size; ++row)
    if (has_piece(raw_board[convert({row, location.col})]))
    {
      if (!same_colors(piece_to_move, raw_board[convert({row, location.col})]))
        mark_as<mark_type>(raw_board[convert({row, location.col})]);
      break;
    }
    else
      mark_as<mark_type>(raw_board[convert({row, location.col})]);
  for (coordinate row = location.row - 1; row >= 0; --row)
    if (has_piece(raw_board[convert({row, location.col})]))
    {
      if (!same_colors(piece_to_move, raw_board[convert({row, location.col})]))
        mark_as<mark_type>(raw_board[convert({row, location.col})]);
      break;
    }
    else
      mark_as<mark_type>(raw_board[convert({row, location.col})]);
  for (coordinate col = location.col + 1; col < board_size; ++col)
    if (has_piece(raw_board[convert({location.row, col})]))
    {
      if (!same_colors(piece_to_move, raw_board[convert({location.row, col})]))
        mark_as<mark_type>(raw_board[convert({location.row, col})]);
      break;
    }
    else
      mark_as<mark_type>(raw_board[convert({location.row, col})]);
  for (coordinate col = location.col - 1; col >= 0; --col)
    if (has_piece(raw_board[convert({location.row, col})]))
    {
      if (!same_colors(piece_to_move, raw_board[convert({location.row, col})]))
        mark_as<mark_type>(raw_board[convert({location.row, col})]);
      break;
    }
    else
      mark_as<mark_type>(raw_board[convert({location.row, col})]);
}

template <PieceTypes mark_type>
void fill_bishop_move(const coord& location, std::array<square, n_squares> &raw_board)
{
  square piece_to_move = raw_board[convert(location)];
  coordinate row = location.row + 1;
  coordinate col = location.col + 1;
  for (; row < board_size && col < board_size; ++row, ++col)
    if (has_piece(raw_board[convert({row, col})]))
    {
      if (!same_colors(piece_to_move, raw_board[convert({row, col})]))
        mark_as<mark_type>(raw_board[convert({row, col})]);
      break;
    }
    else
      mark_as<mark_type>(raw_board[convert({row, col})]);
  row = location.row - 1;
  col = location.col - 1;
  for (; row >= 0 && col >= 0; --row, --col)
    if (has_piece(raw_board[convert({row, col})]))
    {
      if (!same_colors(piece_to_move, raw_board[convert({row, col})]))
        mark_as<mark_type>(raw_board[convert({row, col})]);
      break;
    }
    else
      mark_as<mark_type>(raw_board[convert({row, col})]);
  row = location.row + 1;
  col = location.col - 1;
  for (; row < board_size && col >= 0; ++row, --col)
    if (has_piece(raw_board[convert({row, col})]))
    {
      if (!same_colors(piece_to_move, raw_board[convert({row, col})]))
        mark_as<mark_type>(raw_board[convert({row, col})]);
      break;
    }
    else
      mark_as<mark_type>(raw_board[convert({row, col})]);
  row = location.row - 1;
  col = location.col + 1;
  for (; row >= 0 && col < board_size; --row, ++col)
    if (has_piece(raw_board[convert({row, col})]))
    {
      if (!same_colors(piece_to_move, raw_board[convert({row, col})]))
        mark_as<mark_type>(raw_board[convert({row, col})]);
      break;
    }
    else
      mark_as<mark_type>(raw_board[convert({row, col})]);
}

template <PieceTypes mark_type>
void fill_knight_move(const coord& location, std::array<square, n_squares> &raw_board)
{
  int moves[8][2] = {{2, 1}, {2, -1}, {-2, -1}, {-2, 1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
  square piece_to_move = raw_board[convert(location)];
  for (int i = 0; i < 8; ++i)
  {
    coord lcoord(location.row + moves[i][0], location.col + moves[i][1]);
    if (valid_coord(lcoord) && !same_colors(piece_to_move, raw_board[convert(lcoord)]))
      mark_as<mark_type>(raw_board[convert(lcoord)]);
  }
}

template <PieceTypes mark_type>
void fill_king_move(const coord& location, std::array<square, n_squares> &raw_board)
{
  int moves[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
  square piece_to_move = raw_board[convert(location)];
  for (int i = 0; i < 8; ++i)
  {
    coord lcoord(location.row + moves[i][0], location.col + moves[i][1]);
    if (valid_coord(lcoord) && !same_colors(piece_to_move, raw_board[convert(lcoord)]))
    {
      mark_as<mark_type>(raw_board[convert(lcoord)]);
    }
  }
}

void fill_pawn_move(coord location, std::array<square, n_squares> &raw_board)
{
  auto piec = raw_board[convert(location)];
  if (piec & WHITE)
  { // white
    if (location.col == pawn_original_row_square)
    { // can jump two squares
      coord cord(location.row, location.col + 2);
      if (!has_piece(raw_board[convert(cord)]))
        mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    }
    else
    { // can jump one square
      coord cord(location.row, location.col + 1);
      if (!has_piece(raw_board[convert(cord)]))
        mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    }
  }
  else
  { // black
    if (board_size - location.col == pawn_original_row_square)
    { // can jump two squares
      coord cord(location.row, location.col - 2);
      if (!has_piece(raw_board[convert(cord)]))
        mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    }
    else
    { // can jump one square
      coord cord(location.row, location.col - 1);
      if (!has_piece(raw_board[convert(cord)]))
        mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    }
  }
}

void fill_pawn_attack(coord location, std::array<square, n_squares> &raw_board)
{
  auto piec = raw_board[convert(location)];
  if (piec & WHITE)
  { // white
    coord cord(location.row + 1, location.col + 1);
    if (valid_coord(cord))
      mark_as<ATTACKED_SQUARE>(raw_board[convert(cord)]);
    cord = coord(location.row - 1, location.col + 1);
    if (valid_coord(cord))
      mark_as<ATTACKED_SQUARE>(raw_board[convert(cord)]);
  }
  else
  { // black
    coord cord(location.row + 1, location.col - 1);
    if (valid_coord(cord))
      mark_as<ATTACKED_SQUARE>(raw_board[convert(cord)]);
    cord = coord(location.row - 1, location.col - 1);
    if (valid_coord(cord))
      mark_as<ATTACKED_SQUARE>(raw_board[convert(cord)]);
  }
}

void fill_attacked_squares(coord location, std::array<square, n_squares> &raw_board)
{
  switch (bits_of_type_of_piece(raw_board[convert(location)]))
  {
  case PAWN:
  {
    fill_pawn_attack(location, raw_board);
    break;
  }
  case ROOK:
  {
    fill_rook_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  }
  case BISHOP:
  {
    fill_bishop_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  }
  case KNIGHT:
  {
    fill_king_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  }
  case QUEEN:
  {
    fill_rook_move<ATTACKED_SQUARE>(location, raw_board);
    fill_bishop_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  }
  case KING:
  {
    fill_king_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  }
  case NO_PIECE:
  default:
    break;
  }
}

void fill_allowed_moves(coord location, std::array<square, n_squares> &raw_board)
{
  switch (bits_of_type_of_piece(raw_board[convert(location)]))
  {
  case PAWN:
  {
    fill_pawn_move(location, raw_board);
    break;
  }
  case ROOK:
  {
    fill_rook_move<LEGAL_SQUARE>(location, raw_board);
    break;
  }
  case BISHOP:
  {
    fill_bishop_move<LEGAL_SQUARE>(location, raw_board);
    break;
  }
  case KNIGHT:
  {
    fill_king_move<LEGAL_SQUARE>(location, raw_board);
    break;
  }
  case QUEEN:
  {
    fill_rook_move<LEGAL_SQUARE>(location, raw_board);
    fill_bishop_move<LEGAL_SQUARE>(location, raw_board);
    break;
  }
  case KING:
  {
    fill_king_move<LEGAL_SQUARE>(location, raw_board);
    break;
  }
  case NO_PIECE:
  default:
    break;
  }
};

movement find_movement(const std::array<square, n_squares> &board_state)
{
  uint8_t number_of_moved_pieces = 0;
  std::array<bool, n_squares> changed{0};
  for (linear_array pos = 0; pos < n_squares; ++pos)
    if ((has_piece(board_state[pos]) != has_detected_piece(board_state[pos])) ||
        !color_and_detected_color_match(board_state[pos])) // compare if  square moved or if color
                                                           // of  square on square changed
    {
      changed[pos] = 1;
      number_of_moved_pieces += 1;
    }

  coord originalpos;
  coord finalpos;
  switch (number_of_moved_pieces)
  {
  case 2: //  square was eaten or moved
    for (linear_array pos = 0; pos < n_squares; ++pos)
      if (changed[pos])
      {
        if (!has_detected_piece(board_state[pos]) && has_piece(board_state[pos])) // if there was a  square and now there is not then this is the original position
          originalpos = convert(pos);
        else
          finalpos = convert(pos);
      }
    break;
  default: // clearly a failure happened, no updating to take place
    return {NO_PIECE, {0, 0}, {0, 0}};
    break;
  }
  return {board_state[convert(finalpos)], originalpos, finalpos};
}

struct Board
{
  Board()
  {
    initialize_table();
  }

  std::array<square, n_squares> m_board;
  size_t offset = 0;
  bool white_turn = true;

  void update(const std::array<uint16_t, n_squares> &measurments)
  {
    clear_utility_flags(m_board);
    for (linear_array i = 0; i < n_squares; ++i)
      m_board[i] |= (measurments[i] > 550) ? DETECTED_BLACK_PIECE : (measurments[i] < 500) ? DETECTED_WHITE_PIECE : NO_PIECE;
    movement moved_piece = find_movement(m_board);
    if (moved_piece.moved_piece & KING)
    {
      for (linear_array pos = 0; pos < n_squares; ++pos)
      {
        if (white_turn && (BLACK & m_board[pos]))
          fill_attacked_squares(convert(pos), m_board);
        else if ((m_board[pos] & WHITE))
          fill_attacked_squares(convert(pos), m_board);
      }
      if (is_marked_as<ATTACKED_SQUARE>(m_board[convert(moved_piece.end)])) // we moved the king to this position yet its attacked by other pieces, no can do cowboy
        return;
    }
    fill_allowed_moves(moved_piece.origin, m_board);
    if (!is_marked_as<LEGAL_SQUARE>(m_board[convert(moved_piece.end)]))
    {
      // the move is not on the list of allowed moves, no can do cowboy
      return;
    }
    m_board[convert(moved_piece.end)] = update_move(m_board[convert(moved_piece.origin)]);
    m_board[convert(moved_piece.origin)] = NO_PIECE;
    white_turn = !white_turn;
  }

  Board &operator<<(square type)
  {
    m_board[offset % n_squares] = type;
    ++offset;
    return *this;
  }
};

std::ostream &operator<<(std::ostream &os, const Board &obj)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", get_entry(obj.m_board[row * board_size + col]));
    std::printf("|\n");
  }
  return os;
}

void function1()
{
  Board board;
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << black_piece(PAWN) << white_piece(PAWN) << NO_PIECE << NO_PIECE
        << white_piece(KING) << NO_PIECE << NO_PIECE << NO_PIECE;

  std::cout << board << std::endl;
  std::array<uint16_t, n_squares> measurments{515, 515, 515, 515,
                                              dummy_white, 515, 515, 515,
                                              515, 515, 515, 515,
                                              dummy_white, 515, 515, 515};

  board.update(measurments);

  std::cout << board << std::endl;
}

void function2()
{
  Board board;
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << black_piece(KNIGHT) << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << black_piece(KING) << NO_PIECE << NO_PIECE << NO_PIECE;

  std::printf("\nattacked status:\n");print_attacked_status(board.m_board);
  fill_knight_move<ATTACKED_SQUARE>({1, 1}, board.m_board);
  std::printf("\nattacked status:\n");print_attacked_status(board.m_board);
}

void function3()
{
  Board board;
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << black_piece(ROOK) << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << black_piece(KING) << NO_PIECE << NO_PIECE << NO_PIECE;
  
  std::printf("\nattacked status:\n");print_attacked_status(board.m_board);
  fill_rook_move<ATTACKED_SQUARE>({1, 0}, board.m_board);
  std::printf("\nattacked status:\n");print_attacked_status(board.m_board);
  fill_rook_move<ATTACKED_SQUARE>({0, 3}, board.m_board);
  std::printf("\nattacked status:\n");print_attacked_status(board.m_board);
}

/*
Time to write tests that validate the logic of the game 
*/

int main()
{
  function2();
  return 0;
}