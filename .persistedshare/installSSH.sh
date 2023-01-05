#!/usr/bin/env bash
#
# Licensed under the MIT License. See LICENSE-CODE in the project root for details.
#
# Exit codes:
# 0 - Success
# 1 - Unexpected failure
# 3 - Do not have permissions to run command
# 4 - Distribution not supported by script
#

cat << EOF

Github Codespaces ssh install script.

EOF

if [ "$1" = "false" ]; then INSTALL=0; else INSTALL=1; fi
if [ "$2" = "false" ]; then START=0; else START=1; fi

# Disable history substitution given use of "!" or errors occur in certain distros
set H+

# Utility function for exiting
exitScript()
{
    echo -e "\nPress enter to dismiss this message"
    read
    exit $1
}

# Wrapper function to only use sudo if not already root
sudoIf()
{
    if [ "$(id -u)" -ne 0 ]; then
        sudo $1 $2
    else
        $1 $2
    fi
}

# Utility function that waits for any existing installation operations to complete
# on Debian/Ubuntu based distributions and then calls apt-get
aptSudoIf() 
{
    while sudoIf fuser /var/lib/dpkg/lock >/dev/null 2>&1; do
        echo -ne "(*) Waiting for other package operations to complete.\r"
        sleep 1
        echo -ne "\r\033[K"
    done
    sudoIf apt-get "$1"
}

install()
{
     if [ $INSTALL -ne 0 ]; then
        echo -e "\n(*) Installing ssh server."
        # Install .NET Core dependencies
        if ! "$1" "$2"; then
            echo "(!) SSH Server installation failed!"
            exitScript 1
        fi
    fi
}

start()
{
     if [ $START -ne 0 ]; then
        echo -e "\n(*) Starting ssh server."
        # Install .NET Core dependencies
        if ! "$1" "$2"; then
            echo "(!) SSH Server start failed!"
            exitScript 1
        fi
    fi
}

createSSHGroupAlpine()
{
    if ! getent group ssh ; then
        sudoIf addgroup ssh
    fi
}

# Ensure apt is in non-interactive to avoid prompts
export DEBIAN_FRONTEND=noninteractive

# If not already root, validate user has sudo access and error if not.
if [ "$(id -u)" -ne 0 ]; then

# Can't indent or text will be indented
cat << EOF
To begin the installation process, your OS will now ask you to enter your
admin / root (sudo) password.

EOF
    # Validate user actually can use sudo
    if ! sudo -v > /dev/null 2>&1; then

# Can't indent or text will be indented
cat << EOF

(!) Dependency installation failed! You do not have the needed admin / root
    access to install ssh in the container.
EOF
        exitScript 3
    else
        echo ""
    fi
fi

#openSUSE - Has to be first since apt-get is available but package names different
if type zypper > /dev/null 2>&1; then
    echo "(*) Detected SUSE (unoffically/community supported)"
    install sudoIf "zypper -n in openssh-server"
    start sudoIf "/usr/bin/ssh-keygen -A"
    start sudoIf "/usr/sbin/sshd"

# Debian / Ubuntu
elif type apt-get > /dev/null 2>&1; then
    echo "(*) Detected Debian / Ubuntu"
   
    # Get latest package data
    echo -e "\n(*) Updating package lists..."
    if ! aptSudoIf "update"; then
        echo "(!) Failed to update list of available packages!"
        exitScript 1
    fi

    install aptSudoIf "install -yq openssh-server"
    start sudoIf "/etc/init.d/ssh start"

#RHL/Fedora/CentOS
elif type yum  > /dev/null 2>&1; then
    echo "(*) Detected RHL / Fedora / CentOS"

    # Update package repo indexes - returns 0 if no pacakges to upgrade,
    # 100 if there are packages to upgrade, and 1 on error
    echo -e "\n(*) Updating package lists..."
    sudoIf "yum check-update" >/dev/null 2>&1
    if [ $? -eq 1 ]; then
        echo "(!) Failed to update package list!"
        exitScript 1
    fi
    
    install sudoIf "dnf -y install openssh-server openssh-clients"
    start sudoIf "/usr/bin/ssh-keygen -A"
    start sudoIf "/usr/sbin/sshd"

#ArchLinux
elif type pacman > /dev/null 2>&1; then
    echo "(*) Detected Arch Linux (unoffically/community supported)"
    install sudoIf "pacman -Syu --noconfirm"
    install sudoIf "pacman -Sq --noconfirm --needed openssh"
    start sudoIf "/usr/bin/ssh-keygen -A"
    start sudoIf "/usr/sbin/sshd"

#Alpine Linux
elif type apk > /dev/null 2>&1; then
    echo "(*) Detected Alpine Linux"
    
    # Update package repo indexes    
    echo -e "\n(*) Updating and upgrading..."
    if ! sudoIf "apk update --wait 30"; then
        echo "(!) Failed to update package lists."
        exitScript 1
    fi
    # Upgrade to avoid package dependency conflicts
    if ! sudoIf "apk upgrade"; then
        echo "(!) Failed to upgrade."
        exitScript 1
    fi

    install sudoIf "apk add --no-cache openssh openssh-server openssh-server-pam"
    install createSSHGroupAlpine
    install sudoIf "touch /etc/pam.d/sshd"
    install sudoIf "touch /etc/pam.d/sshd.pam"
    install sudoIf "/usr/bin/ssh-keygen -A"
    start sudoIf "/usr/sbin/sshd.pam"

#If no supported package manager is found
else

# Can't indent or text will be indented
cat << EOF
(!) We are unable to install ssh for this version of Linux containers."
EOF

    exitScript 4
fi

echo -e "\n(*) Success!\n"
# Don't pause on exit here - we'll handle this in the extension
