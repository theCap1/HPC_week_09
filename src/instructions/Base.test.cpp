#include <catch2/catch.hpp>
#include "Base.h"

TEST_CASE( "Tests dpAddSr.", "[Base][dpAddSr]" ) {
  uint32_t l_ins = 0;
  mini_jit::instructions::Base::shift_t l_shift = mini_jit::instructions::Base::shift_t::lsl;

  // add x0, x0, x0
  l_ins = mini_jit::instructions::Base::dpAddSr( 0,
                                                 0,
                                                 0,
                                                 0,
                                                 l_shift,
                                                 1 );
  REQUIRE( l_ins == 0x8B000000 );

  // add x5, x4, x2
  l_ins = mini_jit::instructions::Base::dpAddSr( 5,
                                                 4,
                                                 2,
                                                 0,
                                                 l_shift,
                                                 1 );
  REQUIRE( l_ins == 0x8b020085 );

  // add x12, x22, x4, lsl #17
  l_ins = mini_jit::instructions::Base::dpAddSr( 12,
                                                 22,
                                                 4,
                                                 17,
                                                 l_shift,
                                                 1 );
  REQUIRE( l_ins == 0x8b0446cc );

  l_shift = mini_jit::instructions::Base::shift_t::lsr;
  // add w12, w22, w4, lsr #17
  l_ins = mini_jit::instructions::Base::dpAddSr( 12,
                                                 22,
                                                 4,
                                                 17,
                                                 l_shift,
                                                 0 );
  REQUIRE( l_ins == 0x0b4446cc );
}

TEST_CASE( "Tests dpLdrImm.", "[Base][dpLdrImm]" ) {
  uint32_t l_ins = 0;

  // ldr w0, [x0], #0
  l_ins = mini_jit::instructions::Base::dpLdrImm( 0,
                                                  0,
                                                  0,
                                                  0,
                                                  0 );
  REQUIRE( l_ins == 0xb8400400 );

  // ldr w1, [x0], #0
  l_ins = mini_jit::instructions::Base::dpLdrImm( 1,
                                                  0,
                                                  0,
                                                  0,
                                                  0 );
  REQUIRE( l_ins == 0xb8400401 );

  // ldr w1, [x0], #1
  l_ins = mini_jit::instructions::Base::dpLdrImm( 1,
                                                  0,
                                                  0,
                                                  1,
                                                  0 );
  REQUIRE( l_ins == 0xb8401401 );

  // ldr x5, [x0], #23
  l_ins = mini_jit::instructions::Base::dpLdrImm( 5,
                                                  0,
                                                  0,
                                                  23,
                                                  1 );
  REQUIRE( l_ins == 0xf8417405 );

  // ldr x5, [x0, #23]!
  l_ins = mini_jit::instructions::Base::dpLdrImm( 5,
                                                  0,
                                                  1,
                                                  23,
                                                  1 );
  REQUIRE( l_ins == 0xf8417c05 );

  // ldr w5, [x0, #23]!
  l_ins = mini_jit::instructions::Base::dpLdrImm( 5,
                                                  0,
                                                  1,
                                                  23,
                                                  0 );
  REQUIRE( l_ins == 0xb8417c05 );
}