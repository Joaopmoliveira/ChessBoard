#include <array>
#include <cstdint>
#include <bitset>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

using linear_array = uint_fast8_t;
using coordinate = int;
using square = uint_fast16_t;

constexpr coordinate board_size = 4;
constexpr linear_array n_squares = board_size * board_size;

/*
[1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16] bits in byte
1 bit - flags the color is WHITE_PIECE
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
  NO_PIECE = 0,    // 0000 0000 0000 0000
  WHITE_PIECE = 1,       // 0000 0000 0000 0001
  BLACK_PIECE= 2 << 0,  // 0000 0000 0000 0010
  PAWN = 2 << 1,   // 0000 0000 0000 0100
  ROOK = 2 << 2,   // 0000 0000 0000 1000
  BISHOP = 2 << 3, // 0000 0000 0001 0000
  KNIGHT = 2 << 4, // 0000 0000 0010 0000
  QUEEN = 2 << 5,  // 0000 0000 0100 0000
  KING = 2 << 6,   // 0000 0000 1000 0000
  MASK_EXTERNAL_INFO = WHITE_PIECE | BLACK_PIECE| PAWN | ROOK | BISHOP | KNIGHT | QUEEN | KING, // 0000 0000 1111 1111
  MASK_PIECES = PAWN | ROOK | BISHOP | KNIGHT | QUEEN | KING, // 0000 0000 1111 1100
  // < ----- special move flags ------- >
  EN_PASSANT = 2 << 7, // 0000 0001 0000 0000
  FIRST = 2 << 8,      // 0000 0010 0000 0000
  MASK_NON_UTILITIES = WHITE_PIECE | BLACK_PIECE| PAWN | ROOK | BISHOP | KNIGHT | QUEEN | KING | EN_PASSANT | FIRST, // 0000 0011 1111 1111
  // < ----- utility flags ------- >
  DETECTED_BLACK_PIECE = 2 << 9,  // 0000 0010 0000 0000
  DETECTED_WHITE_PIECE_PIECE = 2 << 10, // 0000 0100 0000 0000
  ATTACKED_SQUARE = 2 << 11,      // 0000 1000 0000 0000
  LEGAL_SQUARE = 2 << 12,         // 0001 0000 0000 0000
};

/*
A coord represents a position in a grid which can be converted 
to a linear position
*/
struct coord
{
  coordinate row;
  coordinate col;

  coord() : row{-1}, col{-1} {}
  coord(int in_row, int in_col) : row{in_row}, col{in_col} {}
};

struct movement
{
  uint_fast8_t number_of_moves;
  std::array<square, 4> changed_squares;
  uint_fast8_t number_of_empty_squares;
  std::array<coord, 2> empty_squares;
  uint_fast8_t number_of_filled_squares;
  std::array<coord, 2> filled_squares;

  movement();

  void check_and_store_if_changed_square(square in, linear_array pos);
};

unsigned char piece_names[256][3];

void fill_entry(square address, const char string[2])
{
  address &= MASK_EXTERNAL_INFO;
  assert(address < 256);
  piece_names[address][0] = string[0];
  piece_names[address][1] = string[1];
}

inline square update_move(square p)
{
  if (p & FIRST)
    return p ^ FIRST;
  return p;
}

unsigned char *get_entry(square address)
{
  address &= MASK_EXTERNAL_INFO;
  assert(address < 256);
  return piece_names[address];
}

void initialize_table()
{
  for (size_t i = 0; i < 256; ++i)
    for (size_t j = 0; j < 3; ++j)
      piece_names[i][j] = '\0';
  fill_entry(KING | WHITE_PIECE, "wK");
  fill_entry(KING | BLACK_PIECE, "bK");
  fill_entry(QUEEN | WHITE_PIECE, "wQ");
  fill_entry(QUEEN | BLACK_PIECE, "bQ");
  fill_entry(KNIGHT | WHITE_PIECE, "wN");
  fill_entry(KNIGHT | BLACK_PIECE, "bN");
  fill_entry(BISHOP | WHITE_PIECE, "wB");
  fill_entry(BISHOP | BLACK_PIECE, "bB");
  fill_entry(ROOK | WHITE_PIECE, "wR");
  fill_entry(ROOK | BLACK_PIECE, "bR");
  fill_entry(PAWN | WHITE_PIECE, "wP");
  fill_entry(PAWN | BLACK_PIECE, "bP");
  fill_entry(NO_PIECE, " O");
  fill_entry(BLACK_PIECE, " B");
  fill_entry(WHITE_PIECE, " W");
}

