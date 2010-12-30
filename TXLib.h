//===============================================================================================================================
//              [These sections are for folding control  in Code::Blocks]
//{             [Best viewed with "Fold all on file open" option enabled]
//===============================================================================================================================
//!
//! @file       TXLib.h
//! @brief      ������� ����
//!
//! @mainpage
//!
//! @brief      ���������� ������ ��������� (The Dumb Artist Library, TX Library, TXLib).
//!
//! @version    [Version 0.01 alpha, build 72]
//! @author     Copyright (C) Ded, 2005-10 (Ilya Dedinsky, http://ded32.net.ru)
//! @date       2010
//!
//! @include    "Doc/MainPage.txt"
//! @include    "Doc/Examples.txt"
//!
//-------------------------------------------------------------------------------------------------------------------------------
//!
//! @defgroup Drawing   ���������
//! @defgroup Mouse     ��������� ����
//! @defgroup Dialogs   ���������� ����
//! @defgroup Misc      ������
//! @defgroup Service   ���������
//! @defgroup Technical ����������� ������
//}
//===============================================================================================================================

#ifndef   __TXLIB_H
#define   __TXLIB_H

//{ <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< All the code is here, unfold it

//-------------------------------------------------------------------------------------------------------------------------------
//{          Compiler- and platform-specific
//! @name    ��������� � ������������ � ����������
//-------------------------------------------------------------------------------------------------------------------------------
//! @cond INTERNAL

#ifndef __cplusplus
#error TXLib.h: Must use C++ to compile this
#endif

#ifdef __STRICT_ANSI__                          // Try to extend strict ANSI C
#warning TXLib.h: Trying to extend strict ANSI compatibility
#undef __STRICT_ANSI__
#endif

#if defined (__GNUC__)

    #if (__GNUC__ >= 4)
        #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
        #pragma GCC diagnostic ignored "-Wstrict-aliasing"
        #pragma GCC diagnostic ignored "-Wunreachable-code"
        #pragma GCC diagnostic ignored "-Wunused-value"
        #pragma GCC diagnostic ignored "-Wunused-function"
        #pragma GCC diagnostic ignored "-Wunused-label"  // just for fun in _txCanvas_OnCmdAbout()
    #endif

    #define _TX_CHECK_FORMAT( fmtIdx )  __attribute__ (( format (printf, (fmtIdx), (fmtIdx)+1) ))
    #define _TX_CHECK_USAGE             __attribute__ (( warn_unused_result ))

#else

    #define _TX_CHECK_FORMAT( fmtIdx )
    #define _TX_CHECK_USAGE

#endif

#if defined (_MSC_VER)

    #pragma warning (push, 4)                   // set maximum warning level

    #pragma warning (disable: 4127)             // conditional expression is constant
    #pragma warning (disable: 4245)             // conversion from... to..., signed/unsigned mismatch
    #pragma warning (disable: 4351)             // new behavior: elements of array ... will be default initialized

    #define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1

#endif

#if defined (_MSC_VER) && (_MSC_VER == 1200)    // MSVC 6 (1998)

    #pragma warning (push, 3)                   // at level 4, std headers emit warnings

    #pragma warning (disable: 4018)             // '<': signed/unsigned mismatch
    #pragma warning (disable: 4100)             // unreferenced formal parameter
    #pragma warning (disable: 4511)             // copy constructor could not be generated
    #pragma warning (disable: 4512)             // assignment operator could not be generated
    #pragma warning (disable: 4663)             // C++ language change: to explicitly specialize class template '...'
    #pragma warning (disable: 4710)             // function '...' not inlined

    #if !defined (WINVER)
        #define WINVER   0x0400                 // MSVC 6: Defaults to Windows 95
    #endif

#endif

#if defined (_MSC_VER) && (_MSC_VER >= 1400)    // MSVC 8 (2005) or greater

    #define _TX_USE_SECURE_CRT

#else

    #define  strncpy_s    strncpy               // MSVC prior to 8(2005) versions
    #define  strncat_s    strncat               // do NOT have secure variants of these
    #define  ctime_s      ctime                 // these functions, so use unsecure ones.
    #define _snprintf_s  _snprintf              //
    #define _vsnprintf_s _vsnprintf             //

#endif

#if defined (__INTEL_COMPILER)

//  remark #174                                 // expression has no effect
//  remark #304                                 // access control not specified ("public" by default)
//  remark #522                                 // function "..." redeclared "inline" after being called
//  remark #981                                 // operands are evaluated in unspecified order
//  warning #1684                               // conversion from pointer to same-sized integral type (portability problem)

#endif

#if !defined (WINVER)
    #define WINVER       0x0500                 // Defaults to Windows 2000
#endif

#if !defined (_WIN32_WINNT)
    #define _WIN32_WINNT WINVER
#endif

#undef  UNICODE                                 // Drop the Unicode

//! @endcond
//}

//-------------------------------------------------------------------------------------------------------------------------------
//{          Includes
//-------------------------------------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <direct.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <iostream>
#include <algorithm>

#include <conio.h>

#include <windows.h>
#include <tlhelp32.h>

//}

//-------------------------------------------------------------------------------------------------------------------------------
//{          Compiler- and platform-specific
//! @name    ��������� � ������������ � ����������
//-------------------------------------------------------------------------------------------------------------------------------
//! @cond INTERNAL

#ifndef __cplusplus
#error TXLib.h: Must use C++ to compile this
#endif

#ifdef __STRICT_ANSI__                          // Try to extend strict ANSI C
#warning TXLib.h: Trying to extend strict ANSI compatibility
#undef __STRICT_ANSI__
#endif

#if defined (__GNUC__)

    #if (__GNUC__ >= 4)
        #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
        #pragma GCC diagnostic ignored "-Wstrict-aliasing"
        #pragma GCC diagnostic ignored "-Wunreachable-code"
        #pragma GCC diagnostic ignored "-Wunused-value"
        #pragma GCC diagnostic ignored "-Wunused-function"
        #pragma GCC diagnostic ignored "-Wunused-label"  // just for fun in _txCanvas_OnCmdAbout()
    #endif

    #define _TX_CHECK_FORMAT( fmtIdx )  __attribute__ (( format (printf, (fmtIdx), (fmtIdx)+1) ))
    #define _TX_CHECK_USAGE             __attribute__ (( warn_unused_result ))

#else

    #define _TX_CHECK_FORMAT( fmtIdx )
    #define _TX_CHECK_USAGE

#endif

#if defined (_MSC_VER)

    #pragma warning (push, 4)                   // set maximum warning level

    #pragma warning (disable: 4127)             // conditional expression is constant
    #pragma warning (disable: 4245)             // conversion from... to..., signed/unsigned mismatch
    #pragma warning (disable: 4351)             // new behavior: elements of array ... will be default initialized

    #define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1

#endif

#if defined (_MSC_VER) && (_MSC_VER == 1200)    // MSVC 6 (1998)

    #pragma warning (push, 3)                   // at level 4, std headers emit warnings

    #pragma warning (disable: 4100)             // unreferenced formal parameter
    #pragma warning (disable: 4511)             // copy constructor could not be generated
    #pragma warning (disable: 4512)             // assignment operator could not be generated
    #pragma warning (disable: 4100)             // unreferenced formal parameter
    #pragma warning (disable: 4511)             // copy constructor could not be generated
    #pragma warning (disable: 4512)             // assignment operator could not be generated
    #pragma warning (disable: 4710)             // function '...' not inlined

    #if !defined (WINVER)
        #define WINVER   0x0400                 // MSVC 6: Defaults to Windows 95
    #endif

#endif

#if defined (_MSC_VER) && (_MSC_VER >= 1400)    // MSVC 8 (2005) or greater

    #define _TX_USE_SECURE_CRT

#else

    #define  strncpy_s    strncpy               // MSVC prior to 8(2005) versions
    #define  strncat_s    strncat               // do NOT have secure variants of these
    #define  ctime_s      ctime                 // these functions, so use unsecure ones.
    #define _snprintf_s  _snprintf              //
    #define _vsnprintf_s _vsnprintf             //

#endif

#if !defined (WINVER)
    #define WINVER       0x0500                 // Defaults to Windows 2000
#endif

#if !defined (_WIN32_WINNT)
    #define _WIN32_WINNT WINVER
#endif

#undef  UNICODE                                 // Drop the Unicode

//! @endcond
//}

//-------------------------------------------------------------------------------------------------------------------------------
//{          Compiler- and platform-specific
//! @name    ��������� � ������������ � ����������
//-------------------------------------------------------------------------------------------------------------------------------
//! @cond INTERNAL

#if defined (_MSC_VER) && (_MSC_VER == 1200)    // MSVC 6 (1998)

    #pragma warning (push, 4)                   // Restore maximum level

#endif

//! @endcond
//}

//===============================================================================================================================
//! @cond INTERNAL

/*! @cond OFF */ namespace { /*! @endcond */ namespace TX { // <<< Code is here

//! @endcond
//===============================================================================================================================

//===============================================================================================================================
//{          TXLib interface
//! @name    ��������� ����������
//===============================================================================================================================

//===============================================================================================================================
//{          Colors
//! @name    �����
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   �������� ���������������� ������.
//!
//!          ��. @ref TX_BLACK, @ref TX_BLUE � ������ ����� � ������ ����.
//!
//! @see     txSetColor(), txSetFillColor(), txGetColor(), txGetFillColor(), txGetPixel()
//! @hideinitializer
//! @usage
//! @code
//!          txSetColor (TX_RED);
//!          txSetColor (TX_NULL);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

const COLORREF
#ifdef FOR_DOXYGEN_ONLY
    TX_COLOR_NAMES   = 0,
#endif
    TX_BLACK         = RGB (  0,   0,   0),   //!< ������ ����.
    TX_BLUE          = RGB (  0,   0, 128),   //!< �����-����� ����.
    TX_GREEN         = RGB (  0, 128,   0),   //!< ������� ����.
    TX_CYAN          = RGB (  0, 128, 128),   //!< ��������� ����.
    TX_RED           = RGB (128,   0,   0),   //!< �����-������� ����.
    TX_MAGENTA       = RGB (128,   0, 128),   //!< �����-��������� ����.
    TX_BROWN         = RGB (128, 128,   0),   //!< ���������� ����. ����������. Do it yourself using @ref RGB().
    TX_ORANGE        = RGB (255, 128,   0),   //!< ��������� ����.
    TX_GRAY          = RGB (160, 160, 160),   //!< ����� ����.
    TX_DARKGRAY      = RGB (128, 128, 128),   //!< �����-����� ����.
    TX_LIGHTGRAY     = RGB (192, 192, 192),   //!< ������-����� ����.
    TX_LIGHTBLUE     = RGB (  0,   0, 255),   //!< ������-����� ����.
    TX_LIGHTGREEN    = RGB (  0, 255, 128),   //!< ������-������� ����.
    TX_LIGHTCYAN     = RGB (  0, 255, 255),   //!< ������-��������� ����.
    TX_LIGHTRED      = RGB (255,   0, 128),   //!< ������-������� ����.
    TX_LIGHTMAGENTA  = RGB (255,   0, 255),   //!< ������-��������� ����.
    TX_PINK          = RGB (255, 128, 255),   //!< ������� ���������:)
    TX_YELLOW        = RGB (255, 255, 128),   //!< ������ ����.
    TX_WHITE         = RGB (255, 255, 255),   //!< ����� ����.
    TX_TRANSPARENT   = 0xFFFFFFFF,            //!< ���������� ����. <i>��������� ���������.</i>
    TX_NULL          = TX_NULL,               //!< ���������� ����. <i>��������� ���������.</i>

//  �������� ������ (����������) - ��. @ref txExtractColor(), @ref txRGB2HSL(), @ref txHSL2RGB()

    TX_HUE          = 0x04000000,             //!< �������� ��� ����� � ������ HSL
    TX_SATURATION   = 0x05000000,             //!< ������������ ����� � ������ HSL
    TX_LIGHTNESS    = 0x06000000;             //!< �������� ����� � ������ HSL

//}

//===============================================================================================================================
//{          Tune-up constants
//! @name    ����������� ���������
//===============================================================================================================================

//-------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   �� �������� ������������� ���������� ����
//!
//!          �������� ����� ���������� TXLib.h � ���������.
//-------------------------------------------------------------------------------------------------------------------------------

#ifdef FOR_DOXYGEN_ONLY
#define      _TX_NO_HIDE_CONSOLE
#endif

//-------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   ����� �������
//-------------------------------------------------------------------------------------------------------------------------------

const char   _TX_CONSOLE_FONT[]           = "Lucida Console";

//-------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   ���� ������ �������
//-------------------------------------------------------------------------------------------------------------------------------

const COLORREF _TX_CONSOLE_COLOR          = TX_LIGHTGRAY;

//-------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   �������� ������� ������� ������� (��)
//-------------------------------------------------------------------------------------------------------------------------------

const unsigned _TX_CURSOR_BLINK_INTERVAL  = 250;

//-------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   �������� ���������� ������ (��)
//-------------------------------------------------------------------------------------------------------------------------------

const int    _TX_WINDOW_UPDATE_INTERVAL   = 10;

//-------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   ������� �������� �������� (��)
//-------------------------------------------------------------------------------------------------------------------------------

const int    _TX_TIMEOUT                  = 1000;

//-------------------------------------------------------------------------------------------------------------------------------
//! @cond    INTERNAL
//! @ingroup Technical
//! @brief   �������������� �������������� ������� ���������� ���� ���� TXLib
//-------------------------------------------------------------------------------------------------------------------------------

const int    _TX_IDM_ABOUT                = 40000;
const int    _TX_IDM_CONSOLE              = 40001;

//! @endcond

//}

//===============================================================================================================================
//{          Diagnostics and Tools
//! @name    ����������� � �������
//===============================================================================================================================

//! @cond INTERNAL
#define  TX_QUOTE( symbol )   _TX_QUOTE (symbol)
#define _TX_QUOTE( symbol )   #symbol
//! @endcond

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   ������� ������ ����������.
//!
//!          ��� ��������� ������������� ����������� ��� ���������� ������.
//!
//! @see     txVersion()
//}------------------------------------------------------------------------------------------------------------------------------
//! @{

#define _TX_VERSION           "TXLib [Version 0.01 alpha, build 72]"
#define _TX_AUTHOR            "Copyright (C) Ded, 2005-10 (Ilya Dedinsky, http://ded32.net.ru)"

//! @}
//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ��� � ������ �������� �����������
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#if   defined (__GNUC__)

    #define __TX_COMPILER__   "GNU C++ " TX_QUOTE (__GNUC__)  "."       \
                                         TX_QUOTE (__GNUC_MINOR__) "."  \
                                         TX_QUOTE (__GNUC_PATCHLEVEL__) \
                                         ", C++ = " TX_QUOTE (__cplusplus)
#elif defined (_MSC_VER)
    #define __TX_COMPILER__   "Microsoft C++ " TX_QUOTE (_MSC_VER) \
                                         ", C++ = " TX_QUOTE (__cplusplus)

#elif defined (__INTEL_COMPILER)
    #define __TX_COMPILER__   "Intel C++ Compiler " TX_QUOTE (__INTEL_COMPILER) \
                                         ", C++ = " TX_QUOTE (__cplusplus)

#else
    #define __TX_COMPILER__   "Unknown compiler" \
                                         ", C++ = " TX_QUOTE (__cplusplus)

#endif

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ������, �������������� � ��� ����� � ����� ������ �����, ��� �� ����������.
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------
//! @{

#define __TX_FILELINE__       __FILE__ " (" TX_QUOTE (__LINE__) ")"

//! @}
//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ��� ������� �������
//! @warning ���� ����������� ����� ������� �� �������������� ������������, �� __TX_FUNCTION__
//!          ������������ � ��� ��������� ����� � ����� ������.
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#if defined (__GNUC__)
    #define __TX_FUNCTION__   __PRETTY_FUNCTION__

#elif defined (__FUNCSIG__)
    #define __TX_FUNCTION__   __FUNCSIG__

#elif defined (__BORLANDC__) && (__BORLANDC__ >= 0x550)
    #define __TX_FUNCTION__   __FUNC__

#elif defined (__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
    #define __TX_FUNCTION__   __func__

#else
    #define __TX_FUNCTION__   "(" __TX_FILELINE__ ")"

#endif

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ������ ������������ ������� assert(), � ������� ��������� ����� MessageBox(),
//!          ������� � OutputDebugString().
//!
//! @param   condition ������� ��� ��������
//!
//!          ���� �������, ����������� assert(), �������, �� ������ ������ �� ������.\n
//!          ���� ������� ����������� �����, �� ��������� ��������������� ��������� �
//!          ��������� �������� �����������.
//!
//! @return  1, ���� assert() �� ��������, � 0, ���� �� �������� (�� � ���� ������
//!          ���������� ������ �� ��������, �.�. ��������� ����� ��������).
//!
//! @hideinitializer
//! @usage
//! @code
//!          assert (0 <= i && i < ARRAY_SIZE);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

#undef  assert

#ifndef NDEBUG
    #define assert( cond )    ( !(cond)? (TX_THROW ("\aAssertion failed: \"%s\"" _ #cond), 0) : txReturn1() )
#else
    #define assert( cond )    ( 1 )

#endif

//! @cond INTERNAL
inline int txReturn1()        { return 1; }   // To disable warning "right-hand operand of comma has no effect"
//! @endcond

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ������, ����������� �������� ���������� ����� ���������� � �����-���� ������ ������.
//!
//! @note    <b>������ ������������� ������ ���������������� � �������.</b>
//!
//! @see     TX_THROW()
//! @usage
//! @code
//!          TX_THROW ("������� ����� �����: ����� '����� � ���', ���� '%s', ������ %d" _ fileName _ lineNum);
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#define _                     ,

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ������� ����������� ��������������� ���������.
//!
//! @return  ������ false
//!
//! @see     TX_NEEDED(), _
//! @usage
//! @code
//!          TX_THROW ("�� ���� ��������� '����� � ���'! ������ ������ '%s'" _ fileName);
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#ifndef NDEBUG
    #define TX_THROW( msg )   ( _txThrow (__FILE__, __LINE__, 									  \
                                          ((__TX_FUNCTION__[0] != '(')? __TX_FUNCTION__ : NULL),  \
                                          (DWORD)(-1), msg) )

#else
    #define TX_THROW(msg)     ( 0 )

#endif

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ������� ��� ����� � ����� ������, ��� ��������� ����� TX_PRINT_HERE().
//!
//! @usage
//! @code
//!          TX_PRINT_HERE();
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#ifndef NDEBUG
    #define TX_PRINT_HERE()   printf ("%s (%d) %s: Here... :)\n", __FILE__, __LINE__, __TX_FUNCTION__)

#else
    #define TX_PRINT_HERE()

#endif

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ������� ��������������� ��������� � ������ �������� ��������.
//!          ������������, ���� ���� ������ if() :)
//!
//! @note    <b>��������������, ��� �������� � ������ �������� ���������� 0 ��� false.</b>\n\n
//!          <b>��� ���������� � ������ Release (��� ���� ��������� NDEBUG) TX_NEEDED
//!          ������������ � ������ ��������.</b>
//!
//! @return  ������ false
//! @usage
//! @code
//!          FILE* input = fopen ("a.txt", "r"); input TX_NEEDED;
//!          fgets (str, sizeof (str) - 1, input) TX_NEEDED;
//!          (fclose (input) != 0) TX_NEEDED;
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#ifndef NDEBUG
    #define TX_NEEDED         || TX_THROW (NULL)

#else
    #define TX_NEEDED

#endif

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ���������� ������������ �� ���� �����
//!
//! @param   a  ���� �� ����� :)
//! @param   b  ������ �� ����� :)
//!
//! @return  ������������ �� ���� ����� a � b
//!
//! @hideinitializer
//! @usage
//! @code
//!          if (MAX (3, 7) != 7) printf ("Your CPU is broken, throw it away.");
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

#define MAX( a, b )           ( (a) > (b) ? (a) : (b) )

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ���������� ����������� �� ���� �����
//!
//! @param   a  ���� �� ����� :)
//! @param   b  ������ �� ����� :)
//!
//! @return  ����������� �� ���� ����� a � b
//!
//! @hideinitializer
//! @usage
//! @code
//!          if (MIN (3, 7) != 3) printf ("Your CPU is still broken, throw it away again.");
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

#define MIN( a, b )           ( (a) < (b) ? (a) : (b) )

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ����� ��
//!
//! @return  ����� ��
//!
//! @hideinitializer
//! @usage
//! @code
//!          if (txPI == 1) MessageBox (txWindow(), "�� ������ � ������ ���������.", "�����������", MB_ICONSTOP);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

