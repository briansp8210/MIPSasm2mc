    add  $t0, $zero, $zero
    addi $t1, $zero, 10
    addi $t2, $zero, 13
    mul  $t3, $t1, $t1
    j    Jump
bubble:
    li   $t0, 10
    li   $t1, 4
    mul  $t4, $t0, $t1
outer:
    addi $t6, $t0, 8
    sub  $t0, $t4, $t6
    li   $t1, 0
inner:
    lw   $t2, 4($t0)
    lw   $t3, 0($t0)
    ble  $t2, $t3, no_swap
    sw   $t2, 0($t0)
    sw   $t3, 4($t0)
    li   $t1, 1
no_swap:
    addi $t5, $zero, 4
    sub  $t0, $t0, $t5
    blt  $t0, $zero, next_turn
    j    inner
next_turn:
    bnez $t1, outer
    j    End
Jump:
    sub  $t2, $t2, $t1
Loop:
    add  $t4, $t3, $t2
    beq  $t1, $t2, Loop
    j    bubble
End:
    sll $zero, $zero, 0
