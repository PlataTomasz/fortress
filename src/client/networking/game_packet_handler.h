#if !defined(GAME_PACKET_HANDLER_INCLUDED)
#define GAME_PACKET_HANDLER_INCLUDED

#include <stdint.h>
#include <core/object/ref_counted.h>
#include <modules/enet/enet_packet_peer.h>

class GamePacketHandler
{
public:
    static void handle_game_packet(Ref<ENetPacketPeer> sender, const uint8_t *data, uint64_t size);
};

#endif // GAME_PACKET_HANDLER_INCLUDED
