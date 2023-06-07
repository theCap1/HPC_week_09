#include "myExample.h"

uint32_t ( *mini_jit::generators::myExample::generate() )() {
  uint32_t l_ins = 0;

  // mov w0, #0x3
  l_ins = instructions::Base::dpLdrImm( 1,
                                        0,
                                        0,  // 1 = pre, 0 = post
                                        8,
                                        1);
  m_kernel.addInstruction( l_ins );

  // ret
  l_ins = instructions::Base::bRet();
  m_kernel.addInstruction( l_ins );


  // we might debug through file-io
  std::string l_file = "myExample.bin";
  m_kernel.write( l_file.c_str() );

  m_kernel.setKernel();

  return (uint32_t (*)()) m_kernel.getKernel();
}