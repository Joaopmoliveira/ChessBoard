#include <array>
#include <iostream>
#include <cstdint>
#include <bitset>

using linear_array = uint8_t;
using coordinate = int;
using square = uint_fast16_t;

constexpr coordinate board_size = 4;
constexpr linear_array n_squares = board_size * board_size;

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
  NO_PIECE = 0,    // 0000 0000 0000 0000
  WHITE = 1,       // 0000 0000 0000 0001
  BLACK = 2 << 0,  // 0000 0000 0000 0010
  PAWN = 2 << 1,   // 0000 0000 0000 0100
  ROOK = 2 << 2,   // 0000 0000 0000 1000
  BISHOP = 2 << 3, // 0000 0000 0001 0000
  KNIGHT = 2 << 4, // 0000 0000 0010 0000
  QUEEN = 2 << 5,  // 0000 0000 0100 0000
  KING = 2 << 6,   // 0000 0000 1000 0000
  MASK_EXTERNAL_INFO = WHITE | BLACK | PAWN | ROOK | BISHOP | KNIGHT | QUEEN | KING,
  MASK_PIECES = PAWN | ROOK | BISHOP | KNIGHT | QUEEN | KING,
  // < ----- special move flags ------- >
  EN_PASSANT = 2 << 7, // 0000 0001 0000 0000
  FIRST = 2 << 8,      // 0000 0010 0000 0000
  MASK_NON_UTILITIES = WHITE | BLACK | PAWN | ROOK | BISHOP | KNIGHT | QUEEN | KING | EN_PASSANT | FIRST,
  // < ----- utility flags ------- >
  DETECTED_BLACK_PIECE = 2 << 9,  // 0000 0010 0000 0000
  DETECTED_WHITE_PIECE = 2 << 10, // 0000 0100 0000 0000
  ATTACKED_SQUARE = 2 << 11,      // 0000 1000 0000 0000
  LEGAL_SQUARE = 2 << 12,         // 0001 0000 0000 0000
};

/* TO IGNORE ---------------------------------- > */
unsigned char val[256][3];

void fill_entry(square address, const char string[2])
{
  val[address & MASK_EXTERNAL_INFO][0] = string[0];
  val[address & MASK_EXTERNAL_INFO][1] = string[1];
}

inline square update_move(square p)
{
  if (p & FIRST)
    return p ^ FIRST;
  return p;
}

unsigned char *get_entry(square address)
{
  return val[address & MASK_EXTERNAL_INFO];
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

  coord() : row{-1}, col{-1} {}
  coord(int in_row, int in_col) : row{in_row}, col{in_col} {}
};

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
  return coord.row * board_size + coord.col;
}

inline bool same_colors(square a, square b)
{
  if (b & WHITE)
    return a & WHITE;
  if (b & BLACK)
    return a & BLACK;
  return false;
}

inline bool has_white_color(square a) { return a & WHITE; }

inline bool has_black_color(square a) { return (a & BLACK); }

inline square black_piece(PieceTypes type) { return type | BLACK | FIRST; }

inline square white_piece(PieceTypes type) { return type | WHITE | FIRST; }

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
  return (b & DETECTED_BLACK_PIECE) || (b & DETECTED_WHITE_PIECE);
}

inline bool color_and_detected_color_match(square b)
{
  if (b & WHITE)
    return b & DETECTED_WHITE_PIECE;
  if (b & BLACK)
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

void print_attacked_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", is_marked_as<ATTACKED_SQUARE>(raw_board[convert({row, col})]) ? "X" : "O");
    std::printf("|\n");
  }
}

void print_legal_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", is_marked_as<LEGAL_SQUARE>(raw_board[convert({row, col})]) ? "X" : "O");
    std::printf("|\n");
  }
}

void print_enpassant_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row, col})] & EN_PASSANT ? "X" : "O");
    std::printf("|\n");
  }
}

void print_first_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row, col})] & FIRST ? "X" : "O");
    std::printf("|\n");
  }
}

void print_detected_piece_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row, col})] & (DETECTED_BLACK_PIECE | DETECTED_WHITE_PIECE) ? "X" : "O");
    std::printf("|\n");
  }
}

void print_detected_black_piece_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row, col})] & DETECTED_BLACK_PIECE ? "X" : "O");
    std::printf("|\n");
  }
}

void print_detected_white_piece_status(const std::array<square, n_squares> &raw_board)
{
  for (int row = 0; row < board_size; ++row)
  {
    std::printf("| ");
    for (int col = 0; col < board_size; ++col)
      std::printf(" %s ", raw_board[convert({row, col})] & DETECTED_WHITE_PIECE ? "X" : "O");
    std::printf("|\n");
  }
}

