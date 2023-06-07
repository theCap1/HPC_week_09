#ifndef MINI_JIT_GENERATORS_TRIAD_H
#define MINI_JIT_GENERATORS_TRIAD_H

#include "../backend/Kernel.h"

namespace mini_jit {
  namespace generators {
    class Triad;
  }
}

class mini_jit::generators::Triad {
  private:
    //! kernel backend
    backend::Kernel m_kernel;
    
  public:
    /**
     * Generated a kernel for the stream triad c = a + 2.0f*b.
     *
     * @param i_nValues number of values (limited to at most 65536*12-1 values).
     *
     * @return function pointer to kernel.
     **/
    void ( *generate( uint64_t i_nValues ) )( float const * i_a,
                                              float const * i_b,
                                              float       * o_c );
};

#endif
