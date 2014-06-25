#ifndef MEMORYACCESSOR_H
#define MEMORYACCESSOR_H
#include<windows.h>

using namespace std;

class MemoryAccessor
{
public:
    MemoryAccessor(const DWORD begin,const DWORD end);
    virtual ~MemoryAccessor();

    /** \brief Permet un acc�s direct � n'importe quel octet de la copie de la m�moire
    /
    /   Retourne l'octet dont l'adresse est address dans la capture m�moire stock�e dans file_pointer_
    /
    */
    virtual byte operator[](const DWORD address)=0;

    int relativeAdress(DWORD address)
    {
        return address-beginning_address_;
    }

    inline int size() const {return size_;};
    inline int beginning_address() const {return beginning_address_;};
    inline int ending_address() const {return ending_address_;};

protected:
private:
    DWORD beginning_address_;
    DWORD ending_address_;
    int size_;
};

#endif // MEMORYACCESSOR_H
