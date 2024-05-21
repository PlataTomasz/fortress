extends Node

# Called when the node enters the scene tree for the first time.
func _ready():
	var implementor: ExampleImplementor = ExampleImplementor.new()
	var implementor_user: ExampleInterfaceUser = ExampleInterfaceUser.new()
	
	implementor_user.connect_test_signal(implementor)
	implementor.example_interface_method()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
