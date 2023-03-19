//
// Created by moise on 19.03.2023.
//

#ifndef IPKCPC_COMMON_H
#define IPKCPC_COMMON_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3
#define AF_INET 2

#define bzero(b, len) (memset((b), '\0', (len)), (void) 0)
#endif

#endif// IPKCPC_COMMON_H
