#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    class NBTStringTag : public NBTTagBase
    {
    public:
        NBTStringTag(istream& stream);
        NBTStringTag(string value);
        void operator=(const NBTStringTag& other);
        void operator=(const string& value);

        string& value();

        virtual NBTTagTypes type() const override;

    protected:
        virtual void write_data(ostream& stream) const override;

    private:
        string m_value;
    };
}