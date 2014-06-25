#ifndef BLOCK_H
#define BLOCK_H
/// \file Block.h

#include <vector>
#include <windows.h>
#include <memory>
#include <MemoryAccessor.h>

using namespace std;

/**\class Block
* \brief Represente une portion de la m�moire
**/
template<typename T> class Block
{

public:
    enum class BlockType
    {
        TYPE1,
        TYPE2
    };
    Block(DWORD begin, DWORD end, BlockType type, T mem_access);
    virtual ~Block();


    /** \brief Renvoie un sous Block
     *
     * Renvoie le sous Block se trouvant � l'indice "indice"
     *
     * \param indice int
     * \return Block � l'indice correspondant
     *
     */
    Block& getBlock(int indice) const;

    /** \brief Renvoie un sous Block
     *
     * Renvoie le ieme block de type correspondant
     *
     * \param type BlockType
     * \param indice int
     * \return Block
     *
     */
    Block& getBlock(Block::BlockType type, int indice) const;


    /** \brief Renvoie tous les sous Blocks d'un type donn�
     *
     * \param type BlockType
     * \return vector<Block>
     *
     */
    vector<Block<T>> getBlocksByType(BlockType type) const;

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
    void setSubBlock(DWORD begin, DWORD end, BlockType type);

    /** \brief Fusion de deux Block
     *
     * \param b const Block&
     * \return Block Block r�sultant de la fusion des Blocks fournis en param�tres.
     *
     */
    Block* operator+(const Block& b);

    /** \brief Extraction d'un Block
     *
     * Extrait et renvoie un nouveau Block d'apr�s les adresses sp�cifi�es.
     * Le Block renvoy� peut �ventuellement contenir des sous Block si ceux ci existaient dans le Block appelant.
     * Le Block sur lequel est appell� la m�thode n'est pas modifi�.
     *
     * \param begin DWORD
     * \param end DWORD
     * \return Block Le Block extrait
     *
     */
    Block* extract(DWORD begin, DWORD end) const;

    /** \brief Extraction d'un block
     *
     * Extrait et renvoie un nouveau Block d'apr�s les adresses sp�cifi�es.
     * Le Block renvoy� ne contient aucun sous Block.
     * Le Block sur lequel est appell� la m�thode n'est pas modifi�.
     *
     * \param begin DWORD
     * \param end DWORD
     * \return Block Le Block extrait
     *
     */
    Block* extractAndClean(DWORD begin, DWORD end) const;

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
    T mem_accessor_;
    vector<Block<T>*> subblocks_;
};

#endif // BLOCK_H
