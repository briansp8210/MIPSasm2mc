# MIPSasm2mc

MIPSasm2mc is a converter from **MIPS** assembly language to corresponding machine code.  
This is inspired by my computer organization course, so the supported instructions will be those appearing in the Lab for now.  
Following example demonstrates its function :

#### Input assembly code :
```assembly
    add  $t0, $zero, $zero
    addi $t1, $zero, 5
    addi $t2, $zero, 0xf7
L1:
    lw   $t2, 0($sp)
    addi $sp, $sp, -4
    addi $t1, $t1, -1
    blt  $t0, $t1, L1

    sll  $r0, $r0, 0
```

#### Output machine code :

```
00000000000000000100000000100000
00100000000010010000000000000101
00100000000010100000000011110111
10001111101010100000000000000000
00100011101111011111111111111100
00100001001010011111111111111111
00011001000010011111111111111100
00000000000000000000000000000000
```

## Usage

```
./MIPSasm2mc input_asm output_mc
```

## Input file format

* Instruction
    * Instruction mnemonic is not case-sensitive
    * Separate from first argument with at least a white space
    * Separate among operands with `,`
* Register
    * Register name is not case-sensitive
    * Support [two naming](https://www.cs.umd.edu/class/sum2003/cmsc311/Notes/Mips/altReg.html) for each register, both should prefixed by `$`
* Immediate value
    * Support decimal, octal (prefixed with `0`) and hexadecimal (prefixed with `0x`)

## Supported instructions

* **R type**
`sll`, `sllv`, `jr`, `mul`, `add`, `sub`, `and`, `or`, `slt`, `sltu`
* **I type**
`beq`, `bnez`, `blt`, `ble`, `addi`, `ori`, `li`, `lw`, `sw`
* **J type**
`j`, `jal`
