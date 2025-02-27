PDCurses for X11
================

This is a port of PDCurses for X11, aka XCurses.  It is designed to
allow existing curses programs to be re-compiled with PDCurses,
resulting in native X11 programs.


Building
--------

- Run "./configure". To build the wide-character version of the library,
  specify "--enable-widec" as a parameter. To use X Input Methods, add
  "--enable-xim". I recommend these options, but I haven't yet made
  them the defaults, for the sake of backwards compatibility.

  If your system is lacking in UTF-8 support, you can force the use of
  UTF-8 instead of the system locale via "--enable-force-utf8".

  If configure can't find your X include files or X libraries, you can
  specify the paths with the arguments "--x-includes=inc_path" and/or
  "--x-libraries=lib_path".

  By default, the library and demo programs are built with the optimizer
  switch -O2. You can turn this off, and turn on debugging (-g), by
  adding "--enable-debug" to the configure command.

- Run "make". This should build libXCurses and all the demo programs.

- Optionally, run "make install". curses.h and panel.h will be renamed
  when installed (to xcurses.h and xpanel.h), to avoid conflicts with
  any existing curses installations. Unrenamed copies of curses.h and
  panel.h are installed in (by default) /usr/local/include/xcurses.


Usage
-----

PDCurses for X11 uses the System V IPC shared memory facility, along
with sockets, to share data between the curses program and the child
process created to manage the X stuff.

When compiling your application, you need to include the \<curses.h\> or
\<xcurses.h\> that comes with PDCurses. You also need to link your code
with libXCurses. You may need to link with the following libraries under
X11R5:

    Xaw Xmu Xt X11

or, under X11R6:

    Xaw Xmu Xt X11 SM ICE Xext

You can run "xcurses-config --libs" to show the link parameters for your
system. If using dynamic linking, on some systems, "-lXCurses" suffices.

By calling Xinitscr() rather than initscr(), you can pass your program
name and resource overrides to PDCurses. The program name is used as the
title of the X window, and for defining X resources specific to your
program.


Interaction with stdio
----------------------

Be aware that curses programs that expect to have a normal tty
underneath them will be very disappointed! Output directed to stdout
will go to the xterm that invoked the PDCurses application, or to the
console if not invoked directly from an xterm. Similarly, stdin will
expect its input from the same place as stdout.


X Resources
-----------

PDCurses for X11 recognizes the following resources:

### lines

Specifies the number of lines the "screen" will have. Directly equates
to LINES. There is no theoretical maximum. The minimum value must be 2.
Default: 24

### cols

Specifies the number of columns the "screen" will have. Directly equates
to COLS. There is no theoretical maximum. The minimum value must be 2.
Default: 80

### normalFont

The name of a fixed width font. Defaults:
- narrow: -misc-fixed-medium-r-normal--13-120-75-75-c-70-iso8859-1
- wide: -misc-fixed-medium-r-normal--20-200-75-75-c-100-iso10646-1

### italicFont

The name of a fixed width font to be used for characters with A_ITALIC
attributes. Must have the same cell size as normalFont. Defaults:
- narrow: -misc-fixed-medium-o-normal--13-120-75-75-c-70-iso8859-1
- wide: -misc-fixed-medium-o-normal--20-200-75-75-c-100-iso10646-1

### boldFont

The name of a fixed width font to be used for characters with A_BOLD
attributes. Must have the same cell size as normalFont. Defaults:
- narrow: -misc-fixed-bold-r-normal--13-120-75-75-c-70-iso8859-1
- wide: -misc-fixed-bold-r-normal--20-200-75-75-c-100-iso10646-1

### pointer

The name of a valid pointer cursor. Default: xterm

### pointerForeColor

The foreground color of the pointer. Default: black

### pointerBackColor

The background color of the pointer. Default: white

### cursorColor

### textCursor

The alignment of the text cursor; horizontal or vertical. Default:
horizontal

### colorBlack

The color of the COLOR_BLACK attribute. Default: Black

### colorRed

