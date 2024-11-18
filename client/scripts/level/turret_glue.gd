extends Turret

@export var turret_crystal: Node3D

func _on_death(damage_object):
	turret_crystal.visible = false

func _ready():
	damageable_component.death.connect(_on_death)
