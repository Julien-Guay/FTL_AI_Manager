#include "Block.h"

Block::Block(DWORD begin, DWORD end, BlockType type):begin_(begin),end_(end),type_(type),size_((long)(end - begin +1)), subblocks_(vector<Block*>())
{
}

Block::~Block()
{
    vector<Block*>::iterator i(subblocks_.begin());
    while(i!=subblocks_.end())
    {
        delete *i;
    }
}

Block& Block::getBlock(int indice) const
{
    return *subblocks_[indice];
}

Block& Block::getBlock(BlockType type, int indice) const
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
long Block::getSize()
{
    return size_;
}
DWORD Block::getBegin()
{
    return begin_;
}
DWORD Block::getEnd()
{
    return end_;
}
Block::BlockType Block::getType()
{
    return type_;
}

//bool Block::BlockType::operator==(const Block::BlockType type){
//}
