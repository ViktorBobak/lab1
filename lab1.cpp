////Завдання 1////
#include <iostream>
#include <thread>

using namespace std;

void Thread1()
{
    cout << "1 ";
}

void Thread2()
{
    cout << "2 ";
}

int main()
{
    thread t1(Thread1);
    thread t2(Thread2);

    return 0;
}
////Завдання 2////
#include <iostream>
#include <thread>

using namespace std;

void Thread1()
{
    cout << "1 ";
}

void Thread2()
{
    cout << "2 ";
}

int main()
{
    thread t1(Thread1);
    thread t2(Thread2);

    t1.detach();
    t2.detach();

    return 0;
}
////Завдання 3////
#include <iostream>
#include <windows.h>
#include <thread>
#include <list>

using namespace std;

list<int> l;

void AddToList(int value)
{
    for (int i = 0; i < 10; i++)
    {
        l.push_back(value + i);
        cout << "Added: " << value + i << endl;
    }
}

void ListContains(int value)
{
    for (int i = 0; i < 10; i++)
    {
        bool found = false;

        for (int x : l)
        {
            if (x == value)
            {
                found = true;
                break;
            }
        }

        if (found)
            cout << value << " - входить" << endl;
        else
            cout << value << " - не входить" << endl;
    }
}

int main()
{

    SetConsoleOutputCP(65001);

    int value = 5;

    thread t1(AddToList, value);
    thread t2(ListContains, value);

    t1.join();
    t2.join();

    return 0;
}
////Завдання 4////
#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <Windows.h>

using namespace std;

list<int> l;
mutex m;

void AddToList(int value)
{
    for (int i = 0; i < 10; i++)
    {
        m.lock();

        l.push_back(value + i);
        cout << "Added: " << value + i << endl;

        m.unlock();
    }
}

void ListContains(int value)
{
    for (int i = 0; i < 10; i++)
    {
        m.lock();

        bool found = false;

        for (int x : l)
        {
            if (x == value)
            {
                found = true;
                break;
            }
        }

        if (found)
            cout << value << " - входить" << endl;
        else
            cout << value << " - не входить" << endl;

        m.unlock();
    }
}

int main()
{

    SetConsoleOutputCP(65001);
    int value = 5;

    thread t1(AddToList, value);
    thread t2(ListContains, value);

    t1.join();
    t2.join();

    return 0;
}
////Завдання 5////
#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <Windows.h>

using namespace std;

list<int> l;
mutex m;

void AddToList(int value)
{
    lock_guard<mutex> lock(m);

    l.push_back(value);

    cout << "Додано: " << value << endl;
}

void ListContains(int value)
{
    lock_guard<mutex> lock(m);

    bool found = false;

    for (int x : l)
    {
        if (x == value)
        {
            found = true;
            break;
        }
    }

    if (found)
        cout << value << " - входить" << endl;
    else
        cout << value << " - не входить" << endl;
}

int main()
{
    SetConsoleOutputCP(65001);

    for (int i = 0; i < 10; i++)
    {
        thread t1(AddToList, 5 + i);
        thread t2(ListContains, 5);

        t1.detach();
        t2.detach();
    }


    this_thread::sleep_for(chrono::seconds(1));

    return 0;
}
////Завдання 6////
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <Windows.h>

using namespace std;

class someData
{
public:
    string name;
    string surname;
    string address;
    int age;
};

class exchangePerson
{
private:
    someData data;
    mutex m;

public:

    static void JohnDoe(exchangePerson& person)
    {
        lock_guard<mutex> lock(person.m);

        person.data.name = "John";
        person.data.surname = "Doe";
        person.data.address = "Unknown";
        person.data.age = 120;
    }

    static void JacobSmith(exchangePerson& person)
    {
        lock_guard<mutex> lock(person.m);

        person.data.name = "Jacob";
        person.data.surname = "Smith";
        person.data.address = "Known";
        person.data.age = 1;
    }

    static void Swap(exchangePerson& a, exchangePerson& b)
    {
        if (&a == &b)
            return;

        lock(a.m, b.m);

        lock_guard<mutex> lock1(a.m, adopt_lock);
        lock_guard<mutex> lock2(b.m, adopt_lock);

        swap(a.data, b.data);
    }

    void Print()
    {
        lock_guard<mutex> lock(m);

        cout << "Name: " << data.name << endl;
        cout << "Surname: " << data.surname << endl;
        cout << "Address: " << data.address << endl;
        cout << "Age: " << data.age << endl;
    }
};

int main()
{
    SetConsoleOutputCP(65001);

    exchangePerson person1;
    exchangePerson person2;

    thread t1(exchangePerson::JohnDoe, ref(person1));
    thread t2(exchangePerson::JacobSmith, ref(person2));

    t1.detach();
    t2.detach();

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Before swap:" << endl;

    cout << "\nPerson 1:" << endl;
    person1.Print();

    cout << "\nPerson 2:" << endl;
    person2.Print();

    thread t3(exchangePerson::Swap, ref(person1), ref(person2));

    t3.join();

    cout << "\nAfter swap:" << endl;

    cout << "\nPerson 1:" << endl;
    person1.Print();

    cout << "\nPerson 2:" << endl;
    person2.Print();

    return 0;
}
////Завдання 7////
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <Windows.h>

using namespace std;

class someData
{
public:
    string name;
    string surname;
    string address;
    int age;
};

class exchangePerson
{
private:
    someData data;
    mutex m;

public:

    static void JohnDoe(exchangePerson& person)
    {
        lock_guard<mutex> lock(person.m);

        person.data.name = "John";
        person.data.surname = "Doe";
        person.data.address = "Unknown";
        person.data.age = 120;
    }

    static void JacobSmith(exchangePerson& person)
    {
        lock_guard<mutex> lock(person.m);

        person.data.name = "Jacob";
        person.data.surname = "Smith";
        person.data.address = "Known";
        person.data.age = 1;
    }

    static void Swap(exchangePerson& a, exchangePerson& b)
    {
        if (&a == &b)
            return;

        unique_lock<mutex> lock1(a.m, defer_lock);
        unique_lock<mutex> lock2(b.m, defer_lock);

        lock(lock1, lock2);

        swap(a.data, b.data);
    }

    void Print()
    {
        lock_guard<mutex> lock(m);

        cout << "Name: " << data.name << endl;
        cout << "Surname: " << data.surname << endl;
        cout << "Address: " << data.address << endl;
        cout << "Age: " << data.age << endl;
    }
};

int main()
{
	SetConsoleOutputCP(65001);

    exchangePerson person1;
    exchangePerson person2;

    thread t1(exchangePerson::JohnDoe, ref(person1));
    thread t2(exchangePerson::JacobSmith, ref(person2));

    t1.detach();
    t2.detach();

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Before swap:" << endl;

    cout << "\nPerson 1:" << endl;
    person1.Print();

    cout << "\nPerson 2:" << endl;
    person2.Print();

    thread t3(exchangePerson::Swap, ref(person1), ref(person2));

    t3.join();

    cout << "\nAfter swap:" << endl;

    cout << "\nPerson 1:" << endl;
    person1.Print();

    cout << "\nPerson 2:" << endl;
    person2.Print();

    return 0;
}
