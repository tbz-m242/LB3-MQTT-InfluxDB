###################################################################
#File Name	    : Vagrantfile                                                                                              
#Description	  : This is a Vagrantfile for an automated
#                 deployment of the project M242 Lb03.                                                                                 
#Args           :                                                                                           
#Author       	: Yves Wetter                                             
#Email         	: yves.wetter@edu.tbz.ch                                         
###################################################################
Vagrant.configure("2") do |config|

  config.vm.define "m242-mosquitto" do |mosquitto|
    mosquitto.vm.box = "ubuntu/bionic64"
    mosquitto.vm.hostname = "m242-mosquitto"
    mosquitto.vm.network "public_network" , bridge: [
      "Intel(R) Wi-Fi 6 AX201 160MHz",
      "WLAN",
      "Drahtlos-LAN-Adapter WLAN",
      "en0: Wi-Fi (AirPort)"
    ]
    mosquitto.vm.network "private_network", ip: "192.168.11.2",
      virtualbox__intnet: "iot"
    mosquitto.vm.synced_folder "install/", "/mnt"
    mosquitto.vm.provision :shell, :path => "./install/mosquitto/install.sh"
  end

  config.vm.define "m242-influxdb" do |influxdb|
    influxdb.vm.box = "ubuntu/bionic64"
    influxdb.vm.hostname = "m242-influxdb"
    influxdb.vm.network "private_network", ip: "192.168.11.3",
      virtualbox__intnet: "iot"
    influxdb.vm.synced_folder "install/", "/mnt"
    influxdb.vm.provision :shell, :path => "./install/influxdb/install.sh"
  end

  config.vm.define "m242-grafana" do |grafana|
    grafana.vm.box = "ubuntu/bionic64"
    grafana.vm.hostname = "m242-grafana"
    grafana.vm.network "private_network", ip: "192.168.11.4",
      virtualbox__intnet: "iot"
    grafana.vm.synced_folder "install/", "/mnt"
    grafana.vm.provision :shell, :path => "./install/grafana/install.sh"
    grafana.vm.network "forwarded_port", guest: 3000, host: 3000
  end
end