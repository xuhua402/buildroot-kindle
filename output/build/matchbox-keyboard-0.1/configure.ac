AC_PREREQ(2.53)
AC_INIT([matchbox-keyboard], 0.1, [mallum@handhelds.org])
AC_CONFIG_SRCDIR([src/matchbox-keyboard.c])

AM_INIT_AUTOMAKE()
AM_MAINTAINER_MODE
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_GNU_SOURCE
AC_PROG_CC
AC_HEADER_DIRENT
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_PID_T
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_FORK
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT

AC_ARG_ENABLE(cairo,
  [  --enable-cairo    enable experimental Cairo support [default=no]],
   		enable_cairo=$enableval, 
		enable_cairo=no)	    

AC_ARG_ENABLE(examples,
  [  --enable-examples  Build embedding examples ( requires GTK ) [default=no]],
   		enable_examples=$enableval, 
		enable_examples=no)
 
AC_ARG_ENABLE(debug,
  [  --enable-debug    enable debug ( verbose ) build],
     enable_debug=$enableval, enable_debug=no )

AC_ARG_WITH(expat-includes,    
  [  --with-expat-includes=DIR     Use Expat includes in DIR], 
	   expat_includes=$withval, expat_includes=yes)

AC_ARG_WITH(expat-lib,         
  [  --with-expat-lib=DIR          Use Expat library in DIR], 
	   expat_lib=$withval, expat_lib=yes)

PKG_CHECK_MODULES(FAKEKEY, libfakekey,,
	         AC_MSG_ERROR([*** You need to install libfakekey from MB SVN  ***]))

if test x$enable_cairo = xyes; then
   PKG_CHECK_MODULES(CAIRO, cairo,, [enable_cairo="no"])
fi

if test x$enable_cairo = xno; then
PKG_CHECK_MODULES(XFT, xft,,
	         AC_MSG_ERROR([*** Required xft Librarys not found ***]))
fi

AM_CONDITIONAL(WANT_CAIRO, test x$enable_cairo = xyes)

if test x$enable_cairo = xyes; then
   AC_DEFINE_UNQUOTED(WANT_CAIRO, 1, [Use Cairo to paint libs])
fi

if test x$enable_examples = xyes; then
   PKG_CHECK_MODULES(GTK2, gtk+-2.0,, [enable_examples="no"])
fi

AM_CONDITIONAL(WANT_EXAMPLES, test x$enable_examples = xyes)

dnl ------ Expat ------------------------------------------------------------

  case "$expat_includes" in
    yes|no)
	EXPAT_CFLAGS=""
	;;
    *)
	EXPAT_CFLAGS="-I$expat_includes"
	;;
  esac
	
  case "$expat_lib" in
    yes)

	case "$expat" in
	  yes)
		EXPAT_LIBS="-lexpat"
		;;
	    *)
		EXPAT_LIBS="-L$expat/lib -lexpat"
		;;
	esac

	;;
   no)
	;;
   *)
	EXPAT_LIBS="-L$expat_lib -lexpat"
	;;
   esac

   expatsaved_CPPFLAGS="$CPPFLAGS"
   CPPFLAGS="$CPPFLAGS $EXPAT_CFLAGS"
   expatsaved_LIBS="$LIBS"
   LIBS="$LIBS $EXPAT_LIBS"

   AC_CHECK_HEADER(expat.h)
   case "$ac_cv_header_expat_h" in
     no)
	 AC_CHECK_HEADER(xmlparse.h)

	 case "$ac_cv_header_xmlparse_h" in
	   no)
		have_expat_header=no;
		;;
	   yes)
		HAVE_XMLPARSE_H=1
		AC_SUBST(HAVE_XMLPARSE_H)
		AC_DEFINE_UNQUOTED(HAVE_XMLPARSE_H,$HAVE_XMLPARSE_H,
				       [Use xmlparse.h instead of expat.h])
		have_expat_header=yes
	        ;;
	 esac
	 ;;
     yes)
	 have_expat_header=yes
	;;
   esac
	
   case "$have_expat_header" in
     no)
	expat=no
	;;
     yes)
	AC_CHECK_FUNCS(XML_ParserCreate)

	case "$ac_cv_func_XML_ParserCreate" in
          no)
	  	expat=no
		;;
	  yes)
		HAVE_EXPAT=1
		AC_SUBST(HAVE_EXPAT)
		AC_DEFINE_UNQUOTED(HAVE_EXPAT,$HAVE_EXPAT,
		[Found a useable expat library])
		;;
	esac
	;;
   esac
	
   CPPFLAGS="$saved_CPPFLAGS"
   LIBS="$saved_LIBS"

   if test x$expat = xno; then
      AC_MSG_ERROR([cannot find expat library])
   fi


dnl ------ Debug Build ------------------------------------------------------

if test x$enable_debug = xyes; then
   AC_DEFINE_UNQUOTED(WANT_DEBUG, 1, [Make a debug (Verbose) Build])
fi


dnl ------ GCC flags --------------------------------------------------------

if test "x$GCC" = "xyes"; then
        GCC_WARNINGS="-g -Wall -fno-strict-aliasing"
        FAKEKEY_CFLAGS="$GCC_WARNINGS $FAKEKEY_CFLAGS"
fi


dnl ------ Substitute in found libs, clags to Makefiles etc -----------------

AC_SUBST(FAKEKEY_CFLAGS)
AC_SUBST(FAKEKEY_LIBS)

AC_SUBST(XFT_CFLAGS)
AC_SUBST(XFT_LIBS)

AC_SUBST(EXPAT_LIBS)
AC_SUBST(EXPAT_CFLAGS)

AC_OUTPUT([
Makefile
src/Makefile  
layouts/Makefile
examples/Makefile
])

dnl ==========================================================================
echo "
                    Matchbox-keyboard $VERSION
                  =========================

            prefix:                       ${prefix}
            source code location:         ${srcdir}
            compiler:                     ${CC} 

            Building with Debug:          ${enable_debug}
            Building with Cairo:          ${enable_cairo}
            Building Examples:            ${enable_examples}
"