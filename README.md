# btcmon - very small cryptocurrency monitor

This is a super small windows app to show you the current price of any crypto. <br>
It pulls it from https://api.cryptowat.ch/markets/coinbase-pro/btcusd/price , <br>
which can be changed to another API or currency (default is BTC/USD)<br>
It will update as the window title text (including when minimized) <br>

<b>Why?</b>
(other than 'I got bored')

RAM usage:<br>
this app < 3MB <br>
cryptowat.ch on a browser > 20MB (just for that tab)  <br>

<b>Compiling</b>

Required libraries:<br>
C++ Requests :
<br>https://whoshuu.github.io/cpr/
<br> (c++ requests uses curl and https://github.com/nlohmann/json )
