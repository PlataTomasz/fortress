#if !defined(GAMEPLAY_TAGS_INCLUDED)
#define GAMEPLAY_TAGS_INCLUDED

#include <core/io/resource.h>

class GameplayTags : public Resource{
    PackedStringArray tags;

    PackedStringArray get_tags() {
        return tags;
    };

    void add_tag(const String &tag) {
        int pos = tags.find(tag);
        if(pos < 0) {
            tags.push_back(tag);
        }
        // Fail silently if exists
    }

    bool has_tag(const String &tag) {
        return tag.find(tag) >= 0;
    }

    void remove_tag(const String &tag) {
        tags.erase(tag);
    }

    operator PackedStringArray() {
        return tags;
    }
};

#endif // GAMEPLAY_TAGS_INCLUDED
