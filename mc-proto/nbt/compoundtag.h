#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTCompoundTag : public NBTTagBase
    {
    public:
        NBTCompoundTag(mcstream& stream);
        NBTCompoundTag(const string& name, const map<string, NBTTagPtr>& value);

        void operator=(const NBTCompoundTag& other);
        void operator=(const map<string, NBTTagPtr>& value);
        NBTTagPtr& operator[](const string& key);

        size_t size() const;
        bool contains(const string& key) const;
        string name() const;

        template <class T>
        T& get(const string& key);

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTCompoundTag& t);

    private:
        mutable map<string, NBTTagPtr> m_value;
        string m_name;
    };

    template <class T>
    T& NBTCompoundTag::get(const string& key)
    {
        return (T&)*((T*)m_value[key].get());
    }
}