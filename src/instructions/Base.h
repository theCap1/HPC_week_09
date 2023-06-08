#ifndef MINI_JIT_INSTRUCTIONS_BASE_H
#define MINI_JIT_INSTRUCTIONS_BASE_H

#include <cstdint>

namespace mini_jit {
  namespace instructions {
    class Base;
  }
}

class mini_jit::instructions::Base {
  public:
    //! shift type
    enum shift_t: char {
      lsl = 0,
      lsr = 1,
      asr = 3,
    };


    /**
     * Gets the machine code for the no operation instruction.
     *
     * @return nop instruction.
     **/
    static uint32_t nop();

    /**
     * Gets the machine code for the return instruction.
     * 
     * @return return instruction.
     **/ 
    static uint32_t bRet();

     /**
      * Gets the machine code for compare and branch on nonzero.
      *
      * @param i_regGp general purpose register which is compared.
      * @param i_imm19 value of the 19-bit immediate.
      * @param i_size 32-bit version if 0, 64-bit version if 1.
      *
      * @return instruction.
      **/
    static uint32_t bCbnz( uint8_t i_regGp,
                           int32_t i_imm19,
                           uint8_t i_size );

    /**
     * Gets the machine code for a move.
     *
     * @param i_regGp general purpose register which is set.
     * @param i_imm16 value of the 16-bit immediate.
     * @param i_size 32-bit version if 0, 64-bit version if 1.
     *
     * @return instruction.
     **/
    static uint32_t dpMovImm( uint8_t  i_regGp,
                              uint16_t i_imm16,
                              uint8_t  i_size );

    /**
     * Gets the machine code for add immediate.
     *
     * @param i_regGpDes general purpose destination register.
     * @param i_regGpSrc general purpose source register.
     * @param i_imm12 value of the 12-bit immediate.
     * @param i_size 32-bit version if 0, 64-bit version if 1.
     *
     * @return instruction.
     **/
    static uint32_t dpAddImm( uint8_t  i_regGpDes,
                              uint8_t  i_regGpSrc,
                              uint16_t i_imm12,
                              uint8_t  i_size );

    /**
     * Gets the machine code for add shifted register.
     *
     * @param i_regGpDes general purpose destination register.
     * @param i_regGpSrc0 first general purpose source register.
     * @param i_regGpSrc1 second general purpose source register.
     * @param i_imm6 amount of the shift type of the shift.
     * @param i_shift type of the shift.
     * @param i_size 32-bit version if 0, 64-bit version if 1.
     *
     * @return instruction.
     **/
    static uint32_t dpAddSr( uint8_t i_regGpDes,
                             uint8_t i_regGpSrc0,
                             uint8_t i_regGpSrc1,
                             uint8_t i_imm6,
                             shift_t i_shift,
                             uint8_t i_size );

    /**
     * Gets the machine code for sub immediate.
     *
     * @param i_regGpDes general purpose destination register.
     * @param i_regGpSrc general purpose source register.
     * @param i_imm12 value of the 12-bit immediate.
     * @param i_size 32-bit version if 0, 64-bit version if 1.
     *
     * @return instruction.
     **/
    static uint32_t dpSubImm( uint8_t  i_regGpDes,
                              uint8_t  i_regGpSrc,
                              uint16_t i_imm12,
                              uint8_t  i_size );

    /**
     * Gets the machine code for ldr immediate.
     *
     * @param i_regGpDes general purpose destination register.
     * @param i_regGpSrc general purpose register with address to memory.
     * @param i_prePost pre or post immediate -> 1 = pre, 0 = post
     * @param i_imm9 value of the 12-bit immediate.
     * @param i_size 32-bit version if 0, 64-bit version if 1.
     *
     * @return instruction.
     **/
    static uint32_t dpLdrImm( uint8_t   i_regGpDes,
                              uint8_t   i_regGpAdr,
                              uint8_t   i_prePost,
                              uint16_t  i_imm9,
                              uint8_t   i_size );
};

#endif
