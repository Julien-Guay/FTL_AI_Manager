#ifndef VIRTUALBLOCK_H
#define VIRTUALBLOCK_H

#include <Block.h>
#include <MemoryFileAccessor.h>

class VirtualBlock : public Block
{
    public:
        /** Default constructor */
    VirtualBlock(DWORD begin, DWORD end, BlockType type, shared_ptr<MemoryFileAccessor> file_accessor);
        /** Default destructor */
        virtual ~VirtualBlock();
        /** Access file_accessor_
         * \return The current value of file_accessor_
         */
        shared_ptr<MemoryFileAccessor> Getfile_accessor_() { return file_accessor_; }
        /** Set file_accessor_
         * \param val New value to set
         */
        void Setfile_accessor_(shared_ptr<MemoryFileAccessor> val) { file_accessor_ = val; }
    protected:
    private:
        shared_ptr<MemoryFileAccessor> file_accessor_; //!< Member variable "file_accessor_"
};

#endif // VIRTUALBLOCK_H
