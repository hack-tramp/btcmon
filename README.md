# btcmon - super small cryptocurrency monitor

This is a super small (<500KB on disk, 1.5MB in RAM) windows app to show you the live price of any crypto pair. <br><br>
It pulls it from https://api.cryptowat.ch/markets/coinbase-pro/btcusd/price  <br>

The price is set as the window title text, including when minimized on the taskbar <br>

<b>Why?</b>
(other than 'I got bored')

RAM usage:<br>
this app < 2MB <br>
cryptowat.ch on a browser > 20MB (just for that tab)  <br>

<b>Compiling</b>

Required libraries:<br>
cpr (https://whoshuu.github.io/cpr/) - see btcmon-cpr.cpp<br>
or<br>
curl (https://curl.haxx.se/libcurl/) - see btcmon.cpp

