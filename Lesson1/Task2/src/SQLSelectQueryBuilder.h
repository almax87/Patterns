#include <string>
#include <vector>
#include <map>
#include <utility>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder() = default;

    // Добавление одного столбца
    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept {
        columns_.push_back(column);
        return *this;
    }

    // Добавление нескольких столбцов
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (const auto& column : columns) {
            columns_.push_back(column);
        }
        return *this;
    }

    // Установка таблицы
    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept {
        table_ = table;
        return *this;
    }

    // Добавление одного условия WHERE
    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) noexcept {
        where_conditions_.emplace_back(column, value);
        return *this;
    }

    // Добавление нескольких условий WHERE
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [column, value] : kv) {
            where_conditions_.emplace_back(column, value);
        }
        return *this;
    }

    // Построение SQL-запроса
    std::string BuildQuery() const {
        std::string query = "SELECT ";

        // Добавление столбцов
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

        // Добавление таблицы
        query += " FROM " + table_;

        // Добавление условий WHERE
        if (!where_conditions_.empty()) {
            query += " WHERE ";
            for (size_t i = 0; i < where_conditions_.size(); ++i) {
                if (i != 0) {
                    query += " AND ";
                }
                query += where_conditions_[i].first + "=" + where_conditions_[i].second;
            }
        }

        query += ";";
        return query;
    }

private:
    std::vector<std::string> columns_;
    std::string table_;
    std::vector<std::pair<std::string, std::string>> where_conditions_;
};