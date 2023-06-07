#ifndef MINI_JIT_GENERATORS_MYEXAMPLE_H
#define MINI_JIT_GENERATORS_MYEXAMPLE_H

#include "../backend/Kernel.h"
#include "../instructions/Base.h"

namespace mini_jit {
  namespace generators {
    class myExample;
  }
}

class mini_jit::generators::myExample {
  private:
    //! kernel backend
    backend::Kernel m_kernel;
    
  public:
    /**
     * Generates a kernel of myExample which loads a value from an address to a register.
     *
     * @return function pointer to kernel.
     **/
    uint32_t ( *generate() )();
};

#endif