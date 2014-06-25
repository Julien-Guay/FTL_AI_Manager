#include "Block.h"

template<typename T> Block<T>::Block(DWORD begin, DWORD end, BlockType type, T mem_access):begin_(begin),end_(end),type_(type), mem_accessor_(mem_access), size_((long)(end - begin +1)), subblocks_(vector<Block*>())
{
}

template<typename T> Block<T>::~Block()
{
    typename vector<Block<T>*>::iterator i(subblocks_.begin());
    while(i!=subblocks_.end())
    {
        delete *i;
    }
}

template<typename T> Block<T>& Block<T>::getBlock(int indice) const
{
    return *subblocks_[indice];
}

template<typename T> Block<T>& Block<T>::getBlock(Block::BlockType type, int indice) const
{
    int count = 0;

    for(auto it(subblocks_.begin()) ; it != subblocks_.end() ; it++)
    {
        if((*it)->getType() == type)
        {
            if(count == indice)
                return **it;
            else
                count++;
        }
    }
    //TODO Implémenter la gestion des erreurs
}

vector<const Block*>* Block::getBlocksByType(BlockType type) const
{
    vector<const Block*>* blocks_by_type = new vector<const Block*>();
    vector<Block*>::const_iterator subblock( subblocks_.begin());

    while(subblock != subblocks_.end())
    {
        if((*subblock)->getType() == type)
        {
            blocks_by_type->push_back(*subblock);
        }
    }
    return blocks_by_type;
}

//    void Block::setSubBlock(DWORD begin, DWORD end, BlockType type){
//        if(subblocks_.size() == 0 )
//        {
//            subblocks_.push_back(new )
//        }
//    }
//    Block* operator+(const Block& b){
//    }
//    Block* extract(DWORD begin, DWORD end) const{
//    }
//    Block* extractAndClean(DWORD begin, DWORD end) const{
//    }
template<typename T> long Block<T>::getSize()
{
    return size_;
}
template<typename T> DWORD Block<T>::getBegin()
{
    return begin_;
}
template<typename T> DWORD Block<T>::getEnd()
{
    return end_;
}
template<typename T> typename Block<T>::BlockType Block<T>::getType()
{
    return type_;
}
