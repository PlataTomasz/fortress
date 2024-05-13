#include "float_attribute.h"

void FloatAttribute::set_base(float new_base_value) {
    base = new_base_value;
    _recalculate();
}

float FloatAttribute::get_base() {
    return base;
}

FloatAttribute::FloatAttribute() {

}

void CappedFloatAttribute::set_min(float p_min) {
    min = p_min;
}

float CappedFloatAttribute::get_min() {
    return min;
}

void CappedFloatAttribute::set_max(float p_max) {
    max = p_max;
}

float CappedFloatAttribute::get_max() {
    return max;
}

float CappedFloatAttribute::get_current() {
    return CLAMP(current, min, max);
}

float CappedFloatAttribute::get_current_uncapped() {
    return current;
}


void FloatAttribute::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_base"), &FloatAttribute::get_base);
    ::ClassDB::bind_method(D_METHOD("set_base"), &FloatAttribute::set_base);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "base"), "set_base", "get_base");
}

void CappedFloatAttribute::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_current"), &CappedFloatAttribute::get_current);
    ::ClassDB::bind_method(D_METHOD("get_current_uncapped"), &CappedFloatAttribute::get_current_uncapped);

    ::ClassDB::bind_method(D_METHOD("get_min"), &CappedFloatAttribute::get_min);
    ::ClassDB::bind_method(D_METHOD("set_min", "p_min"), &CappedFloatAttribute::set_min);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min"), "set_min", "get_min");

    ::ClassDB::bind_method(D_METHOD("get_max"), &CappedFloatAttribute::get_max);
    ::ClassDB::bind_method(D_METHOD("set_max", "p_max"), &CappedFloatAttribute::set_max);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max"), "set_max", "get_max");
}

FloatAttribute::FloatAttribute(float p_base) {
    base = p_base;
    _recalculate();
}

CappedFloatAttribute::CappedFloatAttribute(float p_current, float p_min, float p_max) {
    current = p_current;
    min = p_min;
    max = p_max;
}

