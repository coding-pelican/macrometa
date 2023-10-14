/**
 * @file mcmt.h
 * @brief Macrometa: Macro Metaprogramming (MCMT) Library for C
 * @version 0.1
 * @date 2023-10-10
 * @author Gyeongtae Kim (DevDasae, @coding-pelican) (codingpelican@gmail.com)
 * @copyright Copyright (c) 2023
 * @remark This library is a collection of macros aimed at enabling metaprogramming in C using the preprocessor.
 *        It was inspired by the article "C/C++ Preprocessor Metaprogramming" by Saad Ahmad
 *        (http://saadahmad.ca/cc-preprocessor-metaprogramming-2/) and the C preprocessor tricks, tips, and idioms
 *        mentioned in the article "C Preprocessor tricks, tips, and idioms"
 *        (https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms).
 *        For more information and updates, visit the GitHub repository at
 *        https://github.com/coding-pelican/macrometa.
 *
 * @remark This library is based on the C11 standard.
 */

/**
 * @mainpage Macrometa: Macro Metaprogramming (MCMT) Library for C
 *
 * @section intro Introduction
 * The Macrometa Macro Metaprogramming (MCMT) Library is designed to facilitate metaprogramming in C through the creative use of macros.
 * This library offers various macro-based tools and utilities to empower developers to achieve complex tasks and logic generation during compile-time.
 * MCMT is particularly useful for tasks that require repetitive code generation, type-safe macros, and conditional macro logic.
 *
 * @section sections Library Sections
 * The MCMT Library is organized into the following sections, each dedicated to a specific set of macro functionalities:
 *
 * - @ref mcmt_basic: Basic macros for handling empty arguments and expansions.
 * - @ref mcmt_concat: Macros for concatenating and manipulating identifiers.
 * - @ref mcmt_cat: Macros for complex identifier concatenation and deferring macro calls.
 * - @ref mcmt_macro_extn_impl_ovld: Macros for extending, implementing, and overloading generic macros.
 * - @ref mcmt_arg: Macros for manipulating and counting arguments.
 * - @ref mcmt_bit_logic: Macros for bitwise logic operations.
 * - @ref mcmt_logic: Macros for boolean and logical operations.
 * - @ref mcmt_list: Macros for handling lists and checking for emptiness.
 * - @ref mcmt_tuple: Macros for working with tuples and enclosed expressions.
 * - @ref mcmt_for_each: Macros for iterating through lists and applying operations.
 * - @ref mcmt_compare: Macros for comparing and checking the existence of macro arguments.
 * - @ref mcmt_arith: Macros for basic arithmetic operations.
 * - @ref mcmt_range: Macros for generating ranges of values.
 *
 * @section usage Usage Example
 * Below is a brief example of how to use the MCMT Library for simple metaprogramming operations:
 *
 * @code
 * #include "macrometa.h"
 * #include <stdio.h>
 *
 * // Define a macro to square a number.
 * #define SQUARE(x) MUL(x, x)
 *
 * int main() {
 *     int result = SQUARE(5); // Expands to 25 at compile-time.
 *     printf("Square: %d\n", result);
 *     return 0;
 * }
 * @endcode
 *
 * This is just a small glimpse of what MCMT can do. You can explore various sections of the library to enhance your metaprogramming capabilities in C.
 */

#ifndef MCMT_H
#define MCMT_H

/**********************************
 * MCMT_BASIC_H
 * @brief Macros for Basic Metaprogramming Operations.
 *********************************/
#pragma region mcmt_basic

/**
 * @brief Expands to nothing.
 */
#define EMPTY()

/**
 * @brief Removes arguments.
 * @param ... Arguments to be removed.
 */
#define IGNORE(...)

/**
 * @brief Expands arguments.
 * @param ... Arguments to be expanded.
 */
#define EXPAND(...)       EXPAND_LIMIT(__VA_ARGS__)
#define EXPAND0(...)      __VA_ARGS__
#define EXPAND1(...)      EXPAND0(__VA_ARGS__)
#define EXPAND2(...)      EXPAND1(EXPAND1(__VA_ARGS__))
#define EXPAND3(...)      EXPAND2(EXPAND2(__VA_ARGS__))
#define EXPAND4(...)      EXPAND3(EXPAND3(__VA_ARGS__))
#define EXPAND5(...)      EXPAND4(EXPAND4(__VA_ARGS__))
#define EXPAND6(...)      EXPAND5(EXPAND5(__VA_ARGS__))
#define EXPAND7(...)      EXPAND6(EXPAND6(__VA_ARGS__))
#define EXPAND_LIMIT(...) EXPAND7(EXPAND7(__VA_ARGS__))

/**
 * @brief Expands to a comma.
 */
#define COMMA(...) ,

#define ENCLOSE(...)        (__VA_ARGS__)
#define UNCLOSE_UNEVAL(...) __VA_ARGS__
#define UNCLOSE(...)        UNCLOSE_UNEVAL __VA_ARGS__

#pragma endregion // mcmt_basic
/*-------------------------------*/

/**********************************
 * MCMT_CONCAT_H
 * @brief Macros for concatenating and manipulating identifiers.
 **********************************/
#pragma region mcmt_concat

/**
 * @brief Concatenate two tokens.
 * @param _X First token.
 * @param _Y Second token.
 * @return Concatenation of the two tokens.
 */
#define CONCAT(_X, _Y) CONCAT_UNEVAL(_X, _Y)

/**
 * @brief Concatenate three tokens.
 * @param _X First token.
 * @param _Y Second token.
 * @param _Z Third token.
 * @return Concatenation of the three tokens.
 */
#define CONCAT3(_X, _Y, _Z)         CONCAT3_UNEVAL(_X, _Y, _Z)
#define CONCAT4(_X, _Y, _Z, _W)     CONCAT4_UNEVAL(_X, _Y, _Z, _W)
#define CONCAT5(_X, _Y, _Z, _W, _V) CONCAT5_UNEVAL(_X, _Y, _Z, _W, _V)
#define CONCAT_VA(_Arg, ...)        CONCAT_VA_UNEVAL(_Arg, __VA_ARGS__)

#define PRIM_CONCAT(_X, _Y) _X##_Y
#if defined(_MSC_VER)
#    define CONCAT_RETURN(EXPANDED, _XY)       _XY
#    define CONCAT_UNEVAL(_X, _Y)              CONCAT_RETURN(~, _X##_Y)
#    define CONCAT3_UNEVAL(_X, _Y, _Z)         CONCAT_RETURN(~, _X##_Y##_Z)
#    define CONCAT4_UNEVAL(_X, _Y, _Z, _W)     CONCAT_RETURN(~, _X##_Y##_Z##_W)
#    define CONCAT5_UNEVAL(_X, _Y, _Z, _W, _V) CONCAT_RETURN(~, _X##_Y##_Z##_W##_V)
#    define CONCAT_VA_RETURN(EXPANDED, ...)    __VA_ARGS__
#    define CONCAT_VA_UNEVAL(_Arg, ...)        CONCAT_VA_RETURN(~, _Arg##__VA_ARGS__)
#else // !MSVC workarounds
#    define CONCAT_UNEVAL(_X, _Y)              _X##_Y
#    define CONCAT3_UNEVAL(_X, _Y, _Z)         _X##_Y##_Z
#    define CONCAT4_UNEVAL(_X, _Y, _Z, _W)     _X##_Y##_Z##_W
#    define CONCAT5_UNEVAL(_X, _Y, _Z, _W, _V) _X##_Y##_Z##_W##_V
#    define CONCAT_VA_UNEVAL(_Arg, ...)        _Arg##__VA_ARGS__
#endif // defined(_MSC_VER)

