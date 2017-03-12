#ifndef __LIBDATABASE_IPERSISTSTATEMENT_H__
#define __LIBDATABASE_IPERSISTSTATEMENT_H__
#include <memory>

class iDataStatement;

class iPersistStatement
{
public:
    explicit iPersistStatement(const std::shared_ptr<iDataStatement>& spStmt);
    virtual ~iPersistStatement() {}

    virtual int Commit() = 0;

private:
    std::shared_ptr<iDataStatement> m_spStmt;
};

#endif // !__LIBDATABASE_IPERSISTSTATEMENT_H__
