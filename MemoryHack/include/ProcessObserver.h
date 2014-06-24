#ifndef ProcessObserver_H
#define ProcessObserver_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <psapi.h>
#include <Block.h>
#include <VirtualBlock.h>

using namespace std;

class ProcessObserver
{
    public:
        ProcessObserver();
        virtual ~ProcessObserver();

        /** \brief Créée un Block virtuel
         *
         * Copie la RAM de à partir de l'adresse beginning_adress_ jusqu'à ending_address_
         * dans le fichier file_name_ qui est créé à cette occasion et renvoie un pointeur vers un
         * nouveau block contenant un MemoryFileAccessor encapsulant ce fichier
         */
        VirtualBlock* buildVirtualBlock(const DWORD beginning_address,const DWORD ending_address);

        /** \brief Créée un Block réel
         *
         * Copie la RAM de à partir de l'adresse beginning_adress_ jusqu'à ending_address_
         * dans un tableau et renvoie un pointeur vers un nouveau block contenant ce tableau.
         *
         */
        Block* buildRealBlock(const DWORD beginning_address,const DWORD ending_address);

        /** \brief Retourne la plus grande valeur adressable
        /
        /   Retourne la plus grande valeur adressable, c'est à dire (la working set size de FTL) - 1
        /
        */
        DWORD getMemoryLength();

    protected:
    private:



};

#endif // ProcessObserver_H
