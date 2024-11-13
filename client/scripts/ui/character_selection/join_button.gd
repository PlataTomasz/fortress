extends Button

@export var nickname_input: LineEdit
@export var address_input: LineEdit
@export var character_select_btn_group: ButtonGroup 

var current_character_button: BaseButton

func set_enabled(enabled: bool):
	disabled = !enabled

func are_inputs_valid():
	var bool1: bool = nickname_input.is_valid()
	var bool2: bool = current_character_button != null
	return bool1 and bool2
	#address_input.is_valid() and 

func _on_nickname_changed(new_nickname: String):
	set_enabled(are_inputs_valid())
	
func _on_address_changed(new_address: String):
	set_enabled(are_inputs_valid())
	
func _on_character_button_pressed(btn: BaseButton):
	current_character_button = btn
	set_enabled(are_inputs_valid())
	
func _ready() -> void:
	nickname_input.text_changed.connect(_on_nickname_changed)
	#address_input.text_changed.connect(_on_address_changed)
	character_select_btn_group.pressed.connect(_on_character_button_pressed)
