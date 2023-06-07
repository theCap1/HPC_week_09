#include <iostream>
#include "Triad.h"
#include "../instructions/Base.h"
#include "../instructions/Asimd.h"

void ( *mini_jit::generators::Triad::Triad::generate( uint64_t i_nValues ) )( float const * i_a,
                                                                              float const * i_b,
                                                                              float       * o_c ) {
  uint32_t l_ins = 0;

  // store according to procedure call standard
  m_kernel.addInstruction( 0xA9BF53F3 );
  m_kernel.addInstruction( 0xA9BF5BF5 );
  m_kernel.addInstruction( 0xA9BF63F7 );
  m_kernel.addInstruction( 0xA9BF6BF9 );
  m_kernel.addInstruction( 0xA9BF73FB );
  m_kernel.addInstruction( 0xA9BF7BFD );

  m_kernel.addInstruction( 0x6DBF27E8 );
  m_kernel.addInstruction( 0x6DBF2FEA );
  m_kernel.addInstruction( 0x6DBF37EC );
  m_kernel.addInstruction( 0x6DBF3FEE );

  // set loop counter
  int m_counter = i_nValues/48;
  l_ins = instructions::Base::dpMovImm( 3,
                                        m_counter,
                                        1 );
  m_kernel.addInstruction( l_ins );

  mini_jit::instructions::Asimd::arrspec_t l_as = mini_jit::instructions::Asimd::arrspec_t::s4;

  // set multiplier for triad
  l_ins = instructions::Asimd::dpFmovVectorImm( 31,
                                                0,
                                                l_as );
  m_kernel.addInstruction( l_ins );

  // reset offset
  m_kernel.resetOffset();
  
  if (i_nValues/(48) > 0)   // do this until fewer than 48 values are left to process
  {
    for (int i = 0; i < 3; i++)
    {
      l_ins = instructions::Asimd::lsLd1MultipleNoOff(i*4,
                                                      0,
                                                      l_as,
                                                      4);
      m_kernel.addInstruction( l_ins );

      l_ins = instructions::Base::dpAddImm( 0,
                                            0,
                                            64,   // Bytes that are loaded in 4 register for 16 words
                                            1 );
      m_kernel.addInstruction( l_ins );

      l_ins = instructions::Asimd::lsLd1MultipleNoOff(12+i*4,
                                                      1,
                                                      l_as,
                                                      4);
      m_kernel.addInstruction( l_ins );

      l_ins = instructions::Base::dpAddImm( 1,
                                            1,
                                            64,
                                            1 );
      m_kernel.addInstruction( l_ins );
      
    }

    for (int i = 0; i < 12; i++)
    {
      l_ins = instructions::Asimd::dpFmla(  i,
                                            31,
                                            12+i,
                                            0,
                                            1 );
      m_kernel.addInstruction( l_ins );
    }

    for (int i = 0; i < 3; i++)
    {
      l_ins = instructions::Asimd::lsSt1MultipleNoOff(  i*4,
                                                        2,
                                                        l_as,
                                                        4 );
        m_kernel.addInstruction( l_ins );

        l_ins = instructions::Base::dpAddImm( 2,
                                              2,
                                              64,
                                              1 );
        m_kernel.addInstruction( l_ins );
    }
    

    // decrease loop-counter
    l_ins = instructions::Base::dpSubImm( 3,
                                          3,
                                          1,
                                          1 );
    m_kernel.addInstruction( l_ins );

    // loop if required
    int32_t l_jumpPc = -m_kernel.getOffset() / 4;
    l_ins = instructions::Base::bCbnz(  3,
                                        l_jumpPc,
                                        0 );
    m_kernel.addInstruction( l_ins );
  }

  /******************************************************************************/

  // set loop counter
  m_counter = (i_nValues%48)/16;
  l_ins = instructions::Base::dpMovImm( 3,
                                        m_counter,
                                        1 );
  m_kernel.addInstruction( l_ins );

  // reset offset
  m_kernel.resetOffset();

  if (m_counter > 0)   // do this until fewer than 16 values are left to process
  {
    l_ins = instructions::Asimd::lsLd1MultipleNoOff(0,
                                                    0,
                                                    l_as,
                                                    4);
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Base::dpAddImm( 0,
                                          0,
                                          64,   // Bytes that are loaded in 4 register for 16 words
                                          1 );
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Asimd::lsLd1MultipleNoOff(4,
                                                    1,
                                                    l_as,
                                                    4);
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Base::dpAddImm( 1,
                                          1,
                                          64,
                                          1 );
    m_kernel.addInstruction( l_ins );

    for (int i = 0; i < 4; i++)
    {
      l_ins = instructions::Asimd::dpFmla(  i,
                                            31,
                                            4+i,
                                            0,
                                            1 );
      m_kernel.addInstruction( l_ins );
    }

    l_ins = instructions::Asimd::lsSt1MultipleNoOff(  0,
                                                      2,
                                                      l_as,
                                                      4 );
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Base::dpAddImm( 2,
                                          2,
                                          64,
                                          1 );
    m_kernel.addInstruction( l_ins );
    

    // decrease loop-counter
    l_ins = instructions::Base::dpSubImm( 3,
                                          3,
                                          1,
                                          1 );
    m_kernel.addInstruction( l_ins );

    // loop if required
    int32_t l_jumpPc = -m_kernel.getOffset() / 4;
    l_ins = instructions::Base::bCbnz(  3,
                                        l_jumpPc,
                                        0 );
    m_kernel.addInstruction( l_ins );
  }

  /******************************************************************************/

  // set loop counter
  m_counter = ((i_nValues%48)%16)/4;
  l_ins = instructions::Base::dpMovImm( 3,
                                        m_counter,
                                        1 );
  m_kernel.addInstruction( l_ins );

  // reset offset
  m_kernel.resetOffset();

  if (m_counter > 0)   // do this until fewer than 4 values are left to process
  {
    l_ins = instructions::Asimd::lsLd1MultipleNoOff(0,
                                                    0,
                                                    l_as,
                                                    1);
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Base::dpAddImm( 0,
                                          0,
                                          16,   // Bytes that are loaded in 4 register for 16 words
                                          1 );
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Asimd::lsLd1MultipleNoOff(1,
                                                    1,
                                                    l_as,
                                                    1);
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Base::dpAddImm( 1,
                                          1,
                                          16,
                                          1 );
    m_kernel.addInstruction( l_ins );
      
    l_ins = instructions::Asimd::dpFmla(  0,
                                          31,
                                          1,
                                          0,
                                          1 );
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Asimd::lsSt1MultipleNoOff(  0,
                                                      2,
                                                      l_as,
                                                      1 );
    m_kernel.addInstruction( l_ins );

    l_ins = instructions::Base::dpAddImm( 2,
                                          2,
                                          16,
                                          1 );
    m_kernel.addInstruction( l_ins );
    

    // decrease loop-counter
    l_ins = instructions::Base::dpSubImm( 3,
                                          3,
                                          1,
                                          1 );
    m_kernel.addInstruction( l_ins );

    // loop if required
    int32_t l_jumpPc = -m_kernel.getOffset() / 4;
    l_ins = instructions::Base::bCbnz(  3,
                                        l_jumpPc,
                                        0 );
    m_kernel.addInstruction( l_ins );
  }
  

  // restore according to procedure call standard
  m_kernel.addInstruction( 0x6CC13FEE );
  m_kernel.addInstruction( 0x6CC137EC );
  m_kernel.addInstruction( 0x6CC12FEA );
  m_kernel.addInstruction( 0x6CC127E8 );

  m_kernel.addInstruction( 0xA8C17BFD );
  m_kernel.addInstruction( 0xA8C173FB );
  m_kernel.addInstruction( 0xA8C16BF9 );
  m_kernel.addInstruction( 0xA8C163F7 );
  m_kernel.addInstruction( 0xA8C15BF5 );
  m_kernel.addInstruction( 0xA8C153F3 );

  // ret
  l_ins = instructions::Base::bRet();
  m_kernel.addInstruction( l_ins );

  // we might debug through file-io
  std::string l_file = "triad.bin";
  m_kernel.write( l_file.c_str() );

  m_kernel.setKernel();

  return (void (*)( float const *, float const *, float * )) m_kernel.getKernel();
}
