extends LineEdit

@export var regex_string: String
var regex = RegEx.new()

func _init() -> void:
	var regex_compile_error = regex.compile("^[A-Za-z0-9_]{3,16}$")

func is_valid() -> bool:
	var regex_result: RegExMatch = regex.search(text)
	if(regex_result):
		return not regex_result.get_string().is_empty()
	else:
		return false
