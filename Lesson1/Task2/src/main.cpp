#include "SQLSelectQueryBuilder.h"
#include <iostream>

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");
    
    if(query_builder.BuildQuery() == "SELECT name, phone FROM students WHERE id=42 AND name=John;")
        std::cout << "Query created..." << std::endl;
    else
        std::cout << "Error!" << std::endl;

    
    return 0;
}