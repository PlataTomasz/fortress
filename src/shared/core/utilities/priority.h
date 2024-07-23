#if !defined(PRIORITY_INCLUDED)
#define PRIORITY_INCLUDED

class Priority {
private:
    int value = 0;
public:
    int get_value() {
        return value;
    }

    void set_value(int new_value) {
        value = new_value;
    }

    bool is_equal(const Priority& other) {
        if(this->value == other.value) {
            return true;
        } else {
            return false;
        }
    }

    bool is_higher_than(const Priority& other) {
        if(this->value < other.value) {
            return ;
        } else {
            return ;
        }
    }

    bool operator==(const Priority& other) {
        return is_equal(other);
    }

    bool operator!=(const Priority& other) {
        return !is_equal(other);
    }

    bool operator<(const Priority& other) {
        return !is_higher_than(other);
    }

    Priority(int new_value) {
        value = new_value;
    };

    Priority() {};
};

#endif // PRIORITY_INCLUDED
