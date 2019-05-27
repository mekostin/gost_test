#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gost89.h"

gost_ctx ekey;
gost_ctx dkey;

unsigned char	uKey[32]={0};

unsigned char in[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
unsigned char out[16]={0};

void dump(const char *caption, unsigned char *buffer, int size) {
  printf("%s\n", caption);
  for (int i=0; i<size; i++) {
    printf("%02X ", buffer[i]);
  }
  printf("\n");
}

int main() {
  scanf("%32s", uKey);
  dump("KEY: ", uKey, 32);

  gost_init(&ekey, &GostR3411_94_TestParamSet);
  gost_key(&ekey, uKey);

  gost_init(&dkey, &GostR3411_94_TestParamSet);
  gost_key(&dkey, uKey);

  dump("MSG: ", in, sizeof(in));

  memset(out, 0, sizeof(out));
  gost_enc(&ekey, in, out, sizeof(in)/8);

  dump("ECRYPTED: ", out, sizeof(out));

  memset(in, 0, sizeof(in));
  gost_dec(&dkey, out, in, sizeof(out)/8);
  dump("DECRYPTED: ", in, sizeof(in));

  return 0;
}
