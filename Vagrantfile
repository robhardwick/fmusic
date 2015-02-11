# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  config.vm.box = "http://files.vagrantup.com/precise64.box"
  config.vm.provision "shell", inline: <<-SHELL
    # Install dependencies
    /vagrant/scripts/deps.sh

    # Clean up
    sudo apt-get clean
    sudo apt-get autoclean
    sudo apt-get autoremove
  SHELL
end
