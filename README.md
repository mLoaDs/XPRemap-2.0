<img width="128" alt="xbox-360-control-game-tool" src="https://github.com/user-attachments/assets/23e3f696-c71f-4920-8ba8-8920c937d7a8">

# XPRemap-2.0
by the2000

XPowerRemap (or XPRemap) is a DLL plugin that allows user to configure and remap input buttons.

About:
--------------------------------------------------------------------------------
XPowerRemap (or XPRemap) is a DLL plugin that allows user to configure and remap
input buttons. In addition to remapping the buttons, the user can also adjust
the deadzone thresholds of the analog switches, invert analog stick directions,
and set the rate of presses.

This latest version adds support for kernel 12611. Priority to applying
deadzones before button remaps have also been added. In addition to the minor
fix, this plugin now also allows rapid fire feature (see notes for details and
additional info) and analog stick inversions.

Agreement:
--------------------------------------------------------------------------------
This work is presented as is. I, the2000, do not guarantee anything will work
smoothly and flawlessly. Using this work means you agree that anything can and
will happen that is not in everyone's favor. You agree to not blame anyone if
such situation arises. You will also take FULL AND COMPLETE responsibility for
your usage of this work. I, nor any other person who worked with me on this,
will not offer any support unless we deem it necessary.

Requirements:
--------------------------------------------------------------------------------
-fbBuild 0.1 (for 12611) / FreeBOOT 0.032 by Ikari (for 9199)
-DashLaunch 2.xx by [cOz] (make sure to follow the readme he included).

Notes:
--------------------------------------------------------------------------------
-The original work of this tool came from [cOz], so be sure to thank him as much
as you would thank me.

-To use the plugin, extract the zip package and put the contents of
"put_contents_to_usb_root" to the root of your USB drive. The root of the USB
drive must contain the launch.ini file + plugins directory, and not the
"put_contents_to_usb_root" folder.

-Modify the [QuickLaunchButtons] section of launch.ini if necessary. You can
modify the [plugins] section but make sure to follow the notes below regarding
paths.

-Modify the /plugins/xpremap/xpremap.ini file to suit your needs. It important
to follow the instructions/notes/comments added in the .ini file or the plugin
will not work properly.

-IMPORTANT ABOUT STICK DIRECTION INVERTS: The labels on the .ini pertain to the
user input and not the output (if remapped from the p[1/2/3/4]config section).
I.E.: If LYTHUMB is mapped to output RYTHUMB, to invert the directions, set
LYTHUMB's invert to 1 in the .ini file. (This is explained again in the .ini).

-IMPORTANT ABOUT RAPIDFIRE: this whole plugin is hooked to xam.xex's export for
the input driver read function. As such, all features apply on lower level 
(excluding kernel, HAL, & hardware). What this means is that the rapid fire
feature may and will not work in many games that perform prelude or postlude
code before and after reading input from the driver. One of which is the XInput2
API. This API is used mostly in games that require special/unique controllers.
Rhythm games (Guitar Hero, Rock Band, etc.), driving games that use the steering
wheel, fighting games that use arcade type joysticks (Street Fighter), etc, are
among the games where XPRemap's rapidfire feature may not work.

There is, however, a workaround for this. It involves modifying the
XInput2Sample function within the executable. Make it so that it returns the
pChanged parameter as TRUE.

You can also set the deadzones of the analog sticks to the max. By doing so,
when you hold the button which rapidfire is set, you can just tilt the analog
sticks back & forth. This will still trigger the XInput2Sample function to
return pChanged as TRUE while not having an effect in the game (because of
being in deadzone). This may be an easier solution instead of tapping a digital
button. Though this method is still not guaranteed to be reliable.

If all else fails, then hardware mod is the most trusted and effective solution
for rapid fire. Additionally, code is public, so you can write your own rapid
fire feature! Lots of solutions there so please do not complain about it!

-It is important the paths are modified or changed accordingly. The package is
already organized so that the XPRemap plugin is in /plugins/xpremap/ directory
of the loading device. The xpremap.ini found in /plugins/xpremap/ should not be
moved or the configuration will not be loaded by the DLL. The xpremap.xex, on
the other hand, can be moved else where (so long as launch.xex can find it). But
I suggest and strongly recommend to just use the default placements.

-If the plugin does not work, check your devices. The pre-compiled XEX uses
USB device by default, so if you are using that build, make sure to only insert
the device that hosts the plugin.

-This plugin uses the base address of 0x91F30000. Make sure you have no plugins
or applications using that address or the DLL will not work properly. As an
early friendly warning, future dash/kernel updates may, and will, render this
plugin unusable.

-This plugin modifies the input on a general level. In other words, all
applications (including the dashboard) will have their buttons remapped.

-It is NOW POSSIBLE to install/put the plugin in HDD, MMU, Flash, DVD drive, or
USB FATX (XTAF) format devices. To do this, you will need to compile the source
after changing the preprocessor code for USE_DEV.

-All other versions of Kernel/Dash Launch are theoretically supported, but not
directly. You may have to modify certain pieces of the code to achieve this.

Changelog:
--------------------------------------------------------------------------------
2.0:
  - Now supports kernel 12611
  - All changes made in version 1.5
  - Source code now made public

1.5: (not released)
  - Prioritized deadzones over remap so that the deadzone setting is applied on
    the input
  - Added analog stick direction inversions
  - Added a simple rapidfire solution
  - Cleaned up the reading of config from .ini

1.0:
  - Initial public release
  - Allows remapping digital pads and swapping analogs
  - User configurable deadzone settings

0.x: (not released)
  - [cOz]'s initial version for deadzone adjustments

--------------------------------------------------------------------------------
Thanks/Shouts:
--------------------------------------------------------------------------------
Ced2911
DeadlyD
Echelo
Icekiller
Jefff
LoveMHz
[cOz]
