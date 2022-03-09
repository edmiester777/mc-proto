#pragma once

#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTDoubleTag : public NBTTagBase
    {
    public:
        NBTDoubleTag(istream& stream);
        NBTDoubleTag(double value);
        void operator=(const NBTDoubleTag& other);
        void operator=(double value);

        double value() const;

        virtual NBTTagTypes type() const override;        
        virtual void write_data(ostream& stream) const override;

    private:
        double m_value;
    };
}