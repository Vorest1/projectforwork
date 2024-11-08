#include <iostream>
#include <cassert>
#include "SmartPtr.h"
#include "Sequence.h"
#include "DynamicArray.h"
#include "Test.h"

void Test_Uniqe_Pointer() {
    srand(time(nullptr));
    int* data = new int[10];
    int a = 5;
    int len = 10;
    for (int i = 0; i < len; i++) {
        data[i] = i;
    }

    std::cout << "Test 1 elem in unique pointer: ";
    Uniqe_Ptr<int> ptr = Uniqe_Ptr<int>();
    Uniqe_Ptr<int> ptr2(new int(a));
    assert(*ptr2 == 5);
    assert(*(ptr2.Get()) == 5);
    std::cout << "DONE\n";


    std::cout << "Test metod Get: ";
    Uniqe_Ptr<Sequence<int>> ptr3 = new ArraySequence<int>(data, len);
    assert(ptr3->Get(0) == data[0]);
    assert(ptr3->Get(1) == data[1]);
    assert(ptr3->Get(2) == data[2]);
    assert(ptr3->Get(3) == data[3]);
    assert(ptr3->Get(4) == data[4]);
    std::cout << "DONE\n";
    delete[] data;

    std::cout << "Test metod Swap: ";
    *ptr2 = 7;
    assert(*ptr2 == 7);
    ptr2.Swap(ptr);
    assert(*ptr == 7);
    std::cout << "DONE\n";


    std::cout << "Test delete copyed uniqe pointer: ";
    assert(ptr2.Get() == nullptr);
    std::cout << "DONE\n";


    std::cout << "Test metod Del: ";
    ptr.Del();
    assert(ptr.Get() == nullptr);
    std::cout << "DONE\n";
}

void Test_Shared_Pointer() {
    srand(time(nullptr));
    int* data = new int[5];
    for (int i = 0; i < 5; i++) {
        data[i] = rand() % 100;
    }
    int a = 5;
    Shared_Ptr<int> ptr2(new int(a));


    std::cout << "Test method Get_count until copy: ";//тест на правильность работы счётчика при создании
    std::cout << ptr2.Get_count() << "\n";
    assert(ptr2.Get_count() == 1);
    std::cout << "DONE\n";


    std::cout << "Test method Uniq for shared pointer: ";//тест на единственность ссылки
    assert(ptr2.Uniq() == true);
    std::cout << "DONE\n";


    std::cout << "Test method Get_count after copy: ";//тест на правильность работы счётчика после копирования неединственность ссылки
    Shared_Ptr<int> ptr4 = Shared_Ptr<int>(ptr2);
    assert(ptr2.Get_count() == 2);
    std::cout << "DONE\n";


    std::cout << "Test method Uniq after copy: ";//тест на неединственность ссылки
    assert(ptr2.Uniq() == false);
    std::cout << "DONE\n";


    std::cout << "Test 1 elem in shared pointer:  ";
    assert(*ptr2 == 5);
    assert(ptr2.Get() == 5);
    std::cout << "DONE\n";


    std::cout << "Test metod Get and correct filling array:";
    Sequence<int>* seq = new ArraySequence<int>(data, 5);
    delete[] data;
    Shared_Ptr<Sequence<int>> ptr3 = Shared_Ptr<Sequence<int>>(seq);
    assert(ptr3->Get(0) == (*seq)[0]);
    assert(ptr3->Get(1) == (*seq)[1]);
    assert(ptr3->Get(2) == (*seq)[2]);
    assert(ptr3->Get(3) == (*seq)[3]);
    assert(ptr3->Get(4) == (*seq)[4]);
    std::cout << "DONE\n";


    std::cout << "Test correct working after changing the pointer: ";
    ptr2 = (new int(7));
    assert(*ptr2 == 7);
    assert(ptr2.Get_count() == 1);
    std::cout << "DONE\n";


    std::cout << "Test method Swap: ";
    Shared_Ptr<int> ptr = Shared_Ptr<int>();
    ptr2.Swap(ptr);
    assert(*ptr == 7);
    assert(&(ptr2.Get()) == nullptr);
    std::cout << "DONE\n";


    std::cout << "Test method Del: ";
    ptr.Del();
    assert(&(ptr.Get()) == nullptr);
    std::cout << "DONE\n";
}


void TestTime_MyF(int quantity) {
    clock_t start = clock();
    for (int i = 0; i < quantity; ++i) {
        Uniqe_Ptr<int> Uptr(new int(i));
        *Uptr += 1;
    }
    clock_t end = clock();
    double utime = end - start;

    clock_t start2 = clock();
    for (int i = 0; i < quantity; ++i) {
        Shared_Ptr<int> Sptr(new int(i));
        *Sptr += 1;
    }
    clock_t end2 = clock();
    double stime = end2 - start2;

    cout << "Time my function for " << quantity << " elements: U_Ptr(" << utime << "), S_Ptr(" << stime << ")\n";
}

void TestTime_STD(int quantity) {
    clock_t start = clock();
    for (int i = 0; i < quantity; ++i) {
        unique_ptr<int> Uptr(new int(i));
        *Uptr += 1;
    }
    clock_t end = clock();
    double utime = end - start;

    clock_t start2 = clock();
    for (int i = 0; i < quantity; ++i) {
        shared_ptr<int> ptr(new int(i));
        *ptr += 1;
    }
    clock_t end2 = clock();
    double stime = end2 - start2;

    cout << "Time STD function for " << quantity << " elements: U_Ptr(" << utime << "), S_Ptr(" << stime << ")\n";
}

void Time_Test() {
    int quantity = 100;
    cout << "\n/--------------------------------------------------------/\n\n";
    for (int i = quantity; i < 100000000; i *= 10) {
        TestTime_STD(i);
    }
    cout << "\n/--------------------------------------------------------/\n\n";
    for (int i = quantity; i < 100000000; i *= 10) {
        TestTime_MyF(i);
    }
    cout << "\n/--------------------------------------------------------/\n\n";
}

