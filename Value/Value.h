#pragma once
// 值类型的实现

#include <cassert>

enum ValueType
{
    VT_INT,
    VT_FLOAT,
    VT_DOUBLE,
    VT_STRING,
};

#if IMPLEMENT_01
struct Value
{
    ValueType   type;
    union 
    {
        int     intValue;
        float   floatValue;
        double  doubleValue;
        char*   strValue;
    };
};

#elif IMPLEMENT_02
class Value
{
public:
    Value();
    ~Value();

    Value(const Value& other);
    Value(Value&& other);

    Value& operator=(const Value& rhs);
    Value& operator=(Value&& rhs);

public:
    explicit Value(int value);
    explicit Value(float value);
    explicit Value(double value);
    explicit Value(char* value);

public:
    ValueType GetType() const;

    bool    isInt() const;
    bool    isFloat() const;
    bool    isDouble() const;
    bool    isString() const;

public:
    int     asInt() const;
    float   asFloat() const;
    double  asDouble() const;
    char*   asString() const;

private:
    ValueType   m_type;
    char*       m_value;
};

#elif IMPLEMENT_03
class Value
{
public:
    virtual ~Value();

public:
    virtual int     asInt() { assert(false); };
    virtual float   asFloat() { assert(false); };
    virtual double  asDouble() { assert(false); };
    virtual char*   asString() { assert(false); };
};

class IntValue
    : public Value
{
public:
    explicit Value(int value) : m_value(value) {}

    virtual int asInt() { return m_value; }

private:
    int     m_value;
};

#endif // IMPLEMENT_01


