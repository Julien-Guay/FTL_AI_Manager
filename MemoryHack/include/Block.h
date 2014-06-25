#ifndef BLOCK_H
#define BLOCK_H
/// \file Block.h

#include <vector>
#include <windows.h>
#include <memory>
#include <MemoryAccessor.h>

#include <MemoryAccessor.h>

using namespace std;

/**\class Block
* \brief Represente une portion de la mémoire
**/
template<typename T>
class Block
{

public:
    enum class BlockType
    {
        TYPEVOID,
        TYPE1,
        TYPE2
    };

    Block(DWORD begin, DWORD end, BlockType type, shared_ptr<T> mem_accessor);
    virtual ~Block();


    /** \brief Renvoie un sous Block
     *
     * Renvoie le sous Block se trouvant à l'indice "indice"
     *
     * \param indice int
     * \return Block& à l'indice correspondant
     *
     */
    Block& getBlock(int indice) const;

    /** \brief Renvoie un sous Block
     *
     * Renvoie le ieme block de type correspondant
     *
     * \param type BlockType
     * \param indice int
     * \return Block&
     *
     */
    Block& getBlock(Block::BlockType type, int indice) const;


    /** \brief Renvoie tous les sous Blocks d'un type donné
     *
     * \param type BlockType
     * \return vector< const Block*>*
     *
     */
    vector<const Block<T>*>* getBlocksByType(BlockType type) const;

    /** \brief Crée un sous Block
     *
     * Crée un sous Block de type "type" aux adresses de début et de fin spécifiées
     *
     * \param begin DWORD
     * \param end DWORD
     * \param type BlockType
     * \return void
     *
     */
    void setSubBlock(DWORD begin, DWORD end, BlockType type);

//    /** \brief Fusion de deux Block
//     *
//     * \param b const Block&
//     * \return Block Block résultant de la fusion des Blocks fournis en paramètres.
//     *
//     */
//    virtual Block* operator+(const Block& b) = 0;

//    /** \brief Extraction d'un Block
//     *
//     * Extrait et renvoie un nouveau Block d'après les adresses spécifiées.
//     * Le Block renvoyé peut éventuellement contenir des sous Block si ceux ci existaient dans le Block appelant.
//     * Le Block sur lequel est appellé la méthode n'est pas modifié.
//     *
//     * \param begin DWORD
//     * \param end DWORD
//     * \return Block Le Block extrait
//     *
//     */
//     Block* extract(DWORD begin, DWORD end) const;

//    /** \brief Extraction d'un block
//     *
//     * Extrait et renvoie un nouveau Block d'après les adresses spécifiées.
//     * Le Block renvoyé ne contient aucun sous Block.
//     * Le Block sur lequel est appellé la méthode n'est pas modifié.
//     *
//     * \param begin DWORD
//     * \param end DWORD
//     * \return Block Le Block extrait
//     *
//     */
//    virtual Block* extractAndClean(DWORD begin, DWORD end) const = 0;

    //Getter
    long getSize();
    DWORD getBegin();
    DWORD getEnd();
    BlockType getType();

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
