#include "../inc.h"
#include "tag.h"

namespace minecraft
{
    class NBTByteArrayTag : public NBTTagBase
    {
    public:
        NBTByteArrayTag(istream& stream);
        NBTByteArrayTag(const vector<uint8_t>& value);
        void operator=(const NBTByteArrayTag& other);
        void operator=(const vector<uint8_t>& value);

        size_t size() const;
        uint8_t operator[](int index) const;

        virtual NBTTagTypes type() const override;
        virtual void write_data(ostream& stream) const override;

    private:
        vector<uint8_t> m_value;
    };
}