const double txPI = asin (1.0) * 2;

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   ��������/��������� ���������� ����������� ���������� ���� ����������.
//!
//!          ����������� ���� ����� ������ @ref TX_TRACE, ������� ������������� �����
//!          ������ ���������� (statement). �� ��������� ����������� ���������.
//!
//!          �� ��������� ����������� ������� ����� ������� OutputDebugString(),
//!          �� ����� ����� ����������� ���������-���������, ��������,
//!          <a href=http://technet.microsoft.com/ru-ru/sysinternals/bb896647%28en-us%29.aspx>
//!          DebugView</a> ��� WinTail. ��� ����� ��������, ������������� ������ @ref TX_TRACE.
//!
//!          _TX_ALLOW_TRACE � @ref TX_TRACE �������� ����� ���������� TXLib.h � ���������.
//! @usage
//! @code
//!          #define  _TX_ALLOW_TRACE   // ��� ��������� ������ ��������� DebugView
//!          #include "TXLib.h"
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------
//! @{

#ifdef FOR_DOXYGEN_ONLY
#define _TX_ALLOW_TRACE
#endif

#ifdef _TX_ALLOW_TRACE
    #define $                 TX_TRACE

#else
    #define $

#endif

//! @}
//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   ���������� ���������� ���� ���������� ����� OutputDebugString().
//!
//!          �� ��������� ����������� ������� ����� ������� OutputDebugString(),
//!          �� ����� ����� ����������� ���������-���������, ��������,
//!          <a href=http://technet.microsoft.com/ru-ru/sysinternals/bb896647%28en-us%29.aspx>
//!          DebugView</a> ��� WinTail.
//!
//!          TX_TRACE ����� �������������� � ���� ���, ����� �� ����� ����������
//!          ����� ������ ������� ���� TXLib.
//!
//!          ����������� ����� �������������� ��������� ���� ����� ������ @ref _TX_ALLOW_TRACE.
//!          �� ��������� ��� ���������.
//!
//!          TX_TRACE � @ref _TX_ALLOW_TRACE �������� ����� ���������� TXLib.h � ���������.
//! @usage
//! @code
//!          #define  TX_TRACE  printf (__LINE__ " ");
//!          #include "TXLib.h"
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------
//! @{

#ifdef FOR_DOXYGEN_ONLY
#define TX_TRACE
#endif

#ifndef TX_TRACE

    #define TX_TRACE          OutputDebugString (__TX_FILELINE__ ": ");

#endif

//! @}
//}

//===============================================================================================================================
//{          Initialization
//! @name    ������������� ����������
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   �������� ���� ���������
//!
//! @param   sizeX     ������ ���� �� ����������� (� ��������)
//! @param   sizeY     ������ ���� �� ���������   (� ��������)
//! @param   centered  ������������� ���� �� �������
//!
//!          ��� �������� ���� ��������������� ��������� ��������� �� ���������,
//!          ��. ������� @ref txSetDefaults().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txOK()
//! @usage
//! @code
//!          txCreateWindow ( 800,  600);
//!          txCreateWindow (1024,  768, false);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txCreateWindow (double sizeX, double sizeY, bool centered = true);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ��������� ���������� ��������� �� ���������.
//!
//!          ��������� �� ���������:\n
//!          - ����� - ���� ����� (TX_WHITE), ������� 1
//!          - ������� - ���� ����� (TX_WHITE)
//!          - ����� - ��������� �����, ���� ����� (TX_WHITE)
//!          - ���������� ��������� �������� - ����������� ����� (R2_COPYPEN)
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txSelectFont(), txSelectRegion(), txSetROP2()
//! @usage
//! @code
//!          txSetDefaults();
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSetDefaults();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   �������� ������������ ������ ����������
//!
//! @return  ��������� ����������
//!
//! @see     txCreateWindow()
//! @usage
//! @code
//!          txCreateWindow (800, 600);
//!          if (!txOK())
//!              {
//!              MessageBox (txWindow(), "�� ������ ������� ����", "��������", MB_ICONSTOP);
//!              return;
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

inline bool txOK();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Technical
//! @brief   ���������� ������ � ����������� � ������� ������ ����������.
//!
//! @return  ������ � ����������� � ������� ������ ����������.
//!
//! @usage
//! @code
//!          printf ("I personally love %s\n", txVersion());
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

const char* txVersion();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ������ ���� ��������� � ���� ��������� POINT.
//!
//! @return  ������ ���� ��������� � ���� ��������� POINT.
//!
//! @see     txGetExtentX(), txGetExtentY()
//! @usage
//! @code
//!          POINT size = txGetExtent();
//!          txLine (0, 0,      size.x, size.y);
//!          txLine (0, size.y, size.x, 0);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

POINT txGetExtent();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ������ ���� ���������.
//!
//! @return  ������ ���� ���������.
//!
//! @see     txGetExtent(), txGetExtentY()
//! @usage
//! @code
//!          txSetTextAlign (TA_CENTER);
//!          txTextOut (txGetExtentX() / 2, 100, "Oh, oh, you're in the [army]middle now");
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txGetExtentX();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ������ ���� ���������.
//!
//! @return  ������ ���� ���������.
//!
//! @see     txGetExtent(), txGetExtentX()
//! @usage
//! @code
//!          void DrawHouse (int height);
//!          ...
//!          DrawHouse (txGetExtentY() / 2);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txGetExtentY();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ���������� ��������� ��������� ������
//!
//! @return  ���������� (��������� �����, handler) ��������� ��������� (device context, DC)
//!          ������ (HDC).
//!
//! @see     txWindow(), txLock(), txUnlock(), txGDI()
//! @usage
//! @code
//!          txBitBlt (txDC(),   0,   0, 100, 100, txDC(), 0, 0);
//!          txBitBlt (txDC(), 100,   0, 100, 100, txDC(), 0, 0);
//!          txBitBlt (txDC(), 0,   100, 100, 100, txDC(), 0, 0);
//!          txBitBlt (txDC(), 100, 100, 100, 100, txDC(), 0, 0);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

inline HDC txDC();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ���������� ���� ������
//!
//! @return  ���������� (��������� �����, handler) ���� ������
//!
//! @see     txDC(), txLock(), txUnlock(), txGDI()
//! @usage
//! @code
//!          SetWindowText (txWindow(), "����� ��������� - ������ � � ����� �����!");
//!          MessageBox (txWindow(), "�����������", "��������", MB_ICONINFORMATION);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

inline HWND txWindow();

//}

//===============================================================================================================================
//{          Setting the parameters
//! @name    ��������� ������ � ������� ���������
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������������� ������� ���� � ������� �����, ���� ������.
//!
//! @param   color      ���� ����� � ������, ��. @ref TX_BLACK "�����", RGB()
//! @param   thickness  ������� �����
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txColor(), txGetColor(), txFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//! @usage
//! @code
//!          txSetColor (TX_RED);
//!          txSetColor (RGB (255, 128, 0), 5);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSetColor (COLORREF color, double thickness = 1);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������������� ������� ���� ����� � ������.
//!
//! @param   red    ���������� �������� ����� � ��������� [0; 1]
//! @param   green  ���������� �������� ����� � ��������� [0; 1]
//! @param   blue   ���������� ������   ����� � ��������� [0; 1]
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor()
//! @usage
//! @code
//!          txColor (1.0, 0.5, 0.25);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txColor (double red, double green, double blue);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ������� ���� ����� � ������.
//!
//! @return  ������� ���� ����� � ������, ��. @ref TX_BLACK "�����", RGB()
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//! @usage
//! @code
//!          COLORREF color = txGetColor();
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

COLORREF txGetColor();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������������� ������� ���� ���������� �����.
//!
//! @param   color  ���� ����������, ��. @ref TX_BLACK "�����", RGB()
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txFillColor(), txGetFillColor(), txColor(), txGetColor(), @ref TX_BLACK "�����", RGB()
//! @usage
//! @code
//!          txSetFillColor (TX_RED);
//!          txSetFillColor (RGB (255, 128, 0));
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSetFillColor (COLORREF color);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������������� ������� ���� ���������� �����.
//!
//! @param   red    ���������� �������� ����� � ��������� [0; 1]
//! @param   green  ���������� �������� ����� � ��������� [0; 1]
//! @param   blue   ���������� ������   ����� � ��������� [0; 1]
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetFillColor(), txGetFillColor(), txSetColor(), txGetColor()
//! @usage
//! @code
//!          txFillColor (1.0, 0.5, 0.25);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txFillColor (double red, double green, double blue);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ������� ���� ���������� �����.
//!
//! @return  ������� ���� ���������� �����, ��. @ref TX_BLACK "�����", RGB()
//!
//! @see     txSetFillColor(), txGetFillColor(), txSetColor(), txGetColor(), @ref TX_BLACK "�����", RGB()
//! @usage
//! @code
//!          COLORREF color = txGetFillColor();
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

COLORREF txGetFillColor();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������������� ����� �������������� ������ ��� ���������.
//!
//!          ��� ��������� ����������� ���������� ����� �� ������ ������� �������
//!          �� ������, � ��������� ����� ������ � ������� ����� ����� � ����������.
//!
//! @param   mode  ����� ���������� ������
//!
//! @title   ������ �������������� ������:
//! @table   @tr R2_COPYPEN     @td ������� = ����� ����� (����� ���������� ����� :) @endtr
//!          @tr R2_NOTCOPYPEN  @td ������� = ~�����\n @endtr
//!          @tr @endtr
//!          @tr R2_BLACK       @td ������� = ������ ���� (���� ����� ������������)    @endtr
//!          @tr R2_WHITE       @td ������� = �����  ���� (���� ����� ������������)    @endtr
//!          @tr R2_NOT         @td ������� = ~�������    (���� ����� ������������)\n  @endtr
//!          @tbr
//!          @tr R2_XORPEN      @td ������� =    ������� ^  �����    @endtr
//!          @tr R2_NOTXORPEN   @td ������� = ~ (������� ^  �����)\n @endtr
//!          @tbr
//!          @tr R2_MASKPEN     @td ������� =    ������� &  �����    @endtr
//!          @tr R2_NOTMASKPEN  @td ������� = ~ (������� &  �����)   @endtr
//!          @tr R2_MASKNOTPEN  @td ������� =    ������� & ~�����    @endtr
//!          @tr R2_MASKPENNOT  @td ������� =   ~������� &  �����\n  @endtr
//!          @tbr
//!          @tr R2_MERGEPEN    @td ������� =    ������� |  �����    @endtr
//!          @tr R2_NOTMERGEPEN @td ������� = ~ (������� |  �����)   @endtr
//!          @tr R2_MERGENOTPEN @td ������� =    ������� | ~�����    @endtr
//!          @tr R2_MERGEPENNOT @td ������� =   ~������� |  �����\n  @endtr
//!          @tbr
//!          @tr R2_NOP         @td ������� ������ �� ����������.    @endtr
//! @endtable
//!
//! @return  ���������� ����� �������������� ������, ��. @ref TX_BLACK "�����", RGB()
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txSetROP2 (R2_XORPEN);
//!          txSetROP2 (R2_COPYPEN);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSetROP2 (int mode);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������� (���������) ���� �� ���� ������� ������ (���������).
//!
//! @param   red    ���������� �������� ����� � ��������� [0; 255]
//! @param   green  ���������� �������� ����� � ��������� [0; 255]
//! @param   blue   ���������� ������   ����� � ��������� [0; 255]
//!
//! @return  ��������� ���� � ������� COLORREF.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����"
//! @see     RGB(), txExtractColor(), txRGB2HSL(), txHSL2RGB()
//! @usage
//! @code
//!          txSetColor (RGB (255, 128, 0));
//!
//!          int red = 20, green = 200, blue = 20;
//!          COLORREF color = RGB (red, green, blue);
//!          txSetFillColor (color);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

#ifdef FOR_DOXYGEN_ONLY
COLORREF RGB (int red, int green, int blue);
#endif

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ��������� �������� ���������� (�������� �����) �� ���������� �����.
//!
//! @param   color      ��������� ����
//! @param   component  ����������� ����������, ��. @ref TX_BLACK "�����"
//!
//! @return  �������� ����������, ��. @ref TX_BLACK "�����"
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), TX_BLACK "�����"
//! @see     RGB(), txExtractColor(), txRGB2HSL(), txHSL2RGB(), @ref TX_BLACK "�����"
//! @usage
//! @code
//!          int red       = txExtractColor (color, TX_RED);
//!          int lightness = txExtractColor (TX_BLUE, TX_LIGHTNESS);
//!
//!          ������ ������� ��. � �������� AppearText(), AppearEarth() ������� 5 ("�����").
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txExtractColor (COLORREF color, COLORREF component);

//{--------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ����������� ���� �� ������� RGB � ������ HSL.
//!
//!          ������ @b RGB ������������ ���
//!
//!          - ������� ���������� ����� (Red),   �� 0 �� 255.
//!          - ������� ���������� ����� (Green), �� 0 �� 255.
//!          - �����   ���������� ����� (Blue),  �� 0 �� 255.
//!
//!          ������ @b HSL ������������ ���
//!
//!          - �������� ��� (Hue),        �� 0 �� 360.
//!          - ������������ (Saturation), �� 0 �� 255.
//!          - ��������     (Lightness),  �� 0 �� 255.
//!
//! @param   rgbColor  ������������� ���� � ������� @ref RGB
//!
//! @return  ��������� ���� � ���� COLORREF.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����"
//! @see     RGB(), txExtractColor(), txRGB2HSL(), txHSL2RGB(), @ref TX_BLACK "�����"
//! @usage
//! @code
//!          COLORREF hslColor = txRGB2HSL (TX_RED);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

COLORREF txRGB2HSL (COLORREF rgbColor);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ����������� ���� �� ������� HSL � ������ @ref RGB.
//!
//!          ������ @b RGB ������������ ���
//!
//!          - ������� ���������� ����� (Red),   �� 0 �� 255.
//!          - ������� ���������� ����� (Green), �� 0 �� 255.
//!          - �����   ���������� ����� (Blue),  �� 0 �� 255.
//!
//!          ������ @b HSL ������������ ���
//!
//!          - �������� ��� (Hue),        �� 0 �� 360.
//!          - ������������ (Saturation), �� 0 �� 255.
//!          - ��������     (Lightness),  �� 0 �� 255.
//!
//! @param   hslColor  ������������� ���� � ������� HSL
//!
//! @return  ��������� ���� � ���� COLORREF.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����"
//! @see     RGB(), txExtractColor(), txRGB2HSL(), txHSL2RGB(), @ref TX_BLACK "�����"
//! @usage
//! @code
//!          int hue = 10, saturation = 128, lightness = 128;
//!          COLORREF hslColor = RGB (hue, saturation, lightness);
//!          txSetColor (txHSL2RGB (hslColor));
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

COLORREF txHSL2RGB (COLORREF hslColor);

//}

//===============================================================================================================================
//{          Drawing
//! @name    ��������� �����
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������� ����� ������� ������ ����������.
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetFillColor(), txFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//! @usage
//! @code
//!          txClear();
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txClear();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ ������� (����� �� ������).
//!
//! @param   x      �-���������� �����
//! @param   y      Y-���������� �����
//! @param   color  ���� �����, ��. @ref TX_BLACK "�����", RGB()
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txPixel(), txGetPixel(), @ref TX_BLACK "�����", RGB()
//! @usage
//! @code
//!          txSetPixel (100, 100, TX_RED);
//!          txSetPixel (100, 100, RGB (255, 128, 0));
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSetPixel (double x, double y, COLORREF color);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ ������� (����� �� ������).
//!
//! @param   x      �-���������� �����
//! @param   y      Y-���������� �����
//! @param   red    ���������� �������� ����� � ��������� [0; 1]
//! @param   green  ���������� �������� ����� � ��������� [0; 1]
//! @param   blue   ���������� ������   ����� � ��������� [0; 1]
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetPixel(), txGetPixel()
//! @usage
//! @code
//!          txSetPixel (100, 100, 1.0, 0.5, 0.25);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txPixel (double x, double y, double red, double green, double blue);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ������� ���� ����� (�������) �� ������.
//!
//! @param   x  �-���������� �����
//! @param   y  Y-���������� �����
//!
//! @return  ������� ���� �������, ��. @ref TX_BLACK "�����", RGB()
//!
//! @see     txSetPixel(), txPixel(), @ref TX_BLACK "�����", RGB()
//! @usage
//! @code
//!          COLORREF color = txGetPixel (100, 200);
//!
//!          if (txGetPixel (x, y) == TX_RED) CarCrash (x, y);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

COLORREF txGetPixel (double x, double y);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ �����.
//!
//! @param   x0  X-���������� ��������� �����
//! @param   y0  Y-���������� ��������� �����
//! @param   x1  X-���������� ��������  �����
//! @param   y1  Y-���������� ��������  �����
//!
//!          ���� � ������� ����� �������� �������� txSetColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txLine (100, 200, 400, 500);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txLine (double x0, double y0, double x1, double y1);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ �������������.
//!
//! @param   x0  X-���������� �������� ������  ����
//! @param   y0  Y-���������� �������� ������  ����
//! @param   x1  X-���������� �������  ������� ����
//! @param   y1  Y-���������� �������  ������� ����
//!
//!          ���� � ������� ����� �������� �������� txSetColor(), ���� ���������� - txSetFillColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txRectangle (100, 200, 400, 500);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txRectangle (double x0, double y0, double x1, double y1);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ ������� ����� ��� �������������.
//!
//! @param   points     ������ �������� POINT � ������������ �����
//! @param   numPoints  ���������� ����� � �������
//!
//!          ���� � ������� ����� �������� �������� txSetColor(), ���� ���������� - txSetFillColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          POINT star[6] = {{150, 300}, {200, 100}, {250, 300}, {100, 200}, {300, 200}, {150, 300}};
//!          txPolygon (star, 6);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txPolygon (const POINT points[], int numPoints);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ ������.
//!
//! @param   x0  X-���������� �������� ������  ���� ���������� ��������������
//! @param   y0  Y-���������� �������� ������  ���� ���������� ��������������
//! @param   x1  X-���������� �������  ������� ���� ���������� ��������������
//! @param   y1  Y-���������� �������  ������� ���� ���������� ��������������
//!
//!          ���� � ������� ����� �������� �������� txSetColor(), ���� ���������� - txSetFillColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txEllipse (100, 100, 300, 200);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txEllipse (double x0, double y0, double x1, double y1);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ ���������� ��� ����.
//!
//! @param   x  �-���������� ������
//! @param   y  Y-���������� ������
//! @param   r  ������
//!
//!          ���� � ������� ����� �������� �������� txSetColor(), ���� ���������� - txSetFillColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txCircle (100, 100, 10);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txCircle (double x, double y, double r);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ ���� �������.
//!
//! @param   x0          X-���������� �������� ������  ���� ��������������,
//!                        ���������� ������ �������, ����������� ����
//! @param   y0          Y-���������� �������� ������  ���� ��������������
//! @param   x1          X-���������� �������  ������� ���� ��������������
//! @param   y1          Y-���������� �������  ������� ���� ��������������
//! @param   startAngle  ���� ����� ������������ ��� OX � ������� ���� (� ��������)
//! @param   totalAngle  �������� ���� (� ��������)
//!
//!          ���� � ������� ����� �������� �������� txSetColor(), ���� ���������� - txSetFillColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txArc (100, 100, 300, 200, 0, 180);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txArc (double x0, double y0, double x1, double y1, double startAngle, double totalAngle);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ ������ �������.
//!
//! @param   x0          X-���������� �������� ������  ���� ��������������,
//!                        ���������� ������ �������, ����������� ������
//! @param   y0          Y-���������� �������� ������  ���� ��������������
//! @param   x1          X-���������� �������  ������� ���� ��������������
//! @param   y1          Y-���������� �������  ������� ���� ��������������
//! @param   startAngle  ���� ����� ������������ ��� OX � ������� ������� (� ��������)
//! @param   totalAngle  �������� ������� (� ��������)
//!
//!          ���� � ������� ����� �������� �������� txSetColor(), ���� ���������� - txSetFillColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txPie (100, 100, 300, 200, 0, 180);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txPie (double x0, double y0, double x1, double y1, double startAngle, double totalAngle);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ ����� �������.
//!
//! @param   x0          X-���������� �������� ������ ���� ��������������,
//!                        ���������� ������ �������, ����������� �����
//! @param   y0          Y-���������� �������� ������ ���� ��������������
//! @param   x1          X-���������� ������� ������� ���� ��������������
//! @param   y1          Y-���������� ������� ������� ���� ��������������
//! @param   startAngle  ���� ����� ������������ ��� OX � ������� ����� (� ��������)
//! @param   totalAngle  �������� ����� (� ��������)
//!
//!          ���� � ������� ����� �������� �������� txSetColor(), ���� ���������� - txSetFillColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txChord (100, 100, 300, 200, 0, 180);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txChord (double x0, double y0, double x1, double y1, double startAngle, double totalAngle);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   �������� ������������ ������ ������� ������ ����������.
//!
//! @param   x      �-���������� ����� ������ �������
//! @param   y      Y-���������� ����� ������ �������
//! @param   color  ���� ���������� ������� (TX_TRANSPARENT - ���������������)
//! @param   mode   ����� ������� (FLOODFILLSURFACE - ������� ����������� ����)
//!
//!          ���� ���������� �������� �������� txSetFillColor().
//!          �� ������������� ��� ���������� - �������� �������� ��������.
//!
//! @title   ������ �������: @table
//!          @tr FLOODFILLSURFACE @td - �������� �������,    ��������� ������ color. @endtr
//!          @tr FLOODFILLBORDER  @td - �������� �� �������, ��������� ������ color. @endtr
//!          @endtable
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()
//! @usage
//! @code
//!          txFloodFill (100, 100);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txFloodFill (double x, double y,
                  COLORREF color = TX_TRANSPARENT, DWORD mode = FLOODFILLSURFACE);