#pragma endregion // mcmt_concat
/*-------------------------------*/

/**********************************
 * MCMT_CAT_H
 * @brief Macros for complex identifier concatenation and deferring macro calls.
 *********************************/
#pragma region mcmt_cat

/* different flavors of CAT */
#define CAT_WITH(_X, EXPANDED, _METHOD, _Y) CAT_WITH_##_METHOD(_X, _Y)
#define CAT_WITH_ENCLOSED(_X, _Y)           _X _Y
#define CAT_WITH_DEFAULT(_X, _Y)            _X##_Y

/* defer call to CAT_WITH until args are evaluated */
#define ENCLOSE_EXPAND(...) EXPANDED, ENCLOSED, (__VA_ARGS__))IGNORE(
#define GET_CAT_EXP(_X, _Y)  (_X, ENCLOSE_EXPAND _Y, DEFAULT, _Y)
#define EXPAND_CAT_WITH(...) CAT_WITH __VA_ARGS__

/* complex concatenate */
#define CAT(_X, _Y)  EXPAND_CAT_WITH(GET_CAT_EXP(_X, _Y))
#define CAT_(_X, _Y) EXPAND_CAT_WITH(GET_CAT_EXP(_X, CONCAT(_, _Y)))

#pragma endregion // mcmt_cat
/*-------------------------------*/

/**********************************
 * MCMT_MACRO_EXTN_IMPL_OVLD_H
 * @brief Macros for extending, implementing, and overloading generic macros
 *********************************/
#pragma region mcmt_macro_extn_impl_ovld

#define MACRO_EXTN(_MCR, _EXTS)                               MACRO_EXTN_UNEVAL(_MCR, _EXTS)
#define MACRO_IMPL(_MCR)                                      MACRO_IMPL_UNEVAL(_MCR)
#define MACRO_IMPL_OVERLOAD(_MCR_Suffixed)                    MACRO_IMPL_OVERLOAD_UNEVAL(_MCR_Suffixed)
#define MACRO_IMPL_OVERLOAD_UNARY(_MCR_Suffixed, _OVLS)       MACRO_IMPL_OVERLOAD_UNARY_UNEVAL(_MCR_Suffixed, _OVLS)
#define MACRO_IMPL_OVERLOAD_BINARY(_MCR_Suffixed, _OVLS, _OP) MACRO_IMPL_OVERLOAD_BINARY_UNEVAL(_MCR_Suffixed, _OVLS, _OP)
#define OPER_EXTN(_OP, _EXTS)                                 OPER_EXTN_UNEVAL(_OP, _EXTS)
#define OPER_IMPL(_OP)                                        OPER_IMPL_UNEVAL(_OP)
#define OPER_IMPL_OVERLOAD(_OP_Suffixed)                      OPER_IMPL_OVERLOAD_UNEVAL(_OP_Suffixed)
#define OPER_IMPL_OVERLOAD_UNARY(_OP_Suffixed, _operand)      OPER_IMPL_OVERLOAD_UNARY_UNEVAL(_OP_Suffixed, _operand)
#define OPER_IMPL_OVERLOAD_BINARY(_OP_Suffixed, _lhs, _rhs)   OPER_IMPL_OVERLOAD_BINARY_UNEVAL(_OP_Suffixed, _lhs, _rhs)

#if defined(_MSC_VER)
#    define MACRO_EXTN_UNEVAL(_MCR, _EXTS)                               CONCAT_RETURN(~, _MCR##_##_EXTS)
#    define MACRO_IMPL_UNEVAL(_MCR)                                      CONCAT_RETURN(~, __##_MCR)
#    define MACRO_IMPL_OVERLOAD_UNEVAL(_MCR_Suffixed)                    CONCAT_RETURN(~, __##_MCR_Suffixed)
#    define MACRO_IMPL_OVERLOAD_UNARY_UNEVAL(_MCR_Suffixed, _OVLS)       CONCAT_RETURN(~, __##_MCR_Suffixed##_OVLS)
#    define MACRO_IMPL_OVERLOAD_BINARY_UNEVAL(_MCR_Suffixed, _OVLS, _OP) CONCAT_RETURN(~, __##_MCR_Suffixed##_##_OVLS##_##_OP)
#    define OPER_EXTN_UNEVAL(_OP, _EXTS)                                 CONCAT_RETURN(~, _OP##_##_EXTS)
#    define OPER_IMPL_UNEVAL(_OP)                                        CONCAT_RETURN(~, __##_OP)
#    define OPER_IMPL_OVERLOAD_UNEVAL(_OP_Suffixed)                      CONCAT_RETURN(~, __##_OP_Suffixed)
#    define OPER_IMPL_OVERLOAD_UNARY_UNEVAL(_OP_Suffixed, _operand)      CONCAT_RETURN(~, __##_OP_Suffixed##_operand)
#    define OPER_IMPL_OVERLOAD_BINARY_UNEVAL(_OP_Suffixed, _lhs, _rhs)   CONCAT_RETURN(~, __##_OP_Suffixed##_lhs##_rhs)
#else // !MSVC workarounds
#    define MACRO_EXTN_UNEVAL(_MCR, _EXTS)                               _MCR##_##_EXTS
#    define MACRO_IMPL_UNEVAL(_MCR)                                      __##_MCR
#    define MACRO_IMPL_OVERLOAD_UNEVAL(_MCR_Suffixed)                    __##_MCR_Suffixed
#    define MACRO_IMPL_OVERLOAD_UNARY_UNEVAL(_MCR_Suffixed, _OVLS)       __##_MCR_Suffixed##_OVLS
#    define MACRO_IMPL_OVERLOAD_BINARY_UNEVAL(_MCR_Suffixed, _OVLS, _OP) __##_MCR_Suffixed##_##_OVLS##_##_OP
#    define OPER_EXTN_UNEVAL(_OP, _EXTS)                                 _OP##_##_EXTS
#    define OPER_IMPL_UNEVAL(_OP)                                        __##_OP
#    define OPER_IMPL_OVERLOAD_UNEVAL(_OP_Suffixed)                      __##_OP_Suffixed
#    define OPER_IMPL_OVERLOAD_UNARY_UNEVAL(_OP_Suffixed, _operand)      __##_OP_Suffixed##_operand
#    define OPER_IMPL_OVERLOAD_BINARY_UNEVAL(_OP_Suffixed, _lhs, _rhs)   __##_OP_Suffixed##_lhs##_rhs
#endif // defined(_MSC_VER)