The color of the COLOR_RED attribute. Default: red3

### colorGreen

The color of the COLOR_GREEN attribute. Default: green3

### colorYellow

The color of the COLOR_YELLOW attribute. Default: yellow3

### colorBlue

The color of the COLOR_BLUE attribute. Default: blue3

### colorMagenta

The color of the COLOR_MAGENTA attribute. Default: magenta3

### colorCyan

The color of the COLOR_CYAN attribute. Default: cyan3

### colorWhite

The color of the COLOR_WHITE attribute. Default: Grey

### colorBoldBlack

COLOR_BLACK combined with A_BOLD. Default: grey40

### colorBoldRed

COLOR_RED combined with A_BOLD. Default: red1

### colorBoldGreen

COLOR_GREEN combined with A_BOLD. Default: green1

### colorBoldYellow

COLOR_YELLOW combined with A_BOLD. Default: yellow1

### colorBoldBlue

COLOR_BLUE combined with A_BOLD. Default: blue1

### colorBoldMagenta

COLOR_MAGENTA combined with A_BOLD. Default: magenta1

### colorBoldCyan

COLOR_CYAN combined with A_BOLD. Default: cyan1

### colorBoldWhite

COLOR_WHITE combined with A_BOLD. Default: White

### bitmap

The name of a valid bitmap file of depth 1 (black and white) used for
the application's icon. The file is an X bitmap. Default: a 32x32 or
64x64 pixmap depending on the window manager

### pixmap

The name of a valid pixmap file of any depth supported by the window
manager (color) for the application's icon, The file is an X11 pixmap.
This resource is only available if the libXpm package has been installed
(most systems have this by default). This resource overrides the
"bitmap" resource. Default: none, uses default bitmap above

### translations

Translations enable the user to customize the action that occurs when a
key, combination of keys, or a button is pressed.  The translations are
similar to those used by xterm.

Defaults:

    <Key>:        XCursesKeyPress()
    <KeyUp>:      XCursesKeyPress()
    <BtnDown>:    XCursesButton()
    <BtnUp>:      XCursesButton()
    <BtnMotion>:  XCursesButton()

