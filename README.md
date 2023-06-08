# HPC_week_9
## Homework for the 9th week

### 10 JITed Kernels in Praxis

#### 10.1 Getting Started

No documentation is given for 10.1.1 and 10.1.2 because they are just a warm up and the neccessary skills are needed to do the in the successive tasks. The completion of the following tasks should be sufficient as proof that 10.1.1 and 10.1.2 were were completed.
As base instruction the `ldr` (immediate) instruction was chosen to be implemented in `instructions/base.cpp` together with the demo class `myExample.cpp` for 10.1.3. The compilation and disassembly returns:

```s
0000000000000000 <.data>:
   0:   f8408401        ldr     x1, [x0], #8
   4:   d65f03c0        ret
```

As relevant bits the following were identified
- 0-4: Destination GP register of load
- 5-9: GP register that stores memory address or stack pointer
- 12-20:  9 bit immediate
- 30:     register size
- 11: Pre-/ Post-Index immediate

#### 10.2 ASIMD: First Steps

The implemented JITing function can be found in `generators/triad.cpp` and the according header. Up to 24 registers are filled with import values at once. The brach condition loops as long through the memory until less then 48 values remain. then smaller load operations are JITed as needed.
To achieve support for more values than 65,536 the we could implement some kind of recursiveness or split the arrays into multiple parts. 