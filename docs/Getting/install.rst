.. SPDX-License-Identifier: GPL-3.0-or-later
.. SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors
.. SPDX-FileCopyrightText: James Robertson <jwrober@gmail.com>
.. SPDX-FileCopyrightText: Louis Moureaux <m_louis30@yahoo.com>

.. include:: /global-include.rst

Installing Freeciv21
********************

The developers of Freeciv21 provide pre-compiled binaries and installation packages for tagged releases. They
can be found on the Longturn GitHub Repository for Freeciv21 at
https://github.com/longturn/freeciv21/releases. The Longturn community provides binary packages for
Debian-based Linux distributions (Debian and Ubuntu), Microsoft Windows\ |reg|, and Apple macOS\ |reg|.

If you are an Arch Linux user, you can find Freeciv21 in the AUR at https://aur.archlinux.org/packages/freeciv21.

.. note::
  We are in the process of moving to openSUSE Build Service (OBS) for our native Linux packages. The above
  mentioned GitHub releases page will eventually lose the Debian package in favor of OBS. See steps below
  to add our OBS repository to your system. We currently support all editions (*Stable*, *Development*, and 
  *Unstable*) of Freeciv21 in OBS.

  OBS supports both ``x86_64`` and ``aarch64`` binaries.

  Refer to :ref:`openSUSE Build Service (OBS) <coding-packaging-obs-support>` for which OS versions are 
  supported.


A comment about editions of Freeciv21:

* The *Stable* edition is typically a point release behind *Development* and is maintained for long term 
  support. We patch for bugs and rarely if ever add features to it.
* The *Development* edition is being actively worked on. We are constantly adding new features, fixing bugs, 
  and improving on existing features. Following our :doc:`Release </Contributing/release>` process, we tag the 
  code periodically with a development or pre-stable release. The *Development* edition follows these 
  pre-release builds.
* The *Unstable* edition follows the ``HEAD`` of the ``master`` branch. This is bleeding edge code, may break, 
  or crash. The edition is updated every time we merge a :doc:`Pull Request </Contributing/pull-request>` to 
  ``master``. Your mileage may very, however the developers typically work hard to keep the game playable. 
  Often if a breaking bug or issue is discovered it is resolved quickly. The developers play on *Unstable*, so 
  there is some incentive to keep it working.


Windows
=======

For more information on using the Windows Installer package, you can read about it at :doc:`windows-install`.

Debian and Ubuntu Linux
=======================

These systems rely on the :file:`.deb` package file type.

To install the Debian / Ubuntu package, we first need to add our build service repository. Once that is
complete, we can install Freeciv21.

To install the *Stable* edition on :strong:`Debian`:

.. code-block:: sh

  $ echo `cat /etc/os-release | grep VERSION_ID | awk -F"=" '{print $2}'`
  $ wget -qO- \
      https://build.opensuse.org/projects/home:longturn/signing_keys/download?kind=gpg | \
      sudo gpg --dearmor -o /etc/apt/keyrings/obs-longturn.gpg
  $ sudo bash -c \
      'echo "deb [signed-by=/etc/apt/keyrings/obs-longturn.gpg] https://download.opensuse.org/repositories/home:/longturn/Debian_[##]/ ./" > \
      /etc/apt/sources.list.d/obs-longturn.list'
  $ sudo apt update
  $ sudo apt install freeciv21


Notes on the commands above:

* The ``echo`` command will give you the version of Debian you are running in the familiar ``##``
  format.
