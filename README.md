# Arduino Clock
<h2> Presentation </h2>
This project is as simple as his title, just a clock display on a 4 Digital 7 Segment Display. The hour can be change via a remote control.

<h2> Modules </h2>
  <ul>
    <li>Arduino card with at least 9 pins</li>
    <li>4 Digital 7 Segment Display</li>
    <li>RTC, in my case I use a DS1307</li>
    <li>IR receiver module</li>
    <li>Decoder (not essential but better to use less pins on arduino card), in my case I use a 74HC595 IC</li>
  </ul>

<h2> Libraries </h2>
  <ul>
    <li>IRremote.h</li>
    <p>to manage the remote control</p>
    <li>Wire.h</li>
    <p>allow you to communicate with SDA and SCL pins of the Arduino card (usefull for the RTC)</p><p>you can see where is your SDA and SCL pins here : https://www.arduino.cc/en/reference/wire</p>
    <li>DS1307.h</li>
    <p>to create an instance of clock object to get the hour</p>
  </ul>
