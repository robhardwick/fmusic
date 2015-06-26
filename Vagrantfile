# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
    config.vm.box = "ubuntu/trusty64"

    config.vm.provider "virtualbox" do |v|
        v.memory = 2048
        v.cpus = 2
    end

    config.vm.provision "shell", inline: <<-SHELL
        # Update
        sudo apt-get update -qq
        sudo DEBIAN_FRONTEND=noninteractive apt-get upgrade -qq -o Dpkg::Options::="--force-confnew"

        # Install dependencies
        /vagrant/scripts/deps-ubuntu.sh

        # Setup JACK
        sudo sh -c 'echo "@audio\t-\trtprio\t99" >> /etc/security/limits.conf'
        sudo usermod -a -G audio vagrant

        # Clean up
        sudo apt-get clean
        sudo apt-get autoclean
        sudo apt-get autoremove
        rm -r /tmp/qt /tmp/qt.tgz
    SHELL
end
