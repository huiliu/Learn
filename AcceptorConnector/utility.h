#pragma once

class noncopyable
{
public:
    noncopyable() = delete;
    noncopyable(const noncopyable&) = delete;
    noncopyable(noncopyable&&) = delete;
};