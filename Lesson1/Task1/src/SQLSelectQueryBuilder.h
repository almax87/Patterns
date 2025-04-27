#include <string>
#include <vector>
#include <map>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder() = default;

    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns_.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        where_conditions_[column] = value;
        return *this;
    }

    std::string BuildQuery() const {
        std::string query = "SELECT ";

        // Добавляем столбцы или * если столбцы не указаны
        if (columns_.empty()) {
            query += "*";
        } else {
            for (size_t i = 0; i < columns_.size(); ++i) {
                if (i != 0) {
                    query += ", ";
                }
                query += columns_[i];
            }
        }

        // Добавляем таблицу (обязательное поле)
        query += " FROM " + table_;

        // Добавляем условия WHERE если они есть
        if (!where_conditions_.empty()) {
            query += " WHERE ";
            bool first = true;
            for (const auto& condition : where_conditions_) {
                if (!first) {
                    query += " AND ";
                }
                query += condition.first + "=" + condition.second;
                first = false;
            }
        }

        query += ";";
        return query;
    }

private:
    std::vector<std::string> columns_;
    std::string table_;
    std::map<std::string, std::string> where_conditions_;
};