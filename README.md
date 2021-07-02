# SERIAL-TO-ESP-NOW
If you want to send data from your pc to ESP Slaves from a ESP Master using ESP-NOW, here is your solution


## HOW TO USE THIS REPO ? 

First:
```
git clone [address of the repo]
```

Then you need to push the ESP-NOW/ESP_code/ESP_master.ino to your master and ESP-NOW/ESP_code/ESP_slave.ino to your two slaves. 

When everything is connected, yout need to launch the python code:
```
python3 send_data.py
```

You'll need to input some values, is they are above 10 the LED will be ON and if it's under 10 the LED will be OFF.
