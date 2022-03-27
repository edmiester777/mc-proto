#pragma once

#include "../../packet.h"
#include "../../states.h"
#include "../../../minecraft/types.h"

namespace minecraft
{
    class ChunkSection
    {
    public:
        ChunkSection(mcstream& stream);

        int numBlocks() const;
        const ChunkBlockPalettedContainer& chunkPalette() const;
        const PalettedContainer& biomePalette() const;

        friend mcstream& operator>>(mcstream& stream, ChunkSection& c);

    private:
        u16 m_numBlocks;
        ChunkBlockPalettedContainer m_blockPalette;
        PalettedContainer m_biomePalette;
    };

    class InboundChunkDataPacket : public Packet
    {
        PACKET_IMPL(InboundChunkDataPacket, States::PLAY, PlayPacketIds::I_CHUNK_DATA)
    public:
        /**
         * Chunk data packet.
         * 
         * @param stream stream from which to read packet
         * @param overworld flag signifies whether to load overworld specific flags
         */
        InboundChunkDataPacket(mcstream& stream, bool overworld);

        int chunkX() const;
        int chunkZ() const;
        int isFullChunk() const;
        sp<NBTCompoundTag> heightmaps() const;
        bool trustEdges() const;
        bitset skylightMask() const;
        bitset blockLightMask() const;
        bitset emptySkylightMask() const;
        bitset emptyBlockLightMask() const;
        vector<vector<u8>>& skylightArrays();
        vector<vector<u8>>& blockLightArrays();
        vector<Block>& blocks();


        string to_string() const override;

    private:
        int m_chunkX;
        int m_chunkZ;
        bool m_fullChunkData;
        sp<NBTCompoundTag> m_heightmaps;
        sp<ChunkSection> m_chunkSections[MC_NUM_VERTICAL_CHUNKS];
        bool m_trustEdges;
        bitset m_skylightMask;
        bitset m_blockLightMask;
        bitset m_emptySkylightMask;
        bitset m_emptyBlockLightMask;
        vector<vector<u8>> m_skylightArrays;
        vector<vector<u8>> m_blockLightArrays;
        vector<Block> m_blocks;
    };
}