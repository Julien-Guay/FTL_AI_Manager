#ifndef BLOCK_H
#define BLOCK_H
/// \file Block.h

#include <vector>
#include <windows.h>
#include <memory>
#include <MemoryAccessor.h>

using namespace std;

enum class BlockType
{
    TYPEVOID,
    TYPE1,
    TYPE2
};

/**\class Block
* \brief Represente une portion de la m�moire
**/
template<typename T>
class Block
{

public:


    Block(DWORD begin, DWORD end, BlockType type, shared_ptr<T> mem_accessor)
        :begin_(begin),end_(end),type_(type),size_((long)(end - begin +1)), subblocks_(vector<Block*>()), mem_accessor_(mem_accessor)
    {

    }
    virtual ~Block()
    {
        typename vector<Block*>::iterator i(subblocks_.begin());
        while(i!=subblocks_.end())
        {
            delete *i;
        }
    }


    /** \brief Renvoie un sous Block
     *
     * Renvoie le sous Block se trouvant � l'indice "indice"
     *
     * \param indice int
     * \return Block& � l'indice correspondant
     *
     */
    Block& getBlock(int indice) const
    {
        return *subblocks_[indice];
    }

    /** \brief Renvoie un sous Block
     *
     * Renvoie le ieme block de type correspondant
     *
     * \param type BlockType
     * \param indice int
     * \return Block&
     *
     */
    Block& getBlock(BlockType type, int indice) const
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
        //TODO Impl�menter la gestion des erreurs
    }


    /** \brief Renvoie tous les sous Blocks d'un type donn�
     *
     * \param type BlockType
     * \return vector< const Block*>*
     *
     */
    vector<const Block<T>*>* getBlocksByType(BlockType type) const
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

    /** \brief Cr�e un sous Block
     *
     * Cr�e un sous Block de type "type" aux adresses de d�but et de fin sp�cifi�es
     *
     * \param begin DWORD
     * \param end DWORD
     * \param type BlockType
     * \return void
     *
     */
    void setSubBlock(DWORD begin, DWORD end, BlockType type)
    {
        //Si il ne contient aucun sousblock, il faut cr�er les nouveaux sousblock
        if(subblocks_.size() == 0 )
        {
            if(begin != begin_)
            {
                subblocks_.push_back(new Block(begin_, begin, BlockType::TYPEVOID, mem_accessor_));//TODO D�finir le type de block
            }
            subblocks_.push_back(new Block(begin, end, type, mem_accessor_));
            if(end !=end_)
            {
                subblocks_.push_back(new Block(end, end_, BlockType::TYPEVOID, mem_accessor_));//TODO D�finir le type de block
            }
        }
        else//sinon il faut rechercher le sousblock qui va �tre d�coup�
        {
            typename vector<Block*>::iterator subblock( subblocks_.begin());
            while((*subblock)->getBegin()> begin || subblock == subblocks_.end())
            {
                subblock++;
            }
            if((*subblock)->getEnd()<end)
            {
                //Cas d'erreur : d�coupe entre deux sousblocks
                exit(1);
            }
            (*subblock)->setSubBlock(begin, end, type);
        }
    }

//    /** \brief Fusion de deux Block
//     *
//     * \param b const Block&
//     * \return Block Block r�sultant de la fusion des Blocks fournis en param�tres.
//     *
//     */
//    virtual Block* operator+(const Block& b) = 0;

//    /** \brief Extraction d'un Block
//     *
//     * Extrait et renvoie un nouveau Block d'apr�s les adresses sp�cifi�es.
//     * Le Block renvoy� peut �ventuellement contenir des sous Block si ceux ci existaient dans le Block appelant.
//     * Le Block sur lequel est appell� la m�thode n'est pas modifi�.
//     *
//     * \param begin DWORD
//     * \param end DWORD
//     * \return Block Le Block extrait
//     *
//     */
//     Block* extract(DWORD begin, DWORD end) const;

//    /** \brief Extraction d'un block
//     *
//     * Extrait et renvoie un nouveau Block d'apr�s les adresses sp�cifi�es.
//     * Le Block renvoy� ne contient aucun sous Block.
//     * Le Block sur lequel est appell� la m�thode n'est pas modifi�.
//     *
//     * \param begin DWORD
//     * \param end DWORD
//     * \return Block Le Block extrait
//     *
//     */
//    virtual Block* extractAndClean(DWORD begin, DWORD end) const = 0;

    //Getter
    long getSize()
    {
        return size_;
    }
    DWORD getBegin()
    {
        return begin_;
    }
    DWORD getEnd()
    {
        return end_;
    }
    BlockType getType()
    {
        return type_;
    }

protected:
private:
    const long size_;
    const DWORD begin_;
    const DWORD end_;
    BlockType type_;
    vector<Block*> subblocks_;
    shared_ptr<MemoryAccessor> mem_accessor_;
};

#endif // BLOCK_H
