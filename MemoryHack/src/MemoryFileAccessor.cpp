#include "MemoryFileAccessor.h"


MemoryFileAccessor::~MemoryFileAccessor()
{
    remove(file_name_.c_str());
}

MemoryFileAccessor::MemoryFileAccessor(const int begin,const int end,const string& name):beginning_address_(begin),ending_address_(end),size_(end-begin),file_name_(name)
{
}

void MemoryFileAccessor::copyMemoryInFile()
{
    byte value = 0;
    DWORD pid;
    HWND hwnd;
    hwnd = FindWindow(NULL,"FTL");//Rentré en dur comme un gros porc
    ofstream file(file_name_, ios::out | ios::trunc | ios::binary);  //On ouvre le fichier en écriture
    if(!hwnd)
    {
        cout<<"La fenêtre n'a pas été trouvée"<<endl;
        exit(1);//Dans l'idéal il faudrait lancer une exception
    }
    if(!file)//Si le fichier ne s'est pas bien ouvert
    {
        cout<<"Le fichier ne s'est pas ouvert correctement"<<endl;
        exit(2);//Dans l'idéal il faudrait lancer une exception
    }
    GetWindowThreadProcessId(hwnd,&pid);
    HANDLE phandle = OpenProcess(PROCESS_QUERY_INFORMATION,0,pid);
    if(!phandle)
    {
        cout<<"Impossible d'obtenir la poignée (handle)"<<endl;
        exit(3);//Dans l'idéal il faudrait lancer une exception
    }
    for(DWORD address=beginning_address_; address<=ending_address_; address++)
    {
        ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0);
        file.write((char*)&value, sizeof(byte));
    }
    CloseHandle(phandle);
    file.close();
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
    file.seekg(address-this->beginning_address_);
    file.read((char*)&value, sizeof(byte));
    file.close();
    return value;
}

DWORD MemoryFileAccessor::getMaxAdress()
{
    DWORD pid, psize;
    PROCESS_MEMORY_COUNTERS counters;
    HWND hwnd;
    hwnd = FindWindow(NULL,"Démineur");
    if(!hwnd)
    {
        cout <<"Window not found!\n";
        exit(1);
    }
    GetWindowThreadProcessId(hwnd,&pid);
    HANDLE phandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,0,pid);
    if(!phandle)
    {
        cout <<"Could not get handle!\n";
        exit(1);
    }
    if(!GetProcessMemoryInfo(phandle,&counters, sizeof(counters)))
    {
        cout <<"Erreur : getProcessMemoryInfo\n";
        exit(1);
    }
    psize = counters.PagefileUsage;
    return psize;
}