//}

//===============================================================================================================================
//{          Drawing text
//! @name    ������ � �������
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������ �����.
//!
//! @param   x     �-���������� ��������� ����� ������
//! @param   y     Y-���������� ��������� ����� ������
//! @param   text  ��������� ������
//!
//!          ���� ������ �������� �������� txSetColor().
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()
//! @usage
//! @code
//!          txTextOut (100, 100, "����� ����� �� ���� ���� �������.");
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txTextOut (double x, double y, const char text[]);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   �������� ������� �����.
//!
//! @param   name       �������� ������
//! @param   sizeY      ������ ���� (������ �� Y)
//! @param   sizeX      ������ ����
//! @param   bold       �������� ������ (�� 0 �� 1000)
//! @param   italic     ������
//! @param   underline  �������������
//! @param   strikeout  ������������
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txTextOut()
//! @usage
//! @code
//!          txSelectFont ("Comic Sans MS", 20);
//!          txTextOut (100, 100, "����� ����� �� ���� ���� �������.");
//!          txSelectFont ("Comic Sans MS", 20, 10, false, true, false, true);
//!          txTextOut (100, 200, "�� �� ������-�� ���.");
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSelectFont (const char name[], double sizeY,
                   double sizeX   = 0,
                   int  bold      = FW_DONTCARE,
                   bool italic    = false,
                   bool underline = false,
                   bool strikeout = false);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ��������� ������� ��������� �������.
//!
//! @param   text  ��������� ������
//!
//! @return  ������� ������� � ��������� SIZE.
//!
//! @see     txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()
//! @usage
//! @code
//!          SIZE size = txGetTextExtent (text);
//!          txTextOut (100 + size.cx / 2, 200 + size.cy / 2, text);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

SIZE txGetTextExtent (const char text[]);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ��������� ������ ��������� �������.
//!
//! @param   text  ��������� ������
//!
//! @return  ������ �������.
//!
//! @see     txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()
//! @usage
//! @code
//!          txTextOut (100 + txGetTextExtentX (text) / 2, 200 + txGetTextExtentY (text) / 2, text);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txGetTextExtentX (const char text[]);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ��������� ������ ��������� �������.
//!
//! @param   text  ��������� ������
//!
//! @return  ������ �������.
//!
//! @see     txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()
//! @usage
//! @code
//!          txTextOut (100 + txGetTextExtentX (text) / 2, 200 + txGetTextExtentY (text) / 2, text);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txGetTextExtentY (const char text[]);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������������� ������� ������������ ������.
//!
//! @param   align  ����� ������������
//!
//! @title   ����� ������������: @table
//!          @tr TA_BASELINE @td ����� (X,Y) ���������� ������� ����� ������. @endtr
//!          @tr TA_BOTTOM   @td ����� (X,Y) ���������� ������ ������� ���������� ��������������\n
//!                              (����� ����� ���� ���� �����).   @endtr
//!          @tr TA_TOP      @td ����� (X,Y) ���������� ������� ������� ���������� ��������������\n
//!                              (����� ����� ���� ���� �����).\n @endtr
//!          @tbr
//!          @tr TA_CENTER   @td ����� ����� �������� �� ����������� ������������ ����� (X,Y). @endtr
//!          @tr TA_LEFT     @td ����� (X,Y) ���������� ����� ������� ���������� ��������������\n
//!                              (����� ����� ������ ���� �����). @endtr
//!          @tr TA_RIGHT    @td ����� (X,Y) ���������� ������ ������� ���������� ��������������\n
//!                              (����� ����� ����� ���� �����).  @endtr
//!          @endtable
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()
//! @usage
//! @code
//!          txSetTextAlign (TA_RIGHT);
//!
//!          txSetTextAlign();
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSetTextAlign (unsigned align = TA_CENTER | TA_BASELINE);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���� ����� �� ��� ��������.
//!
//! @param   name  �������� ������
//!
//! @return  ���������� � ������ � ��������� LOGFONT.
//!          ���� ����� �� ������, ���������� NULL.
//!
//! @see     txTextOut(), txSelectFont()
//! @usage
//! @code
//!          if (txFontExist ("Comic Sans MS")) txSelectFont ("Comic Sans MS", 30);
//!          else                               txSelectFont ("Times", 30);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

LOGFONT* txFontExist (const char name[]);

//}

//===============================================================================================================================
//{          Drawing to memory DC and image loading
//! @name    ��������� � ������ (�� "����������� ������") � �������� �����������
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������� �������������� ����� (�������� ���������, Device Context, DC) � ������.
//!
//! @param   sizeX   ������ ������
//! @param   sizeY   ������ ������
//! @param   bitmap  Bitmap to be associated with DC
//!
//! @return  ���������� (��������� �����, �������� Windows) ���������� ������ (��������� ���������).
//!
//! @remarks ��������� �������� ����� ����� ����� ������� ��� ������ txDeleteDC().
//!
//! @see     txCreateWindow(), txCreateCompatibleDC(), txLoadImage(), txDeleteDC()
//!
//! @usage
//! @code
//!          HDC save = txCreateCompatibleDC (100, 100);
//!
//!          txBitBlt (backup, 0, 0, 100, 100, txDC(), 0, 0);
//!          txTextOut (20, 20, "Boo!");
//!          txSleep (2000);
//!          txBitBlt (txDC(), 0, 0, 100, 100, save, 0, 0);
//!
//!          txDeleteDC (save);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

HDC txCreateCompatibleDC (double sizeX, double sizeY, HBITMAP bitmap = NULL);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ��������� �� ����� ����������� � ������� BMP. ������ ��� �������� ��������.
//!
//! @param   filename  ��� ����� � ������������ � ������� BMP
//!
//!          ����������� ����������� � ����������� �������� ��������� � ������ ("����������� �����"),
//!          ������� ����� ����� ����� <b>�����������</b> ������� ��� ������ txDeleteDC().
//!
//!          ����������� �������������� ������ � ������� BMP. ���� ����� ���� ������� �������, �������� JPG, �
//!          ������������� ��� �� ������ ���������� �� BMP, �� �� ����� ������ �� ���������. ����� �����������
//!          ��������� �� �����.
//!
//! @return  ���������� ���������� ��������� ��������� � ������, � ����������� ������������.
//!
//! @see     txCreateWindow(), txCreateCompatibleDC(), txLoadImage(), txDeleteDC(), txBitBlt(), txAlphaBlend(),
//!          txTransparentBlt()
//! @usage
//!          ������ ������������� ��. � ����� TX\Examples\Tennis\Tennis.cpp.
//! @code
//!          HDC background = txLoadImage ("Resources\\Images\\Background.bmp");
//!          if (!background) MessageBox (txWindow(), "Cannot load background", "Epic fail", 0);
//!
//!          txBitBlt (txDC(), 0, 0, 800, 600, background, 0, 0);
//!          txDeleteDC (background);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

HDC txLoadImage (const char filename[]);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ���������� ����� (�������� ���������, DC) � ������.
//!
//! @param   dc  �������� ��������� ��� �����������
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txCreateWindow(), txCreateCompatibleDC(), txLoadImage(), txDeleteDC()
//! @usage
//!          ������ ������������� ��. � ����� TX\Examples\Tennis\Tennis.cpp.
//! @code
//!          HDC background = txLoadImage ("Resources\\Images\\Background.bmp");
//!          if (!background) MessageBox (txWindow(), "Cannot load background", "Oh, not now", 0);
//!
//!          txBitBlt (txDC(), 0, 0, 800, 600, background, 0, 0);
//!          txDeleteDC (background);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txDeleteDC (HDC dc);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   �������� ����������� � ������ ������ (��������� ���������, DC) �� ������.
//!
//! @param   dest    �������� ���������� (���� ����������)
//! @param   xDest   �-���������� �������� ������ ���� �����������-���������
//! @param   yDest   Y-���������� �������� ������ ���� �����������-���������
//! @param   width   ������ ����������� �����������
//! @param   height  ������ ����������� �����������
//! @param   src     �������� ��������� (������ ����������)
//! @param   xSrc    �-���������� �������� ������ ���� �����������-���������
//! @param   ySrc    Y-���������� �������� ������ ���� �����������-���������
//! @param   rOp     ��������� �������� �����������
//!
//! @title   ������ �����������:
//! @table   @tr SRCCOPY     @td ������ �������� :) - ����� ���������������� �����\n @endtr
//!          @tbr
//!          @tr BLACKNESS   @td ��������� �����-�������� ������ ������ (�����-�������� ������������). @endtr
//!          @tr WHITENESS   @td ��������� �����-�������� ����� ������  (�����-�������� ������������). @endtr
//!          @tr DSTINVERT   @td ����������� ����� �� ������-���������  (�����-�������� ������������). @endtr
//!          @tr PATCOPY     @td �������� ���� ������� ����� ������-���������.\n @endtr
//!          @tbr
//!          @tr MERGECOPY   @td �������� =   �������� & ���� ������� ����� ���������. @endtr
//!          @tr MERGEPAINT  @td �������� = ~ �������� | �������� @endtr
//!          @tr NOTSRCCOPY  @td �������� = ~ �������� @endtr
//!          @tr NOTSRCERASE @td �������� = ~ (�������� | ��������) @endtr
//!          @tr PATINVERT   @td �������� =  ����� ��������� ^  �������� @endtr
//!          @tr PATPAINT    @td �������� = (����� ��������� | ~��������) | �������� @endtr
//!          @tr SRCAND      @td �������� =  �������� & �������� @endtr
//!          @tr SRCERASE    @td �������� = ~�������� & �������� @endtr
//!          @tr SRCINVERT   @td �������� =  �������� ^ �������� @endtr
//!          @tr SRCPAINT    @td �������� =  �������� | �������� @endtr
//!          @endtable
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txAlphaBlend(), txTransparentBlt(), txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(),
//!          @ref TX_BLACK "�����", RGB()
//! @usage
//!          ������ ������������� ��. � ����� TX\Examples\Tennis\Tennis.cpp.
//! @code
//!          HDC background = txLoadImage ("Resources\\Images\\Background.bmp");
//!          if (!background) MessageBox (txWindow(), "Cannot load background", "Once again :(", 0);
//!
//!          txBitBlt (txDC(), 0, 0, 800, 600, background, 0, 0);
//!          txDeleteDC (background);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txBitBlt (HDC dest, double xDest, double yDest, double width, double height,
               HDC src,  double xSrc,  double ySrc,  DWORD rOp = SRCCOPY);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   �������� ����������� � ������ ������ (��������� ���������, DC) �� ������
//!          � ������ ������������.
//!
//! @param   dest        �������� ���������� (���� ����������)
//! @param   xDest       �-���������� �������� ������ ���� �����������-���������
//! @param   yDest       Y-���������� �������� ������ ���� �����������-���������
//! @param   width       ������ ����������� �����������
//! @param   height      ������ ����������� �����������
//! @param   src         �������� ��������� (������ ����������)
//! @param   xSrc        �-���������� �������� ������ ���� �����������-���������
//! @param   ySrc        Y-���������� �������� ������ ���� �����������-���������
//! @param   transColor  ����, ������� ����� ��������� ����������
//!
//!          ����������� ������� TransparentBlt �� Win32 API ����� �������������� �����������.
//!          � txTransparentBlt ��� ������ ��� ��������� �������������. If you need image scaling,
//!          use original function TransparentBlt and don't mess with stupid TX-based tools.
//!          (See implementation of txTransparentBlt in TXLib.h).
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txBitBlt(), txTransparentBlt(), txLoadImage(), txCreateCompatibleDC()
//! @usage
//!          ������ ������������� ��. � ����� TX\Examples\Tennis\Tennis.cpp.
//! @code
//!          HDC superman = txLoadImage ("Resources\\Images\\Superman.bmp");
//!          if (!superman) MessageBox (txWindow(), "Cannot load superman, all the monsters will succeed", "Sorry", 0);
//!
//!          txTransparentBlt (txDC(), 0, 0, 800, 600, superman, 0, 0);
//!          txDeleteDC (superman);  // So pity :(
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txTransparentBlt (HDC dest, double xDest, double yDest, double width, double height,
                       HDC src,  double xSrc,  double ySrc,  COLORREF transColor = TX_BLACK);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   �������� ����������� � ������ ������ (��������� ���������, DC) �� ������
//!          � ������ ������������.
//!
//! @param   dest    �������� ���������� (���� ����������)
//! @param   xDest   �-���������� �������� ������ ���� �����������-���������
//! @param   yDest   Y-���������� �������� ������ ���� �����������-���������
//! @param   width   ������ ����������� �����������
//! @param   height  ������ ����������� �����������
//! @param   src     �������� ��������� (������ ����������)
//! @param   xSrc    �-���������� �������� ������ ���� �����������-���������
//! @param   ySrc    Y-���������� �������� ������ ���� �����������-���������
//! @param   alpha   ����� ������������ �����������, � ���������� � �����-������.\n
//!                    (0 - ��� ���������, 1 - ������������ ������ �����-�����)
//!
//!          ����������� ������ ���� ��������� � ������� txLoadImage() � �����
//!          32-������� RGBA-������. �������������� ����� (�����-�����) �����
//!          ������� �������� �� ������������ �������� �����������.
//!
//!          �����-����� ����� �������, ��������, � Adobe Photoshop, ��������
//!          "����� ����� (New Channel)" � ������� ������� (Channels). ������
//!          ���� � �����-������ ������������� ������ ������������, ����� -
//!          ������ ��������������. ��� ���� � ���������� �������� ���� �����������
//!          (� ������ RGB) ������ ���� ������.
//!
//!          ����������� ������� AlphaBlend �� Win32 API ����� �������������� �����������.
//!          � txAlphaBlend ��� ������ ��� ��������� �������������. If you still need image
//!          scaling, use original function AlphaBlend and don't mess with stupid TX-based
//!          tools. (See implementation of txAlphaBlend in TXLib.h).
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txBitBlt(), txTransparentBlt(), txLoadImage(), txCreateCompatibleDC()
//! @usage
//!          ������ ������������� ��. � ����� TX\Examples\Tennis\Tennis.cpp.
//! @code
//!          HDC batman = txLoadImage ("Resources\\Images\\Batman.bmp");
//!          if (!batman) MessageBox (txWindow(), "Call to batman failed", "Help yourself out", 0);
//!
//!          txAlphaBlend (txDC(), 0, 0, 800, 600, batman, 0, 0);
//!          txDeleteDC (batman);  // Don't worry, batman will return in "Batman returns"
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txAlphaBlend (HDC dest, double xDest, double yDest, double width, double height,
                   HDC src,  double xSrc,  double ySrc,  double alpha = 1.0);
//}

//===============================================================================================================================
//{          Drawing utilities
//! @name    ������ ������� ���������
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ��������� ���������� ����������� ����, �� ��������� �������.
//!
//!          ��� ������ ���������� ������������ ������� @ref txEnd().
//!
//! @warning ��������� ������������ �� ������ �����. ��� ����� �������� � ��������
//!          ����������� � ����. ���� � ��������� ��������� ��������, �� �����������
//!          ������� @ref txSleep(), ��� ��� ��� ������������� ��������� �����������,
//!          ���������� �� ��������� ����������.
//!
//! @return  �������� �������� ���������� (���� 0, �� ��������� ��������������).
//!
//! @see     txBegin(), txEnd(), txSleep(), txUpdateWindow(), txTextCursor()
//! @usage
//! @code
//!          txBegin();                        // ����� ����������� "���������"
//!          txSetFillColor (TX_WHITE);
//!          txClear();                        // ��� ������� �� ������� ��� txBegin()
//!          txSetFillColor (TX_RED);
//!          txRectangle (100, 100, 200, 200);
//!          txEnd();                          // ����� �� ����� ������ ������������� �������
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txBegin();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������������ ���������� ����, ��������������� �������� txBegin().
//!
//! @warning ���� txBegin() ���������� ��������� ���, �� ��� ������ ����������
//!          ��������� ������� �� ��� ������� txEnd().
//!
//! @return  �������� �������� ���������� (���� 0, �� ��������� ��������������).
//!
//! @see     txBegin(), txEnd(), txSleep(), txUpdateWindow(), txTextCursor()
//! @usage
//! @code
//!          txBegin();                        // ����� ����������� "���������"
//!          txSetFillColor (TX_WHITE);
//!          txClear();                        // ��� ������� �� ������� ��� txBegin()
//!          txSetFillColor (TX_RED);
//!          txRectangle (100, 100, 200, 200);
//!          txEnd();                          // ����� �� ����� ������ ������������� �������
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txEnd();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ����������� ���������� ��������� �� ������������ �����.
//!
//! @param   time  �������� � �������������
//!
//!          �� ����� �������� ���������� ����������� � ���� ������
//!          ������������� �������������� � ���� ����������������.
//!          ����� ����������, ���� ��� ����, �����������������.
//!
//! @return  ��������� ���������� ���������� ����.
//!
//! @see     txBegin(), txEnd(), txSleep(), txUpdateWindow()
//! @usage
//! @code
//!          txSleep (500); // ������� ����������
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSleep (int time);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Service
//! @brief   ��������� ��� ������������ ���������� ����������� � ����.
//!
//! @param   update  ����� ���������� (false - ��������� ����������)
//!
//!          � ������� �� txBegin() � txEnd(), ������� ������������ ��������� ������
//!          � �������� ��� "������ ��� ���������� ��������", txUpdateWindow() ���������
//!          ���� ���������� ��� ����� ����������.
//!
//!          ����� ������ ���������� � ���������� ��. � �������� @ref txBegin(), @ref txEnd() � @ref txSleep().
//!
//! @return  ���������� ��������� ������ ����������.
//!
//! @see     txBegin(), txEnd(), txSleep(), txUpdateWindow(), txTextCursor(), txLock(), txUnlock(), txGDI()
//! @usage
//! @code
//!          txUpdateWindow (false);
//!          ...
//!          txUpdateWindow();
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

inline bool txUpdateWindow (bool update = true);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ��������� ��� ��������� ��������� ��������� ������� � ����.
//!
//! @param   blink  false - ��������� �������� ������
//!
//! @return  ���������� �������� ����������.
//!
//! @see     txCreateWindow(), txUpdateWindow(), txLock(), txUnlock(), txGDI()
//! @usage
//! @code
//!          txTextCursor (false);
//!          ...
//!          txTextCursor();
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txTextCursor (bool blink = true);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! @brief   ������������� ������� ������������� ������ ���������.
//!
//! @param   x0  X-���������� �������� ������  ����
//! @param   y0  Y-���������� �������� ������  ����
//! @param   x1  X-���������� �������  ������� ����
//! @param   y1  Y-���������� �������  ������� ����
//!
//!          ���, ��� ����������� ��� ������� ���������, �� ��������.
//!
//!          ��������������� ������� TXLib �� ������������, �������������� ��
//!          ���� ����� ����������� ������� ������ � ��������� �� Win32 API.
//!
//! @return  ����������� �������������� �������. ���� ������ �� ������ ��� �� ���������� - NULL.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//! @usage
//! @code
//!          txSelectRegion (100, 100, 300, 400);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

HRGN txSelectRegion (double x0, double y0, double x1, double y1);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Service
//! @brief   ������������� ������� ������ GDI.
//!
//! @param   obj  ���������� ������� GDI
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), @ref TX_BLACK "�����", RGB()
//!          txSelectFont(), txSelectRegion()
//! @usage
//! @code
//!          HPEN pen = CreatePen (PS_DASH, 1, RGB (255, 128, 0));
//!          txSelectObject (pen);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txSelectObject (HGDIOBJ obj);

//}

