#include "chunkdata.h"

namespace minecraft
{
    ChunkSection::ChunkSection(mcstream& stream)
    {
        stream >> *this;
    }

    int ChunkSection::numBlocks() const
    {
        return m_numBlocks;
    }

    const ChunkBlockPalettedContainer& ChunkSection::chunkPalette() const
    {
        return m_blockPalette;
    }

    const PalettedContainer& ChunkSection::biomePalette() const
    {
        return m_biomePalette;
    }

    mcstream& operator>>(mcstream& stream, ChunkSection& c)
    {
        stream
            >> c.m_numBlocks
            >> c.m_blockPalette >> c.m_biomePalette;

        return stream;
    }


    InboundChunkDataPacket::InboundChunkDataPacket(mcstream& stream, bool overworld)
    {
        stream >> m_chunkX >> m_chunkZ;

        m_heightmaps = dynamic_pointer_cast<NBTCompoundTag>(read_nbt_from_stream(stream));
        
        // reading chunk column states
        varint len;
        stream >> len;
        for (int i = 0; i < MC_NUM_VERTICAL_CHUNKS; ++i)
        {
            m_chunkSections[i] = sp<ChunkSection>(new ChunkSection(stream));
        }

        // reading block entries
        stream >> len;
        m_blocks.resize(len.val());
        for (int i = 0; i < len.val(); ++i)
        {
            m_blocks[i] = Block(stream);
        }

        stream >> m_trustEdges;

        // skylight info is only sent to overworld
        if (overworld)
            stream >> m_skylightMask;
        stream >> m_blockLightMask;
        if (overworld)
            stream >> m_emptySkylightMask;
        stream >> m_emptyBlockLightMask;

        if (overworld)
        {
            stream >> len;
            m_skylightArrays.resize(len.val());

            for (int i = 0; i < len.val(); ++i)
            {
                stream >> len;
                vector<u8>& v = m_skylightArrays[i];
                v.resize(len.val());
                stream.read((char*)v.data(), len.val());
            }
        }

        stream >> len;
        m_blockLightArrays.resize(len.val());
        for (int i = 0; i < len.val(); ++i)
        {
            stream >> len;
            vector<u8>& v = m_blockLightArrays[i];
            v.resize(len.val());
            stream.read((char*)m_blockLightArrays.data(), len.val());
        }
    }

    int InboundChunkDataPacket::chunkX() const
    {
        return m_chunkX;
    }

    int InboundChunkDataPacket::chunkZ() const
    {
        return m_chunkZ;
    }

    int InboundChunkDataPacket::isFullChunk() const
    {
        return m_fullChunkData;
    }

    sp<NBTCompoundTag> InboundChunkDataPacket::heightmaps() const
    {
        return m_heightmaps;
    }

    bool InboundChunkDataPacket::trustEdges() const
    {
        return m_trustEdges;
    }

    bitset InboundChunkDataPacket::skylightMask() const
    {
        return m_skylightMask;
    }

    bitset InboundChunkDataPacket::blockLightMask() const
    {
        return m_blockLightMask;
    }

    bitset InboundChunkDataPacket::emptySkylightMask() const
    {
        return m_emptyBlockLightMask;
    }

    bitset InboundChunkDataPacket::emptyBlockLightMask() const
    {
        return m_emptyBlockLightMask;
    }

    vector<vector<u8>>& InboundChunkDataPacket::skylightArrays()
    {
        return m_skylightArrays;
    }

    vector<vector<u8>>& InboundChunkDataPacket::blockLightArrays()
    {
        return m_blockLightArrays;
    }

    vector<Block>& InboundChunkDataPacket::blocks()
    {
        return m_blocks;
    }

    string InboundChunkDataPacket::to_string() const
    {
        stringstream s;
        s << endl
            << "\tcolumn location: (" << m_chunkX << ", " << m_chunkZ << ")" << endl
            << "\ttrust edges: " << (m_trustEdges ? "true" : "false") << endl
            << "\tblock count: " << m_blocks.size() << endl
            << "\tsky light array count: " << m_skylightArrays.size() << endl
            << "\tblock light array count: " << m_blockLightArrays.size();

        for (int i = 0; i < m_blocks.size(); ++i)
        {
            s << m_blocks[i];
        }
        return s.str();
    }
}