#pragma once
class VM
{
public:
    VM() : StackIndex_(0) {}
public:
    char interpret(char bytecode[], size_t size);

private:
    int add(int left, int right);
    int sub(int left, int right);
    int div(int left, int right);
    int mul(int left, int right);

private:
    char    pop();
    void    push(char c);
private:
    static const char MAX_STACK = 100;
    char StackIndex_;
    char Stack_[MAX_STACK];
};

