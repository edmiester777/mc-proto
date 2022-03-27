#include "palettedcontainer.h"
#include "types.h"

namespace minecraft
{
    Palette::Palette(u8 entryBits, mcstream& stream) : m_bitsPerEntry(entryBits)
    {
    }

    u8 Palette::entryBits() const
    {
        return m_bitsPerEntry;
    }

    BlockStates Palette::blockStateFromId(u32 id) const
    {
        return (BlockStates)id;
    }

    IndirectPalette::IndirectPalette(u8 entryBits, mcstream& stream)
        : Palette(entryBits, stream)
    {
        varint size;
        stream >> size;

        for (u32 id = 0; id < size.val(); ++id)
        {
            varint state;
            stream >> state;

            m_idToStateMap[id] = (BlockStates)state.val();
        }
    }

    BlockStates IndirectPalette::blockStateFromId(u32 id) const
    {
        return m_idToStateMap.at(id);
    }

    PalettedContainer::PalettedContainer(mcstream& stream)
    {
        stream >> *this;
    }

    u32 PalettedContainer::read(int start, int offset)
    {
        u32 mask = (1 << m_palette->entryBits()) - 1;
        u32 val;
        if (start == m_data.size() - 1)
            val = m_data[start] >> offset;
        else
        {
            int endlong = start;

            // check if we flow over into the next long
            if (64 - offset < m_palette->entryBits())
                ++endlong;

            int endoffset = offset + m_palette->entryBits() % 64;

            val = m_data[start] >> offset | m_data[endlong] << endoffset;
        }

        return val & mask;
    }


    mcstream& operator>>(mcstream& stream, PalettedContainer& container)
    {
        // reading palette info
        u8 bitsPerEntry;
        stream >> bitsPerEntry;

        if (between(bitsPerEntry, 0, 4))
            container.m_palette = shared_ptr<Palette>(new IndirectPalette(4, stream));
        else if (between(bitsPerEntry, 5, 8))
            container.m_palette = shared_ptr<Palette>(new IndirectPalette(8, stream));
        else
            container.m_palette = shared_ptr<Palette>(new Palette(bitsPerEntry, stream));

        // reading long data
        varint numlongs;
        stream >> numlongs;
        container.m_data.resize(numlongs.val());
        for (int i = 0; i < numlongs.val(); ++i)
            stream >> container.m_data[i];

        return stream;
    }


    ChunkBlockPalettedContainer::ChunkBlockPalettedContainer(mcstream& stream)
        : PalettedContainer(stream)
    {
    }

    u32 ChunkBlockPalettedContainer::readBlockFromCoords(int x, int y, int z)
    {
        int blockNum = (((y * MC_CHUNK_HEIGHT) + z) * MC_CHUNK_WIDTH) + x;
        int start = (m_palette->entryBits() * blockNum) / 64;
        int offset = (m_palette->entryBits() * blockNum) % 64;
        return read(start, offset);
    }
}