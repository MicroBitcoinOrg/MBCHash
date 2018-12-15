// Copyright (c) 2018 iamstenman
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "crypto/sph/sph_groestl.h"
#include "crypto/kupyna/kupyna512.h"
#include "mirinae.h"
#include <memory.h>

void mirinae(const void* data, size_t length, void* output, int height, const void* seed)
{	
	unsigned char hash[64] = { 0 };
	unsigned char offset[64] = { 0 };
	const int window = 4096;
	int64_t n = 0;

	sph_groestl512_context ctx_groestl;
	struct kupyna512_ctx_t ctx_kupyna;

	kupyna512_init(&ctx_kupyna);
	kupyna512_update(&ctx_kupyna, seed, 32);
	kupyna512_final(&ctx_kupyna, offset);
	
	memcpy(&n, offset, 8);
	unsigned int iterations = (((n % height) + (height + 1)) % window);

	sph_groestl512_init(&ctx_groestl);
	sph_groestl512(&ctx_groestl, data, length);
	sph_groestl512_close(&ctx_groestl, hash);

	for (int i = 0; i < iterations; i++) {
		for (int j = 0; j < hash[0]; j++) {
			kupyna512_init(&ctx_kupyna);
			kupyna512_update(&ctx_kupyna, hash, 64);
			kupyna512_final(&ctx_kupyna, hash);
		}
	}

	sph_groestl512_init(&ctx_groestl);
	sph_groestl512(&ctx_groestl, hash, 64);
	sph_groestl512_close(&ctx_groestl, hash);

	memcpy(output, hash, 32);
}
