extends Button

@export var content_area: Control
@export var panel_to_display: Control

func _on_pressed() -> void:
	content_area.change_currently_visible_element(panel_to_display)
