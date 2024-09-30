#ifndef SCRIPTTABLEREADER_H
#define SCRIPTTABLEREADER_H

#include <sol/sol.hpp>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "objects/GlobalId.h"

namespace TIE {

class ScriptTableReader {
    public:
        ScriptTableReader(const sol::table&);
        ScriptTableReader();

        const bool hasKey(const std::string&) const;

        const ScriptTableReader& getReader(const std::string&) const;
        const std::map<std::string, ScriptTableReader>& getReaders() const;

		template <typename T>
        const std::map<std::string, T>& getValues() const { return std::map<std::string, T>(); }

        template <>
        const std::map<std::string, bool>& getValues() const {
            return this->boolValues;
        }

        template <>
        const std::map<std::string, float>& getValues() const {
            return this->floatValues;
        }

        template <>
        const std::map<std::string, std::string>& getValues() const {
            return this->stringValues;
        }

        template <>
        const std::map<std::string, GlobalId>& getValues() const {
            return this->functionValues;
        }

        template <>
        const std::map<std::string, sol::table>& getValues() const {
            return this->tableValues;
        }
        
		template <typename T>
        const bool has(const std::string& key) const { return false; }
		
        template <>
        const bool has<bool>(const std::string& key) const {
            return this->boolValues.count(key);
        }

        template <>
        const bool has<float>(const std::string& key) const {
            return this->floatValues.count(key);
        }

        template <>
        const bool has<std::string>(const std::string& key) const {
            return this->stringValues.count(key);
        }

        template <>
        const bool has<GlobalId>(const std::string& key) const {
            return this->functionValues.count(key);
        }

        template <>
        const bool has<sol::table>(const std::string& key) const {
            return this->tableValues.count(key);
        }

		template <typename T>
        const T* get(const std::string& key) const { return nullptr; }

        template <>
        const bool* get<bool>(const std::string& key) const {
            return &this->boolValues.at(key);
        }

        template <>
        const float* get<float>(const std::string& key) const {
            return &this->floatValues.at(key);
        }

        template <>
        const std::string* get<std::string>(const std::string& key) const {
            return &this->stringValues.at(key);
        }

        template <>
        const GlobalId* get<GlobalId>(const std::string& key) const {
            return &this->functionValues.at(key);
        }

        template <>
        const sol::table* get<sol::table>(const std::string& key) const {
            return &this->tableValues.at(key);
        }

		template <typename T>
        const T& get(const std::string& key, const T& default) const { return default; }

        template <>
        const bool& get<bool>(const std::string& key, const bool& default ) const {
            if (this->boolValues.count(key)) {
                return this->boolValues.at(key);
            } else {
                return default;
            }
        }

        template <>
        const float& get<float>(const std::string& key, const float& default ) const {
            if (this->floatValues.count(key)) {
                return this->floatValues.at(key);
            } else {
                return default;
            }
        }

        template <>
        const std::string& get<std::string>(const std::string& key, const std::string& default ) const {
            if (this->stringValues.count(key)) {
                return this->stringValues.at(key);
            } else {
                return default;
            }
        }
        
        template <>
        const GlobalId& get<GlobalId>(const std::string& key, const GlobalId& default ) const {
            if (this->functionValues.count(key)) {
                return this->functionValues.at(key);
            } else {
                return default;
            }
        }

        template <>
        const sol::table& get<sol::table>(const std::string& key, const sol::table& default ) const {
            if (this->tableValues.count(key)) {
                return this->tableValues.at(key);
            } else {
                return default;
            }
        }

		template <typename T>
        T& get(const std::string& key, T& default) { return default; }

        template <>
        std::vector<GlobalId>& get(const std::string& key, std::vector<GlobalId>& container) {
            if (this->tableValues.count(key)) {
                if (this->tableValues.at(key).is<std::vector<GlobalId>>()) {
                    sol::table& table = this->tableValues.at(key).as<sol::table>();
                    for (int i = 1; i <= table.size(); i++) {
                        container.push_back(table[i]);
                    }
                }
            }
            return container;
        }

    private:
        void read(const sol::table&);
        static const ScriptTableReader& getEmptyReader();

        // TODO Rename to just plurals like floats bools strings
		std::map<std::string, bool> keys;
		std::map<std::string, bool> boolValues;
		std::map<std::string, float> floatValues;
		std::map<std::string, std::string> stringValues;
		std::map<std::string, GlobalId> functionValues;
		std::map<std::string, sol::table> tableValues;
		std::map<std::string, ScriptTableReader> readers;
};

}

#endif
