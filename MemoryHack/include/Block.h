#ifndef BLOCK_H
#define BLOCK_H
/// \file Block.h

#include <windows.h>
#include MemoryFileAccessor.h

using namespace std
/**\class Block
* \brief Represente une portion de la m�moire
**/
class Block
{
public:
/// Default constructor
    Block(MemoryFileAccessor& file_accessor, DWORD begin, DWORD end);
    virtual ~Block();

/** \brief Renvoie un sous Block
 *
 * Renvoie le sous Block se trouvant � l'indice "indice"
 *
 * \param indice int
 * \return Block � l'indice correspondant
 *
 */
    Block getBlock(int indice) const;

    /** \brief Renvoie un sous Block
     *
     * Renvoie le ieme block de type correspondant
     *
     * \param type block_type
     * \param indice int
     * \return Block
     *
     */
    Block getBlock(block_type type, int indice) const;


    /** \brief Renvoie tous les sous Blocks d'un type donn�
     *
     * \param type block_type
     * \return vector<Block>
     *
     */
    vector<Block> getBlocksByType(block_type type) const;

    /** \brief Cr�e un sous Block
     *
     * Cr�e un sous Block de type "type" aux adresses de d�but et de fin sp�cifi�es
     *
     * \param begin DWORD
     * \param end DWORD
     * \param type block_type
     * \return void
     *
     */
    void setSubBlock(DWORD begin, DWORD end, block_type type);

    /** \brief Fusion de deux Block
     *
     * \param a const Block&
     * \param b const Block&
     * \return Block Block r�sultant de la fusion des Blocks fournis en param�tres.
     *
     */
    Block operator+(const Block& a, const Block& b);

    /** \brief Extraction d'un Block
     *
     * Extrait et renvoie un Block d'apr�s les adresses sp�cifi�es.
     * Le Block renvoy� peut �ventuellement contenir des sous Block si ceux ci existaient dans le Block appelant.
     * Le Block sur lequel est appell� la m�thode n'est pas modifi�.
     *
     * \param begin DWORD
     * \param end DWORD
     * \return Block
     *
     */
    Block extract(DWORD begin, DWORD end) const;

    /** \brief Extraction d'un block
     *
     * Extrait et renvoie un Block d'apr�s les adresses sp�cifi�es.
     * Le Block renvoy� ne contient aucun sous Block.
     * Le Block sur lequel est appell� la m�thode n'est pas modifi�.
     *
     * \param begin DWORD
     * \param end DWORD
     * \return Block
     *
     */
    Block extractAndClean(DWORD begin, DWORD end) const;

protected:
    const long size_;
    const DWORD begin_;
    const DWORD end_;
    MemoryFileAccessor& file_accessor_
    enum block_type {TYPE1,
                    TYPE2
                   };
private:
};

#endif // BLOCK_H
