extends Entity

func _on_death(damage_object):
	self.visible = false

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	damageable_component.death.connect(_on_death)
