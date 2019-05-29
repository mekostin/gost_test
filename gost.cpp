#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gost89.h"

gost_ctx ekey;
gost_ctx dkey;

unsigned char	uKey[32]={0};

unsigned char in[32]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
unsigned char out[32]={0};

unsigned char iv_enc[16]={0};
unsigned char iv_dec[16]={0};

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


  memset(iv_enc, 0, sizeof(iv_enc));
  memset(iv_dec, 0, sizeof(iv_dec));

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

  printf("\n\n");
  memset(out, 0, sizeof(out));
  gost_enc_cfb(&ekey, iv_enc, in, out, 2);
  dump("ECRYPTED CFB_1: ", out, sizeof(out));

  gost_enc_cfb(&ekey, iv_enc, in+16, out+16, 2);
  dump("ECRYPTED CFB_2: ", out, sizeof(out));

  memset(in, 0, sizeof(in));
  gost_dec_cfb(&dkey, iv_dec, out, in, sizeof(out)/8);
  dump("DECRYPTED CFB: ", in, sizeof(in));


  return 0;
}
