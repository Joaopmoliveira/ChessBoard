#include "embbeded_chess_logic.h"

constexpr uint16_t dummy_black = 560;
constexpr uint16_t dummy_white = 490;

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