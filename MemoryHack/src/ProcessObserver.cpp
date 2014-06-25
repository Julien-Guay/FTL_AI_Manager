#include "ProcessObserver.h"
#include <MemoryFileAccessor.h>

ProcessObserver::~ProcessObserver()
{
}

ProcessObserver::ProcessObserver()
{
}

Block<MemoryFileAccessor>* ProcessObserver::buildVirtualBlock(const DWORD beginning_address,const DWORD ending_address)
{
    Block<MemoryFileAccessor>* virtual_block_ptr = 0;
    string file_name="toto.dat";
    byte value = 0;
    DWORD pid;
    HWND hwnd;
    hwnd = FindWindow(NULL,"FTL");//Rentré en dur comme un gros porc
    ofstream file(file_name, ios::out | ios::trunc | ios::binary);  //On ouvre le fichier en écriture
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
    for(DWORD address=beginning_address; address<=ending_address; address++)
    {
        ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0);
        file.write((char*)&value, sizeof(byte));
    }
    CloseHandle(phandle);
    file.close();
    shared_ptr<MemoryFileAccessor> mem_file_accessor (new MemoryFileAccessor(beginning_address,ending_address,file_name));
    virtual_block_ptr = new Block<MemoryFileAccessor>(beginning_address,ending_address,(Block<MemoryFileAccessor>::BlockType)0,mem_file_accessor);
    return virtual_block_ptr;
}

Block<MemoryArrayAccessor>* ProcessObserver::buildRealBlock(const DWORD beginning_address,const DWORD ending_address)
{
    int bufferSize = ending_address-beginning_address;
    byte* buffer = 0;
    buffer = new byte[bufferSize];
    DWORD pid;
    HWND hwnd;
    hwnd = FindWindow(NULL,"FTL");//Rentré en dur comme un gros porc
    if(!hwnd)
    {
        cout<<"La fenêtre n'a pas été trouvée"<<endl;
        exit(1);//Dans l'idéal il faudrait lancer une exception
    }
    GetWindowThreadProcessId(hwnd,&pid);
    HANDLE phandle = OpenProcess(PROCESS_QUERY_INFORMATION,0,pid);
    if(!phandle)
    {
        cout<<"Impossible d'obtenir la poignée (handle)"<<endl;
        exit(3);//Dans l'idéal il faudrait lancer une exception
    }
    ReadProcessMemory(phandle,(void*)beginning_address,buffer,sizeof(byte)*bufferSize,0);
    CloseHandle(phandle);
}

DWORD ProcessObserver::getMemoryLength()
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