#pragma endregion // mcmt_macro_extn_impl_ovld
/*-------------------------------*/

/**********************************
 * MCMT_ARG_H
 * @brief Macros for Handling Arguments.
 *********************************/
#pragma region mcmt_arg

/******** extracts fst, snd, trd args ********/
#pragma region extracts_fst_snd_trd_args

/**
 * @brief Extracts the first argument from a list of arguments.
 * @param _fst The first argument.
 * @param ... The rest of the arguments (ignored).
 * @return The first argument.
 * @details This macro extracts and returns the first argument, `_fst`, from a list of arguments.
 * For example, if used as `FST(a, b, c)`, it will result in `_fst` being `a`.
 */
#define FST(_fst, ...) _fst

/**
 * @brief Extracts the second argument from a list of arguments.
 * @param fst The first argument (ignored).
 * @param _snd The second argument.
 * @param ... The rest of the arguments (ignored).
 * @return The second argument.
 * @details This macro extracts and returns the second argument, `_snd`, from a list of arguments.
 * For example, if used as `SND(a, b, c)`, it will result in `_snd` being `b`.
 */
#define SND(fst, _snd, ...) _snd

/**
 * @brief Extracts the third argument from a list of arguments.
 * @param fst The first argument (ignored).
 * @param snd The second argument (ignored).
 * @param _trd The third argument.
 * @param ... The rest of the arguments (ignored).
 * @return The third argument.
 * @details This macro extracts and returns the third argument, `_trd`, from a list of arguments.
 * For example, if used as `TRD(a, b, c, d)`, it will result in `_trd` being `c`.
 */
#define TRD(fst, snd, _trd, ...) _trd

/**
 * @brief Combines the first and second arguments into a comma-separated list.
 * @param _fst The first argument.
 * @param _snd The second argument.
 * @param ... The rest of the arguments (ignored).
 * @return A comma-separated list of the first and second arguments.
 * @details This macro combines the first and second arguments, `_fst` and `_snd`, into a comma-separated list.
 * For example, if used as `FST_SND(a, b, c)`, it will result in `_fst, _snd` being `a, b`.
 */
#define FST_SND(_fst, _snd, ...) _fst, _snd

/**
 * @brief Combines the second and third arguments into a comma-separated list.
 * @param fst The first argument (ignored).
 * @param _snd The second argument.
 * @param _trd The third argument.
 * @param ... The rest of the arguments (ignored).
 * @return A comma-separated list of the second and third arguments.
 * @details This macro combines the second and third arguments, `_snd` and `_trd`, into a comma-separated list.
 * For example, if used as `SND_TRD(a, b, c, d)`, it will result in `_snd, _trd` being `b, c`.
 */
#define SND_TRD(fst, _snd, _trd, ...) _snd, _trd

/**
 * @brief Combines the first and third arguments into a comma-separated list.
 * @param _fst The first argument.
 * @param snd The second argument (ignored).
 * @param _trd The third argument.
 * @param ... The rest of the arguments (ignored).
 * @return A comma-separated list of the first and third arguments.
 * @details This macro combines the first and third arguments, `_fst` and `_trd`, into a comma-separated list.
 * For example, if used as `FST_TRD(a, b, c, d)`, it will result in `_fst, _trd` being `a, c`.
 */
#define FST_TRD(_fst, snd, _trd, ...) _fst, _trd

/**
 * @brief Combines the first, second, and third arguments into a comma-separated list.
 * @param _fst The first argument.
 * @param _snd The second argument.
 * @param _trd The third argument.
 * @param ... The rest of the arguments (ignored).
 * @details This macro combines the first, second, and third arguments, `_fst`, `_snd`, and `_trd`, into a comma-separated list.
 * For example, if used as `FST_SND_TRD(a, b, c, d)`, it will result in `_fst, _snd, _trd` being `a, b, c`.
 */
#define FST_SND_TRD(_fst, _snd, _trd, ...) _fst, _snd, _trd

#pragma endregion // extracts_fst_snd_trd_args
/*------- extracts fst, snd, trd args -------*/

/******** extracts_fst_snd_trd_rest_args ********/
#pragma region extracts_fst_snd_trd_rest_args

/**
 * @brief Extracts the rest of the arguments after the first argument.
 * @param fst The first argument (ignored).
 * @param ... The rest of the arguments.
 * @return The rest of the arguments, excluding the first one.
 * @details This macro extracts and returns the rest of the arguments after the first argument.
 * For example, if used as `FST_REST(a, b, c)`, it will result in `(b, c)`.
 */
#define FST_REST(fst, ...) __VA_ARGS__

/**
 * @brief Extracts the rest of the arguments after the second argument.
 * @param _fst The first argument.
 * @param snd The second argument (ignored).
 * @param ... The rest of the arguments.
 * @return The rest of the arguments, excluding the second one.
 * @details This macro extracts and returns the rest of the arguments after the second argument.
 * For example, if used as `SND_REST(a, b, c, d)`, it will result in `(a, c, d)`.
 */
#define SND_REST(_fst, snd, ...) _fst, __VA_ARGS__

/**
 * @brief Extracts the rest of the arguments after the third argument.
 * @param _fst The first argument.
 * @param _snd The second argument.
 * @param trd The third argument (ignored).
 * @param ... The rest of the arguments.
 * @return The rest of the arguments, excluding the third one.
 * @details This macro extracts and returns the rest of the arguments after the third argument.
 * For example, if used as `TRD_REST(a, b, c, d, e)`, it will result in `(a, b, d, e)`.
 */
#define TRD_REST(_fst, _snd, trd, ...) _fst, _snd, __VA_ARGS__

/**
 * @brief Extracts the rest of the arguments after the first two arguments.
 * @param fst The first argument (ignored).
 * @param snd The second argument (ignored).
 * @param ... The rest of the arguments.
 * @return The rest of the arguments, excluding the first two.
 * @details This macro extracts and returns the rest of the arguments after the first two arguments.
 * For example, if used as `FST_SND_REST(a, b, c, d, e)`, it will result in `(c, d, e)`.
 */
#define FST_SND_REST(fst, snd, ...) __VA_ARGS__

/**
 * @brief Extracts the rest of the arguments after the second and third arguments.
 * @param _fst The first argument.
 * @param snd The second argument (ignored).
 * @param trd The third argument (ignored).
 * @param ... The rest of the arguments.
 * @return The rest of the arguments, excluding the second and third ones.
 * @details This macro extracts and returns the rest of the arguments after the second and third arguments.
 * For example, if used as `SND_TRD_REST(a, b, c, d, e, f)`, it will result in `(a, d, e, f)`.
 */
#define SND_TRD_REST(_fst, snd, trd, ...) _fst, __VA_ARGS__

/**
 * @brief Extracts the rest of the arguments after the first and third arguments.
 * @param fst The first argument (ignored).
 * @param _snd The second argument.
 * @param trd The third argument (ignored).
 * @param ... The rest of the arguments.
 * @return The rest of the arguments, excluding the first and third ones.
 * @details This macro extracts and returns the rest of the arguments after the first and third arguments.
 * For example, if used as `TRD_FST_REST(a, b, c, d, e, f)`, it will result in `(b, d, e, f)`.
 */
