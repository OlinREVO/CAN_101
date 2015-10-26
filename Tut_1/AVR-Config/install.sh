# Should be run with:
# wget https://raw.githubusercontent.com/OlinREVO/AVR-Config/master/install.sh
# bash install.sh

sudo apt-get install avrdude gcc-avr avr-libc git-core build-essential checkinstall
wget https://github.com/OlinREVO/AVR-Config/archive/master.zip
unzip master.zip
cd AVR-Config-master
sudo cp .avrduderc /root/ # For `sudo make flash`
mv .avrduderc ~
sudo mv 50-avr-programmers.rules /etc/udev/rules.d/
cd ..
rm -r AVR-Config-master
rm master.zip

git clone https://github.com/OlinREVO/AVR-CAN.git
cd AVR-CAN/
