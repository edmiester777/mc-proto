#include "../../packet.h"
#include "../../states.h"
#include "../../../minecraft/entitytypes.h"

namespace minecraft
{
    class InboundSpawnExperienceOrbPacket : public Packet
    {
        PACKET_IMPL(InboundSpawnExperienceOrbPacket, States::PLAY, PlayPacketIds::I_SPAWN_EXPERIENCE_ORB)
    public:
        InboundSpawnExperienceOrbPacket(mcstream& stream);

        EntityMetadataType entityType() const;
        double x() const;
        double y() const;
        double z() const;
        int16_t count() const;

        string to_string() const override;

        friend mcstream& operator>>(mcstream& stream, InboundSpawnExperienceOrbPacket& p);

    private:
        EntityMetadataType m_entityType;
        double m_x;
        double m_y;
        double m_z;
        int16_t m_count;
    };
}