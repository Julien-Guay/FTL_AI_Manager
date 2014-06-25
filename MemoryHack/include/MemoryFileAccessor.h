#ifndef MemoryFileAccessor_H
#define MemoryFileAccessor_H
#include <windows.h>
#include <iostream>
#include <fstream>
#include <MemoryAccessor.h>

using namespace std;

class MemoryFileAccessor : public MemoryAccessor
{
public:
    MemoryFileAccessor(const DWORD begin,const DWORD end,const string file);
    virtual ~MemoryFileAccessor();

    /** \brief Permet un acc�s direct � n'importe quel octet de la copie de la m�moire
    /
    /   Retourne l'octet dont l'adresse est address dans la capture m�moire stock�e dans file_pointer_
    /
    */
    byte operator[](const DWORD address);
protected:
private:
    string file_name_;
    ifstream file_stream_;

};

#endif // MemoryFileAccessor_H
