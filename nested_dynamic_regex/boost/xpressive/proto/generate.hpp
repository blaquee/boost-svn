#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file generate.hpp
    /// Contains definition of generate\<\> class template, which end users can
    /// specialize for generating domain-specific expression wrappers.
    //
    //  Copyright 2004 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_GENERATE_HPP_EAN_02_13_2007
    #define BOOST_PROTO_GENERATE_HPP_EAN_02_13_2007

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/selection/max.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/matches.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {

        namespace detail
        {
            template<typename Domain, typename Expr>
            struct generate_if
              : lazy_enable_if<
                    matches<Expr, typename Domain::grammar>
                  , typename Domain::template apply<Expr>
                >
            {};

            // Optimization, generate fewer templates...
            template<typename Expr>
            struct generate_if<proto::default_domain, Expr>
            {
                typedef Expr type;
            };

            template<typename Expr>
            struct arity_;

            template<typename Tag, typename Args, long N>
            struct arity_<expr<Tag, Args, N> >
              : mpl::long_<N>
            {};

            template<typename Expr>
            struct tag_;

            template<typename Tag, typename Args, long N>
            struct tag_<expr<Tag, Args, N> >
            {
                typedef Tag type;
            };

            template<typename Expr>
            struct args_;

            template<typename Tag, typename Args, long N>
            struct args_<expr<Tag, Args, N> >
            {
                typedef Args type;
            };

            template<typename Expr, long Arity = detail::arity_<Expr>::value>
            struct by_value_generator_;

        #define BOOST_PROTO_DEFINE_BY_VALUE_TYPE(Z, N, Expr)\
            typename result_of::unref<typename args_<Expr>::type::BOOST_PP_CAT(arg, N) >::type

        #define BOOST_PROTO_DEFINE_BY_VALUE(Z, N, expr)\
            proto::unref(expr.BOOST_PP_CAT(arg, N))

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/generate.hpp>))
        #include BOOST_PP_ITERATE()

        #undef BOOST_PROTO_DEFINE_BY_VALUE
        #undef BOOST_PROTO_DEFINE_BY_VALUE_TYPE

        }

        namespace generatorns_
        {
            struct default_generator
            {
                template<typename Expr>
                struct apply
                {
                    typedef Expr type;
                };

                template<typename Expr>
                static Expr const &make(Expr const &expr)
                {
                    return expr;
                };
            };

            template<template<typename> class Extends>
            struct generator
            {
                template<typename Expr>
                struct apply
                {
                    typedef Extends<Expr> type;
                };

                template<typename Expr>
                static Extends<Expr> make(Expr const &expr)
                {
                    return Extends<Expr>(expr);
                }
            };

            template<template<typename> class Extends>
            struct pod_generator
            {
                template<typename Expr>
                struct apply
                {
                    typedef Extends<Expr> type;
                };

                template<typename Expr>
                static Extends<Expr> make(Expr const &expr)
                {
                    Extends<Expr> that = {expr};
                    return that;
                }
            };

            template<typename Generator>
            struct by_value_generator
            {
                template<typename Expr>
                struct apply
                  : Generator::template apply<
                        typename detail::by_value_generator_<Expr>::type
                    >
                {};

                template<typename Expr>
                static typename apply<Expr>::type make(Expr const &expr)
                {
                    return Generator::make(detail::by_value_generator_<Expr>::make(expr));
                }
            };
        }

    }}

    #endif // BOOST_PROTO_GENERATE_HPP_EAN_02_13_2007

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

            template<typename Expr>
            struct by_value_generator_<Expr, N>
            {
                typedef expr<
                    typename tag_<Expr>::type
                  , BOOST_PP_CAT(args, N)<
                        // typename result_of::unref<typename args_<Expr>::type::arg0>::type, ...
                        BOOST_PP_ENUM(BOOST_PP_MAX(N, 1), BOOST_PROTO_DEFINE_BY_VALUE_TYPE, Expr)
                    >
                > type;

                static type const make(Expr const &expr)
                {
                    type that = {
                        // proto::unref(expr.arg0), ...
                        BOOST_PP_ENUM(BOOST_PP_MAX(N, 1), BOOST_PROTO_DEFINE_BY_VALUE, expr)
                    };
                    return that;
                }
            };

    #undef N

#endif
