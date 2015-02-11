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

    # Add toolchain repo for GCC 4.8
    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo apt-get update -qq

    # Install GCC 4.8
    sudo DEBIAN_FRONTEND=noninteractive apt-get install -qq build-essential cmake gcc-4.8 g++-4.8
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50

    # Clean up
    sudo apt-get clean
    sudo apt-get autoclean
    sudo apt-get autoremove
  SHELL
end