#define FST_TRD_REST(fst, _snd, trd, ...) _snd, __VA_ARGS__

/**
 * @brief Extracts the rest of the arguments after the first two arguments.
 * @param fst The first argument (ignored).
 * @param snd The second argument (ignored).
 * @param trd The third argument (ignored).
 * @param ... The rest of the arguments.
 * @return The rest of the arguments, excluding the first two.
 * @details This macro extracts and returns the rest of the arguments after the first two arguments.
 * For example, if used as `FST_SND_TRD_REST(a, b, c, d, e, f)`, it will result in `(d, e, f)`.
 */
#define FST_SND_TRD_REST(fst, snd, trd, ...) __VA_ARGS__

#pragma endregion // extracts_fst_snd_trd_rest_args
/*------- extracts_fst_snd_trd_rest_args -------*/

/******** MCMT_ARG_COUNT_H ********/
/**
 * @brief Macros for counting the number of arguments.
 */
#pragma region mcmt_arg_count

// TODO(DevDasae): Implement COUNT_OPT, Research recursive parameter counting methods
/**
 * @brief Counts the number of arguments in a variadic argument list.
 * @param ... The variadic arguments.
 * @details This macro counts the number of arguments provided in a variadic argument list and returns the count as an integer.
 * It uses a clever technique that leverages a recursive macro to count the arguments.
 * For example, if used as `COUNT(a, b, c)`, it will result in `3`.
 */
#define COUNT(...) COUNT_UNEVAL(__VA_ARGS__, COUNT_INV_SEQ_N())
/**
 * @brief Helper macro to count the number of arguments in a variadic argument list.
 * @param ... The variadic arguments.
 * @details This macro is not meant to be used directly. It is used internally by `COUNT(...)`.
 */
#define COUNT_UNEVAL(...) COUNT_CHECK(__VA_ARGS__)
/**
 * @brief Helper macro to count the number of arguments in a variadic argument list.
 * @param __128, __127, ... The numbered arguments.
 * @details This macro is not meant to be used directly. It is used internally to generate the argument count.
 */
#define COUNT_CHECK(__128, __127, __126, __125, __124, __123, __122, __121, __120, __119, __118, __117, __116, __115, __114, __113, __112, __111, __110, __109, __108, __107, __106, __105, __104, __103, __102, __101, __100, __99, __98, __97, __96, __95, __94, __93, __92, __91, __90, __89, __88, __87, __86, __85, __84, __83, __82, __81, __80, __79, __78, __77, __76, __75, __74, __73, __72, __71, __70, __69, __68, __67, __66, __65, __64, __63, __62, __61, __60, __59, __58, __57, __56, __55, __54, __53, __52, __51, __50, __49, __48, __47, __46, __45, __44, __43, __42, __41, __40, __39, __38, __37, __36, __35, __34, __33, __32, __31, __30, __29, __28, __27, __26, __25, __24, __23, __22, __21, __20, __19, __18, __17, __16, __15, __14, __13, __12, __11, __10, __9, __8, __7, __6, __5, __4, __3, __2, __1, __N, ...) __N
/**
 * @brief Generates a sequence of arguments for argument counting.
 * @details This macro generates a sequence of arguments for argument counting.
 * It is used internally by the `COUNT` macro.
 */
#define COUNT_INV_SEQ_N() \
    128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, vararg when given 1

#pragma endregion // mcmt_arg_count
/*------- MCMT_ARG_COUNT_H -------*/

#define REPLACE_REST(...) __VA_ARGS__) IGNORE(
#define REPLACE_REST_TO_ENCLOSED(_ArgsEnclosed) UNCLOSE(_ArgsEnclosed)) IGNORE(

#pragma endregion // mcmt_arg
/*--------------------------------*/

/**********************************
 * MCMT_RECUR_H
 *********************************/
#pragma region mcmt_recur

/******** MCMT_RECUR_DEFER_H ********/
#pragma region mcmt_recur_defer

/**
 * @brief Defer macro expansion of its arguments.
 * @param ... The arguments to be deferred.
 * @details The DEFER macro is designed to defer the expansion of its arguments. It effectively delays the expansion of
 * the provided arguments, allowing them to be evaluated later in the preprocessing phase. This is particularly useful
 * for controlling the order of macro expansions and solving issues related to macro ordering.
 *
 * The DEFER macro is used in conjunction with other macros,
 * such as `RECUR`, `EVAL`, `IF - (Conditional Branch Closures)`to manage the sequence of macro evaluations.
 * For example, you can use them as follows:
 * Part of the definition of the `ADD` Recursive function:
 * @code
 * #define ADD_UNEVAL(_A, _N) \
 *   IF( IS_NOT_ZERO(_N) ) ( DEFER2( ADD_INDIRECT )()( INC(_A), DEC(_N) ), _A )
 * @endcode
 * When passed as a parameter:
 * @code
 * TRY_EXTRACT_EXISTS( DEFER( LIST_HEAD )( __VA_ARGS__ EXISTS(1) ), 0 )
 * @endcode
 */
#define DEFER(...)  __VA_ARGS__ EMPTY()
#define DEFER1(...) __VA_ARGS__ EMPTY()

/**
 * @brief Defer macro expansion twice.
 * @param ... The arguments to be deferred twice.
 * @details To defer expansion twice, the DEFER2 macro adds an additional deferred EMPTY() call. This allows for further
 * control over the order of macro expansions and can be useful in scenarios where precise sequencing is required.
 */
#define DEFER2(...) __VA_ARGS__ DEFER(EMPTY)()
#define DEFER3(...) __VA_ARGS__ DEFER2(EMPTY)()
#define DEFER4(...) __VA_ARGS__ DEFER3(EMPTY)()
#define DEFER5(...) __VA_ARGS__ DEFER4(EMPTY)()
#define DEFER6(...) __VA_ARGS__ DEFER5(EMPTY)()
#define DEFER7(...) __VA_ARGS__ DEFER6(EMPTY)()
#define DEFER8(...) __VA_ARGS__ DEFER7(EMPTY)()

#pragma endregion // mcmt_recur_defer
/*------- MCMT_RECUR_DEFER_H -------*/

/******** MCMT_RECUR_EVAL_H ********/
#pragma region mcmt_recur_eval_h

/**
 * @brief The top-level EVAL macro.
 * @param ... The arguments to be repeatedly expanded.
 * @return The result of multiple evaluations of the arguments.
 * @details The EVAL macro calls EVAL_LIMIT, which limits the number of recursive expansions to a predefined level.
 * This top-level macro provides a convenient way to apply multiple evaluations to a set of arguments without the need to
 * manually specify the recursion depth.
 */
