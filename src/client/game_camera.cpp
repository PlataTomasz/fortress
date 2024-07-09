#include "game_camera.hpp"
#include <scene/3d/node_3d.h>
#include <core/math/vector3.h>
#include <shared/helper_macros.h>

#include <scene/main/viewport.h>

#include <core/input/input_event.h>

Vector3 GameCamera::CAMERA_OFFSET = Vector3(0, 10, 5);
Vector3 GameCamera::CAMERA_SPEED_VECTOR = Vector3(5, 0, 5);

GameCamera::GameCamera()
{

}

Vector3 GameCamera::screen_to_world(const Vector2& screen_pos) {
    
    //TODO: Project need to be used on camera node

    Vector3 rough_world_pos = project_position(screen_pos, 1000);
    Vector3 click_pos = project_ray_origin(screen_pos);

    double l = (rough_world_pos.x - click_pos.x);
    double m = (rough_world_pos.y - click_pos.y);
    double n = (rough_world_pos.z - click_pos.z);

    double world_x = click_pos.x - (click_pos.y/m)*l;
    double world_z = click_pos.z - (click_pos.y/m)*n;

    //y is zero because that doesn't matter
    return Vector3(world_x, 0, world_z);
}

void GameCamera::input(const Ref<InputEvent> &p_event) {
    if(p_event->is_action_pressed("camera_drag")) {
        _camera_drag = true;
        return;
    }
    if(p_event->is_action_released("camera_drag")) {
        _camera_drag = false;
        return;
    }
    // 1: Camera drag press stores position in variable
    // 2:
    /*
    if(p_event->is_action_pressed("camera_drag")) {
        if(p_event->is_action_pressed("camera_drag")) {

        }

        Vector2 new_camera_pos = drag_start_pos * (-1);
        // Mouse press to mouse release: Positions
        // Camera moves opposite way than mouse
    }
    */
    if(_camera_drag) {
        if(InputEventMouseMotion *mouse_motion_event = Object::cast_to<InputEventMouseMotion>(p_event.ptr())) {
            // Move camera in opposite direction
            /// FIXME: Add camera offset
            //print_line("MOUSE:", mouse_motion_event->get_position());
           
            // OLD
            //Vector3 new_camera_pos = (screen_to_world(mouse_motion_event->get_position()) / 10) + CAMERA_OFFSET;

            Viewport *default_viewport = get_viewport();
            ERR_FAIL_NULL(default_viewport);

            Vector2 mouse_pos_screen_centered = mouse_motion_event->get_position() - default_viewport->get_visible_rect().get_size()/2;
            Vector2 mouse_direction =  mouse_pos_screen_centered.normalized();


            // NEW
            //Vector3 new_camera_pos = screen_to_world(mouse_motion_event->get_position() + default_viewport->get_visible_rect().get_size()/2)/10 + CAMERA_OFFSET;

            const Vector3 curr_cam_pos = get_position();
            Vector3 new_camera_pos = Vector3(CAMERA_SPEED_VECTOR.x, 0, CAMERA_SPEED_VECTOR.z) * Vector3(mouse_direction.x, 1, mouse_direction.y)/10 + curr_cam_pos;

            print_line("MOUSE: ", mouse_motion_event->get_position());
            print_line("CAM:", new_camera_pos);

            set_position(new_camera_pos);
        }
        return;
    }
}

void GameCamera::_notification(int p_notification) {
    DISABLE_IN_EDITOR();
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        _init();
        break;

    case NOTIFICATION_PROCESS:
        _process_frame();
        break;
    
    default:
        break;
    }
}

void GameCamera::_on_tracked_node_exiting() {
    tracked_node = nullptr;
}

void GameCamera::_init() {
    set_rotation_degrees(Vector3(-45,0,0));
    set_position(CAMERA_OFFSET);
    set_process_input(true);
}

void GameCamera::set_tracked_node(Node3D* node)
{
    tracked_node = node;
}

void GameCamera::set_freecam(bool p_freecam)
{
    freecam = p_freecam;
}

void GameCamera::_process_frame()
{
    DISABLE_IN_EDITOR();

    //Camera behaviour
    /*
        - Free cam
        - Tracking entity
    */

    if(!freecam)
    {
        ERR_FAIL_NULL(tracked_node);
        //TODO: Check if Followed node is still valid
        if(tracked_node)
        {
            //printf("Followed node: %s\n", String(followedNode->get_name()).ascii().get_data());
            //TODO: Apply offset, so camera POV won't change upon 
            Vector3 camPos = this->get_position();
            Vector3 nodePos = tracked_node->get_position();
            /*
            camPos.x = nodePos.x+GameCamera::CAMERA_OFFSET.x;
            camPos.x = nodePos.y+GameCamera::CAMERA_OFFSET.y;
            camPos.z = nodePos.z+GameCamera::CAMERA_OFFSET.z;
            */
            this->set_position(camPos);
        }
    } else {
        // Freecam behaviour
        /*
            - Camera position can be modified with middle mouse button
        */
    }
}
