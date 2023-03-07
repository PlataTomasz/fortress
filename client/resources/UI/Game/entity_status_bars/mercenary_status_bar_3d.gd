extends EntityStatusBar3D


# Called when the node enters the scene tree for the first time.
func _ready():
	get_parent().connect("health_changed", on_hp_change)
	pass # Replace with function body.

func on_hp_change():
	print("xdd")

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
