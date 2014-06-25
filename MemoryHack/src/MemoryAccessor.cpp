#include "MemoryAccessor.h"

MemoryAccessor::MemoryAccessor(const DWORD begin,const DWORD end):beginning_address_(begin),ending_address_(end),size_(end-begin+1)
{

}

MemoryAccessor::~MemoryAccessor()
{

}
