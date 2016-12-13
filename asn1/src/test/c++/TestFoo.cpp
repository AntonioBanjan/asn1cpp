/*
 * TestFoo.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */
#include "gtest/gtest.h"
#include "Foo.h"
#include <vector>
#include <functional>

TEST(FooTest, TestFoo) {

    Foo objFoo;

    objFoo.Do();

    ASSERT_EQ(true, true);
}

template<template<class > class ... T>
struct XXX {

};

template<typename T>
struct Initializer {

    Initializer(T* ptr) :
            m_ptr(ptr) {

    }

    virtual ~Initializer() {

        m_ptr->Init();
    }

private:
    T* m_ptr;
};

template<typename D>
struct Base {

    Base(D* ptrD) {
        Initializer<D> i(ptrD);
    }
    virtual ~Base() {
    }
    virtual void Init() = 0;
};

template<typename T>
struct StaticScalarTypeChecker {

    static void Check(...);

    template<typename U>
    static void Check(U u) {

        T t = static_cast<T>(u);
    }
};

struct Derived: public Base<Derived> {

    Derived() :
            Base(this) {
    }
    ~Derived() {
    }

    void Init() override {

        std::cout << "Init" << std::endl;
    }
};

template<typename T>
struct Qsort {

    static void Sort(typename std::vector<T>& items,
            const std::function<int(const T, const T)>& comparator) {

        Sort(items, 0, items.size() - 1, comparator);

    }
private:
    static void Sort(typename std::vector<T>& items, size_t left, size_t right,
            typename std::function<int(const T, const T)> comparator) {

        T pivot = items[(left + right) / 2];

        size_t i = left;

        size_t j = right;

        while (i <= j) {

            while (comparator(items[i], pivot) < 0) {
                i++;
            }
            while (comparator(items[j], pivot) > 0) {
                j--;
            }

            if (i <= j) {

                T temp = items[i];

                items[i] = items[j];

                items[j] = temp;

                i++;
                j--;
            }
        }

        if (left < j) {

            Sort(items, left, j, comparator);
        }

        if (i < right) {

            Sort(items, i, right, comparator);
        }
    }
};

TEST(FooTest, TestXXX) {

    std::vector<int> items { 10, 2, 3, 900, 45, 60 };

    const std::function<int(int, int)> intComparator(
            [](const int i0, const int i1) {return i0 - i1;});

    Qsort<int>::Sort(items, intComparator);

    std::cout << " End " << std::endl;
}

TEST(FooTest, ConcurrencyTest) {

}

