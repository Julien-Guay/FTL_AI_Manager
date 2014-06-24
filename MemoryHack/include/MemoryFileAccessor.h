#ifndef MemoryFileAccessor_H
#define MemoryFileAccessor_H
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

class MemoryFileAccessor
{
public:
    MemoryFileAccessor(const DWORD begin,const DWORD end,const string file);
    virtual ~MemoryFileAccessor();

    /** \brief Permet un accès direct à n'importe quel octet de la copie de la mémoire
    /
    /   Retourne l'octet dont l'adresse est address dans la capture mémoire stockée dans file_pointer_
    /
    */
    byte operator[](const DWORD address);
protected:
private:
    DWORD beginning_address_;
    DWORD ending_address_;
    int size_;
    string file_name_;
    ifstream file_stream_;

};

#endif // MemoryFileAccessor_H
