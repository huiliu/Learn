#include "SQLite.h"
#include <iostream>
#include <memory>
struct A
{
    A(int y) : year(y) {}

    int year;
    char* name;
};

struct Desturct
{
    void operator()(A* p)
    {
        if (nullptr != p)
        {
            std::cout << "destruct by function: " << p->name << std::endl;
            delete p->name;
            delete p;
        }
    }
};

void
case01()
{
    std::shared_ptr<A> p(nullptr, Desturct());
    A* xx = new A(1);

    xx->name = new char(4);
    memcpy(xx->name, "liuh", 4);

    p.reset(xx);
}

void
case02()
{
    std::shared_ptr<A> p(new A(11111), Desturct());
    A* xx = new A(22222);

    xx->year = 100;
    xx->name = new char(4);
    memcpy(xx->name, "liuh", 4);

    p.reset(xx);
}
struct Foo {
    Foo(int n = 0) noexcept : bar(n) {
        std::cout << "Foo: constructor, bar = " << bar << '\n';
    }
    ~Foo() {
        std::cout << "Foo: destructor, bar = " << bar << '\n';
    }
    int getBar() const noexcept { return bar; }
private:
    int bar;
};

void case03()
{
    std::shared_ptr<Foo> sptr = std::make_shared<Foo>(1);
    std::cout << "The first Foo's bar is " << sptr->getBar() << "\n";

    // reset the shared_ptr, hand it a fresh instance of Foo
    // (the old instance will be destroyed after this call)
    sptr.reset(new Foo);
    std::cout << "The second Foo's bar is " << sptr->getBar() << "\n";
}

int main()
{
    case01();
    case02();
    case03();
    return 1;

    SQLite mySqlite("test.db");
    iDataConnection* pconn = mySqlite.Connect("test.db");

    pconn->Execute("CREATE TABLE test(id int)");
    pconn->Execute("INSERT INTO test VALUES(10)");
    pconn->Execute("INSERT INTO test VALUES(20)");
    pconn->Execute("INSERT INTO test VALUES(30)");
    pconn->Execute("INSERT INTO test VALUES(10)");

    iDataStatement* pStatement = pconn->CreateStatement();

    pStatement->Prepare("SELECT * FROM test");

    pStatement->BindInt32(1, 10);

    iResultSet* result= pStatement->Execute();

    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();

    pconn->Close();
    return 0;
}

