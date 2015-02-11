# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  config.vm.box = "http://files.vagrantup.com/precise64.box"
  config.vm.provision "shell", inline: <<-SHELL
    # Update
    sudo apt-get update -qq
    sudo DEBIAN_FRONTEND=noninteractive apt-get upgrade -qq -o Dpkg::Options::="--force-confnew"

    # Install dependencies
    /vagrant/scripts/deps.sh

    # Clean up
    sudo apt-get clean
    sudo apt-get autoclean
    sudo apt-get autoremove
  SHELL
end
