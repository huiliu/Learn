// utf8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <codecvt>
#include <fstream>
#include <boost/log/trivial.hpp>
#include <cstring>

void ReadFile() {
    std::ifstream ifs("./data");
    if (!ifs.is_open()) {
        BOOST_LOG_TRIVIAL(error) << "打开文件失败！" << std::endl;
        return;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wcout.imbue(std::locale("chs"));
    char buff[1024] = { 0 };
    while (true)
    {
        if (ifs.eof()) {
            break;
        }

        ifs.getline(buff, 1024);
        std::wcout << conv.from_bytes(buff) << std::endl;

        memset(buff, 0, 1024);
    }

    ifs.close();
}

void TestLocale()
{
    auto l1 = std::locale();
    auto l2 = std::locale("en_US.UTF-8");
    std::locale l3(l1, l2, std::locale::ctype);
    auto l4 = std::locale(l1, new std::codecvt_utf8<wchar_t>);
    std::cout << "locale setting is " << l1.name() << '\n'
        << l2.name() << '\n'
        << l3.name() << '\n'
        << l4.name() << '\n'
        << std::endl;
}

int main()
{
    const char* str = "中国！";
    std::cout << "Hello World!\n" << str << std::endl;
    ReadFile();

    TestLocale();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
