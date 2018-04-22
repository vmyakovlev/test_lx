#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <deque>
#include <vector>
#include <stdint.h>
#include <unordered_map>

typedef std::vector<uint8_t> _telement;
typedef std::deque<_telement*> _tblocks;

typedef std::unordered_map<size_t,std::vector<size_t>> _tcrcs_per_block;

#endif // TYPEDEFS_H
