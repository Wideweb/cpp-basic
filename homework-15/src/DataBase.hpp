#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

struct Entity {
    unsigned int id;
};

template <typename TEntity,
          typename = std::enable_if_t<std::is_base_of_v<Entity, TEntity>>>
class DataBase {
  private:
    std::vector<TEntity> m_Entities;
    std::string m_FilePath;
    unsigned int m_LastId;

  public:
    DataBase(const std::string &file) : m_FilePath(file), m_LastId(0) {}
    ~DataBase() {}

    void add(TEntity entity) {
        fetch();

        m_LastId++;
        entity.id = m_LastId;
        m_Entities.push_back(entity);

        flush();
    }

    bool update(const TEntity &entity) {
        fetch();

        auto it = std::find_if(
            m_Entities.begin(), m_Entities.end(),
            [&entity](const auto &item) { return item.id == entity.id; });

        if (it == m_Entities.end()) {
            return false;
        }

        int index = std::distance(m_Entities.begin(), it);
        m_Entities[index] = entity;

        flush();

        return true;
    }

    bool remove(const TEntity &entity) {
        fetch();

        m_Entities.erase(std::remove_if(
            m_Entities.begin(), m_Entities.end(),
            [&entity](TEntity &item) { return item.id == entity.id; }));

        flush();

        return true;
    }

    const std::vector<TEntity> &getAll() {
        fetch();
        return m_Entities;
    }

  private:
    void fetch() {
        m_Entities.clear();

        if (!std::filesystem::exists(m_FilePath)) {
            throw std::invalid_argument(
                "Данные не были загружены (файл данных не найден)");
        }

        std::fstream in(m_FilePath, std::ios::in | std::ios::binary);

        std::vector<TEntity> entities;

        std::copy(std::istream_iterator<TEntity, char>(in),
                  std::istream_iterator<TEntity, char>(),
                  std::back_inserter(entities));

        m_Entities = std::move(entities);

        if (m_Entities.empty()) {
            m_LastId = 0;
        } else {
            m_LastId = m_Entities[m_Entities.size() - 1].id;
        }
    }

    void flush() {
        if (!std::filesystem::exists(m_FilePath)) {
            throw std::invalid_argument(
                "Данные не были сохранены (файл данных не найден)");
        }

        std::fstream out(m_FilePath,
                         std::ios::out | std::ios::trunc | std::ios::binary);

        for (const auto &entity : m_Entities) {
            out << entity << std::endl;
        }

        out.close();
    }
};