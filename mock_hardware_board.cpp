#include "test_utilities.h"
#include <utility>
#include <chrono>
#include <array>

template<typename T,unsigned int s>
array<T,s> convert_array(std::array<T,s> in){
      array<T,s> local;
      for(size_t i = 0; i < s; ++i){
            local[i] = in[i]; 
      }
      return local;
}

/*
Time to write tests that validate the logic of the game :
1. validate legal logic of game
2. validate attack logic of game
3. validate first logic of game
4. validate en passant logic of game
*/
void test_white_piece_measurment_detection()
{
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
      print_detected_black_piece_status(board.m_board);
      std::printf("\n");

      std::array<uint16_t, n_squares> measurments{dummy_black, 515, 515, dummy_black,
                                                  515, 515, 515, 515,
                                                  dummy_white, dummy_white, 515, dummy_white,
                                                  515, 515, dummy_black, 515};

      clear_and_update_detection(board.m_board, convert_array<uint16_t, n_squares>(measurments));

      std::printf("expected: ===========\n");
      std::printf("| X O O X |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O X O |\n");
      std::printf("code result: ===========\n");
      print_detected_black_piece_status(board.m_board);
      std::printf("\n");
}

void test_black_piece_measurment_detection()
{
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
      print_detected_black_piece_status(board.m_board);
      std::printf("\n");

      std::array<uint16_t, n_squares> measurments{dummy_black, 515, 515, dummy_black,
                                                  515, 515, 515, 515,
                                                  dummy_white, dummy_white, 515, dummy_white,
                                                  515, 515, dummy_black, 515};

      clear_and_update_detection(board.m_board, convert_array<uint16_t, n_squares>(measurments));

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| X X O X |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_detected_white_piece_status(board.m_board);
      std::printf("\n");
}

void test_piece_measurment_detection()
{
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
      print_detected_black_piece_status(board.m_board);
      std::printf("\n");

      std::array<uint16_t, n_squares> measurments{dummy_black, 515, 515, dummy_black,
                                                  515, 515, 515, 515,
                                                  dummy_white, dummy_white, 515, dummy_white,
                                                  515, 515, dummy_black, 515};

      clear_and_update_detection(board.m_board, convert_array<uint16_t, n_squares>(measurments));

      std::printf("expected: ===========\n");
      std::printf("| X O O X |\n");
      std::printf("| O O O O |\n");
      std::printf("| X X O X |\n");
      std::printf("| O O X O |\n");
      std::printf("code result: ===========\n");
      print_detected_piece_status(board.m_board);
      std::printf("\n");
}

