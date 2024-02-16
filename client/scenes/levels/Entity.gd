extends Entity

# Simple scripted entity, which moves over time
func _physics_process(delta):
	position += Vector3(1,0,1);