struct movement
{
  uint_fast8_t number_of_moves;
  std::array<square, 4> changed_squares;
  uint_fast8_t number_of_empty_squares;
  std::array<coord, 2> empty_squares;
  uint_fast8_t number_of_filled_squares;
  std::array<coord, 2> filled_squares;

  movement() : number_of_moves{0}, number_of_empty_squares{0}, number_of_filled_squares{0} {}

  void set_changed_square(square in, linear_array pos)
  {
    if (has_piece(in) && !has_detected_piece(in)) // piece was moved from this square
    {
      changed_squares[number_of_moves] = in;
      empty_squares[number_of_empty_squares] = convert(pos);
      ++number_of_moves;
      ++number_of_empty_squares;
      return;
    }
    if (color_and_detected_color_match(in))
    {
      changed_squares[number_of_moves] = in;
      filled_squares[number_of_filled_squares] = convert(pos);
      ++number_of_moves;
      ++number_of_filled_squares;
    }
  }
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
void fill_bishop_move(const coord &location, std::array<square, n_squares> &raw_board)
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
  coordinate offset = (piece & WHITE) ? 1 : -1;

  if (piece & FIRST)
  { // can jump two squares
    coord cord(location.row, location.col + offset * 2);
    if (!has_piece(raw_board[convert(cord)]))
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
  }
  else
  { // can jump one square
    coord cord(location.row, location.col + offset);
    if (!has_piece(raw_board[convert(cord)]))
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    // now we check for en passant
    cord = coord(location.row + 1, location.col + offset);
    if (valid_coord(cord) && raw_board[convert(cord)] & EN_PASSANT)
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
    cord = coord(location.row - 1, location.col + offset);
    if (valid_coord(cord) && raw_board[convert(cord)] & EN_PASSANT)
      mark_as<LEGAL_SQUARE>(raw_board[convert(cord)]);
  }
}

void fill_pawn_attack(coord location, std::array<square, n_squares> &raw_board)
{
  auto piece = raw_board[convert(location)];
  coordinate offset = (piece & WHITE) ? 1 : -1;
  coord cord(location.row + 1, location.col + offset);
  if (valid_coord(cord))
    mark_as<ATTACKED_SQUARE>(raw_board[convert(cord)]);
  cord = coord(location.row - 1, location.col + offset);
  if (valid_coord(cord))
    mark_as<ATTACKED_SQUARE>(raw_board[convert(cord)]);
}

void fill_attacked_squares(coord location, std::array<square, n_squares> &raw_board)
{
  switch (MASK_PIECES & raw_board[convert(location)])
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
  switch (MASK_PIECES & raw_board[convert(location)])
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
  movement detected_movements{};
  for (linear_array pos = 0; pos < n_squares; ++pos)
    if (board_state[pos])
      if (((has_piece(board_state[pos]) != has_detected_piece(board_state[pos])) || !color_and_detected_color_match(board_state[pos]))) // of  square on square changed
        detected_movements.set_changed_square(board_state[pos], pos);
  return detected_movements;
}

const char *board_errors[] = {"king not detected", "ilegal move", "king in check", "unexpected number moves", "casteling not allowed", "inconsistent en passant"};

[[nodiscard]] const char *parse_moved_or_eaten_movement(movement in, std::array<square, n_squares> &raw_board, bool white_turn)
{
  // first we check if the move is legal without check considerations
  std::array<square, n_squares> board_after_move{raw_board};
  fill_allowed_moves(in.empty_squares[0], board_after_move);
  if (!is_marked_as<LEGAL_SQUARE>(board_after_move[convert(in.filled_squares[0])]))
  {
    // the move is not on the list of allowed moves, no can do cowboy
    return board_errors[1];
  }
  // the move is legal without checks.. now we check if the the king is attacked after the move
  board_after_move[convert(in.filled_squares[0])] = update_move(board_after_move[convert(in.empty_squares[0])]);
  board_after_move[convert(in.empty_squares[0])] = NO_PIECE;
  coordinate our_king_location = -1;
  for (linear_array pos = 0; pos < n_squares; ++pos)
  {
    if (white_turn)
    {
      if (BLACK & board_after_move[pos])
        fill_attacked_squares(convert(pos), board_after_move);
      if (board_after_move[pos] & KING && board_after_move[pos] & WHITE)
        our_king_location = pos;
    }
    else
    {
      if (WHITE & board_after_move[pos])
        fill_attacked_squares(convert(pos), board_after_move);
      if (board_after_move[pos] & KING && board_after_move[pos] & BLACK)
        our_king_location = pos;
    }
  }
  if (our_king_location < 0)
    return board_errors[0];

  if (is_marked_as<ATTACKED_SQUARE>(board_after_move[our_king_location])) // we moved the king to this position yet its attacked by other pieces, no can do cowboy
    return board_errors[2];

  raw_board[convert(in.filled_squares[0])] = update_move(raw_board[convert(in.empty_squares[0])]);
  raw_board[convert(in.empty_squares[0])] = NO_PIECE;
  clear_en_passant_flags(raw_board);
  if (raw_board[convert(in.filled_squares[0])] & PAWN && abs(in.empty_squares[0].col - in.filled_squares[0].col) == 0) // the pawn pushed two squares
  {
    coord en_passant_available{in.filled_squares[0].row, white_turn ? in.filled_squares[0].col - 1 : in.filled_squares[0].col + 1};
    raw_board[convert(en_passant_available)] &= EN_PASSANT;
  }
  return nullptr;
}

