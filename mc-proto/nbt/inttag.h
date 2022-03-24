#pragma once
#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    using namespace std;

    class NBTIntTag : public NBTTagBase
    {
    public:
        NBTIntTag(mcstream& stream);
        NBTIntTag(int val);
        void operator=(const NBTIntTag& other);
        void operator=(int value);

        int32_t value();

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTIntTag& tag);

    private:
        i32 m_value;
    };
}