#define EVAL(...)  EVAL_LIMIT(__VA_ARGS__)
#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(__VA_ARGS__)
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL3(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL4(...) EVAL3(EVAL3(__VA_ARGS__))
#define EVAL5(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL6(...) EVAL5(EVAL5(__VA_ARGS__))
#define EVAL7(...) EVAL6(EVAL6(__VA_ARGS__))

/**
 * @brief EVAL is a recursive macro that expands its arguments multiple times.
 * @param ... The arguments to be repeatedly expanded.
 * @return The result of multiple evaluations of the arguments.
 * @details EVAL is a macro designed for recursive expansion of its arguments. When EVAL is called, it repeatedly expands
 * its arguments using a lower-level EVAL macro, effectively doubling the number of expansions with each recursion level.
 * This allows for 2^n evaluations of an expression, where n is the number of times EVAL is nested.
 *
 * The EVAL macro is a powerful tool for achieving multiple levels of macro expansion, enabling advanced metaprogramming
 * techniques in C. However, it's important to be cautious with its usage, as excessive recursion can lead to long
 * compilation times or even compilation errors.
 *
 * The maximum number of possible evaluations depends on the number of nested EVAL calls. In the provided code, EVAL_LIMIT
 * is defined to limit the number of recursive expansions to eight levels. You can increase or decrease this limit
 * according to your specific needs, but be mindful of the potential impact on compilation performance.
 */
#define EVAL_LIMIT(...) EVAL7(EVAL7(__VA_ARGS__))
// #define EVAL_LIMIT(...) EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(__VA_ARGS__))))))))

#pragma endregion // mcmt_recur_eval_h
/*------- MCMT_RECUR_EVAL_H -------*/

/**
 * @brief Recursively expands its arguments and displays expansion results sequentially.
 * @param ... The arguments to be expanded recursively.
 * @details This macro is used for recursive expansion of its arguments. It repeatedly expands its arguments
 * and sequentially displays the expansion results according to the evaluation level. Each level of expansion
 * results is separated by numbers to indicate the evaluation level.
 * For example, if used as `RECUR(MACRO)`, it will display the expansion results as follows:
 * 1)   MACRO RECUR_INDIRECT ()(MACRO)
 * 1-1) MACRO RECUR_UNEVAL(MACRO)
 * 2)   MACRO MACRO RECUR_INDIRECT ()(MACRO)
 * 2-1) MACRO MACRO RECUR_UNEVAL(MACRO)
 * 3)   MACRO MACRO MACRO RECUR_INDIRECT ()(MACRO)
 * ...
 */
#define RECUR(...) EVAL(RECUR_UNEVAL(__VA_ARGS__))

/**
 * @brief Helper macro for recursive expansion.
 * @param ... The arguments to be expanded recursively.
 * @details This macro is used internally by `RECUR` to provide the recursive expansion functionality.
 * It expands its arguments and incorporates `DEFER(RECUR_INDIRECT)()` to ensure proper sequencing of
 * the expansion results for each level.
 * This the same as #define RECUR(x) x DEFER(RECUR_INDIRECT) () (x)
 * -> #define RECUR_UNEVAL(x)         x RECUR_INDIRECT EMPTY()()(x)
 */
#define RECUR_UNEVAL(...) __VA_ARGS__ DEFER(RECUR_INDIRECT)()(__VA_ARGS__)

/**
 * @brief Indirect macro for recursive expansion.
 * @details This macro is used internally by `RECUR` and `RECUR_UNEVAL` to create an indirect recursive call.
 * It ensures that the recursive expansion process can continue and maintains the sequencing of expansion results
 * for each level.
 */
#define RECUR_INDIRECT() RECUR_UNEVAL

#pragma endregion // mcmt_recur
/*-------------------------------*/

/*********************************
 * MCMT_BIT_LOGIC_H
 *********************************/
#pragma region mcmt_bit_logic

/* bit logic */
#define BIT_TRUE(...)  1
#define BIT_FALSE(...) 0

#define BIT_CMPL(_bit)      OPER_IMPL_OVERLOAD_UNARY_UNEVAL(BIT_CMPL_, _bit)
#define __BIT_CMPL_0        1
#define __BIT_CMPL_1        0
#define BIT_NOT(_bit)       OPER_IMPL_OVERLOAD_UNARY_UNEVAL(BIT_NOT_, _bit)
#define __BIT_NOT_0         1
#define __BIT_NOT_1         0
#define BIT_AND(_p, _q)     OPER_IMPL_OVERLOAD_BINARY_UNEVAL(BIT_AND_, _p, _q)
#define __BIT_AND_00        0
#define __BIT_AND_01        0
#define __BIT_AND_10        0
#define __BIT_AND_11        1
#define BIT_OR(_p, _q)      OPER_IMPL_OVERLOAD_BINARY_UNEVAL(BIT_OR_, _p, _q)
#define __BIT_OR_00         0
#define __BIT_OR_01         1
#define __BIT_OR_10         1
#define __BIT_OR_11         1
#define BIT_XOR(_p, _q)     OPER_IMPL_OVERLOAD_BINARY_UNEVAL(BIT_XOR_, _p, _q)
#define __BIT_XOR_00        0
#define __BIT_XOR_01        1
#define __BIT_XOR_10        1
#define __BIT_XOR_11        0
#define BIT_BOOL_EQ(_p, _q) OPER_IMPL_OVERLOAD_BINARY_UNEVAL(BIT_BOOL_EQ_, _p, _q)
#define __BIT_BOOL_EQ_00    1
#define __BIT_BOOL_EQ_01    0
#define __BIT_BOOL_EQ_10    0
#define __BIT_BOOL_EQ_11    1

/* if-statement: falseClause is optional */
#define BIT_IF(_condBit, _trueClause, ...)     OPER_IMPL_OVERLOAD_UNARY_UNEVAL(BIT_IF_, _condBit)(_trueClause, __VA_ARGS__)
#define __BIT_IF_0(trueClause, ...)            __VA_ARGS__
#define __BIT_IF_1(_trueClause, ...)           _trueClause
#define BIT_IF_NOT(_condBit, _trueClause, ...) OPER_IMPL_OVERLOAD_UNARY_UNEVAL(BIT_IF_NOT_, _condBit)(_trueClause, __VA_ARGS__)
#define __BIT_IF_NOT_0(_trueClause, ...)       _trueClause
#define __BIT_IF_NOT_1(trueClause, ...)        __VA_ARGS__

#pragma endregion // mcmt_bit_logic
/*-------------------------------*/

/*********************************
 * MCMT_LOGIC_H
 *********************************/
#pragma region mcmt_logic

/* probe */
#define IS_PROBE(...) SND(__VA_ARGS__, 0)
#define PROBE()       ~, 1

/* not */
#define NOT(_value) IS_PROBE(OPER_IMPL_OVERLOAD_UNARY_UNEVAL(NOT_, _value))
#define __NOT_0     PROBE()

/* boolean */
#define BOOL(_value) BIT_CMPL(NOT(_value))

// TODO(DevDasae): Research IF structures for code readability
/* if-statement: falseClause is optional */
#define IF(_cond)     OPER_IMPL_OVERLOAD_UNARY(BIT_IF_, BOOL(_cond))
#define IF_NOT(_cond) OPER_IMPL_OVERLOAD_UNARY(BIT_IF_NOT_, BOOL(_cond))

#define WHEN(_pred)   IF(_pred)(UNCLOSE, IGNORE)
#define UNLESS(_pred) IF_NOT(_pred)(UNCLOSE, IGNORE)

/******** exist_testing_macro ********/
#pragma region exist_testing_macro

/* test if the value is an existing macro */
#define PATTERN_MATCH_EXISTS(...)  EXPANDED, EXISTS(__VA_ARGS__)) IGNORE(
#define GET_PATTERN_EXISTS_RESULT(_EXISTS) (PRIM_CONCAT(PATTERN_MATCH_, _EXISTS), DOESNT_EXIST)

/* extract the 2nd field in the tuple */
#define GET_PATTERN_EXIST_VALUE_EXPANDER(EXPANDED, _existValue) _existValue
#define GET_PATTERN_EXIST_VALUE(_resultPair)                    GET_PATTERN_EXIST_VALUE_EXPANDER _resultPair
#define EXISTS_PATTERN(_value) \
    GET_PATTERN_EXIST_VALUE(GET_PATTERN_EXISTS_RESULT(_value))

/* return 1 if exists, otherwise 0 */
#define DOES_VALUE_EXIST(_EXISTS)       OPER_IMPL_OVERLOAD_UNARY_UNEVAL(DOES_VALUE_EXIST_, _EXISTS)
#define __DOES_VALUE_EXIST_DOESNT_EXIST 0
#define __DOES_VALUE_EXIST_EXISTS(...)  1

/* extract x from EXIST(x) */
#define EXTRACT_VALUE(_value)       OPER_IMPL_OVERLOAD_UNARY_UNEVAL(EXTRACT_VALUE_, _value)
#define __EXTRACT_VALUE_EXISTS(...) __VA_ARGS__

/* extract value if exists, otherwise return given default value */
#define TRY_EXTRACT_EXISTS(value, ...)          \
    IF(DOES_VALUE_EXIST(EXISTS_PATTERN(value))) \
    (                                           \
        EXTRACT_VALUE(value), __VA_ARGS__       \
    )

#pragma endregion // exist_testing_macro
/*------- exist_testing_macro -------*/

/******** boolean_operations ********/
#pragma region boolean_operations

#define BOOL_OPER_OVERLOAD_UNARY(_OP_Suffixed, _x, _default)      TRY_EXTRACT_EXISTS(OPER_IMPL_OVERLOAD_UNARY_UNEVAL(_OP_Suffixed, _x), _default)
#define BOOL_OPER_OVERLOAD_BINARY(_OP_Suffixed, _x, _y, _default) TRY_EXTRACT_EXISTS(OPER_IMPL_OVERLOAD_BINARY_UNEVAL(_OP_Suffixed, _x, _y), _default)

#define AND(x, y) BOOL_OPER_OVERLOAD_BINARY(AND_, x, y, 0)
#define __AND_11  EXISTS(1)

#define OR(x, y) BOOL_OPER_OVERLOAD_BINARY(OR_, x, y, 1)
#define __OR_00  EXISTS(0)

#define XOR(x, y) BOOL_OPER_OVERLOAD_BINARY(XOR_, x, y, 0)
#define __XOR_01  EXISTS(1)
#define __XOR_10  EXISTS(1)

#define IS_ZERO(x)     BOOL_OPER_OVERLOAD_UNARY(IS_ZERO_, x, 0)
#define __IS_ZERO_0    EXISTS(1)
#define IS_NOT_ZERO(x) NOT(IS_ZERO(x))

#define IS_ONE(_x)     BOOL_OPER_OVERLOAD_UNARY(IS_ONE_, x, 0)
#define __IS_ONE_1     EXISTS(1)
#define IS_NOT_ONE(_x) NOT(IS_ONE(_x))

#pragma endregion // boolean_operations
/*------- boolean_operations -------*/

#pragma endregion // mcmt_logic
/*-------------------------------*/

/*********************************
 * MCMT_LIST_H
 *********************************/
#pragma region mcmt_list

#define LIST_HEAD(_arg, ...) _arg
#define LIST_TAIL(arg, ...)  __VA_ARGS__

#define IS_EMPTY(...)                            \
    TRY_EXTRACT_EXISTS(                          \
        DEFER(LIST_HEAD)(__VA_ARGS__ EXISTS(1)), \
        0                                        \
    )

#define IS_NOT_EMPTY(...) \
    NOT(IS_EMPTY(__VA_ARGS__))


#pragma endregion // mcmt_list
/*-------------------------------*/

/*********************************
 * MCMT_TUPLE_H
 *********************************/
#pragma region mcmt_tuple

/* test if arguments is enclosed in parentheses */
#define IS_ENCLOSED(_x, ...) TRY_EXTRACT_EXISTS(TEST_ENCLOSED _x, 0)
#define TEST_ENCLOSED(...)   EXISTS(1)

// TODO(DevDasae): Apply BIT_IF
#define IF_ENCLOSED(...)                  OPER_IMPL_OVERLOAD_UNARY(IF_ENCLOSED_, IS_ENCLOSED(__VA_ARGS__))
#define __IF_ENCLOSED_0(trueClause, ...)  __VA_ARGS__
#define __IF_ENCLOSED_1(_trueClause, ...) _trueClause

#define UNCLOSE_OPT(...)      \
    IF_ENCLOSED(__VA_ARGS__)  \
    (                         \
        UNCLOSE(__VA_ARGS__), \
        __VA_ARGS__           \
    )

#pragma endregion // mcmt_tuple
/*-------------------------------*/

/*********************************
 * MCMT_FOR_EACH_H
 *********************************/
#pragma region mcmt_for_each

// TODO(DevDasae): Refactor this parts
/* 1D */
#define FOR_EACH(_OP, ...) EVAL(FOR_EACH_UNEVAL(_OP, __VA_ARGS__))
#define FOR_EACH_UNEVAL(_OP, ...)                                                                                \
    IF(IS_NOT_EMPTY(__VA_ARGS__))                                                                                \
    (                                                                                                            \
        DEFER(_OP)(UNCLOSE_OPT(LIST_HEAD(__VA_ARGS__))) DEFER2(FOR_EACH_INDIRECT)()(_OP, LIST_TAIL(__VA_ARGS__)) \
    )
#define FOR_EACH_INDIRECT() FOR_EACH_UNEVAL

/* 2D */
#define FOR_EACH_2D(_OP, _List1, _List2)        EVAL(FOR_EACH_2D_UNEVAL(_OP, _List1, _List2))
#define FOR_EACH_2D_UNEVAL(_OP, _List1, _List2) __FOR_EACH_2D(_OP, _List1, _List1, _List2, _List2)
#define __FOR_EACH_2D(_OP, _List1, _OriginList1, _List2, _OriginList2)                                                                 \
    IF(IS_NOT_EMPTY _List2)                                                                                                            \
    (                                                                                                                                  \
        _OP(LIST_HEAD _List1, LIST_HEAD _List2) DEFER2(FOR_EACH_2D_INDIRECT)()(_OP, _List1, _List1, (LIST_TAIL _List2), _OriginList2), \
        IF(IS_NOT_EMPTY(LIST_TAIL _List1))(                                                                                            \
            DEFER3(FOR_EACH_2D_INDIRECT)()(_OP, (LIST_TAIL _OriginList1), (LIST_TAIL _OriginList1), _OriginList2, _OriginList2)        \
        )                                                                                                                              \
    )
#define FOR_EACH_2D_INDIRECT() __FOR_EACH_2D

/* 3D */
#define FOR_EACH_3D(_OP, _List1, _List2, _List3)        EVAL(FOR_EACH_3D_UNEVAL(_OP, _List1, _List2, _List3))
#define FOR_EACH_3D_UNEVAL(_OP, _List1, _List2, _List3) __FOR_EACH_3D_UNEVAL(_OP, _List1, _List1, _List2, _List2, _List3, _List3)
#define __FOR_EACH_3D_UNEVAL(_OP, _List1, _OriginList1, _List2, _OriginList2, _List3, _OriginList3)                                                                      \
    IF(IS_NOT_EMPTY _List3)                                                                                                                                              \
    (                                                                                                                                                                    \
        _OP(LIST_HEAD _List1, LIST_HEAD _List2, LIST_HEAD _List3) DEFER2(FOR_EACH_3D_INDIRECT)()(_OP, _List1, _List1, _List2, _List2, (LIST_TAIL _List3), _OriginList3), \
        IF(IS_NOT_EMPTY(LIST_TAIL _List2))(                                                                                                                              \
            DEFER3(FOR_EACH_3D_INDIRECT)()(_OP, _OriginList1, _OriginList1, (LIST_TAIL _OriginList2), (LIST_TAIL _OriginList2), _OriginList3, _OriginList3)              \
                IF(IS_NOT_EMPTY(LIST_TAIL _List1))(                                                                                                                      \
                    DEFER4(FOR_EACH_3D_INDIRECT)()(                                                                                                                      \
                        _OP, (LIST_TAIL _OriginList1), (LIST_TAIL _OriginList1), _OriginList2, _OriginList2, _OriginList3, _OriginList3                                  \
                    )                                                                                                                                                    \
                )                                                                                                                                                        \
        )                                                                                                                                                                \
    )
#define FOR_EACH_3D_INDIRECT() __FOR_EACH_3D_UNEVAL

#pragma endregion // mcmt_for_each
/*-------------------------------*/

/*********************************
 * MCMT_COMPARE_H
 *********************************/
#pragma region mcmt_compare

// TODO(DevDasae): Consider applying other CATs
#define NOT_COMPARABLE(_p, _q)                   \
    IS_ENCLOSED(                                 \
        CAT_(COMPARE, _p)(CAT_(COMPARE, _q))(()) \
    )

#define IS_COMPARABLE(_p)     \
    IS_ENCLOSED(              \
        CAT_(COMPARE, _p)(()) \
    )

/*
 * The 'NOT_EQUALS' operation requires a 'COMPARE_{arg}(_x) _x' macro function for each argument. ex) COMPARE_foo(_x) _x, COMPARE_bar(_x) _x
 */
#define NOT_EQUALS(_p, _q)                            \
    IF(BIT_AND(IS_COMPARABLE(_p), IS_COMPARABLE(_q))) \
    (                                                 \
        NOT_COMPARABLE,                               \
        1 IGNORE                                      \
    )(_p, _q)

/*
 * The 'EQUALS' operation requires a 'COMPARE_{arg}(_x) _x' macro function for each argument. ex) COMPARE_foo(_x) _x, COMPARE_bar(_x) _x
 */
#define EQUALS(_p, _q) BIT_CMPL(NOT_EQUALS(_p, _q))

#pragma endregion // mcmt_compare
/*-------------------------------*/

/*********************************
 * MCMT_ARITH_H
 *********************************/
#pragma region mcmt_arith

/******** MCMT_ARITH_BASIC_H ********/
#pragma region mcmt_arith_basic

// TODO(DevDasae): Implement return of actual integer literal for N{number}
// NOTE: Does this project require implementing unsigned operations or operations with negative ranges?

/* increase */
#define INC(_N) OPER_IMPL_OVERLOAD_UNARY_UNEVAL(INC_, _N)

/* decrease */
#define DEC(_N) OPER_IMPL_OVERLOAD_UNARY_UNEVAL(DEC_, _N)

#pragma endregion // mcmt_arith_basic
/*------- MCMT_ARITH_BASIC_H -------*/

/**
 * Q: Why are the EVALs below redefined even though they already exist?
 * A: We've found that when macros that use loops/recursion are nested,
 * i.e. when a parent recursive macro contains a child recursive macro that uses an EVAL to return a result,
 * the parent EVAL extension of the EVAL level being used by the child recursive macro must be defined separately.
 *
 * If the parent recursive macro and the child recursive macro use the same level of EVAL, you will see the following result.
 * `EVAL(EVAL(EVAL(EVAL(EVAL(EVAL(EVAL(...({return value})...)`
 */

#define ARITH_L0_EVAL(...)       ARITH_L0_EVAL_LIMIT(__VA_ARGS__)
#define ARITH_L0_EVAL0(...)      __VA_ARGS__
#define ARITH_L0_EVAL1(...)      ARITH_L0_EVAL0(__VA_ARGS__)
#define ARITH_L0_EVAL2(...)      ARITH_L0_EVAL1(ARITH_L0_EVAL1(__VA_ARGS__))
#define ARITH_L0_EVAL3(...)      ARITH_L0_EVAL2(ARITH_L0_EVAL2(__VA_ARGS__))
#define ARITH_L0_EVAL4(...)      ARITH_L0_EVAL3(ARITH_L0_EVAL3(__VA_ARGS__))
#define ARITH_L0_EVAL5(...)      ARITH_L0_EVAL4(ARITH_L0_EVAL4(__VA_ARGS__))
#define ARITH_L0_EVAL6(...)      ARITH_L0_EVAL5(ARITH_L0_EVAL5(__VA_ARGS__))
#define ARITH_L0_EVAL7(...)      ARITH_L0_EVAL6(ARITH_L0_EVAL6(__VA_ARGS__))
#define ARITH_L0_EVAL_LIMIT(...) ARITH_L0_EVAL7(ARITH_L0_EVAL7(__VA_ARGS__))

#define ARITH_L1_EVAL(...)       ARITH_L1_EVAL_LIMIT(__VA_ARGS__)
#define ARITH_L1_EVAL0(...)      __VA_ARGS__
#define ARITH_L1_EVAL1(...)      ARITH_L1_EVAL0(__VA_ARGS__)
#define ARITH_L1_EVAL2(...)      ARITH_L1_EVAL1(ARITH_L1_EVAL1(__VA_ARGS__))
#define ARITH_L1_EVAL3(...)      ARITH_L1_EVAL2(ARITH_L1_EVAL2(__VA_ARGS__))
#define ARITH_L1_EVAL4(...)      ARITH_L1_EVAL3(ARITH_L1_EVAL3(__VA_ARGS__))
#define ARITH_L1_EVAL5(...)      ARITH_L1_EVAL4(ARITH_L1_EVAL4(__VA_ARGS__))
#define ARITH_L1_EVAL6(...)      ARITH_L1_EVAL5(ARITH_L1_EVAL5(__VA_ARGS__))
#define ARITH_L1_EVAL7(...)      ARITH_L1_EVAL6(ARITH_L1_EVAL6(__VA_ARGS__))
#define ARITH_L1_EVAL_LIMIT(...) ARITH_L1_EVAL7(ARITH_L1_EVAL7(__VA_ARGS__))

#define ARITH_L2_EVAL(...)       ARITH_L2_EVAL_LIMIT(__VA_ARGS__)
#define ARITH_L2_EVAL0(...)      __VA_ARGS__
#define ARITH_L2_EVAL1(...)      ARITH_L2_EVAL0(__VA_ARGS__)
#define ARITH_L2_EVAL2(...)      ARITH_L2_EVAL1(ARITH_L2_EVAL1(__VA_ARGS__))
#define ARITH_L2_EVAL3(...)      ARITH_L2_EVAL2(ARITH_L2_EVAL2(__VA_ARGS__))
#define ARITH_L2_EVAL4(...)      ARITH_L2_EVAL3(ARITH_L2_EVAL3(__VA_ARGS__))
#define ARITH_L2_EVAL5(...)      ARITH_L2_EVAL4(ARITH_L2_EVAL4(__VA_ARGS__))
#define ARITH_L2_EVAL6(...)      ARITH_L2_EVAL5(ARITH_L2_EVAL5(__VA_ARGS__))
#define ARITH_L2_EVAL7(...)      ARITH_L2_EVAL6(ARITH_L2_EVAL6(__VA_ARGS__))
#define ARITH_L2_EVAL_LIMIT(...) ARITH_L2_EVAL7(ARITH_L2_EVAL7(__VA_ARGS__))

#define ARITH_L3_EVAL(...)       ARITH_L3_EVAL_LIMIT(__VA_ARGS__)
#define ARITH_L3_EVAL0(...)      __VA_ARGS__
#define ARITH_L3_EVAL1(...)      ARITH_L3_EVAL0(__VA_ARGS__)
#define ARITH_L3_EVAL2(...)      ARITH_L3_EVAL1(ARITH_L3_EVAL1(__VA_ARGS__))
#define ARITH_L3_EVAL3(...)      ARITH_L3_EVAL2(ARITH_L3_EVAL2(__VA_ARGS__))
#define ARITH_L3_EVAL4(...)      ARITH_L3_EVAL3(ARITH_L3_EVAL3(__VA_ARGS__))
#define ARITH_L3_EVAL5(...)      ARITH_L3_EVAL4(ARITH_L3_EVAL4(__VA_ARGS__))
#define ARITH_L3_EVAL6(...)      ARITH_L3_EVAL5(ARITH_L3_EVAL5(__VA_ARGS__))
#define ARITH_L3_EVAL7(...)      ARITH_L3_EVAL6(ARITH_L3_EVAL6(__VA_ARGS__))
#define ARITH_L3_EVAL_LIMIT(...) ARITH_L3_EVAL7(ARITH_L3_EVAL7(__VA_ARGS__))

/* add */
#define ADD(_A, _N) ARITH_L0_EVAL(ADD_UNEVAL(_A, _N))
#define ADD_UNEVAL(_A, _N)                        \
    IF(IS_NOT_ZERO(_N))                           \
    (                                             \
        DEFER2(ADD_INDIRECT)()(INC(_A), DEC(_N)), \
        _A                                        \
    )
#define ADD_INDIRECT() ADD_UNEVAL

/* subtract */
#define SUB(_A, _N) ARITH_L0_EVAL(SUB_UNEVAL(_A, _N))
#define SUB_UNEVAL(_A, _N)                        \
    IF(IS_NOT_ZERO(_N))                           \
    (                                             \
        DEFER2(SUB_INDIRECT)()(DEC(_A), DEC(_N)), \
        _A                                        \
    )
#define SUB_INDIRECT() SUB_UNEVAL

/* multiply */
#define MUL(_A, _N) ARITH_L1_EVAL(MUL_UNEVAL(_A, _N, 0))
#define MUL_UNEVAL(_A, _N, _SUM)       \
    IF(IS_NOT_ZERO(_COUNT))            \
    (                                  \
        DEFER2(MUL_INDIRECT)()(        \
            _A, DEC(_N), ADD(_SUM, _A) \
        ),                             \
        _SUM                           \
    )
#define MUL_INDIRECT() MUL_UNEVAL

/* divide */
#define DIV(_A, _N) ARITH_L1_EVAL(DIV_UNEVAL(_A, _N, 0, _A)) /* ARITH_L1_EVAL defines QUOTIENT range */
#define DIV_UNEVAL(_A, _N, _QUOTIENT, _REMAINDER)       \
    IF(IS_NOT_ZERO(_REMAINDER))                         \
    (                                                   \
        DEFER2(DIV_INDIRECT)()(                         \
            _A, _N, INC(_QUOTIENT), SUB(_REMAINDER, _N) \
        ),                                              \
        _QUOTIENT                                       \
    )
#define DIV_INDIRECT() DIV_UNEVAL

/* binominal */
#define BINOM(_N, _K) ARITH_L2_EVAL(BINOM_UNEVAL(_N, _K, 1, 1)) /* ARITH_L2_EVAL defines max K */
#define BINOM_UNEVAL(_N, _K, _NUMER, _DENOM)                   \
    IF(IS_NOT_ZERO(_K))                                        \
    (                                                          \
        DEFER2(BINOM_INDIRECT)()(                              \
            DEC(_N), DEC(_K), MUL(_NUMER, _N), MUL(_DENOM, _K) \
        ),                                                     \
        DIV(_NUMER, _DENOM)                                    \
    )
#define BINOM_INDIRECT() BINOM_UNEVAL

#pragma endregion // mcmt_arith
/*-------------------------------*/

/*********************************
 * MCMT_RANGE_H
 *********************************/
#pragma region mcmt_range

#define OUTPUT_RANGE_VAL(_x) _x,

#define RANGE(_start, _end, _step)        EVAL2(RANGE_UNEVAL(_start, _end, _step))
#define RANGE_UNEVAL(_start, _end, _step) __RANGE_UNEVAL(_start, _end, _step) _end
#define __RANGE_UNEVAL(_start, _end, _step)                                                \
    IF(IS_NOT_ZERO(SUB(_end, _start)))                                                     \
    (                                                                                      \
        OUTPUT_RANGE_VAL(_start) DEFER2(RANGE_INDIRECT)()(ADD(_start, _step), _end, _step) \
    )
#define RANGE_INDIRECT() __RANGE_UNEVAL

#pragma endregion // mcmt_range
/*-------------------------------*/

#endif // !MCMT_H
