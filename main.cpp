#include <iostream>
using U64 = unsigned long long;

// clang-format off
enum Square {
  a8, b8, c8, d8, e8, f8, g8, h8,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a1, b1, c1, d1, e1, f1, g1, h1
};

enum Colors {white, black};

const std::string square_to_coordinate[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "a7", "b7", "c7",
    "d7", "e7", "f7", "g7", "h7", "a6", "b6", "c6", "d6", "e6", "f6",
    "g6", "h6", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a4",
    "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a3", "b3", "c3", "d3",
    "e3", "f3", "g3", "h3", "a2", "b2", "c2", "d2", "e2", "f2", "g2",
    "h2", "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

// clang-format on

unsigned int state = 1804289383;

unsigned int get_random_U32_number() {
  unsigned int number = state;

  number ^= number << 13;
  number ^= number >> 17;
  number ^= number << 5;

  state = number;
  return state;
}

U64 get_random_U64_number() {
  U64 n1, n2, n3, n4;

  n1 = (U64)(get_random_U32_number() & 0xFFFF);
  n2 = (U64)(get_random_U32_number() & 0xFFFF);
  n3 = (U64)(get_random_U32_number() & 0xFFFF);
  n4 = (U64)(get_random_U32_number() & 0xFFFF);

  return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

U64 generate_magic_number() {
  return get_random_U64_number() & get_random_U64_number() &
         get_random_U64_number();
}

// set/get/pop macros
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square)                                              \
  set_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define count_bits(bitboard) __builtin_popcountll(bitboard)
#define get_lsb_index(bb) __builtin_ctzll(bb)

// static inline int count_bits(U64 bitboard) {
//   int count = 0;
//
//   while (bitboard) {
//     count++;
//     bitboard &= bitboard - 1;
//   }
//
//   return count;
// }
// static inline int get_lsb_index(U64 bitboard){
// if(bitboard){
// return count_bits((bitboard & - bitboard) - 1);
// }
// else
// return -1;
// }
void print_bitboard(U64 bitboard) {
  std::cout << "\n";
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      int square = rank * 8 + file;

      if (!file) {
        std::cout << (8 - rank) << " ";
      }

      std::cout << (get_bit(bitboard, square) ? 1 : 0) << " ";
    }
    std::cout << "\n";
  }

  std::cout << "  a b c d e f g h\n\n";
  std::cout << "Bitboard: " << bitboard << std::endl;
  ;
}

// not a file
// 8 0 1 1 1 1 1 1 1
// 7 0 1 1 1 1 1 1 1
// 6 0 1 1 1 1 1 1 1
// 5 0 1 1 1 1 1 1 1
// 4 0 1 1 1 1 1 1 1
// 3 0 1 1 1 1 1 1 1
// 2 0 1 1 1 1 1 1 1
// 1 0 1 1 1 1 1 1 1
//   a b c d e f g h
// Bitboard: 18374403900871474942
//
//
// not h file
// 8 1 1 1 1 1 1 1 0
// 7 1 1 1 1 1 1 1 0
// 6 1 1 1 1 1 1 1 0
// 5 1 1 1 1 1 1 1 0
// 4 1 1 1 1 1 1 1 0
// 3 1 1 1 1 1 1 1 0
// 2 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 1 0
//  a b c d e f g h
// Bitboard: 9187201950435737471
//
// not gh file
//
// 8 1 1 1 1 1 1 0 0
// 7 1 1 1 1 1 1 0 0
// 6 1 1 1 1 1 1 0 0
// 5 1 1 1 1 1 1 0 0
// 4 1 1 1 1 1 1 0 0
// 3 1 1 1 1 1 1 0 0
// 2 1 1 1 1 1 1 0 0
// 1 1 1 1 1 1 1 0 0
//  a b c d e f g h
// Bitboard: 4557430888798830399
//
// not ab file
// 8 0 0 1 1 1 1 1 1
// 7 0 0 1 1 1 1 1 1
// 6 0 0 1 1 1 1 1 1
// 5 0 0 1 1 1 1 1 1
// 4 0 0 1 1 1 1 1 1
// 3 0 0 1 1 1 1 1 1
// 2 0 0 1 1 1 1 1 1
// 1 0 0 1 1 1 1 1 1
//  a b c d e f g h
//
// Bitboard: 18229723555195321596

