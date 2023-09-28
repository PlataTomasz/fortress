extends Button


# Called when the node enters the scene tree for the first time.
func _ready():
	connect("button_down", connect_to_server)

func connect_to_server():
	var mAPI: MultiplayerAPI = MultiplayerAPI.create_default_interface()
	var enet_multiplayer_peer: ENetMultiplayerPeer = ENetMultiplayerPeer.new()
	enet_multiplayer_peer.create_client("localhost", 7654)
	mAPI.multiplayer_peer = enet_multiplayer_peer
	get_tree().set_multiplayer(mAPI, "/App/Client")
	
		

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
