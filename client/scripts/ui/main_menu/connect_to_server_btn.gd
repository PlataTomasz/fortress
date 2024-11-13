extends Button

@export var content_area: Control
@export var panel_to_display: Control
@export var client: Client

func _on_pressed() -> void:
	content_area.change_currently_visible_element(panel_to_display)

func _on_player_disconnected(player: Player) -> void:
	visible = false
	
func _on_player_connected(player: Player) -> void:
	visible = true
	
func _ready() -> void:
	client.player_connected.connect(_on_player_connected)
	client.player_disconnected.connect(_on_player_disconnected)