//===============================================================================================================================
//{          Mouse
//! @name    ������ � �����
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Mouse
//! @brief   ���������� ������� ����!
//!
//! @return  ������� ���� ��� ��������� POINT.
//!
//! @see     txMouseX(), txMouseY(), txMousePos(), txMouseButtons()
//! @usage
//! @code
//!          RECT area = { 100, 100, 110, 110 };
//!
//!          while (txMouseButtons() != 1)
//!              {
//!              if (In (txMousePos(), area)) txTextOut (100, 100, "What are you doing here?!");
//!              txSleep (0);
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

POINT txMousePos();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Mouse
//! @brief   ���������� �-���������� ����!
//!
//! @return  �-���������� ����.
//!
//! @see     txMouseX(), txMouseY(), txMousePos(), txMouseButtons()
//! @usage
//! @code
//!          while (txMouseButtons() != 1)
//!              {
//!              txCircle (txMouseX(), txMouseY(), 20);
//!              txSleep (0);
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txMouseX();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Mouse
//! @brief   ���������� Y-���������� ����!
//!
//! @return  Y-���������� ����.
//!
//! @see     txMouseX(), txMouseY(), txMousePos(), txMouseButtons()
//! @usage
//! @code
//!          while (txMouseButtons() != 1)
//!              {
//!              txCircle (txMouseX(), txMouseY(), 20);
//!              txSleep (0);
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txMouseY();

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Mouse
//! @brief   ���������� ��������� ������ ����!
//!
//!          � ������������ �������� ������������ � ������� 1-� (�������)
//!          ��� �������� ������� ����� ������ ����, 2-� - ������, 3-� -
//!          �������.\n ��������, ������������ ����� 5 (�������� 101) ��������
//!          ������������� ������� ������� � ����� ������, �� �� ������ ������.
//!
//! @return  ��������� ������ ����!
//!
//! @see     txMouseX(), txMouseY(), txMousePos(), txMouseButtons()
//! @usage
//! @code
//!          while (txMouseButtons() != 3)
//!              {
//!              if (txMouseButtons() & 1) txCircle (txMouseX(), txMouseY(), 20);
//!              if (txMouseButtons() & 2) txLine   (txMouseX(), txMouseY(), 0, 0);
//!              txSleep (0);
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

int txMouseButtons();

//}

//===============================================================================================================================
//{          Other staff
//! @name    ������ �������� �������
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ���������� ������� ������� � ���������
//!
//! @param   arr  ��� �������
//!
//!          ������ sizearr() ����� ������ ������� � ������ �� ������ �������� �������,
//!          ���������� ������ ������� � ���������.
//!
//! @return  ������ ������� � ���������
//!
//! @warning ����������� ������� ������ � ��� �������� ������ ���� ��������
//!          � ����� ������������� sizearr(). ������ ������� � ������ ������ ����
//!          �������� ��� ����������.
//! @hideinitializer
//! @usage
//! @code
//!          POINT coord[] = { {110, 110}, {120, 120}, {130, 110}, {140, 120} };
//!
//!          for (int i = 0; i < sizearr (coord) - 1; i++)
//!              txLine (coord[i].x, coord[i].y, coord[i+1].x, coord[i+1].y);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

#define sizearr( arr )   ( sizeof (arr) / sizeof (arr)[0] )

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ��������, ��������� �� �������� � ������ ���������� ��������� [a; b]
//!
//! @param   x  ����������� ��������
//! @param   a  �����  ������� (������������)
//! @param   b  ������ ������� (������������)
//!
//! @return  ���� a <= x && x <= b, �� ������, ���� ��� - ����
//!
//! @hideinitializer
//! @usage
//! @code
//!          while (txMouseButtons() != 1)
//!              {
//!              if (In (txMouseX(), 110, 120)) txTextOut (100, 100, "Meet the wall!");
//!              txSleep (0);
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline
bool In (T x, T a, T b)
    {
    return a <= x && x <= b;
    }

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ��������, ��������� �� ����� pt ������ �������������� rect
//!
//! @param   pt    ����������� ����� � ���� <tt> POINT {x, y} </tt>
//! @param   rect  �������������     � ���� <tt> RECT  {left, top, right, bottom} </tt>
//!
//!          ������ ��� ���������� ������.
//!
//! @return  ��������� ��������
//!
//! @usage
//! @code
//!          RECT button = { 100, 100, 150, 120 };
//!
//!          txSetFillColor (TX_LIGHTGRAY);
//!          txRectangle (button.left, button.top, button.right, button.bottom);
//!
//!          txSetTextAlign();
//!          txSetFillColor (TX_WHITE);
//!          txTextOut (125, 115, "Cookie");
//!
//!          for (;;)
//!              {
//!              if (In (txMousePos(), button))
//!                  {
//!                  txSetFillColor (TX_TRANSPARENT);
//!                  txRectangle (button.left, button.top, button.right, button.bottom);
//!
//!                  if (txMouseButtons())
//!                      {
//!                      txSetFillColor (TX_DARKGRAY);
//!                      txRectangle (button.left, button.top, button.right, button.bottom);
//!
//!                      txSetFillColor (TX_WHITE);
//!                      txTextOut (125, 115, "You got cookie");
//!
//!                      break;
//!                      }
//!                  }
//!
//!              txSleep (0);
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------
//! @{

inline
bool In (const POINT& pt, const RECT& rect)
    {
    return In (pt.x, rect.left, rect.right) &&
           In (pt.y, rect.top,  rect.bottom);
    }

inline
bool In (const COORD& pt, const SMALL_RECT& rect)
    {
    return In (pt.X, rect.Left, rect.Right) &&
           In (pt.Y, rect.Top,  rect.Bottom);
    }

//! @}

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ��������� ��������� �����
//!
//! @param   range  ������ ������� ��������� (�� ������� ���� �������).
//!
//! @return  ��������� ����� ����� � ��������� [0; range).\n
//!
//!          �� ��� �������, ��� �������� ������ �������� � ����������� ����������? :)
//!
//! @hideinitializer
//! @usage
//! @code
//!          char message[100] = "Maybe...";
//!          sprintf ("You SUDDENLY got %d bucks now! Note that tax rate is $%d.", random (100), 100);
//!          MessageBox (txWindow(), message, "Lottery", 0);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

#define random( range )  ( rand() % (range) )

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ������������� �������� ����.
//!
//! @param   filename  ��� ��������� �����. ���� NULL - ������������� ����.
//! @param   mode      ����� ���������������
//!
//! @title   ������ ���������������: @table
//!          @tr SND_ASYNC       @td ���� ������������� ������������ � ������� ���������.\n
//!                                  ����� �������� ��������, �������� txPlaySound (NULL). @endtr
//!          @tr SND_SYNC        @td ���������� ��������� ������������������ �� ���������
//!                                  ��������������� �����. @endtr
//!          @tr SND_LOOP        @td ����������� ���� ��� ���������������.\n
//!                                  ����� �������� ��������, �������� txPlaySound (NULL).\n @endtr
//!          @tbr
//!          @tr SND_NODEFAULT   @td �� ������������ ���� �� ���������, ���� ������ ���������
//!                                  ��������� �������� ����. @endtr
//!          @tr SND_NOSTOP      @td ���� �����-���� ���� ��� �������������, �� �������������
//!                                  ��� ��� ��������������� ���������� �����. @endtr
//!          @tr SND_APPLICATION @td ����������� ����, ��������� ���������, ������������������
//!                                  ��� ������� ���� �������� ������. @endtr
//!          @endtable
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @note    �������������� ������ ����� � ������� WAV. ��������� ������� (MP3 � ��.) ����
//!          ��������������. �������������� �� ������ ���������� �� �������, ��� � � ������
//!          � �������� �������� � txLoadImage().
//! @usage
//! @code
//!          txPlaySound ("tada.wav"); // so happy that this always exists
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

bool txPlaySound (const char filename[] = NULL, DWORD mode = SND_ASYNC);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Service
//! @brief   ������ ����� ������ �������. ��. �������� �������.
//!
//!          � ���� ������� ���� ������� � ������� �������� ���������, ������� ��� � �����
//!          ����������, ����� @a ����������� ���� �������. ��� ����� [�����������]�������
//!          ��� ������������ ��� � ����������, ��� ���������.
//!
//! @return  ���� �������� ���� ������� - true, ����� - false.
//!
//! @see     txCreateWindow(), txSleep()
//! @usage
//! @code
//!          int main()
//!              {
//!              txCreateWindow (800, 600);
//!
//!              txSetTextAlign (TA_CENTER);
//!              txTextOut (txGetExtentX()/2, txGetExtentY()/2, "Press any key to exit!");
//!
//!              txIDontWantToHaveAPauseAfterMyProgramBeforeTheWindowWillCloseAndIWillNotBeAskingWhereIsMyPicture();
//!              return 0;
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

// See definition of this function below in this file.

bool txIDontWantToHaveAPauseAfterMyProgramBeforeTheWindowWillCloseAndIWillNotBeAskingWhereIsMyPicture();

//}

//===============================================================================================================================
//{          Back-hole (I hope, not an ass-hole:) of the library)
//! @name    ����� ��������� �������
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Service
//! @brief   ������������� �������������� ���������� ������� ��������� Windows.
//!
//! @param   handler  ����� �������������� ���������� ������� ����
//!
//!          ���������� ����� ���������� �� ��������� ������� ���������� TXLib.
//!          �� ������ ���� �������� �� ��������� ����������:
//! @code
//!          LRESULT CALLBACK NewWndProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam);
//! @endcode
//!
//! @warning ���������� ���������� �� ���������������� (�������) ������, ������������
//!          \ref txCreateWindow(). ��� @b �� ��� �� ����� �����, � ������� �����������
//!          main(). � ����� � ���� ������ ����������� ��� ������ � ����������� �����������
//!          ��� �� ���������, �.�. ����� ���������� "����� �� �������" (race condition).
//!
//! @warning ���� ���������� ������ ��������, �� ������ 0, ����������� ���������
//!          ��������� ���������� TXLib �� ������������. ��������, ��� ���� ��
//!          ������ ��������� ���������. �������� ��������� ��������� � �������
//!          Alt-Ctrl-Del �� ���������� �����, ��� �� ����� ������������ ����������
//!          <a href=http://technet.microsoft.com/en-us/sysinternals/bb896653.aspx>
//!          Process Explorer</a>. ���� �� ������ �� ���� ��������� �������� ���������,
//!          ������� �� �� �������� Win32 (��. MSDN), ������� ����� DefWindowProc().
//!
//! @return  ����� ����������� ��������������� ����������� ��������� ����.
//!
//! @note    ������ �������� ������� ������� ����� � ������� SetWindowLong/SetWindowLongPtr:
//! @code
//!          WNDPROC OldWndProc = (WNDPROC) SetWindowLongPtr (txWindow(), GWL_WNDPROC, (LONG_PTR) NewWndProc);
//! @endcode
//!          ��� ���� ���� ����������� ������ �������� ������ ������� ������� � ������� CallWindowProc(),
//!          (��. MSDN), ����� ����������� ����� ������ �� ����������, ��� ������� ����.
//!
//! @see     txCreateWindow(), txDialog, txInputBox()
//! @usage
//! @code
//!          LRESULT CALLBACK MyWndHandler (HWND window, UINT message, WPARAM wParam, LPARAM lParam);
//!
//!          int main()
//!              {
//!              txCreateWindow (800, 600);
//!
//!              txSetWindowProc (MyWndHandler);
//!
//!              txCircle (txGetExtentX()/2, txGetExtentY()/2, 100);
//!
//!              printf ("\n" "Still working ");
//!              }
//!
//!          LRESULT CALLBACK MyWndHandler (HWND window, UINT message, WPARAM wParam, LPARAM lParam)
//!              {
//!              static int i = 0;
//!              if (i++ % 10 == 0) printf ("\b" "%c", "-\\|/" [i/10 % 4]);
//!              return 0;
//!              }
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

WNDPROC txSetWindowHandler (WNDPROC handler);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Service
//! @brief   ���������� ������ (��������� ���������).
//!
//! @param   wait  ������� ����� ����������� ���� ��������������� �������
//!
//!          ����� ������� ����� ������� Win32 GDI ���������� �������������
//!          ����� �������� txLock() � ����� �������������� � ������� @ref txUnlock().
//!          ��� ������� � ���, ��� ���������� ����������� ���� (��� ���, ���
//!          ����� - ��������� ��������� WM_PAINT :) ���������� � ���������
//!          ��������������� ������. ������� ����������� ������ - ���
//!          ��������������� ������ ���� �� �����������.
//!
//!          txLock() ���������� EnterCriticalSection(), � ���������
//!          ���������������� �����, ����������� ����, ��� ��� �������
//!          ����������� ������. ����� ���������� ��������� ������� ���������
//!          � ���� ��������� ����������� �� �������� ������������.
//!
//!          txLock() /@ref txUnlock() - �������������� ��������, �� ���������� ��
//!          ���������������� ��������� @ref txBegin() / @ref txEnd() /@ref txUpdateWindow(),
//!          ������� �� ���������������� �����, � ������ ��������� �������� ��
//!          ���������� ����. � ������� �� @ref txBegin() / @ref txEnd(), �� ��
//!          ������������ �������� ������.
//!
//! @return  ��������� ����������
//!
//! @see     txDC(), txLock(), txUnlock(), txGDI()
//! @usage   ��. �������� ����� ������� _txCanvas_OnPaint() � _txConsole_Draw() � TXLib.h.
//!
//}------------------------------------------------------------------------------------------------------------------------------

inline bool txLock (bool wait = true);

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Service
//! @brief   ������������� ������
//!
//!          ����� �������� ��. � @ref txLock().
//!
//! @return  ��������� ���������� (������ false).
//!
//! @see     txDC(), txLock(), txGDI()
//! @usage
//! @code
//! @usage   ��. �������� ����� ������� _txCanvas_OnPaint() � _txConsole_Draw() � TXLib.h.
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------
//! @{

inline bool txUnlock();

template <typename T> inline
T    txUnlock (T value);

//! @}

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Service
//! @brief   ����� ������� Win32 GDI � �������������� ����������� � ��������������.
//!
//! @param   command  ������� GDI (��������, ������������ ��������)
//!
//! @return  ��������, ������������ ���������� �������� GDI.
//!
//! @note    ���� � ������ ������� GDI ������������ �������, �� ����������� �������
//!          ������, ����� ��������� ���� ��������, ��� ��� txGDI() ���-���� ������.
//!
//! @see     txDC(), txLock(), txUnlock()
//! @hideinitializer
//! @usage
//! @code
//!          txGDI (( Rectangle (txDC(), x1, y1, x2, y2) )); // �� �������� ��� ��� ������
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

#define txGDI( command )  txUnlock ( (txLock(), (command)) )

//}

//===============================================================================================================================
//{          Dialogs
//! @name    ������ � ����������� ������
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Dialogs
//! @brief   ������� ����� ��� ���������� ����.
//!
//!          ��� �������� ������ ����������� ���� �����:
//!           -# ������������ ���� ����� �� ����� �������� ������;
//!           -# ������ ������ � ������������ ��������� ���������� (���������)
//!              �������� txDialog::setLayout(), ��� ������� ����� ������������
//!              ��� ������ ����������� ���� �������� txDialog::dialogBox();
//!           -# �������������� � ����� ������ ������� txDialog::dialogProc() ���
//!              ��������� ������� ����������� ���� ��� ��������� ����� �������
//!              �� ������� � ������� �������� TX_BEGIN_MESSAGE_MAP(),
//!              TX_END_MESSAGE_MAP, TX_COMMAND_MAP.
//!
//! @see     txDialog::setLayout(), txDialog::dialogProc(), txDialog::Layout,
//! @see     TX_BEGIN_MESSAGE_MAP(), TX_END_MESSAGE_MAP, TX_COMMAND_MAP
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

