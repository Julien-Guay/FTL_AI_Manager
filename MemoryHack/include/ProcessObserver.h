#ifndef ProcessObserver_H
#define ProcessObserver_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <psapi.h>

using namespace std;

class ProcessObserver
{
    public:
        ProcessObserver(const int begin,const int end,const string& name);
        virtual ~ProcessObserver();

        /** \brief Copie une portion de la RAM dans file_pointer_
         *
         * Copie la RAM de � partir de l'adresse beginning_adress_ jusqu'� ending_address_
         * dans le fichier file_name_ qui est c�� � cette occasion.
         *
         */
        void copyMemoryInFile();

        /** \brief Permet un acc�s direct � n'importe quel octet de la copie de la m�moire
        /
        /   Retourne l'octet dont l'adresse est address dans la capture m�moire stock�e dans file_pointer_
        /
        */
        byte operator[](const DWORD address);

        /** \brief Retourne la plus grande valeur adressable
        /
        /   Retourne la plus grande valeur adressable, c'est � dire la working set size de FTL -1
        /
        */
        DWORD getMaxAdress();

    protected:
    private:
        DWORD beginning_address_;
        DWORD ending_address_;
        int size_;
        string file_name_;



};

#endif // ProcessObserver_H
