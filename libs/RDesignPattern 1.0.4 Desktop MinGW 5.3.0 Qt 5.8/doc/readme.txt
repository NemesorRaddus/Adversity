                                                       *RDesignPattern*
                                                       ****************
============
Introduction
============

This library grants easy and safe ways of using popular design patterns. Currently, it only supports reference/Meyers' singleton.

==========
How to use
==========

NOTE:In this readme only library inclusion through QtCreator on Windows is described.

NOTE 2:Copying whole library folder to project files folder is recommended.

1. Open your project .pro file.
2. Right click somewhere on text.
3. Choose Add library->External library.
4. In File with library field select file libRDesignPattern.a in debug or release folder (it doesn't matter which file you choose).
5. In Path to headers field select folder with library.
6. On the left, select only "Windows".
7. Below, under caption "Windows" tick only the first option (library inside "debug" or "release" subdirectory).
8. Click next and finish this procedure.
9. Run qmake (Projects panel on the left, right click on your project's name, run qmake).
10. Library should be ready to use!

=============
RRefSingleton
=============

This class allows easy creation of reference/Meyers' singleton in your project. To use it, #include "rrefsingleton.h".

To create a new singleton value, type RRefSingleton <Type>::getInstance(). This function returns a reference to static RRefSingleton <Type> object. You can use it directly to operate on singleton value or you can store it inside proper reference.


Functions overview:


static RRefSingleton<T> &getInstance() noexcept;

Standard way of creating new singleton. However it can also be used to access already created singleton.


static RRefSingleton<T> &getInstance(const T &value) noexcept;

Overloaded version of getInstance(). Sets value of singleton to value.


inline T &value() noexcept;

Returns value of singleton.


inline const T &value() const noexcept;

Overloaded version of value().


inline T &operator()() noexcept;

See value().


inline const T &operator()() const noexcept;

See value().



Example:

//example.h

#include <QDebug>
#include "rrefsingleton.h"

class Foo
{
public:
    void doSomething();

private:
    RRefSingleton <int> &indirectReference = RRefSingleton <int>::getInstance(10);
};

class Bar
{
public:
    void doSomethingElse();

private:
    int &directReference = RRefSingleton <int>::getInstance()();
};

//example.cpp

#include "example.h"

void Foo::doSomething()
{
    qDebug()<<"2. "<<indirectReference.value();
    indirectReference() = 20;
    qDebug()<<"3. "<<RRefSingleton<int>::getInstance().value();
}

void Bar::doSomethingElse()
{
    qDebug()<<"4. "<<directReference;
}

//main.cpp

#include "example.h"

int main()
{
    RRefSingleton <int>::getInstance()() = 0;
    Foo a;
    Bar b;
    qDebug()<<"1. "<<a.indirectReference()();
    a.doSomething();
    b.doSomethingElse();
    qDebug()<<"5. "<<RRefSingleton <int>::getInstance()();
}

//output

1. 0
2. 10
3. 20
4. 20
5. 20

Hint: If you want to make a specific class singleton-only, try this code template:

#ifndef SINGLETONONLY
#define SINGLETONONLY

class SingletonOnly
{
friend class RRefSingleton <SingletonOnly>; // friend declaration to allow RRefSingleton do its work
public:
//...
private:
    SingletonOnly(); // private constructor to disallow any other copies
};

namespace // anonymous namespace to avoid ambiguity during linking phase
{
    SingletonOnly &object = RRefSingleton <SingletonOnly>::getInstance()(); // reference to interact with the object
}

#endif //SINGLETONONLY



===========
FINAL WORDS
===========

I hope you enjoy this library. If you do, please recommend it to your friend and send only whole library folder. If you don't and you would like to share some constructive criticism, let me know at raddusx@wp.pl.

by Piotr "Raddus" Juszczyk