struct txDialog
    {

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Dialogs
//! @brief   ��������� ��� ������� ���� ��������.
//!
//!          ������ �������� ����� ������������ �������� ������� �������,
//!          ��������������� � ���� txDialog::CONTROL.
//!
//! @see     txDialog::Layout, txDialog::setLayout()
//! @hideinitializer
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

    public:
    enum CONTROL
        {
        DIALOG    = 0x00000000,                  //!< ������ �������� �������
        BUTTON    = 0xFFFF0080,                  //!< ������
        EDIT      = 0xFFFF0081,                  //!< ������������� �����
        STATIC    = 0xFFFF0082,                  //!< ��������������� ������� (�����, �������� � �.�.)
        LISTBOX   = 0xFFFF0083,                  //!< ������ � ����������
        SCROLLBAR = 0xFFFF0084,                  //!< ������ ���������
        COMBOBOX  = 0xFFFF0085,                  //!< ��������������� ������
        END       = 0x00000000                   //!< ����� �������� �������
        };

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Dialogs
//! @brief   ����� ��� �������� �������� ����������� ���� (��������)
//!
//!          ������ ����� �������� ������ �������� ������ ����������� ����.
//!          ��� �������� ������ �� ������� ������� � ��������� ������� (.rc):
//!
//!           - ������� ������� ��������� ���������� ���� � �����
//!           - ��������� �������� ��������� ��������
//!           - ��������� ������� - txDialog::END ��� {NULL}
//!
//! @see     txDialog::setLayout(), txDialog::dialogBox(), txDialog::dialogProc()
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

    public:
    struct Layout
        {
        CONTROL     wndclass;                    //!< ��� ��������
        const char* caption;                     //!< �������� ��� �����
        WORD        id;                          //!< ������������� ��������
        short        x;                          //!< ���������� �������� ������ ����
        short        y;                          //!< ���������� ������� ������� ����
        short       sx;                          //!< ������ �� X
        short       sy;                          //!< ������ �� Y
        DWORD       style;                       //!< ����� ��������

        const char* font;                        //!< ����� ����������� ����
        WORD        fontsize;                    //!< ������ ������ ����������� ����
        };

//{------------------------------------------------------------------------------------------------------------------------------
//! @brief   �����������.
//! @see     txDialog::txDialog (const txDialog::Layout*)
//!
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

    public:
    txDialog();

//{------------------------------------------------------------------------------------------------------------------------------
//! @brief   �����������.
//!
//! @param   layout  ����� ����������� ����
//!
//! @see     txDialog::Layout, txDialog::setLayout()
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

    txDialog (const Layout* layout);

//{------------------------------------------------------------------------------------------------------------------------------
//! @brief   ����������.
//}------------------------------------------------------------------------------------------------------------------------------

    virtual ~txDialog() {};

//{------------------------------------------------------------------------------------------------------------------------------
//! @brief   ������������� ������� ����� ����������� ����.
//!
//! @param   layout  ����� ����������� ����
//!
//! @return  ���������� �����.
//!
//! @see     txDialog::Layout, txDialog::txDialog (const txDialog::Layout*), txDialog::dialogBox()
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

    const Layout* setLayout (const Layout *layout);

//{------------------------------------------------------------------------------------------------------------------------------
//! @brief   ������� ��������� ��������� ����������� ����.
//!
//! @param   _wnd     ����������
//! @param   _msg     ����� ���������
//! @param   _wParam  1-� �������� ��������� (WORD)
//! @param   _lParam  2-� �������� ��������� (DWORD)
//!
//!          ��� ������� ���� �������������� ��� ��������� ������� ����,
//!          ��� ��������� �� � ������� �������� TX_BEGIN_MESSAGE_MAP(),
//!          TX_END_MESSAGE_MAP, TX_COMMAND_MAP.
//!
//! @return  � ����������� ������� false, ��������� ��. DialogProc
//!          � <a href=msdn.com>MSDN</a>.
//!
//! @see     txDialog::dialogBox()
//! @see     TX_BEGIN_MESSAGE_MAP(), TX_END_MESSAGE_MAP, TX_COMMAND_MAP
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

    virtual int dialogProc (HWND _wnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

//{------------------------------------------------------------------------------------------------------------------------------
//! @brief   ��������� ���������� ����.
//!
//! @param   layout   ����� ����������� ����.\n
//!                     ���� �� ������ - ������������ ��������, �������� txDialog::setLayout()
//!                     ��� ������������� txDialog::txDialog (const txDialog::Layout*).
//! @param   bufsize  ������ ������ ��� �������� ������� ������� (���� �� ������ - ������ �� ���������)
//!
//! @return  ��������, ��������� � ������� EndDialog().\n
//!          �� ��������� - ����� ������� <i>(this),</i> ��� �������� ����
//!          �������� txDialog::dialogBox().
//!
//! @see     txDialog::dialogProc(), txDialog::setLayout(), txDialog::Layout, txDialog
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

    INT_PTR dialogBox (const Layout* layout = NULL, size_t bufsize = 0);

//{------------------------------------------------------------------------------------------------------------------------------
//! @brief   ��������� ���������� ����.
//!
//! @param   resource  ������������� ����������� �������
//!
//! @return  ��������, ��������� � ������� EndDialog().\n
//!          �� ��������� - ����� ������� <i>(this),</i> ��� �������� ����
//!          �������� txDialog::dialogBox().
//!
//! @see     txDialog::dialogProc()
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

    INT_PTR dialogBox (WORD resource);

//{------------------------------------------------------------------------------------------------------------------------------
//! @brief   �������� ����������� ����������� � �������� ������������.
//}------------------------------------------------------------------------------------------------------------------------------

    private:
    txDialog (const txDialog&);
    txDialog& operator = (const txDialog&);

//{------------------------------------------------------------------------------------------------------------------------------
//! ��������� ���������� ������� (�� @ref txDialog::dialogProc(), �.�. ������� ����
//! Win32 ������ ���� �����������).
//}------------------------------------------------------------------------------------------------------------------------------

    private:
    static int CALLBACK dialogProc__ (HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

//{------------------------------------------------------------------------------------------------------------------------------
//! ������� ����� �������.
//}------------------------------------------------------------------------------------------------------------------------------

    private:
    const Layout* layout_;
    };

//}

//===============================================================================================================================
//{          Message Map macros
//! @name    ������� ��� ���������� ����������� ����� ��������� (Message Map)
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ��������� ����� ��������� (Message Map).

//! @see     TX_BEGIN_MESSAGE_MAP(), TX_END_MESSAGE_MAP, TX_HANDLE(), TX_COMMAND_MAP,
//! @see     txDialog::dialogProc(), txDialog
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#define TX_BEGIN_MESSAGE_MAP()                                                     \
    virtual int dialogProc (HWND _wnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)  \
        {                                                                          \
        (void)_wnd; (void)_msg; (void)_wParam; (void)_lParam;                      \
                                                                                   \
        switch (_msg)                                                              \
            {                                                                      \
            case WM_NULL:

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ��������� ����������� ��������� (Message handler) ����� ���������.
//!
//! @param   id  ������������� ���������
//!
//! @see     TX_BEGIN_MESSAGE_MAP(), TX_END_MESSAGE_MAP, TX_HANDLE(), TX_COMMAND_MAP,
//! @see     txDialog::dialogProc(), txDialog
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#define TX_HANDLE( id )                                                            \
            break;                                                                 \
            case (id):

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ������ ����� ������ (Command map) � ����� ���������.

//! @see     TX_BEGIN_MESSAGE_MAP(), TX_END_MESSAGE_MAP, TX_HANDLE(), TX_COMMAND_MAP,
//! @see     txDialog::dialogProc(), txDialog
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#define TX_COMMAND_MAP                                                             \
            default: break;                                                        \
            }                                                                      \
                                                                                   \
        if (_msg == WM_COMMAND) switch (LOWORD (_wParam))                          \
            {                                                                      \
            case 0:

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Misc
//! @brief   ����������� ����� ���������.

//! @see     TX_BEGIN_MESSAGE_MAP(), TX_END_MESSAGE_MAP, TX_HANDLE(), TX_COMMAND_MAP,
//! @see     txDialog::dialogProc(), txDialog
//! @usage
//! @code
//!          C�. ���������� ������� txInputBox().
//! @endcode
//! @hideinitializer
//}------------------------------------------------------------------------------------------------------------------------------

#define TX_END_MESSAGE_MAP                                                         \
            default: break;                                                        \
            }                                                                      \
                                                                                   \
        return FALSE;                                                              \
        }
//}

//===============================================================================================================================
//{          txDialog example: txInputBox()
//! @name    ������ ������������� ������ �������: ������� txInputBox()
//===============================================================================================================================

//{------------------------------------------------------------------------------------------------------------------------------
//! @ingroup Dialogs
//! @brief   ���� ������ � ��������� ����.
//!
//! @param   text     ����� � ��������
//! @param   caption  ��������� ����
//! @param   input    �������� ������ �� ���������
//!
//! @return  ��������� ������ (����������� ���������� �������).
//!
//! @warning ������������ ������ - �����������, � ����������� ��� ������ ������ �������.
//!          ���� txInputBox() ����� ���������� ��������� ���, �� ��� ���������� ������
//!          �� ���������� ���������� � ������ ������ ��� ������ <i>strcpy()</i>.
//! @see     txDialog, TX_BEGIN_MESSAGE_MAP, TX_BEGIN_COMMAND_MAP, TX_HANDLE, TX_END_MESSAGE_MAP
//! @usage
//! @code
//!          const char* name = txInputBox ("So what's ur name??!", "System", "Sorry I'm Vasya Pupkin");
//!          MessageBox (txWindow(), name, "Aaand nooowww.. the winner iiis...", 0);
//! @endcode
//}------------------------------------------------------------------------------------------------------------------------------

const char* txInputBox (const char* text = NULL, const char* caption = NULL, const char* input = NULL)
    {
    //---------------------------------------------------------------------------------------------------------------------------
    // ��������� ����� EXE-�����, �� ������, ���� ���-��� ��������� ������ �������� �������
    //---------------------------------------------------------------------------------------------------------------------------

$   char name[256] = ""; GetModuleFileName (NULL, name, sizeof (name) - 1);

    //---------------------------------------------------------------------------------------------------------------------------
    // ���� �� ������� ���������, ������������ �����-����� ������� �������. � ��� ������?..
    //---------------------------------------------------------------------------------------------------------------------------

$   if (!text)    text    = "������� ������:";
$   if (!caption) caption = name;
$   if (!input)   input   = "";

    //---------------------------------------------------------------------------------------------------------------------------
    // �������������� ��������� �������. ��� ��������� � GetDlgItemText().
    // ���� ������ �������� �� �������, � ���������� ��������, �� ��� �������� � ��� �������������.
    // � ��� �� ��� - ������� �����, � ���������. ������� � ���, ��� � ������ ���� ����������������
    // ������ ��������� �������� � ������� ������. ������� ��� ������������� �� ��� ��� �����
    // ��������� �� ����� ����������, �����������. �� ��� ����������, ��� ��� ����� �����������
    // � txDialog::dialogBox() � _tx_DLGTEMPLATE_()... �_�
    //---------------------------------------------------------------------------------------------------------------------------

    #define ID_TEXT_  101
    #define ID_INPUT_ 102

    //---------------------------------------------------------------------------------------------------------------------------
    // ������� ������ (����) ������� � ���� ������� ��������.
    // � ������� ������� ������� ����� � ��������� txDialog::Layout � �������� �� ������
    // txDialog ���� ������ ���������� ����� �� �������� ������� ������� � .rc - �����.
    // ��. �������� ���������� rc-����� � ������������ �� Win32 (MSDN, http://msdn.com).
    //---------------------------------------------------------------------------------------------------------------------------

$   txDialog::Layout layout[] =

    //----------------------+-----------+-------------+-----------------+--------------------------------------------------------
    //     ��� ��������     | ���       | ����������- |   ����������    | ����� ���������
    //     �������          | ��������  | ���, ������-|-----------------| (��. �������� ��������� ������� � MSDN).
    //                      |           | ��� � ���   | X | Y |���.|���.|
    //----------------------+-----------+-------------+---+---+----+----+--------------------------------------------------------
    //                      |           |             |   |   |    |    |
        {{ txDialog::DIALOG,   caption,   0,             0,  0, 240,  85                                                     },
         { txDialog::STATIC,   text,      ID_TEXT_,     10, 10, 150,  40, SS_LEFT                                            },
         { txDialog::EDIT,     input,     ID_INPUT_,    10, 60, 220,  15, ES_LEFT | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP  },
         { txDialog::BUTTON,   "&OK",     IDOK,        180, 10,  50,  15, BS_DEFPUSHBUTTON                     | WS_TABSTOP  },
         { txDialog::BUTTON,   "&Cancel", IDCANCEL,    180, 30,  50,  15, BS_PUSHBUTTON                        | WS_TABSTOP  },
         { txDialog::END                                                                                                     }};

    //---------------------------------------------------------------------------------------------------------------------------
    // ����� ������� ��� InputBox. ����������, �.�. ����� ��� ���� �������.
    // ����� � �������� ��� ������� ������ ����� (str) � ������� ������� ����������� ����,
    // ��������� Win32 (��� ��������� ��������� TX_BEGIN_MESSAGE_MAP � �������). ����� �� ������
    // ����������� ������, �� ����� ������� ������� �������� ������ � ���������� ������� ���������,
    // � str ��������� ��������� ���� (��� ���������� �� ����� ����� DialogBoxParam � ����������
    // ��� � ����� �� ����� ��������� WM_INITDIALOG).
    //---------------------------------------------------------------------------------------------------------------------------

    struct inputDlg : txDialog
        {
        char str [1024];

        //-----------------------------------------------------------------------------------------------------------------------

        inputDlg() :
            str()                               // ��������� ���� ������. �� �������� �� ������
            {                                   //     ������������, ������� ��� ���:
$           memset (str, 0, sizeof (str) - 1);  // ��������� ���� ������
            }

        //-----------------------------------------------------------------------------------------------------------------------

        TX_BEGIN_MESSAGE_MAP()    // ����� ���������. �� ����� ���� ��� ������ ������� �������.

            TX_COMMAND_MAP        // ����� �������������� WM_COMMAND. �� ����� ���� ��� switch.

                //---------------------------------------------------------------------------------------------------------------
                // ��� ������� ������ OK �������� ������ �� ���� ����� � ���� ���������� str,
                // �.�. ����� �������� ������� ������ ����� ����� � ����� ��� �� ��� ��������.
                // ���� ������ �� ����� ���� ������������ � case �� ��������� switch.
                // _wnd - ��� �������� ������� �������, ��. ����������� ������� TX_BEGIN_MESSAGE_MAP().
                //---------------------------------------------------------------------------------------------------------------

                TX_HANDLE (IDOK) $ GetDlgItemText (_wnd, ID_INPUT_, str, sizeof (str) - 1);

        TX_END_MESSAGE_MAP

        //-----------------------------------------------------------------------------------------------------------------------
        // ����� ����������� ������ �������
        //-----------------------------------------------------------------------------------------------------------------------

        };

    //---------------------------------------------------------------------------------------------------------------------------
    // ������� �������, ����� ����� �� ������.
    // �� ����� ��� ���������� "���������� ��������", ��� ����� � ��� ���� �� ������� ��������� -
    // �������. �� ����� ���� ��� ������� ������� ����� #undef. ����� ����������� �� ���������
    // �������, � ��� ����� ������������� �� _. ����� �������� ����� �� ����������� ���� ��� �����
    // ���� ���, ����������, ����� ��� �� �����.
    //---------------------------------------------------------------------------------------------------------------------------

    #undef ID_TEXT_
    #undef ID_INPUT_

    //---------------------------------------------------------------------------------------------------------------------------
    // ��� ����������� ������, ������ ��� ������ � ��� ������ ���� ����� ���������� �������.
    //---------------------------------------------------------------------------------------------------------------------------

$   static inputDlg dlg;

    //---------------------------------------------------------------------------------------------------------------------------
    // �������� layout � ��������� ���� �������
    //---------------------------------------------------------------------------------------------------------------------------

$   dlg.dialogBox (layout);

    //---------------------------------------------------------------------------------------------------------------------------
    // ���������� ����� ������ �� ������������ �������. ��� ����� ������, ������ ��� �����������
    // ������ �� ����� ��� ������ �� ������� � ������ � ���, ��������������, ����. �����
    // ������������� ���������� ���������� ������������� �����, �� ����� � ��������� �������.
    //---------------------------------------------------------------------------------------------------------------------------

$   return dlg.str;
    }

//}

//}

//===============================================================================================================================
//{          TXLib implementation
//! @name    ���������� ������� ����������
//===============================================================================================================================
//! @cond    INTERNAL

//===============================================================================================================================
//{          [Internal] Function prototypes
//! @name    ��������� ���������� �������
//===============================================================================================================================

bool         _txCleanup();
void         _txOnExit();

HWND         _txCanvas_CreateWindow (SIZE size);
bool         _txCanvas_OK();
bool         _txConsole_InitSTDIO();
bool         _txCanvas_DestroyWindow();
int          _txCanvas_SetRefreshLock (int count);
bool         _txCanvas_OnCreate     (HWND wnd);
bool         _txCanvas_OnDestroy    (HWND wnd);
bool         _txCanvas_OnClose      (HWND);
bool         _txCanvas_OnPaint      (HWND wnd);
bool         _txCanvas_OnChar       (HWND wnd, WPARAM ch);
bool         _txCanvas_OnTimer      (HWND wnd, WPARAM id);
bool         _txCanvas_OnMouse      (HWND wnd, WPARAM buttons, LPARAM coords);
bool         _txCanvas_OnCmdAbout   (HWND wnd, WPARAM cmd);
bool         _txCanvas_OnCmdConsole (HWND wnd, WPARAM cmd);
LRESULT CALLBACK _txCanvas_WndProc  (HWND wnd, UINT msg, WPARAM wpar, LPARAM lpar);
DWORD   WINAPI   _txCanvas_ThreadProc (LPVOID data);

HDC          _txBuffer_Create (HWND wnd, const POINT* size = NULL, HBITMAP bmap = NULL);
bool         _txBuffer_Delete (HDC dc);
bool         _txBuffer_Select (HGDIOBJ obj, HDC dc = txDC());

bool         _txConsole_Attach();
bool         _txConsole_OK();
bool         _txConsole_Detach();
bool         _txConsole_Draw (HDC dc);
HWND         _txConsole_GetWindow();

void*        _tx_DLGTEMPLATE_Create (void* globalMem, size_t bufsize, DWORD style, DWORD exStyle,
                                     WORD controls, short x, short y, short cx, short cy,
                                     const char caption[], const char font[], WORD fontsize,
                                     HANDLE menu = NULL);
void*        _tx_DLGTEMPLATE_Add    (void* dlgTemplatePtr, size_t bufsize, DWORD style, DWORD exStyle,
                                     short x, short y, short cx, short cy,
                                     WORD id, const char wclass[], const char caption[]);

bool         _txThrow (const char file[], int line, const char func[], DWORD error,
                       const char msg[], ...) _TX_CHECK_FORMAT (5);
bool         _txCheck (const char msg[] = NULL);

#define      _txWaitFor(p)   { for (int __i##__LINE__ = 0; __i##__LINE__ < _TX_TIMEOUT/10; __i##__LINE__++) \
                                 { if ((p) != 0) break; Sleep (10); } }
//}

//===============================================================================================================================
//{          [Internal] DLL functions import
//! @name    ������ ������� ���������
//===============================================================================================================================

FARPROC _txImport (const char lib[], const char name[], int required = true)
    {
$   HMODULE dll  = LoadLibrary (lib);
$   if (!dll  && required) TX_THROW ("\aCannot load %s" _ lib);
$   if (!dll) return NULL;

$   FARPROC addr = GetProcAddress (dll, name);
$   if (!addr && required) TX_THROW ("\aCannot import %s\\%s" _ lib _ name);

$   return addr;
    }

//-------------------------------------------------------------------------------------------------------------------------------
//{          Import helpers
//! @name    ����� �����������
//-------------------------------------------------------------------------------------------------------------------------------

#define _TX_IMPORT( lib, retval, name, params ) \
     retval (WINAPI* name) params = (retval (WINAPI*) params) _txImport (lib ".dll", #name, true)

#define _TX_IMPORT_OPT( lib, retval, name, params ) \
     retval (WINAPI* name) params = (retval (WINAPI*) params) _txImport (lib ".dll", #name, false)

//}

//----------------------------------------------------------------------------
// Some IDEs don't link with these libs by default in console projects, so do sunrise by hand. :(
//{ <tears>

namespace Win32 {

_TX_IMPORT ("GDI32", int,      GetDeviceCaps,          (HDC dc, int index));
_TX_IMPORT ("GDI32", HDC,      CreateCompatibleDC,     (HDC dc));
_TX_IMPORT ("GDI32", HBITMAP,  CreateCompatibleBitmap, (HDC dc, int width, int height));
_TX_IMPORT ("GDI32", HGDIOBJ,  GetStockObject,         (int object));
_TX_IMPORT ("GDI32", HGDIOBJ,  SelectObject,           (HDC dc, HGDIOBJ object));
_TX_IMPORT ("GDI32", HGDIOBJ,  GetCurrentObject,       (HDC dc, UINT objectType));
_TX_IMPORT ("GDI32", int,      GetObjectA,             (HGDIOBJ obj, int bufsize, LPVOID buffer));
_TX_IMPORT ("GDI32", BOOL,     DeleteDC,               (HDC dc));
_TX_IMPORT ("GDI32", BOOL,     DeleteObject,           (HGDIOBJ object));
_TX_IMPORT ("GDI32", COLORREF, SetTextColor,           (HDC dc, COLORREF color));
_TX_IMPORT ("GDI32", int,      SetBkMode,              (HDC dc, int bkMode));
_TX_IMPORT ("GDI32", HFONT,    CreateFontA,            (int height, int width, int escapement, int orientation,
                                                        int weight, DWORD italic, DWORD underline, DWORD strikeout,
                                                        DWORD charSet, DWORD outputPrec, DWORD clipPrec,
                                                        DWORD quality, DWORD pitchAndFamily, LPCTSTR face));
_TX_IMPORT ("GDI32", int,      EnumFontFamiliesExA,    (HDC dc, LPLOGFONT logFont, FONTENUMPROC enumProc,
                                                        LPARAM lParam, DWORD reserved));
_TX_IMPORT ("GDI32", COLORREF, SetPixel,               (HDC dc, int x, int y, COLORREF color));
_TX_IMPORT ("GDI32", COLORREF, GetPixel,               (HDC dc, int x, int y));
_TX_IMPORT ("GDI32", HPEN,     CreatePen,              (int penStyle, int width, COLORREF color));
_TX_IMPORT ("GDI32", HBRUSH,   CreateSolidBrush,       (COLORREF color));
_TX_IMPORT ("GDI32", BOOL,     MoveToEx,               (HDC dc, int x, int y, LPPOINT point));
_TX_IMPORT ("GDI32", BOOL,     LineTo,                 (HDC dc, int x, int y));
_TX_IMPORT ("GDI32", BOOL,     Polygon,                (HDC dc, CONST POINT* points, int n));
_TX_IMPORT ("GDI32", BOOL,     Rectangle,              (HDC dc, int x0, int y0, int x1, int y1));
_TX_IMPORT ("GDI32", BOOL,     Ellipse,                (HDC dc, int x0, int y0, int x1, int y1));
_TX_IMPORT ("GDI32", BOOL,     Arc,                    (HDC dc, int x0, int y0, int x1, int y1,
                                                        int xStart, int yStart, int xEnd, int yEnd));
_TX_IMPORT ("GDI32", BOOL,     Pie,                    (HDC dc, int x0, int y0, int x1, int y1,
                                                        int xStart, int yStart, int xEnd, int yEnd));
_TX_IMPORT ("GDI32", BOOL,     Chord,                  (HDC dc, int x0, int y0, int x1, int y1,
                                                        int xStart, int yStart, int xEnd, int yEnd));
_TX_IMPORT ("GDI32", BOOL,     TextOutA,               (HDC dc, int x, int y, LPCTSTR string, int length));
_TX_IMPORT ("GDI32", UINT,     SetTextAlign,           (HDC dc, UINT mode));
_TX_IMPORT ("GDI32", BOOL,     GetTextExtentPoint32A,  (HDC dc, LPCTSTR string, int length, LPSIZE size));
_TX_IMPORT ("GDI32", BOOL,     ExtFloodFill,           (HDC dc, int x, int y, COLORREF color, UINT type));
_TX_IMPORT ("GDI32", BOOL,     BitBlt,                 (HDC dest, int xDest, int yDest, int width, int height,
                                                        HDC src,  int xSrc,  int ySrc,  DWORD rOp));
_TX_IMPORT ("GDI32", BOOL,     PatBlt,                 (HDC dc, int x0, int y0, int width, int height, DWORD rOp));
_TX_IMPORT ("GDI32", int,      SetROP2,                (HDC dc, int mode));
_TX_IMPORT ("GDI32", HRGN,     CreateRectRgn,          (int x0, int y0, int x1, int y1));
_TX_IMPORT ("GDI32", BOOL,     GetBitmapDimensionEx,   (HBITMAP bitmap, LPSIZE dimensions));

_TX_IMPORT ("USER32",HANDLE,   LoadImageA,             (HINSTANCE inst, LPCTSTR name, UINT type,
                                                        int sizex, int sizey, UINT mode));
_TX_IMPORT ("WinMM", BOOL,     PlaySound,              (LPCSTR sound, HMODULE mod, DWORD mode));

_TX_IMPORT_OPT ("MSImg32",BOOL,TransparentBlt,         (HDC dest, int destX, int destY, int destWidth, int destHeight,
                                                        HDC src,  int srcX,  int srcY,  int srcWidth,  int srcHeight,
                                                        UINT transparentColor));
_TX_IMPORT_OPT ("MSImg32",BOOL,AlphaBlend,             (HDC dest, int destX, int destY, int destWidth, int destHeight,
                                                        HDC src,  int srcX,  int srcY,  int srcWidth,  int srcHeight,
                                                        BLENDFUNCTION blending));
}  // namespace Win32
using namespace Win32;

//} </tears>

//}

//===============================================================================================================================
//{          [Internal] Global data
//! @name    ���������� ������
//           �� ��������� � ��������� ��� �����, ��� ����, ����� ��� ������� �� ���� :)
//===============================================================================================================================

HANDLE           _txCanvas_Thread       = NULL;   // The thread that owns the TXLib window
HWND             _txCanvas_Wnd          = NULL;

// To make background screen updating smooth, screen refresh process is:
// 1) BackBuf [0 == Main TXLib memory DC] --copied to--> BackBuf [1 == intermediate buffer].
// 2) Console text is drawing on BackBuf [1 == intermediate buffer].
// 3) BackBuf [1 == intermediate buffer]  --copied to--> Screen DC.

HDC              _txCanvas_BackBuf[2]   = {NULL,  // [0] Main TXLib memory DC
                                           NULL}; // [1] intermediate buffer for console text

CRITICAL_SECTION _txCanvas_LockBackBuf  = {0};    // Prevent simultanuous asccess to back buffer,
                                                  //     see txLock()/txUnlock()

UINT             _txCanvas_RefreshTimer = 0;      // Timer to redraw TXLib window

int              _txCanvas_RefreshLock  = 0;      // Blocks automatic on-timer redraw,
                                                  //     see txBegin()/txEnd()

HWND             _txConsole_Wnd         = NULL;   // Console window associated to process
bool             _txConsole_CursorMode  = true;   // To blink or not to blink, that is the question.

bool             _txRunning             = false;
bool             _txExit                = false;  // Setting this to true just before return from
                                                  //     main(), automatically closes the window.
POINT            _txMousePos            = {0};
int              _txMouseButtons        =  0;

WNDPROC          _txAltWndProc          = NULL;   // Alternative WndProc, for @ref txSetWindowHandler()

//}

//===============================================================================================================================
//{          TXLib engine init/check/cleanup
//! @name    �������������/��������/���������� TXLib
//===============================================================================================================================

//-------------------------------------------------------------------------------------------------------------------------------
//{          Start tracing output
//-------------------------------------------------------------------------------------------------------------------------------

#ifndef NDEBUG

int  _txInitTrace = (OutputDebugString ("\n"),
                     OutputDebugString ("The Dumb Artist Library - " _TX_VERSION " " _TX_AUTHOR ": "
                                        "\"" __FILE__ "\", compiled "__DATE__ " " __TIME__ "\n"),
                     OutputDebugString ("\n"), 1);
#endif

//}

//-------------------------------------------------------------------------------------------------------------------------------

bool txCreateWindow (double sizeX, double sizeY, bool centered /*= true*/)
    {
$   if (txOK()) return false;

$   atexit (_txOnExit);

$   _txExit     = false;
$   _txRunning  = false;  // _txCanvas_OnCreate will set it to true

$   InitializeCriticalSection (&_txCanvas_LockBackBuf);

$   _txConsole_Attach();

$   SIZE size = { (int)sizeX, (int)sizeY };
$   if (centered) { size.cx *= -1; size.cy *= -1; }

$   DWORD id = 0;
$   _txCanvas_Thread = CreateThread (NULL, 0, _txCanvas_ThreadProc, &size, 0, &id);  // Where REAL creation is...
$   _txCanvas_Thread || TX_THROW ("Cannot create _txCanvas_Thread: CreateThread() failed");
$   _txWaitFor (_txCanvas_OK());
$   _txCanvas_OK()   || TX_THROW ("Cannot create canvas window");

$   txSetDefaults();

$   SetLastError (0);
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txSetDefaults()
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   txUpdateWindow (false);
$   txLock();

//{  Set defaults for graphics layer

$   RECT r = {0};

$   GetClientRect (_txCanvas_Wnd,  &r) TX_NEEDED;
$   SIZE szCanvas = { r.right - r.left, r.bottom - r.top };

$   GetClientRect (_txConsole_Wnd, &r) TX_NEEDED;
$   SIZE szCon    = { r.right - r.left, r.bottom - r.top };

$   _txBuffer_Select (GetStockObject (WHITE_PEN),   txDC()) TX_NEEDED;
$   _txBuffer_Select (GetStockObject (WHITE_BRUSH), txDC()) TX_NEEDED;
$   _txBuffer_Select (CreateFont (szCon.cy/25, szCon.cx/80, 0, 0,
                                  FW_REGULAR, FALSE, FALSE, FALSE,
                                  DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                  DEFAULT_QUALITY, DEFAULT_PITCH, _TX_CONSOLE_FONT),
                                  txDC()) TX_NEEDED;

$   Win32::SetTextColor (txDC(), TX_WHITE);
$   Win32::SetBkMode    (txDC(), TRANSPARENT) TX_NEEDED;

$   Win32::SetROP2      (txDC(), R2_COPYPEN) TX_NEEDED;

//}

//{  Set defaults for console  layer

$   HDC dc = _txCanvas_BackBuf[1]; dc TX_NEEDED;

$   CONSOLE_SCREEN_BUFFER_INFO con = {{0}};
$   GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &con) TX_NEEDED;

$   SIZE szChr  = { (short) (con.srWindow.Right  - con.srWindow.Left + 1),
                    (short) (con.srWindow.Bottom - con.srWindow.Top  + 1) };

$   SIZE szFont = { (short) ((1.0 * szCon.cx / szChr.cx) / (1.0 * szCon.cx / szCanvas.cx)),
                    (short) ((1.0 * szCon.cy / szChr.cy) / (1.0 * szCon.cy / szCanvas.cy)) };

$   _txBuffer_Select (txFontExist (_TX_CONSOLE_FONT)? CreateFont (szFont.cy, szFont.cx, 0, 0,
                                                                  FW_REGULAR, FALSE, FALSE, FALSE,
                                                                  DEFAULT_CHARSET,
                                                                  OUT_DEFAULT_PRECIS,
                                                                  CLIP_DEFAULT_PRECIS,
                                                                  DEFAULT_QUALITY, FIXED_PITCH,
                                                                  _TX_CONSOLE_FONT)
                                              :
                                              GetStockObject (SYSTEM_FIXED_FONT),
               dc) TX_NEEDED;

$   Win32::SetTextColor (dc, _TX_CONSOLE_COLOR);
$   Win32::SetBkMode    (dc, TRANSPARENT) TX_NEEDED;

//}

$   txUnlock();
$   txUpdateWindow (true);

    return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
bool txOK()
    {
$   return _txConsole_OK() &&
           _txCanvas_OK();
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCheck (const char msg[])
    {
$   if (txOK()) return true;

$   MessageBox (txWindow(), "������: ���� ��������� �� �������!    ", (msg && *msg)? msg : "TXLib", MB_ICONSTOP);

$   exit (1); //  �� ��������� ������ �������� � ����� ������� � ���������� ���������� ������ ���. :(

//  return false;
    }

//-------------------------------------------------------------------------------------------------------------------------------

void _txOnExit()
    {
$   _txRunning = false;

$   Sleep (10);
$   if (!_txExit) WaitForSingleObject (_txCanvas_Thread, INFINITE);

$   if (_txCanvas_Thread)
        {
$       CloseHandle (_txCanvas_Thread) TX_NEEDED;
$       _txCanvas_Thread = NULL;
        }

$   _txConsole_Detach();

$   DeleteCriticalSection (&_txCanvas_LockBackBuf);

#ifndef NDEBUG
    OutputDebugString ("\n");
    OutputDebugString (_TX_VERSION " -- FINISHED\n");
    OutputDebugString ("\n");
#endif
    }

//}

//===============================================================================================================================
//{          [Internal] Main window functions      (_txCanvas...)
//! @name    ������� ��������� ����                (_txCanvas...)
//===============================================================================================================================

DWORD WINAPI _txCanvas_ThreadProc (LPVOID data)
    {
$   assert (data);

$   _txCanvas_CreateWindow (*(SIZE*) data);
$   _txCanvas_Wnd || TX_THROW ("Cannot create canvas: _txCanvas_CreateWindow() failed");

$   MSG msg = {0};
$   while (GetMessage  (&msg, NULL, 0, 0))
        {
$       TranslateMessage (&msg);
$       DispatchMessage  (&msg);

$       Sleep (0);
        }

$   return (DWORD) msg.wParam;
    }

//-------------------------------------------------------------------------------------------------------------------------------

HWND _txCanvas_CreateWindow (SIZE clientSize)
    {
$   const char className[] = __FILE__ "\\_txCanvas\\Class";

$   WNDCLASSEX wc    = {0};
$   wc.cbSize        = sizeof (wc);
$   wc.style         = CS_HREDRAW | CS_VREDRAW;
$   wc.lpfnWndProc   = _txCanvas_WndProc;
$   wc.hInstance     = NULL;
$   wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
$   wc.hbrBackground = (HBRUSH) GetStockObject (HOLLOW_BRUSH);
$   wc.lpszClassName = className;
$   RegisterClassEx (&wc) || TX_THROW ("RegisterClass (\"%s\") failed"_ className);

$   char name[256] = ""; GetModuleFileName (NULL, name, sizeof (name) - 1) TX_NEEDED;
$   strncat_s (name, " - TXLib", sizeof (name));
$   const char* title = strrchr (name, '\\'); title = title? title+1 : name;

$   int centered = false;
$   if (clientSize.cx < 0 && clientSize.cy < 0) { clientSize.cx *= -1; clientSize.cy *= -1; centered = true; }

$   SIZE scr     = { GetSystemMetrics (SM_CXSCREEN),     GetSystemMetrics (SM_CYSCREEN)     };
$   SIZE frame   = { GetSystemMetrics (SM_CXFIXEDFRAME), GetSystemMetrics (SM_CYFIXEDFRAME) };
$   SIZE caption = { 0, GetSystemMetrics (SM_CYCAPTION) };
$   SIZE size    = { clientSize.cx + 2*frame.cx, clientSize.cy + 2*frame.cy + caption.cy };
$   POINT center = { scr.cx / 2, scr.cy / 2 };

$   if (!centered)
        {
$       RECT r = {0}; GetWindowRect (_txConsole_Wnd, &r) TX_NEEDED;
$       center.x = (r.right + r.left) / 2;
$       center.y = (r.bottom + r.top) / 2;
        }

$   _txCanvas_Wnd = CreateWindowEx (0, className, title, WS_POPUP | WS_BORDER | WS_CAPTION | WS_SYSMENU,
                                    center.x - size.cx/2, center.y - size.cy/2, size.cx, size.cy,
                                    NULL, NULL, NULL, NULL);
$   _txCanvas_Wnd || TX_THROW ("Cannot create canvas: CreateWindowEx (\"%s\") failed"_ className);

$   ShowWindow          (_txCanvas_Wnd, SW_SHOW);
$   SetForegroundWindow (_txCanvas_Wnd) TX_NEEDED;
$   UpdateWindow        (_txCanvas_Wnd) TX_NEEDED;

$   if (_txConsole_Wnd)
        {
$       int hide = 0;

        #ifndef _TX_NO_HIDE_CONSOLE
$       hide = SWP_HIDEWINDOW;
        #endif

$       SetWindowPos (_txConsole_Wnd, HWND_NOTOPMOST, center.x - size.cx*2/5, center.y - size.cy*2/5, 0, 0,
                      SWP_NOSIZE | SWP_NOACTIVATE | hide) TX_NEEDED;

$       HMENU menu = GetSystemMenu (_txCanvas_Wnd, false); menu TX_NEEDED;
$       AppendMenu (menu, MF_SEPARATOR, 0, NULL) TX_NEEDED;
$       AppendMenu (menu, MF_STRING | MF_UNCHECKED, _TX_IDM_CONSOLE, "Show Console")     TX_NEEDED;
$       AppendMenu (menu, MF_STRING | MF_UNCHECKED, _TX_IDM_ABOUT,   "About Library...") TX_NEEDED;
$       CheckMenuItem (menu,  _TX_IDM_CONSOLE, (IsWindowVisible (_txConsole_Wnd))? MF_CHECKED : MF_UNCHECKED);
        }

$   return _txCanvas_Wnd;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OK()
    {
$   return _txCanvas_Thread     &&
           _txCanvas_Wnd        &&
           _txCanvas_BackBuf[0] &&
           _txCanvas_BackBuf[1];
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_DestroyWindow()
    {
$   if (!_txCanvas_Wnd) return false;

$   char className[128] = "";
$   GetClassName (_txCanvas_Wnd, className, sizeof (className) - 1) TX_NEEDED;

$   DestroyWindow (_txCanvas_Wnd) TX_NEEDED;

$   HMODULE exe = GetModuleHandle (NULL);
$   if (exe) UnregisterClass (className, exe) TX_NEEDED;

$   _txCanvas_Wnd = NULL;
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

int _txCanvas_SetRefreshLock (int count)
    {
$   int oldCount = _txCanvas_RefreshLock;

$   _txCanvas_RefreshLock = count;

$   if (_txCanvas_RefreshLock <= 0 || oldCount <= 0)
        if (_txCanvas_Wnd)
            {
$           InvalidateRect (_txCanvas_Wnd, NULL, false);
$           UpdateWindow   (_txCanvas_Wnd);
            }

$   return oldCount;
    }

//}

//===============================================================================================================================
//{          [Internal] Main window event handlers (_txCanvas_On...)
//! @name    ������� ��������� ����                (_txCanvas_On...)
//===============================================================================================================================

bool _txCanvas_OnCreate (HWND wnd)
    {
$   _txRunning = true;

$   _txCanvas_BackBuf[0] = _txBuffer_Create (wnd); _txCanvas_BackBuf[0] TX_NEEDED;
$   _txCanvas_BackBuf[1] = _txBuffer_Create (wnd); _txCanvas_BackBuf[1] TX_NEEDED;

$   SetTimer (wnd, _txCanvas_RefreshTimer, _TX_WINDOW_UPDATE_INTERVAL, NULL)   TX_NEEDED;

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OnDestroy (HWND wnd)
    {
$   if (_txCanvas_RefreshTimer) KillTimer (wnd, _txCanvas_RefreshTimer) TX_NEEDED;

$   if (_txCanvas_BackBuf[0]) _txBuffer_Delete (_txCanvas_BackBuf[0]); _txCanvas_BackBuf[0] = NULL;
$   if (_txCanvas_BackBuf[1]) _txBuffer_Delete (_txCanvas_BackBuf[1]); _txCanvas_BackBuf[1] = NULL;

$   PostQuitMessage (0);

//  Should terminate user process (main() etc.) even if they are not finished.
//  So, use exit(). Assume pressing [X] to be normal exit, so exit (0).

$   if (_txRunning) { _txExit = true; exit (EXIT_SUCCESS); }

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OnClose (HWND)
    {
$   assert (_txCanvas_OK());

$   char name[256] = __FILE__;
$   GetModuleFileName (NULL, name, sizeof (name) - 1) TX_NEEDED;

$   if (_txRunning &&
        MessageBox (txWindow(), "������� main() �� ���������. "
                    "��������� ��� ��� ��������. ��������?    ", name,
                     MB_OKCANCEL | MB_ICONSTOP) != IDOK) return false;
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OnPaint (HWND wnd)
    {
$   assert (wnd);
$   if (!_txCanvas_OK()) return false;

$   PAINTSTRUCT ps = {0};
$   HDC dc = BeginPaint (wnd, &ps);
$   if (!dc) return false;

$   if (!txLock (false))
      {
$     EndPaint (wnd, &ps) TX_NEEDED;
$     return false;
      }

$   RECT r = {0};
$   GetClientRect (wnd, &r) TX_NEEDED;
$   POINT size = { r.right - r.left, r.bottom - r.top };

$   if (!_txCanvas_RefreshLock)
      {
$     Win32::BitBlt (_txCanvas_BackBuf[1], 0, 0, size.x, size.y, txDC(), 0, 0, SRCCOPY);

$     if (_txConsole_OK())
          {
$         _txConsole_Draw (_txCanvas_BackBuf[1]);
          }
      }

$   Win32::BitBlt (dc, 0, 0, size.x, size.y, _txCanvas_BackBuf[1], 0, 0, SRCCOPY);

$   txUnlock();

$   EndPaint (wnd, &ps) TX_NEEDED;

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OnChar (HWND, WPARAM ch)
    {
$   if (!_txCanvas_OK()) return false;

$   INPUT_RECORD evt = {0};

$   evt.EventType                        = KEY_EVENT;
$   evt.Event.KeyEvent.bKeyDown          = true;
$   evt.Event.KeyEvent.wRepeatCount      = 1;
$   evt.Event.KeyEvent.wVirtualKeyCode   = 0;
$   evt.Event.KeyEvent.wVirtualScanCode  = 0;
$   evt.Event.KeyEvent.uChar.AsciiChar   = (unsigned char) ch;
$   evt.Event.KeyEvent.dwControlKeyState = 0;

$   DWORD written = 0;
$   WriteConsoleInput (GetStdHandle (STD_INPUT_HANDLE), &evt, 1, &written) TX_NEEDED;

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OnMouse (HWND, WPARAM buttons, LPARAM coords)
    {
$   if (!_txCanvas_OK()) return false;

$   _txMousePos.x   = LOWORD (coords);
$   _txMousePos.y   = HIWORD (coords);
$   _txMouseButtons = (int) buttons;

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OnTimer (HWND, WPARAM)
    {
$   if (!_txCanvas_OK()) return false;

$   InvalidateRect (_txCanvas_Wnd, NULL, false) TX_NEEDED;
$   UpdateWindow   (_txCanvas_Wnd)              TX_NEEDED;

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OnCmdConsole (HWND wnd, WPARAM cmd)
    {
$   assert (wnd); assert (_txCanvas_OK()); assert (_txConsole_OK());

$   bool visible = IsWindowVisible (_txConsole_Wnd) != 0;

$   ShowWindow (_txConsole_Wnd, visible? SW_HIDE : SW_SHOW);

$   visible = IsWindowVisible (_txConsole_Wnd) != 0;
$   CheckMenuItem (GetSystemMenu (wnd, false), (int)cmd, visible? MF_CHECKED : MF_UNCHECKED);

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txCanvas_OnCmdAbout (HWND, WPARAM)
    {
    //{ Overriding the missing names, if the set is uncomplete

    #if defined (__MODULE) || defined (__VERSION) || defined (__DESCRIPTION) || defined (__AUTHOR)

        #ifndef __MODULE
        #define __MODULE       "TXLib"                       " \t\t"  "#define __MODULE to set the name."
        #endif

        #ifndef __VERSION
        #define __VERSION      "(0.000000000)."              " \t\t" "#define __VERSION to set the string value."
        #endif

        #ifndef __DESCRIPTION
        #define __DESCRIPTION  "(��� ���� ������ ��������)." " \t\t" "#define __DESCRIPTION to override project role."
        #endif

        #ifndef __AUTHOR
        #define __AUTHOR       "(��������� ���)."            " \t\t" "#define __AUTHOR to override this name."
        #endif

    #endif
    //}

$   time_t timeT      = time (NULL) - clock()/CLOCKS_PER_SEC;
$   char   timeS[100] = "";

#ifdef  _TX_USE_SECURE_CRT
$   ctime_s  (timeS, sizeof (timeS), &timeT);
#else
$   strncpy (timeS, ctime (&timeT), sizeof (timeS) - 1);
#endif

$   char name[1024] = ""; GetModuleFileName (NULL, name, sizeof (name) - 1) TX_NEEDED;
$   char cwd [1024] = ""; _getcwd           (cwd,        sizeof (cwd)  - 1) TX_NEEDED;
$   char text[1024] = "";

    #define EOL_ "    \n"

$   _snprintf_s (text, sizeof (text) - 1,
                 #ifdef  _TX_USE_SECURE_CRT
                 _TRUNCATE,
                 #endif

                 "Application:" EOL_ "\n"

                 #if defined (__MODULE) || defined (__VERSION) || defined (__DESCRIPTION) || defined (__PROGRAMMER)
                     __MODULE " version " __VERSION EOL_
                     __DESCRIPTION EOL_
                     "Copyright (c) " __AUTHOR EOL_
                 #else
                     "����� ����� �� ���� ���� �������:)" EOL_
                     "#define __MODULE to \"your program name\" before including TXLib.h to use this billboard..." EOL_
                 #endif

                 "\n" "Developed with:" EOL_ "\n"
                 "The Dumb Artist Library (TX Library) - " _TX_VERSION EOL_
                 _TX_AUTHOR EOL_ "\n"

                 "TXLib file:" "\t" __FILE__ EOL_
                 "Compiled:"   "\t" __TX_COMPILER__ ", on: " __DATE__ ", " __TIME__ EOL_ "\n"

                 "Run file:"   "\t" "%s, started: %.6s %.4s %.8s" EOL_
                 "Run from:"   "\t" "%s" EOL_,

                 name,
                 timeS + 4, timeS + 20, timeS + 11,  // These offsets are standardized by ANSI
                 cwd);

    #undef EOL_

$   MessageBox (txWindow(), text, "About "
                                           #ifdef __MODULE
                                           __MODULE
                                           #else
                                           "TXLib"
                                           #endif
                                                   , MB_ICONINFORMATION);

//  And a bit of HTTP-code in C++ function:

    goto http;
    http://ded32.net.ru                    // See valuable refs here :)

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK _txCanvas_WndProc (HWND wnd, UINT msg, WPARAM wpar, LPARAM lpar)
    {
    #define IS_TXLIB_HOTKEY_()  ( msg  == WM_KEYDOWN       && \
                                  wpar == VK_F12           && \
                                  GetKeyState (VK_CONTROL) && \
                                  GetKeyState (VK_SHIFT)   && \
                                  GetKeyState (VK_MENU) )

    if (_txAltWndProc && !IS_TXLIB_HOTKEY_())
        {
$       LRESULT res = _txAltWndProc (wnd, msg, wpar, lpar);
$       if (res) return res;
        }

    switch (msg)
        {
        case WM_CREATE:       $ _txCanvas_OnCreate     (wnd);         break;

        case WM_CLOSE:        $ if (!_txCanvas_OnClose (wnd))         return 0;
        case WM_DESTROY:      $ _txCanvas_OnDestroy    (wnd);         break;

        case WM_PAINT:        $ _txCanvas_OnPaint      (wnd);         break;
        case WM_CHAR:         $ _txCanvas_OnChar       (wnd, wpar);   break;
        case WM_TIMER:        $ _txCanvas_OnTimer      (wnd, wpar);   break;

        case WM_LBUTTONUP:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MOUSEMOVE:    $ _txCanvas_OnMouse  (wnd, wpar, lpar); break;
        default:              $ break;
        }

    if (msg == WM_SYSCOMMAND) switch (wpar)
        {
        case _TX_IDM_ABOUT:   $ _txCanvas_OnCmdAbout   (wnd, wpar);   break;
        case _TX_IDM_CONSOLE: $ _txCanvas_OnCmdConsole (wnd, wpar);   break;
        default:              $ break;
        }

    if (IS_TXLIB_HOTKEY_())
        {
$       _txCanvas_OnCmdAbout (wnd, wpar);
        }

    return DefWindowProc (wnd, msg, wpar, lpar);

    #undef IS_TXLIB_HOTKEY_
    }

//}

//===============================================================================================================================
//{          [Internal] Console-support functions  (_txConsole...)
//! @name    ������� ����������� ����              (_txConsole...)
//===============================================================================================================================

bool _txConsole_Attach()
    {
#ifdef _TX_NO_HIDE_CONSOLE
$   if (!_txConsole_GetWindow())
#endif
        {
$       FreeConsole();
$       AllocConsole();

$       HANDLE con = GetStdHandle (STD_OUTPUT_HANDLE); con TX_NEEDED;
$       COORD size = { 80, 25 };
$       SetConsoleScreenBufferSize (con, size);
        }

$   _txConsole_Wnd = _txConsole_GetWindow();

$   _txConsole_InitSTDIO() TX_NEEDED;

$   return _txConsole_Wnd != NULL;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txConsole_InitSTDIO()
    {
$   int crtIn  = _open_osfhandle ((ptrdiff_t) GetStdHandle (STD_INPUT_HANDLE),  _O_TEXT);
$   int crtOut = _open_osfhandle ((ptrdiff_t) GetStdHandle (STD_OUTPUT_HANDLE), _O_TEXT);

$   *stdin  = * _fdopen (crtIn,  "r");
$   *stdout = * _fdopen (crtOut, "w");

$   setvbuf (stdin,  NULL, _IONBF, 0);
$   setvbuf (stdout, NULL, _IONBF, 0);

$   std::ios::sync_with_stdio();

$   SetConsoleCP       (1251);
$   SetConsoleOutputCP (1251);

$     setlocale (LC_CTYPE,  "Russian");
$   _wsetlocale (LC_CTYPE, L"Russian_Russia.ACP");

$   return !ferror (stdin)  &&
           !ferror (stdout) &&
           std::cin.good()  &&
           std::cout.good();
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txConsole_OK()
    {
$   return _txConsole_Wnd != NULL;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txConsole_Detach()
    {
$   FreeConsole();
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txConsole_Draw (HDC dc)
    {
$   assert (_txConsole_OK()); assert (_txCanvas_OK());

$   if (!txLock (false)) return false;

$   CONSOLE_SCREEN_BUFFER_INFO con = {{0}};
$   GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &con) TX_NEEDED;

$   TCHAR* buf = new TCHAR [con.dwSize.X * con.dwSize.Y + 1]; buf TX_NEEDED;

$   COORD zero = {0};
$   DWORD read = 0;
$   ReadConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE), buf,
                                con.dwSize.X * con.dwSize.Y * sizeof (TCHAR),
                                zero, &read) TX_NEEDED;
$   SIZE fontSz = {0};
$   Win32::GetTextExtentPoint32 (dc, "W", 1, &fontSz) TX_NEEDED;

$   int sizeX = con.srWindow.Right - con.srWindow.Left + 1;
$   for (int y = con.srWindow.Top; y <= con.srWindow.Bottom; y++)
        Win32::TextOut (dc, 0, y*fontSz.cy, buf + y*con.dwSize.X + con.srWindow.Left, sizeX) TX_NEEDED;

$   delete[] buf;

$   if (_txConsole_CursorMode &&
      GetTickCount() % _TX_CURSOR_BLINK_INTERVAL*2 > _TX_CURSOR_BLINK_INTERVAL &&
      In (con.dwCursorPosition, con.srWindow))
      {
$     Win32::TextOut (dc,
                     (con.dwCursorPosition.X - con.srWindow.Left)*fontSz.cx,
                     (con.dwCursorPosition.Y - con.srWindow.Top) *fontSz.cy + 1,
                      "_", 1);
      }

$   txUnlock();

$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

HWND _txConsole_GetWindow()
    {
$   static _TX_IMPORT_OPT ("Kernel32", HWND, GetConsoleWindow, ());
$   if (GetConsoleWindow) return GetConsoleWindow();

$   SetLastError (0);

$   char title[1024] = "";
$   GetConsoleTitle (title, sizeof (title) - 1);

$   char unique [128] = "";
$   LARGE_INTEGER time = {{0}};
$   QueryPerformanceCounter (&time) TX_NEEDED;

$   _snprintf_s (unique, sizeof (unique) - 1, __FILE__ "(%d)\\Temp Title %08lx%08lx", __LINE__, time.HighPart, time.LowPart);

$   SetConsoleTitle (unique) TX_NEEDED;

$   HWND con = NULL;
$   _txWaitFor (con = FindWindow (NULL, unique));

$   SetConsoleTitle (title) TX_NEEDED;

$   con || TX_THROW ("Cannot find console window");

$   SetLastError (0);
$   return con;
    }

//}

//===============================================================================================================================
//{          [Internal] Memory DC functions        (_txBuffer...)
//! @name    ������� "������������ ������" (������������ ������, _txBuffer...)
//===============================================================================================================================

HDC _txBuffer_Create (HWND wnd, const POINT* size, HBITMAP bitmap)
    {
$   txLock();

$   HDC wndDC = GetDC (wnd); wndDC TX_NEEDED;
$   (Win32::GetDeviceCaps (wndDC, RASTERCAPS) & RC_BITBLT) || TX_THROW ("GetDeviceCaps(): RASTERCAPS: RC_BITBLT not supported");

$   RECT r = {0};
$   GetClientRect (wnd, &r) TX_NEEDED;
$   POINT sz = { r.right - r.left, r.bottom - r.top };
$   if (!size) size = &sz;

$   HDC dc = Win32::CreateCompatibleDC (wndDC);
$   dc || TX_THROW ("Cannot create buffer: CreateCompatibleDC() failed");

$   HBITMAP bmap = bitmap? bitmap : Win32::CreateCompatibleBitmap (wndDC, size->x, size->y);
$   bmap || TX_THROW ("Cannot create buffer: CreateCompatibleBitmap() failed");

$   Win32::SelectObject (dc, bmap) TX_NEEDED;

$   if (!bitmap) Win32::PatBlt (dc, 0, 0, size->x, size->y, BLACKNESS) TX_NEEDED;

$   ReleaseDC (wnd, wndDC) TX_NEEDED;

$   txUnlock();
$   return dc;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txBuffer_Delete (HDC dc)
    {
$   if (!dc) return false;

$   txLock ();

$   _txBuffer_Select (Win32::GetStockObject (NULL_PEN),    dc) TX_NEEDED;
$   _txBuffer_Select (Win32::GetStockObject (NULL_BRUSH),  dc) TX_NEEDED;
$   _txBuffer_Select (Win32::GetStockObject (SYSTEM_FONT), dc) TX_NEEDED;

$   Win32::DeleteObject (Win32::GetCurrentObject (dc, OBJ_BITMAP));
$   Win32::DeleteObject (Win32::GetCurrentObject (dc, OBJ_REGION));

$   Win32::DeleteDC (dc) TX_NEEDED;

$   txUnlock();
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool _txBuffer_Select (HGDIOBJ obj, HDC dc /*= txDC()*/)
    {
$   assert (obj); assert (dc);

$   txLock ();

$   obj = Win32::SelectObject (dc, obj);
$   if (obj) Win32::DeleteObject (obj);

$   txUnlock();

$   return obj != NULL;
    }

//}

//===============================================================================================================================
//{          TXLib API implementation
//! @name    ���������� TXLib API
//===============================================================================================================================

inline
const char* txVersion()
    {
$   return _TX_VERSION;
    }

//-------------------------------------------------------------------------------------------------------------------------------

POINT txGetExtent()
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   RECT r = {0};
$   GetClientRect (txWindow(), &r);
$   POINT size = { r.right - r.left, r.bottom - r.top };
$   return size;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
int txGetExtentX()
    {
$   return txGetExtent().x;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
int txGetExtentY()
    {
$   return txGetExtent().y;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
HDC txDC()
    {
$   return _txCanvas_BackBuf[0];
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
HWND txWindow()
    {
$   return _txCanvas_Wnd;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txSetColor (COLORREF color, double thickness /*= 1*/)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   return _txBuffer_Select (Win32::CreatePen ((color == TX_TRANSPARENT? PS_NULL : PS_SOLID), (int)thickness, color)) &&
            txGDI   ((Win32::SetTextColor (txDC(), color) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txColor (double red, double green, double blue)
    {
$   if (red   > 1) red   = 1; if (red   < 0) red   = 0;
$   if (green > 1) green = 1; if (green < 0) green = 0;
$   if (blue  > 1) blue  = 1; if (blue  < 0) blue  = 0;

$   return txSetColor (RGB (red * 255, green * 255, blue * 255));
    }

//-------------------------------------------------------------------------------------------------------------------------------

COLORREF txGetColor()
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   HGDIOBJ obj = txGDI ((Win32::GetCurrentObject (txDC(), OBJ_PEN))); obj TX_NEEDED;

$   char buf [MAX (sizeof (LOGPEN), sizeof (EXTLOGPEN))] = {0};

$   int size = GetObject (obj, 0, NULL);
$   GetObject (obj, sizeof (buf), buf) TX_NEEDED;

$   return (size == sizeof (LOGPEN))? ((LOGPEN*)buf)->lopnColor : ((EXTLOGPEN*)buf)->elpColor;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txSetFillColor (COLORREF color)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   return _txBuffer_Select ((color == TX_TRANSPARENT)? Win32::GetStockObject   (HOLLOW_BRUSH) :
                                                 Win32::CreateSolidBrush (color));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txFillColor (double red, double green, double blue)
    {
$   if (red   > 1) red   = 1; if (red   < 0) red   = 0;
$   if (green > 1) green = 1; if (green < 0) green = 0;
$   if (blue  > 1) blue  = 1; if (blue  < 0) blue  = 0;

$   return txSetFillColor (RGB (red * 255, green * 255, blue * 255));
    }

//-------------------------------------------------------------------------------------------------------------------------------

COLORREF txGetFillColor()
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   HGDIOBJ obj = txGDI ((Win32::GetCurrentObject (txDC(), OBJ_BRUSH))); obj TX_NEEDED;

$   LOGBRUSH buf = {0};
$   txGDI ((Win32::GetObject (obj, sizeof (buf), &buf))) TX_NEEDED;

$   return buf.lbColor;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txSetROP2 (int mode)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   return txGDI ((Win32::SetROP2 (txDC(), mode) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txClear()
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());
$   POINT size = txGetExtent();

$   return txGDI ((Win32::PatBlt (txDC(), 0, 0, size.x, size.y, PATCOPY) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txSetPixel (double x, double y, COLORREF color)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   txGDI ((Win32::SetPixel (txDC(), (int)x, (int)y, color)));

$   RECT r = { (int)x, (int)y, (int)x, (int)y };
$   InvalidateRect (txWindow(), &r, false) TX_NEEDED;
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txPixel (double x, double y, double red, double green, double blue)
    {
$   if (red   > 1) red   = 1; if (red   < 0) red   = 0;
$   if (green > 1) green = 1; if (green < 0) green = 0;
$   if (blue  > 1) blue  = 1; if (blue  < 0) blue  = 0;

$   return txSetPixel (x, y, RGB (red * 255, green * 255, blue * 255));
    }

//-------------------------------------------------------------------------------------------------------------------------------

COLORREF txGetPixel (double x, double y)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   return txGDI ((Win32::GetPixel (txDC(), (int)x, (int)y)));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txLine (double x0, double y0, double x1, double y1)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   txGDI ((Win32::MoveToEx (txDC(), (int)x0, (int)y0, NULL))) TX_NEEDED;
$   txGDI ((Win32::LineTo   (txDC(), (int)x1, (int)y1)))       TX_NEEDED;

$   RECT r = { (int)x0, (int)y0, (int)x1, (int)y1 };
$   InvalidateRect (txWindow(), &r, false) TX_NEEDED;
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txRectangle (double x0, double y0, double x1, double y1)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   txGDI ((Win32::Rectangle (txDC(), (int)x0, (int)y0, (int)x1, (int)y1))) TX_NEEDED;

$   RECT r = { (int)x0, (int)y0, (int)x1, (int)y1 };
$   InvalidateRect (txWindow(), &r, false) TX_NEEDED;
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txPolygon (const POINT points[], int numPoints)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   return txGDI ((Win32::Polygon (txDC(), points, numPoints) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txEllipse (double x0, double y0, double x1, double y1)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   txGDI ((Win32::Ellipse (txDC(), (int)x0, (int)y0, (int)x1, (int)y1))) TX_NEEDED;

$   RECT r = { (int)x0, (int)y0, (int)x1, (int)y1 };
$   InvalidateRect (txWindow(), &r, false) TX_NEEDED;
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txCircle (double x, double y, double r)
    {
$   return txEllipse (x-r, y-r, x+r, y+r);
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txArc (double x0, double y0, double x1, double y1, double startAngle, double totalAngle)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   double start = startAngle * txPI / 180, end = (startAngle + totalAngle) * txPI / 180;
$   POINT center = { (int)((x0+x1)/2), (int)((y0+y1)/2) };

$   return txGDI ((Win32::Arc (txDC(), (int)x0, (int)y0, (int)x1, (int)y1,
                                        center.x + (int)(100*cos (start)), center.y - (int)(100*sin (start)),
                                        center.x + (int)(100*cos (end)),   center.y - (int)(100*sin (end))) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txPie (double x0, double y0, double x1, double y1, double startAngle, double totalAngle)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   double start = startAngle * txPI / 180, end = (startAngle + totalAngle) * txPI / 180;
$   POINT center = { (int)((x0+x1)/2), (int)((y0+y1)/2) };

$   return txGDI ((Win32::Pie (txDC(), (int)x0, (int)y0, (int)x1, (int)y1,
                                        center.x + (int)(100*cos (start)), center.y - (int)(100*sin (start)),
                                        center.x + (int)(100*cos (end)),   center.y - (int)(100*sin (end))) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txChord (double x0, double y0, double x1, double y1, double startAngle, double totalAngle)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   double start = startAngle * txPI / 180, end = (startAngle + totalAngle) * txPI / 180;
$   POINT center = { (int)((x0+x1)/2), (int)((y0+y1)/2) };

$   return txGDI ((Win32::Chord (txDC(), (int)x0, (int)y0, (int)x1, (int)y1,
                                          center.x + (int)(100*cos (start)), center.y - (int)(100*sin (start)),
                                          center.x + (int)(100*cos (end)),   center.y - (int)(100*sin (end))) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txFloodFill (double x, double y,
                  COLORREF color /*= TX_TRANSPARENT*/, DWORD mode /*= FLOODFILLSURFACE*/)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());
$   if (color == TX_TRANSPARENT) color = txGetPixel (x, y);

$   return txGDI ((Win32::ExtFloodFill (txDC(), (int)x, (int)y, color, mode) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txTextOut (double x, double y, const char text[])
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   int len = (int) strlen (text);
$   txGDI ((Win32::TextOut (txDC(), (int)x, (int)y, text, len))) TX_NEEDED;

$   SIZE size = {0};
$   txGDI ((Win32::GetTextExtentPoint32 (txDC(), text, len, &size))) TX_NEEDED;

$   RECT r = { (int)x, (int)y, (int)x + size.cx, (int)y + size.cy };
$   InvalidateRect (txWindow(), &r, false) TX_NEEDED;
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txSelectFont (const char name[], double sizeY,
                   double sizeX   /*= 0*/,
                   int  bold      /*= FW_DONTCARE*/,
                   bool italic    /*= false*/,
                   bool underline /*= false*/,
                   bool strikeout /*= false*/)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   _txBuffer_Select (txFontExist (name)? CreateFont ((int)sizeY, (int) ((int)sizeX? sizeX : sizeY/3), 0, 0,
                                               bold, italic, underline, strikeout,
                                               DEFAULT_CHARSET,
                                               OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                               DEFAULT_QUALITY, FIXED_PITCH, name)
                                   :
                                   GetStockObject (SYSTEM_FIXED_FONT));
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

SIZE txGetTextExtent (const char text[])
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   SIZE size = {0};
$   txGDI ((Win32::GetTextExtentPoint32 (txDC(), text, (int) strlen (text), &size))) TX_NEEDED;

$   return size;
    }

//-------------------------------------------------------------------------------------------------------------------------------

int txGetTextExtentX (const char text[])
    {
$   return txGetTextExtent (text) .cx;
    }

//-------------------------------------------------------------------------------------------------------------------------------

int txGetTextExtentY (const char text[])
    {
$   return txGetTextExtent (text) .cy;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txSetTextAlign (unsigned align /*= TA_CENTER | TA_BASELINE*/)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   txGDI ((Win32::SetTextAlign (txDC(), align)));
$   return true;
    }

//-------------------------------------------------------------------------------------------------------------------------------

LOGFONT* txFontExist (const char name[])
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   static LOGFONT font = {0};
$   font.lfCharSet = DEFAULT_CHARSET;
$   strncpy_s (font.lfFaceName, name, sizeof (font.lfFaceName) - 1);

    struct enumFonts
        {
        static int CALLBACK Proc (const LOGFONT* fnt, const TEXTMETRIC*, DWORD, LPARAM data)
            {
$           assert (fnt); assert (data);
#ifndef __STRICT_ANSI__
$           return _strnicmp (fnt->lfFaceName, ((LOGFONT*)data)->lfFaceName, LF_FACESIZE) != 0;
#else
$           return  strncmp  (fnt->lfFaceName, ((LOGFONT*)data)->lfFaceName, LF_FACESIZE) != 0;
#endif
            }
        };

$   return txGDI ((Win32::EnumFontFamiliesEx (txDC(), &font, enumFonts::Proc, (LPARAM)&font, 0) == 0? &font : NULL));
    }

//-------------------------------------------------------------------------------------------------------------------------------

HRGN txSelectRegion (double x0, double y0, double x1, double y1)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   HRGN rgn = Win32::CreateRectRgn ((int)x0, (int)y0, (int)x1, (int)y1);

$   txSelectObject (rgn) TX_NEEDED;

$   return rgn;
    }
//-------------------------------------------------------------------------------------------------------------------------------

bool txSelectObject (HGDIOBJ obj)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   return _txBuffer_Select (obj);
    }

//-------------------------------------------------------------------------------------------------------------------------------

HDC txCreateCompatibleDC (double sizeX, double sizeY, HBITMAP bitmap /*= NULL*/)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   POINT size = { (int)sizeX, (int)sizeY };
$   HDC dc = _txBuffer_Create (txWindow(), &size, bitmap); dc TX_NEEDED;
$   return dc;
    }

//-------------------------------------------------------------------------------------------------------------------------------

HDC txLoadImage (const char filename[])
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   HBITMAP image = (HBITMAP) LoadImage (NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
$   if (!image) return NULL;

$   HDC dc = txCreateCompatibleDC (0, 0, image);

$   return dc;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txDeleteDC (HDC dc)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   return _txBuffer_Delete (dc);
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txBitBlt (HDC dest, double xDest, double yDest, double width, double height,
               HDC src,  double xSrc,  double ySrc,  DWORD rOp /*= SRCCOPY*/)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   return txGDI ((Win32::BitBlt (dest, (int)xDest, (int)yDest, (int)width, (int)height,
                                  src,  (int)xSrc,  (int)ySrc, rOp) != 0));
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txTransparentBlt (HDC dest, double xDest, double yDest, double width, double height,
                       HDC src,  double xSrc,  double ySrc,  COLORREF transColor /*= TX_BLACK*/)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   if (!TransparentBlt) return false;

$   return Win32::TransparentBlt (dest, (int)xDest, (int)yDest, (int)width, (int)height,
                                  src,  (int)xSrc,  (int)ySrc,  (int)width, (int)height, transColor) != 0;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txAlphaBlend (HDC dest, double xDest, double yDest, double width, double height,
                   HDC src,  double xSrc,  double ySrc,  double alpha /*= 1.0*/)
    {
$   _txCheck (__TX_FUNCTION__); assert (txOK());

$   if (!AlphaBlend) return false;

$   if (alpha < 0) alpha = 0;
$   if (alpha > 1) alpha = 1;

#ifndef AC_SRC_ALPHA
#define AC_SRC_ALPHA 0x01   // On some old MinGW versions, or MSVC6, this is not defined.
#endif

$   BLENDFUNCTION blend = {AC_SRC_OVER, 0, (BYTE) (alpha * 255), AC_SRC_ALPHA};

$   return Win32::AlphaBlend (dest, (int)xDest, (int)yDest, (int)width, (int)height,
                              src,  (int)xSrc,  (int)ySrc,  (int)width, (int)height, blend) != 0;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
int txBegin()
    {
$   _txCanvas_SetRefreshLock (_txCanvas_RefreshLock + 1);

$   return _txCanvas_RefreshLock;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
int txEnd()
    {
$   _txCanvas_SetRefreshLock (_txCanvas_RefreshLock - 1);

$   return _txCanvas_RefreshLock;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
bool txUpdateWindow (bool update /*= true*/)
    {
$   return _txCanvas_SetRefreshLock (update? 0 : 1) != 0;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
bool txSleep (int time)
    {
    _txCheck (__TX_FUNCTION__); assert (txOK());

$   int old = _txCanvas_SetRefreshLock (0);

$   Sleep (time);

$   _txCanvas_SetRefreshLock (old);
$   return old != 0;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
bool txLock (bool wait /*= true*/)
    {
$   if (wait) { return    EnterCriticalSection (&_txCanvas_LockBackBuf), true; }
    else      { return TryEnterCriticalSection (&_txCanvas_LockBackBuf) != 0;  }
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
bool txUnlock()
    {
$   LeaveCriticalSection (&_txCanvas_LockBackBuf);
$   return false;
    }

//-------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline
T txUnlock (T value)
    {
$   txUnlock();
$   return value;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
POINT txMousePos()
    {
$   return _txMousePos;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
int txMouseX()
    {
$   return _txMousePos.x;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
int txMouseY()
    {
$   return _txMousePos.y;
    }

//-------------------------------------------------------------------------------------------------------------------------------

inline
int txMouseButtons()
    {
$   return _txMouseButtons;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txPlaySound (const char filename[] /*= NULL*/, DWORD mode /*= SND_ASYNC*/)
    {
$   mode |= SND_FILENAME | SND_NODEFAULT | SND_NOWAIT;
$   if (mode & SND_LOOP) mode = (mode & ~SND_SYNC) | SND_ASYNC;

$   if (!filename) mode = SND_PURGE;

$   return PlaySound (filename, NULL, mode) != 0;
    }

//-------------------------------------------------------------------------------------------------------------------------------

WNDPROC txSetWindowHandler (WNDPROC handler)
    {
$   WNDPROC old = _txAltWndProc; _txAltWndProc = handler;
$   return  old;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txTextCursor (bool blink /*= true*/)
    {
$   bool old = _txConsole_CursorMode;

$   _txConsole_CursorMode = blink;

$   return old;
    }

//-------------------------------------------------------------------------------------------------------------------------------

bool txIDontWantToHaveAPauseAfterMyProgramBeforeTheWindowWillCloseAndIWillNotBeAskingWhereIsMyPicture()
    {
$   MessageBox (txWindow(),
                "��� ��������������� ������. ����� ������. �� ������ �������:" "\n\n"
                "txIDontWantToHaveAPauseAfterMyProgramBeforeTheWindowWillCloseAndIWillNotBeAskingWhereIsMyPicture(),"
                "\n\n" "���� �� ����� [����������]�������� ��� ���, �� ����� ���� ��� ������� �� ��������." "\n"
                "�� ��� ��� ���� ���������� �������. ��. ����������� ���� ������� � �������� ������� ����������." "\n\n",
                "�� ����������", MB_ICONSTOP);

    // The truth is out there...

$   return false;
    }

//-------------------------------------------------------------------------------------------------------------------------------
//! @cond INTERNAL

inline
bool txDisableAutoPause()  // Bingo! Now you are learned to use the [force]sources.
    {
$   _txExit = true;
$   return true;
    }

//! @endcond
//-------------------------------------------------------------------------------------------------------------------------------

int txExtractColor (COLORREF color, COLORREF component)
    {
$   switch (component)
        {
        case TX_RED:
        case TX_HUE:        $ return (color >>  0) & 0xFF;

        case TX_GREEN:
        case TX_SATURATION: $ return (color >>  8) & 0xFF;

        case TX_BLUE:
        case TX_LIGHTNESS:  $ return (color >> 16) & 0xFF;

        default:            $ return -1;
        }
    }

//-------------------------------------------------------------------------------------------------------------------------------

COLORREF txRGB2HSL (COLORREF rgbColor)
    {
$   int r = txExtractColor (rgbColor, TX_RED),
        g = txExtractColor (rgbColor, TX_GREEN),
        b = txExtractColor (rgbColor, TX_BLUE);

$   double m1 = MAX (MAX (r, g), b) / 255.0,
           m2 = MIN (MIN (r, g), b) / 255.0,
           dm = m1 - m2,
           sm = m1 + m2,

           ir = r / 255.0,
           ig = g / 255.0,
           ib = b / 255.0,

           ih = 0,
           is = 0,
           il = sm / 2;

$   const double prec = 0.001;

$   if (fabs (dm) < prec)
        {
$       is = dm / ((sm <= 1)? sm : (2-sm));

$       double cr = (m1 - ir) / dm,
               cg = (m1 - ig) / dm,
               cb = (m1 - ib) / dm;

$       if (fabs (ir - m1) < prec) ih =     cb - cg;
$       if (fabs (ig - m1) < prec) ih = 2 + cr - cb;
$       if (fabs (ib - m1) < prec) ih = 4 + cg - cr;
        }

$   return RGB ((int)(ih >= 0? ih*60 : ih*60 + 360), (int)(is*255), (int)(il*255));
    }

//-------------------------------------------------------------------------------------------------------------------------------

COLORREF txHSL2RGB (COLORREF hslColor)
    {
    struct xRGB
        {
        static double calc (double h, double m1, double m2)
            {
$           if (h < 0)   h += 360;
$           if (h > 360) h -= 360;

$           return (h <  60)? m1 + (m2-m1) *      h  / 60 :
                   (h < 180)? m2 :
                   (h < 240)? m1 + (m2-m1) * (240-h) / 60 :
                              m1;
            }
        };

$   int h = txExtractColor (hslColor, TX_HUE),
        s = txExtractColor (hslColor, TX_SATURATION),
        l = txExtractColor (hslColor, TX_LIGHTNESS);

$   double ih = h,
           il = l / 100.0,
           is = s / 100.0,

           m2 = (il <= 0.5)? il * (1 + is) : il + is - il * is,
           m1 = 2 * il - m2,

           ir = s? xRGB::calc (ih + 120, m1, m2) : il,
           ig = s? xRGB::calc (ih,       m1, m2) : il,
           ib = s? xRGB::calc (ih - 120, m1, m2) : il;

$   return RGB (ir * 255, ig * 255, ib * 255);
    }

//}

//===============================================================================================================================
//{          txDialog methods implementation
//! @name    ���������� ������� ������ txDialog
//===============================================================================================================================

txDialog::txDialog () :
    layout_ (NULL)
    {$}

//-------------------------------------------------------------------------------------------------------------------------------

txDialog::txDialog (const Layout* layout) :
    layout_ (layout)
    {$}

//-------------------------------------------------------------------------------------------------------------------------------

const txDialog::Layout* txDialog::setLayout (const Layout* layout)
    {
$   return std::swap (layout_, layout), layout;
    }

//-------------------------------------------------------------------------------------------------------------------------------

INT_PTR txDialog::dialogBox (const txDialog::Layout* layout /*= NULL*/, size_t bufsize /*= 0*/)
    {
$   if (!layout)  layout = layout_;
$   if (!layout)  return TX_THROW ("�� ���������� ������������ ������ �������    ");

$   if (!bufsize) bufsize = 1024;

$   DLGTEMPLATE* tmpl = (DLGTEMPLATE*) GlobalAlloc (GPTR, bufsize);
$   if (!tmpl) return TX_THROW ("GlobalAlloc(): ��� ������ ��� ������� �������    ");

$   const Layout* dlg = &layout[0];

$   const Layout  def = { DIALOG, NULL, 0,    0, 0, 0, 0,
                                  WS_CAPTION | WS_SYSMENU | DS_MODALFRAME | DS_CENTER,
                                  "MS Shell Dlg", 8 };

$   void* ptr = _tx_DLGTEMPLATE_Create (tmpl, bufsize,
                                       (dlg->style? dlg->style : def.style) | DS_SETFONT, 0, 0,
                                        dlg->x, dlg->y, dlg->sx, dlg->sy,
                                        dlg->caption?  dlg->caption  : def.caption,
                                        dlg->font?     dlg->font     : def.font,
                                        dlg->fontsize? dlg->fontsize : def.fontsize);
$   WORD i = 0;
$   for (i = 1; layout[i].wndclass != END; ++i)
        {
$       const Layout* item = &layout[i];

$       ptr = _tx_DLGTEMPLATE_Add (ptr, bufsize - ((char*)ptr - (char*)tmpl),
                                   item->style | WS_VISIBLE, 0,
                                   item->x, item->y, item->sx, item->sy,
                                   item->id, (const char*)item->wndclass,
                                   item->caption);
        }

$   tmpl->cdit = (unsigned short) (i-1);
$   INT_PTR res = DialogBoxIndirectParam (NULL, tmpl, NULL, dialogProc__, (LPARAM) this);

$   GlobalFree (tmpl);
$   return res;
    }

//-------------------------------------------------------------------------------------------------------------------------------

INT_PTR txDialog::dialogBox (WORD resourceID)
    {
$   const char* resName = (char*)(ptrdiff_t)resourceID;

$   if (!FindResource (NULL, resName, RT_DIALOG)) return TX_THROW ("�� ������ ������ ������� %d   " _ resourceID);

$   return DialogBoxParam (NULL, resName, NULL, dialogProc__, (LPARAM) this);
    }

//-------------------------------------------------------------------------------------------------------------------------------

int txDialog::dialogProc (HWND, UINT, WPARAM, LPARAM)
    {
$   return FALSE;
    }

//-------------------------------------------------------------------------------------------------------------------------------

int CALLBACK txDialog::dialogProc__ (HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
$   static txDialog* this__ = NULL;

$   if (msg == WM_INITDIALOG) this__ = (txDialog*) lParam;
$   if (!this__) return FALSE;

$   switch (msg)
        {
        case WM_INITDIALOG: $ SetForegroundWindow (wnd);         break;

        case WM_COMMAND:    $ switch (LOWORD (wParam))
            {
            case IDOK:
            case IDCANCEL:  $ SetForegroundWindow (txWindow());
                            $ EndDialog (wnd, (INT_PTR) this__); break;
            default:        $ break;
            }

        default:            $ break;
        }

$   return this__-> dialogProc (wnd, msg, wParam, lParam);
    }

//}

//===============================================================================================================================
//{          Low-level txDialog functions
//! @name    ������� �������������� ������ � ����������� ������
//===============================================================================================================================

void* _tx_DLGTEMPLATE_Create (void* globalMem, size_t bufsize, DWORD style, DWORD exStyle,
                              WORD controls, short x, short y, short cx, short cy,
                              const char caption[], const char font[], WORD fontsize,
                              HANDLE menu /*= NULL*/)
    {
$   if (!globalMem) return NULL;

$   WORD* pw = (WORD*) globalMem;

$   DLGTEMPLATE* tmpl = ((DLGTEMPLATE*&) pw)++;

$   tmpl->style = style;
$   tmpl->dwExtendedStyle = exStyle;
$   tmpl->cdit  = controls;
$   tmpl->x     = x;
$   tmpl->y     = y;
$   tmpl->cx    = cx;
$   tmpl->cy    = cy;

$   *pw++ = (WORD)(ptrdiff_t) NULL;
$   *pw++ = (WORD)(ptrdiff_t) menu;

$   if (caption)
        {
$       pw  += MultiByteToWideChar (CP_ACP, 0, caption? caption : "", -1, (wchar_t*) pw,
                                   (int) (bufsize? bufsize - ((char*)pw - (char*)globalMem) : 0xFFFF));
        }

$   if (style & DS_SETFONT)
         {
$        *pw++ = fontsize;
$         pw  += MultiByteToWideChar (CP_ACP, 0, font?    font    : "", -1, (wchar_t*) pw,
                                     (int) (bufsize? bufsize - ((char*)pw - (char*)globalMem) : 0xFFFF));
         }

$   return pw;
    }

//-------------------------------------------------------------------------------------------------------------------------------

void* _tx_DLGTEMPLATE_Add (void* dlgTemplatePtr, size_t bufsize, DWORD style, DWORD exStyle,
                           short x, short y, short cx, short cy,
                           WORD id, const char wclass[], const char caption[])
    {
$   if (!dlgTemplatePtr) return NULL;

$   WORD* pw = (LPWORD) dlgTemplatePtr;  // Force align at word boundary
$   (ULONG&) pw  += 3;
$   (ULONG&) pw >>= 2;
$   (ULONG&) pw <<= 2;

$   DLGITEMTEMPLATE* tmpl = ((DLGITEMTEMPLATE*&) pw)++;

$   tmpl->style = style;
$   tmpl->dwExtendedStyle = exStyle;
$   tmpl->x     = x;
$   tmpl->y     = y;
$   tmpl->cx    = cx;
$   tmpl->cy    = cy;
$   tmpl->id    = id;

$   if (HIWORD (wclass) == 0xFFFF)
        {
$       *pw++ = (WORD) (HIWORD (wclass));
$       *pw++ = (WORD) (LOWORD (wclass));
        }
    else if (wclass)
        {
$       pw  += MultiByteToWideChar (CP_ACP, 0, (char*) wclass, -1, (wchar_t*) pw,
                                   (int) (bufsize? bufsize - ((char*)pw - (char*)dlgTemplatePtr) : 0xFFFF));
        }
    else
        {
$       *pw++ = 0;
        }

$   if (caption)
         {
$        pw  += MultiByteToWideChar (CP_ACP, 0, caption, -1, (wchar_t*) pw,
                                    (int) (bufsize? bufsize - ((char*)pw - (char*)dlgTemplatePtr) : 0xFFFF));
         }
    else
        {
$       *pw++ = 0;
        }

$   *pw++ = 0;

$   return pw;
    }

//}

//===============================================================================================================================
//{          Diagnostics
//! @name    �����������
//===============================================================================================================================

bool _txThrow (const char file[], int line, const char func[], DWORD error,
               const char msg[], ...)
    {
    const size_t MAXSTR = 1024;

    bool fatal = (msg && *msg == '\a')? (msg++, true) : false;

    va_list arg; va_start (arg, msg);

    #ifdef  _TX_USE_SECURE_CRT
        #define TR_ ,_TRUNCATE

    #else
        #define TR_

    #endif

    char str[MAXSTR] = "", *s = str;

    if (file)
        s += _snprintf_s (s, sizeof (str) - 1 - (s-str) TR_, "TX_THROW(): %s", file);

    if (line)
        s += _snprintf_s (s, sizeof (str) - 1 - (s-str) TR_, " (%d)", line);

    if (func)
        s += _snprintf_s (s, sizeof (str) - 1 - (s-str) TR_, " %s",   func);

    if (msg && *msg)
        s +=  _snprintf_s (s, sizeof (str) - 1 - (s-str) TR_, ": "),
        s += _vsnprintf_s (s, sizeof (str) - 1 - (s-str) TR_, msg, arg);

    if (error == (DWORD)(-1))
        error = GetLastError();

    if (error)
        s += _snprintf_s (s, sizeof (str) - (s-str) TR_, ": Error %lu: ", error),
        s += FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            NULL, error, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
                            s, (DWORD) (sizeof (str) - (s-str)), NULL) - 3;

        s += _snprintf_s  (s, sizeof (str) - 1 - (s-str) TR_, "    \n");

    #undef TR_

    printf (str);

    OutputDebugString (str);
    MessageBox (NULL, str, fatal? "��������� ������" : "������ � ���������",
                MB_ICONSTOP | MB_TOPMOST | MB_SYSTEMMODAL);

    va_end (arg);

    if (fatal)
        {
        if (!IsDebuggerPresent()) { _txExit = true; exit (EXIT_FAILURE); }

/* --> */   DebugBreak();  // --> �� � ���������, ���� ���� ���������� ��������� � �����������.
            }              //     �������� �� ������� ��������� ��������. �������� �� ���� �������.

    return false;
    }

//}

//! @endcond
//}

//===============================================================================================================================
//! @cond INTERNAL

/*! @cond OFF */ } /*! @endcond */ } // namespace TX, anonymous namespace

//-------------------------------------------------------------------------------------------------------------------------------
//{          Easy using of TX:: and some of std::
//-------------------------------------------------------------------------------------------------------------------------------

using namespace TX;                  // Allow easy usage of TXLib functions
using namespace TX::Win32;           // Simulate linkage with Win32 libs

using std::cin;                      // Predefined usings to avoid "using namespace std"
using std::cout;

//}
//! @endcond
//===============================================================================================================================

//-------------------------------------------------------------------------------------------------------------------------------
//{          Compiler- and platform-specific
//! @name    ��������� � ������������ � ����������
//-------------------------------------------------------------------------------------------------------------------------------
//! @cond    INTERNAL

#if defined (__GNUC__) && (__GNUC__ >= 4)

    #pragma GCC diagnostic warning "-Wstrict-aliasing"

    // Still block this warning to avoid reporting about "= {}" initialization.

    #if 0
    #pragma GCC diagnostic warning "-Wmissing-field-initializers"
    #endif

    // These warnings really occur at end of compilation, so do not restore them.

    #if 0
    #pragma GCC diagnostic warning "-Wunreachable-code"
    #pragma GCC diagnostic warning "-Wunused-value"
    #pragma GCC diagnostic warning "-Wunused-function"
    #pragma GCC diagnostic warning "-Wunused-label"
    #endif

#endif

#if defined (_MSC_VER)

    #pragma warning (default: 4127)          // conditional expression is constant
    #pragma warning (default: 4245)          // conversion from... to..., signed/unsigned mismatch
    #pragma warning (default: 4351)          // new behavior: elements of array ... will be default initialized

    #pragma warning (default: 4018)          // '<': signed/unsigned mismatch
    #pragma warning (default: 4100)          // unreferenced formal parameter
    #pragma warning (default: 4511)          // copy constructor could not be generated
    #pragma warning (default: 4512)          // assignment operator could not be generated
    #pragma warning (default: 4663)          // C++ language change: to explicitly specialize class template '...'

    // This warning really occur at end of compilation, so do not restore it.

    #if 0
    #pragma warning (default: 4710)          // function '...' not inlined
    #endif

#endif

//-------------------------------------------------------------------------------------------------------------------------------

#undef $

//! @endcond
//}

//===============================================================================================================================

//}

#endif // __TXLIB_H

//===============================================================================================================================
// EOF
//===============================================================================================================================

