#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
//проверка утечек (при утечке в отладке выйдет сообщение об утечке)

#include <iostream> 
#include <ctime>
#include <cassert>
#include "Test.h"
#include "DynamicArray.h"
#include "Sequence.h"
#include "SmartPtr.h"

Sequence<int>* Get_Arr() {
    Sequence<int>* seq = new ArraySequence<int>;
    int type;
    while (true) {
        std::cout << "Choose option:\n"
            "1. Insert in back\n"
            "2. Insert in front\n"
            "3. Insert at pos\n"
            "4. Show array\n"
            "5. Exit\n";
        std::cin >> type;
        if (type == 1) {
            std::cout << "insert value\n";
            int number;
            std::cin >> number;
            seq->Append(number);
            continue;
        }
        if (type == 2) {
            std::cout << "insert value\n";
            int number;
            std::cin >> number;
            seq->Prepend(number);
            continue;
        }
        if (type == 3) {
            std::cout << "insert index\n";
            size_t index;
            std::cin >> index;
            std::cout << "insert value\n";
            int number;
            std::cin >> number;
            seq->InsertAt(number, index);
            continue;
        }
        if (type == 4) {
            for (size_t i = 0; i < seq->GetSize(); ++i) {
                std::cout << seq->Get(i) << " ";
            }
            std::cout << "\n";
            continue;
        }
        if (type == 5) {
            break;
        }
    }
    return seq;
}

void Interf() {
    std::cout << "Enter 1st arr: \n";
    Sequence<int>* seq = Get_Arr();
    Uniqe_Ptr<Sequence<int>> uptr(seq);
    for (int i = 0; i < seq->GetSize(); ++i) {
        std::cout << seq->Get(i) << " ";
    }

    std::cout << "\nEnter 2nd arr: \n";
    Uniqe_Ptr<Sequence<int>> uptr2 = Get_Arr();
    uptr = uptr2->Concat(seq);

    std::cout << "Ptr2: ";
    for (int i = 0; i < uptr2->GetSize(); ++i) {
        std::cout << uptr2->Get(i) << " ";
    }

    std::cout << "\nPtr1: ";

    for (int i = 0; i < uptr->GetSize(); ++i) {
        std::cout << uptr->Get(i) << " ";
    }
}

int main() {
    while (true) {
        int type;
        std::cout << "\n1)Program concatenation 2 arrays"
                     "\n2)Tests"
                     "\n3)Exit\n";
        std::cin >> type;
        if (type == 1) {
            Interf();
        }else if(type == 3){
            break;
        }
        else {
            std::cout << "\n\n\n/______________________________________________________/\n";
            Test_Uniqe_Pointer();
            std::cout << "\nALL TESTS OF UNIQE POINTER COMPLETED SUCCESFULLY" << std::endl;
            std::cout << "\n/______________________________________________________/\n";
            Test_Shared_Pointer();
            std::cout << "\nALL TESTS OF SHARED POINTER COMPLETED SUCCESFULLY" << std::endl;
            std::cout << "\n/______________________________________________________/\n";
            Time_Test();
            break;
        }
    }

    _CrtDumpMemoryLeaks();//функция поиска утечки
    return 0;
}
