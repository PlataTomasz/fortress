#if !defined(TRAITS_INCLUDED)
#define TRAITS_INCLUDED

template <class F, class T, class R, class... P>
R (F::*method_pointer_fix(R (T::*p_method)(P...)))(P...) {
    return (R (F::*)(P...))p_method;
}

#endif // TRAITS_INCLUDED
