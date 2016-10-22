//
// Created by koncord on 29.08.16.
//

#ifndef OPENMW_PACKETCLASS_HPP
#define OPENMW_PACKETCLASS_HPP


#include <components/openmw-mp/Packets/PlayerPacket.hpp>

namespace mwmp
{
    class PacketClass : public PlayerPacket
    {
    public:
        PacketClass(RakNet::RakPeerInterface *peer);

        virtual void Packet(RakNet::BitStream *bs, BasePlayer *player, bool send);
    };
}


#endif //OPENMW_PACKETCLASS_HPP