The most useful action for KeyPress translations is string(). The
argument to the string() action can be either a string or a hex
representation of a character; e.g., string(0x1b) will send the ASCII
escape character to the application; string("[11~") will send [ 1 1 ~ ,
as separate keystrokes.

### shmmin

On most systems, there are two Unix kernel parameters that determine the
allowable size of a shared memory segment. These parameters are usually
something like SHMMIN and SHMMAX. To use shared memory, a program must
allocate a segment of shared memory that is between these two values.
Usually these values are like 1 for SHMMIN and some large number for
SHMMAX. Sometimes the Unix kernel is configured to have a value of
SHMMIN that is bigger than the size of one of the shared memory segments
that libXCurses uses. On these systems an error message like:

    Cannot allocate shared memory for SCREEN: Invalid argument

will result. To overcome this problem, this resource should be set to
the kernel value for SHMMIN. This ensures that a shared memory segment
will always be bigger than the kernel value for SHMMIN (and hopefully
less than SHMMAX!) Default: 0

### borderColor

The color of the border around the screen. Default: black

### borderWidth

The width in pixels of the border around the screen. Default: 0

### clickPeriod

The period (in milliseconds) between a button press and a button release
that determines if a click of a button has occurred. Default: 100

### doubleClickPeriod

The period (in milliseconds) between two button press events that
determines if a double click of a button has occurred. Default: 200

### composeKey

The name of the X key that defines the "compose key", which is used to
enter characters in the Latin-1 character set above 0xA0. (See "Compose
Keys for Latin-1" below.) This is used only when PDCurses is built
without XIM support. While in compose mode, the text cursor will appear
as a hollow rectangle. Default: Multi_key


Using Resources
---------------

All applications have a top-level class name of "XCurses". If Xinitscr()
is used, it sets an application's top-level widget name. (Otherwise the
name defaults to "PDCurses".)

Examples for app-defaults or .Xdefaults:

    !
    ! resources for XCurses class of programs
    !
    XCurses*lines:  30
    XCurses*cols:   80
    XCurses*normalFont:     9x13
    XCurses*bitmap: /tmp/xcurses.xbm
    XCurses*pointer: top_left_arrow
    !
    ! resources for testcurs - XCurses
    !
    testcurs.colorRed:      orange
    testcurs.colorBlack:    midnightblue
    testcurs.lines: 25
    *testcurs.Translations: #override \n \
      <Key>F12:  string(0x1b) string("[11~") \n
    !
    ! resources for THE - XCurses
    !
    ! resources with the * wildcard can be overridden by a parameter passed
    ! to initscr()
    !
    the*normalFont: 9x15
    the*lines:      40
    the*cols:       86
    the*pointer:    xterm
    the*pointerForeColor: white
    the*pointerBackColor: black
    !
    ! resources with the . format can not be overridden by a parameter passed
    ! to Xinitscr()
    !
    the.bitmap:     /home/mark/the/the64.xbm
    the.pixmap:     /home/mark/the/the64.xpm

Resources may also be passed as parameters to the Xinitscr() function.
Parameters are strings in the form of switches; e.g., to set the color
"red" to "indianred", and the number of lines to 30, the string passed
to Xinitscr would be: "-colorRed indianred -lines 30"


Compose Keys for Latin-1
------------------------

When built without XIM support, PDCurses for X11 provides its own,
limited compose key system for Latin-1 characters. The available
combinations are listed here. For a given character, any of the
combinations shown in the last column may be used. To generate a
character, press the "compose" key followed by one of the pairs of
keystrokes. Where no key is evident, the spacebar is used.  Thus, to
generate the NO-BREAK SPACE, press the "compose" key followed by two
hits of the spacebar.

With a typical modern X server, you can get many more compose key
combinations by using XIM instead. Configure PDCurses with --enable-xim
to use XIM support.

This document is encoded in UTF-8.

    Hex| Dec |Chr| Description ISO 10646-1:1993(E) | Compose key combinations
    ---+-----+---+---------------------------------+-------------------------
    A0 | 160 |   | NO-BREAK SPACE                  |
    A1 | 161 | ¡ | INVERTED EXCLAMATION MARK       | !   !!
    A2 | 162 | ¢ | CENT SIGN                       | c|  |c  c/  c$  C$  C|
    A3 | 163 | £ | POUND SIGN                      | L-  L$  L=  l-  l$  l=  |-
    A4 | 164 | ¤ | CURRENCY SIGN                   | xo  ox  XO  g$
    A5 | 165 | ¥ | YEN SIGN                        | =y  y=  =Y  Y=  Y-  y$  y-
    A6 | 166 | ¦ | BROKEN BAR                      | |   ||  vb  VB  |^
    A7 | 167 | § | SECTION SIGN                    | SO  SS  s!  S!  so
    A8 | 168 | ¨ | DIAERESIS                       | "   ""
    A9 | 169 | © | COPYRIGHT SIGN                  | CO  co  OC
    AA | 170 | ª | FEMININE ORDINAL INDICATOR      | sa  SA  a_  A_
    AB | 171 | « | LEFT DOUBLE ANGLE QUOTES        | <<
    AC | 172 | ¬ | NOT SIGN                        | -,  no  NO
    AD | 173 | ­ | SOFT HYPHEN                     | -   --
    AE | 174 | ® | REGISTERED SIGN                 | RO  ro  OR
    AF | 175 | ¯ | MACRON                          | -^  _^  __
    B0 | 176 | ° | DEGREE SIGN                     | o   0^  0*  de  DE  ^0
    B1 | 177 | ± | PLUS-MINUS SIGN                 | -+  +-
    B2 | 178 | ² | SUPERSCRIPT TWO                 | 2   2^  s2  ^2
    B3 | 179 | ³ | SUPERSCRIPT THREE               | 3   3^  s3  ^3
    B4 | 180 | ´ | ACUTE ACCENT                    | '   ''
    B5 | 181 | µ | MICRO SIGN                      | u   /u  /U  *m  *M
    B6 | 182 | ¶ | PILCROW SIGN                    | p!  P!  pg  PG
    B7 | 183 | · | MIDDLE DOT                      | .   .^  ..
    B8 | 184 | ¸ | CEDILLA                         | ,   ,,
    B9 | 185 | ¹ | SUPERSCRIPT ONE                 | 1   1^  s1  ^1
    BA | 186 | º | MASCULINE ORDINAL INDICATOR     | o_  s0  S0
    BB | 187 | » | RIGHT DOUBLE ANGLE QUOTES       | >>
    BC | 188 | ¼ | VULGAR FRACTION ONE QUARTER     | 14
    BD | 189 | ½ | VULGAR FRACTION ONE HALF        | 12
    BE | 190 | ¾ | VULGAR FRACTION THREE QUARTERS  | 34
    BF | 191 | ¿ | INVERTED QUESTION MARK          | ?   ??
    C0 | 192 | À | CAPITAL A WITH GRAVE ACCENT     | `A  A`
    C1 | 193 | Á | CAPITAL A WITH ACUTE ACCENT     | 'A  A'
    C2 | 194 | Â | CAPITAL A WITH CIRCUMFLEX ACCENT| ^A  A^  A>
    C3 | 195 | Ã | CAPITAL A WITH TILDE            | ~A  A~  A-
    C4 | 196 | Ä | CAPITAL A WITH DIAERESIS        | "A  A"
    C5 | 197 | Å | CAPITAL A WITH RING ABOVE       | oA  Ao  A*  OA  *A
    C6 | 198 | Æ | CAPITAL LIGATURE AE             | AE
    C7 | 199 | Ç | CAPITAL C WITH CEDILLA          | ,C  C,
    C8 | 200 | È | CAPITAL E WITH GRAVE ACCENT     | `E  E`
    C9 | 201 | É | CAPITAL E WITH ACUTE ACCENT     | 'E  E'
    CA | 202 | Ê | CAPITAL E WITH CIRCUMFLEX ACCENT| ^E  E^  E>
    CB | 203 | Ë | CAPITAL E WITH DIAERESIS        | "E  E"
    CC | 204 | Ì | CAPITAL I WITH GRAVE ACCENT     | `I  I`
    CD | 205 | Í | CAPITAL I WITH ACUTE ACCENT     | 'I  I'
    CE | 206 | Î | CAPITAL I WITH CIRCUMFLEX ACCENT| ^I  I^  I>
    CF | 207 | Ï | CAPITAL I WITH DIAERESIS        | "I  I"
    D0 | 208 | Ð | CAPITAL ETH                     | D-
    D1 | 209 | Ñ | CAPITAL N WITH TILDE            | ~N  N~  N-
    D2 | 210 | Ò | CAPITAL O WITH GRAVE ACCENT     | `O  O`
    D3 | 211 | Ó | CAPITAL O WITH ACUTE ACCENT     | 'O  O'
    D4 | 212 | Ô | CAPITAL O WITH CIRCUMFLEX ACCENT| ^O  O^  O>
    D5 | 213 | Õ | CAPITAL O WITH TILDE            | ~O  O~  O-
    D6 | 214 | Ö | CAPITAL O WITH DIAERESIS        | "O  O"
    D7 | 215 | × | MULTIPLICATION SIGN             | x   xx  XX  mu  MU
    D8 | 216 | Ø | CAPITAL O WITH STROKE           | /O  O/
    D9 | 217 | Ù | CAPITAL U WITH GRAVE ACCENT     | `U  U`
    DA | 218 | Ú | CAPITAL U WITH ACUTE ACCENT     | 'U  U'
    DB | 219 | Û | CAPITAL U WITH CIRCUMFLEX ACCENT| ^U  U^  U>
    DC | 220 | Ü | CAPITAL U WITH DIAERESIS        | "U  U"
    DD | 221 | Ý | CAPITAL Y WITH ACUTE ACCENT     | 'Y  Y'
    DE | 222 | Þ | CAPITAL THORN                   | P   TH  |P
    DF | 223 | ß | SMALL SHARP S                   | ss
    E0 | 224 | à | SMALL A WITH GRAVE ACCENT       | `a  a`
    E1 | 225 | á | SMALL A WITH ACUTE ACCENT       | 'a  a'
    E2 | 226 | â | SMALL A WITH CIRCUMFLEX ACCENT  | ^a  a^  a>
    E3 | 227 | ã | SMALL A WITH TILDE              | ~a  a~  a-
    E4 | 228 | ä | SMALL A WITH DIAERESIS          | "a  a"
    E5 | 229 | å | SMALL A WITH RING ABOVE         | oa  ao  Oa  a*  *a
    E6 | 230 | æ | SMALL LIGATURE AE               | ae
    E7 | 231 | ç | SMALL C WITH CEDILLA            | ,c  c,
    E8 | 232 | è | SMALL E WITH GRAVE ACCENT       | `e  e`
    E9 | 233 | é | SMALL E WITH ACUTE ACCENT       | 'e  e'
    EA | 234 | ê | SMALL E WITH CIRCUMFLEX ACCENT  | ^e  e^  e>
    EB | 235 | ë | SMALL E WITH DIAERESIS          | "e  e"
    EC | 236 | ì | SMALL I WITH GRAVE ACCENT       | `i  i`
    ED | 237 | í | SMALL I WITH ACUTE ACCENT       | 'i  i'
    EE | 238 | î | SMALL I WITH CIRCUMFLEX ACCENT  | ^i  i^  i>
    EF | 239 | ï | SMALL I WITH DIAERESIS          | "i  i"
    F0 | 240 | ð | SMALL ETH                       | d-
    F1 | 241 | ñ | SMALL N WITH TILDE              | ~n  n~  n-
    F2 | 242 | ò | SMALL O WITH GRAVE ACCENT       | `o  o`
    F3 | 243 | ó | SMALL O WITH ACUTE ACCENT       | 'o  o'
    F4 | 244 | ô | SMALL O WITH CIRCUMFLEX ACCENT  | ^o  o^  o>
    F5 | 245 | õ | SMALL O WITH TILDE              | ~o  o~  o-
    F6 | 246 | ö | SMALL O WITH DIAERESIS          | "o  o"
    F7 | 247 | ÷ | DIVISION SIGN                   | -:  :-
    F8 | 248 | ø | SMALL O WITH OBLIQUE BAR        | /o  o/
    F9 | 249 | ù | SMALL U WITH GRAVE ACCENT       | `u  u`
    FA | 250 | ú | SMALL U WITH ACUTE ACCENT       | 'u  u'
    FB | 251 | û | SMALL U WITH CIRCUMFLEX ACCENT  | ^u  u^  u>
    FC | 252 | ü | SMALL U WITH DIAERESIS          | "u  u"
    FD | 253 | ý | SMALL Y WITH ACUTE ACCENT       | 'y  y'
    FE | 254 | þ | SMALL THORN                     | p   th  |p
    FF | 255 | ÿ | SMALL Y WITH DIAERESIS          | "y  y"


Deprecated
----------

XCursesProgramName is no longer used. To set the program name, you must
use Xinitscr(), or PDC_set_title() to set just the window title.

The XCursesExit() function is now called automatically via atexit().
(Multiple calls to it are OK, so you don't need to remove it if you've
already added it for previous versions of PDCurses.)

XCURSES is no longer defined automatically, but need not be defined,
unless you want the X11-specific prototypes. (Normal curses programs
won't need it.)


Distribution Status
-------------------

As of April 13, 2006, the files in this directory are released to the
Public Domain, except for ScrollBox*, which are under essentially the
MIT X License; config.guess and config.sub, which are under the GPL; and
configure, which is under a free license described within it.


Acknowledgements
----------------

X11 port was provided by Mark Hessling <mark@rexx.org>
