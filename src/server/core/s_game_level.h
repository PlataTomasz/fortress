#if !defined(S_GAME_LEVEL_INCLUDED)
#define S_GAME_LEVEL_INCLUDED

#include <scene/3d/node_3d.h>

class S_GameLevel : public Node3D
{
GDCLASS(S_GameLevel, Node3D);
private:
	Node *entities_node;
protected:
public:
	TypedArray<S_BaseEntity> get_entities()
	{
		return entities_node->get_children();
	}

	S_GameLevel()
	{
		entities_node = memnew(Node);
		entities_node->set_name("Entities");
		add_child(entities_node);
	}
};

#endif // S_GAME_LEVEL_INCLUDED
