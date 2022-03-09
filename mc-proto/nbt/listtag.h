#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTListTag : public NBTTagBase
    {
    public:
        NBTListTag(istream& stream);
        NBTListTag(const NBTTagTypes type, const vector<shared_ptr<NBTTagBase>>& value);
        void operator=(const NBTListTag& other);
        shared_ptr<NBTTagBase>& operator[](int index);

        vector<shared_ptr<NBTTagBase>>& value();
        size_t size() const;
        NBTTagTypes elementType() const;
        
        template <class T>
        T& get(int index);

        virtual NBTTagTypes type() const override;
        virtual void write_data(ostream& stream) const override;

    private:
        NBTTagTypes m_elementType;
        mutable vector<shared_ptr<NBTTagBase>> m_value;
    };

    template <class T>
    T& NBTListTag::get(int index)
    {
        return (T&)*((T*)m_value[index].get());
    }
}