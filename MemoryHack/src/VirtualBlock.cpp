#include "VirtualBlock.h"

VirtualBlock::VirtualBlock(DWORD begin, DWORD end, BlockType type, shared_ptr<MemoryFileAccessor> file_accessor):Block(begin, end, type),file_accessor_(file_accessor)
{
    //ctor
}

VirtualBlock::~VirtualBlock()
{
    //dtor
}