[[nodiscard]] const char *parse_en_passant_movement(movement in, std::array<square, n_squares> &raw_board, bool white_turn)
{
  // first we check if the move is legal without check considerations
  std::array<square, n_squares> board_after_move{raw_board};

  // check that cleared squares are side by side and belong to distinct colors
  if (!(abs(in.empty_squares[1].col - in.empty_squares[0].col) == 1) || in.empty_squares[1].row != in.empty_squares[0].row)
    return board_errors[5];

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
    return board_errors[1];
  }
  board_after_move[convert(in.filled_squares[0])] = update_move(address_zero_to_use ? board_after_move[convert(in.empty_squares[0])] : board_after_move[convert(in.empty_squares[1])]);
  board_after_move[convert(in.empty_squares[0])] = NO_PIECE;
  board_after_move[convert(in.empty_squares[1])] = NO_PIECE;

  coordinate our_king_location = -1;
  for (linear_array pos = 0; pos < n_squares; ++pos)
  {
    if (white_turn)
    {
      if (BLACK & board_after_move[pos])
        fill_attacked_squares(convert(pos), board_after_move);
      if (board_after_move[pos] & KING && board_after_move[pos] & WHITE)
        our_king_location = pos;
    }
    else
    {
      if (WHITE & board_after_move[pos])
        fill_attacked_squares(convert(pos), board_after_move);
      if (board_after_move[pos] & KING && board_after_move[pos] & BLACK)
        our_king_location = pos;
    }
  }
  if (our_king_location < 0)
    return board_errors[0];

  if (is_marked_as<ATTACKED_SQUARE>(board_after_move[our_king_location])) // we moved the king to this position yet its attacked by other pieces, no can do cowboy
    return board_errors[2];

  raw_board[convert(in.filled_squares[0])] = update_move(address_zero_to_use ? raw_board[convert(in.empty_squares[0])] : raw_board[convert(in.empty_squares[1])]);
  raw_board[convert(in.empty_squares[0])] = NO_PIECE;
  raw_board[convert(in.empty_squares[1])] = NO_PIECE;

  clear_en_passant_flags(raw_board);
  return nullptr;
}

[[nodiscard]] const char *parse_casteling_movement(movement in, std::array<square, n_squares> &raw_board, bool white_turn)
{
  return board_errors[4]; // TODO: for now casteling is dissallowed because our board is not large enough
}

