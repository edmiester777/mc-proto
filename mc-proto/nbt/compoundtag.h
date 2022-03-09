#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTCompoundTag : public NBTTagBase
    {
    public:
        NBTCompoundTag(istream& stream);
        NBTCompoundTag(const map<string, NBTTagPtr>& value);

        void operator=(const NBTCompoundTag& other);
        void operator=(const map<string, NBTTagPtr>& value);
        NBTTagPtr& operator[](const string& key);

        size_t size() const;
        bool contains(const string& key);

        template <class T>
        T& get(const string& key);

        virtual NBTTagTypes type() const override;
        virtual void write_data(ostream& stream) const override;

    private:
        mutable map<string, NBTTagPtr> m_value;
    };

    template <class T>
    T& NBTCompoundTag::get(const string& key)
    {
        return (T&)*((T*)m_value[key].get());
    }
}