#include <stdio.h>
#include <stdbool.h>

/**
 * Checks if a number is even (i.e., divisible by 2) using inline assembly.
 * A more complete primality test would build upon this.
 *
 * @param n The integer to check.
 * @return true if n is even (and not prime, unless n=2), false otherwise.
 */
bool check_even_asm(int n) {
    // Treat n=2 as a special case for this example, as it is prime but even.
    if (n == 2) {
        return false; // 2 is prime
    }
    if (n < 2) {
        return true; // 0, 1 are not prime
    }

    int result; // 0 if odd, non-zero if even (LSB is 0 or 1)

    // GCC/Clang Inline Assembly (AT&T syntax for x86-64)
    __asm__ (
        // 1. Bitwise AND: 'n & 1'
        // 'andl $1, %%eax' performs EAX = EAX & 1
        "andl $1, %1\n\t"

        // 2. Move the result of the AND back to the 'result' variable.
        // We're essentially using %1 as a temporary register that holds 'n',
        // performs the operation, and then is read back into the output operand %0.
        // The 'movl' is often optimized away by the compiler depending on constraints.
        "movl %1, %0"

        // Output Operands:
        // "=r" (result) : 'r' means any general-purpose register.
        //                 The result of the operation will be placed here (operand %0).
        : "=r" (result)

        // Input Operands:
        // "r" (n)       : 'r' means any general-purpose register.
        //                 The value of 'n' is loaded into a register (operand %1).
        : "r" (n)

        // Clobbered Registers (Not strictly necessary for this simple case, but good practice):
        // If an instruction modifies any registers not listed as outputs/inputs,
        // they should be listed here. None are explicitly clobbered here outside of
        // the operands.
        :
    );

    // If the LSB is 1 (result == 1), the number is odd.
    // If the LSB is 0 (result == 0), the number is even.
    return (result == 0);
}

// Simplified 'is_prime' function leveraging the check_even_asm
bool is_prime_simplified(int n) {
    if (n == 2) return true;
    if (n <= 1 || check_even_asm(n)) return false;

    // The *rest* of the primality test would go here (checking for odd divisors up to sqrt(n))
    // This part must be done in C or with a complex assembly loop.

    // For this example, we'll only check 3:
    if (n % 3 == 0) return false;

    // This is *NOT* a complete prime check, it's illustrative.
    return true;
}


int main() {
    printf("Is 10 even (via ASM)? %s\n", check_even_asm(10) ? "Yes" : "No"); // Output: Yes
    printf("Is 7 even (via ASM)? %s\n", check_even_asm(7) ? "Yes" : "No");   // Output: No

    printf("Is 7 prime (simplified)? %s\n", is_prime_simplified(7) ? "Yes" : "No"); // Output: Yes
    printf("Is 97 prime (simplified)? %s\n", is_prime_simplified(97) ? "Yes" : "No"); // Output: Yes
    printf("Is 2147483647 prime (simplified)? %s\n", is_prime_simplified(2147483647) ? "Yes" : "No"); // Output: Yes

    return 0;
}
