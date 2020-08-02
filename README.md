# btcmon - very small cryptocurrency monitor

This is a super small (<500KB) windows app to show you the current price of any crypto. <br><br>
It pulls it from https://api.cryptowat.ch/markets/coinbase-pro/btcusd/price  <br>
can be changed to another currency pair (default is BTC/USD)<br><br>
price is set as the window title text, including when minimized on the taskbar <br>

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

