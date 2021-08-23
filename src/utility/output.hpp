#ifndef UTILITY_OUTPUT_HPP
#define UTILITY_OUTPUT_HPP

#include <ostream>
#include <tuple>
#include <type_traits>
#include <utility>

// whether OutputT type is callable std::operator(decltype(os), OutputT)
template<class OutputT
    , class CharT
    , class TraitsT>
auto isCallableOperator(std::basic_ostream<CharT, TraitsT> &os)
    -> decltype(std::operator <<(os, std::declval<OutputT>())
        , std::true_type{});
template<class>
auto isCallableOperator(...)
    -> decltype(std::false_type{});

// for container (using iterator)
template<class CharT
    , class TraitsT
    , class ContainerT>
auto operator <<(std::basic_ostream<CharT, TraitsT> &os
    , ContainerT &&container)
    -> decltype(container.begin()
        , container.end()
        , os);

// helper for contaner
template<class CharT
    , class TraitsT
    , class IterT>
std::basic_ostream<CharT, TraitsT>
    &containerHelper(std::basic_ostream<CharT, TraitsT> &os
        , IterT first
        , IterT last);

// std::pair
template<class CharT
    , class TraitsT
    , class FirstT
    , class SecondT>
std::basic_ostream<CharT, TraitsT>
    &operator <<(std::basic_ostream<CharT, TraitsT> &os
        , const std::pair<FirstT, SecondT> &pair);

// std::tuple
template<class CharT
    , class TraitsT
    , class ...TupleT>
std::basic_ostream<CharT, TraitsT>
    &operator <<(std::basic_ostream<CharT, TraitsT> &os
        , const std::tuple<TupleT...> &tuple);
// std::tuple (helper)
template<std::size_t Index = 0ull
    , class CharT
    , class TraitsT
    , class ...TupleT>
std::basic_ostream<CharT, TraitsT>
    &tupleHelper(std::basic_ostream<CharT, TraitsT> &os
        , const std::tuple<TupleT...> &tuple);

template<class CharT
    , class TraitsT
    , class ContainerT>
auto operator <<(std::basic_ostream<CharT, TraitsT> &os
    , ContainerT &&container)
    -> decltype(container.begin()
        , container.end()
        , os)
{
    if constexpr(decltype(isCallableOperator<ContainerT>(os))::value)
        return std::operator <<(os
            , container);
    else
        return containerHelper(os
            , container.begin()
            , container.end());
}

template<class CharT
    , class TraitsT
    , class IterT>
std::basic_ostream<CharT, TraitsT>
    &containerHelper(std::basic_ostream<CharT, TraitsT> &os
        , IterT first
        , IterT last)
{
    os << '{';

    bool isFirst{true};
    while(first != last)
    {
        if(!std::exchange(isFirst, false))
            os << ',';
        os << *first;

        first++;
    }

    os << '}';

    return os;
}

template<class CharT
    , class TraitsT
    , class FirstT
    , class SecondT>
std::basic_ostream<CharT, TraitsT>
    &operator <<(std::basic_ostream<CharT, TraitsT> &os
        , const std::pair<FirstT, SecondT> &pair)
{
    os << '{'
        << pair.first
        << ','
        << pair.second
        << '}';
    
    return os;
}

template<class CharT
    , class TraitsT
    , class ...TupleT>
std::basic_ostream<CharT, TraitsT>
    &operator <<(std::basic_ostream<CharT, TraitsT> &os
        , const std::tuple<TupleT...> &tuple)
{
    os << '{';

    if constexpr(std::tuple_size<std::tuple<TupleT...>>::value != 0ull)
        tupleHelper<0ull>(os, tuple);

    os << '}';

    return os;
}

template<std::size_t Index
    , class CharT
    , class TraitsT
    , class ...TupleT>
std::basic_ostream<CharT, TraitsT>
    &tupleHelper(std::basic_ostream<CharT, TraitsT> &os
        , const std::tuple<TupleT...> &tuple)
{
    os << std::get<Index>(tuple);

    if constexpr(Index + 1ull != std::tuple_size<std::tuple<TupleT...>>::value)
    {
        os << ',';
        tupleHelper<Index + 1ull>(os, tuple);
    }

    return os;
}

#endif