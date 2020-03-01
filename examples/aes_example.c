#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <openssl/aes.h>

void HexCode(unsigned char* data, int len)
{
	int i = 0;
	for(; i < len; i++)
		printf("%02x", (unsigned int)data[i]);
	printf("\n\n");
}

int main()
{
	AES_KEY k;

	unsigned char key[32] 	= "abf6ebc59bce34e02d676340bb9e8936";
	unsigned char iv[16] 	= "9bce34e02d676340";
	unsigned char text[] 	= "/data/input/1.jpg";
	
	int size = sizeof(text) - 1;
	size = (size < 16) ? size + (16 - (size % 16)) + 16 : size + (16 - (size % 16));
	
	unsigned char *data = malloc(size);
	memset((void*)data, 0, size);
	strcpy(data, text);

	unsigned char *cipher = malloc(size);
	memset((void*)cipher, 0, size);

	AES_set_encrypt_key(key, 256, &k);
	AES_cbc_encrypt(data, cipher, size, &k, iv, AES_ENCRYPT);

	printf("aes cbc 128 zeropadding hex:\n");
	HexCode(cipher, size);

	free(data);
	free(cipher);

	return 0;
}

