extends Node

@export var client_scene: PackedScene
@export var server_scene: PackedScene

func load_shared_pck() -> void:
	var status = ProjectSettings.load_resource_pack("res://content.pck")
	if(!status):
		print("Failed to load content.pck!")
		get_tree().quit()

func _ready() -> void:
	load_shared_pck()
	
	if(ClassDB.class_exists("Server")):
		add_child(server_scene.instantiate())
	else:
		add_child(client_scene.instantiate())
