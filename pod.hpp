#ifndef pod_hpp
#define pod_hpp

template <typename type_t>
struct pod
{
    type_t operator()()
    {
        type_t type;
        memset(&type, 0, sizeof(type_t));
        return type;
    }

    template <typename T1>
    type_t operator()(T1 t1)
    {
        type_t type = {t1};
        return type;
    }

    template <typename T1, typename T2>
    type_t operator()(T1 t1, T2 t2)
    {
        type_t type = {t1, t2};
        return type;
    }

    template <typename T1, typename T2, typename T3>
    type_t operator()(T1 t1, T2 t2, T3 t3)
    {
        type_t type = {t1, t2, t3};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4)
    {
        type_t type = {t1, t2, t3, t4};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
    {
        type_t type = {t1, t2, t3, t4, t5};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
    {
        type_t type = {t1, t2, t3, t4, t5, t6};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
    {
        type_t type = {t1, t2, t3, t4, t5, t6, t7};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
    {
        type_t type = {t1, t2, t3, t4, t5, t6, t7, t8};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
    {
        type_t type = {t1, t2, t3, t4, t5, t6, t7, t8, t9};
        return type;
    }
};

#endif