const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_hg_file = 4557430888798830399ULL;
const U64 not_ab_file = 18229723555195321596ULL;

// relevant occupacy bit count for every square on board
const int bishop_relevant_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7,
    5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7,
    7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6,
};

const int rook_relevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 12, 11, 11, 11, 11, 11, 11, 12,
};

// pawn attacks table [side to move][attack availbale in current given square]
U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 king_attacks[64];
U64 bishop_attacks[64];
U64 rook_attacks[64];

U64 mask_pawn_attacks(int square, int side) {
  // result attacks bitboard
  U64 attacks = 0ULL;

  U64 bitboard = 0ULL;
  set_bit(bitboard, square);

  // white pawns
  if (!side) {
    if ((bitboard >> 7) & not_a_file)
      attacks |= (bitboard >> 7);
    if ((bitboard >> 9) & not_h_file)
      attacks |= (bitboard >> 9);
  } else { // black pawns
    if ((bitboard << 7) & not_h_file)
      attacks |= (bitboard << 7);
    if ((bitboard << 9) & not_a_file)
      attacks |= (bitboard << 9);
  }

  return attacks;
}

U64 mask_knight_attacks(int square) {
  // result attacks bitboard
  U64 attacks = 0ULL;

  U64 bitboard = 0ULL;
  set_bit(bitboard, square);

  // knight attack 17,15,10,6
  if ((bitboard >> 17) & not_h_file)
    attacks |= (bitboard >> 17);
  if ((bitboard >> 15) & not_a_file)
    attacks |= (bitboard >> 15);
  if ((bitboard >> 10) & not_hg_file)
    attacks |= (bitboard >> 10);
  if ((bitboard >> 6) & not_ab_file)
    attacks |= (bitboard >> 6);
  if ((bitboard << 17) & not_a_file)
    attacks |= (bitboard << 17);
  if ((bitboard << 15) & not_h_file)
    attacks |= (bitboard << 15);
  if ((bitboard << 10) & not_ab_file)
    attacks |= (bitboard << 10);
  if ((bitboard << 6) & not_hg_file)
    attacks |= (bitboard << 6);

  return attacks;
}

U64 mask_king_attacks(int square) {
  U64 attacks = 0ULL;

  U64 bitboard = 0ULL;
  set_bit(bitboard, square);
  if ((bitboard >> 8))
    attacks |= (bitboard >> 8);
  if ((bitboard >> 9) & not_h_file)
    attacks |= (bitboard >> 9);
  if ((bitboard >> 7) & not_a_file)
    attacks |= (bitboard >> 7);
  if ((bitboard >> 1) & not_h_file)
    attacks |= (bitboard >> 1);
  if ((bitboard << 8))
    attacks |= (bitboard << 8);
  if ((bitboard << 9) & not_a_file)
    attacks |= (bitboard << 9);
  if ((bitboard << 7) & not_h_file)
    attacks |= (bitboard << 7);
  if ((bitboard << 1) & not_a_file)
    attacks |= (bitboard << 1);
  return attacks;
}

U64 mask_bishop_attacks(int square) {
  U64 attacks = 0ULL;

  U64 bitboard = 0ULL;
  set_bit(bitboard, square);

  int r, f; // rank and file

  // target rank and file
  int tr = square / 8;
  int tf = square % 8;

  for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++)
    attacks |= (1ULL << (r * 8 + f));

  for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++)
    attacks |= (1ULL << (r * 8 + f));

  for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--)
    attacks |= (1ULL << (r * 8 + f));

  for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--)
    attacks |= (1ULL << (r * 8 + f));
  return attacks;
}