inline coord convert(linear_array position)
{
  coordinate col = position % board_size;
  coordinate row = position / board_size;
  return {row, col};
}

inline bool valid_coord(coord in)
{
  return (in.row >= 0 && in.row < board_size) && (in.col >= 0 && in.col < board_size);
}

inline linear_array convert(coord coord)
{
  assert(coord.col >= 0 && coord.row >= 0);
  return coord.row * board_size + coord.col;
}

inline bool same_colors(square a, square b)
{
  if (b & WHITE_PIECE)
    return a & WHITE_PIECE;
  if (b & BLACK_PIECE)
    return a & BLACK_PIECE;
  return false;
}

inline bool has_white_piece_color(square a) { return a & WHITE_PIECE; }

inline bool has_black_color(square a) { return (a & BLACK_PIECE); }

inline square black_piece(PieceTypes type) { return type | BLACK_PIECE| FIRST; }

inline square white_piece(PieceTypes type) { return type | WHITE_PIECE | FIRST; }

inline bool has_piece(square b)
{
  return MASK_PIECES & b;
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

inline bool has_detected_piece(square b)
{
  return (b & DETECTED_BLACK_PIECE) || (b & DETECTED_WHITE_PIECE_PIECE);
}

inline bool color_and_detected_color_match(square b)
{
  if (b & WHITE_PIECE)
    return b & DETECTED_WHITE_PIECE_PIECE;
  if (b & BLACK_PIECE)
    return b & DETECTED_BLACK_PIECE;
  return false;
}

void clear_utility_flags(std::array<square, n_squares> &raw_board)
{
  for (auto &v : raw_board)
    v &= MASK_NON_UTILITIES;
}

void clear_en_passant_flags(std::array<square, n_squares> &raw_board)
{
  for (auto &v : raw_board)
    if (v & EN_PASSANT)
      v ^= EN_PASSANT;
}

movement::movement() : number_of_moves{0}, number_of_empty_squares{0}, number_of_filled_squares{0}
{
  changed_squares.fill(NO_PIECE);
  empty_squares.fill(coord{});
  filled_squares.fill(coord{});
}

void movement::check_and_store_if_changed_square(square in, linear_array pos)
{
  assert(in);
  if (!has_piece(in) && has_detected_piece(in))
  { // piece was to this previously empty square
    changed_squares[number_of_moves] = in;
    filled_squares[number_of_filled_squares] = convert(pos);
    ++number_of_moves;
    ++number_of_filled_squares;
    return;
  }
  if (has_piece(in) && !has_detected_piece(in)) // piece was moved from this square
  {
    changed_squares[number_of_moves] = in;
    empty_squares[number_of_empty_squares] = convert(pos);
    ++number_of_moves;
    ++number_of_empty_squares;
    return;
  }
  if (has_piece(in) && !color_and_detected_color_match(in)) // the square as always filled but the colors between the current piece and the new piece are incorrect
  {
    changed_squares[number_of_moves] = in;
    filled_squares[number_of_filled_squares] = convert(pos);
    ++number_of_moves;
    ++number_of_filled_squares;
  }
}

template <PieceTypes mark_type>
void fill_rook_move(coord location, std::array<square, n_squares> &raw_board) // TODO : this code can be considerably simplified
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
void fill_bishop_move(const coord &location, std::array<square, n_squares> &raw_board) // TODO : this code can be considerably simplified
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
void fill_knight_move(const coord &location, std::array<square, n_squares> &raw_board)
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
void fill_king_move(const coord &location, std::array<square, n_squares> &raw_board)
{
  int moves[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
  square piece_to_move = raw_board[convert(location)];
  for (int i = 0; i < 8; ++i)
  {
    coord lcoord(location.row + moves[i][0], location.col + moves[i][1]);
    if (valid_coord(lcoord))
      if (!same_colors(piece_to_move, raw_board[convert(lcoord)]))
        mark_as<mark_type>(raw_board[convert(lcoord)]);
  }
}

void fill_pawn_move(coord location, std::array<square, n_squares> &raw_board)
{
  auto piece = raw_board[convert(location)];
  coordinate offset = (piece & WHITE_PIECE) ? 1 : -1;

  if (piece & FIRST)
  { // can jump two squares
    coord cord(location.row + offset * 2, location.col);
    if (valid_coord(cord) && !has_piece(raw_board[convert(cord)]))
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    cord = coord(location.row + offset, location.col);
    if (valid_coord(cord) && !has_piece(raw_board[convert(cord)]))
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
  }
  else
  { // can jump one square
    coord cord(location.row + offset, location.col);
    if (valid_coord(cord) && !has_piece(raw_board[convert(cord)]))
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    // now we check for en passant
    cord = coord(location.row + offset, location.col - 1);
    if (valid_coord(cord) && raw_board[convert(cord)] & EN_PASSANT)
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    cord = coord(location.row + offset, location.col + 1);
    if (valid_coord(cord) && raw_board[convert(cord)] & EN_PASSANT)
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
  }
}

void fill_pawn_attack(coord location, std::array<square, n_squares> &raw_board)
{
  auto piece = raw_board[convert(location)];
  coordinate offset = (piece & WHITE_PIECE) ? 1 : -1;
  coord cord(location.row + offset, location.col - 1);
  if (valid_coord(cord))
    mark_as<ATTACKED_SQUARE>(raw_board[convert(cord)]);
  cord = coord(location.row + offset, location.col + 1);
  if (valid_coord(cord))
    mark_as<ATTACKED_SQUARE>(raw_board[convert(cord)]);
}

void fill_attacked_squares(coord location, std::array<square, n_squares> &raw_board)
{
  switch (MASK_PIECES & raw_board[convert(location)])
  {
  case PAWN:
    fill_pawn_attack(location, raw_board);
    break;
  case ROOK:
    fill_rook_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  case BISHOP:
    fill_bishop_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  case KNIGHT:
    fill_king_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  case QUEEN:
    fill_rook_move<ATTACKED_SQUARE>(location, raw_board);
    fill_bishop_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  case KING:
    fill_king_move<ATTACKED_SQUARE>(location, raw_board);
    break;
  case NO_PIECE:
  default:
    break;
  }
}

void fill_allowed_moves(coord location, std::array<square, n_squares> &raw_board)
{
  switch (MASK_PIECES & raw_board[convert(location)])
  {
  case PAWN:
    fill_pawn_move(location, raw_board);
    break;
  case ROOK:
    fill_rook_move<LEGAL_SQUARE>(location, raw_board);
    break;
  case BISHOP:
    fill_bishop_move<LEGAL_SQUARE>(location, raw_board);
    break;
  case KNIGHT:
    fill_king_move<LEGAL_SQUARE>(location, raw_board);
    break;
  case QUEEN:
    fill_rook_move<LEGAL_SQUARE>(location, raw_board);
    fill_bishop_move<LEGAL_SQUARE>(location, raw_board);
    break;
  case KING:
    fill_king_move<LEGAL_SQUARE>(location, raw_board);
    break;
  case NO_PIECE:
  default:
    break;
  }
};

movement find_movement(const std::array<square, n_squares> &board_state)
{
  movement detected_movements{};
  for (linear_array pos = 0; pos < n_squares; ++pos)
    if (board_state[pos])
      detected_movements.check_and_store_if_changed_square(board_state[pos], pos);
  return detected_movements;
}

enum error_code
{
  KING_NOT_DETECTED = 0,
  ILLEGAL_MOVE = 1,
  PINNED_PIECE = 2,
  TOO_MANY_MOVES = 3,
  CASTELING_DISSALOWED = 4,
  INVALID_EN_PASSANT = 5
};
const char *board_errors[] = {"king not detected", "ilegal move", "king in check", "unexpected number moves", "casteling not allowed", "inconsistent en passant"};

[[nodiscard]] const char *parse_moved_or_eaten_movement(movement in, std::array<square, n_squares> &raw_board, bool WHITE_PIECE_turn)
{
  // first we check if the move is legal without check considerations
  std::array<square, n_squares> board_after_move{raw_board};
  fill_allowed_moves(in.empty_squares[0], board_after_move);
  if (!is_marked_as<LEGAL_SQUARE>(board_after_move[convert(in.filled_squares[0])]))
  {
    // the move is not on the list of allowed moves, no can do cowboy
    return board_errors[ILLEGAL_MOVE];
  }
  // the move is legal without checks.. now we check if the the king is attacked after the move
  board_after_move[convert(in.filled_squares[0])] = update_move(board_after_move[convert(in.empty_squares[0])]);
  board_after_move[convert(in.empty_squares[0])] = NO_PIECE;
  coordinate our_king_location = -1;
  for (linear_array pos = 0; pos < n_squares; ++pos)
  {
    if (WHITE_PIECE_turn)
    {
      if (BLACK_PIECE& board_after_move[pos])
        fill_attacked_squares(convert(pos), board_after_move);
      if (board_after_move[pos] & KING && board_after_move[pos] & WHITE_PIECE)
        our_king_location = pos;
    }
    else
    {
      if (WHITE_PIECE & board_after_move[pos])
        fill_attacked_squares(convert(pos), board_after_move);
      if (board_after_move[pos] & KING && board_after_move[pos] & BLACK_PIECE)
        our_king_location = pos;
    }
  }
  if (our_king_location < 0)
    return board_errors[KING_NOT_DETECTED];

  if (is_marked_as<ATTACKED_SQUARE>(board_after_move[our_king_location])) // we moved the king to this position yet its attacked by other pieces, no can do cowboy
    return board_errors[PINNED_PIECE];

  raw_board[convert(in.filled_squares[0])] = update_move(raw_board[convert(in.empty_squares[0])]);
  raw_board[convert(in.empty_squares[0])] = NO_PIECE;
  clear_en_passant_flags(raw_board);
  if (raw_board[convert(in.filled_squares[0])] & PAWN && abs(in.empty_squares[0].col - in.filled_squares[0].col) == 2) // the pawn pushed two squares
  {
    coord en_passant_available{in.filled_squares[0].row, WHITE_PIECE_turn ? in.filled_squares[0].col - 1 : in.filled_squares[0].col + 1};
    raw_board[convert(en_passant_available)] &= EN_PASSANT;
  }
  return nullptr;
}

[[nodiscard]] const char *parse_en_passant_movement(movement in, std::array<square, n_squares> &raw_board, bool WHITE_PIECE_turn)
{
  // first we check if the move is legal without check considerations
  std::array<square, n_squares> board_after_move{raw_board};

  // check that cleared squares are side by side and belong to distinct colors
  if (!(abs(in.empty_squares[1].col - in.empty_squares[0].col) == 1) || in.empty_squares[1].row != in.empty_squares[0].row)
    return board_errors[INVALID_EN_PASSANT];

  bool address_zero_to_use = true;

  if (in.filled_squares[0].col != in.empty_squares[0].col)     // its the piece that was in adress 0 that did the en passant
    fill_allowed_moves(in.empty_squares[0], board_after_move); // there is one filled square
  else                                                         // its the piece that was in adress 1 that did the en passant
  {
    address_zero_to_use = false;
    fill_allowed_moves(in.empty_squares[1], board_after_move);
  } // there is one filled square

  if (!is_marked_as<LEGAL_SQUARE>(board_after_move[convert(in.filled_squares[0])]))
  {
    // the move is not on the list of allowed moves, no can do cowboy
    return board_errors[ILLEGAL_MOVE];
  }
  board_after_move[convert(in.filled_squares[0])] = update_move(address_zero_to_use ? board_after_move[convert(in.empty_squares[0])] : board_after_move[convert(in.empty_squares[1])]);
  board_after_move[convert(in.empty_squares[0])] = NO_PIECE;
  board_after_move[convert(in.empty_squares[1])] = NO_PIECE;

  coordinate our_king_location = -1;
  for (linear_array pos = 0; pos < n_squares; ++pos)
  {
    if (WHITE_PIECE_turn)
    {
      if (BLACK_PIECE& board_after_move[pos])
        fill_attacked_squares(convert(pos), board_after_move);
      if (board_after_move[pos] & KING && board_after_move[pos] & WHITE_PIECE)
        our_king_location = pos;
    }
    else
    {
      if (WHITE_PIECE & board_after_move[pos])
        fill_attacked_squares(convert(pos), board_after_move);
      if (board_after_move[pos] & KING && board_after_move[pos] & BLACK_PIECE)
        our_king_location = pos;
    }
  }
  if (our_king_location < 0)
    return board_errors[KING_NOT_DETECTED];

  if (is_marked_as<ATTACKED_SQUARE>(board_after_move[our_king_location])) // we moved the king to this position yet its attacked by other pieces, no can do cowboy
    return board_errors[PINNED_PIECE];

  raw_board[convert(in.filled_squares[0])] = update_move(address_zero_to_use ? raw_board[convert(in.empty_squares[0])] : raw_board[convert(in.empty_squares[1])]);
  raw_board[convert(in.empty_squares[0])] = NO_PIECE;
  raw_board[convert(in.empty_squares[1])] = NO_PIECE;

  clear_en_passant_flags(raw_board);
  return nullptr;
}

[[nodiscard]] const char *parse_casteling_movement(movement in, std::array<square, n_squares> &raw_board, bool WHITE_PIECE_turn)
{
  return board_errors[4]; // TODO: for now casteling is dissallowed because our board is not large enough
}

void clear_and_update_detection(std::array<square, n_squares> &m_board, const std::array<uint16_t, n_squares> &measurments)
{
  clear_utility_flags(m_board);
  for (linear_array i = 0; i < n_squares; ++i)
    m_board[i] |= (measurments[i] > 550) ? DETECTED_BLACK_PIECE : (measurments[i] < 500) ? DETECTED_WHITE_PIECE_PIECE
                                                                                         : NO_PIECE; // CHECK: I am still not sure this is correct
}

struct Board
{
  Board(bool is_WHITE_PIECE_to_start_first = true) : WHITE_PIECE_turn{is_WHITE_PIECE_to_start_first}
  {
    initialize_table();
  }

  std::array<square, n_squares> m_board;
  size_t offset = 0;
  bool WHITE_PIECE_turn;

  /*
  each function inside the update must be tested to the limit so that things are correct
  */
  [[nodiscard]] const char *update(const std::array<uint16_t, n_squares> &measurments)
  {
    clear_and_update_detection(m_board, measurments);
    movement moved_piece = find_movement(m_board);
    const char *error_msg = nullptr;
    switch (moved_piece.number_of_moves)
    {
    case 2:
      error_msg = parse_moved_or_eaten_movement(moved_piece, m_board, WHITE_PIECE_turn);
      break;
    case 3:
      error_msg = parse_en_passant_movement(moved_piece, m_board, WHITE_PIECE_turn);
      break;
    case 4:
      error_msg = parse_casteling_movement(moved_piece, m_board, WHITE_PIECE_turn);
      break;
    default:
      error_msg = board_errors[TOO_MANY_MOVES];
      break;
    }
    WHITE_PIECE_turn = !WHITE_PIECE_turn;
    return error_msg;
  }

  void map_to(std::array<unsigned char,n_squares+1>& dst){
    for(size_t i = 1; i < dst.size(); ++i)
      dst[i] = MASK_EXTERNAL_INFO & m_board[i-1];
  }

  Board &operator<<(square type)
  {
    // this means that when we fill the board, at a later point in time we can refill it with a known initial position
    m_board[offset % n_squares] = type;
    ++offset;
    return *this;
  }
};



uint8_t s0 = 7; // 38 - 7
uint8_t s1 = 6; // 35 - 6
uint8_t s2 = 5; // 34 - 5
uint8_t s3 = 4; // 27 - 4

uint8_t controlPin[] = {s0, s1, s2, s3};

uint8_t SIG_pin = A0;

std::array<uint8_t,1+n_squares> board_status;
std::array<uint16_t,n_squares> measurments;

inline uint16_t readMux(int channel)
{
    uint8_t muxChannel[16][4] = {
        {0, 0, 0, 0}, // channel 0
        {1, 0, 0, 0}, // channel 1
        {0, 1, 0, 0}, // channel 2
        {1, 1, 0, 0}, // channel 3
        {0, 0, 1, 0}, // channel 4
        {1, 0, 1, 0}, // channel 5
        {0, 1, 1, 0}, // channel 6
        {1, 1, 1, 0}, // channel 7
        {0, 0, 0, 1}, // channel 8
        {1, 0, 0, 1}, // channel 9
        {0, 1, 0, 1}, // channel 10
        {1, 1, 0, 1}, // channel 11
        {0, 0, 1, 1}, // channel 12
        {1, 0, 1, 1}, // channel 13
        {0, 1, 1, 1}, // channel 14
        {1, 1, 1, 1}  // channel 15
    };

    digitalWrite(controlPin[0], muxChannel[channel][0]);
    digitalWrite(controlPin[1], muxChannel[channel][1]);
    digitalWrite(controlPin[2], muxChannel[channel][2]);
    digitalWrite(controlPin[3], muxChannel[channel][3]);

    return analogRead(SIG_pin);
}

Board board;

void setup()
{
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);

    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);

    board_status[0] = 65535;

    board << white_piece(KING) << white_piece(ROOK)     << white_piece(BISHOP) << white_piece(PAWN)
          << NO_PIECE          << NO_PIECE              << NO_PIECE            << NO_PIECE
          << NO_PIECE          << NO_PIECE              << NO_PIECE            << NO_PIECE
          << black_piece(KING) << black_piece(ROOK)     << black_piece(BISHOP) << black_piece(PAWN);

    Serial.begin(9600);
}

void loop()
{
    for (uint8_t chanel = 0; chanel < measurments.size(); ++chanel)
        measurments[chanel] = readMux(chanel);
    
    board.update(measurments);
    
    char buffer;
    auto val = Serial.readBytes(&buffer, 1);
    if (!val)
        return;
        
    if (buffer == 'r'){
        board.map_to(board_status);
        Serial.write((unsigned char *)board_status.data(), board_status.size());
    }
}