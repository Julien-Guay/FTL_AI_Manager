#ifndef MEMORYARRAYACCESSOR_H
#define MEMORYARRAYACCESSOR_H

#include <MemoryAccessor.h>
#include <iostream>
#include <assert.h>

using namespace std;

class MemoryArrayAccessor : public MemoryAccessor
{
    public:
        MemoryArrayAccessor(const DWORD begin,const DWORD end);
        virtual ~MemoryArrayAccessor();
    protected:
    private:
        byte* memory_array_;
        byte operator[](const DWORD address);
};

#endif // MEMORYARRAYACCESSOR_H
