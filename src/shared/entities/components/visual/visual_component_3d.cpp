#include "visual_component_3d.h"

#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>

void VisualComponent3D::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_POSTINITIALIZE:
			_init();
			break;

		default:
			break;
	}
}

//Maybe use different replicator for components and status effects?
void VisualComponent3D::_init() {
	mesh_instance_3d = memnew(MeshInstance3D);
	mesh_instance_3d->set_name("Mesh");
	add_child(mesh_instance_3d);

	BoxMesh *mesh = memnew(BoxMesh);
	mesh_instance_3d->set_mesh(mesh);
}