#include "ui_controler.h"
#include <shared/entities/entity.h>

void UIController::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY:
			_ready();
			break;

		default:
			break;
	}
}

void UIController::_ready() {
    //Hook into the level entities
    Node *entities = get_node_or_null(NodePath("/root/Client/Game/Level/Entities"));
    ERR_FAIL_NULL_MSG(entities, "Hooking into Level/Entities failed!");

    entities->connect("child_entered_tree", callable_mp(this, &UIController::_on_new_entity_entered));
}

void UIController::_enter_tree() {
}

//Spawns healthbar for new entities
void UIController::_on_new_entity_entered(Node *node) {
    Entity *ent = static_cast<Entity *>(node);
    //DamageableComponent *damageable = ent->get_component<DamageableComponent>();
}

void UIController::_on_entity_leave(Node *node) {
    Entity *ent = static_cast<Entity *>(node);

}