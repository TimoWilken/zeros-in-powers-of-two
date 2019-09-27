#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
// compile with gcc zeros.c -lgmp
#include <gmp.h>

const unsigned long int ZEROS_IN_BASE = 10ul;
unsigned char exit_signalled = 0;


void handle_signal(const int signo) {
  exit_signalled = signo == SIGINT;
}


int main(const int argc, const char * const * const argv) {
  if (signal(SIGINT, handle_signal) == SIG_ERR) {
    dprintf(2, "%s: can't trap SIGINT\n", argv[0]);
    return 2;
  }

  unsigned long int exponent = 30739014ul, remainder, zero_place;
  mpz_t power_of_2;
  mpz_init(power_of_2);

  if (argc > 1) {
    exponent = atol(argv[1]);
  }

  for (; ; exponent++) {
    mpz_ui_pow_ui(power_of_2, 2ul, exponent);
    printf("2^%ld: ", exponent);

    for (zero_place = 0; mpz_sgn(power_of_2) /* != 0 */; zero_place++) {
      remainder = mpz_tdiv_q_ui(power_of_2, power_of_2, ZEROS_IN_BASE);
      // NOTE: prints power_of_2 to the least significant zero in reverse order.
      putchar('0' + remainder);
      if (!remainder) {
        puts("...");
        break;
      }

      if (exit_signalled) {
        dprintf(2, "%s: caught SIGINT, got to 2^%ld\n", argv[0], exponent - 1);
        mpz_clear(power_of_2);
        return 0;
      }
    }

    if (remainder) {
      dprintf(2, "2^%ld contains no zeros!\n", exponent);
    }
  }
}
