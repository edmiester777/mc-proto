#pragma once

#include "../inc.h"

namespace minecraft
{
    enum class BlockTypes;
    enum class BlockStates;

    /**
     * Implementation of https://wiki.vg/Chunk_Format#Paletted_Container_structure
     */
    class Palette
    {
    public:
        Palette(u8 entryBits, mcstream& stream);

        u8 entryBits() const;
        virtual BlockStates blockStateFromId(u32 id) const;

    private:
        u8 m_bitsPerEntry;
    };


    class IndirectPalette : public Palette
    {
    public:
        IndirectPalette(u8 entryBits, mcstream& stream);

        virtual BlockStates blockStateFromId(u32 id) const override;

    private:
        map<u32, BlockStates> m_idToStateMap;
    };

    /**
     * Note: this is underimplemented. We must read block state data from the
     *       bitset. I'll be implementing a true bitset later for ease of use.
     * 
     * TODO: finish implementation for state tracking.
     */
    class PalettedContainer
    {
    public:
        PalettedContainer(mcstream& stream);

        u32 read(int start, int offset);

        friend mcstream& operator>>(mcstream& stream, PalettedContainer& container);

    protected:
        shared_ptr<Palette> m_palette;

    private:
        vector<u64> m_data;
    };

    class ChunkBlockPalettedContainer : public PalettedContainer
    {
    public:
        ChunkBlockPalettedContainer(mcstream& stream);

        u32 readBlockFromCoords(int x, int y, int z);
    };
}