#!/bin/bash
###################################################################
#File Name      : install.sh
#Description    : automated installation of Mosquitto.
#Args           :
#Author         : Yves Wetter
#Email          : yves.wetter@edu.tbz.ch
###################################################################
#default settings
    sudo apt-get update && sudo apt-get upgrade
    sudo apt-get -y install debconf-utils ufw
# installation
echo -c "begin installing"
sudo apt-get install -y mosquitto
sudo systemctl enable mosquitto
sudo systemctl restart mosquitto
# Firewall
    sudo ufw default deny incoming
    sudo ufw allow 1883/tcp
    sudo ufw allow 9001
    sudo ufw allow 22/tcp
    sudo ufw -f enable