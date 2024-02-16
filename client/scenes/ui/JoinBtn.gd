extends Button

func _on_pressed():
	var client: Client = get_node("/root/Client")
	var ip_input: LineEdit = get_node("../IpInput")
	var nickname_input: LineEdit = get_node("../NickInput")
	
	# Validate nickname
	var ip_port: PackedStringArray = ip_input.get_text().split(":")
	var ip: String = ip_port[0]
	# Default port if not provided
	var port: int = ip_port[1] if ip_port[0].length() > 0 else 7654
	var err: Error = client.connect_to_game_server(ip, port)
	if err == OK:
		# Hide character seelction screen
		var char_select: Control = get_node("/root/Client/UserInterface/CharacterSelection")
		char_select.visible = false
	else:
		printerr("Connection to server failed with error code:", err)
