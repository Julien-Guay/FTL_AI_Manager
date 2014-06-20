#ifndef BLOCK_H
#define BLOCK_H
/// \file Block.h

#include <windows.h>
#include MemoryFileAccessor.h

using namespace std
/**\class Block
* \brief Represente une portion de la mémoire
**/
class Block
{
public:
/// Default constructor
    Block(MemoryFileAccessor& file_accessor, DWORD begin, DWORD end);
    virtual ~Block();

/** \brief Renvoie un sous Block
 *
 * Renvoie le sous Block se trouvant à l'indice "indice"
 *
 * \param indice int
 * \return Block à l'indice correspondant
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


    /** \brief Renvoie tous les sous Blocks d'un type donné
     *
     * \param type block_type
     * \return vector<Block>
     *
     */
    vector<Block> getBlocksByType(block_type type) const;

    /** \brief Crée un sous Block
     *
     * Crée un sous Block de type "type" aux adresses de début et de fin spécifiées
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
     * \return Block Block résultant de la fusion des Blocks fournis en paramètres.
     *
     */
    Block operator+(const Block& a, const Block& b);

    /** \brief Extraction d'un Block
     *
     * Extrait et renvoie un Block d'après les adresses spécifiées.
     * Le Block renvoyé peut éventuellement contenir des sous Block si ceux ci existaient dans le Block appelant.
     * Le Block sur lequel est appellé la méthode n'est pas modifié.
     *
     * \param begin DWORD
     * \param end DWORD
     * \return Block
     *
     */
    Block extract(DWORD begin, DWORD end) const;

    /** \brief Extraction d'un block
     *
     * Extrait et renvoie un Block d'après les adresses spécifiées.
     * Le Block renvoyé ne contient aucun sous Block.
     * Le Block sur lequel est appellé la méthode n'est pas modifié.
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
