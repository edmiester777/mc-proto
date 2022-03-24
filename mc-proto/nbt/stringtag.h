#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    class NBTStringTag : public NBTTagBase
    {
    public:
        NBTStringTag(mcstream& stream);
        NBTStringTag(string value);
        void operator=(const NBTStringTag& other);
        void operator=(const string& value);

        string& value();

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTStringTag& tag);

    private:
        string m_value;
    };
}