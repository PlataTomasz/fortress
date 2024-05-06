#if !defined(TRAITS_INCLUDED)
#define TRAITS_INCLUDED

template <class F, class T, class R, class... P>
R (F::*method_pointer_fix(R (T::*p_method)(P...)))(P...) {
    return (R (F::*)(P...))p_method;
}

class ExampleTrait {
public:
    void exampleTraitMethod(){};

    template<class T>
    static void _bind_t_uses_abilities() {
        ::ClassDB::bind_method(D_METHOD("exampleTraitMethod"), method_pointer_fix<T>(&T::exampleTraitMethod));
    }
};

#endif // TRAITS_INCLUDED
