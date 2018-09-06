# A simple Fibonacci function in assembly
# a=0, b=1
#function fibonacci(n) {
 #  if (n < 2){
 #    return 1;
 #  }else{
 #    return fibonacci(n-2) + fibonacci(n-1);
 #  }
#}
# assumes:
#  f is in $s0 and $a1, $a2 has a and b, $s1/$a0 has N
        .text
    .globl  main
main:                       # main has to be a global label
    addu $s7, $0, $ra       # save the return address in a global register

    addi $s0, $0, -1        # initialize $s0 to -1
    addi $a1, $0, 0         # a = 0
    addi $a2, $0, 1         # b = 1

  # Prompt and input the value of N
    .data
    .globl inputNmsg
inputNmsg:  .asciiz  "\nEnter N :"
    .text

    inputLoop:

    li   $v0, 4             # print_str
    la   $a0, inputNmsg     # takes the address of string as an argument
    syscall
    li   $v0, 5             # read_int
    syscall
    blt $v0,2,inputLoop
    bgt $v0, 45, inputLoop
    add  $s1, $0, $v0       # The value of N has been read into $s1
    add  $a0, $0, $s1       # set the parameter to N for fib call
    sub  $a0, $a0, 1
    jal  fib                # Call the fibonacci function
    add  $s0, $0, $v0       # f = fib(N);
  
  #  Output the result
    .data
    .globl  outputMsg
outputMsg:  .asciiz  "\nfib(N) = "
    .text
    li   $v0, 4             # print_str 
    la   $a0, outputMsg     # takes the address of string as an argument 
    syscall                 # output the label
    li   $v0, 1             # print_int
    add  $a0, $0, $s0       # takes integer
    syscall                 # output f

  # Usual stuff at the end of the main
    addu $ra, $0, $s7       # restore the return address
    jr   $ra                # return to the main program
    add  $0, $0, $0         # nop

    .globl  fib            # function named "fib"
fib:
    sub  $sp, $sp, 16        # make space on the stack for four items
    sw   $a1, 12($sp)
    sw   $a2, 8($sp)
    sw   $ra, 4($sp)        # save the return address on the stack 
    sw   $a0, 0($sp)        # save the argument n on the stack 

    slt  $t0, $a0, 1        # test for n &lt; 1
    beq  $t0, $zero, L1     # if (n &gt;= 1) go to L1
    add  $v0, $zero, 1      # otherwise return 1
    add  $sp, $sp, 16        # pop the saved items off stack, no call
    jr   $ra                # and return


    L1:
    sub  $a0, $a0, 1        # when n &gt;= 1:  decrement the argument
    jal  fib                # call fib(n-1)

    lw   $a0, 0($sp)        # restore the value of argument n
    lw   $ra, 4($sp)        # restore the return address

 # lw   $a2, 8($sp)        # restore the return address
 # lw   $a1, 12($sp)        # restore the return address

    add  $sp, $sp, 16        # release the save area on the stack

    #add  $v0, $a0, $v0      # yes it's a add! 
    #bgt $t0, $2, L3
    #blt $t0, $3, L4
    
#L3:
    add $s0, $a1, $a2
    add $a1, $a2, $0
    add $a2, $s0, $0
    add $v0, $s0, $0
#L4:
    jr   $ra                # return
