#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    class NBTByteArrayTag : public NBTTagBase
    {
    public:
        NBTByteArrayTag(mcstream& stream);
        NBTByteArrayTag(const vector<uint8_t>& value);
        void operator=(const NBTByteArrayTag& other);
        void operator=(const vector<uint8_t>& value);

        size_t size() const;
        uint8_t operator[](int index) const;

        virtual NBTTagTypes type() const override;
        virtual void write_data(mcstream& stream) const override;

        friend mcstream& operator>>(mcstream& stream, NBTByteArrayTag& tag);

    private:
        vector<uint8_t> m_value;
    };
}