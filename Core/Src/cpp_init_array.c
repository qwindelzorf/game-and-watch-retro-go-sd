#include <stdint.h>
#include <stdio.h>
#include "cpp_init_array.h"

/* C++ constructors */
// C++ projects are usually using __libc_init_array() to call constructors
// but this function is not working with the overlay
// so we need to call constructors manually
// Call to __libc_init_array is still done in startup_stm32h7b0xx.s to initialize
// constuctors if needed by the main application (which is currently not the case)
void cpp_init_array(void (**start)(void), void (**end)(void)) {
    while (start < end) {
        (*start++)();
    }
}