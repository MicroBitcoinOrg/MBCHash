// Copyright (c) 2018 iamstenman
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MBCHASH_H
#define MBCHASH_H

#ifdef __cplusplus
extern "C" {
#endif

void mirinae(const void* data, size_t length, void* output, int height, const void* seed);

#ifdef __cplusplus
}
#endif

#endif
