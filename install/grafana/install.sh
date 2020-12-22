#!/bin/bash
###################################################################
#File Name      : install.sh
#Description    : automated installation of Grafana.
#Args           :
#Author         : Yves Wetter
#Email          : yves.wetter@edu.tbz.ch
###################################################################
#default settings
    sudo apt-get update && sudo apt-get upgrade
    sudo apt-get -y install debconf-utils ufw
# installation
udo apt-get install -y apt-transport-https software-properties-common wget
wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
sudo add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"
sudo apt-get update
sudo apt-get install -y grafana
sudo systemctl enable --now grafana-server
sudo systemctl start grafana-server
# Firewall
    sudo ufw default deny incoming
    sudo ufw allow 3000/tcp
    sudo ufw allow 22/tcp
    sudo ufw -f enable