void clear_and_update_detection(std::array<square, n_squares>& m_board,const std::array<uint16_t, n_squares> &measurments){
  clear_utility_flags(m_board);
  for (linear_array i = 0; i < n_squares; ++i)
    m_board[i] |= (measurments[i] > 550) ? DETECTED_BLACK_PIECE : (measurments[i] < 500) ? DETECTED_WHITE_PIECE
                                                                                         : NO_PIECE;
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

  [[nodiscard]] const char *update(const std::array<uint16_t, n_squares> &measurments)
  {
    clear_and_update_detection(m_board,measurments);
    movement moved_piece = find_movement(m_board);
    const char *error_msg = nullptr;
    switch (moved_piece.number_of_moves)
    {
    case 2:
      error_msg = parse_moved_or_eaten_movement(moved_piece, m_board, white_turn);
      break;
    case 3:
      error_msg = parse_en_passant_movement(moved_piece, m_board, white_turn);
      break;
    case 4:
      error_msg = parse_casteling_movement(moved_piece, m_board, white_turn);
      break;
    default:
      error_msg = board_errors[3];
      break;
    }
    white_turn = !white_turn;
    return error_msg;
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

/*
Time to write tests that validate the logic of the game :
1. validate legal logic of game
2. validate attack logic of game
3. validate first logic of game
4. validate en passant logic of game
*/
void test_white_piece_measurment_detection(){
  Board board;
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_detected_black_piece_status(board.m_board);std::printf("\n");

  std::array<uint16_t, n_squares> measurments{dummy_black, 515,               515,         dummy_black,
                                              515,          515,              515,            515,
                                              dummy_white, dummy_white,       515,          dummy_white,
                                              515,         515,             dummy_black,      515};

  clear_and_update_detection(board.m_board,measurments);

  std::printf("expected: ===========\n");
  std::printf("| X O O X |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O X O |\n");
  std::printf("code result: ===========\n");
  print_detected_black_piece_status(board.m_board);std::printf("\n");
}

void test_black_piece_measurment_detection(){
  Board board;
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_detected_black_piece_status(board.m_board);std::printf("\n");

  std::array<uint16_t, n_squares> measurments{dummy_black, 515,               515,         dummy_black,
                                              515,          515,              515,            515,
                                              dummy_white, dummy_white,       515,          dummy_white,
                                              515,         515,             dummy_black,      515};

  clear_and_update_detection(board.m_board,measurments);

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| X X O X |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_detected_white_piece_status(board.m_board);std::printf("\n");
}

void test_piece_measurment_detection(){
  Board board;
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_detected_black_piece_status(board.m_board);std::printf("\n");

  std::array<uint16_t, n_squares> measurments{dummy_black, 515,               515,         dummy_black,
                                              515,          515,              515,            515,
                                              dummy_white, dummy_white,       515,          dummy_white,
                                              515,         515,             dummy_black,      515};

  clear_and_update_detection(board.m_board,measurments);

  std::printf("expected: ===========\n");
  std::printf("| X O O X |\n");
  std::printf("| O O O O |\n");
  std::printf("| X X O X |\n");
  std::printf("| O O X O |\n");
  std::printf("code result: ===========\n");
  print_detected_piece_status(board.m_board);std::printf("\n");
}

void test_rook_attacked_squares(){
  Board board;
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << black_piece(ROOK) << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_attacked_status(board.m_board);

  fill_rook_move<ATTACKED_SQUARE>({1, 1}, board.m_board);

  std::printf("expected: ===========\n");
  std::printf("| O X O O |\n");
  std::printf("| X O X X |\n");
  std::printf("| O X O O |\n");
  std::printf("| O X O O |\n");
  std::printf("code result: ===========\n");
  print_attacked_status(board.m_board);


  clear_utility_flags(board.m_board);

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_attacked_status(board.m_board);

  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(ROOK);

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_attacked_status(board.m_board);

  fill_rook_move<ATTACKED_SQUARE>({3, 3}, board.m_board);

  std::printf("expected: ===========\n");
  std::printf("| O O O X |\n");
  std::printf("| O O O X |\n");
  std::printf("| O O O X |\n");
  std::printf("| X X X O |\n");
  std::printf("code result: ===========\n");
  print_attacked_status(board.m_board);
}

void test_rook_legal_squares(){
  Board board;
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << black_piece(ROOK) << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_legal_status(board.m_board);

  fill_rook_move<LEGAL_SQUARE>({1, 1}, board.m_board);

  std::printf("expected: ===========\n");
  std::printf("| O X O O |\n");
  std::printf("| X O X X |\n");
  std::printf("| O X O O |\n");
  std::printf("| O X O O |\n");
  std::printf("code result: ===========\n");
  print_legal_status(board.m_board);


  clear_utility_flags(board.m_board);

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_legal_status(board.m_board);

  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(ROOK);

  std::printf("expected: ===========\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("| O O O O |\n");
  std::printf("code result: ===========\n");
  print_legal_status(board.m_board);

  fill_rook_move<LEGAL_SQUARE>({3, 3}, board.m_board);

  std::printf("expected: ===========\n");
  std::printf("| O O O X |\n");
  std::printf("| O O O X |\n");
  std::printf("| O O O X |\n");
  std::printf("| X X X O |\n");
  std::printf("code result: ===========\n");
  print_legal_status(board.m_board);
}

void test_bishop_attacked_squares(){

}

void test_bishop_legal_squares(){

}

void test_knight_attacked_squares(){

}

void test_knight_legal_squares(){

}

void test_queen_attacked_squares(){

}

void test_queen_legal_squares(){

}

void test_king_attacked_squares(){

}

void test_king_move_squares(){

}

void test_pawn_attacked_squares(){

}

void test_pawn_move_squares(){

}

void test_king_board_update_after_measurment(){

}

void test_queen_board_update_after_measurment(){

}

void test_pawn_board_update_after_measurment(){

}

void test_knight_board_update_after_measurment(){

}

void test_rook_board_update_after_measurment(){

}

void test_bishop_board_update_after_measurment(){

}

int main()
{
  std::printf("test_white_piece_measurment_detection: <------------> \n"); test_white_piece_measurment_detection();
  std::printf("test_black_piece_measurment_detection: <------------> \n"); test_black_piece_measurment_detection();
  std::printf("test_piece_measurment_detection: <------------> \n"); test_piece_measurment_detection();
  std::printf("test_rook_attacked_squares: <------------> \n"); test_rook_attacked_squares();
  std::printf("test_rook_legal_squares: <------------> \n"); test_rook_legal_squares();
  return 0;
}