U64 mask_rook_attacks(int square) {
  U64 attacks = 0ULL;

  U64 bitboard = 0ULL;
  set_bit(bitboard, square);

  int r, f; // rank and file

  // target rank and file
  int tr = square / 8;
  int tf = square % 8;

  for (r = tr + 1; r <= 6; r++)
    attacks |= (1ULL << (r * 8 + tf));
  for (r = tr - 1; r >= 1; r--)
    attacks |= (1ULL << (r * 8 + tf));
  for (f = tf + 1; f <= 6; f++)
    attacks |= (1ull << (tr * 8 + f));
  for (f = tf - 1; f >= 1; f--)
    attacks |= (1ull << (tr * 8 + f));
  return attacks;
}

U64 bishop_attacks_on_the_fly(int square, U64 block) {
  U64 attacks = 0ULL;

  U64 bitboard = 0ULL;
  set_bit(bitboard, square);

  int r, f; // rank and file

  // target rank and file
  int tr = square / 8;
  int tf = square % 8;

  for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
    attacks |= (1ULL << (r * 8 + f));
    if ((1ULL << (r * 8 + f)) & block)
      break;
  }

  for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
    attacks |= (1ULL << (r * 8 + f));
    if ((1ULL << (r * 8 + f)) & block)
      break;
  }

  for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
    attacks |= (1ULL << (r * 8 + f));
    if ((1ULL << (r * 8 + f)) & block)
      break;
  }

  for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
    attacks |= (1ULL << (r * 8 + f));
    if ((1ULL << (r * 8 + f)) & block)
      break;
  }

  return attacks;
}
U64 rook_attacks_on_the_fly(int square, U64 block) {
  U64 attacks = 0ULL;

  U64 bitboard = 0ULL;
  set_bit(bitboard, square);

  int r, f; // rank and file

  // target rank and file
  int tr = square / 8;
  int tf = square % 8;

  for (r = tr + 1; r <= 7; r++) {
    attacks |= (1ULL << (r * 8 + tf));
    if ((1ULL << (r * 8 + tf)) & block)
      break;
  }
  for (r = tr - 1; r >= 0; r--) {
    attacks |= (1ULL << (r * 8 + tf));
    if ((1ULL << (r * 8 + tf)) & block)
      break;
  }
  for (f = tf + 1; f <= 7; f++) {
    attacks |= (1ull << (tr * 8 + f));
    if ((1ULL << (tr * 8 + f)) & block)
      break;
  }
  for (f = tf - 1; f >= 0; f--) {
    attacks |= (1ull << (tr * 8 + f));
    if ((1ULL << (tr * 8 + f)) & block)
      break;
  }

  return attacks;
}

// init leaper pieces
void init_leapers_attacks() {
  for (int square = 0; square < 64; square++) {
    king_attacks[square] = mask_king_attacks(square);
    pawn_attacks[white][square] = mask_pawn_attacks(square, white);
    pawn_attacks[black][square] = mask_pawn_attacks(square, black);
    knight_attacks[square] = mask_knight_attacks(square);
  }
}

// ocuupancy
U64 set_occupancy(int index, int bits_in_mask, U64 attack_map) {
  U64 occupancy = 0ULL;

  for (int count = 0; count < bits_in_mask; count++) {
    // get lsb index of attack mask
    int square = get_lsb_index(attack_map);
    // pop lsb index in attack map
    pop_bit(attack_map, square);
    // pop lsb index in attack map
    if (index & (1 << count))
      occupancy |= (1ULL << square);
  }

  return occupancy;
}
int main() {

  // init_leapers_attacks();

  // std::cout << random();

  print_bitboard((U64)get_random_U32_number());
  print_bitboard((U64)get_random_U32_number() & 0xFFFF);
  print_bitboard(get_random_U64_number());
  print_bitboard(generate_magic_number());
  return 0;
}
