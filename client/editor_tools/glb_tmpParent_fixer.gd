
## Prepare a Scene for MeshLibrary export
## Full workflow:
## - Copy a bunch of glb file in a folder of the project
## - Let Godot 4 auto import run
## - Create an empty 3D Scene
## - Drag&drop imported assets on root Node3D, or in 3D view (location is irrelevant)
## - save scene (or the script will not find it)
## - With this scene active, open this script and run it (Ctrl+Shift+X)
##   Scene will be modified!
## - Scene > Export As > MeshLibrary

## See https://github.com/godotengine/godot-proposals/issues/3406 for context

## Edit: this code expects a glb structure which is actually not the result of the Godot glb importer,
## but present in the assets it was developped for. So adaptations may be required for other assets.

## License: MIT No Attribution (MIT-0)

@tool
extends EditorScript

# Going a little overboard with sanity checks,
# but I want to understand what is happening if this fails in the future
func _run():
	var scene_root := get_scene()
	if scene_root == null:
		printerr("No currently active scene")
		return

	print("Current scene is %s" % scene_root.scene_file_path)

	if !(scene_root is Node3D):
		printerr("Root node must be a Node3D")
		return

	for entry in scene_root.get_children():
		var name := entry.name
		print("Processing %s from %s" % [name, entry.scene_file_path])

		if !(entry is Node3D):
			printerr("Processed node must be a Node3D")
			return

		if entry.get_child_count() != 1:
			printerr("Processed node should have exactly one child")
			return
		
		var tmpParent := entry.get_child(0)

		if !(tmpParent is Node3D):
			printerr("tmpParent node must be a Node3D")
			return
		
		var transform := (tmpParent as Node3D).transform
		if !(transform.is_equal_approx(Transform3D.IDENTITY)):
			# Not sure if possible, but possibly depends on glb structure?
			printerr("tmpParent transform should be identity")
			return

		if tmpParent.get_child_count() != 1:
			printerr("tmpParent node should have exactly one child")
			return

		var mesh := tmpParent.get_child(0)
		if !(mesh is MeshInstance3D):
			printerr("mesh node must be a MeshInstance3D")
			return
		
		# Move mesh under root node
		tmpParent.remove_child(mesh)
		scene_root.add_child(mesh)
		mesh.owner = scene_root
		
		# Remove undeeded scene instance
		scene_root.remove_child(entry)
		
		# Rename mesh node
		mesh.name = name

	print("Script completed without error, scene exportable to MeshLibrary")
