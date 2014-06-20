#include "Block.h"

Block::Block(DWORD begin, DWORD end, BlockType type):begin_(begin),end_(end),type_(type),size_((long)(end - begin +1)), subblocks_(vector<Block*>())
{
}

Block::~Block()
{
    vector<Block*>::iterator i(subblocks_.begin());
    while(i!=subblocks_.end()){
        delete *i;
    }
}

Block& Block::getBlock(int indice) const{
    return *subblocks_[indice];
}

Block& Block::getBlock(Block::BlockType type, int indice) const{
    int count = 0;

    for(auto it(subblocks_.begin()) ; it != subblocks_.end() ; it++)
    {
        //Erreur de compil
        if((*it)->getType == type){
            if(count == indice)
                return **it;
            else
                count++;
        }
    }
}
//    vector<Block> getBlocksByType(BlockType type) const{
//    }
//    void setSubBlock(DWORD begin, DWORD end, BlockType type){
//    }
//    Block* operator+(const Block& b){
//    }
//    Block* extract(DWORD begin, DWORD end) const{
//    }
//    Block* extractAndClean(DWORD begin, DWORD end) const{
//    }
    long Block::getSize(){
        return size_;
    }
    DWORD Block::getBegin(){
        return begin_;
    }
    DWORD Block::getEnd(){
        return end_;
    }
    Block::BlockType Block::getType(){
        return type_;
    }
