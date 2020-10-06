#=========================================================================
# crt0.S : Entry point for RISC-V user programs
#=========================================================================

  .text
  .global _start
  .type   _start, @function
_start:
  .weak   _stack
  # Initialize stack pointer (if defined)
  lla     a0, _stack
  beqz    a0, 1f
  mv      sp, a0

  # Initialize global pointer
.option push
.option norelax
1:auipc gp, %pcrel_hi(__global_pointer$)
  addi  gp, gp, %pcrel_lo(1b)
.option pop

#ifdef __nds_v5
.L_init_itb:
  la      a0, _ITB_BASE_
  csrrw   x0, uitb, a0
#endif

  # Set mstatus.fs to 1 (initial)
#ifdef __riscv_flen
  li      a0, (1 << 13)
  csrs    mstatus, a0
#endif

  # Enable unaligned memory access (mmisc_ctl.UNA)
  li      a0, (1 << 6)
  csrs    mmisc_ctl, a0

  # Clear the bss segment
  la      a0, _edata
  la      a2, _end
  sub     a2, a2, a0
  li      a1, 0
  call    memset

  la      a0, __libc_fini_array   # Register global termination functions
  call    atexit                  #  to be called upon exit
  call    __libc_init_array       # Run global initialization functions

  li      a0, 0                      # a0 = argc = 0
  li      a1, 0                      # a1 = argv = NULL
  li      a2, 0                      # a2 = envp = NULL
  call    main
  tail    exit
  .size  _start, .-_start

  .global _init
  .type   _init, @function
  .global _fini
  .type   _fini, @function
_init:
_fini:
  # These don't have to do anything since we use init_array/fini_array.
  ret
  .size  _init, .-_init
  .size  _fini, .-_fini
