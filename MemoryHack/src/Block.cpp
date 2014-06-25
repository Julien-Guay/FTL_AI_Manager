#include "Block.h"
template <typename T>
Block<T>::Block(DWORD begin, DWORD end, BlockType type, shared_ptr<T> mem_accessor)
    :begin_(begin),end_(end),type_(type),size_((long)(end - begin +1)), subblocks_(vector<Block*>()), mem_accessor_(mem_accessor)
{
}

template <typename T>
Block<T>::~Block()
{
    typename vector<Block*>::iterator i(subblocks_.begin());
    while(i!=subblocks_.end())
    {
        delete *i;
    }
}

template <typename T>
Block<T>& Block<T>::getBlock(int indice) const
{
    return *subblocks_[indice];
}


template <typename T>
Block<T>& Block<T>::getBlock(BlockType type, int indice) const
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

template <typename T>
vector<const Block<T>*>* Block<T>::getBlocksByType(BlockType type) const
{
    vector<const Block*>* blocks_by_type = new vector<const Block*>();
    typename vector<Block*>::const_iterator subblock( subblocks_.cbegin());

    while(subblock != subblocks_.end())
    {
        if((*subblock)->getType() == type)
        {
            blocks_by_type->push_back(*subblock);
        }
        subblock++;
    }
    return blocks_by_type;
}

//TODO Voir comment définir les types des blocks encadrants
template <typename T>
void Block<T>::setSubBlock(DWORD begin, DWORD end, BlockType type)
{
    //Si il ne contient aucun sousblock, il faut créer les nouveaux sousblock
    if(subblocks_.size() == 0 )
    {
        if(begin != begin_)
        {
            subblocks_.push_back(new Block(begin_, begin, BlockType::TYPEVOID, mem_accessor_));//TODO Définir le type de block
        }
        subblocks_.push_back(new Block(begin, end, type, mem_accessor_));
        if(end !=end_)
        {
            subblocks_.push_back(new Block(end, end_, BlockType::TYPEVOID, mem_accessor_));//TODO Définir le type de block
        }
    }
    else//sinon il faut rechercher le sousblock qui va être découpé
    {
        typename vector<Block*>::iterator subblock( subblocks_.begin());
        while((*subblock)->getBegin()> begin || subblock == subblocks_.end())
        {
            subblock++;
        }
        if((*subblock)->getEnd()<end){
            //Cas d'erreur : découpe entre deux sousblocks
            exit(1);
        }
        (*subblock)->setSubBlock(begin, end, type);
    }
}
//    Block* operator+(const Block& b){
//    }
//template <class T>
//    Block<T>* Block<T>::extract(DWORD begin, DWORD end) const{
//    }

//    Block* extractAndClean(DWORD begin, DWORD end) const{
//    }

/*-------------
----GETTERS----
-------------*/
template <typename T>
long Block<T>::getSize()
{
    return size_;
}

template <typename T>
DWORD Block<T>::getBegin()
{
    return begin_;
}

template <typename T>
DWORD Block<T>::getEnd()
{
    return end_;
}

template <typename T>
typename Block<T>::BlockType Block<T>::getType()
{
    return type_;
}