void test_rook_attacked_squares()
{
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

void test_rook_legal_squares()
{
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

void test_bishop_attacked_squares()
{
      Board board;
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(BISHOP) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_bishop_move<ATTACKED_SQUARE>({1, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X O X O |\n");
      std::printf("| O O O O |\n");
      std::printf("| X O X O |\n");
      std::printf("| O O O X |\n");
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
            << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(BISHOP);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_bishop_move<ATTACKED_SQUARE>({3, 3}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X O O O |\n");
      std::printf("| O X O O |\n");
      std::printf("| O O X O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);
}

void test_bishop_legal_squares()
{
      Board board;
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(BISHOP) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_bishop_move<LEGAL_SQUARE>({1, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X O X O |\n");
      std::printf("| O O O O |\n");
      std::printf("| X O X O |\n");
      std::printf("| O O O X |\n");
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
            << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(BISHOP);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_bishop_move<LEGAL_SQUARE>({3, 3}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X O O O |\n");
      std::printf("| O X O O |\n");
      std::printf("| O O X O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);
}

void test_knight_attacked_squares()
{
      Board board;
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(KNIGHT) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_knight_move<ATTACKED_SQUARE>({1, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O X |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O X |\n");
      std::printf("| X O X O |\n");
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
            << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(KNIGHT);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_knight_move<ATTACKED_SQUARE>({3, 3}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O X O |\n");
      std::printf("| O X O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);
}

void test_knight_legal_squares()
{
      Board board;
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(KNIGHT) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_knight_move<LEGAL_SQUARE>({1, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O X |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O X |\n");
      std::printf("| X O X O |\n");
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
            << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(KNIGHT);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_knight_move<LEGAL_SQUARE>({3, 3}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O X O |\n");
      std::printf("| O X O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);
}

void test_queen_attacked_squares()
{
      Board board;
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(QUEEN) << NO_PIECE << NO_PIECE
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
      fill_bishop_move<ATTACKED_SQUARE>({1, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X X X O |\n");
      std::printf("| X O X X |\n");
      std::printf("| X X X O |\n");
      std::printf("| O X O X |\n");
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
            << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(QUEEN);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_rook_move<ATTACKED_SQUARE>({3, 3}, board.m_board);
      fill_bishop_move<ATTACKED_SQUARE>({3, 3}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X O O X |\n");
      std::printf("| O X O X |\n");
      std::printf("| O O X X |\n");
      std::printf("| X X X O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);
}

void test_queen_legal_squares()
{
      Board board;
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(QUEEN) << NO_PIECE << NO_PIECE
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
      fill_bishop_move<LEGAL_SQUARE>({1, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X X X O |\n");
      std::printf("| X O X X |\n");
      std::printf("| X X X O |\n");
      std::printf("| O X O X |\n");
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
            << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(QUEEN);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_rook_move<LEGAL_SQUARE>({3, 3}, board.m_board);
      fill_bishop_move<LEGAL_SQUARE>({3, 3}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X O O X |\n");
      std::printf("| O X O X |\n");
      std::printf("| O O X X |\n");
      std::printf("| X X X O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);
}

void test_king_attacked_squares()
{
      Board board;
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(KING) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_king_move<ATTACKED_SQUARE>({1, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X X X O |\n");
      std::printf("| X O X O |\n");
      std::printf("| X X X O |\n");
      std::printf("| O O O O |\n");
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
            << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(KING);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_king_move<ATTACKED_SQUARE>({3, 3}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O X X |\n");
      std::printf("| O O X O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);
}

void test_king_legal_squares()
{
      Board board;
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(KING) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_king_move<LEGAL_SQUARE>({1, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| X X X O |\n");
      std::printf("| X O X O |\n");
      std::printf("| X X X O |\n");
      std::printf("| O O O O |\n");
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
            << NO_PIECE << NO_PIECE << NO_PIECE << black_piece(KING);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_king_move<LEGAL_SQUARE>({3, 3}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O X X |\n");
      std::printf("| O O X O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);
}

void test_pawn_attacked_squares()
{
      Board board;
      board << NO_PIECE << white_piece(PAWN) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_pawn_attack({0, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| X O X O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
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
            << NO_PIECE << NO_PIECE << black_piece(PAWN) << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);

      fill_pawn_attack({3, 2}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O X O X |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_attacked_status(board.m_board);
}

void test_pawn_move_squares()
{
      Board board;
      board << NO_PIECE << white_piece(PAWN) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_pawn_move({0, 1}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O X O O |\n");
      std::printf("| O X O O |\n");
      std::printf("| O O O O |\n");
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
            << NO_PIECE << NO_PIECE << black_piece(PAWN) << NO_PIECE;

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);

      fill_pawn_move({3, 2}, board.m_board);

      std::printf("expected: ===========\n");
      std::printf("| O O O O |\n");
      std::printf("| O O X O |\n");
      std::printf("| O O X O |\n");
      std::printf("| O O O O |\n");
      std::printf("code result: ===========\n");
      print_legal_status(board.m_board);
}

void test_king_board_update_after_measurment()
{
      Board board{false};
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(KING) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::array<uint16_t, n_squares> measurments{515, 515, dummy_black, 515,
                                                  515, 515, 515, 515,
                                                  515, 515, 515, 515,
                                                  515, 515, 515, 515};
      std::printf("expected: ===========\n");
      std::printf("| O O  O  O |\n");
      std::printf("| O bK O  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      auto error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| O O  bK  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{515, 515, 515, dummy_black,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515};

      board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| O O  O  bK |\n");
      std::printf("| O O  O  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, dummy_black};
      board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("expected error: %s\n", error);
      };

      // the board should still retain the board in the previous state
      std::printf("expected: ===========\n");
      std::printf("| O O  O  bK |\n");
      std::printf("| O O  O  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("| O O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;
}

void test_queen_board_update_after_measurment()
{
      Board board{false};
      board << black_piece(KING) << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << black_piece(QUEEN) << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

      std::array<uint16_t, n_squares> measurments{dummy_black, 515, dummy_black, 515,
                                                  515, 515, 515, 515,
                                                  515, 515, 515, 515,
                                                  515, 515, 515, 515};
      std::printf("expected: ===========\n");
      std::printf("| bK O  O  O |\n");
      std::printf("| O  bQ O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      auto error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| bK O bQ  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{dummy_black, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, dummy_black, 515};

      board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| bK O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O bQ  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{dummy_black, 515, 515, 515,
                                                    515, 515, 515, dummy_black,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515};
      board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("expected error: %s\n", error);
      };

      // the board should still retain the board in the previous state
      std::printf("expected: ===========\n");
      std::printf("| bK O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O bQ  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;
}

void test_pawn_board_update_after_measurment_start_with_two_squares()
{
      Board board{false};
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << black_piece(KING) << black_piece(PAWN) << NO_PIECE << NO_PIECE;

      std::array<uint16_t, n_squares> measurments{515, 515, 515, 515,
                                                  515, dummy_black, 515, 515,
                                                  515, 515, 515, 515,
                                                  dummy_black, 515, 515, 515};
      std::printf("expected: ===========\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| bK bP  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      auto error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  bP  O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| bK O   O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{515, dummy_black, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    dummy_black, 515, 515, 515};

      board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| O bP  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{515, 515, dummy_black, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    dummy_black, 515, 515, 515};
      board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("expected error: %s\n", error);
      };

      // the board should still retain the board in the previous state
      std::printf("expected: ===========\n");
      std::printf("| O bP  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;
}

void test_knight_board_update_after_measurment()
{
      Board board{false};
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << black_piece(KING) << black_piece(KNIGHT) << NO_PIECE << NO_PIECE;

      std::array<uint16_t, n_squares> measurments{515, 515, 515, 515,
                                                  515, 515, dummy_black, 515,
                                                  515, 515, 515, 515,
                                                  dummy_black, 515, 515, 515};
      std::printf("expected: ===========\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| bK bN  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      auto error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O  bN  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| bK O   O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{dummy_black, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    dummy_black, 515, 515, 515};

      board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| bN O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{515, 515, dummy_black, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    dummy_black, 515, 515, 515};
      board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("expected error: %s\n", error);
      };

      // the board should still retain the board in the previous state
      std::printf("expected: ===========\n");
      std::printf("| bN O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;
}

void test_rook_board_update_after_measurment()
{
      Board board{false};
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << black_piece(KING) << black_piece(ROOK) << NO_PIECE << NO_PIECE;

      std::array<uint16_t, n_squares> measurments{515, dummy_black, 515, 515,
                                                  515, 515, 515, 515,
                                                  515, 515, 515, 515,
                                                  dummy_black, 515, 515, 515};
      std::printf("expected: ===========\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| bK bR  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      auto error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| O  bR  O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| bK O   O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{dummy_black, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    dummy_black, 515, 515, 515};

      board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| bR O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{515, 515, 515, 515,
                                                    515, dummy_black, 515, 515,
                                                    515, 515, 515, 515,
                                                    dummy_black, 515, 515, 515};
      board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("expected error: %s\n", error);
      };

      // the board should still retain the board in the previous state
      std::printf("expected: ===========\n");
      std::printf("| bR O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;
}

void test_bishop_board_update_after_measurment()
{
      Board board{false};
      board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << black_piece(KING) << black_piece(BISHOP) << NO_PIECE << NO_PIECE;

      std::array<uint16_t, n_squares> measurments{515, 515, 515, 515,
                                                  515, 515, 515, dummy_black,
                                                  515, 515, 515, 515,
                                                  dummy_black, 515, 515, 515};
      std::printf("expected: ===========\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| O  O   O  O |\n");
      std::printf("| bK bB  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      auto error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  bB |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{515, 515, dummy_black, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    dummy_black, 515, 515, 515};

      board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("unexpected error: %s\n", error);
            return;
      };

      std::printf("expected: ===========\n");
      std::printf("| O  O  bB O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;

      measurments = std::array<uint16_t, n_squares>{515, dummy_black, 515, 515,
                                                    515, 515, 515, 515,
                                                    515, 515, 515, 515,
                                                    dummy_black, 515, 515, 515};
      board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
      error = board.update(convert_array<uint16_t, n_squares>(measurments));
      if (error)
      {
            std::printf("expected error: %s\n", error);
      };

      // the board should still retain the board in the previous state
      std::printf("expected: ===========\n");
      std::printf("| O  O  bB O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| O  O  O  O |\n");
      std::printf("| bK O  O  O |\n");
      std::printf("code result: ===========\n");
      std::cout << board << std::endl;
}

struct requested_moves
{
      square piece_to_move;
      coord relative;
};

array<uint16_t, n_squares> find_and_move_piece(array<square, n_squares> raw_board, requested_moves to_move)
{
      array<uint16_t, n_squares> measurments{};
      measurments.fill(515);
      coord piece_to_move{};
      for (linear_array pos = 0; pos < n_squares; ++pos)
            if (has_piece(raw_board[pos]) && ((MASK_PIECES & raw_board[pos]) == (MASK_PIECES & to_move.piece_to_move)) && same_colors(raw_board[pos], to_move.piece_to_move))
            {
                  piece_to_move = convert(pos);
                  break;
            }
      coord final_position = coord(piece_to_move.row + to_move.relative.row, piece_to_move.col + to_move.relative.col);
      raw_board[convert(final_position)] = update_move(raw_board[convert(piece_to_move)]);
      raw_board[convert(piece_to_move)] = NO_PIECE;
      for (linear_array pos = 0; pos < n_squares; ++pos)
      {
            if (!has_piece(raw_board[pos]))
            {
                  measurments[pos] = 515;
                  continue;
            }
            if (raw_board[pos] & BLACK_PIECE)
            {
                  measurments[pos] = dummy_black;
                  continue;
            }
            else if (raw_board[pos] & WHITE_PIECE)
            {
                  measurments[pos] = dummy_white;
                  continue;
            }

            throw std::runtime_error("should not");
      }
      return measurments;
}

const char *expected_boards[] = {"| wK wR wB wP |\n| O  O  O  O|\n| O  O  O  O |\n| bK bR bB bP |",
                                 "| wK O  wB wP |\n| O  O  O  O|\n| O  O  O  O |\n| bK wR bB bP |",
                                 "| wK O  wB wP |\n| O  O  O  O|\n| O  O  O  O |\n| O  bK bB bP |",
                                 "| wK O  wB  O |\n| O  O  O  O|\n| O  O  O wP |\n| O  bK bB bP |",
                                 "| wK O  wB  O |\n| O  O  O  O|\n| O  O  O bB |\n| O  bK  O bP |"};

template <bool print>
void simulate_tiny_game()
{

      requested_moves moves_to_execute[] = {{ROOK | WHITE_PIECE, {3, 0}}, {KING | BLACK_PIECE, {0, 1}}, {PAWN | WHITE_PIECE, {2, 0}}, {BISHOP | BLACK_PIECE, {-1, 1}}};
      Board board{};
      board << white_piece(KING) << white_piece(ROOK) << white_piece(BISHOP) << white_piece(PAWN)
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
            << black_piece(KING) << black_piece(ROOK) << black_piece(BISHOP) << black_piece(PAWN);

      std::vector<size_t> durations;
      for (int i = 0; i < sizeof(moves_to_execute) / sizeof(requested_moves); ++i)
      {
            if constexpr (print)
            {
                  std::printf("\nexpected state :\n%s", expected_boards[i]);
                  std::printf("\ncode result:\n");
                  std::cout << board << std::endl;
            }
            auto measurments = find_and_move_piece(board.m_board, moves_to_execute[i]);
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            auto msg = board.update(measurments);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            durations.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());
            if constexpr (print)
            {
                  if (msg)
                  {
                        std::printf("detected unexpected error!!!! msg: %s\n", msg);
                  }
            }
      }
      if constexpr (print)
      {
            std::printf("\nexpected state :\n%s", expected_boards[3]);
            std::printf("\ncode result:\n");
            std::cout << board << std::endl;
      }
      for (const auto &timing : durations)
            std::cout << "Time difference = " << timing << "[ns]" << std::endl;
}

int main()
{
      std::printf("test_white_piece_measurment_detection: <=================================> \n");
      test_white_piece_measurment_detection();
      std::printf("test_black_piece_measurment_detection: <=================================> \n");
      test_black_piece_measurment_detection();
      std::printf("test_piece_measurment_detection: <=================================> \n");
      test_piece_measurment_detection();
      std::printf("test_rook_attacked_squares: <=================================> \n");
      test_rook_attacked_squares();
      std::printf("test_rook_legal_squares: <=================================> \n");
      test_rook_legal_squares();
      std::printf("test_knight_attacked_squares: <=================================> \n");
      test_knight_attacked_squares();
      std::printf("test_knight_legal_squares: <=================================> \n");
      test_knight_legal_squares();
      std::printf("test_queen_attacked_squares: <=================================> \n");
      test_queen_attacked_squares();
      std::printf("test_queen_legal_squares: <=================================> \n");
      test_queen_legal_squares();
      std::printf("test_king_attacked_squares: <=================================> \n");
      test_king_attacked_squares();
      std::printf("test_king_legal_squares: <=================================> \n");
      test_king_legal_squares();
      std::printf("test_pawn_attacked_squares: <=================================> \n");
      test_pawn_attacked_squares();
      std::printf("test_pawn_move_squares: <=================================> \n");
      test_pawn_move_squares();
      std::printf("test_king_board_update_after_measurment: <=================================> \n");
      test_king_board_update_after_measurment();
      std::printf("test_queen_board_update_after_measurment: <=================================> \n");
      test_queen_board_update_after_measurment();
      std::printf("test_pawn_board_update_after_measurment_start_with_two_squares: <=================================> \n");
      test_pawn_board_update_after_measurment_start_with_two_squares();
      std::printf("test_knight_board_update_after_measurment: <=================================> \n");
      test_knight_board_update_after_measurment();
      std::printf("test_rook_board_update_after_measurment: <=================================> \n");
      test_rook_board_update_after_measurment();
      std::printf("test_bishop_board_update_after_measurment: <=================================> \n");
      test_bishop_board_update_after_measurment();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<true>();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<false>();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<false>();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<false>();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<false>();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<false>();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<false>();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<false>();
      std::printf("simulate_tiny_game: <=================================> \n");
      simulate_tiny_game<false>();
      return 0;
}