* The ``wget`` command downloads and installs the repository's GPG key needed by ``apt``.
* The ``sudo bash -c`` command will write a sources :file:`.list` file. For it to work, you will need to
  manually change the ``[##]`` in the example above with the value of the ``echo`` command.


If you wish to install the *Development* edition change 
``https://download.opensuse.org/repositories/home:/longturn/Debian_[##]/``
to ``https://download.opensuse.org/repositories/home:/longturn:/development/Debian_[##]/``.

If you wish to install the *Unstable* edition change 
``https://download.opensuse.org/repositories/home:/longturn/Debian_[##]/``
to ``https://download.opensuse.org/repositories/home:/longturn:/unstable/Debian_[##]/``.


To install the *Stable* edition on :strong:`Ubuntu`:

.. code-block:: sh

  $ echo `cat /etc/os-release | grep VERSION_ID | awk -F"=" '{print $2}'`
  $ wget -qO- \
      https://build.opensuse.org/projects/home:longturn/signing_keys/download?kind=gpg | \
      sudo gpg --dearmor -o /etc/apt/keyrings/obs-longturn.gpg
  $ sudo bash -c \
      'echo "deb [signed-by=/etc/apt/keyrings/obs-longturn.gpg] https://download.opensuse.org/repositories/home:/longturn/xUbuntu_[YY.MM]/ ./" > \
      /etc/apt/sources.list.d/obs-longturn.list'
  $ sudo apt update
  $ sudo apt install freeciv21


Notes on the commands above:

* The ``echo`` command will give you the version of Ubuntu you are running in the familiar ``YY.MM``
  format.
* The ``wget`` command downloads and installs the repository's GPG key needed by ``apt``.
* The ``sudo bash -c`` command will write a sources :file:`.list` file. For it to work, you will need to
  manually change the ``[YY.MM]`` in the example above with the value of the ``echo`` command.

If you wish to install the *Development* edition change 
``https://download.opensuse.org/repositories/home:/longturn/xUbuntu_[YY.MM]/``
to ``https://download.opensuse.org/repositories/home:/longturn:/development/xUbuntu_[YY.MM]/``.

If you wish to install the *Unstable* edition change 
``https://download.opensuse.org/repositories/home:/longturn/xUbuntu_[YY.MM]/``
to ``https://download.opensuse.org/repositories/home:/longturn:/unstable/xUbuntu_[YY.MM]/``.


:strong:`File from our Releases Page`:

If you obtained the :file:`.deb` from the releases page, use the ``apt`` command with elevated privileges
like this:

.. code-block:: sh

  $ sudo apt install ./freeciv21_*_amd64.deb


Fedora and openSUSE Tumbleweed Linux
====================================

These systems rely on the :file:`.rpm` package file type.

To install the Fedora / openSUSE Tumbleweed package, we first need to add our build service repository. Once
that is complete, we can install Freeciv21.

.. note::
  The Fedora and Tumbleweed repositories contain the key needed and is installed automatically, so do not
  worry that the commands below do not include steps.

To install the *Stable* edition on :strong:`Red Hat Fedora`:

.. code-block:: sh

  $ echo `cat /etc/os-release | grep VERSION_ID | awk -F"=" '{print $2}'`
  $ sudo dnf config-manager addrepo \
      --from-repofile=https://download.opensuse.org/repositories/home:/longturn/Fedora_[##]/home:longturn.repo
  $ sudo dnf update
  $ sudo dnf install freeciv21


Notes on the commands above:

* The ``echo`` command will give you the version of Fedora you are running in the familiar ``##``
  format.
* The ``dnf`` command will add the repository to your system. You will need to manually change the ``[##]``
  in the example above with the value of the ``echo`` command.


If you wish to install the *Development* edition change 
``https://download.opensuse.org/repositories/home:/longturn/Fedora_[##]/home:longturn.repo``
to 
``https://download.opensuse.org/repositories/home:/longturn:/development/Fedora_[##]/home:longturn:development.repo``.

If you wish to install the *Unstable* edition change 
``https://download.opensuse.org/repositories/home:/longturn/Fedora_[##]/home:longturn.repo``
to 
``https://download.opensuse.org/repositories/home:/longturn:/unstable/Fedora_[##]/home:longturn:unstable.repo``.


To install the *Stable* edition on :strong:`openSUSE Tumbleweed`:

openSUSE Tumbleweed is a rolling release, which means it does not have a specific version. With that, we
simply add the repository.

.. code-block:: sh

  $ sudo zypper addrepo --refresh \
      https://download.opensuse.org/repositories/home:/longturn/openSUSE_Tumbleweed/ Longturn
  $ sudo zypper install freeciv21


If you wish to install the *Development* edition change 
``https://download.opensuse.org/repositories/home:/longturn/openSUSE_Tumbleweed/ Longturn``
to 
``https://download.opensuse.org/repositories/home:/longturn:/development/openSUSE_Tumbleweed/ Longturn:Development``.

If you wish to install the *Unstable* edition change 
``https://download.opensuse.org/repositories/home:/longturn/openSUSE_Tumbleweed/ Longturn``
to 
``https://download.opensuse.org/repositories/home:/longturn:/unstable/openSUSE_Tumbleweed/ Longturn:Unstable``.


Generic Linux
=============

Freeciv21 is also available as a snap or flatpak containerized application. Different distributions support
one or the other by default.

:strong:`Snap`

Debian Linux variants (those that rely on ``apt`` for package management):

.. code-block:: sh

  $ sudo apt install snapd
  $ sudo systemctl enable snapd
  $ sudo snap install freeciv21


Fedora/Red Hat Linux variants (those that rely on ``dnf`` for package management):

.. code-block:: sh

  $ sudo dnf install snapd
  $ sudo systemctl enable snapd
  $ sudo snap install freeciv21


:strong:`Flatpak`

Debian Linux variants (those that rely on ``apt`` for package management):

.. code-block:: sh

  $ sudo apt install flatpak
  $ sudo flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
  $ sudo flatpak install net.longturn.freeciv21


Fedora/Red Hat variants (those that rely on ``dnf`` for package management):

.. code-block:: sh

  $ sudo dnf install flatpak
  $ sudo flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
  $ sudo flatpak install net.longturn.freeciv21


If you want to install the *Development* edition of Freeciv21, you can use the Flathub Beta repository. 

.. code-block:: sh

  $ sudo flatpak remote-add --if-not-exists flathub-beta https://flathub.org/beta-repo/flathub-beta.flatpakrepo


macOS
=====

To install the macOS ``.dmg`` package, you start by double-clicking the file to mount it in Finder. Drag the
game to the Applications folder. When finished, unmount the package.

.. _Freeciv21 macOS Install:
.. figure:: /_static/images/macos-install.png
  :align: center
  :alt: Freeciv21 macOS Install
  :figclass: align-center

  Freeciv21 macOS Install

.. note::
  In newer versions of macOS, you may get an error message when trying to mount the package: "Freeciv21.app is
  damaged and can't be opened." You will need to adjust the security settings on your computer. Here are some
  website links to help:

  * https://community.kde.org/Mac
  * https://appletoolbox.com/app-is-damaged-cannot-be-opened-mac/
  * https://support.apple.com/guide/mac-help/open-an-app-by-overriding-security-settings-mh40617/15.0/mac/15.0


Docker
======

* Install :ref:`freeciv21-server in a docker container <manuals-advanced-docker>`.

A Note About Native Language Support
====================================

Freeciv21 is packaged with Native Language Support (NLS), also known as Internationalization (i18n). By
default, Freeciv21 will use the primary language that the client operating system is set to use. However, you
may wish to play the game with a different language.

All the code and strings used in the game are based on US English (``en_US``) and encoded as UTF8
(``en_US.UTF8``). If you wish to play the game in a different language, you can do so by setting an
environment variable to the language code of your choice.

At a minimum, all you need is the two letter code of the language you wish to play with. Here is a list of
them: https://en.wikipedia.org/wiki/List_of_ISO_639_language_codes

.. note::
  We do not support every single language code in the list above, but we do have some translations for many of
  them.

On a Linux or macOS based system, open a terminal and set the ``LANG`` variable to the language code. In the 
example we pick German (Deutsch).

.. code-block:: sh

  $ LANG=de_DE.UTF8 path/to/freeciv21-client


That setting will stay in effect as long as the terminal window is open. Freeciv21 will use the environment
context into account.

If you have installed the snap package, you can run the game with the language of your choice as well.
Following the example above, we pick German and then open the game via ``snap``.

.. code-block:: sh

  $ LANG=de_DE.UTF8 snap run freeciv21.freeciv21-client


.. note::
  You can also add ``export LANG=de_DE.UTF8`` to your user's :file:`.bashrc` or :file:`.bash_profile`.
  On macOS use :file:`.zshrc`. The variable will then be set every time you logon to your computer. However,
  this could also sets the language for pretty much every application.


The ``LANG`` variable also works on Windows based systems. Open a command prompt, powershell prompt, or
terminal.

.. code-block:: sh

  PS C:\Users\Username> setx LANG de_DE.UTF8


Then open Freeciv21 from the start menu like normal.

.. note::
  As with the note related to Linux based systems. The ``setx`` command sets a user level environment variable
  to the language selected. Any applications that use the ``LANG`` variable will also be impacted. This is
  especially true when working in the MSYS2 environment. You can set the variable to another language following
  the same step above. Simply set the variable to a different locale code.
