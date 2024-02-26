extends Button	

@onready var client: Client = get_node("/root/Client")

func _ready():
	multiplayer.connect("connected_to_server", _on_connect_to_server)
	multiplayer.connect("server_disconnected", _on_disconnect_from_server)

func _on_pressed():
	var ip_input: LineEdit = get_node("../IpInput")
	var nickname_input: LineEdit = get_node("../NicknameInput")
	
	# Validate nickname
	var ip_port: PackedStringArray = ip_input.get_text().split(":")
	var ip: String = ip_port[0] if ip_port[0].length() > 0 else "localhost"
	# Default port if not provided
	var port: int = 7654
	if ip_port.size() > 1 and ip_port[1].length() > 0:
		port = int(ip_port[1])
		
	client.player.nickname = nickname_input.text
		
	var err: Error = client.connect_to_game_server("localhost", 7654)
	if err != OK:
		printerr("Connection to server failed with error code:", err)

func _on_connect_to_server():
	var char_select: Control = get_node("/root/Client/UserInterface/CharacterSelection")
	char_select.visible = false
	
func _on_disconnect_from_server():
	var char_select: Control = get_node("/root/Client/UserInterface/CharacterSelection")
	char_select.visible = true
