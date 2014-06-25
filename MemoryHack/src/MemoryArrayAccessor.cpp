#include "MemoryArrayAccessor.h"

MemoryArrayAccessor::MemoryArrayAccessor(const DWORD begin,const DWORD end):MemoryAccessor(begin,end)
{
    memory_array_ = new byte(size());
    assert(memory_array_);
}

MemoryArrayAccessor::~MemoryArrayAccessor()
{
    delete memory_array_;
}

byte MemoryArrayAccessor::operator[](const DWORD address)
{
    return memory_array_[relativeAdress(address)];
}
