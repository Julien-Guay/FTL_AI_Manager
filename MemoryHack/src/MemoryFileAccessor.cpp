#include "MemoryFileAccessor.h"

MemoryFileAccessor::MemoryFileAccessor(const DWORD begin,const DWORD end,const string file):MemoryAccessor(begin,end),file_name_(file),file_stream_(file_name_,ios::in | ios::binary)
{

}

MemoryFileAccessor::~MemoryFileAccessor()
{
    file_stream_.close();
    remove(file_name_.c_str());
}

byte MemoryFileAccessor::operator[](const DWORD address)
{
    byte value=0;
    ifstream file(file_name_, ios::in| ios::binary);
    if(!file)
    {
        cout<<"Le fichier ne s'est pas ouvert correctement"<<endl;
        exit(2);//Dans l'idéal il faudrait lancer une exception
    }
    file.seekg(relativeAdress(address));
    file.read((char*)&value, sizeof(byte));
    file.close();
    return value;
}
