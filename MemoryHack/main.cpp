#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    DWORD address = 0;
    int value = 1;
    DWORD pid, psize;
    PROCESS_MEMORY_COUNTERS counters;
    HWND hwnd;
    hwnd = FindWindow(NULL,"Démineur");

    cout<<  value << endl;

    ofstream fichier("test2.txt", ios::out | ios::trunc);  // on ouvre le fichier en lecture


    if(fichier)  // si l'ouverture a réussi
    {
        if(!hwnd)
        {
            cout <<"Window not found!\n";
            cin.get();
        }
        else
        {
            GetWindowThreadProcessId(hwnd,&pid);
            HANDLE phandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,0,pid);
            if(!phandle)
            {
                cout <<"Could not get handle!\n";
                cin.get();
            }
            else
            {
                if(GetProcessMemoryInfo(phandle,&counters, sizeof(counters)))
                {

                    psize = counters.PagefileUsage;

                }
                while(address < psize)
                {

                    if(ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0) && value)
                    {
                        fichier << address << " " <<value << endl;
                    }
                    if(!(address%1000000)){
                        cout<< ((address*100)/psize) << "%" <<endl;
                        Sleep(50);
                    }
                    address++;
//                Sleep(50);
                }
            }
            CloseHandle(phandle);
        }

        fichier.close();  // on ferme le fichier
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    return 0;
}



