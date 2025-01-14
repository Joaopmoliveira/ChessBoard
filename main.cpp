#include "test_utilities.h"

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

void test_bishop_legal_squares(){
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

void test_knight_attacked_squares(){
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

void test_knight_legal_squares(){
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

void test_queen_attacked_squares(){
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

void test_queen_legal_squares(){
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

void test_king_attacked_squares(){
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

void test_king_legal_squares(){
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

void test_pawn_attacked_squares(){
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

void test_pawn_move_squares(){
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

void test_king_board_update_after_measurment(){
  Board board{false};
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << black_piece(KING) << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

  std::array<uint16_t, n_squares> measurments{515,          515,              dummy_black,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515};
  std::printf("expected: ===========\n");
  std::printf("| O O  O  O |\n");
  std::printf("| O bK O  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  auto error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| O O  bK  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{515,          515,              515,         dummy_black,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515};

  board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| O O  O  bK |\n");
  std::printf("| O O  O  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         dummy_black};
  board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("expected error: %s\n", error);};

  // the board should still retain the board in the previous state
  std::printf("expected: ===========\n");
  std::printf("| O O  O  bK |\n");
  std::printf("| O O  O  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("| O O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;
}

void test_queen_board_update_after_measurment(){
  Board board{false};
  board << black_piece(KING) << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << black_piece(QUEEN) << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE;

  std::array<uint16_t, n_squares> measurments{dummy_black,          515,              dummy_black,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515};
  std::printf("expected: ===========\n");
  std::printf("| bK O  O  O |\n");
  std::printf("| O  bQ O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  auto error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| bK O bQ  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{dummy_black,        515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              dummy_black,         515};
                                              
  board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| bK O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O bQ  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{dummy_black,          515,              515,         515,
                                              515,          515,              515,         dummy_black,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515};
  board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("expected error: %s\n", error);};

  // the board should still retain the board in the previous state
  std::printf("expected: ===========\n");
  std::printf("| bK O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O bQ  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;
}

void test_pawn_board_update_after_measurment_start_with_two_squares(){
  Board board{false};
  board << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << NO_PIECE << NO_PIECE << NO_PIECE << NO_PIECE
        << black_piece(KING) << black_piece(PAWN) << NO_PIECE << NO_PIECE;

  std::array<uint16_t, n_squares> measurments{515,          515,              515,         515,
                                              515,          dummy_black,        515,         515,
                                              515,          515,                515,         515,
                                              dummy_black,  515,                515,         515};
  std::printf("expected: ===========\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| bK bP  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  auto error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  bP  O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| bK O   O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{515,        dummy_black,      515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              dummy_black,  515,              515  ,       515};
                                              
  board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| O bP  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{515,          515,              dummy_black,         515,
                                              515,          515,              515,         515, 
                                              515,          515,              515,         515,
                                              dummy_black,          515,              515,         515};
  board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("expected error: %s\n", error);};

  // the board should still retain the board in the previous state
  std::printf("expected: ===========\n");
  std::printf("| O bP  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;
}

void test_knight_board_update_after_measurment(){
  Board board{false};
  board << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << black_piece(KING) << black_piece(KNIGHT)   << NO_PIECE << NO_PIECE;

  std::array<uint16_t, n_squares> measurments{515,          515,              515,         515,
                                              515,          515,        dummy_black,         515,
                                              515,          515,                515,         515,
                                              dummy_black,  515,                515,         515};
  std::printf("expected: ===========\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| bK bN  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  auto error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O  bN  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| bK O   O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{dummy_black,515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              dummy_black,  515,              515  ,       515};
                                              
  board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| bN O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{515,          515,              dummy_black,         515,
                                              515,          515,              515,         515, 
                                              515,          515,              515,         515,
                                              dummy_black,          515,              515,         515};
  board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("expected error: %s\n", error);};

  // the board should still retain the board in the previous state
  std::printf("expected: ===========\n");
  std::printf("| bN O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;
}

void test_rook_board_update_after_measurment(){
  Board board{false};
  board << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << black_piece(KING) << black_piece(ROOK)   << NO_PIECE << NO_PIECE;

  std::array<uint16_t, n_squares> measurments{515,          dummy_black,        515,         515,
                                              515,          515,                515,         515,
                                              515,          515,                515,         515,
                                              dummy_black,  515,                515,         515};
  std::printf("expected: ===========\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| bK bR  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  auto error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| O  bR  O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| bK O   O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{dummy_black,515,              515,         515,
                                              515,          515,              515,         515,
                                              515,          515,              515,         515,
                                              dummy_black,  515,              515  ,       515};
                                              
  board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| bR O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{515,          515,              515,         515,
                                              515,          dummy_black,              515,         515, 
                                              515,          515,              515,         515,
                                              dummy_black,          515,              515,         515};
  board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("expected error: %s\n", error);};

  // the board should still retain the board in the previous state
  std::printf("expected: ===========\n");
  std::printf("| bR O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;
}

void test_bishop_board_update_after_measurment(){
  Board board{false};
  board << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << NO_PIECE          << NO_PIECE              << NO_PIECE << NO_PIECE
        << black_piece(KING) << black_piece(BISHOP)   << NO_PIECE << NO_PIECE;

  std::array<uint16_t, n_squares> measurments{515,          515,        515,         515,
                                              515,          515,        515,         dummy_black,
                                              515,          515,        515,         515,
                                              dummy_black,  515,        515,         515};
  std::printf("expected: ===========\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| O  O   O  O |\n");
  std::printf("| bK bB  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  auto error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  bB |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{515        ,515,      dummy_black,         515,
                                                515,        515,              515,         515,
                                                515,        515,              515,         515,
                                              dummy_black,  515,              515  ,       515};
                                              
  board.white_turn = false; // we allow black to move twice in a row... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("unexpected error: %s\n", error); return;};

  std::printf("expected: ===========\n");
  std::printf("| O  O  bB O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;

  measurments = std::array<uint16_t, n_squares>{515,         dummy_black,              515,         515,
                                              515,               515,              515,         515, 
                                              515,               515,              515,         515,
                                              dummy_black,       515,              515,         515};
  board.white_turn = false; // we allow black to move trice... this is actually illegal but for now it allows us to check stuff
  error = board.update(measurments);
  if(error) {std::printf("expected error: %s\n", error);};

  // the board should still retain the board in the previous state
  std::printf("expected: ===========\n");
  std::printf("| O  O  bB O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| O  O  O  O |\n");
  std::printf("| bK O  O  O |\n");
  std::printf("code result: ===========\n");
  std::cout << board << std::endl;
}



int main(){
  std::printf("test_white_piece_measurment_detection: <=================================> \n"); test_white_piece_measurment_detection();
  std::printf("test_black_piece_measurment_detection: <=================================> \n"); test_black_piece_measurment_detection();
  std::printf("test_piece_measurment_detection: <=================================> \n"); test_piece_measurment_detection();
  std::printf("test_rook_attacked_squares: <=================================> \n"); test_rook_attacked_squares();
  std::printf("test_rook_legal_squares: <=================================> \n"); test_rook_legal_squares();
  std::printf("test_knight_attacked_squares: <=================================> \n"); test_knight_attacked_squares();
  std::printf("test_knight_legal_squares: <=================================> \n"); test_knight_legal_squares();
  std::printf("test_queen_attacked_squares: <=================================> \n"); test_queen_attacked_squares();
  std::printf("test_queen_legal_squares: <=================================> \n"); test_queen_legal_squares();
  std::printf("test_king_attacked_squares: <=================================> \n"); test_king_attacked_squares();
  std::printf("test_king_legal_squares: <=================================> \n"); test_king_legal_squares();
  std::printf("test_pawn_attacked_squares: <=================================> \n"); test_pawn_attacked_squares();
  std::printf("test_pawn_move_squares: <=================================> \n"); test_pawn_move_squares();
  std::printf("test_king_board_update_after_measurment: <=================================> \n"); test_king_board_update_after_measurment();
  std::printf("test_queen_board_update_after_measurment: <=================================> \n"); test_queen_board_update_after_measurment();
  std::printf("test_pawn_board_update_after_measurment_start_with_two_squares: <=================================> \n"); test_pawn_board_update_after_measurment_start_with_two_squares();
  std::printf("test_knight_board_update_after_measurment: <=================================> \n"); test_knight_board_update_after_measurment();
  std::printf("test_rook_board_update_after_measurment: <=================================> \n"); test_rook_board_update_after_measurment();
  std::printf("test_bishop_board_update_after_measurment: <=================================> \n"); test_bishop_board_update_after_measurment();
  return 0;
}