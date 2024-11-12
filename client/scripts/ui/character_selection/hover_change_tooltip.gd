extends TextureRect

var ability: Ability

@export var tooltip: AbilityTooltip

func _on_mouse_entered():
	if ability == null: return
	
	tooltip.ability_icon_display.texture = ability.icon
	tooltip.ability_name_display.text = ability.displayed_name
	tooltip.ability_description_display.text = ability.displayed_description

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	mouse_entered.connect(_on_mouse_entered)
