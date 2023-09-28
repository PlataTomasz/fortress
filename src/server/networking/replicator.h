#if !defined(ENTITY_REPLICATOR_INCLUDED)
#define ENTITY_REPLICATOR_INCLUDED

#include <core/variant/variant.h>
#include <core/templates/hash_map.h>
#include <scene/main/node.h>
#include <core/templates/list.h>
#include <modules/enet/enet_multiplayer_peer.h>

/**
 * Entity synchronization Node - Serverside
*/
class EntityReplicator : public Node
{
public:
    
private:
    uint64_t last_net_id = 0;

    //List of all peers that need full gamestate to be sent
    List<Ref<ENetMultiplayerPeer>> full_snaphot_peers;

    struct SyncedEntity
    {
        uint64_t net_id;
        Object* obj;
    };

    /**
     * Called every fixed tick. Synchronizes state of entities on clients, sending packets to all connected peers.
    */
    void synchronize_broadcast()
    {
        TypedArray<Node> node_children = get_children();
        
        //64KB packet buffer
        //TODO: Compress data in buffer
        uint8_t buffer[65565];
        //Current buffer size in bytes
        uint8_t buffer_size = sizeof(uint64_t);

        uint64_t *frame_count = reinterpret_cast<uint64_t*>(&buffer);
        //Put current physics frame count in the beggining of replication packet
        *frame_count = Engine::get_singleton()->get_physics_frames();        
        
        for(int i = 0;i < node_children.size();i++)
        {
            /*
            Iterate through all children to create one big packet to sync gamestate - need separator for each chunk

            Such packet includes only changes based on last gamestate delta, but when game starts or client suffers a huge packet loss, a full gamestate is sent to affected players 
            */
            //How much size is needed to synchronize specific node over network?




            //static_cast<Entity>(node_children[i].operator Object *())
        }
        

        //send_packet_to_all_peers(&buffer, buffer_size);

    }
    
protected:
    void _notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_PHYSICS_PROCESS: {
                synchronize_broadcast();
            } break;



            default:
                break;
        }
    }
public:
};

#endif // ENTITY_REPLICATOR_INCLUDED