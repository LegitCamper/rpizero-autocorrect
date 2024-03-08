#include "autocorrect/auto_correct.h"

#include "debug.h"
#include "read.h"
#include "write.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

extern int __bss_start__;
extern int __bss_end__;

#define N 26

extern void blink_words(struct TrieNode *root, char *word) {
  struct TrieNode temp = *root;
  for (int i = 0; i < N; ++i) {
    if (temp.children[i] != 0) {
      char *new_word = malloc(strlen(word) + 2);
      strcpy(new_word, word);
      new_word[strlen(word)] = 'a' + i;
      new_word[strlen(word) + 1] = '\0';
      blink_words(temp.children[i], new_word);

      if (temp.children[i]->is_leaf == 1) {
        int l = strlen(word);
        for (int i = 0; i < l; i++) {
          int blink_interval = 1500000 / strlen(word);
          blink_act(strlen(word), blink_interval);
        }
      }
    }
  }
}

extern void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags) {
  while (1) { // can never exit
    blink_words(&TRIE_ROOT, "");
    // blink_act(1, 500000);
  }
}

void _cstartup(unsigned int r0, unsigned int r1, unsigned int r2) {
  /*__bss_start__ and __bss_end__ are defined in the linker script */
  int *bss = &__bss_start__;
  int *bss_end = &__bss_end__;

  /*
      Clear the BSS section

      See http://en.wikipedia.org/wiki/.bss for further information on the
          BSS section

      See https://sourceware.org/newlib/libc.html#Stubs for further
          information on the c-library stubs
  */
  while (bss < bss_end)
    *bss++ = 0;

  /* We should never return from main ... */
  kernel_main(r0, r1, r2);

  /* ... but if we do, safely trap here */
  while (1) {
    /* EMPTY! */
  }
}
